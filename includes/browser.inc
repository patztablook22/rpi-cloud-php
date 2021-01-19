<?php

class Browser {

  private $imageExtensions;
  private $root;
  private $pathFull;
  private $dirFull;
  public  $path;
  public  $valid;
  public  $isDir;
  public  $filename;
  public  $image;

  function __construct($root, $path) {
    $this->root       =   $root.'/';
    $this->path       =   substr( urldecode($path), 1 );
    $this->path       =   explode("?", $this->path)[0];
    $this->pathFull   =   $this->root.$this->path;
    $this->dirFull    =   pathinfo( $this->pathFull, PATHINFO_DIRNAME );
    $this->filename   =   pathinfo( $this->path, PATHINFO_FILENAME );
    $this->isDir      = is_dir($this->pathFull);

    if ( strpos($this->path, "..") === false ) {
      $this->valid = file_exists($this->pathFull);
    } else {
      $this->valid = false;
    }

    if ( ! $this->valid ) {
      return;
    }


  }

  function path() {
    $parents = explode("/", $this->path);
    array_unshift($parents, "DISK");
    for ($i = 0; $i < sizeof($parents); $i++) {
      if ($i != 0)
        echo "/";
      echo "<a href=\"/";
      for ($j = 0; $j < $i; $j++) {
        if ($j != 0)
          echo "/";
        echo $parents[$j + 1];
      }
      echo "\">".$parents[$i]."</a>";
    }
    echo "\n";
  }

  function show() {
    if ( $this-> valid ) {
      if ( $this->isDir )
        $this->showDir();
     else
       $this->showFile();
    }
  }

  private function showDir() {
    echo "<div class=\"showDir\">\n";
    $ls = scandir($this->pathFull);

    foreach ($ls as $i) {
      if (is_dir($this->pathFull."/".$i))
        $this->dirItem($i);
    }

    foreach ($ls as $i) {
      if (!is_dir($this->pathFull."/".$i))
        $this->dirItem($i);
    }
    echo "\t</div>\n";
  }

  private function dirItem($i) {
      if ( $i[0] == "." && $i != ".." )
        return;

      $url = $this->path;

      if (!empty($url) && substr($url, -1) != "/")
        $url.= "/";
      $url.= $i;
    
      echo "\t\t<a class=\"dirItem\" href=\"/$url\">$i";

      if ($i != ".." && is_dir($this->pathFull."/".$i))
        echo "/";

      echo "</a><br />\n";
  }

  private function showFile() {

    echo "<div class=\"showFile\">\n";

    $extension   = pathinfo( $this->path, PATHINFO_EXTENSION );
    $description = $this->dirFull."/.".$this->filename.".".$extension.".md";

    if (file_exists($description)) {
      $fd  = fopen($description, "r") or die("couldn't read description file");
      $buf = trim(fread($fd, filesize($description)));
      echo "\t\t<p class=\"comment\">\"$buf\"</p><br />\n";
    }

    echo "\t\t";

    switch ($extension) {
    case "mp3":
      echo "<audio src=\"/$this->pathFull\" autoplay controls> </audio>";
      break;
    case "png":
    case "jpg":
      echo "<img src=\"/$this->pathFull\" />";
      break;
    case "mp4":
      echo "<video width=\"320\" height=\"240\" controls>"
        ."<source src=\"/$this->pathFull\" type=\"video/mp4\">"
        ."</video>";
      break;
    case "txt":
    case "md":
      $fd = fopen($this->pathFull, "r") or die("couldn't read the file");
      echo "<pre>".fread($fd, filesize($this->pathFull))."</pre>";
      fclose($fd);
      break;
    default:
      echo "a file";
      header("Location: /$this->pathFull");
      break;
    }

    echo "\n\t</div>\n";

  }


}

?>
