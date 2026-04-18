<?PHP

  // CONFIG LOAD..
  define("SEAMINER_CONFIG_PATH", __DIR__ . DIRECTORY_SEPARATOR . "config.inc");
 
  require(SEAMINER_CONFIG_PATH);

  // CHECK CONFIG
  if (!is_readable(SEAMINER_CACHE_PATH)) {
    die("SeaMiner Config Error. Invalid cache path, cache path doesn't exist.<br>");
  }

  if (!is_readable(SEAMINER_CACHE_PATH . DIRECTORY_SEPARATOR . "root")) {
    die("SeaMiner Config Error. Invalid root cache path, root cache path doesn't exist.<br>");
  }

  // VARIABLES AND FUNCTION DECLARATION
  define("SEAMINER_FUNC_PATH", __DIR__ . DIRECTORY_SEPARATOR . "func.inc");

  require(SEAMINER_FUNC_PATH);  

  //if ( $_SERVER['SCRIPT_FILENAME'] !== SEAMINER_WRITER_FILENAME ) {
  //  if (!refererCheck()) {
  //    die("SeaMiner Access Error. Invalid referer.<br>");
  //  }
  //}
