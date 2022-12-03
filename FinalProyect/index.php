<?php

$temp = $_POST['temp'];
$hume = $_POST['hume'];
echo "La temperatura es: ". $temp. " <br> La humedad es: " .$hume;

$usuario = "root";
$contrasena = "root";
$servidor = "localhost";
$basededatos = "final proyect";

$conexion = mysqli_connect($servidor, $usuario, $contrasena) or die ("No se ha podido conectar al servidor de mySQL");

$db = mysqli_select_db($conexion, $basededatos) or die ("No se ha podido seleccionar la base de datos");

$fecha = time();
$sql = "INSERT INTO data(Date, Temperature, Humidity) VALUES(" .$fecha. ", " .$temp. ", " .$hume. ")";

$resultado = mysqli_query($conexion, $sql);
?>