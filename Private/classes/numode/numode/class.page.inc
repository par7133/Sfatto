<?php

/**
 * Copyright (c) 2016, 2028 NuMode
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither NuMode nor the names of its contributors 
 *       may be used to endorse or promote products derived from this software 
 *       without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * class.page.inc
 * 
 * Page class.
 *
 * @author Daniele Bonini <code@gaox.io>
 * @copyrights (c) 2016, 2028 NuMode 
 * @license https://opensource.org/licenses/BSD-3-Clause 
 */

namespace numode\numode;

/**
 * Page
 *
 * Page class
 *
 * @package  Page
 * @author   Daniele Bonini <code@gaox.io>
 * @version  2.0
 * @access   public
 */
final class Page 
{
  
  const URL_OUTPUT_RAW = 1;
  const URL_OUTPUT_FORMATTED = 2;
  const URL_OUTPUT_TEXT = 3;
  
  /**
   * Default constructor
   * 
   * @return void
   */
  private function __construct()
  {
  }
  
  /**
   * The buffer for the javascript of page footer
   *  
   * @access private
   * @var Array
   */
  private static $aFooterJSBuffer = Array2::PHP_EMPTY;
  
  /**
   * Add the given javascript code to the page buffer
   * 
   * @param string $JScode the JS code to add in the page footer
   */
  public static function addToJSBuffer(string $JScode): void
  {
    self::$aFooterJSBuffer[] = $JScode;
  }

  /**
   * Clear the page buffer for the javascript code
   */
  public static function clearJSBuffer(): void 
  {
    self::$aFooterJSBuffer = Array2::PHP_EMPTY;
  }

  /**
   * Display the content of the page buffer for the javascript code
   */
  public static function displayJSBuffer(): void
  {
    foreach(self::$aFooterJSBuffer as $JScode) {
      echo $JScode . PHP_EOL. PHP_EOL;
    }  
  }
  
  /**
   * Enable the links of the given text
   * 
   * @param string $text the text being parsed for links
   * @return the text with enabled links
   */
  public static function enableEmailLinks(string $text, bool $masked): string
  {
    settype($text, "string");
    settype($masked, "boolean");
    
    $callable_masked = function($aResults) {
      $result = implode(PHP_STR, $aResults); 
      return "<a href='mailto:$result'>" . mb_strrichr($result, "@", true) . "@.." . mb_strrichr($result, ".", false) . "</a>";
    };

    $callable_unmasked = function($aResults) {
      $result = implode(PHP_STR, $aResults); 
      return "<a href='mailto:$result'>$result</a>";
    };

    $regexPattern = "/(([A-Za-z0-9]+_+)|([A-Za-z0-9]+\-+)|([A-Za-z0-9]+\.+)|([A-Za-z0-9]+\++))*[A-Za-z0-9]+@((\w+\-+)|(\w+\.))*\w{1,63}\.[a-zA-Z]{2,6}/";
    
    if ($masked) {
      $callable = $callable_masked;
    } else {
      $callable = $callable_unmasked;
    } 
    
    return preg_replace_callback($regexPattern, $callable, $text);
  }  

  /**
   * Enable the links of the given text
   * 
   * @param string $text the text being parsed for links
   * @return the text with enabled links
   */
  public static function enableLinks(string $text): string
  {
    //return preg_replace("/(https?:\/\/)?([\da-z\.-]+)\.([a-z\.]{2,8})([\/\w \.-]*)$/", "\\0&nbsp;<a href='\\0' target=\"_blank\">[#1]</a>", $text);
    return preg_replace("/(https?:\/\/)([\da-z\.-]+)\.([a-z\.]{2,8})(\/?.+)?$/", "<span style='color:darkgray; background:#E0E0E0;'>\\0&nbsp;[&nbsp;<a href='\\0' target=\"_blank\" style=\"font-size: large;\">@</a>&nbsp;]</span>", $text);
  }  
  
