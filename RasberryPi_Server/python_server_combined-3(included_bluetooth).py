import socket
from _thread import *
import time 
from bluetooth import *
import sqlite3

#-*- coding:utf-8 -*-
import paho.mqtt.client as mqtt

mqtt = mqtt.Client("python_pub") #Mqtt Client 오브젝트 생성
mqtt.connect("192.168.0.58", 1883) #MQTT 서버에 연결
blue_socket=BluetoothSocket( RFCOMM ) # bluetooth 연결
blue_socket.connect(("98:DA:60:01:8A:5F", 1))
print("bluetooth Connected!")
print('server start')
con = sqlite3.connect("santa.db")
cur = con.cursor()
print('wait')
HOST = ''
PORT = 7788
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
server_socket.bind((HOST,PORT))
server_socket.listen()

'''MQTT'''
OPR1_MQTT = "OFF"
OPR2_MQTT = "OFF"
OPR3_MQTT = "OFF"
OPR4_MQTT = "OFF"
OPR5_MQTT = "OFF"
OPR6_MQTT = "OFF"
OPR7_MQTT = "OFF"

def threaded(client_socket,addr):
        print('Connected by:', addr[0], ':', addr[1])
        while True:
                try:
                        data = client_socket.recv(1024)

                        if not data:
                                print('Disconnected by' + addr[0],':',addr[1])
                                break

                        print('Received from' + addr[0],':',addr[1],data.decode())

                        client_socket.send(data)

                except ConnectionResetError as e:
                        print('Disconnected by'+addr[0],':',addr[1])
                        break

        client_socket.close()


