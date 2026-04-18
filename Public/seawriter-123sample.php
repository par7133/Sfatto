<?PHP

 include("../Private/classes/seaminer/init.inc");

 $seaminer_sign = date("Ymd-His") . "-" . mt_rnd(0000000000, 9999999999);
 $seaminer_title = "This is a new title"; 
 $seaminer_text = "This is a new text";
 $seaminer_account = "root"; 
 
 seacreateNewUpd($seaminer_account, $seaminer_sign, $seaminer_title, $seaminer_text);
