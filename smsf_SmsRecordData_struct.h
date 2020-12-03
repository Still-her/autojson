#ifndef smsf_SmsRecordData_DEFINE_H_
#define smsf_SmsRecordData_DEFINE_H_
#include <string>
#include <vector>
using namespace std;
namespace smsf_SmsRecordData{
struct stsmsPayload{
	string contentId;
};

struct stplmnId{
	string mcc;
	string mnc;
};

struct sttai{
	stplmnId plmnId;
	string tac;
	string nid;
};

struct stecgi{
	stplmnId plmnId;
	string eutraCellId;
	string nid;
};

struct stgNbId{
	int bitLength;
	string gNBValue;
};

struct stglobalNgenbId{
	stplmnId plmnId;
	string n3IwfId;
	stgNbId gNbId;
	string ngeNbId;
	string wagfId;
	string tngfId;
	string nid;
	string eNbId;
};

struct stglobalENbId{
	stplmnId plmnId;
	string n3IwfId;
	stgNbId gNbId;
	string ngeNbId;
	string wagfId;
	string tngfId;
	string nid;
	string eNbId;
};

struct steutraLocation{
	sttai tai;
	stecgi ecgi;
	bool ignoreEcgi;
	int ageOfLocationInformation;
	string ueLocationTimestamp;
	string geographicalInformation;
	string geodeticInformation;
	stglobalNgenbId globalNgenbId;
	stglobalENbId globalENbId;
};

struct stncgi{
	stplmnId plmnId;
	string nrCellId;
	string nid;
};

struct stglobalGnbId{
	stplmnId plmnId;
	string n3IwfId;
	stgNbId gNbId;
	string ngeNbId;
	string wagfId;
	string tngfId;
	string nid;
	string eNbId;
};

struct stnrLocation{
	sttai tai;
	stncgi ncgi;
	int ageOfLocationInformation;
	string ueLocationTimestamp;
	string geographicalInformation;
	string geodeticInformation;
	stglobalGnbId globalGnbId;
};

struct stn3gppTai{
	stplmnId plmnId;
	string tac;
	string nid;
};

struct sttnapId{
	string ssId;
	string bssId;
	string civicAddress;
};

struct sttwapId{
	string ssId;
	string bssId;
	string civicAddress;
};

struct sthfcNodeId{
	string hfcNId;
};

struct stn3gaLocation{
	stn3gppTai n3gppTai;
	string n3IwfId;
	string ueIpv4Addr;
	string ueIpv6Addr;
	int portNumber;
	sttnapId tnapId;
	sttwapId twapId;
	sthfcNodeId hfcNodeId;
	string gli;
};

struct stueLocation{
	steutraLocation eutraLocation;
	stnrLocation nrLocation;
	stn3gaLocation n3gaLocation;
};

struct stSmsRecordData{
	string smsRecordId;
	stsmsPayload smsPayload;
	string accessType;
	string gpsi;
	string pei;
	stueLocation ueLocation;
	string ueTimeZone;
};

}
#endif
