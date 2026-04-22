<?PHP

function searefererCheck(): bool 
{ 
  $ret = true;
  if ( SEAMINER_REFERER_CHECK === "ENFORCE" ) {
    $referer = filter_input(INPUT_SERVER, "HTTP_REFERER"); 
    //echo("referer=$referer");
    if (mb_stripos(SEAMINER_REFERER_ACCEPTED, $referer) === false) {
      $ret = false;  
    }
  }
  return $ret;
}


function seacreateNewUpd($newupdAccount, $newupdSign, $newupdTitle, $newupdText) {

  // Create the empty scafoldings..
  $newupdFilename = $newupdSign . "-" . "UPD000001" . ".xml";

  $sourcePath = SEAMINER_PATH . DIRECTORY_SEPARATOR . "template.xml";
  $destFileName = $newupdFilename;
  $destPath = SEAMINER_CACHE_PATH . DIRECTORY_SEPARATOR . $newupdAccount . DIRECTORY_SEPARATOR . $destFileName;

  if (!is_readable(SEAMINER_CACHE_PATH . DIRECTORY_SEPARATOR . $newupdAccount)) {
    mkdir(SEAMINER_CACHE_PATH . DIRECTORY_SEPARATOR . $newupdAccount);
  }

  copy($sourcePath, $destPath);

  $fpath = $destPath;

  // Fill variables and data in..
  $fileCont = file_get_contents($fpath);
  $fileCont = str_replace("%FILENAME%", $newupdFilename, $fileCont);

  $fileCont .= "" . PHP_EOL;

  $fileCont .= "<CONTENT>" . PHP_EOL;
  $fileCont .= "  <UPDATE>" . PHP_EOL;
  $fileCont .= "    <TITLE>" . $newupdTitle . "</TITLE>" . PHP_EOL;
  $fileCont .= "    <TEXT>" . $newupdText . "</TEXT>" . PHP_EOL;
  $fileCont .= "  </UPDATE>" . PHP_EOL;
  $fileCont .= "</CONTENT>" . PHP_EOL;

  file_put_contents($fpath, $fileCont);
}
