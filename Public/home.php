<?PHP

/**
 * Copyright (c) 2016, 2028 NuMode
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
 * home.php
 * 
 * Sfatto homapage.
 *
 * @author Daniele Bonini <code@gaox.io>
 * @copyrights (c) 2016, 2028 NuMode     
 * @license https://opensource.org/licenses/BSD-3-Clause 
 */


   $status = "";

   $date = date("Ymd");
   if ((int)file_get_contents("https://" . APP_HOST . "/".AVATAR_NAME."/seastats/?op=checkdateforupd&date=$date&account=".AVATAR_NAME) > 0) {

     $dom = new DOMDocument;
     $dom->loadXML(file_get_contents("https://" . APP_HOST . "/".AVATAR_NAME."/seaminer/?date=$date&account=".AVATAR_NAME));
     if (!$dom) {
       die("Sfatto Xml Parsing Error. XML file format problem detected.<br>");
     }

     $CONTENT = simplexml_import_dom($dom);
 
     $ai = count($CONTENT->UPDATE)-1;

     $ret = [
       'ID'=>$CONTENT->UPDATE[$ai]->ID,
       'TITLE'=>$CONTENT->UPDATE[$ai]->TITLE,
       'TEXT'=>$CONTENT->UPDATE[$ai]->TEXT,
       'INDEX'=>$CONTENT->UPDATE[$ai]->INDEX
     ];

     $status = $ret['TEXT'];  

     
   }

   if ($status === "") {
     if (defined("APP_" . strtoupper(AVATAR_NAME) . "_STATUS_CMD") && constant("APP_" . strtoupper(AVATAR_NAME) . "_STATUS_CMD") !== "") {

       $status = exec(constant("APP_" . strtoupper(AVATAR_NAME) . "_STATUS_CMD"));
     }
   } 

   if ($status === "") {
     $status = constant("APP_" . strtoupper(AVATAR_NAME) . "_GENERIC_STATUS");
   }

   echo(enableEmoticons(HTMLencode($status, true)));