  /**
   * Enable the links of the given text
   * 
   * @param string $text the text being parsed for links
   * @return the text with enabled links
   */
  public static function getFirstEnabledLink(string $text, bool $formatted = true): string
  {
    $matches = [];
    $bDFLTLINK = false;
    //return preg_replace("/(https?:\/\/)([\da-z\.-]+)\.([a-z\.]{2,8})(\/?.+)?$/", "<span style='color:darkgray; background:#E0E0E0;'>\\0&nbsp;[&nbsp;<a href='\\0' target=\"_blank\" style=\"font-size: large;\">@</a>&nbsp;]</span>", $text);
    //$preg_retval = preg_match("/(https?:\/\/[\da-z\.-]+\.[a-z\.]{2,8}(\/?.+)?)$/", $text, $matches);
    $preg_retval = preg_match("/((https?:\/\/)?[\w\.-]+\.[a-z\.]{2,8}(\/?.+)?)$/", $text, $matches);
    if ($preg_retval>=1) {
      //return preg_replace("/^(https?:\/\/)(([\da-z\.-]+)\.([a-z\.]{2,8}))(\/?[.]+)?$/", "<a class='link-image' href='\\0' target='_blank'>\\2</a>", $matches[1]);
      $url = $matches[1];
    } else {
      //return preg_replace("/^(https?:\/\/)(([\da-z\.-]+)\.([a-z\.]{2,8}))(\/?[.]+)?$/", "<a class='link-image' href='\\0' target='_blank'>\\2</a>", ENGINE_DFLTLINK);
      $url = ENGINE_DFLTLINK;
    }  

    if (mb_stripos1($url, ENGINE_DFLTLINK)) {
      $bDFLTLINK = true;
    }  
    
    $url = str_replace(PHP_TILDE, PHP_SLASH, $url);
    
    $urlText = preg_replace("/(https?:\/\/)(([\da-z\.-]+)\.([a-z\.]{2,8}))(\/?.+)?$/", "\\2", $url);
    
    if ($formatted) {
      /*
      if ($bDFLTLINK) { 
        return "[AD]&nbsp;<a class='link-image' href='http://" . $url . "' target='_blank'>" . (mb_strlen($urlText)<=26 ? $urlText : left($urlText, 10) . ".." . right($urlText, 14)) . "</a>";
      } else {  
        return "<a class='link-image' href='http://" . $url . "' target='_blank'>" . (mb_strlen($urlText)<=26 ? $urlText : left($urlText, 10) . ".." . right($urlText, 14)) . "</a>";
      } */
      
      if ($bDFLTLINK) { 
        return "[AD]&nbsp;<a class='link-image' onclick='openLink(\"http://" . $url . "\",\"_blank\")'>" . (mb_strlen($urlText)<=26 ? $urlText : left($urlText, 10) . ".." . right($urlText, 14)) . "</a>";
      } else {  
        return "<a class='link-image' onclick='openLink(\"http://" . $url . "\",\"_blank\")'>" . (mb_strlen($urlText)<=26 ? $urlText : left($urlText, 10) . ".." . right($urlText, 14)) . "</a>";
      }  
      
    } else {
      return $urlText; 
    }  
  }
  
