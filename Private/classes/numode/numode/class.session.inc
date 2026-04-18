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
 * class.session.inc
 * 
 * Session class.
 *
 * @author Daniele Bonini <code@gaox.io>
 * @copyrights (c) 2016, 2028 NuMode
 * @license https://opensource.org/licenses/BSD-3-Clause 
 */

namespace numode\numode;

/**
 * Session
 *
 * Session class
 *
 * @package  Session
 * @author   Daniele Bonini <code@gaox.io>
 * @version  2.0
 * @access   public
 */
final class Session 
{
  /**
   * Default constructor
   * 
   * @return void
   */
  private function __construct()
  {
  }

  /**
   * Check if the given session variable exists
   * 
   * @param string  $key the key of the variable
   * @return bool  if the session variable exists, true/false
   * @access public
   */
  public static function exists(string $key): bool 
  {
    return isset($_SESSION[$key]) ? true : false;
      
  }
  
  /**
   * Check if the session is started
   * 
   * @return bool  if the session is started, true/false
   * @access public
   */
  public static function isStarted(): bool
  {
    return isset($_SESSION) ? true : false;
  }

  /**
   * Check if the session is active
   * 
   * @return bool  if the session is active, true/false
   * @access public
   */
  public static function isActive(): bool
  {
    return session_status() === PHP_SESSION_ACTIVE ? true : false;
  }
  
  /**
   * Start the session
   * 
   * @return void
   * @access public
   */
  public static function start(): void
  {
    if (!self::isStarted()) {
      session_name(SESSION_NAME);
    }
    if (!self::isActive()) {
      session_start();
    }
  }

  /**
   * Start the session with a new context
   * 
   * @return void
   * @access public
   */
  public static function startWithNewContext(): void
  {
    if (!self::isStarted()) {
      session_name(SESSION_NAME);
    }
    if (!self::isActive()) {
      session_start();
    }
    session_regenerate_id(true);    
  }
  
  /**
   * Start the session in editing mode
   * 
   * @return void
   * @access public
   */
  public static function startEditing(): void
  {
    if (!self::isActive()) {
      session_start();
    }
  }

  /**
   * Retrieve the value of the given session variable
   * 
   * @param string  $key the key of session variable to retrieve
   * @param mixed  $default a default value
   * @return mixed  the value
   * @access public
   */
  public static function get(string $key, $default=false) 
  {
    if (self::exists($key)) {
      return $_SESSION[$key];
    } else {
      return $default;
    }
  }
  
  /**
   * Set the value of the given session variable
   * 
   * @param string  $key the key of the session variable
   * @param mixed  $value the new value to assign
   * @return void
   * @access public
   */
  public static function set(string $key, $value): void
  {
    $_SESSION[$key] = $value;
  }

  /**
   * Unset the given session variable
   * 
   * @param string  $key the key of the session variable
   * @return void
   * @access public
   */
  public static function unset1(string $key): void 
  {
    if (self::exists($key)) {
      unset($_SESSION[$key]);
    }
  }

  /**
   * Release the write handle of the session
   * 
   * @return void
   * @access public
   */
  public static function closeEditing(): void
  {
    self::close();
  }

  /**
   * Close the session
   * 
   * @return void
   * @access public
   */
  public static function close(): void
  {
    if (self::isActive()) {
      session_write_close();
    }
  }
  
  /**
   * Destroy the session
   * 
   * @return void
   * @access public
   */
  public static function destory(): void
  {
    self::start();

    session_unset();
    session_destroy();
  }
}