def loop():
        client_socket, addr = server_socket.accept()
        #start_new_thread(threaded, (client_socket, addr))
        while True:
                #if not data:
                #        print('Disconnected by' + addr[0],':',addr[1])
                #        break
                #설명: 클라이언트로 부터 데이터 수신
                data = client_socket.recv(1024)
                print('Received from' + addr[0],':',addr[1],data.decode())

                #설명:bytes형태 -> str형태로 변경
                text_data = data.decode()

                #배송주문이 있는지 확인해서 있으면 OPR1_START 신호 송신
                #cur.execute("select child_name, child_address from delivery_t where delivery_status = 0;")
                #signal = cur.fetchall())
                #if(signal){
                #       text = "OPR1_START"  # 생산 시작 신호
                #       text_byte = text.encode('utf-8')
                #       client_socket.sendall(text_byte)
                #}
                
                #OPR1 종료 데이터 수신 시 delivery_t, production_t 데이터 삽입 및 2공정 시작 신호 송신
                if text_data == 'OPR1_END':
                        
                        '''MQTT'''
                        global OPR1_MQTT
                        OPR1_MQTT = "ON"
                        time.sleep(1)
                        global OPR2_MQTT
                        OPR2_MQTT = "ON"
                        
                        print('1공정 끝')

                        # delivery_t 테이블에 데이터 삽입, production_t 테이블에 데이터 삽입(delivery_t 에 저장될 데이터 저장 형식 결정 필요
                        # ex) 앱 인벤터통해 등록 후, 고객 정보 등록 후 랜덤으로 불러와서 할지 등)
                        #cur.execute("insert into delivery_t (child_name ,product_name ,delivery_status) values('홍길동','선물상자',0);")
                        #con.commit()
                        #time.sleep(0.5)
                        
                        cur.execute("insert into production_t(delivery_num, opr_stat, prd_stat) select seq as delivery_num,'OPR1','1' from sqlite_sequence;")
                        con.commit()

                        # 데이터 송신 시 byte 형태로 변경하여 보냄
                        text = "OPR2_START"  # 로봇1(컨베이어로 옮기는 로봇) 작동 신호 송신
                        text_byte = text.encode('utf-8')
                        client_socket.sendall(text_byte)
                        text_data = '0'

                #OPR2 종료 데이터 수신 시 production_t OPR1 -> OPR2 업데이트 및 3공정 시작 신호 송신
                if text_data == 'OPR2_END':
                                        
                        '''MQTT'''
                        OPR1_MQTT = "OFF"
                        OPR2_MQTT = "OFF"
                        global OPR3_MQTT
                        OPR3_MQTT = "ON"                    
                        
                        print('2공정 끝')

                        # production_t 테이블의 opr_stat을 OPR2로 업데이트
                        cur.execute("update production_t set opr_stat ='OPR2' where opr_stat = 'OPR1' and delivery_num = (select seq from sqlite_sequence);")
                        con.commit()
                        time.sleep(0.5)
                        text = "OPR3_START" # 로봇2(리본 부착하는 생산 로봇) 작동 신호 송신
                        text_byte = text.encode('utf-8')
                        client_socket.sendall(text_byte)
                        time.sleep(0.5)

                #OPR3 종료 데이터 수신 시 production_t OPR2 -> OPR3 업데이트 및 4공정 시작 신호 송신
                if text_data == 'OPR3_END':
                                        
                        '''MQTT'''
                        OPR3_MQTT = "OFF"
                        global OPR4_MQTT
                        OPR4_MQTT = "ON"
                        
                        print('3공정 끝')

                        # production_t 테이블의 opr_stat을 OPR3로 업데이트
                        cur.execute("update production_t set opr_stat ='OPR3' where opr_stat = 'OPR2' and delivery_num = (select seq from sqlite_sequence);")
                        con.commit()
                        time.sleep(0.5)
                        text = "OPR4_START"  # 비전 검사 작동 신호 송신
                        text_byte = text.encode('utf-8')
                        client_socket.sendall(text_byte)

                #OPR4 종료 데이터 수신 시 production_t OPR3 -> OPR4 업데이트 및 5공정 시작 신호 송신
                if text_data == 'OPR4_END':
                                        
                        '''MQTT'''
                        OPR4_MQTT = "OFF"
                        global OPR5_MQTT
                        OPR5_MQTT = "ON"
                        
                        print('4공정 끝')

                        # production_t 테이블의 opr_stat을 OPR4로 업데이트
                        cur.execute("update production_t set opr_stat ='OPR4' where opr_stat = 'OPR3' and delivery_num = (select seq from sqlite_sequence);")
                        con.commit()
                        text = "OPR5_START"   # 로봇3(썰매에 적재하는 이동 로봇) 작동 신호 송신
                        text_byte = text.encode('utf-8')
                        client_socket.sendall(text_byte)

                #OPR4_ERROR 데이터 수신 시 production_t테이블의 prd_stat 컬럼 '0'(불량)업데이트 및 6공정(불량품 이동) 시작 신호 송신
                if text_data == 'OPR4_ERROR':
                                                        
                        '''MQTT'''
                        OPR4_MQTT = "OFF"
                        OPR5_MQTT = "ON"
                                               
                        print('불량품 이동 공정 끝')

                        # production_t 테이블의 prd_stat을 '0'(불량)으로 업데이트
                        cur.execute("update production_t set prd_stat = '0' where opr_stat = 'OPR3' and delivery_num = (select seq from sqlite_sequence);")
                        con.commit()
                        text = "OPR6_START" # 불량품 적재장소로 상자 이동하도록 로봇에 신호 송신
                        text_byte = text.encode('utf-8')
                        client_socket.sendall(text_byte)


                #OPR5 종료 데이터 수신 시 production_t OPR4 -> OPR5 업데이트 및 7공정 시작 신호 송신
                if text_data == 'OPR5_END':
                         
                        '''MQTT'''
                        OPR5_MQTT = "OFF"
                        global OPR6_MQTT
                        OPR6_MQTT = "ON"
                
                        print('5공정 끝')

                        # production_t 테이블의 opr_stat을 OPR5로 업데이트
                        cur.execute("update production_t set opr_stat ='OPR5' where opr_stat = 'OPR4' and delivery_num = (select seq from sqlite_sequence);")
                        con.commit()

                        # delivery_t에 Address확인하여 차량에 주소 송신
                        result = cur.execute("select child_address from(select * from delivery_t where delivery_status = 0 order by ROWID LIMIT 1);")
                        while True:
                            row = result.fetchone()
                            if row == None:
                                break
                            msg = row[0]+"_GO"
                            blue_socket.send(msg)
                            break;

                        #아래 3줄은 필요 없는 구문
                        text = "OPR7_START"   # 썰매에 배송 출발 신호 송신(배송지에 따라 다른 데이터 보내야함)
                        text_byte = text.encode('utf-8')
                        client_socket.sendall(text_byte)
                        
                #OPR6 종료 데이터 수신 시 production_t OPR5 -> OPR6 업데이트 및 7공정 시작 신호 송신
                if text_data == 'OPR6_END':
                        print('6공정 끝')
                                                                
                        '''MQTT'''
                        OPR_MQTT = "OFF"
                        global OPR7_MQTT
                        OPR7_MQTT = "ON"
                        

                        # production_t 테이블의 opr_stat을 OPR6로 업데이트
                        #cur.execute("update production_t set opr_stat ='OPR6' where opr_stat = 'OPR5' and delivery_num = (select seq from sqlite_sequence);")
                        #con.commit()
                        #text = "OPR6_START"
                        #text_byte = text.encode('utf-8')
                        #client_socket.sendall(text_byte)

                #OPR7 종료 데이터 수신 시 delivery_t delivery_status(배송상태) 1->2(배송완료)로 업데이트
                if text_data == 'OPR7_END':               
                                                       
                        
                        print('공정 끝')

                        # production_t 테이블의 opr_stat을 OPR6로 업데이트
                        #cur.execute("update production_t set opr_stat ='OPR6' where opr_stat = 'OPR5' and delivery_num = (select seq from sqlite_sequence);")
                        #con.commit()
                        #text = "OPR6_START"
                        #text_byte = text.encode('utf-8')
                        #client_socket.sendall(text_byte)
                        
                mqtt.publish("OPR1_START", OPR1_MQTT)
                mqtt.publish("OPR2_START", OPR2_MQTT)
                mqtt.publish("OPR3_START", OPR3_MQTT)
                mqtt.publish("OPR4_START", OPR4_MQTT)
                mqtt.publish("OPR5_START", OPR5_MQTT)
                mqtt.publish("OPR6_START", OPR6_MQTT)
                mqtt.publish("OPR7_START", OPR7_MQTT)


if __name__=="__main__":
        loop()



server_socket.close()
