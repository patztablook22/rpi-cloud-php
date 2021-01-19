<?php

require_once "includes/browser.inc";
require_once "includes/config.inc"; 

?>

<!DOCTYPE html>
<html lang="en-US">
<head>
</head>
  <?php include "includes/head.inc"; ?>
<body>

  <nav>
    <?= $browser->path() ?>
  </nav>

  <main>
    <?= $browser->show() ?>
  </main>

</body>
</html>
