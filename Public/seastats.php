<?PHP

include("../Private/classes/seaminer/init.inc");

if (!searefererCheck()) {
  die("SeaMiner Access Error. Invalid referer.<br>");
}

// Functions declaration and params

function accountCheck(string $account) {
  $ret = false;
  $pattern = SEAMINER_CACHE_PATH . DIRECTORY_SEPARATOR . $account;
  $accPaths = glob($pattern, GLOB_ONLYDIR);
  if (!empty($accPaths)) {
    $ret = true;
  }
  return $ret;
}

// ACCOUNT
$account = strip_tags(filter_input(INPUT_GET, "account")??"");
if (!accountCheck($account)) {
  die("SeaMiner Access Error. Wrong &lt;account&gt; param value: $account given.<br>");
}

// OP ROUTER
//
// file format example:
//   source: 20250707-153525-8616016962a|blog353.txt
//   dest: 20250707-153525-8616016962a|UPD000001.xml
//
//   where file date is absolute along all the atomi update  
//
$op = strip_tags(filter_input(INPUT_GET, "op")??"");

$op_ret = "false";
switch($op) {
  case "checkdateforupd":
    // CHECK A DATE FOR NUMBER OF EXISTING UPDATES..

    // DATE
    $pdate = strip_tags(filter_input(INPUT_GET, "date")??"");
    if ($pdate==="") {
      die("SeaMiner Access Error. Wrong &lt;date&gt; param value: $pdate given.<br>");
    }

    // RETURN THE NUMBER OF ATOMIC UPDATES FOR THE GIVEN DATE..

    if (stripos($pdate, "~") === false) {

      $pattern = SEAMINER_CACHE_PATH . DIRECTORY_SEPARATOR . $account . DIRECTORY_SEPARATOR . "$pdate*.xml";
      $entries = glob($pattern);
      if (empty($entries)) {
        $op_ret = 0;
      } else { 
        $op_ret = count($entries); 
      } 
      echo($op_ret);

    } else {

      $op_ret = 0;

      $firstLimit = (int)substr($pdate, 0, 8);
      $secondLimit = (int)substr($pdate, 9, 8);

      $i = $firstLimit;

      for ($i = $firstLimit; $i <= $secondLimit; $i++) {       
        $pattern = SEAMINER_CACHE_PATH . DIRECTORY_SEPARATOR . $account . DIRECTORY_SEPARATOR . "$i*.xml";
        $entries = glob($pattern);
        if (!empty($entries)) {
          $op_ret = $op_ret + count($entries); 
        } 
      }

      echo($op_ret);

    }

    break;    
  case "lastupd":
    // RETURN THE LAST ATOMIC UPDATE DATE..
    $pattern = SEAMINER_CACHE_PATH . DIRECTORY_SEPARATOR . $account . DIRECTORY_SEPARATOR . "*.xml";
    $entries = glob($pattern);
    if (!empty($entries)) {
      rsort($entries);
      $op_ret = substr(basename($entries[0]), 0, 15); 
    } 
    echo($op_ret);
    break;
  case "lastweek":
    // RETURN THE LAST WEEK PERIOD OF UPDATES IN DATE RANGE..
    $pattern = SEAMINER_CACHE_PATH . DIRECTORY_SEPARATOR . $account . DIRECTORY_SEPARATOR . "*.xml";
    $entries = glob($pattern);
    if (!empty($entries)) {
      rsort($entries);
      $lastUpdDate = substr(basename($entries[0]), 0, 15); 
    } 
    $lastUpdDateRefo = substr($lastUpdDate, 0, 4) . "-" . substr($lastUpdDate, 4, 2) . "-" . substr($lastUpdDate, 6, 2);
    $date = new DateTimeImmutable($lastUpdDateRefo);
    $newdate = $date->sub(new DateInterval('PT168H')); 
    $op_ret = $newdate->format("Ymd") . "~" . $date->format("Ymd");
    echo($op_ret);
    break;
  case "lastmonth":
    // RETURN THE LAST WEEK PERIOD OF UPDATES IN DATE RANGE..
    $pattern = SEAMINER_CACHE_PATH . DIRECTORY_SEPARATOR . $account . DIRECTORY_SEPARATOR . "*.xml";
    $entries = glob($pattern);
    if (!empty($entries)) {
      rsort($entries);
      $lastUpdDate = substr(basename($entries[0]), 0, 15); 
    } 
    $lastUpdDateRefo = substr($lastUpdDate, 0, 4) . "-" . substr($lastUpdDate, 4, 2) . "-" . substr($lastUpdDate, 6, 2);
    $date = new DateTimeImmutable($lastUpdDateRefo);
    $newdate = $date->sub(new DateInterval('P1M')); 
    $op_ret = $newdate->format("Ymd") . "~" . $date->format("Ymd");
    echo($op_ret);
    break;
  case "lastupdmonth":
    // RETURN THE LAST WEEK PERIOD OF UPDATES IN DATE RANGE..
    $pattern = SEAMINER_CACHE_PATH . DIRECTORY_SEPARATOR . $account . DIRECTORY_SEPARATOR . "*.xml";
    $entries = glob($pattern);
    if (!empty($entries)) {
      rsort($entries);
      $lastUpdDate = substr(basename($entries[0]), 0, 15); 
    } 
    $lastUpdDateRefo = substr($lastUpdDate, 0, 4) . "-" . substr($lastUpdDate, 4, 2) . "-" . substr($lastUpdDate, 6, 2);
    $monthFirstDayRefo = substr($lastUpdDate, 0, 4) . substr($lastUpdDate, 4, 2) . "01";
    $date = new DateTimeImmutable($lastUpdDateRefo);
    $newdate = new DateTimeImmutable($monthFirstDayRefo);
    $op_ret = $newdate->format("Ymd") . "~" . $date->format("Ymd");
    echo($op_ret);
    break;
  default:
    die("Access Error. Wrong &lt;op&gt; param value: $op given.<br>");
    break;
}


