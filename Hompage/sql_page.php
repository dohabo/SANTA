<?php
echo "POST_1 : ";
echo $_POST[Name];
$DB = new SQLite3('santa.db');

if($DB->lastErrorCode() == 0){
	echo "Database connection succeed!";
}
else {
	echo "Database connection failed";
    echo $DB->lastErrorMsg();
}

echo "POST_1 : ";
echo $_POST[Name];
echo "<br>";
echo "POST_2 : ";
echo $_POST[Address];
echo "<br>";
echo "GET_1 : ";
echo $_GET[Products];
echo "<br>";
echo "GET_2 : ";
echo $_GET[Message];

$DB->exec("INSERT INTO 'children' ('name','address') VALUES ('bskyvision','a');");
$DB->exec("commit();");
?>