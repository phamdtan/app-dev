<?php

$max = $_POST['max'];
$peaks = $_POST['peaks'];
$today = date("Y-m-d H:i:s");
$record = $today . ", Maximum decibel: " . $max . ", Number of peaks: " . $peaks . "\n";

$file = "sound.log";
if(file_exists($file))
    $fp = fopen($file, "a");
else
    $fp = fopen($file, "w");
fwrite($fp, $record);
fclose($fp);
echo "From e1900313\n";
?>


