<?php

$browser = new Browser( "disk", $_SERVER["REQUEST_URI"] );

$pageTitle = "patz&gt; ";

if ( !$browser->valid )
  $pageTitle .= "404";
else
  $pageTitle .= pathinfo($browser->path, PATHINFO_FILENAME);

?>
