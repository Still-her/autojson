#include <iostream>
#include <stdio.h>
#include <fstream>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"
#include "smsf_SmsRecordData_struct.h"
using namespace smsf_SmsRecordData;
int json2c(string str, stSmsRecordData &root)
{
rapidjson::Document obj_0;
if (obj_0.Parse(str.c_str()).HasParseError())
{
return 1;
}
if(obj_0.HasMember("smsRecordId") && obj_0["smsRecordId"].IsString())
{
root.smsRecordId = obj_0["smsRecordId"].GetString();
}
if(obj_0.HasMember("smsPayload") && obj_0["smsPayload"].IsObject())
{
const rapidjson::Value& obj_1 = obj_0["smsPayload"];
if(obj_1.HasMember("contentId") && obj_1["contentId"].IsString())
{
root.smsPayload.contentId = obj_1["contentId"].GetString();
}
}
if(obj_0.HasMember("accessType") && obj_0["accessType"].IsString())
{
root.accessType = obj_0["accessType"].GetString();
}
if(obj_0.HasMember("gpsi") && obj_0["gpsi"].IsString())
{
root.gpsi = obj_0["gpsi"].GetString();
}
if(obj_0.HasMember("pei") && obj_0["pei"].IsString())
{
root.pei = obj_0["pei"].GetString();
}
if(obj_0.HasMember("ueLocation") && obj_0["ueLocation"].IsObject())
{
const rapidjson::Value& obj_1 = obj_0["ueLocation"];
if(obj_1.HasMember("eutraLocation") && obj_1["eutraLocation"].IsObject())
{
const rapidjson::Value& obj_2 = obj_1["eutraLocation"];
if(obj_2.HasMember("tai") && obj_2["tai"].IsObject())
{
const rapidjson::Value& obj_3 = obj_2["tai"];
if(obj_3.HasMember("plmnId") && obj_3["plmnId"].IsObject())
{
const rapidjson::Value& obj_4 = obj_3["plmnId"];
if(obj_4.HasMember("mcc") && obj_4["mcc"].IsString())
{
root.ueLocation.eutraLocation.tai.plmnId.mcc = obj_4["mcc"].GetString();
}
if(obj_4.HasMember("mnc") && obj_4["mnc"].IsString())
{
root.ueLocation.eutraLocation.tai.plmnId.mnc = obj_4["mnc"].GetString();
}
}
if(obj_3.HasMember("tac") && obj_3["tac"].IsString())
{
root.ueLocation.eutraLocation.tai.tac = obj_3["tac"].GetString();
}
if(obj_3.HasMember("nid") && obj_3["nid"].IsString())
{
root.ueLocation.eutraLocation.tai.nid = obj_3["nid"].GetString();
}
}
if(obj_2.HasMember("ecgi") && obj_2["ecgi"].IsObject())
{
const rapidjson::Value& obj_3 = obj_2["ecgi"];
if(obj_3.HasMember("plmnId") && obj_3["plmnId"].IsObject())
{
const rapidjson::Value& obj_4 = obj_3["plmnId"];
if(obj_4.HasMember("mcc") && obj_4["mcc"].IsString())
{
root.ueLocation.eutraLocation.ecgi.plmnId.mcc = obj_4["mcc"].GetString();
}
if(obj_4.HasMember("mnc") && obj_4["mnc"].IsString())
{
root.ueLocation.eutraLocation.ecgi.plmnId.mnc = obj_4["mnc"].GetString();
}
}
if(obj_3.HasMember("eutraCellId") && obj_3["eutraCellId"].IsString())
{
root.ueLocation.eutraLocation.ecgi.eutraCellId = obj_3["eutraCellId"].GetString();
}
if(obj_3.HasMember("nid") && obj_3["nid"].IsString())
{
root.ueLocation.eutraLocation.ecgi.nid = obj_3["nid"].GetString();
}
}
if(obj_2.HasMember("ignoreEcgi") && obj_2["ignoreEcgi"].IsBool())
{
root.ueLocation.eutraLocation.ignoreEcgi = obj_2["ignoreEcgi"].GetBool();
}
if(obj_2.HasMember("ageOfLocationInformation") && obj_2["ageOfLocationInformation"].IsInt())
{
root.ueLocation.eutraLocation.ageOfLocationInformation = obj_2["ageOfLocationInformation"].GetInt();
}
if(obj_2.HasMember("ueLocationTimestamp") && obj_2["ueLocationTimestamp"].IsString())
{
root.ueLocation.eutraLocation.ueLocationTimestamp = obj_2["ueLocationTimestamp"].GetString();
}
if(obj_2.HasMember("geographicalInformation") && obj_2["geographicalInformation"].IsString())
{
root.ueLocation.eutraLocation.geographicalInformation = obj_2["geographicalInformation"].GetString();
}
if(obj_2.HasMember("geodeticInformation") && obj_2["geodeticInformation"].IsString())
{
root.ueLocation.eutraLocation.geodeticInformation = obj_2["geodeticInformation"].GetString();
}
if(obj_2.HasMember("globalNgenbId") && obj_2["globalNgenbId"].IsObject())
{
const rapidjson::Value& obj_3 = obj_2["globalNgenbId"];
if(obj_3.HasMember("plmnId") && obj_3["plmnId"].IsObject())
{
const rapidjson::Value& obj_4 = obj_3["plmnId"];
if(obj_4.HasMember("mcc") && obj_4["mcc"].IsString())
{
root.ueLocation.eutraLocation.globalNgenbId.plmnId.mcc = obj_4["mcc"].GetString();
}
if(obj_4.HasMember("mnc") && obj_4["mnc"].IsString())
{
root.ueLocation.eutraLocation.globalNgenbId.plmnId.mnc = obj_4["mnc"].GetString();
}
}
if(obj_3.HasMember("n3IwfId") && obj_3["n3IwfId"].IsString())
{
root.ueLocation.eutraLocation.globalNgenbId.n3IwfId = obj_3["n3IwfId"].GetString();
}
if(obj_3.HasMember("gNbId") && obj_3["gNbId"].IsObject())
{
const rapidjson::Value& obj_4 = obj_3["gNbId"];
if(obj_4.HasMember("bitLength") && obj_4["bitLength"].IsInt())
{
root.ueLocation.eutraLocation.globalNgenbId.gNbId.bitLength = obj_4["bitLength"].GetInt();
}
if(obj_4.HasMember("gNBValue") && obj_4["gNBValue"].IsString())
{
root.ueLocation.eutraLocation.globalNgenbId.gNbId.gNBValue = obj_4["gNBValue"].GetString();
}
}
if(obj_3.HasMember("ngeNbId") && obj_3["ngeNbId"].IsString())
{
root.ueLocation.eutraLocation.globalNgenbId.ngeNbId = obj_3["ngeNbId"].GetString();
}
if(obj_3.HasMember("wagfId") && obj_3["wagfId"].IsString())
{
root.ueLocation.eutraLocation.globalNgenbId.wagfId = obj_3["wagfId"].GetString();
}
if(obj_3.HasMember("tngfId") && obj_3["tngfId"].IsString())
{
root.ueLocation.eutraLocation.globalNgenbId.tngfId = obj_3["tngfId"].GetString();
}
if(obj_3.HasMember("nid") && obj_3["nid"].IsString())
{
root.ueLocation.eutraLocation.globalNgenbId.nid = obj_3["nid"].GetString();
}
if(obj_3.HasMember("eNbId") && obj_3["eNbId"].IsString())
{
root.ueLocation.eutraLocation.globalNgenbId.eNbId = obj_3["eNbId"].GetString();
}
}
if(obj_2.HasMember("globalENbId") && obj_2["globalENbId"].IsObject())
{
const rapidjson::Value& obj_3 = obj_2["globalENbId"];
if(obj_3.HasMember("plmnId") && obj_3["plmnId"].IsObject())
{
const rapidjson::Value& obj_4 = obj_3["plmnId"];
if(obj_4.HasMember("mcc") && obj_4["mcc"].IsString())
{
root.ueLocation.eutraLocation.globalENbId.plmnId.mcc = obj_4["mcc"].GetString();
}
if(obj_4.HasMember("mnc") && obj_4["mnc"].IsString())
{
root.ueLocation.eutraLocation.globalENbId.plmnId.mnc = obj_4["mnc"].GetString();
}
}
if(obj_3.HasMember("n3IwfId") && obj_3["n3IwfId"].IsString())
{
root.ueLocation.eutraLocation.globalENbId.n3IwfId = obj_3["n3IwfId"].GetString();
}
if(obj_3.HasMember("gNbId") && obj_3["gNbId"].IsObject())
{
const rapidjson::Value& obj_4 = obj_3["gNbId"];
if(obj_4.HasMember("bitLength") && obj_4["bitLength"].IsInt())
{
root.ueLocation.eutraLocation.globalENbId.gNbId.bitLength = obj_4["bitLength"].GetInt();
}
if(obj_4.HasMember("gNBValue") && obj_4["gNBValue"].IsString())
{
root.ueLocation.eutraLocation.globalENbId.gNbId.gNBValue = obj_4["gNBValue"].GetString();
}
}
if(obj_3.HasMember("ngeNbId") && obj_3["ngeNbId"].IsString())
{
root.ueLocation.eutraLocation.globalENbId.ngeNbId = obj_3["ngeNbId"].GetString();
}
if(obj_3.HasMember("wagfId") && obj_3["wagfId"].IsString())
{
root.ueLocation.eutraLocation.globalENbId.wagfId = obj_3["wagfId"].GetString();
}
if(obj_3.HasMember("tngfId") && obj_3["tngfId"].IsString())
{
root.ueLocation.eutraLocation.globalENbId.tngfId = obj_3["tngfId"].GetString();
}
if(obj_3.HasMember("nid") && obj_3["nid"].IsString())
{
root.ueLocation.eutraLocation.globalENbId.nid = obj_3["nid"].GetString();
}
if(obj_3.HasMember("eNbId") && obj_3["eNbId"].IsString())
{
root.ueLocation.eutraLocation.globalENbId.eNbId = obj_3["eNbId"].GetString();
}
}
}
if(obj_1.HasMember("nrLocation") && obj_1["nrLocation"].IsObject())
{
const rapidjson::Value& obj_2 = obj_1["nrLocation"];
if(obj_2.HasMember("tai") && obj_2["tai"].IsObject())
{
const rapidjson::Value& obj_3 = obj_2["tai"];
if(obj_3.HasMember("plmnId") && obj_3["plmnId"].IsObject())
{
const rapidjson::Value& obj_4 = obj_3["plmnId"];
if(obj_4.HasMember("mcc") && obj_4["mcc"].IsString())
{
root.ueLocation.nrLocation.tai.plmnId.mcc = obj_4["mcc"].GetString();
}
if(obj_4.HasMember("mnc") && obj_4["mnc"].IsString())
{
root.ueLocation.nrLocation.tai.plmnId.mnc = obj_4["mnc"].GetString();
}
}
if(obj_3.HasMember("tac") && obj_3["tac"].IsString())
{
root.ueLocation.nrLocation.tai.tac = obj_3["tac"].GetString();
}
if(obj_3.HasMember("nid") && obj_3["nid"].IsString())
{
root.ueLocation.nrLocation.tai.nid = obj_3["nid"].GetString();
}
}
if(obj_2.HasMember("ncgi") && obj_2["ncgi"].IsObject())
{
const rapidjson::Value& obj_3 = obj_2["ncgi"];
if(obj_3.HasMember("plmnId") && obj_3["plmnId"].IsObject())
{
const rapidjson::Value& obj_4 = obj_3["plmnId"];
if(obj_4.HasMember("mcc") && obj_4["mcc"].IsString())
{
root.ueLocation.nrLocation.ncgi.plmnId.mcc = obj_4["mcc"].GetString();
}
if(obj_4.HasMember("mnc") && obj_4["mnc"].IsString())
{
root.ueLocation.nrLocation.ncgi.plmnId.mnc = obj_4["mnc"].GetString();
}
}
if(obj_3.HasMember("nrCellId") && obj_3["nrCellId"].IsString())
{
root.ueLocation.nrLocation.ncgi.nrCellId = obj_3["nrCellId"].GetString();
}
if(obj_3.HasMember("nid") && obj_3["nid"].IsString())
{
root.ueLocation.nrLocation.ncgi.nid = obj_3["nid"].GetString();
}
}
if(obj_2.HasMember("ageOfLocationInformation") && obj_2["ageOfLocationInformation"].IsInt())
{
root.ueLocation.nrLocation.ageOfLocationInformation = obj_2["ageOfLocationInformation"].GetInt();
}
if(obj_2.HasMember("ueLocationTimestamp") && obj_2["ueLocationTimestamp"].IsString())
{
root.ueLocation.nrLocation.ueLocationTimestamp = obj_2["ueLocationTimestamp"].GetString();
}
if(obj_2.HasMember("geographicalInformation") && obj_2["geographicalInformation"].IsString())
{
root.ueLocation.nrLocation.geographicalInformation = obj_2["geographicalInformation"].GetString();
}
if(obj_2.HasMember("geodeticInformation") && obj_2["geodeticInformation"].IsString())
{
root.ueLocation.nrLocation.geodeticInformation = obj_2["geodeticInformation"].GetString();
}
if(obj_2.HasMember("globalGnbId") && obj_2["globalGnbId"].IsObject())
{
const rapidjson::Value& obj_3 = obj_2["globalGnbId"];
if(obj_3.HasMember("plmnId") && obj_3["plmnId"].IsObject())
{
const rapidjson::Value& obj_4 = obj_3["plmnId"];
if(obj_4.HasMember("mcc") && obj_4["mcc"].IsString())
{
root.ueLocation.nrLocation.globalGnbId.plmnId.mcc = obj_4["mcc"].GetString();
}
if(obj_4.HasMember("mnc") && obj_4["mnc"].IsString())
{
root.ueLocation.nrLocation.globalGnbId.plmnId.mnc = obj_4["mnc"].GetString();
}
}
if(obj_3.HasMember("n3IwfId") && obj_3["n3IwfId"].IsString())
{
root.ueLocation.nrLocation.globalGnbId.n3IwfId = obj_3["n3IwfId"].GetString();
}
if(obj_3.HasMember("gNbId") && obj_3["gNbId"].IsObject())
{
const rapidjson::Value& obj_4 = obj_3["gNbId"];
if(obj_4.HasMember("bitLength") && obj_4["bitLength"].IsInt())
{
root.ueLocation.nrLocation.globalGnbId.gNbId.bitLength = obj_4["bitLength"].GetInt();
}
if(obj_4.HasMember("gNBValue") && obj_4["gNBValue"].IsString())
{
root.ueLocation.nrLocation.globalGnbId.gNbId.gNBValue = obj_4["gNBValue"].GetString();
}
}
if(obj_3.HasMember("ngeNbId") && obj_3["ngeNbId"].IsString())
{
root.ueLocation.nrLocation.globalGnbId.ngeNbId = obj_3["ngeNbId"].GetString();
}
if(obj_3.HasMember("wagfId") && obj_3["wagfId"].IsString())
{
root.ueLocation.nrLocation.globalGnbId.wagfId = obj_3["wagfId"].GetString();
}
if(obj_3.HasMember("tngfId") && obj_3["tngfId"].IsString())
{
root.ueLocation.nrLocation.globalGnbId.tngfId = obj_3["tngfId"].GetString();
}
if(obj_3.HasMember("nid") && obj_3["nid"].IsString())
{
root.ueLocation.nrLocation.globalGnbId.nid = obj_3["nid"].GetString();
}
if(obj_3.HasMember("eNbId") && obj_3["eNbId"].IsString())
{
root.ueLocation.nrLocation.globalGnbId.eNbId = obj_3["eNbId"].GetString();
}
}
}
if(obj_1.HasMember("n3gaLocation") && obj_1["n3gaLocation"].IsObject())
{
const rapidjson::Value& obj_2 = obj_1["n3gaLocation"];
if(obj_2.HasMember("n3gppTai") && obj_2["n3gppTai"].IsObject())
{
const rapidjson::Value& obj_3 = obj_2["n3gppTai"];
if(obj_3.HasMember("plmnId") && obj_3["plmnId"].IsObject())
{
const rapidjson::Value& obj_4 = obj_3["plmnId"];
if(obj_4.HasMember("mcc") && obj_4["mcc"].IsString())
{
root.ueLocation.n3gaLocation.n3gppTai.plmnId.mcc = obj_4["mcc"].GetString();
}
if(obj_4.HasMember("mnc") && obj_4["mnc"].IsString())
{
root.ueLocation.n3gaLocation.n3gppTai.plmnId.mnc = obj_4["mnc"].GetString();
}
}
if(obj_3.HasMember("tac") && obj_3["tac"].IsString())
{
root.ueLocation.n3gaLocation.n3gppTai.tac = obj_3["tac"].GetString();
}
if(obj_3.HasMember("nid") && obj_3["nid"].IsString())
{
root.ueLocation.n3gaLocation.n3gppTai.nid = obj_3["nid"].GetString();
}
}
if(obj_2.HasMember("n3IwfId") && obj_2["n3IwfId"].IsString())
{
root.ueLocation.n3gaLocation.n3IwfId = obj_2["n3IwfId"].GetString();
}
if(obj_2.HasMember("ueIpv4Addr") && obj_2["ueIpv4Addr"].IsString())
{
root.ueLocation.n3gaLocation.ueIpv4Addr = obj_2["ueIpv4Addr"].GetString();
}
if(obj_2.HasMember("ueIpv6Addr") && obj_2["ueIpv6Addr"].IsString())
{
root.ueLocation.n3gaLocation.ueIpv6Addr = obj_2["ueIpv6Addr"].GetString();
}
if(obj_2.HasMember("portNumber") && obj_2["portNumber"].IsInt())
{
root.ueLocation.n3gaLocation.portNumber = obj_2["portNumber"].GetInt();
}
if(obj_2.HasMember("tnapId") && obj_2["tnapId"].IsObject())
{
const rapidjson::Value& obj_3 = obj_2["tnapId"];
if(obj_3.HasMember("ssId") && obj_3["ssId"].IsString())
{
root.ueLocation.n3gaLocation.tnapId.ssId = obj_3["ssId"].GetString();
}
if(obj_3.HasMember("bssId") && obj_3["bssId"].IsString())
{
root.ueLocation.n3gaLocation.tnapId.bssId = obj_3["bssId"].GetString();
}
if(obj_3.HasMember("civicAddress") && obj_3["civicAddress"].IsString())
{
root.ueLocation.n3gaLocation.tnapId.civicAddress = obj_3["civicAddress"].GetString();
}
}
if(obj_2.HasMember("twapId") && obj_2["twapId"].IsObject())
{
const rapidjson::Value& obj_3 = obj_2["twapId"];
if(obj_3.HasMember("ssId") && obj_3["ssId"].IsString())
{
root.ueLocation.n3gaLocation.twapId.ssId = obj_3["ssId"].GetString();
}
if(obj_3.HasMember("bssId") && obj_3["bssId"].IsString())
{
root.ueLocation.n3gaLocation.twapId.bssId = obj_3["bssId"].GetString();
}
if(obj_3.HasMember("civicAddress") && obj_3["civicAddress"].IsString())
{
root.ueLocation.n3gaLocation.twapId.civicAddress = obj_3["civicAddress"].GetString();
}
}
if(obj_2.HasMember("hfcNodeId") && obj_2["hfcNodeId"].IsObject())
{
const rapidjson::Value& obj_3 = obj_2["hfcNodeId"];
if(obj_3.HasMember("hfcNId") && obj_3["hfcNId"].IsString())
{
root.ueLocation.n3gaLocation.hfcNodeId.hfcNId = obj_3["hfcNId"].GetString();
}
}
if(obj_2.HasMember("gli") && obj_2["gli"].IsString())
{
root.ueLocation.n3gaLocation.gli = obj_2["gli"].GetString();
}
}
}
if(obj_0.HasMember("ueTimeZone") && obj_0["ueTimeZone"].IsString())
{
root.ueTimeZone = obj_0["ueTimeZone"].GetString();
}
return 0;
}
