<?php

/**
 * Copyright 2021, 2028 NuMode
 *
 * This file is part of Sfatto.
 * 
 * Sfatto is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Sfatto is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.  
 * 
 * You should have received a copy of the GNU General Public License
 * along with Sfatto. If not, see <https://www.gnu.org/licenses/>.
 *
 * init.inc
 * 
 * Sfatto Initialization file.
 *
 * @author Daniele Bonini <code@gaox.io>
 * @copyrights (c) 2016, 2028 NuMode   
 */

use numode\numode\Page;
use numode\numode\Session;

error_reporting(E_ALL & ~ (E_WARNING | E_NOTICE | E_STRICT | E_DEPRECATED));  
ini_set('display_startup_errors',1);  
ini_set('display_errors',1);  
ini_set('log_errors',1); 


// CONFIGURATION
define("CONFIG_PATH", __DIR__ . DIRECTORY_SEPARATOR . ".." . DIRECTORY_SEPARATOR . "config");

require CONFIG_PATH . DIRECTORY_SEPARATOR . "config.inc";
require CONFIG_PATH . DIRECTORY_SEPARATOR . "const.php.inc";

define("FUNCTIONS_PATH", __DIR__ . DIRECTORY_SEPARATOR . ".." . DIRECTORY_SEPARATOR . "functions");

require FUNCTIONS_PATH . DIRECTORY_SEPARATOR . "func.string.inc";
require FUNCTIONS_PATH . DIRECTORY_SEPARATOR . "func.various.inc";


mb_internal_encoding("UTF-8");


// AUTOLOADER

define("CLASSES_PATH", __DIR__ . DIRECTORY_SEPARATOR . ".." . DIRECTORY_SEPARATOR . "classes");
define("INTERFACES_PATH", __DIR__ . DIRECTORY_SEPARATOR . ".." . DIRECTORY_SEPARATOR . "interfaces");

/**
 * Autoloader.
 * 
 * @param string $construct the name of the construct to load
 */
function autoloader($construct) {
  
  // For third-party libraries, eg. Pear
  if (!defined("PHP_INCLUDE_PATH")) {
    define("PHP_INCLUDE_PATH", ini_get("include_path"));
  }
  
  //echo($construct . "<br>");

  $constructParts = explode('\\', $construct);
  
  // estrapolate the path from the construct name
  $count = count($constructParts);
  if ($count>1) {
    $i = 0;
    $constructPath = $constructParts[0];
    for ($i=1; $i<($count-1); $i++) {
      $constructPath .= DIRECTORY_SEPARATOR . $constructParts[$i];
    }
    $construct = $constructParts[$i];
  }
  
  //echo($construct . "<br>");

  if (!stripos($construct, "interface")) {
    // if it is a class
  
    switch ($construct) {
      case "special_case":
        $incPath = PHP_INCLUDE_PATH . DIRECTORY_SEPARATOR . "path/to/special_case.php";
        break;
      case "QRcode":
        $incPath = CLASSES_PATH . DIRECTORY_SEPARATOR . "phpqrcode/qrlib.php";
        //echo "incPath = $incPath" . PHP_BR;
        break;
      default:
      
        if (isset($constructPath)) {
          $incPath = CLASSES_PATH . DIRECTORY_SEPARATOR . $constructPath . DIRECTORY_SEPARATOR . "class." . strtolower($construct) . ".inc";
        } else {
          $incPath = CLASSES_PATH . DIRECTORY_SEPARATOR . "class." . strtolower($construct) . ".inc";
        }
        
        break;
    }
    
  } else {
    // if it is an interface
    if (isset($constructPath)) {
      $incPath = INTERFACES_PATH . DIRECTORY_SEPARATOR  . $constructPath . DIRECTORY_SEPARATOR . strtolower($construct) . ".inc";
    } else {
      $incPath = INTERFACES_PATH . DIRECTORY_SEPARATOR . strtolower($construct) . ".inc";
    }  
  }
  
  if (is_readable($incPath)) {
    //echo "$incPath is readable" . PHP_BR;
    require $incPath;
  }
  
}
spl_autoload_register("autoloader", true, true);


// SESSION
//Session::start();

//$now = time();
////if (Cookie::isEmpty("uid") || Cookie::isEmpty("uname")) {
  //if (Session::exists("timeout") && $now > Session::get("timeout")) {
    ////echo("Session terminating..<br>");
    //Session::destory();
    // Regenerate the session..
    //Session::startWithNewContext();
  //}
////}
// Session should live at most for another half of hour
//Session::set("timeout", ($now + SESSION_TIMEOUT));

//Session::closeEditing();


// ERROR HANDLING AND LOGGING

if (DEBUG) {
  error_reporting(E_ALL | E_STRICT);  
  ini_set('display_startup_errors',1);  
  ini_set('display_errors',1);
  ini_set('log_errors',1); 
} else {
  error_reporting(E_ALL & ~ (E_WARNING | E_NOTICE | E_STRICT | E_DEPRECATED));  
  ini_set('display_startup_errors',0);  
  ini_set('display_errors',0);  
  ini_set('log_errors',1); 
}

//Err::setDefaultHandlers();


// HEADERS

// If we are uploading or testing..

//if ((mb_stripos1($ctrlName, "upload") === 1) ||
//    (mb_stripos1($ctrlName, APP_CTRL_INFO) === 1) ||
//    (mb_stripos1($ctrlName, APP_CTRL_THROW) === 1) ||
//    IS_ADMIN_CTRL)
//{

if (true === true) {

  // Disable the cache..
  Page::setNoCacheHeaders();

} else {
  // Set public cache with 5 minutese expiration..
  //Page::setPublicCacheHeaders(300);

  // Disable the cache..
  Page::setNoCacheHeaders();
}


// SHUTDOWN 

/**
 * Shutdown callback.
 * 
 * @return void
 */
function shutdownCallback() {
  
//Err::setLogOnlyHandlers();

/*  
  if (Cache::issetInstance()) {  
    //For non-persistent connections only
    //$cache = &Cache::getInstance();
    //$cache->close();

    Cache::unsetInstance();
  }
*/
  
}
register_shutdown_function("shutdownCallback");

// ERROR PARAMETERS

//errNo
//define("ERR_NO", substr(filter_input1(INPUT_GET, "errNo", FILTER_SANITIZE_MD5TOKEN), 0, 100));
//if (ERR_NO!==PHP_STR && !filter_var1(ERR_NO, FILTER_VALIDATE_ERRNO)) {
//  Err::trigger_error1(ERR::ERR_ERR, "Invalid error number: " . ERR_NO, __FILE__, __LINE__);
//}

//errKey
//define("ERR_KEY", array_search(ERR_NO, Err::$A_ERR_NO));

//errMsg
//define("ERR_MSG", substr(filter_input1(INPUT_GET, "errMsg", FILTER_SANITIZE_ERRMSG), 0, 200));

//errScript
//define("ERR_SCRIPT", substr(filter_input(INPUT_GET, "errScript", FILTER_SANITIZE_STRING), 0, 255));

//errLine
//define("ERR_LINE",  substr(filter_input(INPUT_GET, "errLine", FILTER_SANITIZE_NUMBER_INT), 0, 5));

//errStack
//define("ERR_STACK", substr(filter_input1(INPUT_GET, "errStack", FILTER_SANITIZE_STRING_WITHBR), 0, 2000));

?>
