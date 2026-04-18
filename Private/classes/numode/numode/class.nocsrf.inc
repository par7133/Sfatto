<?php
/**
* NoCSRF, an anti CSRF token generation/checking class.
*
* Copyright (c) 2011 Thibaut Despoulain <http://bkcore.com/blog/code/nocsrf-php-class.html>
* Copyright (c) 2024 Daniele Bonini
* Licensed under the MIT license <http://www.opensource.org/licenses/mit-license.php>
*
* @author Thibaut Despoulain <http://bkcore.com>
* @version 1.5
* @link https://github.com/BKcore/NoCSRF github
*/

namespace numode\numode;


class NoCSRFException extends \Exception { }

final class NoCSRF
{    
    private static $doOriginCheck = false;

    /**
     * Default constructor
     * 
     * @return void
     */
    private function __construct()
    {
    }

    /**
     * Check CSRF tokens match between session and $origin. 
     * Make sure you generated a token in the form before checking it.
     *
     * @param String $key The session and $origin key where to find the token.
     * @param Mixed $origin The object/associative array to retreive the token data from (usually $_POST).
     * @param Boolean $throwException (Facultative) TRUE to throw exception on check fail, FALSE or default to return false.
     * @param Integer $timespan (Facultative) Makes the token expire after $timespan seconds. (null = never)
     * @param Boolean $multiple (Facultative) Makes the token reusable and not one-time. (Useful for ajax-heavy requests).
     * @param String $errmsg Error message o ""
     * 
     * @return Boolean Returns FALSE if a CSRF attack is detected, TRUE otherwise.
     */
    public static function check(string $key, $origin, bool $throwException=false, int $timespan=null, bool $multiple=false, string &$errmsg="" ): bool
    {
        if (!(bool)Session::exists($key)) {
            if($throwException) {
              //throw new NoCSRFException( 'Missing CSRF session token.' );
              echo( 'Missing CSRF session token.' ); 
            }
            return false;
        }

        if ( !isset( $origin[ $key ] ) ) {
            if($throwException) {
              //throw NoCSRFException( 'Missing CSRF form token.' );
              echo( 'Missing CSRF form token.' );
            }
            return false;
        }

        // Get valid token from session
        $hash = (string)Session::get($key);
		
        // Free up session token for one-time CSRF token usage.
        if(!$multiple) {
          Session::startEditing();
          Session::set($key, null);
          Session::closeEditing();
        }
        
        // Origin checks
        if( self::$doOriginCheck && sha1( $_SERVER['REMOTE_ADDR'] . $_SERVER['HTTP_USER_AGENT'] ) != substr( base64_decode( $hash ), 10, 40 ) )
        {
            if($throwException) {
              //throw new NoCSRFException( 'Form origin does not match token origin.' );
              echo( 'Form origin does not match token origin.' );
            }
            return false;
        }
        
        // Check if session token matches form token
        //var_dump($origin[ $key ]);
        //var_dump($hash);
        //exit;
        if ( $origin[ $key ] != $hash ) {
            if($throwException) {
              //throw new NoCSRFException( 'Invalid CSRF token.' );
              echo( 'Invalid CSRF token.' ); 
            }
            return false;
        }

        // Check for token expiration
        if ( $timespan != null && is_int( $timespan ) && intval( substr( base64_decode( $hash ), 0, 10 ) ) + $timespan < time() ) {
            if($throwException) {
              //throw new NoCSRFException( 'CSRF token expired.' );
              echo( 'CSRF token expired.' );
            }
            return false;
        }

        return true;
    }

    /**
     * Adds extra useragent and remote_addr checks to CSRF protections.
     */
    public static function enableOriginCheck(): void
    {
        self::$doOriginCheck = true;
    }

    /**
     * CSRF token generation method. After generating the token, put it inside a hidden form field named $key.
     *
     * @param String $key The session key where the token will be stored. (Will also be the name of the hidden field name)
     * @return String The generated, base64 encoded token.
     */
    public static function generate(string $key ): string
    {
        $extra = self::$doOriginCheck ? sha1( $_SERVER['REMOTE_ADDR'] . $_SERVER['HTTP_USER_AGENT'] ) : '';
        // token generation (basically base64_encode any random complex string, time() is used for token expiration) 
        $token = base64_encode( time() . $extra . self::randomString( 32 ) );
        // store the one-time token in session
        Session::startEditing();
        Session::set($key, $token);
        Session::closeEditing();
        
        return $token;
    }

    /**
     * Generates a random string of given $length.
     *
     * @param Integer $length The string length.
     * @return String The randomly generated string.
     */
    private static function randomString(int $length): string
    {
        $seed = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijqlmnopqrtsuvwxyz0123456789';
        $max = strlen( $seed ) - 1;

        $string = '';
        for ( $i = 0; $i < $length; ++$i )
//            $string .= $seed{intval( mt_rand( 0.0, $max ) )}; // breaks PHP8
              $string .= $seed[intval( mt_rand( 0.0, $max ) )];

        return $string;
    }

}
?>
