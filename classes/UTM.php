<?php 


class UTM
{

  var $campaign_source;    	
  var $campaign_name;  		
  var $campaign_medium;
  var $campaign_content;
  var $campaign_term;   

  var $first_visit;
  var $previous_visit;
  var $current_visit_started;
  var $times_visited;
  
  //constructor
  function __construct($cookie) {
     if (isset($cookie["__utmz"])) {
       $this->utmz = $cookie["__utmz"];
     }
     if (isset($cookie["__utma"])) {
       $this->utma = $cookie["__utma"];
     }
       $this->ParseCookies();
  }

  //returns tokenized google tracking information
  function getAllTokens() {
      return array (
          'Campaign Source' => $this->campaign_source,
          'Campaign Name' => $this->campaign_name,
          'Campaign Medium' => $this->campaign_medium,
          'Campaign Content' => $this->campaign_content,
          'Campaign Term' => $this->campaign_term,
          'Date of first visit' => $this->first_visit,
          'Date of previous visit' => $this->previous_visit,
          'Current visit started at' => $this->current_visit_started,
          'Times visited' => $this->times_visited 
      );
  }

  function ParseCookies(){
    // Parse __utmz cookie
    if (isset($this->utmz)) {
        preg_match("((\d+)\.(\d+)\.(\d+)\.(\d+)\.(.*))", $this->utmz, $matches);
        $domain_hash = $matches[1];
        $timestamp = $matches[2];
        $session_number = $matches[3];
        $campaign_numer = $matches[4];
        $campaign_data = $matches[5];

        // Parse the campaign data
        $campaign_data = parse_str(strtr($campaign_data, "|", "&"));
    }

    $this->campaign_source = isset($utmcsr) ? $utmcsr : '';
    $this->campaign_name = isset($utmccn) ? $utmccn : '';
    $this->campaign_medium = isset($utmcmd) ? $utmcmd : '';
    $this->campaign_term = isset($utmctr) ? $utmctr : '';
    $this->campaign_content = isset($utmcct) ? $utmcct : '';

    // You should tag you campaigns manually to have a full view
    // of your adwords campaigns data. 
    // The same happens with Urchin, tag manually to have your campaign data parsed properly.
    
    if(isset($utmgclid)) {
        $this->campaign_source = "google";
        $this->campaign_name = "";
        $this->campaign_medium = "cpc";
        $this->campaign_content = "";
        $this->campaign_term = $utmctr;
    }

    // Parse the __utma Cookie
    if (isset($this->utma)) {
        list($domain_hash,$random_id,$time_initial_visit,$time_beginning_previous_visit,$time_beginning_current_visit,$session_counter) = preg_split('[\.]', $this->utma);
    }

    $this->first_visit = isset($time_initial_visit) ? date("m/d/Y g:i:s A",$time_initial_visit) : '';
    $this->previous_visit = isset($time_beginning_previous_visit) ? date("m/d/Y g:i:s A",$time_beginning_previous_visit) : '';
    $this->current_visit_started = isset($time_beginning_current_visit) ? date("m/d/Y g:i:s A",$time_beginning_current_visit) : '';
    $this->times_visited = isset($session_counter) ? $session_counter : '';

    // End ParseCookies
    }  

// End GA_Parse
}

?>