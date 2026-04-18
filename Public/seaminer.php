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

function getXMLContent(string $fpath): array
{
  $ret = ['ID'=>'','TITLE'=>'','TEXT'=>'','INDEX'=>''];
  $dom = new DOMDocument;
  $dom->loadXML(file_get_contents($fpath));
  if (!$dom) {
    die("SeaMiner Xml Parsing Error. XML file format problem detected.<br>");
  }
  $CONTENT = simplexml_import_dom($dom);
  $ret = [
    'ID'=>$CONTENT->UPDATE[0]->ID,
    'TITLE'=>$CONTENT->UPDATE[0]->TITLE,
    'TEXT'=>$CONTENT->UPDATE[0]->TEXT,
    'INDEX'=>$CONTENT->UPDATE[0]->INDEX
  ];
  return $ret;
}

// ACCOUNT
$account = strip_tags(filter_input(INPUT_GET, "account")??"");
if (!accountCheck($account)) {
   die("SeaMiner Access Error. Wrong &lt;account&gt; param value: $account given.<br>");
}

$pdate = strip_tags(filter_input(INPUT_GET, "date")??"");

$pid = strip_tags(filter_input(INPUT_GET, "id")??"");

if ($pdate==="" && $pid==="") {
  die("SeaMiner Access Error. Both &lt;date&gt; and &lt;ID&gt; are null.<br>");
}

// OP ROUTER
//
// file format example:
//   source: 20250707-153525-8616016962a|blog353.txt
//   dest: 20250707-153525-8616016962a|UPD000001.xml
//
//   where file date is absolute along all the atomi update  
//
//$op = strip_tags(filter_input(INPUT_GET, "op")??"");

if ($pdate!=="") {
  $op = "checkdateforupd";
} else {
  $op = "checkidforupd";
}

$op_ret = "false";
switch($op) {
  case "checkdateforupd":
    // CHECK A DATE FOR NUMBER OF EXISTING UPDATES..

    // RETURN THE NUMBER OF ATOMIC UPDATES FOR THE GIVEN DATE..
    if (stripos($pdate, "~") === false) {

      $pattern = SEAMINER_CACHE_PATH . DIRECTORY_SEPARATOR . $account . DIRECTORY_SEPARATOR . "$pdate*.xml";
      $entries = glob($pattern);
      if (!empty($entries)) {
        
$XMLdata = <<<XML
<?xml version="1.0" encoding="utf-8"?>
<!-- processing output

GPL 3 License

Copyright 2021, 2028 NuMode

This file is part of SeaMiner.

Symmetry is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

SeaMiner is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.  
 
You should have received a copy of the GNU General Public License
along with SeaMiner. If not, see <https://www.gnu.org/licenses/>.
-->

<CONTENT>

XML;

foreach($entries as $ePath) {
  $a = getXMLContent($ePath);
          
  $XMLdata .= "<UPDATE>";
  $XMLdata .= "<ID>" . $a['ID']. "</ID>";
  $XMLdata .= "<TITLE>" . $a['TITLE']. "</TITLE>";
  $XMLdata .= "<TEXT>" . $a['TEXT']. "</TEXT>";
  $XMLdata .= "<INDEX>" . $a['INDEX']. "</INDEX>";
  $XMLdata .= "</UPDATE>";
}

$XMLdata .= "</CONTENT>";

$op_ret = $XMLdata;
 
      } 
      echo($op_ret);

    } else {

      $op_ret = 0;

      $firstLimit = (int)substr($pdate, 0, 8);
      $secondLimit = (int)substr($pdate, 9, 8);

$XMLdata = <<<XML
<?xml version="1.0" encoding="utf-8"?>
<!--type: seaminer output

GPL 3 License

Copyright 2021, 2028 NuMode

This file is part of SeaMiner.

SeaMiner is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

SeaMiner is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.  
 
You should have received a copy of the GNU General Public License
along with SeaMiner. If not, see <https://www.gnu.org/licenses/>.
-->

<CONTENT>

XML;

for ($i = $firstLimit; $i <= $secondLimit; $i++) {
  $pattern = SEAMINER_CACHE_PATH . DIRECTORY_SEPARATOR . $account . DIRECTORY_SEPARATOR . "$i*.xml";
  $entries = glob($pattern);
  if (!empty($entries)) {

    foreach($entries as $ePath) {
      $a = getXMLContent($ePath);

      $XMLdata .= "<UPDATE>";
      $XMLdata .= "<ID>" . $a['ID']. "</ID>";
      $XMLdata .= "<TITLE>" . $a['TITLE']. "</TITLE>";
      $XMLdata .= "<TEXT>" . $a['TEXT']. "</TEXT>";
      $XMLdata .= "<INDEX>" . $a['INDEX']. "</INDEX>";
      $XMLdata .= "</UPDATE>";
    }
  } 
}

$XMLdata .= "</CONTENT>";

$op_ret = $XMLdata;

      echo($op_ret);

    }

    break;    

  default:
    die("SeaMiner Syntax Error. Wrong &lt;op&gt; value: $op given.<br>");
    break;
}