  /**
   * Get the gallery url
   * 
   * @param string $desc the text being parsed for links
   * @param int $output the kind of output
   * @return the text with enabled links
   */
  public static function getGalleryUrl(string $desc, int $output = self::URL_OUTPUT_FORMATTED): string
  {
    $matches = [];
    $bDFLTLINK = false;

    $preg_retval = preg_match("/((https?:\/\/)?[\w\.-]+\.[a-z\.]{2,8}(\/?.+)?)$/", $desc, $matches);
    if ($preg_retval>=1) {
      $url = $matches[1];
    } else {
      $url = ENGINE_DFLTLINK;
    }  

    if ($output === self::URL_OUTPUT_RAW) {
      return $url;      
    }
    
    if (mb_stripos1($url, ENGINE_DFLTLINK)) {
      $bDFLTLINK = true;
    }  
    
    $url = str_replace(PHP_TILDE, PHP_SLASH, $url);
    
    $urlText = preg_replace("/(https?:\/\/)(([\da-z\.-]+)\.([a-z\.]{2,8}))(\/?.+)?$/", "\\2", $url);
    
    if ($output === self::URL_OUTPUT_FORMATTED) {
      
      if ($bDFLTLINK) { 
        return "[AD]&nbsp;<a class='link-image' onclick='openLink(\"http://" . $url . "\",\"_blank\")'>" . (mb_strlen($urlText)<=26 ? $urlText : left($urlText, 10) . ".." . right($urlText, 14)) . "</a>";
      } else {  
        return "<a class='link-image' onclick='openLink(\"http://" . $url . "\",\"_blank\")'>" . (mb_strlen($urlText)<=26 ? $urlText : left($urlText, 10) . ".." . right($urlText, 14)) . "</a>";
      }  
      
    } else {
      return $urlText; 
    }  
  }
  
  
  /**
   * Encode any HTML of a given string
   * 
   * @param string $s the string to encode
   * @param bool $withBR keep the BR tag, true/false
   * @return string the string encoded
   */
  public static function HTMLencode(?string $s, bool $withBR = false): string 
  {
    if (!isset($s)) {
      return PHP_STR;
    }
    
    $s = str_ireplace("&#39;", "'", $s); 
    $s = str_ireplace("&#34;", "\"", $s);
    $s = str_ireplace("\\n", chr(10), $s);
    $s = htmlspecialchars($s, ENT_QUOTES |ENT_IGNORE | ENT_HTML5, "UTF-8");
    
    if ($withBR) {
      $s = str_ireplace(chr(10), PHP_BR, $s);
    }  
    
    return $s;
  }
  
  /**
   * Set headers to no cache
   * 
   * @param integer $interval the interval in seconds
   */
  public static function setNoCacheHeaders(): void 
  {
    // Backwards Compatibility for HTTP/1.0 clients
    header("Expires: 0");
    header("Pragma: no-cache");
    // HTTP/1.1 support
    header("Cache-Control: no-cache,no-store,max-age=0,s-maxage=0,must-revalidate");
  }
  
  /**
   * Set headers to private cache
   * 
   * @param integer $interval the interval in seconds
   */
  public static function setPrivateCacheHeaders(int $interval = 300): void
  {
    $now = time();
    $pretty_lmtime = gmdate("D, d M Y H:i:s", $now) . " GMT";
    $pretty_extime = gmdate("D, d M Y H:i:s", $now + $interval) . " GMT";
    // Backwards Compatibility for HTTP/1.0 clients
    header("Last Modified: $pretty_lmtime");
    header("Expires: $pretty_extime");
    header("Pragma: ");
    // HTTP/1.1 support
    header("Cache-Control: private,max-age=$interval,s-maxage=0");
  }
  
  /**
   * Set headers to public cache
   * 
   * @param integer $interval the interval in seconds
   */
  public static function setPublicCacheHeaders(int $interval = 300): void
  {
    $now = time();
    $pretty_lmtime = gmdate("D, d M Y H:i:s", $now) . " GMT";
    $pretty_extime = gmdate("D, d M Y H:i:s", $now + $interval) . " GMT";
    // Backwards Compatibility for HTTP/1.0 clients
    header("Last Modified: $pretty_lmtime");
    header("Expires: $pretty_extime");
    header("Pragma: ");
    // HTTP/1.1 support
    header("Cache-Control: public,max-age=$interval");
  }
  
  /** 
   * Make a redirect
   * 
   * @param string $newUrl the url to redirect to
   */
  public static function redirect(string $newUrl): void  
  {
    if (headers_sent()) {
      echo("<script>window.location.replace('" . $newUrl . "');</script>");
    } else {
      header("HTTP/1.0 302 Redirect");
      header('Location: ' . $newUrl);
    } 
    exit();
  }

  /** 
   * Make a permanent redirect
   * 
   * @param string $newUrl the url to redirect to
   */
  public static function redirectPerm(string $newUrl): void  
  {
    if (headers_sent()) {
      echo("<script>window.location.replace('" . $newUrl . "');</script>");
    } else {
      header("HTTP/1.0 301 Moved Permanently");
      header('Location: ' . $newUrl);
    } 
    exit();
  }
  
}
