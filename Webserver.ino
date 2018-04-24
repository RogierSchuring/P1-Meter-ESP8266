/********************************************************************************************\
 * 
 * Webserver related functions
 * 
\********************************************************************************************/


/********************************************************************************************\
 * Web Interface init
\********************************************************************************************/
void WebServerInit()
{
  // Prepare webserver pages
  WebServer.on("/", handle_root);
  WebServer.on("/log", handle_log);
  WebServer.onNotFound(handle_NotFound);
  WebServer.begin();
}

/********************************************************************************************\
 * Web Interface root page
\********************************************************************************************/
void handle_root()
{
  int freeMem = ESP.getFreeHeap();
  IPAddress ip = WiFi.localIP();
  IPAddress gw = WiFi.gatewayIP();

  String reply = "";
  addHeader(true, reply);
  reply += F("<form>");
  reply += F("<table><TH>System Info<TH>");

  char str[20];
  sprintf_P(str, PSTR("%u.%u.%u.%u"), ip[0], ip[1], ip[2], ip[3]);
  reply += F("<TR><TD>IP:<TD>");
  reply += str;

  sprintf_P(str, PSTR("%u.%u.%u.%u"), gw[0], gw[1], gw[2], gw[3]);
  reply += F("<TR><TD>GW:<TD>");
  reply += str;

  reply += F("<TR><TD>STA MAC:<TD>");
  uint8_t mac[] = {0, 0, 0, 0, 0, 0};
  uint8_t* macread = WiFi.macAddress(mac);
  char macaddress[20];
  sprintf_P(macaddress, PSTR("%02x:%02x:%02x:%02x:%02x:%02x"), macread[0], macread[1], macread[2], macread[3], macread[4], macread[5]);
  reply += macaddress;

  reply += F("<TR><TD>ESP Chip ID:<TD>");
  reply += ESP.getChipId();

  reply += F("<TR><TD>Flash Chip ID:<TD>");
  reply += ESP.getFlashChipId();

  reply += F("<TR><TD>Flash Size:<TD>");
  reply += ESP.getFlashChipRealSize(); //ESP.getFlashChipSize();

  reply += F("</table></form>");
  addFooter(reply);
  WebServer.send(200, "text/html", reply);
}

/********************************************************************************************\
 * Web Interface log page
\********************************************************************************************/
void handle_log()
{
  char *TempString = (char*)malloc(80);
  
  String reply = "";
  addHeader(true, reply);
  reply += F("<script language='JavaScript'>function RefreshMe(){window.location = window.location}setTimeout('RefreshMe()', 10000);</script>");
  reply += F("<table><TH>Log<TR><TD>");
  
  if (logcount != -1)
  {
    byte counter = logcount;
    do
    {
      counter++;
      if (counter > MAXLOGLINES-1)
        counter = 0;
      if (Logging[counter].timeStamp > 0)
      {
        reply += Logging[counter].timeStamp;
        reply += " : ";
        reply += Logging[counter].Message;
        reply += F("<BR>");
      }
    }  while (counter != logcount);
  }
  
  reply += F("</table>");
  addFooter(reply);
  WebServer.send(200, "text/html", reply);
  free(TempString);
}

/********************************************************************************************\
 * Web Interface handle unknown requests
\********************************************************************************************/
void handle_NotFound() {
  
}

/********************************************************************************************\
 * Web Interface header (top menu)
\********************************************************************************************/
void addHeader(boolean showMenu, String& str)
{
  boolean cssfile = false;

  str += F("<script language=\"javascript\"><!--\n");
  str += F("function dept_onchange(frmselect) {frmselect.submit();}\n");
  str += F("//--></script>");
  str += F("<head><title>");
  str += hostName;
  str += F("</title>");
  str += F("<style>");
  str += F("* {font-family:sans-serif; font-size:12pt;}");
  str += F("h1 {font-size:16pt; color:black;}");
  str += F("h6 {font-size:10pt; color:black;}");
  str += F(".button-menu {background-color:#ffffff; color:blue; margin: 10px; text-decoration:none}");
  str += F(".button-link {padding:5px 15px; background-color:#0077dd; color:#fff; border:solid 1px #fff; text-decoration:none}");
  str += F(".button-menu:hover {background:#ddddff;}");
  str += F(".button-link:hover {background:#369;}");
  str += F("th {padding:10px; background-color:black; color:#ffffff;}");
  str += F("td {padding:7px;}");
  str += F("table {color:black;}");
  str += F(".div_l {float: left;}");
  str += F(".div_r {float: right; margin: 2px; padding: 1px 10px; border-radius: 7px; background-color:#080; color:white;}");
  str += F(".div_br {clear: both;}");
  str += F("</style>");
  str += F("</head>");
  str += F("<h1>Welcome to device: ");
  str += hostName;
  str += F("</h1>");

  if (showMenu)
  {
    str += F("<BR><a class=\"button-menu\" href=\".\">Main</a>");
    str += F("<a class=\"button-menu\" href=\"log\">Log</a><BR><BR>");
  }
}

/********************************************************************************************\
 * Web Interface footer
\********************************************************************************************/
void addFooter(String& str)
{
  str += F("<h6>Powered by ESP</h6></body>");
}



