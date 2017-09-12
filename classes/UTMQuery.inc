<?php

class UTMQuery {

    var $query;
    var $key;
    var $format;

    public function __construct($key, $JSON_format) {
        $this->key = $key;
        $this->format = $JSON_format;
    } 

    
    //fetches the first UTM history and returns it as a JSON object
    private function get_earliest_utm_history() {
        $this->query = db_query(
            "SELECT source, medium, campaign, time, client_id FROM `gacsom` 
            WHERE client_id = $this->key 
            AND campaign IS NOT NULL 
            AND TRIM(campaign) <> '' 
            ORDER BY time ASC
            LIMIT 1"
        );
        
        $dbdata = array();
        $result = $this->query->fetchAll();

        //now lets format this as a JSON object
        foreach ($result  as $row) {
            $db_data[] = $row;
        }

        $JSON_data = json_encode($db_data); 

        return $JSON_data;
    }

    //fetches the most recent UTM history and returns it as a JSON object
    private function get_most_recent_utm_history() {
        $this->query = db_query(
            "SELECT source, medium, campaign, time, client_id FROM `gacsom` 
            WHERE client_id = $this->key 
            AND campaign IS NOT NULL 
            AND TRIM(campaign) <> '' 
            ORDER BY time DESC
            LIMIT 1"
        );
        
        $db_data = array();
        $result = $this->query->fetchAll();

        //now lets format this as a JSON object
        foreach ($result  as $row) {
            $db_data[] = $row;
        }

        $JSON_data = json_encode($db_data); 
        dpm($JSON_data);

        return $JSON_data;
    }
 
    //fetches all UTM history and returns it as a JSON object
    private function get_all_utm_history() {
        $this->query = db_query(
            "SELECT source, medium, campaign, time, client_id FROM `gacsom` 
            WHERE client_id = $this->key 
            AND campaign IS NOT NULL 
            AND TRIM(campaign) <> '' 
            ORDER BY time DESC"
        );
        
        $db_data = array();
        $result = $this->query->fetchAll();

        //now lets format this as a JSON object
        foreach ($result as $row) {
            $db_data[] = $row;
        }
        
        $JSON_data = json_encode($db_data); 
        
        return $JSON_data;
    }

    public function get_utm_history() {
        switch ($this->format[0]) {
            case 'A':
                return $this->get_all_utm_history();
                break;
            
            case 'F':
                return $this->get_earliest_utm_history();
                break;

            case 'L':
                return $this->get_most_recent_utm_history();
                break;

            default:
                return $this->get_most_recent_utm_history();
                break;
        }
    }
 
} 

?>