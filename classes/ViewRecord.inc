 <?php 

class ViewRecord {
    //class member variables
    var $source;
    var $medium;
    var $campaign;
    var $client_id;
    var $date; 
    var $url;
    
    //constructors
    function __construct($source, $medium, $campaign, $client_id, $date, $url) {
        $this->source = $source;
        $this->medium = $medium;
        $this->campaign = $campaign;
        $this->client_id = $client_id;
        $this->date = $date;
        $this->url = $url;
    }
}  

?>   