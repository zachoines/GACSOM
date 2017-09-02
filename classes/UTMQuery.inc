<?php

class UTMQuery {

    var $query;
    var $key;

    function __construct($key) {
        $this->key = $key;
    }

    function get_most_recent_utm_history() {
        $this->query = db_query(
            "SELECT source, medium, campaign, time, client_id FROM `gacsom` 
            WHERE client_id = $this->key 
            AND campaign IS NOT NULL 
            AND TRIM(campaign) <> '' 
            ORDER BY time ASC
            LIMIT 1"
        );
       
        return $this->query;
    }
 
} 

?>