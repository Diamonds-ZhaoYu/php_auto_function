<?php 
$aaaa = "aaaa";
function autofunction( $file) 
{
  echo "class name: " . $file.PHP_EOL;
}
zhaoyu_set_autofunction("autofunction");
var_dump(zhaoyu_get_all_global_vars());
var_dump(zhaoyu_get_all_classes());
var_dump(zhaoyu_get_all_functions());
new xa();
