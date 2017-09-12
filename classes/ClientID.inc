<?php

class ClientID {

    var $client_id;
    var $ga_cookie;
 
    function __construct($cookie) {
        if (isset($cookie["_ga"])) {
            $this->ga_cookie = $cookie["_ga"];
        } else {
            $this->ga_cookie = "";
        }
    } 
     
    //Finds and returns the google analytics client id from the _ga cookie 
    function GetClientID() {
         if (!isset($this->ga_cookie)) {
            return null;
         } else {
            
            // Parse cookie _ga='<something>.<something>.<clientid>.<timestamp>';
            return explode(".", $this->ga_cookie)[2];
         }
     }
} 
 

?> 