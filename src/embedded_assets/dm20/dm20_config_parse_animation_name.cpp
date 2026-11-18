#include "embedded_assets/embedded_image.h"
#include "embedded_assets/dm20/dm20.hpp"
#include "dm20_config_parse_animation_name.h"
#include "utils/memory.h"
#include "utils/system_memory.h"

namespace bongocat::assets {
    inline static constexpr char ALT_DM20_AEGISDRAMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:aegisdramon";
    inline static constexpr const char* ALT_DM20_AEGISDRAMON_FQID = ALT_DM20_AEGISDRAMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_AEGISDRAMON_FQID_LEN = sizeof(ALT_DM20_AEGISDRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_AEGISDRAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Aegisdramon";
    inline static constexpr const char* ALT_DM20_AEGISDRAMON_FQNAME = ALT_DM20_AEGISDRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_AEGISDRAMON_FQNAME_LEN = sizeof(ALT_DM20_AEGISDRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_AGUMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:agumon";
    inline static constexpr const char* ALT_DM20_AGUMON_FQID = ALT_DM20_AGUMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_AGUMON_FQID_LEN = sizeof(ALT_DM20_AGUMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_AGUMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Agumon";
    inline static constexpr const char* ALT_DM20_AGUMON_FQNAME = ALT_DM20_AGUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_AGUMON_FQNAME_LEN = sizeof(ALT_DM20_AGUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_AIRDRAMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:airdramon";
    inline static constexpr const char* ALT_DM20_AIRDRAMON_FQID = ALT_DM20_AIRDRAMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_AIRDRAMON_FQID_LEN = sizeof(ALT_DM20_AIRDRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_AIRDRAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Airdramon";
    inline static constexpr const char* ALT_DM20_AIRDRAMON_FQNAME = ALT_DM20_AIRDRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_AIRDRAMON_FQNAME_LEN = sizeof(ALT_DM20_AIRDRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_ALPHAMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:alphamon";
    inline static constexpr const char* ALT_DM20_ALPHAMON_FQID = ALT_DM20_ALPHAMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_ALPHAMON_FQID_LEN = sizeof(ALT_DM20_ALPHAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_ALPHAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Alphamon";
    inline static constexpr const char* ALT_DM20_ALPHAMON_FQNAME = ALT_DM20_ALPHAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_ALPHAMON_FQNAME_LEN = sizeof(ALT_DM20_ALPHAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_ANDROMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:andromon";
    inline static constexpr const char* ALT_DM20_ANDROMON_FQID = ALT_DM20_ANDROMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_ANDROMON_FQID_LEN = sizeof(ALT_DM20_ANDROMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_ANDROMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Andromon";
    inline static constexpr const char* ALT_DM20_ANDROMON_FQNAME = ALT_DM20_ANDROMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_ANDROMON_FQNAME_LEN = sizeof(ALT_DM20_ANDROMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_ANGEMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:angemon";
    inline static constexpr const char* ALT_DM20_ANGEMON_FQID = ALT_DM20_ANGEMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_ANGEMON_FQID_LEN = sizeof(ALT_DM20_ANGEMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_ANGEMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Angemon";
    inline static constexpr const char* ALT_DM20_ANGEMON_FQNAME = ALT_DM20_ANGEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_ANGEMON_FQNAME_LEN = sizeof(ALT_DM20_ANGEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_APOLLOMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:apollomon";
    inline static constexpr const char* ALT_DM20_APOLLOMON_FQID = ALT_DM20_APOLLOMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_APOLLOMON_FQID_LEN = sizeof(ALT_DM20_APOLLOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_APOLLOMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Apollomon";
    inline static constexpr const char* ALT_DM20_APOLLOMON_FQNAME = ALT_DM20_APOLLOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_APOLLOMON_FQNAME_LEN = sizeof(ALT_DM20_APOLLOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_BABYDMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:babydmon";
    inline static constexpr const char* ALT_DM20_BABYDMON_FQID = ALT_DM20_BABYDMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_BABYDMON_FQID_LEN = sizeof(ALT_DM20_BABYDMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_BABYDMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Babydmon";
    inline static constexpr const char* ALT_DM20_BABYDMON_FQNAME = ALT_DM20_BABYDMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_BABYDMON_FQNAME_LEN = sizeof(ALT_DM20_BABYDMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_BAKEMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:bakemon";
    inline static constexpr const char* ALT_DM20_BAKEMON_FQID = ALT_DM20_BAKEMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_BAKEMON_FQID_LEN = sizeof(ALT_DM20_BAKEMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_BAKEMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Bakemon";
    inline static constexpr const char* ALT_DM20_BAKEMON_FQNAME = ALT_DM20_BAKEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_BAKEMON_FQNAME_LEN = sizeof(ALT_DM20_BAKEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_BANCHO_MAMEMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:bancho_mamemon";
    inline static constexpr const char* ALT_DM20_BANCHO_MAMEMON_FQID = ALT_DM20_BANCHO_MAMEMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_BANCHO_MAMEMON_FQID_LEN = sizeof(ALT_DM20_BANCHO_MAMEMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_BANCHO_MAMEMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Bancho Mamemon";
    inline static constexpr const char* ALT_DM20_BANCHO_MAMEMON_FQNAME = ALT_DM20_BANCHO_MAMEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_BANCHO_MAMEMON_FQNAME_LEN = sizeof(ALT_DM20_BANCHO_MAMEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_BAO_HACKMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:bao_hackmon";
    inline static constexpr const char* ALT_DM20_BAO_HACKMON_FQID = ALT_DM20_BAO_HACKMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_BAO_HACKMON_FQID_LEN = sizeof(ALT_DM20_BAO_HACKMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_BAO_HACKMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Bao Hackmon";
    inline static constexpr const char* ALT_DM20_BAO_HACKMON_FQNAME = ALT_DM20_BAO_HACKMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_BAO_HACKMON_FQNAME_LEN = sizeof(ALT_DM20_BAO_HACKMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_BETAMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:betamon";
    inline static constexpr const char* ALT_DM20_BETAMON_FQID = ALT_DM20_BETAMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_BETAMON_FQID_LEN = sizeof(ALT_DM20_BETAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_BETAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Betamon";
    inline static constexpr const char* ALT_DM20_BETAMON_FQNAME = ALT_DM20_BETAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_BETAMON_FQNAME_LEN = sizeof(ALT_DM20_BETAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_BIRDRAMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:birdramon";
    inline static constexpr const char* ALT_DM20_BIRDRAMON_FQID = ALT_DM20_BIRDRAMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_BIRDRAMON_FQID_LEN = sizeof(ALT_DM20_BIRDRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_BIRDRAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Birdramon";
    inline static constexpr const char* ALT_DM20_BIRDRAMON_FQNAME = ALT_DM20_BIRDRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_BIRDRAMON_FQNAME_LEN = sizeof(ALT_DM20_BIRDRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_BLITZ_GREYMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:blitz_greymon";
    inline static constexpr const char* ALT_DM20_BLITZ_GREYMON_FQID = ALT_DM20_BLITZ_GREYMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_BLITZ_GREYMON_FQID_LEN = sizeof(ALT_DM20_BLITZ_GREYMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_BLITZ_GREYMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Blitz Greymon";
    inline static constexpr const char* ALT_DM20_BLITZ_GREYMON_FQNAME = ALT_DM20_BLITZ_GREYMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_BLITZ_GREYMON_FQNAME_LEN = sizeof(ALT_DM20_BLITZ_GREYMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_BOTAMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:botamon";
    inline static constexpr const char* ALT_DM20_BOTAMON_FQID = ALT_DM20_BOTAMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_BOTAMON_FQID_LEN = sizeof(ALT_DM20_BOTAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_BOTAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Botamon";
    inline static constexpr const char* ALT_DM20_BOTAMON_FQNAME = ALT_DM20_BOTAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_BOTAMON_FQNAME_LEN = sizeof(ALT_DM20_BOTAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_BREAKDRAMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:breakdramon";
    inline static constexpr const char* ALT_DM20_BREAKDRAMON_FQID = ALT_DM20_BREAKDRAMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_BREAKDRAMON_FQID_LEN = sizeof(ALT_DM20_BREAKDRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_BREAKDRAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Breakdramon";
    inline static constexpr const char* ALT_DM20_BREAKDRAMON_FQNAME = ALT_DM20_BREAKDRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_BREAKDRAMON_FQNAME_LEN = sizeof(ALT_DM20_BREAKDRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_CENTALMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:centalmon";
    inline static constexpr const char* ALT_DM20_CENTALMON_FQID = ALT_DM20_CENTALMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_CENTALMON_FQID_LEN = sizeof(ALT_DM20_CENTALMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_CENTALMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Centalmon";
    inline static constexpr const char* ALT_DM20_CENTALMON_FQNAME = ALT_DM20_CENTALMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_CENTALMON_FQNAME_LEN = sizeof(ALT_DM20_CENTALMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_COCKATRIMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:cockatrimon";
    inline static constexpr const char* ALT_DM20_COCKATRIMON_FQID = ALT_DM20_COCKATRIMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_COCKATRIMON_FQID_LEN = sizeof(ALT_DM20_COCKATRIMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_COCKATRIMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Cockatrimon";
    inline static constexpr const char* ALT_DM20_COCKATRIMON_FQNAME = ALT_DM20_COCKATRIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_COCKATRIMON_FQNAME_LEN = sizeof(ALT_DM20_COCKATRIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_COELAMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:coelamon";
    inline static constexpr const char* ALT_DM20_COELAMON_FQID = ALT_DM20_COELAMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_COELAMON_FQID_LEN = sizeof(ALT_DM20_COELAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_COELAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Coelamon";
    inline static constexpr const char* ALT_DM20_COELAMON_FQNAME = ALT_DM20_COELAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_COELAMON_FQNAME_LEN = sizeof(ALT_DM20_COELAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_COREDRAMON_BLUE_FQID_ARR[] CONFIG_STRING_SECTION = "dm:coredramon_blue";
    inline static constexpr const char* ALT_DM20_COREDRAMON_BLUE_FQID = ALT_DM20_COREDRAMON_BLUE_FQID_ARR;
    inline static constexpr size_t ALT_DM20_COREDRAMON_BLUE_FQID_LEN = sizeof(ALT_DM20_COREDRAMON_BLUE_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_COREDRAMON_BLUE_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Coredramon (Blue)";
    inline static constexpr const char* ALT_DM20_COREDRAMON_BLUE_FQNAME = ALT_DM20_COREDRAMON_BLUE_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_COREDRAMON_BLUE_FQNAME_LEN = sizeof(ALT_DM20_COREDRAMON_BLUE_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_COREDRAMON_GREEN_FQID_ARR[] CONFIG_STRING_SECTION = "dm:coredramon_green";
    inline static constexpr const char* ALT_DM20_COREDRAMON_GREEN_FQID = ALT_DM20_COREDRAMON_GREEN_FQID_ARR;
    inline static constexpr size_t ALT_DM20_COREDRAMON_GREEN_FQID_LEN = sizeof(ALT_DM20_COREDRAMON_GREEN_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_COREDRAMON_GREEN_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Coredramon (Green)";
    inline static constexpr const char* ALT_DM20_COREDRAMON_GREEN_FQNAME = ALT_DM20_COREDRAMON_GREEN_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_COREDRAMON_GREEN_FQNAME_LEN = sizeof(ALT_DM20_COREDRAMON_GREEN_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_CORONAMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:coronamon";
    inline static constexpr const char* ALT_DM20_CORONAMON_FQID = ALT_DM20_CORONAMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_CORONAMON_FQID_LEN = sizeof(ALT_DM20_CORONAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_CORONAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Coronamon";
    inline static constexpr const char* ALT_DM20_CORONAMON_FQNAME = ALT_DM20_CORONAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_CORONAMON_FQNAME_LEN = sizeof(ALT_DM20_CORONAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_CRESCEMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:crescemon";
    inline static constexpr const char* ALT_DM20_CRESCEMON_FQID = ALT_DM20_CRESCEMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_CRESCEMON_FQID_LEN = sizeof(ALT_DM20_CRESCEMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_CRESCEMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Crescemon";
    inline static constexpr const char* ALT_DM20_CRESCEMON_FQNAME = ALT_DM20_CRESCEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_CRESCEMON_FQNAME_LEN = sizeof(ALT_DM20_CRESCEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_CRES_GARURUMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:cres_garurumon";
    inline static constexpr const char* ALT_DM20_CRES_GARURUMON_FQID = ALT_DM20_CRES_GARURUMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_CRES_GARURUMON_FQID_LEN = sizeof(ALT_DM20_CRES_GARURUMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_CRES_GARURUMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Cres Garurumon";
    inline static constexpr const char* ALT_DM20_CRES_GARURUMON_FQNAME = ALT_DM20_CRES_GARURUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_CRES_GARURUMON_FQNAME_LEN = sizeof(ALT_DM20_CRES_GARURUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_CYCLOMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:cyclomon";
    inline static constexpr const char* ALT_DM20_CYCLOMON_FQID = ALT_DM20_CYCLOMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_CYCLOMON_FQID_LEN = sizeof(ALT_DM20_CYCLOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_CYCLOMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Cyclomon";
    inline static constexpr const char* ALT_DM20_CYCLOMON_FQNAME = ALT_DM20_CYCLOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_CYCLOMON_FQNAME_LEN = sizeof(ALT_DM20_CYCLOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_DARK_TYRANOMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:dark_tyranomon";
    inline static constexpr const char* ALT_DM20_DARK_TYRANOMON_FQID = ALT_DM20_DARK_TYRANOMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_DARK_TYRANOMON_FQID_LEN = sizeof(ALT_DM20_DARK_TYRANOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_DARK_TYRANOMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Dark Tyranomon";
    inline static constexpr const char* ALT_DM20_DARK_TYRANOMON_FQNAME = ALT_DM20_DARK_TYRANOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_DARK_TYRANOMON_FQNAME_LEN = sizeof(ALT_DM20_DARK_TYRANOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_DELTAMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:deltamon";
    inline static constexpr const char* ALT_DM20_DELTAMON_FQID = ALT_DM20_DELTAMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_DELTAMON_FQID_LEN = sizeof(ALT_DM20_DELTAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_DELTAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Deltamon";
    inline static constexpr const char* ALT_DM20_DELTAMON_FQNAME = ALT_DM20_DELTAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_DELTAMON_FQNAME_LEN = sizeof(ALT_DM20_DELTAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_DEVIDRAMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:devidramon";
    inline static constexpr const char* ALT_DM20_DEVIDRAMON_FQID = ALT_DM20_DEVIDRAMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_DEVIDRAMON_FQID_LEN = sizeof(ALT_DM20_DEVIDRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_DEVIDRAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Devidramon";
    inline static constexpr const char* ALT_DM20_DEVIDRAMON_FQNAME = ALT_DM20_DEVIDRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_DEVIDRAMON_FQNAME_LEN = sizeof(ALT_DM20_DEVIDRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_DEVIMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:devimon";
    inline static constexpr const char* ALT_DM20_DEVIMON_FQID = ALT_DM20_DEVIMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_DEVIMON_FQID_LEN = sizeof(ALT_DM20_DEVIMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_DEVIMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Devimon";
    inline static constexpr const char* ALT_DM20_DEVIMON_FQNAME = ALT_DM20_DEVIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_DEVIMON_FQNAME_LEN = sizeof(ALT_DM20_DEVIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_DIANAMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:dianamon";
    inline static constexpr const char* ALT_DM20_DIANAMON_FQID = ALT_DM20_DIANAMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_DIANAMON_FQID_LEN = sizeof(ALT_DM20_DIANAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_DIANAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Dianamon";
    inline static constexpr const char* ALT_DM20_DIANAMON_FQNAME = ALT_DM20_DIANAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_DIANAMON_FQNAME_LEN = sizeof(ALT_DM20_DIANAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_DIGITAMAMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:digitamamon";
    inline static constexpr const char* ALT_DM20_DIGITAMAMON_FQID = ALT_DM20_DIGITAMAMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_DIGITAMAMON_FQID_LEN = sizeof(ALT_DM20_DIGITAMAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_DIGITAMAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Digitamamon";
    inline static constexpr const char* ALT_DM20_DIGITAMAMON_FQNAME = ALT_DM20_DIGITAMAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_DIGITAMAMON_FQNAME_LEN = sizeof(ALT_DM20_DIGITAMAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_DODOMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:dodomon";
    inline static constexpr const char* ALT_DM20_DODOMON_FQID = ALT_DM20_DODOMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_DODOMON_FQID_LEN = sizeof(ALT_DM20_DODOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_DODOMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Dodomon";
    inline static constexpr const char* ALT_DM20_DODOMON_FQNAME = ALT_DM20_DODOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_DODOMON_FQNAME_LEN = sizeof(ALT_DM20_DODOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_DORIMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:dorimon";
    inline static constexpr const char* ALT_DM20_DORIMON_FQID = ALT_DM20_DORIMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_DORIMON_FQID_LEN = sizeof(ALT_DM20_DORIMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_DORIMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Dorimon";
    inline static constexpr const char* ALT_DM20_DORIMON_FQNAME = ALT_DM20_DORIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_DORIMON_FQNAME_LEN = sizeof(ALT_DM20_DORIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_DORUGAMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:dorugamon";
    inline static constexpr const char* ALT_DM20_DORUGAMON_FQID = ALT_DM20_DORUGAMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_DORUGAMON_FQID_LEN = sizeof(ALT_DM20_DORUGAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_DORUGAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:DORUgamon";
    inline static constexpr const char* ALT_DM20_DORUGAMON_FQNAME = ALT_DM20_DORUGAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_DORUGAMON_FQNAME_LEN = sizeof(ALT_DM20_DORUGAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_DORUGUREMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:doruguremon";
    inline static constexpr const char* ALT_DM20_DORUGUREMON_FQID = ALT_DM20_DORUGUREMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_DORUGUREMON_FQID_LEN = sizeof(ALT_DM20_DORUGUREMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_DORUGUREMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:DORUguremon";
    inline static constexpr const char* ALT_DM20_DORUGUREMON_FQNAME = ALT_DM20_DORUGUREMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_DORUGUREMON_FQNAME_LEN = sizeof(ALT_DM20_DORUGUREMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_DORUMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:dorumon";
    inline static constexpr const char* ALT_DM20_DORUMON_FQID = ALT_DM20_DORUMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_DORUMON_FQID_LEN = sizeof(ALT_DM20_DORUMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_DORUMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:DORUmon";
    inline static constexpr const char* ALT_DM20_DORUMON_FQNAME = ALT_DM20_DORUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_DORUMON_FQNAME_LEN = sizeof(ALT_DM20_DORUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_DRACOMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:dracomon";
    inline static constexpr const char* ALT_DM20_DRACOMON_FQID = ALT_DM20_DRACOMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_DRACOMON_FQID_LEN = sizeof(ALT_DM20_DRACOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_DRACOMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Dracomon";
    inline static constexpr const char* ALT_DM20_DRACOMON_FQNAME = ALT_DM20_DRACOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_DRACOMON_FQNAME_LEN = sizeof(ALT_DM20_DRACOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_DRIMOGEMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:drimogemon";
    inline static constexpr const char* ALT_DM20_DRIMOGEMON_FQID = ALT_DM20_DRIMOGEMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_DRIMOGEMON_FQID_LEN = sizeof(ALT_DM20_DRIMOGEMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_DRIMOGEMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Drimogemon";
    inline static constexpr const char* ALT_DM20_DRIMOGEMON_FQNAME = ALT_DM20_DRIMOGEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_DRIMOGEMON_FQNAME_LEN = sizeof(ALT_DM20_DRIMOGEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_DURAMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:duramon";
    inline static constexpr const char* ALT_DM20_DURAMON_FQID = ALT_DM20_DURAMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_DURAMON_FQID_LEN = sizeof(ALT_DM20_DURAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_DURAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Duramon";
    inline static constexpr const char* ALT_DM20_DURAMON_FQNAME = ALT_DM20_DURAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_DURAMON_FQNAME_LEN = sizeof(ALT_DM20_DURAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_DURANDAMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:durandamon";
    inline static constexpr const char* ALT_DM20_DURANDAMON_FQID = ALT_DM20_DURANDAMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_DURANDAMON_FQID_LEN = sizeof(ALT_DM20_DURANDAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_DURANDAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Durandamon";
    inline static constexpr const char* ALT_DM20_DURANDAMON_FQNAME = ALT_DM20_DURANDAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_DURANDAMON_FQNAME_LEN = sizeof(ALT_DM20_DURANDAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_ELECMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:elecmon";
    inline static constexpr const char* ALT_DM20_ELECMON_FQID = ALT_DM20_ELECMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_ELECMON_FQID_LEN = sizeof(ALT_DM20_ELECMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_ELECMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Elecmon";
    inline static constexpr const char* ALT_DM20_ELECMON_FQNAME = ALT_DM20_ELECMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_ELECMON_FQNAME_LEN = sizeof(ALT_DM20_ELECMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_ETEMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:etemon";
    inline static constexpr const char* ALT_DM20_ETEMON_FQID = ALT_DM20_ETEMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_ETEMON_FQID_LEN = sizeof(ALT_DM20_ETEMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_ETEMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Etemon";
    inline static constexpr const char* ALT_DM20_ETEMON_FQNAME = ALT_DM20_ETEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_ETEMON_FQNAME_LEN = sizeof(ALT_DM20_ETEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_EXAMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:examon";
    inline static constexpr const char* ALT_DM20_EXAMON_FQID = ALT_DM20_EXAMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_EXAMON_FQID_LEN = sizeof(ALT_DM20_EXAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_EXAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Examon";
    inline static constexpr const char* ALT_DM20_EXAMON_FQNAME = ALT_DM20_EXAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_EXAMON_FQNAME_LEN = sizeof(ALT_DM20_EXAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_EX_TYRANOMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:ex_tyranomon";
    inline static constexpr const char* ALT_DM20_EX_TYRANOMON_FQID = ALT_DM20_EX_TYRANOMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_EX_TYRANOMON_FQID_LEN = sizeof(ALT_DM20_EX_TYRANOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_EX_TYRANOMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Ex-Tyranomon";
    inline static constexpr const char* ALT_DM20_EX_TYRANOMON_FQNAME = ALT_DM20_EX_TYRANOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_EX_TYRANOMON_FQNAME_LEN = sizeof(ALT_DM20_EX_TYRANOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_FIRAMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:firamon";
    inline static constexpr const char* ALT_DM20_FIRAMON_FQID = ALT_DM20_FIRAMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_FIRAMON_FQID_LEN = sizeof(ALT_DM20_FIRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_FIRAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Firamon";
    inline static constexpr const char* ALT_DM20_FIRAMON_FQNAME = ALT_DM20_FIRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_FIRAMON_FQNAME_LEN = sizeof(ALT_DM20_FIRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_FLAREMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:flaremon";
    inline static constexpr const char* ALT_DM20_FLAREMON_FQID = ALT_DM20_FLAREMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_FLAREMON_FQID_LEN = sizeof(ALT_DM20_FLAREMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_FLAREMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Flaremon";
    inline static constexpr const char* ALT_DM20_FLAREMON_FQNAME = ALT_DM20_FLAREMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_FLAREMON_FQNAME_LEN = sizeof(ALT_DM20_FLAREMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_FLYMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:flymon";
    inline static constexpr const char* ALT_DM20_FLYMON_FQID = ALT_DM20_FLYMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_FLYMON_FQID_LEN = sizeof(ALT_DM20_FLYMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_FLYMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Flymon";
    inline static constexpr const char* ALT_DM20_FLYMON_FQNAME = ALT_DM20_FLYMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_FLYMON_FQNAME_LEN = sizeof(ALT_DM20_FLYMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_GABUMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:gabumon";
    inline static constexpr const char* ALT_DM20_GABUMON_FQID = ALT_DM20_GABUMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_GABUMON_FQID_LEN = sizeof(ALT_DM20_GABUMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_GABUMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Gabumon";
    inline static constexpr const char* ALT_DM20_GABUMON_FQNAME = ALT_DM20_GABUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_GABUMON_FQNAME_LEN = sizeof(ALT_DM20_GABUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_GARURUMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:garurumon";
    inline static constexpr const char* ALT_DM20_GARURUMON_FQID = ALT_DM20_GARURUMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_GARURUMON_FQID_LEN = sizeof(ALT_DM20_GARURUMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_GARURUMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Garurumon";
    inline static constexpr const char* ALT_DM20_GARURUMON_FQNAME = ALT_DM20_GARURUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_GARURUMON_FQNAME_LEN = sizeof(ALT_DM20_GARURUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_GAZIMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:gazimon";
    inline static constexpr const char* ALT_DM20_GAZIMON_FQID = ALT_DM20_GAZIMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_GAZIMON_FQID_LEN = sizeof(ALT_DM20_GAZIMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_GAZIMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Gazimon";
    inline static constexpr const char* ALT_DM20_GAZIMON_FQNAME = ALT_DM20_GAZIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_GAZIMON_FQNAME_LEN = sizeof(ALT_DM20_GAZIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_GIROMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:giromon";
    inline static constexpr const char* ALT_DM20_GIROMON_FQID = ALT_DM20_GIROMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_GIROMON_FQID_LEN = sizeof(ALT_DM20_GIROMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_GIROMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Giromon";
    inline static constexpr const char* ALT_DM20_GIROMON_FQNAME = ALT_DM20_GIROMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_GIROMON_FQNAME_LEN = sizeof(ALT_DM20_GIROMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_GIZAMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:gizamon";
    inline static constexpr const char* ALT_DM20_GIZAMON_FQID = ALT_DM20_GIZAMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_GIZAMON_FQID_LEN = sizeof(ALT_DM20_GIZAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_GIZAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Gizamon";
    inline static constexpr const char* ALT_DM20_GIZAMON_FQNAME = ALT_DM20_GIZAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_GIZAMON_FQNAME_LEN = sizeof(ALT_DM20_GIZAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_GRACE_NOVAMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:grace_novamon";
    inline static constexpr const char* ALT_DM20_GRACE_NOVAMON_FQID = ALT_DM20_GRACE_NOVAMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_GRACE_NOVAMON_FQID_LEN = sizeof(ALT_DM20_GRACE_NOVAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_GRACE_NOVAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Grace Novamon";
    inline static constexpr const char* ALT_DM20_GRACE_NOVAMON_FQNAME = ALT_DM20_GRACE_NOVAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_GRACE_NOVAMON_FQNAME_LEN = sizeof(ALT_DM20_GRACE_NOVAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_GREYMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:greymon";
    inline static constexpr const char* ALT_DM20_GREYMON_FQID = ALT_DM20_GREYMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_GREYMON_FQID_LEN = sizeof(ALT_DM20_GREYMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_GREYMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Greymon";
    inline static constexpr const char* ALT_DM20_GREYMON_FQNAME = ALT_DM20_GREYMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_GREYMON_FQNAME_LEN = sizeof(ALT_DM20_GREYMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_GROUNDRAMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:groundramon";
    inline static constexpr const char* ALT_DM20_GROUNDRAMON_FQID = ALT_DM20_GROUNDRAMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_GROUNDRAMON_FQID_LEN = sizeof(ALT_DM20_GROUNDRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_GROUNDRAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Groundramon";
    inline static constexpr const char* ALT_DM20_GROUNDRAMON_FQNAME = ALT_DM20_GROUNDRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_GROUNDRAMON_FQNAME_LEN = sizeof(ALT_DM20_GROUNDRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_HACKMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:hackmon";
    inline static constexpr const char* ALT_DM20_HACKMON_FQID = ALT_DM20_HACKMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_HACKMON_FQID_LEN = sizeof(ALT_DM20_HACKMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_HACKMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Hackmon";
    inline static constexpr const char* ALT_DM20_HACKMON_FQNAME = ALT_DM20_HACKMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_HACKMON_FQNAME_LEN = sizeof(ALT_DM20_HACKMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_HI_ANDROMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:hi_andromon";
    inline static constexpr const char* ALT_DM20_HI_ANDROMON_FQID = ALT_DM20_HI_ANDROMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_HI_ANDROMON_FQID_LEN = sizeof(ALT_DM20_HI_ANDROMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_HI_ANDROMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Hi Andromon";
    inline static constexpr const char* ALT_DM20_HI_ANDROMON_FQNAME = ALT_DM20_HI_ANDROMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_HI_ANDROMON_FQNAME_LEN = sizeof(ALT_DM20_HI_ANDROMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_JESMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:jesmon";
    inline static constexpr const char* ALT_DM20_JESMON_FQID = ALT_DM20_JESMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_JESMON_FQID_LEN = sizeof(ALT_DM20_JESMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_JESMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Jesmon";
    inline static constexpr const char* ALT_DM20_JESMON_FQNAME = ALT_DM20_JESMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_JESMON_FQNAME_LEN = sizeof(ALT_DM20_JESMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_KABUTERIMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:kabuterimon";
    inline static constexpr const char* ALT_DM20_KABUTERIMON_FQID = ALT_DM20_KABUTERIMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_KABUTERIMON_FQID_LEN = sizeof(ALT_DM20_KABUTERIMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_KABUTERIMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Kabuterimon";
    inline static constexpr const char* ALT_DM20_KABUTERIMON_FQNAME = ALT_DM20_KABUTERIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_KABUTERIMON_FQNAME_LEN = sizeof(ALT_DM20_KABUTERIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_KING_ETEMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:king_etemon";
    inline static constexpr const char* ALT_DM20_KING_ETEMON_FQID = ALT_DM20_KING_ETEMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_KING_ETEMON_FQID_LEN = sizeof(ALT_DM20_KING_ETEMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_KING_ETEMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:King Etemon";
    inline static constexpr const char* ALT_DM20_KING_ETEMON_FQNAME = ALT_DM20_KING_ETEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_KING_ETEMON_FQNAME_LEN = sizeof(ALT_DM20_KING_ETEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_KOROMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:koromon";
    inline static constexpr const char* ALT_DM20_KOROMON_FQID = ALT_DM20_KOROMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_KOROMON_FQID_LEN = sizeof(ALT_DM20_KOROMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_KOROMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Koromon";
    inline static constexpr const char* ALT_DM20_KOROMON_FQNAME = ALT_DM20_KOROMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_KOROMON_FQNAME_LEN = sizeof(ALT_DM20_KOROMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_KUNEMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:kunemon";
    inline static constexpr const char* ALT_DM20_KUNEMON_FQID = ALT_DM20_KUNEMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_KUNEMON_FQID_LEN = sizeof(ALT_DM20_KUNEMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_KUNEMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Kunemon";
    inline static constexpr const char* ALT_DM20_KUNEMON_FQNAME = ALT_DM20_KUNEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_KUNEMON_FQNAME_LEN = sizeof(ALT_DM20_KUNEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_KUWAGAMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:kuwagamon";
    inline static constexpr const char* ALT_DM20_KUWAGAMON_FQID = ALT_DM20_KUWAGAMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_KUWAGAMON_FQID_LEN = sizeof(ALT_DM20_KUWAGAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_KUWAGAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Kuwagamon";
    inline static constexpr const char* ALT_DM20_KUWAGAMON_FQNAME = ALT_DM20_KUWAGAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_KUWAGAMON_FQNAME_LEN = sizeof(ALT_DM20_KUWAGAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_LEKISMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:lekismon";
    inline static constexpr const char* ALT_DM20_LEKISMON_FQID = ALT_DM20_LEKISMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_LEKISMON_FQID_LEN = sizeof(ALT_DM20_LEKISMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_LEKISMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Lekismon";
    inline static constexpr const char* ALT_DM20_LEKISMON_FQNAME = ALT_DM20_LEKISMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_LEKISMON_FQNAME_LEN = sizeof(ALT_DM20_LEKISMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_LEOMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:leomon";
    inline static constexpr const char* ALT_DM20_LEOMON_FQID = ALT_DM20_LEOMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_LEOMON_FQID_LEN = sizeof(ALT_DM20_LEOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_LEOMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Leomon";
    inline static constexpr const char* ALT_DM20_LEOMON_FQNAME = ALT_DM20_LEOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_LEOMON_FQNAME_LEN = sizeof(ALT_DM20_LEOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_LUNAMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:lunamon";
    inline static constexpr const char* ALT_DM20_LUNAMON_FQID = ALT_DM20_LUNAMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_LUNAMON_FQID_LEN = sizeof(ALT_DM20_LUNAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_LUNAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Lunamon";
    inline static constexpr const char* ALT_DM20_LUNAMON_FQNAME = ALT_DM20_LUNAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_LUNAMON_FQNAME_LEN = sizeof(ALT_DM20_LUNAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_MAMEMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:mamemon";
    inline static constexpr const char* ALT_DM20_MAMEMON_FQID = ALT_DM20_MAMEMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_MAMEMON_FQID_LEN = sizeof(ALT_DM20_MAMEMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_MAMEMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Mamemon";
    inline static constexpr const char* ALT_DM20_MAMEMON_FQNAME = ALT_DM20_MAMEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_MAMEMON_FQNAME_LEN = sizeof(ALT_DM20_MAMEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_MEGADRAMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:megadramon";
    inline static constexpr const char* ALT_DM20_MEGADRAMON_FQID = ALT_DM20_MEGADRAMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_MEGADRAMON_FQID_LEN = sizeof(ALT_DM20_MEGADRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_MEGADRAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Megadramon";
    inline static constexpr const char* ALT_DM20_MEGADRAMON_FQNAME = ALT_DM20_MEGADRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_MEGADRAMON_FQNAME_LEN = sizeof(ALT_DM20_MEGADRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_MEICOOMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:meicoomon";
    inline static constexpr const char* ALT_DM20_MEICOOMON_FQID = ALT_DM20_MEICOOMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_MEICOOMON_FQID_LEN = sizeof(ALT_DM20_MEICOOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_MEICOOMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Meicoomon";
    inline static constexpr const char* ALT_DM20_MEICOOMON_FQNAME = ALT_DM20_MEICOOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_MEICOOMON_FQNAME_LEN = sizeof(ALT_DM20_MEICOOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_MEICRACKMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:meicrackmon";
    inline static constexpr const char* ALT_DM20_MEICRACKMON_FQID = ALT_DM20_MEICRACKMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_MEICRACKMON_FQID_LEN = sizeof(ALT_DM20_MEICRACKMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_MEICRACKMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Meicrackmon";
    inline static constexpr const char* ALT_DM20_MEICRACKMON_FQNAME = ALT_DM20_MEICRACKMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_MEICRACKMON_FQNAME_LEN = sizeof(ALT_DM20_MEICRACKMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_MERAMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:meramon";
    inline static constexpr const char* ALT_DM20_MERAMON_FQID = ALT_DM20_MERAMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_MERAMON_FQID_LEN = sizeof(ALT_DM20_MERAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_MERAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Meramon";
    inline static constexpr const char* ALT_DM20_MERAMON_FQNAME = ALT_DM20_MERAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_MERAMON_FQNAME_LEN = sizeof(ALT_DM20_MERAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_METAL_GREYMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:metal_greymon";
    inline static constexpr const char* ALT_DM20_METAL_GREYMON_FQID = ALT_DM20_METAL_GREYMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_METAL_GREYMON_FQID_LEN = sizeof(ALT_DM20_METAL_GREYMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_METAL_GREYMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Metal Greymon";
    inline static constexpr const char* ALT_DM20_METAL_GREYMON_FQNAME = ALT_DM20_METAL_GREYMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_METAL_GREYMON_FQNAME_LEN = sizeof(ALT_DM20_METAL_GREYMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_METAL_MAMEMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:metal_mamemon";
    inline static constexpr const char* ALT_DM20_METAL_MAMEMON_FQID = ALT_DM20_METAL_MAMEMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_METAL_MAMEMON_FQID_LEN = sizeof(ALT_DM20_METAL_MAMEMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_METAL_MAMEMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Metal Mamemon";
    inline static constexpr const char* ALT_DM20_METAL_MAMEMON_FQNAME = ALT_DM20_METAL_MAMEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_METAL_MAMEMON_FQNAME_LEN = sizeof(ALT_DM20_METAL_MAMEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_METAL_TYRANOMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:metal_tyranomon";
    inline static constexpr const char* ALT_DM20_METAL_TYRANOMON_FQID = ALT_DM20_METAL_TYRANOMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_METAL_TYRANOMON_FQID_LEN = sizeof(ALT_DM20_METAL_TYRANOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_METAL_TYRANOMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Metal Tyranomon";
    inline static constexpr const char* ALT_DM20_METAL_TYRANOMON_FQNAME = ALT_DM20_METAL_TYRANOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_METAL_TYRANOMON_FQNAME_LEN = sizeof(ALT_DM20_METAL_TYRANOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_MOJYAMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:mojyamon";
    inline static constexpr const char* ALT_DM20_MOJYAMON_FQID = ALT_DM20_MOJYAMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_MOJYAMON_FQID_LEN = sizeof(ALT_DM20_MOJYAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_MOJYAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Mojyamon";
    inline static constexpr const char* ALT_DM20_MOJYAMON_FQNAME = ALT_DM20_MOJYAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_MOJYAMON_FQNAME_LEN = sizeof(ALT_DM20_MOJYAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_MONOCHROMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:monochromon";
    inline static constexpr const char* ALT_DM20_MONOCHROMON_FQID = ALT_DM20_MONOCHROMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_MONOCHROMON_FQID_LEN = sizeof(ALT_DM20_MONOCHROMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_MONOCHROMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Monochromon";
    inline static constexpr const char* ALT_DM20_MONOCHROMON_FQNAME = ALT_DM20_MONOCHROMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_MONOCHROMON_FQNAME_LEN = sizeof(ALT_DM20_MONOCHROMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_MONZAEMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:monzaemon";
    inline static constexpr const char* ALT_DM20_MONZAEMON_FQID = ALT_DM20_MONZAEMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_MONZAEMON_FQID_LEN = sizeof(ALT_DM20_MONZAEMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_MONZAEMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Monzaemon";
    inline static constexpr const char* ALT_DM20_MONZAEMON_FQNAME = ALT_DM20_MONZAEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_MONZAEMON_FQNAME_LEN = sizeof(ALT_DM20_MONZAEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_MUGENDRAMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:mugendramon";
    inline static constexpr const char* ALT_DM20_MUGENDRAMON_FQID = ALT_DM20_MUGENDRAMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_MUGENDRAMON_FQID_LEN = sizeof(ALT_DM20_MUGENDRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_MUGENDRAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Mugendramon";
    inline static constexpr const char* ALT_DM20_MUGENDRAMON_FQNAME = ALT_DM20_MUGENDRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_MUGENDRAMON_FQNAME_LEN = sizeof(ALT_DM20_MUGENDRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_NANIMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:nanimon";
    inline static constexpr const char* ALT_DM20_NANIMON_FQID = ALT_DM20_NANIMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_NANIMON_FQID_LEN = sizeof(ALT_DM20_NANIMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_NANIMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Nanimon";
    inline static constexpr const char* ALT_DM20_NANIMON_FQNAME = ALT_DM20_NANIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_NANIMON_FQNAME_LEN = sizeof(ALT_DM20_NANIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_NANOMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:nanomon";
    inline static constexpr const char* ALT_DM20_NANOMON_FQID = ALT_DM20_NANOMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_NANOMON_FQID_LEN = sizeof(ALT_DM20_NANOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_NANOMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Nanomon";
    inline static constexpr const char* ALT_DM20_NANOMON_FQNAME = ALT_DM20_NANOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_NANOMON_FQNAME_LEN = sizeof(ALT_DM20_NANOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_NUMEMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:numemon";
    inline static constexpr const char* ALT_DM20_NUMEMON_FQID = ALT_DM20_NUMEMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_NUMEMON_FQID_LEN = sizeof(ALT_DM20_NUMEMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_NUMEMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Numemon";
    inline static constexpr const char* ALT_DM20_NUMEMON_FQNAME = ALT_DM20_NUMEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_NUMEMON_FQNAME_LEN = sizeof(ALT_DM20_NUMEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_NYAROMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:nyaromon";
    inline static constexpr const char* ALT_DM20_NYAROMON_FQID = ALT_DM20_NYAROMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_NYAROMON_FQID_LEN = sizeof(ALT_DM20_NYAROMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_NYAROMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Nyaromon";
    inline static constexpr const char* ALT_DM20_NYAROMON_FQNAME = ALT_DM20_NYAROMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_NYAROMON_FQNAME_LEN = sizeof(ALT_DM20_NYAROMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_OGREMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:ogremon";
    inline static constexpr const char* ALT_DM20_OGREMON_FQID = ALT_DM20_OGREMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_OGREMON_FQID_LEN = sizeof(ALT_DM20_OGREMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_OGREMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Ogremon";
    inline static constexpr const char* ALT_DM20_OGREMON_FQNAME = ALT_DM20_OGREMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_OGREMON_FQNAME_LEN = sizeof(ALT_DM20_OGREMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_OMEGAMON_ALTER_S_FQID_ARR[] CONFIG_STRING_SECTION = "dm:omegamon_alter_s";
    inline static constexpr const char* ALT_DM20_OMEGAMON_ALTER_S_FQID = ALT_DM20_OMEGAMON_ALTER_S_FQID_ARR;
    inline static constexpr size_t ALT_DM20_OMEGAMON_ALTER_S_FQID_LEN = sizeof(ALT_DM20_OMEGAMON_ALTER_S_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_OMEGAMON_ALTER_S_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Omegamon Alter S";
    inline static constexpr const char* ALT_DM20_OMEGAMON_ALTER_S_FQNAME = ALT_DM20_OMEGAMON_ALTER_S_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_OMEGAMON_ALTER_S_FQNAME_LEN = sizeof(ALT_DM20_OMEGAMON_ALTER_S_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_OMEGAMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:omegamon";
    inline static constexpr const char* ALT_DM20_OMEGAMON_FQID = ALT_DM20_OMEGAMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_OMEGAMON_FQID_LEN = sizeof(ALT_DM20_OMEGAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_OMEGAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Omegamon";
    inline static constexpr const char* ALT_DM20_OMEGAMON_FQNAME = ALT_DM20_OMEGAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_OMEGAMON_FQNAME_LEN = sizeof(ALT_DM20_OMEGAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_PAGUMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:pagumon";
    inline static constexpr const char* ALT_DM20_PAGUMON_FQID = ALT_DM20_PAGUMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_PAGUMON_FQID_LEN = sizeof(ALT_DM20_PAGUMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_PAGUMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Pagumon";
    inline static constexpr const char* ALT_DM20_PAGUMON_FQNAME = ALT_DM20_PAGUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_PAGUMON_FQNAME_LEN = sizeof(ALT_DM20_PAGUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_PALMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:palmon";
    inline static constexpr const char* ALT_DM20_PALMON_FQID = ALT_DM20_PALMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_PALMON_FQID_LEN = sizeof(ALT_DM20_PALMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_PALMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Palmon";
    inline static constexpr const char* ALT_DM20_PALMON_FQNAME = ALT_DM20_PALMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_PALMON_FQNAME_LEN = sizeof(ALT_DM20_PALMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_PATAMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:patamon";
    inline static constexpr const char* ALT_DM20_PATAMON_FQID = ALT_DM20_PATAMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_PATAMON_FQID_LEN = sizeof(ALT_DM20_PATAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_PATAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Patamon";
    inline static constexpr const char* ALT_DM20_PATAMON_FQNAME = ALT_DM20_PATAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_PATAMON_FQNAME_LEN = sizeof(ALT_DM20_PATAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_PETITMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:petitmon";
    inline static constexpr const char* ALT_DM20_PETITMON_FQID = ALT_DM20_PETITMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_PETITMON_FQID_LEN = sizeof(ALT_DM20_PETITMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_PETITMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Petitmon";
    inline static constexpr const char* ALT_DM20_PETITMON_FQNAME = ALT_DM20_PETITMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_PETITMON_FQNAME_LEN = sizeof(ALT_DM20_PETITMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_PICCOLOMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:piccolomon";
    inline static constexpr const char* ALT_DM20_PICCOLOMON_FQID = ALT_DM20_PICCOLOMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_PICCOLOMON_FQID_LEN = sizeof(ALT_DM20_PICCOLOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_PICCOLOMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Piccolomon";
    inline static constexpr const char* ALT_DM20_PICCOLOMON_FQNAME = ALT_DM20_PICCOLOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_PICCOLOMON_FQNAME_LEN = sizeof(ALT_DM20_PICCOLOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_PINOCHIMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:pinochimon";
    inline static constexpr const char* ALT_DM20_PINOCHIMON_FQID = ALT_DM20_PINOCHIMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_PINOCHIMON_FQID_LEN = sizeof(ALT_DM20_PINOCHIMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_PINOCHIMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Pinochimon";
    inline static constexpr const char* ALT_DM20_PINOCHIMON_FQNAME = ALT_DM20_PINOCHIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_PINOCHIMON_FQNAME_LEN = sizeof(ALT_DM20_PINOCHIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_PITCHMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:pitchmon";
    inline static constexpr const char* ALT_DM20_PITCHMON_FQID = ALT_DM20_PITCHMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_PITCHMON_FQID_LEN = sizeof(ALT_DM20_PITCHMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_PITCHMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Pitchmon";
    inline static constexpr const char* ALT_DM20_PITCHMON_FQNAME = ALT_DM20_PITCHMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_PITCHMON_FQNAME_LEN = sizeof(ALT_DM20_PITCHMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_PIYOMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:piyomon";
    inline static constexpr const char* ALT_DM20_PIYOMON_FQID = ALT_DM20_PIYOMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_PIYOMON_FQID_LEN = sizeof(ALT_DM20_PIYOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_PIYOMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Piyomon";
    inline static constexpr const char* ALT_DM20_PIYOMON_FQNAME = ALT_DM20_PIYOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_PIYOMON_FQNAME_LEN = sizeof(ALT_DM20_PIYOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_PLOTMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:plotmon";
    inline static constexpr const char* ALT_DM20_PLOTMON_FQID = ALT_DM20_PLOTMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_PLOTMON_FQID_LEN = sizeof(ALT_DM20_PLOTMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_PLOTMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Plotmon";
    inline static constexpr const char* ALT_DM20_PLOTMON_FQNAME = ALT_DM20_PLOTMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_PLOTMON_FQNAME_LEN = sizeof(ALT_DM20_PLOTMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_POYOMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:poyomon";
    inline static constexpr const char* ALT_DM20_POYOMON_FQID = ALT_DM20_POYOMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_POYOMON_FQID_LEN = sizeof(ALT_DM20_POYOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_POYOMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Poyomon";
    inline static constexpr const char* ALT_DM20_POYOMON_FQNAME = ALT_DM20_POYOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_POYOMON_FQNAME_LEN = sizeof(ALT_DM20_POYOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_PUKAMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:pukamon";
    inline static constexpr const char* ALT_DM20_PUKAMON_FQID = ALT_DM20_PUKAMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_PUKAMON_FQID_LEN = sizeof(ALT_DM20_PUKAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_PUKAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Pukamon";
    inline static constexpr const char* ALT_DM20_PUKAMON_FQNAME = ALT_DM20_PUKAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_PUKAMON_FQNAME_LEN = sizeof(ALT_DM20_PUKAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_PUNIMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:punimon";
    inline static constexpr const char* ALT_DM20_PUNIMON_FQID = ALT_DM20_PUNIMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_PUNIMON_FQID_LEN = sizeof(ALT_DM20_PUNIMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_PUNIMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Punimon";
    inline static constexpr const char* ALT_DM20_PUNIMON_FQNAME = ALT_DM20_PUNIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_PUNIMON_FQNAME_LEN = sizeof(ALT_DM20_PUNIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_RAREMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:raremon";
    inline static constexpr const char* ALT_DM20_RAREMON_FQID = ALT_DM20_RAREMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_RAREMON_FQID_LEN = sizeof(ALT_DM20_RAREMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_RAREMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Raremon";
    inline static constexpr const char* ALT_DM20_RAREMON_FQNAME = ALT_DM20_RAREMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_RAREMON_FQNAME_LEN = sizeof(ALT_DM20_RAREMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_RASIELMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:rasielmon";
    inline static constexpr const char* ALT_DM20_RASIELMON_FQID = ALT_DM20_RASIELMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_RASIELMON_FQID_LEN = sizeof(ALT_DM20_RASIELMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_RASIELMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Rasielmon";
    inline static constexpr const char* ALT_DM20_RASIELMON_FQNAME = ALT_DM20_RASIELMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_RASIELMON_FQNAME_LEN = sizeof(ALT_DM20_RASIELMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_RUST_TYRANOMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:rust_tyranomon";
    inline static constexpr const char* ALT_DM20_RUST_TYRANOMON_FQID = ALT_DM20_RUST_TYRANOMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_RUST_TYRANOMON_FQID_LEN = sizeof(ALT_DM20_RUST_TYRANOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_RUST_TYRANOMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Rust Tyranomon";
    inline static constexpr const char* ALT_DM20_RUST_TYRANOMON_FQNAME = ALT_DM20_RUST_TYRANOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_RUST_TYRANOMON_FQNAME_LEN = sizeof(ALT_DM20_RUST_TYRANOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_SAKUMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:sakumon";
    inline static constexpr const char* ALT_DM20_SAKUMON_FQID = ALT_DM20_SAKUMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_SAKUMON_FQID_LEN = sizeof(ALT_DM20_SAKUMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_SAKUMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Sakumon";
    inline static constexpr const char* ALT_DM20_SAKUMON_FQNAME = ALT_DM20_SAKUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_SAKUMON_FQNAME_LEN = sizeof(ALT_DM20_SAKUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_SAKUTTOMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:sakuttomon";
    inline static constexpr const char* ALT_DM20_SAKUTTOMON_FQID = ALT_DM20_SAKUTTOMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_SAKUTTOMON_FQID_LEN = sizeof(ALT_DM20_SAKUTTOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_SAKUTTOMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Sakuttomon";
    inline static constexpr const char* ALT_DM20_SAKUTTOMON_FQNAME = ALT_DM20_SAKUTTOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_SAKUTTOMON_FQNAME_LEN = sizeof(ALT_DM20_SAKUTTOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_SAVIOR_HACKMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:savior_hackmon";
    inline static constexpr const char* ALT_DM20_SAVIOR_HACKMON_FQID = ALT_DM20_SAVIOR_HACKMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_SAVIOR_HACKMON_FQID_LEN = sizeof(ALT_DM20_SAVIOR_HACKMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_SAVIOR_HACKMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Savior Hackmon";
    inline static constexpr const char* ALT_DM20_SAVIOR_HACKMON_FQNAME = ALT_DM20_SAVIOR_HACKMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_SAVIOR_HACKMON_FQNAME_LEN = sizeof(ALT_DM20_SAVIOR_HACKMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_SCUMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:scumon";
    inline static constexpr const char* ALT_DM20_SCUMON_FQID = ALT_DM20_SCUMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_SCUMON_FQID_LEN = sizeof(ALT_DM20_SCUMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_SCUMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Scumon";
    inline static constexpr const char* ALT_DM20_SCUMON_FQNAME = ALT_DM20_SCUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_SCUMON_FQNAME_LEN = sizeof(ALT_DM20_SCUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_SEADRAMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:seadramon";
    inline static constexpr const char* ALT_DM20_SEADRAMON_FQID = ALT_DM20_SEADRAMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_SEADRAMON_FQID_LEN = sizeof(ALT_DM20_SEADRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_SEADRAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Seadramon";
    inline static constexpr const char* ALT_DM20_SEADRAMON_FQNAME = ALT_DM20_SEADRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_SEADRAMON_FQNAME_LEN = sizeof(ALT_DM20_SEADRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_SHELLMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:shellmon";
    inline static constexpr const char* ALT_DM20_SHELLMON_FQID = ALT_DM20_SHELLMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_SHELLMON_FQID_LEN = sizeof(ALT_DM20_SHELLMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_SHELLMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Shellmon";
    inline static constexpr const char* ALT_DM20_SHELLMON_FQNAME = ALT_DM20_SHELLMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_SHELLMON_FQNAME_LEN = sizeof(ALT_DM20_SHELLMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_SKULL_GREYMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:skull_greymon";
    inline static constexpr const char* ALT_DM20_SKULL_GREYMON_FQID = ALT_DM20_SKULL_GREYMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_SKULL_GREYMON_FQID_LEN = sizeof(ALT_DM20_SKULL_GREYMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_SKULL_GREYMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Skull Greymon";
    inline static constexpr const char* ALT_DM20_SKULL_GREYMON_FQNAME = ALT_DM20_SKULL_GREYMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_SKULL_GREYMON_FQNAME_LEN = sizeof(ALT_DM20_SKULL_GREYMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_SKULL_MAMMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:skull_mammon";
    inline static constexpr const char* ALT_DM20_SKULL_MAMMON_FQID = ALT_DM20_SKULL_MAMMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_SKULL_MAMMON_FQID_LEN = sizeof(ALT_DM20_SKULL_MAMMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_SKULL_MAMMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Skull Mammon";
    inline static constexpr const char* ALT_DM20_SKULL_MAMMON_FQNAME = ALT_DM20_SKULL_MAMMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_SKULL_MAMMON_FQNAME_LEN = sizeof(ALT_DM20_SKULL_MAMMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_SLAYERDRAMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:slayerdramon";
    inline static constexpr const char* ALT_DM20_SLAYERDRAMON_FQID = ALT_DM20_SLAYERDRAMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_SLAYERDRAMON_FQID_LEN = sizeof(ALT_DM20_SLAYERDRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_SLAYERDRAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Slayerdramon";
    inline static constexpr const char* ALT_DM20_SLAYERDRAMON_FQNAME = ALT_DM20_SLAYERDRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_SLAYERDRAMON_FQNAME_LEN = sizeof(ALT_DM20_SLAYERDRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_TAICHIS_AGUMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:taichis_agumon";
    inline static constexpr const char* ALT_DM20_TAICHIS_AGUMON_FQID = ALT_DM20_TAICHIS_AGUMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_TAICHIS_AGUMON_FQID_LEN = sizeof(ALT_DM20_TAICHIS_AGUMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_TAICHIS_AGUMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Taichis Agumon";
    inline static constexpr const char* ALT_DM20_TAICHIS_AGUMON_FQNAME = ALT_DM20_TAICHIS_AGUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_TAICHIS_AGUMON_FQNAME_LEN = sizeof(ALT_DM20_TAICHIS_AGUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_TAICHIS_GREYMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:taichis_greymon";
    inline static constexpr const char* ALT_DM20_TAICHIS_GREYMON_FQID = ALT_DM20_TAICHIS_GREYMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_TAICHIS_GREYMON_FQID_LEN = sizeof(ALT_DM20_TAICHIS_GREYMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_TAICHIS_GREYMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Taichis Greymon";
    inline static constexpr const char* ALT_DM20_TAICHIS_GREYMON_FQNAME = ALT_DM20_TAICHIS_GREYMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_TAICHIS_GREYMON_FQNAME_LEN = sizeof(ALT_DM20_TAICHIS_GREYMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_TAICHIS_METAL_GREYMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:taichis_metal_greymon";
    inline static constexpr const char* ALT_DM20_TAICHIS_METAL_GREYMON_FQID = ALT_DM20_TAICHIS_METAL_GREYMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_TAICHIS_METAL_GREYMON_FQID_LEN = sizeof(ALT_DM20_TAICHIS_METAL_GREYMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_TAICHIS_METAL_GREYMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Taichis Metal Greymon";
    inline static constexpr const char* ALT_DM20_TAICHIS_METAL_GREYMON_FQNAME = ALT_DM20_TAICHIS_METAL_GREYMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_TAICHIS_METAL_GREYMON_FQNAME_LEN = sizeof(ALT_DM20_TAICHIS_METAL_GREYMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_TAICHIS_WAR_GREYMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:taichis_war_greymon";
    inline static constexpr const char* ALT_DM20_TAICHIS_WAR_GREYMON_FQID = ALT_DM20_TAICHIS_WAR_GREYMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_TAICHIS_WAR_GREYMON_FQID_LEN = sizeof(ALT_DM20_TAICHIS_WAR_GREYMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_TAICHIS_WAR_GREYMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Taichis War Greymon";
    inline static constexpr const char* ALT_DM20_TAICHIS_WAR_GREYMON_FQNAME = ALT_DM20_TAICHIS_WAR_GREYMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_TAICHIS_WAR_GREYMON_FQNAME_LEN = sizeof(ALT_DM20_TAICHIS_WAR_GREYMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_TANEMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:tanemon";
    inline static constexpr const char* ALT_DM20_TANEMON_FQID = ALT_DM20_TANEMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_TANEMON_FQID_LEN = sizeof(ALT_DM20_TANEMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_TANEMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Tanemon";
    inline static constexpr const char* ALT_DM20_TANEMON_FQNAME = ALT_DM20_TANEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_TANEMON_FQNAME_LEN = sizeof(ALT_DM20_TANEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_TITAMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:titamon";
    inline static constexpr const char* ALT_DM20_TITAMON_FQID = ALT_DM20_TITAMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_TITAMON_FQID_LEN = sizeof(ALT_DM20_TITAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_TITAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Titamon";
    inline static constexpr const char* ALT_DM20_TITAMON_FQNAME = ALT_DM20_TITAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_TITAMON_FQNAME_LEN = sizeof(ALT_DM20_TITAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_TOKOMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:tokomon";
    inline static constexpr const char* ALT_DM20_TOKOMON_FQID = ALT_DM20_TOKOMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_TOKOMON_FQID_LEN = sizeof(ALT_DM20_TOKOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_TOKOMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Tokomon";
    inline static constexpr const char* ALT_DM20_TOKOMON_FQNAME = ALT_DM20_TOKOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_TOKOMON_FQNAME_LEN = sizeof(ALT_DM20_TOKOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_TUNOMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:tunomon";
    inline static constexpr const char* ALT_DM20_TUNOMON_FQID = ALT_DM20_TUNOMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_TUNOMON_FQID_LEN = sizeof(ALT_DM20_TUNOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_TUNOMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Tunomon";
    inline static constexpr const char* ALT_DM20_TUNOMON_FQNAME = ALT_DM20_TUNOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_TUNOMON_FQNAME_LEN = sizeof(ALT_DM20_TUNOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_TUSKMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:tuskmon";
    inline static constexpr const char* ALT_DM20_TUSKMON_FQID = ALT_DM20_TUSKMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_TUSKMON_FQID_LEN = sizeof(ALT_DM20_TUSKMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_TUSKMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Tuskmon";
    inline static constexpr const char* ALT_DM20_TUSKMON_FQNAME = ALT_DM20_TUSKMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_TUSKMON_FQNAME_LEN = sizeof(ALT_DM20_TUSKMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_TYRANOMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:tyranomon";
    inline static constexpr const char* ALT_DM20_TYRANOMON_FQID = ALT_DM20_TYRANOMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_TYRANOMON_FQID_LEN = sizeof(ALT_DM20_TYRANOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_TYRANOMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Tyranomon";
    inline static constexpr const char* ALT_DM20_TYRANOMON_FQNAME = ALT_DM20_TYRANOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_TYRANOMON_FQNAME_LEN = sizeof(ALT_DM20_TYRANOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_UNIMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:unimon";
    inline static constexpr const char* ALT_DM20_UNIMON_FQID = ALT_DM20_UNIMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_UNIMON_FQID_LEN = sizeof(ALT_DM20_UNIMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_UNIMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Unimon";
    inline static constexpr const char* ALT_DM20_UNIMON_FQNAME = ALT_DM20_UNIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_UNIMON_FQNAME_LEN = sizeof(ALT_DM20_UNIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_VADEMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:vademon";
    inline static constexpr const char* ALT_DM20_VADEMON_FQID = ALT_DM20_VADEMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_VADEMON_FQID_LEN = sizeof(ALT_DM20_VADEMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_VADEMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Vademon";
    inline static constexpr const char* ALT_DM20_VADEMON_FQNAME = ALT_DM20_VADEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_VADEMON_FQNAME_LEN = sizeof(ALT_DM20_VADEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_VEGIMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:vegimon";
    inline static constexpr const char* ALT_DM20_VEGIMON_FQID = ALT_DM20_VEGIMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_VEGIMON_FQID_LEN = sizeof(ALT_DM20_VEGIMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_VEGIMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Vegimon";
    inline static constexpr const char* ALT_DM20_VEGIMON_FQNAME = ALT_DM20_VEGIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_VEGIMON_FQNAME_LEN = sizeof(ALT_DM20_VEGIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_WHAMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:whamon";
    inline static constexpr const char* ALT_DM20_WHAMON_FQID = ALT_DM20_WHAMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_WHAMON_FQID_LEN = sizeof(ALT_DM20_WHAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_WHAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Whamon";
    inline static constexpr const char* ALT_DM20_WHAMON_FQNAME = ALT_DM20_WHAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_WHAMON_FQNAME_LEN = sizeof(ALT_DM20_WHAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_WINGDRAMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:wingdramon";
    inline static constexpr const char* ALT_DM20_WINGDRAMON_FQID = ALT_DM20_WINGDRAMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_WINGDRAMON_FQID_LEN = sizeof(ALT_DM20_WINGDRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_WINGDRAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Wingdramon";
    inline static constexpr const char* ALT_DM20_WINGDRAMON_FQNAME = ALT_DM20_WINGDRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_WINGDRAMON_FQNAME_LEN = sizeof(ALT_DM20_WINGDRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_YAMATOS_GABUMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:yamatos_gabumon";
    inline static constexpr const char* ALT_DM20_YAMATOS_GABUMON_FQID = ALT_DM20_YAMATOS_GABUMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_YAMATOS_GABUMON_FQID_LEN = sizeof(ALT_DM20_YAMATOS_GABUMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_YAMATOS_GABUMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Yamatos Gabumon";
    inline static constexpr const char* ALT_DM20_YAMATOS_GABUMON_FQNAME = ALT_DM20_YAMATOS_GABUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_YAMATOS_GABUMON_FQNAME_LEN = sizeof(ALT_DM20_YAMATOS_GABUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_YAMATOS_GARURUMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:yamatos_garurumon";
    inline static constexpr const char* ALT_DM20_YAMATOS_GARURUMON_FQID = ALT_DM20_YAMATOS_GARURUMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_YAMATOS_GARURUMON_FQID_LEN = sizeof(ALT_DM20_YAMATOS_GARURUMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_YAMATOS_GARURUMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Yamatos Garurumon";
    inline static constexpr const char* ALT_DM20_YAMATOS_GARURUMON_FQNAME = ALT_DM20_YAMATOS_GARURUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_YAMATOS_GARURUMON_FQNAME_LEN = sizeof(ALT_DM20_YAMATOS_GARURUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_YAMATOS_METAL_GARURUMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:yamatos_metal_garurumon";
    inline static constexpr const char* ALT_DM20_YAMATOS_METAL_GARURUMON_FQID = ALT_DM20_YAMATOS_METAL_GARURUMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_YAMATOS_METAL_GARURUMON_FQID_LEN = sizeof(ALT_DM20_YAMATOS_METAL_GARURUMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_YAMATOS_METAL_GARURUMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Yamatos Metal Garurumon";
    inline static constexpr const char* ALT_DM20_YAMATOS_METAL_GARURUMON_FQNAME = ALT_DM20_YAMATOS_METAL_GARURUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_YAMATOS_METAL_GARURUMON_FQNAME_LEN = sizeof(ALT_DM20_YAMATOS_METAL_GARURUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_YAMATOS_WERE_GARURUMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:yamatos_were_garurumon";
    inline static constexpr const char* ALT_DM20_YAMATOS_WERE_GARURUMON_FQID = ALT_DM20_YAMATOS_WERE_GARURUMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_YAMATOS_WERE_GARURUMON_FQID_LEN = sizeof(ALT_DM20_YAMATOS_WERE_GARURUMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_YAMATOS_WERE_GARURUMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Yamatos Were Garurumon";
    inline static constexpr const char* ALT_DM20_YAMATOS_WERE_GARURUMON_FQNAME = ALT_DM20_YAMATOS_WERE_GARURUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_YAMATOS_WERE_GARURUMON_FQNAME_LEN = sizeof(ALT_DM20_YAMATOS_WERE_GARURUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_YUKIDARUMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:yukidarumon";
    inline static constexpr const char* ALT_DM20_YUKIDARUMON_FQID = ALT_DM20_YUKIDARUMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_YUKIDARUMON_FQID_LEN = sizeof(ALT_DM20_YUKIDARUMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_YUKIDARUMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Yukidarumon";
    inline static constexpr const char* ALT_DM20_YUKIDARUMON_FQNAME = ALT_DM20_YUKIDARUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_YUKIDARUMON_FQNAME_LEN = sizeof(ALT_DM20_YUKIDARUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_YUKIMIBOTAMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:yukimibotamon";
    inline static constexpr const char* ALT_DM20_YUKIMIBOTAMON_FQID = ALT_DM20_YUKIMIBOTAMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_YUKIMIBOTAMON_FQID_LEN = sizeof(ALT_DM20_YUKIMIBOTAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_YUKIMIBOTAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Yukimibotamon";
    inline static constexpr const char* ALT_DM20_YUKIMIBOTAMON_FQNAME = ALT_DM20_YUKIMIBOTAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_YUKIMIBOTAMON_FQNAME_LEN = sizeof(ALT_DM20_YUKIMIBOTAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_YURAMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:yuramon";
    inline static constexpr const char* ALT_DM20_YURAMON_FQID = ALT_DM20_YURAMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_YURAMON_FQID_LEN = sizeof(ALT_DM20_YURAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_YURAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Yuramon";
    inline static constexpr const char* ALT_DM20_YURAMON_FQNAME = ALT_DM20_YURAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_YURAMON_FQNAME_LEN = sizeof(ALT_DM20_YURAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_ZUBAEAGERMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:zubaeagermon";
    inline static constexpr const char* ALT_DM20_ZUBAEAGERMON_FQID = ALT_DM20_ZUBAEAGERMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_ZUBAEAGERMON_FQID_LEN = sizeof(ALT_DM20_ZUBAEAGERMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_ZUBAEAGERMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Zubaeagermon";
    inline static constexpr const char* ALT_DM20_ZUBAEAGERMON_FQNAME = ALT_DM20_ZUBAEAGERMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_ZUBAEAGERMON_FQNAME_LEN = sizeof(ALT_DM20_ZUBAEAGERMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_ZUBAMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:zubamon";
    inline static constexpr const char* ALT_DM20_ZUBAMON_FQID = ALT_DM20_ZUBAMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_ZUBAMON_FQID_LEN = sizeof(ALT_DM20_ZUBAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_ZUBAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Zubamon";
    inline static constexpr const char* ALT_DM20_ZUBAMON_FQNAME = ALT_DM20_ZUBAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_ZUBAMON_FQNAME_LEN = sizeof(ALT_DM20_ZUBAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DM20_ZURUMON_FQID_ARR[] CONFIG_STRING_SECTION = "dm:zurumon";
    inline static constexpr const char* ALT_DM20_ZURUMON_FQID = ALT_DM20_ZURUMON_FQID_ARR;
    inline static constexpr size_t ALT_DM20_ZURUMON_FQID_LEN = sizeof(ALT_DM20_ZURUMON_FQID_ARR)-1;
    inline static constexpr char ALT_DM20_ZURUMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "dm:Zurumon";
    inline static constexpr const char* ALT_DM20_ZURUMON_FQNAME = ALT_DM20_ZURUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DM20_ZURUMON_FQNAME_LEN = sizeof(ALT_DM20_ZURUMON_FQNAME_ARR)-1;

    struct dm20_animation_table_entry_t {
        config_animation_entry_t normal;
        struct {
            const char *fqid{""};
            const char *fqname{""};
        } alt;
    };
    static const dm20_animation_table_entry_t dm20_animation_table[] = {
        { { DM20_AEGISDRAMON_NAME, DM20_AEGISDRAMON_ID, DM20_AEGISDRAMON_FQID, DM20_AEGISDRAMON_FQNAME, DM20_AEGISDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_AEGISDRAMON_FQID, ALT_DM20_AEGISDRAMON_FQNAME } },  // Aegisdramon
        { { DM20_AGUMON_NAME, DM20_AGUMON_ID, DM20_AGUMON_FQID, DM20_AGUMON_FQNAME, DM20_AGUMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_AGUMON_FQID, ALT_DM20_AGUMON_FQNAME } },  // Agumon
        { { DM20_AIRDRAMON_NAME, DM20_AIRDRAMON_ID, DM20_AIRDRAMON_FQID, DM20_AIRDRAMON_FQNAME, DM20_AIRDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_AIRDRAMON_FQID, ALT_DM20_AIRDRAMON_FQNAME } },  // Airdramon
        { { DM20_ALPHAMON_NAME, DM20_ALPHAMON_ID, DM20_ALPHAMON_FQID, DM20_ALPHAMON_FQNAME, DM20_ALPHAMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_ALPHAMON_FQID, ALT_DM20_ALPHAMON_FQNAME } },  // Alphamon
        { { DM20_ANDROMON_NAME, DM20_ANDROMON_ID, DM20_ANDROMON_FQID, DM20_ANDROMON_FQNAME, DM20_ANDROMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_ANDROMON_FQID, ALT_DM20_ANDROMON_FQNAME } },  // Andromon
        { { DM20_ANGEMON_NAME, DM20_ANGEMON_ID, DM20_ANGEMON_FQID, DM20_ANGEMON_FQNAME, DM20_ANGEMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_ANGEMON_FQID, ALT_DM20_ANGEMON_FQNAME } },  // Angemon
        { { DM20_APOLLOMON_NAME, DM20_APOLLOMON_ID, DM20_APOLLOMON_FQID, DM20_APOLLOMON_FQNAME, DM20_APOLLOMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_APOLLOMON_FQID, ALT_DM20_APOLLOMON_FQNAME } },  // Apollomon
        { { DM20_BABYDMON_NAME, DM20_BABYDMON_ID, DM20_BABYDMON_FQID, DM20_BABYDMON_FQNAME, DM20_BABYDMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_BABYDMON_FQID, ALT_DM20_BABYDMON_FQNAME } },  // Babydmon
        { { DM20_BAKEMON_NAME, DM20_BAKEMON_ID, DM20_BAKEMON_FQID, DM20_BAKEMON_FQNAME, DM20_BAKEMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_BAKEMON_FQID, ALT_DM20_BAKEMON_FQNAME } },  // Bakemon
        { { DM20_BANCHO_MAMEMON_NAME, DM20_BANCHO_MAMEMON_ID, DM20_BANCHO_MAMEMON_FQID, DM20_BANCHO_MAMEMON_FQNAME, DM20_BANCHO_MAMEMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_BANCHO_MAMEMON_FQID, ALT_DM20_BANCHO_MAMEMON_FQNAME } },  // Bancho Mamemon
        { { DM20_BAO_HACKMON_NAME, DM20_BAO_HACKMON_ID, DM20_BAO_HACKMON_FQID, DM20_BAO_HACKMON_FQNAME, DM20_BAO_HACKMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_BAO_HACKMON_FQID, ALT_DM20_BAO_HACKMON_FQNAME } },  // Bao Hackmon
        { { DM20_BETAMON_NAME, DM20_BETAMON_ID, DM20_BETAMON_FQID, DM20_BETAMON_FQNAME, DM20_BETAMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_BETAMON_FQID, ALT_DM20_BETAMON_FQNAME } },  // Betamon
        { { DM20_BIRDRAMON_NAME, DM20_BIRDRAMON_ID, DM20_BIRDRAMON_FQID, DM20_BIRDRAMON_FQNAME, DM20_BIRDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_BIRDRAMON_FQID, ALT_DM20_BIRDRAMON_FQNAME } },  // Birdramon
        { { DM20_BLITZ_GREYMON_NAME, DM20_BLITZ_GREYMON_ID, DM20_BLITZ_GREYMON_FQID, DM20_BLITZ_GREYMON_FQNAME, DM20_BLITZ_GREYMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_BLITZ_GREYMON_FQID, ALT_DM20_BLITZ_GREYMON_FQNAME } },  // Blitz Greymon
        { { DM20_BOTAMON_NAME, DM20_BOTAMON_ID, DM20_BOTAMON_FQID, DM20_BOTAMON_FQNAME, DM20_BOTAMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_BOTAMON_FQID, ALT_DM20_BOTAMON_FQNAME } },  // Botamon
        { { DM20_BREAKDRAMON_NAME, DM20_BREAKDRAMON_ID, DM20_BREAKDRAMON_FQID, DM20_BREAKDRAMON_FQNAME, DM20_BREAKDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_BREAKDRAMON_FQID, ALT_DM20_BREAKDRAMON_FQNAME } },  // Breakdramon
        { { DM20_CENTALMON_NAME, DM20_CENTALMON_ID, DM20_CENTALMON_FQID, DM20_CENTALMON_FQNAME, DM20_CENTALMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_CENTALMON_FQID, ALT_DM20_CENTALMON_FQNAME } },  // Centalmon
        { { DM20_COCKATRIMON_NAME, DM20_COCKATRIMON_ID, DM20_COCKATRIMON_FQID, DM20_COCKATRIMON_FQNAME, DM20_COCKATRIMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_COCKATRIMON_FQID, ALT_DM20_COCKATRIMON_FQNAME } },  // Cockatrimon
        { { DM20_COELAMON_NAME, DM20_COELAMON_ID, DM20_COELAMON_FQID, DM20_COELAMON_FQNAME, DM20_COELAMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_COELAMON_FQID, ALT_DM20_COELAMON_FQNAME } },  // Coelamon
        { { DM20_COREDRAMON_BLUE_NAME, DM20_COREDRAMON_BLUE_ID, DM20_COREDRAMON_BLUE_FQID, DM20_COREDRAMON_BLUE_FQNAME, DM20_COREDRAMON_BLUE_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_COREDRAMON_BLUE_FQID, ALT_DM20_COREDRAMON_BLUE_FQNAME } },  // Coredramon (Blue)
        { { DM20_COREDRAMON_GREEN_NAME, DM20_COREDRAMON_GREEN_ID, DM20_COREDRAMON_GREEN_FQID, DM20_COREDRAMON_GREEN_FQNAME, DM20_COREDRAMON_GREEN_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_COREDRAMON_GREEN_FQID, ALT_DM20_COREDRAMON_GREEN_FQNAME } },  // Coredramon (Green)
        { { DM20_CORONAMON_NAME, DM20_CORONAMON_ID, DM20_CORONAMON_FQID, DM20_CORONAMON_FQNAME, DM20_CORONAMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_CORONAMON_FQID, ALT_DM20_CORONAMON_FQNAME } },  // Coronamon
        { { DM20_CRESCEMON_NAME, DM20_CRESCEMON_ID, DM20_CRESCEMON_FQID, DM20_CRESCEMON_FQNAME, DM20_CRESCEMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_CRESCEMON_FQID, ALT_DM20_CRESCEMON_FQNAME } },  // Crescemon
        { { DM20_CRES_GARURUMON_NAME, DM20_CRES_GARURUMON_ID, DM20_CRES_GARURUMON_FQID, DM20_CRES_GARURUMON_FQNAME, DM20_CRES_GARURUMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_CRES_GARURUMON_FQID, ALT_DM20_CRES_GARURUMON_FQNAME } },  // Cres Garurumon
        { { DM20_CYCLOMON_NAME, DM20_CYCLOMON_ID, DM20_CYCLOMON_FQID, DM20_CYCLOMON_FQNAME, DM20_CYCLOMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_CYCLOMON_FQID, ALT_DM20_CYCLOMON_FQNAME } },  // Cyclomon
        { { DM20_DARK_TYRANOMON_NAME, DM20_DARK_TYRANOMON_ID, DM20_DARK_TYRANOMON_FQID, DM20_DARK_TYRANOMON_FQNAME, DM20_DARK_TYRANOMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_DARK_TYRANOMON_FQID, ALT_DM20_DARK_TYRANOMON_FQNAME } },  // Dark Tyranomon
        { { DM20_DELTAMON_NAME, DM20_DELTAMON_ID, DM20_DELTAMON_FQID, DM20_DELTAMON_FQNAME, DM20_DELTAMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_DELTAMON_FQID, ALT_DM20_DELTAMON_FQNAME } },  // Deltamon
        { { DM20_DEVIDRAMON_NAME, DM20_DEVIDRAMON_ID, DM20_DEVIDRAMON_FQID, DM20_DEVIDRAMON_FQNAME, DM20_DEVIDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_DEVIDRAMON_FQID, ALT_DM20_DEVIDRAMON_FQNAME } },  // Devidramon
        { { DM20_DEVIMON_NAME, DM20_DEVIMON_ID, DM20_DEVIMON_FQID, DM20_DEVIMON_FQNAME, DM20_DEVIMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_DEVIMON_FQID, ALT_DM20_DEVIMON_FQNAME } },  // Devimon
        { { DM20_DIANAMON_NAME, DM20_DIANAMON_ID, DM20_DIANAMON_FQID, DM20_DIANAMON_FQNAME, DM20_DIANAMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_DIANAMON_FQID, ALT_DM20_DIANAMON_FQNAME } },  // Dianamon
        { { DM20_DIGITAMAMON_NAME, DM20_DIGITAMAMON_ID, DM20_DIGITAMAMON_FQID, DM20_DIGITAMAMON_FQNAME, DM20_DIGITAMAMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_DIGITAMAMON_FQID, ALT_DM20_DIGITAMAMON_FQNAME } },  // Digitamamon
        { { DM20_DODOMON_NAME, DM20_DODOMON_ID, DM20_DODOMON_FQID, DM20_DODOMON_FQNAME, DM20_DODOMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_DODOMON_FQID, ALT_DM20_DODOMON_FQNAME } },  // Dodomon
        { { DM20_DORIMON_NAME, DM20_DORIMON_ID, DM20_DORIMON_FQID, DM20_DORIMON_FQNAME, DM20_DORIMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_DORIMON_FQID, ALT_DM20_DORIMON_FQNAME } },  // Dorimon
        { { DM20_DORUGAMON_NAME, DM20_DORUGAMON_ID, DM20_DORUGAMON_FQID, DM20_DORUGAMON_FQNAME, DM20_DORUGAMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_DORUGAMON_FQID, ALT_DM20_DORUGAMON_FQNAME } },  // DORUgamon
        { { DM20_DORUGUREMON_NAME, DM20_DORUGUREMON_ID, DM20_DORUGUREMON_FQID, DM20_DORUGUREMON_FQNAME, DM20_DORUGUREMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_DORUGUREMON_FQID, ALT_DM20_DORUGUREMON_FQNAME } },  // DORUguremon
        { { DM20_DORUMON_NAME, DM20_DORUMON_ID, DM20_DORUMON_FQID, DM20_DORUMON_FQNAME, DM20_DORUMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_DORUMON_FQID, ALT_DM20_DORUMON_FQNAME } },  // DORUmon
        { { DM20_DRACOMON_NAME, DM20_DRACOMON_ID, DM20_DRACOMON_FQID, DM20_DRACOMON_FQNAME, DM20_DRACOMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_DRACOMON_FQID, ALT_DM20_DRACOMON_FQNAME } },  // Dracomon
        { { DM20_DRIMOGEMON_NAME, DM20_DRIMOGEMON_ID, DM20_DRIMOGEMON_FQID, DM20_DRIMOGEMON_FQNAME, DM20_DRIMOGEMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_DRIMOGEMON_FQID, ALT_DM20_DRIMOGEMON_FQNAME } },  // Drimogemon
        { { DM20_DURAMON_NAME, DM20_DURAMON_ID, DM20_DURAMON_FQID, DM20_DURAMON_FQNAME, DM20_DURAMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_DURAMON_FQID, ALT_DM20_DURAMON_FQNAME } },  // Duramon
        { { DM20_DURANDAMON_NAME, DM20_DURANDAMON_ID, DM20_DURANDAMON_FQID, DM20_DURANDAMON_FQNAME, DM20_DURANDAMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_DURANDAMON_FQID, ALT_DM20_DURANDAMON_FQNAME } },  // Durandamon
        { { DM20_ELECMON_NAME, DM20_ELECMON_ID, DM20_ELECMON_FQID, DM20_ELECMON_FQNAME, DM20_ELECMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_ELECMON_FQID, ALT_DM20_ELECMON_FQNAME } },  // Elecmon
        { { DM20_ETEMON_NAME, DM20_ETEMON_ID, DM20_ETEMON_FQID, DM20_ETEMON_FQNAME, DM20_ETEMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_ETEMON_FQID, ALT_DM20_ETEMON_FQNAME } },  // Etemon
        { { DM20_EXAMON_NAME, DM20_EXAMON_ID, DM20_EXAMON_FQID, DM20_EXAMON_FQNAME, DM20_EXAMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_EXAMON_FQID, ALT_DM20_EXAMON_FQNAME } },  // Examon
        { { DM20_EX_TYRANOMON_NAME, DM20_EX_TYRANOMON_ID, DM20_EX_TYRANOMON_FQID, DM20_EX_TYRANOMON_FQNAME, DM20_EX_TYRANOMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_EX_TYRANOMON_FQID, ALT_DM20_EX_TYRANOMON_FQNAME } },  // Ex-Tyranomon
        { { DM20_FIRAMON_NAME, DM20_FIRAMON_ID, DM20_FIRAMON_FQID, DM20_FIRAMON_FQNAME, DM20_FIRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_FIRAMON_FQID, ALT_DM20_FIRAMON_FQNAME } },  // Firamon
        { { DM20_FLAREMON_NAME, DM20_FLAREMON_ID, DM20_FLAREMON_FQID, DM20_FLAREMON_FQNAME, DM20_FLAREMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_FLAREMON_FQID, ALT_DM20_FLAREMON_FQNAME } },  // Flaremon
        { { DM20_FLYMON_NAME, DM20_FLYMON_ID, DM20_FLYMON_FQID, DM20_FLYMON_FQNAME, DM20_FLYMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_FLYMON_FQID, ALT_DM20_FLYMON_FQNAME } },  // Flymon
        { { DM20_GABUMON_NAME, DM20_GABUMON_ID, DM20_GABUMON_FQID, DM20_GABUMON_FQNAME, DM20_GABUMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_GABUMON_FQID, ALT_DM20_GABUMON_FQNAME } },  // Gabumon
        { { DM20_GARURUMON_NAME, DM20_GARURUMON_ID, DM20_GARURUMON_FQID, DM20_GARURUMON_FQNAME, DM20_GARURUMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_GARURUMON_FQID, ALT_DM20_GARURUMON_FQNAME } },  // Garurumon
        { { DM20_GAZIMON_NAME, DM20_GAZIMON_ID, DM20_GAZIMON_FQID, DM20_GAZIMON_FQNAME, DM20_GAZIMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_GAZIMON_FQID, ALT_DM20_GAZIMON_FQNAME } },  // Gazimon
        { { DM20_GIROMON_NAME, DM20_GIROMON_ID, DM20_GIROMON_FQID, DM20_GIROMON_FQNAME, DM20_GIROMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_GIROMON_FQID, ALT_DM20_GIROMON_FQNAME } },  // Giromon
        { { DM20_GIZAMON_NAME, DM20_GIZAMON_ID, DM20_GIZAMON_FQID, DM20_GIZAMON_FQNAME, DM20_GIZAMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_GIZAMON_FQID, ALT_DM20_GIZAMON_FQNAME } },  // Gizamon
        { { DM20_GRACE_NOVAMON_NAME, DM20_GRACE_NOVAMON_ID, DM20_GRACE_NOVAMON_FQID, DM20_GRACE_NOVAMON_FQNAME, DM20_GRACE_NOVAMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_GRACE_NOVAMON_FQID, ALT_DM20_GRACE_NOVAMON_FQNAME } },  // Grace Novamon
        { { DM20_GREYMON_NAME, DM20_GREYMON_ID, DM20_GREYMON_FQID, DM20_GREYMON_FQNAME, DM20_GREYMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_GREYMON_FQID, ALT_DM20_GREYMON_FQNAME } },  // Greymon
        { { DM20_GROUNDRAMON_NAME, DM20_GROUNDRAMON_ID, DM20_GROUNDRAMON_FQID, DM20_GROUNDRAMON_FQNAME, DM20_GROUNDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_GROUNDRAMON_FQID, ALT_DM20_GROUNDRAMON_FQNAME } },  // Groundramon
        { { DM20_HACKMON_NAME, DM20_HACKMON_ID, DM20_HACKMON_FQID, DM20_HACKMON_FQNAME, DM20_HACKMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_HACKMON_FQID, ALT_DM20_HACKMON_FQNAME } },  // Hackmon
        { { DM20_HI_ANDROMON_NAME, DM20_HI_ANDROMON_ID, DM20_HI_ANDROMON_FQID, DM20_HI_ANDROMON_FQNAME, DM20_HI_ANDROMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_HI_ANDROMON_FQID, ALT_DM20_HI_ANDROMON_FQNAME } },  // Hi Andromon
        { { DM20_JESMON_NAME, DM20_JESMON_ID, DM20_JESMON_FQID, DM20_JESMON_FQNAME, DM20_JESMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_JESMON_FQID, ALT_DM20_JESMON_FQNAME } },  // Jesmon
        { { DM20_KABUTERIMON_NAME, DM20_KABUTERIMON_ID, DM20_KABUTERIMON_FQID, DM20_KABUTERIMON_FQNAME, DM20_KABUTERIMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_KABUTERIMON_FQID, ALT_DM20_KABUTERIMON_FQNAME } },  // Kabuterimon
        { { DM20_KING_ETEMON_NAME, DM20_KING_ETEMON_ID, DM20_KING_ETEMON_FQID, DM20_KING_ETEMON_FQNAME, DM20_KING_ETEMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_KING_ETEMON_FQID, ALT_DM20_KING_ETEMON_FQNAME } },  // King Etemon
        { { DM20_KOROMON_NAME, DM20_KOROMON_ID, DM20_KOROMON_FQID, DM20_KOROMON_FQNAME, DM20_KOROMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_KOROMON_FQID, ALT_DM20_KOROMON_FQNAME } },  // Koromon
        { { DM20_KUNEMON_NAME, DM20_KUNEMON_ID, DM20_KUNEMON_FQID, DM20_KUNEMON_FQNAME, DM20_KUNEMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_KUNEMON_FQID, ALT_DM20_KUNEMON_FQNAME } },  // Kunemon
        { { DM20_KUWAGAMON_NAME, DM20_KUWAGAMON_ID, DM20_KUWAGAMON_FQID, DM20_KUWAGAMON_FQNAME, DM20_KUWAGAMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_KUWAGAMON_FQID, ALT_DM20_KUWAGAMON_FQNAME } },  // Kuwagamon
        { { DM20_LEKISMON_NAME, DM20_LEKISMON_ID, DM20_LEKISMON_FQID, DM20_LEKISMON_FQNAME, DM20_LEKISMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_LEKISMON_FQID, ALT_DM20_LEKISMON_FQNAME } },  // Lekismon
        { { DM20_LEOMON_NAME, DM20_LEOMON_ID, DM20_LEOMON_FQID, DM20_LEOMON_FQNAME, DM20_LEOMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_LEOMON_FQID, ALT_DM20_LEOMON_FQNAME } },  // Leomon
        { { DM20_LUNAMON_NAME, DM20_LUNAMON_ID, DM20_LUNAMON_FQID, DM20_LUNAMON_FQNAME, DM20_LUNAMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_LUNAMON_FQID, ALT_DM20_LUNAMON_FQNAME } },  // Lunamon
        { { DM20_MAMEMON_NAME, DM20_MAMEMON_ID, DM20_MAMEMON_FQID, DM20_MAMEMON_FQNAME, DM20_MAMEMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_MAMEMON_FQID, ALT_DM20_MAMEMON_FQNAME } },  // Mamemon
        { { DM20_MEGADRAMON_NAME, DM20_MEGADRAMON_ID, DM20_MEGADRAMON_FQID, DM20_MEGADRAMON_FQNAME, DM20_MEGADRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_MEGADRAMON_FQID, ALT_DM20_MEGADRAMON_FQNAME } },  // Megadramon
        { { DM20_MEICOOMON_NAME, DM20_MEICOOMON_ID, DM20_MEICOOMON_FQID, DM20_MEICOOMON_FQNAME, DM20_MEICOOMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_MEICOOMON_FQID, ALT_DM20_MEICOOMON_FQNAME } },  // Meicoomon
        { { DM20_MEICRACKMON_NAME, DM20_MEICRACKMON_ID, DM20_MEICRACKMON_FQID, DM20_MEICRACKMON_FQNAME, DM20_MEICRACKMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_MEICRACKMON_FQID, ALT_DM20_MEICRACKMON_FQNAME } },  // Meicrackmon
        { { DM20_MERAMON_NAME, DM20_MERAMON_ID, DM20_MERAMON_FQID, DM20_MERAMON_FQNAME, DM20_MERAMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_MERAMON_FQID, ALT_DM20_MERAMON_FQNAME } },  // Meramon
        { { DM20_METAL_GREYMON_NAME, DM20_METAL_GREYMON_ID, DM20_METAL_GREYMON_FQID, DM20_METAL_GREYMON_FQNAME, DM20_METAL_GREYMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_METAL_GREYMON_FQID, ALT_DM20_METAL_GREYMON_FQNAME } },  // Metal Greymon
        { { DM20_METAL_MAMEMON_NAME, DM20_METAL_MAMEMON_ID, DM20_METAL_MAMEMON_FQID, DM20_METAL_MAMEMON_FQNAME, DM20_METAL_MAMEMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_METAL_MAMEMON_FQID, ALT_DM20_METAL_MAMEMON_FQNAME } },  // Metal Mamemon
        { { DM20_METAL_TYRANOMON_NAME, DM20_METAL_TYRANOMON_ID, DM20_METAL_TYRANOMON_FQID, DM20_METAL_TYRANOMON_FQNAME, DM20_METAL_TYRANOMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_METAL_TYRANOMON_FQID, ALT_DM20_METAL_TYRANOMON_FQNAME } },  // Metal Tyranomon
        { { DM20_MOJYAMON_NAME, DM20_MOJYAMON_ID, DM20_MOJYAMON_FQID, DM20_MOJYAMON_FQNAME, DM20_MOJYAMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_MOJYAMON_FQID, ALT_DM20_MOJYAMON_FQNAME } },  // Mojyamon
        { { DM20_MONOCHROMON_NAME, DM20_MONOCHROMON_ID, DM20_MONOCHROMON_FQID, DM20_MONOCHROMON_FQNAME, DM20_MONOCHROMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_MONOCHROMON_FQID, ALT_DM20_MONOCHROMON_FQNAME } },  // Monochromon
        { { DM20_MONZAEMON_NAME, DM20_MONZAEMON_ID, DM20_MONZAEMON_FQID, DM20_MONZAEMON_FQNAME, DM20_MONZAEMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_MONZAEMON_FQID, ALT_DM20_MONZAEMON_FQNAME } },  // Monzaemon
        { { DM20_MUGENDRAMON_NAME, DM20_MUGENDRAMON_ID, DM20_MUGENDRAMON_FQID, DM20_MUGENDRAMON_FQNAME, DM20_MUGENDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_MUGENDRAMON_FQID, ALT_DM20_MUGENDRAMON_FQNAME } },  // Mugendramon
        { { DM20_NANIMON_NAME, DM20_NANIMON_ID, DM20_NANIMON_FQID, DM20_NANIMON_FQNAME, DM20_NANIMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_NANIMON_FQID, ALT_DM20_NANIMON_FQNAME } },  // Nanimon
        { { DM20_NANOMON_NAME, DM20_NANOMON_ID, DM20_NANOMON_FQID, DM20_NANOMON_FQNAME, DM20_NANOMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_NANOMON_FQID, ALT_DM20_NANOMON_FQNAME } },  // Nanomon
        { { DM20_NUMEMON_NAME, DM20_NUMEMON_ID, DM20_NUMEMON_FQID, DM20_NUMEMON_FQNAME, DM20_NUMEMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_NUMEMON_FQID, ALT_DM20_NUMEMON_FQNAME } },  // Numemon
        { { DM20_NYAROMON_NAME, DM20_NYAROMON_ID, DM20_NYAROMON_FQID, DM20_NYAROMON_FQNAME, DM20_NYAROMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_NYAROMON_FQID, ALT_DM20_NYAROMON_FQNAME } },  // Nyaromon
        { { DM20_OGREMON_NAME, DM20_OGREMON_ID, DM20_OGREMON_FQID, DM20_OGREMON_FQNAME, DM20_OGREMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_OGREMON_FQID, ALT_DM20_OGREMON_FQNAME } },  // Ogremon
        { { DM20_OMEGAMON_ALTER_S_NAME, DM20_OMEGAMON_ALTER_S_ID, DM20_OMEGAMON_ALTER_S_FQID, DM20_OMEGAMON_ALTER_S_FQNAME, DM20_OMEGAMON_ALTER_S_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_OMEGAMON_ALTER_S_FQID, ALT_DM20_OMEGAMON_ALTER_S_FQNAME } },  // Omegamon Alter S
        { { DM20_OMEGAMON_NAME, DM20_OMEGAMON_ID, DM20_OMEGAMON_FQID, DM20_OMEGAMON_FQNAME, DM20_OMEGAMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_OMEGAMON_FQID, ALT_DM20_OMEGAMON_FQNAME } },  // Omegamon
        { { DM20_PAGUMON_NAME, DM20_PAGUMON_ID, DM20_PAGUMON_FQID, DM20_PAGUMON_FQNAME, DM20_PAGUMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_PAGUMON_FQID, ALT_DM20_PAGUMON_FQNAME } },  // Pagumon
        { { DM20_PALMON_NAME, DM20_PALMON_ID, DM20_PALMON_FQID, DM20_PALMON_FQNAME, DM20_PALMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_PALMON_FQID, ALT_DM20_PALMON_FQNAME } },  // Palmon
        { { DM20_PATAMON_NAME, DM20_PATAMON_ID, DM20_PATAMON_FQID, DM20_PATAMON_FQNAME, DM20_PATAMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_PATAMON_FQID, ALT_DM20_PATAMON_FQNAME } },  // Patamon
        { { DM20_PETITMON_NAME, DM20_PETITMON_ID, DM20_PETITMON_FQID, DM20_PETITMON_FQNAME, DM20_PETITMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_PETITMON_FQID, ALT_DM20_PETITMON_FQNAME } },  // Petitmon
        { { DM20_PICCOLOMON_NAME, DM20_PICCOLOMON_ID, DM20_PICCOLOMON_FQID, DM20_PICCOLOMON_FQNAME, DM20_PICCOLOMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_PICCOLOMON_FQID, ALT_DM20_PICCOLOMON_FQNAME } },  // Piccolomon
        { { DM20_PINOCHIMON_NAME, DM20_PINOCHIMON_ID, DM20_PINOCHIMON_FQID, DM20_PINOCHIMON_FQNAME, DM20_PINOCHIMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_PINOCHIMON_FQID, ALT_DM20_PINOCHIMON_FQNAME } },  // Pinochimon
        { { DM20_PITCHMON_NAME, DM20_PITCHMON_ID, DM20_PITCHMON_FQID, DM20_PITCHMON_FQNAME, DM20_PITCHMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_PITCHMON_FQID, ALT_DM20_PITCHMON_FQNAME } },  // Pitchmon
        { { DM20_PIYOMON_NAME, DM20_PIYOMON_ID, DM20_PIYOMON_FQID, DM20_PIYOMON_FQNAME, DM20_PIYOMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_PIYOMON_FQID, ALT_DM20_PIYOMON_FQNAME } },  // Piyomon
        { { DM20_PLOTMON_NAME, DM20_PLOTMON_ID, DM20_PLOTMON_FQID, DM20_PLOTMON_FQNAME, DM20_PLOTMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_PLOTMON_FQID, ALT_DM20_PLOTMON_FQNAME } },  // Plotmon
        { { DM20_POYOMON_NAME, DM20_POYOMON_ID, DM20_POYOMON_FQID, DM20_POYOMON_FQNAME, DM20_POYOMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_POYOMON_FQID, ALT_DM20_POYOMON_FQNAME } },  // Poyomon
        { { DM20_PUKAMON_NAME, DM20_PUKAMON_ID, DM20_PUKAMON_FQID, DM20_PUKAMON_FQNAME, DM20_PUKAMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_PUKAMON_FQID, ALT_DM20_PUKAMON_FQNAME } },  // Pukamon
        { { DM20_PUNIMON_NAME, DM20_PUNIMON_ID, DM20_PUNIMON_FQID, DM20_PUNIMON_FQNAME, DM20_PUNIMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_PUNIMON_FQID, ALT_DM20_PUNIMON_FQNAME } },  // Punimon
        { { DM20_RAREMON_NAME, DM20_RAREMON_ID, DM20_RAREMON_FQID, DM20_RAREMON_FQNAME, DM20_RAREMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_RAREMON_FQID, ALT_DM20_RAREMON_FQNAME } },  // Raremon
        { { DM20_RASIELMON_NAME, DM20_RASIELMON_ID, DM20_RASIELMON_FQID, DM20_RASIELMON_FQNAME, DM20_RASIELMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_RASIELMON_FQID, ALT_DM20_RASIELMON_FQNAME } },  // Rasielmon
        { { DM20_RUST_TYRANOMON_NAME, DM20_RUST_TYRANOMON_ID, DM20_RUST_TYRANOMON_FQID, DM20_RUST_TYRANOMON_FQNAME, DM20_RUST_TYRANOMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_RUST_TYRANOMON_FQID, ALT_DM20_RUST_TYRANOMON_FQNAME } },  // Rust Tyranomon
        { { DM20_SAKUMON_NAME, DM20_SAKUMON_ID, DM20_SAKUMON_FQID, DM20_SAKUMON_FQNAME, DM20_SAKUMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_SAKUMON_FQID, ALT_DM20_SAKUMON_FQNAME } },  // Sakumon
        { { DM20_SAKUTTOMON_NAME, DM20_SAKUTTOMON_ID, DM20_SAKUTTOMON_FQID, DM20_SAKUTTOMON_FQNAME, DM20_SAKUTTOMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_SAKUTTOMON_FQID, ALT_DM20_SAKUTTOMON_FQNAME } },  // Sakuttomon
        { { DM20_SAVIOR_HACKMON_NAME, DM20_SAVIOR_HACKMON_ID, DM20_SAVIOR_HACKMON_FQID, DM20_SAVIOR_HACKMON_FQNAME, DM20_SAVIOR_HACKMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_SAVIOR_HACKMON_FQID, ALT_DM20_SAVIOR_HACKMON_FQNAME } },  // Savior Hackmon
        { { DM20_SCUMON_NAME, DM20_SCUMON_ID, DM20_SCUMON_FQID, DM20_SCUMON_FQNAME, DM20_SCUMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_SCUMON_FQID, ALT_DM20_SCUMON_FQNAME } },  // Scumon
        { { DM20_SEADRAMON_NAME, DM20_SEADRAMON_ID, DM20_SEADRAMON_FQID, DM20_SEADRAMON_FQNAME, DM20_SEADRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_SEADRAMON_FQID, ALT_DM20_SEADRAMON_FQNAME } },  // Seadramon
        { { DM20_SHELLMON_NAME, DM20_SHELLMON_ID, DM20_SHELLMON_FQID, DM20_SHELLMON_FQNAME, DM20_SHELLMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_SHELLMON_FQID, ALT_DM20_SHELLMON_FQNAME } },  // Shellmon
        { { DM20_SKULL_GREYMON_NAME, DM20_SKULL_GREYMON_ID, DM20_SKULL_GREYMON_FQID, DM20_SKULL_GREYMON_FQNAME, DM20_SKULL_GREYMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_SKULL_GREYMON_FQID, ALT_DM20_SKULL_GREYMON_FQNAME } },  // Skull Greymon
        { { DM20_SKULL_MAMMON_NAME, DM20_SKULL_MAMMON_ID, DM20_SKULL_MAMMON_FQID, DM20_SKULL_MAMMON_FQNAME, DM20_SKULL_MAMMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_SKULL_MAMMON_FQID, ALT_DM20_SKULL_MAMMON_FQNAME } },  // Skull Mammon
        { { DM20_SLAYERDRAMON_NAME, DM20_SLAYERDRAMON_ID, DM20_SLAYERDRAMON_FQID, DM20_SLAYERDRAMON_FQNAME, DM20_SLAYERDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_SLAYERDRAMON_FQID, ALT_DM20_SLAYERDRAMON_FQNAME } },  // Slayerdramon
        { { DM20_TAICHIS_AGUMON_NAME, DM20_TAICHIS_AGUMON_ID, DM20_TAICHIS_AGUMON_FQID, DM20_TAICHIS_AGUMON_FQNAME, DM20_TAICHIS_AGUMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_TAICHIS_AGUMON_FQID, ALT_DM20_TAICHIS_AGUMON_FQNAME } },  // Taichis Agumon
        { { DM20_TAICHIS_GREYMON_NAME, DM20_TAICHIS_GREYMON_ID, DM20_TAICHIS_GREYMON_FQID, DM20_TAICHIS_GREYMON_FQNAME, DM20_TAICHIS_GREYMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_TAICHIS_GREYMON_FQID, ALT_DM20_TAICHIS_GREYMON_FQNAME } },  // Taichis Greymon
        { { DM20_TAICHIS_METAL_GREYMON_NAME, DM20_TAICHIS_METAL_GREYMON_ID, DM20_TAICHIS_METAL_GREYMON_FQID, DM20_TAICHIS_METAL_GREYMON_FQNAME, DM20_TAICHIS_METAL_GREYMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_TAICHIS_METAL_GREYMON_FQID, ALT_DM20_TAICHIS_METAL_GREYMON_FQNAME } },  // Taichis Metal Greymon
        { { DM20_TAICHIS_WAR_GREYMON_NAME, DM20_TAICHIS_WAR_GREYMON_ID, DM20_TAICHIS_WAR_GREYMON_FQID, DM20_TAICHIS_WAR_GREYMON_FQNAME, DM20_TAICHIS_WAR_GREYMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_TAICHIS_WAR_GREYMON_FQID, ALT_DM20_TAICHIS_WAR_GREYMON_FQNAME } },  // Taichis War Greymon
        { { DM20_TANEMON_NAME, DM20_TANEMON_ID, DM20_TANEMON_FQID, DM20_TANEMON_FQNAME, DM20_TANEMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_TANEMON_FQID, ALT_DM20_TANEMON_FQNAME } },  // Tanemon
        { { DM20_TITAMON_NAME, DM20_TITAMON_ID, DM20_TITAMON_FQID, DM20_TITAMON_FQNAME, DM20_TITAMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_TITAMON_FQID, ALT_DM20_TITAMON_FQNAME } },  // Titamon
        { { DM20_TOKOMON_NAME, DM20_TOKOMON_ID, DM20_TOKOMON_FQID, DM20_TOKOMON_FQNAME, DM20_TOKOMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_TOKOMON_FQID, ALT_DM20_TOKOMON_FQNAME } },  // Tokomon
        { { DM20_TUNOMON_NAME, DM20_TUNOMON_ID, DM20_TUNOMON_FQID, DM20_TUNOMON_FQNAME, DM20_TUNOMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_TUNOMON_FQID, ALT_DM20_TUNOMON_FQNAME } },  // Tunomon
        { { DM20_TUSKMON_NAME, DM20_TUSKMON_ID, DM20_TUSKMON_FQID, DM20_TUSKMON_FQNAME, DM20_TUSKMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_TUSKMON_FQID, ALT_DM20_TUSKMON_FQNAME } },  // Tuskmon
        { { DM20_TYRANOMON_NAME, DM20_TYRANOMON_ID, DM20_TYRANOMON_FQID, DM20_TYRANOMON_FQNAME, DM20_TYRANOMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_TYRANOMON_FQID, ALT_DM20_TYRANOMON_FQNAME } },  // Tyranomon
        { { DM20_UNIMON_NAME, DM20_UNIMON_ID, DM20_UNIMON_FQID, DM20_UNIMON_FQNAME, DM20_UNIMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_UNIMON_FQID, ALT_DM20_UNIMON_FQNAME } },  // Unimon
        { { DM20_VADEMON_NAME, DM20_VADEMON_ID, DM20_VADEMON_FQID, DM20_VADEMON_FQNAME, DM20_VADEMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_VADEMON_FQID, ALT_DM20_VADEMON_FQNAME } },  // Vademon
        { { DM20_VEGIMON_NAME, DM20_VEGIMON_ID, DM20_VEGIMON_FQID, DM20_VEGIMON_FQNAME, DM20_VEGIMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_VEGIMON_FQID, ALT_DM20_VEGIMON_FQNAME } },  // Vegimon
        { { DM20_WHAMON_NAME, DM20_WHAMON_ID, DM20_WHAMON_FQID, DM20_WHAMON_FQNAME, DM20_WHAMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_WHAMON_FQID, ALT_DM20_WHAMON_FQNAME } },  // Whamon
        { { DM20_WINGDRAMON_NAME, DM20_WINGDRAMON_ID, DM20_WINGDRAMON_FQID, DM20_WINGDRAMON_FQNAME, DM20_WINGDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_WINGDRAMON_FQID, ALT_DM20_WINGDRAMON_FQNAME } },  // Wingdramon
        { { DM20_YAMATOS_GABUMON_NAME, DM20_YAMATOS_GABUMON_ID, DM20_YAMATOS_GABUMON_FQID, DM20_YAMATOS_GABUMON_FQNAME, DM20_YAMATOS_GABUMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_YAMATOS_GABUMON_FQID, ALT_DM20_YAMATOS_GABUMON_FQNAME } },  // Yamatos Gabumon
        { { DM20_YAMATOS_GARURUMON_NAME, DM20_YAMATOS_GARURUMON_ID, DM20_YAMATOS_GARURUMON_FQID, DM20_YAMATOS_GARURUMON_FQNAME, DM20_YAMATOS_GARURUMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_YAMATOS_GARURUMON_FQID, ALT_DM20_YAMATOS_GARURUMON_FQNAME } },  // Yamatos Garurumon
        { { DM20_YAMATOS_METAL_GARURUMON_NAME, DM20_YAMATOS_METAL_GARURUMON_ID, DM20_YAMATOS_METAL_GARURUMON_FQID, DM20_YAMATOS_METAL_GARURUMON_FQNAME, DM20_YAMATOS_METAL_GARURUMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_YAMATOS_METAL_GARURUMON_FQID, ALT_DM20_YAMATOS_METAL_GARURUMON_FQNAME } },  // Yamatos Metal Garurumon
        { { DM20_YAMATOS_WERE_GARURUMON_NAME, DM20_YAMATOS_WERE_GARURUMON_ID, DM20_YAMATOS_WERE_GARURUMON_FQID, DM20_YAMATOS_WERE_GARURUMON_FQNAME, DM20_YAMATOS_WERE_GARURUMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_YAMATOS_WERE_GARURUMON_FQID, ALT_DM20_YAMATOS_WERE_GARURUMON_FQNAME } },  // Yamatos Were Garurumon
        { { DM20_YUKIDARUMON_NAME, DM20_YUKIDARUMON_ID, DM20_YUKIDARUMON_FQID, DM20_YUKIDARUMON_FQNAME, DM20_YUKIDARUMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_YUKIDARUMON_FQID, ALT_DM20_YUKIDARUMON_FQNAME } },  // Yukidarumon
        { { DM20_YUKIMIBOTAMON_NAME, DM20_YUKIMIBOTAMON_ID, DM20_YUKIMIBOTAMON_FQID, DM20_YUKIMIBOTAMON_FQNAME, DM20_YUKIMIBOTAMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_YUKIMIBOTAMON_FQID, ALT_DM20_YUKIMIBOTAMON_FQNAME } },  // Yukimibotamon
        { { DM20_YURAMON_NAME, DM20_YURAMON_ID, DM20_YURAMON_FQID, DM20_YURAMON_FQNAME, DM20_YURAMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_YURAMON_FQID, ALT_DM20_YURAMON_FQNAME } },  // Yuramon
        { { DM20_ZUBAEAGERMON_NAME, DM20_ZUBAEAGERMON_ID, DM20_ZUBAEAGERMON_FQID, DM20_ZUBAEAGERMON_FQNAME, DM20_ZUBAEAGERMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_ZUBAEAGERMON_FQID, ALT_DM20_ZUBAEAGERMON_FQNAME } },  // Zubaeagermon
        { { DM20_ZUBAMON_NAME, DM20_ZUBAMON_ID, DM20_ZUBAMON_FQID, DM20_ZUBAMON_FQNAME, DM20_ZUBAMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_ZUBAMON_FQID, ALT_DM20_ZUBAMON_FQNAME } },  // Zubamon
        { { DM20_ZURUMON_NAME, DM20_ZURUMON_ID, DM20_ZURUMON_FQID, DM20_ZURUMON_FQNAME, DM20_ZURUMON_ANIM_INDEX, config::config_animation_dm_set_t::dm20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_DM20_ZURUMON_FQID, ALT_DM20_ZURUMON_FQNAME } },  // Zurumon
        
    };
    static const config_animation_names_entry_t dm20_animation_names_table[] = {
        { DM20_AEGISDRAMON_NAME, DM20_AEGISDRAMON_NAME_LEN, DM20_AEGISDRAMON_ID, DM20_AEGISDRAMON_ID_LEN, DM20_AEGISDRAMON_FQID, DM20_AEGISDRAMON_FQID_LEN, DM20_AEGISDRAMON_FQNAME, DM20_AEGISDRAMON_FQNAME_LEN },
        { DM20_AEGISDRAMON_NAME, DM20_AEGISDRAMON_NAME_LEN, DM20_AEGISDRAMON_ID, DM20_AEGISDRAMON_ID_LEN, ALT_DM20_AEGISDRAMON_FQID, ALT_DM20_AEGISDRAMON_FQID_LEN, ALT_DM20_AEGISDRAMON_FQNAME, ALT_DM20_AEGISDRAMON_FQNAME_LEN },
        { DM20_AGUMON_NAME, DM20_AGUMON_NAME_LEN, DM20_AGUMON_ID, DM20_AGUMON_ID_LEN, DM20_AGUMON_FQID, DM20_AGUMON_FQID_LEN, DM20_AGUMON_FQNAME, DM20_AGUMON_FQNAME_LEN },
        { DM20_AGUMON_NAME, DM20_AGUMON_NAME_LEN, DM20_AGUMON_ID, DM20_AGUMON_ID_LEN, ALT_DM20_AGUMON_FQID, ALT_DM20_AGUMON_FQID_LEN, ALT_DM20_AGUMON_FQNAME, ALT_DM20_AGUMON_FQNAME_LEN },
        { DM20_AIRDRAMON_NAME, DM20_AIRDRAMON_NAME_LEN, DM20_AIRDRAMON_ID, DM20_AIRDRAMON_ID_LEN, DM20_AIRDRAMON_FQID, DM20_AIRDRAMON_FQID_LEN, DM20_AIRDRAMON_FQNAME, DM20_AIRDRAMON_FQNAME_LEN },
        { DM20_AIRDRAMON_NAME, DM20_AIRDRAMON_NAME_LEN, DM20_AIRDRAMON_ID, DM20_AIRDRAMON_ID_LEN, ALT_DM20_AIRDRAMON_FQID, ALT_DM20_AIRDRAMON_FQID_LEN, ALT_DM20_AIRDRAMON_FQNAME, ALT_DM20_AIRDRAMON_FQNAME_LEN },
        { DM20_ALPHAMON_NAME, DM20_ALPHAMON_NAME_LEN, DM20_ALPHAMON_ID, DM20_ALPHAMON_ID_LEN, DM20_ALPHAMON_FQID, DM20_ALPHAMON_FQID_LEN, DM20_ALPHAMON_FQNAME, DM20_ALPHAMON_FQNAME_LEN },
        { DM20_ALPHAMON_NAME, DM20_ALPHAMON_NAME_LEN, DM20_ALPHAMON_ID, DM20_ALPHAMON_ID_LEN, ALT_DM20_ALPHAMON_FQID, ALT_DM20_ALPHAMON_FQID_LEN, ALT_DM20_ALPHAMON_FQNAME, ALT_DM20_ALPHAMON_FQNAME_LEN },
        { DM20_ANDROMON_NAME, DM20_ANDROMON_NAME_LEN, DM20_ANDROMON_ID, DM20_ANDROMON_ID_LEN, DM20_ANDROMON_FQID, DM20_ANDROMON_FQID_LEN, DM20_ANDROMON_FQNAME, DM20_ANDROMON_FQNAME_LEN },
        { DM20_ANDROMON_NAME, DM20_ANDROMON_NAME_LEN, DM20_ANDROMON_ID, DM20_ANDROMON_ID_LEN, ALT_DM20_ANDROMON_FQID, ALT_DM20_ANDROMON_FQID_LEN, ALT_DM20_ANDROMON_FQNAME, ALT_DM20_ANDROMON_FQNAME_LEN },
        { DM20_ANGEMON_NAME, DM20_ANGEMON_NAME_LEN, DM20_ANGEMON_ID, DM20_ANGEMON_ID_LEN, DM20_ANGEMON_FQID, DM20_ANGEMON_FQID_LEN, DM20_ANGEMON_FQNAME, DM20_ANGEMON_FQNAME_LEN },
        { DM20_ANGEMON_NAME, DM20_ANGEMON_NAME_LEN, DM20_ANGEMON_ID, DM20_ANGEMON_ID_LEN, ALT_DM20_ANGEMON_FQID, ALT_DM20_ANGEMON_FQID_LEN, ALT_DM20_ANGEMON_FQNAME, ALT_DM20_ANGEMON_FQNAME_LEN },
        { DM20_APOLLOMON_NAME, DM20_APOLLOMON_NAME_LEN, DM20_APOLLOMON_ID, DM20_APOLLOMON_ID_LEN, DM20_APOLLOMON_FQID, DM20_APOLLOMON_FQID_LEN, DM20_APOLLOMON_FQNAME, DM20_APOLLOMON_FQNAME_LEN },
        { DM20_APOLLOMON_NAME, DM20_APOLLOMON_NAME_LEN, DM20_APOLLOMON_ID, DM20_APOLLOMON_ID_LEN, ALT_DM20_APOLLOMON_FQID, ALT_DM20_APOLLOMON_FQID_LEN, ALT_DM20_APOLLOMON_FQNAME, ALT_DM20_APOLLOMON_FQNAME_LEN },
        { DM20_BABYDMON_NAME, DM20_BABYDMON_NAME_LEN, DM20_BABYDMON_ID, DM20_BABYDMON_ID_LEN, DM20_BABYDMON_FQID, DM20_BABYDMON_FQID_LEN, DM20_BABYDMON_FQNAME, DM20_BABYDMON_FQNAME_LEN },
        { DM20_BABYDMON_NAME, DM20_BABYDMON_NAME_LEN, DM20_BABYDMON_ID, DM20_BABYDMON_ID_LEN, ALT_DM20_BABYDMON_FQID, ALT_DM20_BABYDMON_FQID_LEN, ALT_DM20_BABYDMON_FQNAME, ALT_DM20_BABYDMON_FQNAME_LEN },
        { DM20_BAKEMON_NAME, DM20_BAKEMON_NAME_LEN, DM20_BAKEMON_ID, DM20_BAKEMON_ID_LEN, DM20_BAKEMON_FQID, DM20_BAKEMON_FQID_LEN, DM20_BAKEMON_FQNAME, DM20_BAKEMON_FQNAME_LEN },
        { DM20_BAKEMON_NAME, DM20_BAKEMON_NAME_LEN, DM20_BAKEMON_ID, DM20_BAKEMON_ID_LEN, ALT_DM20_BAKEMON_FQID, ALT_DM20_BAKEMON_FQID_LEN, ALT_DM20_BAKEMON_FQNAME, ALT_DM20_BAKEMON_FQNAME_LEN },
        { DM20_BANCHO_MAMEMON_NAME, DM20_BANCHO_MAMEMON_NAME_LEN, DM20_BANCHO_MAMEMON_ID, DM20_BANCHO_MAMEMON_ID_LEN, DM20_BANCHO_MAMEMON_FQID, DM20_BANCHO_MAMEMON_FQID_LEN, DM20_BANCHO_MAMEMON_FQNAME, DM20_BANCHO_MAMEMON_FQNAME_LEN },
        { DM20_BANCHO_MAMEMON_NAME, DM20_BANCHO_MAMEMON_NAME_LEN, DM20_BANCHO_MAMEMON_ID, DM20_BANCHO_MAMEMON_ID_LEN, ALT_DM20_BANCHO_MAMEMON_FQID, ALT_DM20_BANCHO_MAMEMON_FQID_LEN, ALT_DM20_BANCHO_MAMEMON_FQNAME, ALT_DM20_BANCHO_MAMEMON_FQNAME_LEN },
        { DM20_BAO_HACKMON_NAME, DM20_BAO_HACKMON_NAME_LEN, DM20_BAO_HACKMON_ID, DM20_BAO_HACKMON_ID_LEN, DM20_BAO_HACKMON_FQID, DM20_BAO_HACKMON_FQID_LEN, DM20_BAO_HACKMON_FQNAME, DM20_BAO_HACKMON_FQNAME_LEN },
        { DM20_BAO_HACKMON_NAME, DM20_BAO_HACKMON_NAME_LEN, DM20_BAO_HACKMON_ID, DM20_BAO_HACKMON_ID_LEN, ALT_DM20_BAO_HACKMON_FQID, ALT_DM20_BAO_HACKMON_FQID_LEN, ALT_DM20_BAO_HACKMON_FQNAME, ALT_DM20_BAO_HACKMON_FQNAME_LEN },
        { DM20_BETAMON_NAME, DM20_BETAMON_NAME_LEN, DM20_BETAMON_ID, DM20_BETAMON_ID_LEN, DM20_BETAMON_FQID, DM20_BETAMON_FQID_LEN, DM20_BETAMON_FQNAME, DM20_BETAMON_FQNAME_LEN },
        { DM20_BETAMON_NAME, DM20_BETAMON_NAME_LEN, DM20_BETAMON_ID, DM20_BETAMON_ID_LEN, ALT_DM20_BETAMON_FQID, ALT_DM20_BETAMON_FQID_LEN, ALT_DM20_BETAMON_FQNAME, ALT_DM20_BETAMON_FQNAME_LEN },
        { DM20_BIRDRAMON_NAME, DM20_BIRDRAMON_NAME_LEN, DM20_BIRDRAMON_ID, DM20_BIRDRAMON_ID_LEN, DM20_BIRDRAMON_FQID, DM20_BIRDRAMON_FQID_LEN, DM20_BIRDRAMON_FQNAME, DM20_BIRDRAMON_FQNAME_LEN },
        { DM20_BIRDRAMON_NAME, DM20_BIRDRAMON_NAME_LEN, DM20_BIRDRAMON_ID, DM20_BIRDRAMON_ID_LEN, ALT_DM20_BIRDRAMON_FQID, ALT_DM20_BIRDRAMON_FQID_LEN, ALT_DM20_BIRDRAMON_FQNAME, ALT_DM20_BIRDRAMON_FQNAME_LEN },
        { DM20_BLITZ_GREYMON_NAME, DM20_BLITZ_GREYMON_NAME_LEN, DM20_BLITZ_GREYMON_ID, DM20_BLITZ_GREYMON_ID_LEN, DM20_BLITZ_GREYMON_FQID, DM20_BLITZ_GREYMON_FQID_LEN, DM20_BLITZ_GREYMON_FQNAME, DM20_BLITZ_GREYMON_FQNAME_LEN },
        { DM20_BLITZ_GREYMON_NAME, DM20_BLITZ_GREYMON_NAME_LEN, DM20_BLITZ_GREYMON_ID, DM20_BLITZ_GREYMON_ID_LEN, ALT_DM20_BLITZ_GREYMON_FQID, ALT_DM20_BLITZ_GREYMON_FQID_LEN, ALT_DM20_BLITZ_GREYMON_FQNAME, ALT_DM20_BLITZ_GREYMON_FQNAME_LEN },
        { DM20_BOTAMON_NAME, DM20_BOTAMON_NAME_LEN, DM20_BOTAMON_ID, DM20_BOTAMON_ID_LEN, DM20_BOTAMON_FQID, DM20_BOTAMON_FQID_LEN, DM20_BOTAMON_FQNAME, DM20_BOTAMON_FQNAME_LEN },
        { DM20_BOTAMON_NAME, DM20_BOTAMON_NAME_LEN, DM20_BOTAMON_ID, DM20_BOTAMON_ID_LEN, ALT_DM20_BOTAMON_FQID, ALT_DM20_BOTAMON_FQID_LEN, ALT_DM20_BOTAMON_FQNAME, ALT_DM20_BOTAMON_FQNAME_LEN },
        { DM20_BREAKDRAMON_NAME, DM20_BREAKDRAMON_NAME_LEN, DM20_BREAKDRAMON_ID, DM20_BREAKDRAMON_ID_LEN, DM20_BREAKDRAMON_FQID, DM20_BREAKDRAMON_FQID_LEN, DM20_BREAKDRAMON_FQNAME, DM20_BREAKDRAMON_FQNAME_LEN },
        { DM20_BREAKDRAMON_NAME, DM20_BREAKDRAMON_NAME_LEN, DM20_BREAKDRAMON_ID, DM20_BREAKDRAMON_ID_LEN, ALT_DM20_BREAKDRAMON_FQID, ALT_DM20_BREAKDRAMON_FQID_LEN, ALT_DM20_BREAKDRAMON_FQNAME, ALT_DM20_BREAKDRAMON_FQNAME_LEN },
        { DM20_CENTALMON_NAME, DM20_CENTALMON_NAME_LEN, DM20_CENTALMON_ID, DM20_CENTALMON_ID_LEN, DM20_CENTALMON_FQID, DM20_CENTALMON_FQID_LEN, DM20_CENTALMON_FQNAME, DM20_CENTALMON_FQNAME_LEN },
        { DM20_CENTALMON_NAME, DM20_CENTALMON_NAME_LEN, DM20_CENTALMON_ID, DM20_CENTALMON_ID_LEN, ALT_DM20_CENTALMON_FQID, ALT_DM20_CENTALMON_FQID_LEN, ALT_DM20_CENTALMON_FQNAME, ALT_DM20_CENTALMON_FQNAME_LEN },
        { DM20_COCKATRIMON_NAME, DM20_COCKATRIMON_NAME_LEN, DM20_COCKATRIMON_ID, DM20_COCKATRIMON_ID_LEN, DM20_COCKATRIMON_FQID, DM20_COCKATRIMON_FQID_LEN, DM20_COCKATRIMON_FQNAME, DM20_COCKATRIMON_FQNAME_LEN },
        { DM20_COCKATRIMON_NAME, DM20_COCKATRIMON_NAME_LEN, DM20_COCKATRIMON_ID, DM20_COCKATRIMON_ID_LEN, ALT_DM20_COCKATRIMON_FQID, ALT_DM20_COCKATRIMON_FQID_LEN, ALT_DM20_COCKATRIMON_FQNAME, ALT_DM20_COCKATRIMON_FQNAME_LEN },
        { DM20_COELAMON_NAME, DM20_COELAMON_NAME_LEN, DM20_COELAMON_ID, DM20_COELAMON_ID_LEN, DM20_COELAMON_FQID, DM20_COELAMON_FQID_LEN, DM20_COELAMON_FQNAME, DM20_COELAMON_FQNAME_LEN },
        { DM20_COELAMON_NAME, DM20_COELAMON_NAME_LEN, DM20_COELAMON_ID, DM20_COELAMON_ID_LEN, ALT_DM20_COELAMON_FQID, ALT_DM20_COELAMON_FQID_LEN, ALT_DM20_COELAMON_FQNAME, ALT_DM20_COELAMON_FQNAME_LEN },
        { DM20_COREDRAMON_BLUE_NAME, DM20_COREDRAMON_BLUE_NAME_LEN, DM20_COREDRAMON_BLUE_ID, DM20_COREDRAMON_BLUE_ID_LEN, DM20_COREDRAMON_BLUE_FQID, DM20_COREDRAMON_BLUE_FQID_LEN, DM20_COREDRAMON_BLUE_FQNAME, DM20_COREDRAMON_BLUE_FQNAME_LEN },
        { DM20_COREDRAMON_BLUE_NAME, DM20_COREDRAMON_BLUE_NAME_LEN, DM20_COREDRAMON_BLUE_ID, DM20_COREDRAMON_BLUE_ID_LEN, ALT_DM20_COREDRAMON_BLUE_FQID, ALT_DM20_COREDRAMON_BLUE_FQID_LEN, ALT_DM20_COREDRAMON_BLUE_FQNAME, ALT_DM20_COREDRAMON_BLUE_FQNAME_LEN },
        { DM20_COREDRAMON_GREEN_NAME, DM20_COREDRAMON_GREEN_NAME_LEN, DM20_COREDRAMON_GREEN_ID, DM20_COREDRAMON_GREEN_ID_LEN, DM20_COREDRAMON_GREEN_FQID, DM20_COREDRAMON_GREEN_FQID_LEN, DM20_COREDRAMON_GREEN_FQNAME, DM20_COREDRAMON_GREEN_FQNAME_LEN },
        { DM20_COREDRAMON_GREEN_NAME, DM20_COREDRAMON_GREEN_NAME_LEN, DM20_COREDRAMON_GREEN_ID, DM20_COREDRAMON_GREEN_ID_LEN, ALT_DM20_COREDRAMON_GREEN_FQID, ALT_DM20_COREDRAMON_GREEN_FQID_LEN, ALT_DM20_COREDRAMON_GREEN_FQNAME, ALT_DM20_COREDRAMON_GREEN_FQNAME_LEN },
        { DM20_CORONAMON_NAME, DM20_CORONAMON_NAME_LEN, DM20_CORONAMON_ID, DM20_CORONAMON_ID_LEN, DM20_CORONAMON_FQID, DM20_CORONAMON_FQID_LEN, DM20_CORONAMON_FQNAME, DM20_CORONAMON_FQNAME_LEN },
        { DM20_CORONAMON_NAME, DM20_CORONAMON_NAME_LEN, DM20_CORONAMON_ID, DM20_CORONAMON_ID_LEN, ALT_DM20_CORONAMON_FQID, ALT_DM20_CORONAMON_FQID_LEN, ALT_DM20_CORONAMON_FQNAME, ALT_DM20_CORONAMON_FQNAME_LEN },
        { DM20_CRESCEMON_NAME, DM20_CRESCEMON_NAME_LEN, DM20_CRESCEMON_ID, DM20_CRESCEMON_ID_LEN, DM20_CRESCEMON_FQID, DM20_CRESCEMON_FQID_LEN, DM20_CRESCEMON_FQNAME, DM20_CRESCEMON_FQNAME_LEN },
        { DM20_CRESCEMON_NAME, DM20_CRESCEMON_NAME_LEN, DM20_CRESCEMON_ID, DM20_CRESCEMON_ID_LEN, ALT_DM20_CRESCEMON_FQID, ALT_DM20_CRESCEMON_FQID_LEN, ALT_DM20_CRESCEMON_FQNAME, ALT_DM20_CRESCEMON_FQNAME_LEN },
        { DM20_CRES_GARURUMON_NAME, DM20_CRES_GARURUMON_NAME_LEN, DM20_CRES_GARURUMON_ID, DM20_CRES_GARURUMON_ID_LEN, DM20_CRES_GARURUMON_FQID, DM20_CRES_GARURUMON_FQID_LEN, DM20_CRES_GARURUMON_FQNAME, DM20_CRES_GARURUMON_FQNAME_LEN },
        { DM20_CRES_GARURUMON_NAME, DM20_CRES_GARURUMON_NAME_LEN, DM20_CRES_GARURUMON_ID, DM20_CRES_GARURUMON_ID_LEN, ALT_DM20_CRES_GARURUMON_FQID, ALT_DM20_CRES_GARURUMON_FQID_LEN, ALT_DM20_CRES_GARURUMON_FQNAME, ALT_DM20_CRES_GARURUMON_FQNAME_LEN },
        { DM20_CYCLOMON_NAME, DM20_CYCLOMON_NAME_LEN, DM20_CYCLOMON_ID, DM20_CYCLOMON_ID_LEN, DM20_CYCLOMON_FQID, DM20_CYCLOMON_FQID_LEN, DM20_CYCLOMON_FQNAME, DM20_CYCLOMON_FQNAME_LEN },
        { DM20_CYCLOMON_NAME, DM20_CYCLOMON_NAME_LEN, DM20_CYCLOMON_ID, DM20_CYCLOMON_ID_LEN, ALT_DM20_CYCLOMON_FQID, ALT_DM20_CYCLOMON_FQID_LEN, ALT_DM20_CYCLOMON_FQNAME, ALT_DM20_CYCLOMON_FQNAME_LEN },
        { DM20_DARK_TYRANOMON_NAME, DM20_DARK_TYRANOMON_NAME_LEN, DM20_DARK_TYRANOMON_ID, DM20_DARK_TYRANOMON_ID_LEN, DM20_DARK_TYRANOMON_FQID, DM20_DARK_TYRANOMON_FQID_LEN, DM20_DARK_TYRANOMON_FQNAME, DM20_DARK_TYRANOMON_FQNAME_LEN },
        { DM20_DARK_TYRANOMON_NAME, DM20_DARK_TYRANOMON_NAME_LEN, DM20_DARK_TYRANOMON_ID, DM20_DARK_TYRANOMON_ID_LEN, ALT_DM20_DARK_TYRANOMON_FQID, ALT_DM20_DARK_TYRANOMON_FQID_LEN, ALT_DM20_DARK_TYRANOMON_FQNAME, ALT_DM20_DARK_TYRANOMON_FQNAME_LEN },
        { DM20_DELTAMON_NAME, DM20_DELTAMON_NAME_LEN, DM20_DELTAMON_ID, DM20_DELTAMON_ID_LEN, DM20_DELTAMON_FQID, DM20_DELTAMON_FQID_LEN, DM20_DELTAMON_FQNAME, DM20_DELTAMON_FQNAME_LEN },
        { DM20_DELTAMON_NAME, DM20_DELTAMON_NAME_LEN, DM20_DELTAMON_ID, DM20_DELTAMON_ID_LEN, ALT_DM20_DELTAMON_FQID, ALT_DM20_DELTAMON_FQID_LEN, ALT_DM20_DELTAMON_FQNAME, ALT_DM20_DELTAMON_FQNAME_LEN },
        { DM20_DEVIDRAMON_NAME, DM20_DEVIDRAMON_NAME_LEN, DM20_DEVIDRAMON_ID, DM20_DEVIDRAMON_ID_LEN, DM20_DEVIDRAMON_FQID, DM20_DEVIDRAMON_FQID_LEN, DM20_DEVIDRAMON_FQNAME, DM20_DEVIDRAMON_FQNAME_LEN },
        { DM20_DEVIDRAMON_NAME, DM20_DEVIDRAMON_NAME_LEN, DM20_DEVIDRAMON_ID, DM20_DEVIDRAMON_ID_LEN, ALT_DM20_DEVIDRAMON_FQID, ALT_DM20_DEVIDRAMON_FQID_LEN, ALT_DM20_DEVIDRAMON_FQNAME, ALT_DM20_DEVIDRAMON_FQNAME_LEN },
        { DM20_DEVIMON_NAME, DM20_DEVIMON_NAME_LEN, DM20_DEVIMON_ID, DM20_DEVIMON_ID_LEN, DM20_DEVIMON_FQID, DM20_DEVIMON_FQID_LEN, DM20_DEVIMON_FQNAME, DM20_DEVIMON_FQNAME_LEN },
        { DM20_DEVIMON_NAME, DM20_DEVIMON_NAME_LEN, DM20_DEVIMON_ID, DM20_DEVIMON_ID_LEN, ALT_DM20_DEVIMON_FQID, ALT_DM20_DEVIMON_FQID_LEN, ALT_DM20_DEVIMON_FQNAME, ALT_DM20_DEVIMON_FQNAME_LEN },
        { DM20_DIANAMON_NAME, DM20_DIANAMON_NAME_LEN, DM20_DIANAMON_ID, DM20_DIANAMON_ID_LEN, DM20_DIANAMON_FQID, DM20_DIANAMON_FQID_LEN, DM20_DIANAMON_FQNAME, DM20_DIANAMON_FQNAME_LEN },
        { DM20_DIANAMON_NAME, DM20_DIANAMON_NAME_LEN, DM20_DIANAMON_ID, DM20_DIANAMON_ID_LEN, ALT_DM20_DIANAMON_FQID, ALT_DM20_DIANAMON_FQID_LEN, ALT_DM20_DIANAMON_FQNAME, ALT_DM20_DIANAMON_FQNAME_LEN },
        { DM20_DIGITAMAMON_NAME, DM20_DIGITAMAMON_NAME_LEN, DM20_DIGITAMAMON_ID, DM20_DIGITAMAMON_ID_LEN, DM20_DIGITAMAMON_FQID, DM20_DIGITAMAMON_FQID_LEN, DM20_DIGITAMAMON_FQNAME, DM20_DIGITAMAMON_FQNAME_LEN },
        { DM20_DIGITAMAMON_NAME, DM20_DIGITAMAMON_NAME_LEN, DM20_DIGITAMAMON_ID, DM20_DIGITAMAMON_ID_LEN, ALT_DM20_DIGITAMAMON_FQID, ALT_DM20_DIGITAMAMON_FQID_LEN, ALT_DM20_DIGITAMAMON_FQNAME, ALT_DM20_DIGITAMAMON_FQNAME_LEN },
        { DM20_DODOMON_NAME, DM20_DODOMON_NAME_LEN, DM20_DODOMON_ID, DM20_DODOMON_ID_LEN, DM20_DODOMON_FQID, DM20_DODOMON_FQID_LEN, DM20_DODOMON_FQNAME, DM20_DODOMON_FQNAME_LEN },
        { DM20_DODOMON_NAME, DM20_DODOMON_NAME_LEN, DM20_DODOMON_ID, DM20_DODOMON_ID_LEN, ALT_DM20_DODOMON_FQID, ALT_DM20_DODOMON_FQID_LEN, ALT_DM20_DODOMON_FQNAME, ALT_DM20_DODOMON_FQNAME_LEN },
        { DM20_DORIMON_NAME, DM20_DORIMON_NAME_LEN, DM20_DORIMON_ID, DM20_DORIMON_ID_LEN, DM20_DORIMON_FQID, DM20_DORIMON_FQID_LEN, DM20_DORIMON_FQNAME, DM20_DORIMON_FQNAME_LEN },
        { DM20_DORIMON_NAME, DM20_DORIMON_NAME_LEN, DM20_DORIMON_ID, DM20_DORIMON_ID_LEN, ALT_DM20_DORIMON_FQID, ALT_DM20_DORIMON_FQID_LEN, ALT_DM20_DORIMON_FQNAME, ALT_DM20_DORIMON_FQNAME_LEN },
        { DM20_DORUGAMON_NAME, DM20_DORUGAMON_NAME_LEN, DM20_DORUGAMON_ID, DM20_DORUGAMON_ID_LEN, DM20_DORUGAMON_FQID, DM20_DORUGAMON_FQID_LEN, DM20_DORUGAMON_FQNAME, DM20_DORUGAMON_FQNAME_LEN },
        { DM20_DORUGAMON_NAME, DM20_DORUGAMON_NAME_LEN, DM20_DORUGAMON_ID, DM20_DORUGAMON_ID_LEN, ALT_DM20_DORUGAMON_FQID, ALT_DM20_DORUGAMON_FQID_LEN, ALT_DM20_DORUGAMON_FQNAME, ALT_DM20_DORUGAMON_FQNAME_LEN },
        { DM20_DORUGUREMON_NAME, DM20_DORUGUREMON_NAME_LEN, DM20_DORUGUREMON_ID, DM20_DORUGUREMON_ID_LEN, DM20_DORUGUREMON_FQID, DM20_DORUGUREMON_FQID_LEN, DM20_DORUGUREMON_FQNAME, DM20_DORUGUREMON_FQNAME_LEN },
        { DM20_DORUGUREMON_NAME, DM20_DORUGUREMON_NAME_LEN, DM20_DORUGUREMON_ID, DM20_DORUGUREMON_ID_LEN, ALT_DM20_DORUGUREMON_FQID, ALT_DM20_DORUGUREMON_FQID_LEN, ALT_DM20_DORUGUREMON_FQNAME, ALT_DM20_DORUGUREMON_FQNAME_LEN },
        { DM20_DORUMON_NAME, DM20_DORUMON_NAME_LEN, DM20_DORUMON_ID, DM20_DORUMON_ID_LEN, DM20_DORUMON_FQID, DM20_DORUMON_FQID_LEN, DM20_DORUMON_FQNAME, DM20_DORUMON_FQNAME_LEN },
        { DM20_DORUMON_NAME, DM20_DORUMON_NAME_LEN, DM20_DORUMON_ID, DM20_DORUMON_ID_LEN, ALT_DM20_DORUMON_FQID, ALT_DM20_DORUMON_FQID_LEN, ALT_DM20_DORUMON_FQNAME, ALT_DM20_DORUMON_FQNAME_LEN },
        { DM20_DRACOMON_NAME, DM20_DRACOMON_NAME_LEN, DM20_DRACOMON_ID, DM20_DRACOMON_ID_LEN, DM20_DRACOMON_FQID, DM20_DRACOMON_FQID_LEN, DM20_DRACOMON_FQNAME, DM20_DRACOMON_FQNAME_LEN },
        { DM20_DRACOMON_NAME, DM20_DRACOMON_NAME_LEN, DM20_DRACOMON_ID, DM20_DRACOMON_ID_LEN, ALT_DM20_DRACOMON_FQID, ALT_DM20_DRACOMON_FQID_LEN, ALT_DM20_DRACOMON_FQNAME, ALT_DM20_DRACOMON_FQNAME_LEN },
        { DM20_DRIMOGEMON_NAME, DM20_DRIMOGEMON_NAME_LEN, DM20_DRIMOGEMON_ID, DM20_DRIMOGEMON_ID_LEN, DM20_DRIMOGEMON_FQID, DM20_DRIMOGEMON_FQID_LEN, DM20_DRIMOGEMON_FQNAME, DM20_DRIMOGEMON_FQNAME_LEN },
        { DM20_DRIMOGEMON_NAME, DM20_DRIMOGEMON_NAME_LEN, DM20_DRIMOGEMON_ID, DM20_DRIMOGEMON_ID_LEN, ALT_DM20_DRIMOGEMON_FQID, ALT_DM20_DRIMOGEMON_FQID_LEN, ALT_DM20_DRIMOGEMON_FQNAME, ALT_DM20_DRIMOGEMON_FQNAME_LEN },
        { DM20_DURAMON_NAME, DM20_DURAMON_NAME_LEN, DM20_DURAMON_ID, DM20_DURAMON_ID_LEN, DM20_DURAMON_FQID, DM20_DURAMON_FQID_LEN, DM20_DURAMON_FQNAME, DM20_DURAMON_FQNAME_LEN },
        { DM20_DURAMON_NAME, DM20_DURAMON_NAME_LEN, DM20_DURAMON_ID, DM20_DURAMON_ID_LEN, ALT_DM20_DURAMON_FQID, ALT_DM20_DURAMON_FQID_LEN, ALT_DM20_DURAMON_FQNAME, ALT_DM20_DURAMON_FQNAME_LEN },
        { DM20_DURANDAMON_NAME, DM20_DURANDAMON_NAME_LEN, DM20_DURANDAMON_ID, DM20_DURANDAMON_ID_LEN, DM20_DURANDAMON_FQID, DM20_DURANDAMON_FQID_LEN, DM20_DURANDAMON_FQNAME, DM20_DURANDAMON_FQNAME_LEN },
        { DM20_DURANDAMON_NAME, DM20_DURANDAMON_NAME_LEN, DM20_DURANDAMON_ID, DM20_DURANDAMON_ID_LEN, ALT_DM20_DURANDAMON_FQID, ALT_DM20_DURANDAMON_FQID_LEN, ALT_DM20_DURANDAMON_FQNAME, ALT_DM20_DURANDAMON_FQNAME_LEN },
        { DM20_ELECMON_NAME, DM20_ELECMON_NAME_LEN, DM20_ELECMON_ID, DM20_ELECMON_ID_LEN, DM20_ELECMON_FQID, DM20_ELECMON_FQID_LEN, DM20_ELECMON_FQNAME, DM20_ELECMON_FQNAME_LEN },
        { DM20_ELECMON_NAME, DM20_ELECMON_NAME_LEN, DM20_ELECMON_ID, DM20_ELECMON_ID_LEN, ALT_DM20_ELECMON_FQID, ALT_DM20_ELECMON_FQID_LEN, ALT_DM20_ELECMON_FQNAME, ALT_DM20_ELECMON_FQNAME_LEN },
        { DM20_ETEMON_NAME, DM20_ETEMON_NAME_LEN, DM20_ETEMON_ID, DM20_ETEMON_ID_LEN, DM20_ETEMON_FQID, DM20_ETEMON_FQID_LEN, DM20_ETEMON_FQNAME, DM20_ETEMON_FQNAME_LEN },
        { DM20_ETEMON_NAME, DM20_ETEMON_NAME_LEN, DM20_ETEMON_ID, DM20_ETEMON_ID_LEN, ALT_DM20_ETEMON_FQID, ALT_DM20_ETEMON_FQID_LEN, ALT_DM20_ETEMON_FQNAME, ALT_DM20_ETEMON_FQNAME_LEN },
        { DM20_EXAMON_NAME, DM20_EXAMON_NAME_LEN, DM20_EXAMON_ID, DM20_EXAMON_ID_LEN, DM20_EXAMON_FQID, DM20_EXAMON_FQID_LEN, DM20_EXAMON_FQNAME, DM20_EXAMON_FQNAME_LEN },
        { DM20_EXAMON_NAME, DM20_EXAMON_NAME_LEN, DM20_EXAMON_ID, DM20_EXAMON_ID_LEN, ALT_DM20_EXAMON_FQID, ALT_DM20_EXAMON_FQID_LEN, ALT_DM20_EXAMON_FQNAME, ALT_DM20_EXAMON_FQNAME_LEN },
        { DM20_EX_TYRANOMON_NAME, DM20_EX_TYRANOMON_NAME_LEN, DM20_EX_TYRANOMON_ID, DM20_EX_TYRANOMON_ID_LEN, DM20_EX_TYRANOMON_FQID, DM20_EX_TYRANOMON_FQID_LEN, DM20_EX_TYRANOMON_FQNAME, DM20_EX_TYRANOMON_FQNAME_LEN },
        { DM20_EX_TYRANOMON_NAME, DM20_EX_TYRANOMON_NAME_LEN, DM20_EX_TYRANOMON_ID, DM20_EX_TYRANOMON_ID_LEN, ALT_DM20_EX_TYRANOMON_FQID, ALT_DM20_EX_TYRANOMON_FQID_LEN, ALT_DM20_EX_TYRANOMON_FQNAME, ALT_DM20_EX_TYRANOMON_FQNAME_LEN },
        { DM20_FIRAMON_NAME, DM20_FIRAMON_NAME_LEN, DM20_FIRAMON_ID, DM20_FIRAMON_ID_LEN, DM20_FIRAMON_FQID, DM20_FIRAMON_FQID_LEN, DM20_FIRAMON_FQNAME, DM20_FIRAMON_FQNAME_LEN },
        { DM20_FIRAMON_NAME, DM20_FIRAMON_NAME_LEN, DM20_FIRAMON_ID, DM20_FIRAMON_ID_LEN, ALT_DM20_FIRAMON_FQID, ALT_DM20_FIRAMON_FQID_LEN, ALT_DM20_FIRAMON_FQNAME, ALT_DM20_FIRAMON_FQNAME_LEN },
        { DM20_FLAREMON_NAME, DM20_FLAREMON_NAME_LEN, DM20_FLAREMON_ID, DM20_FLAREMON_ID_LEN, DM20_FLAREMON_FQID, DM20_FLAREMON_FQID_LEN, DM20_FLAREMON_FQNAME, DM20_FLAREMON_FQNAME_LEN },
        { DM20_FLAREMON_NAME, DM20_FLAREMON_NAME_LEN, DM20_FLAREMON_ID, DM20_FLAREMON_ID_LEN, ALT_DM20_FLAREMON_FQID, ALT_DM20_FLAREMON_FQID_LEN, ALT_DM20_FLAREMON_FQNAME, ALT_DM20_FLAREMON_FQNAME_LEN },
        { DM20_FLYMON_NAME, DM20_FLYMON_NAME_LEN, DM20_FLYMON_ID, DM20_FLYMON_ID_LEN, DM20_FLYMON_FQID, DM20_FLYMON_FQID_LEN, DM20_FLYMON_FQNAME, DM20_FLYMON_FQNAME_LEN },
        { DM20_FLYMON_NAME, DM20_FLYMON_NAME_LEN, DM20_FLYMON_ID, DM20_FLYMON_ID_LEN, ALT_DM20_FLYMON_FQID, ALT_DM20_FLYMON_FQID_LEN, ALT_DM20_FLYMON_FQNAME, ALT_DM20_FLYMON_FQNAME_LEN },
        { DM20_GABUMON_NAME, DM20_GABUMON_NAME_LEN, DM20_GABUMON_ID, DM20_GABUMON_ID_LEN, DM20_GABUMON_FQID, DM20_GABUMON_FQID_LEN, DM20_GABUMON_FQNAME, DM20_GABUMON_FQNAME_LEN },
        { DM20_GABUMON_NAME, DM20_GABUMON_NAME_LEN, DM20_GABUMON_ID, DM20_GABUMON_ID_LEN, ALT_DM20_GABUMON_FQID, ALT_DM20_GABUMON_FQID_LEN, ALT_DM20_GABUMON_FQNAME, ALT_DM20_GABUMON_FQNAME_LEN },
        { DM20_GARURUMON_NAME, DM20_GARURUMON_NAME_LEN, DM20_GARURUMON_ID, DM20_GARURUMON_ID_LEN, DM20_GARURUMON_FQID, DM20_GARURUMON_FQID_LEN, DM20_GARURUMON_FQNAME, DM20_GARURUMON_FQNAME_LEN },
        { DM20_GARURUMON_NAME, DM20_GARURUMON_NAME_LEN, DM20_GARURUMON_ID, DM20_GARURUMON_ID_LEN, ALT_DM20_GARURUMON_FQID, ALT_DM20_GARURUMON_FQID_LEN, ALT_DM20_GARURUMON_FQNAME, ALT_DM20_GARURUMON_FQNAME_LEN },
        { DM20_GAZIMON_NAME, DM20_GAZIMON_NAME_LEN, DM20_GAZIMON_ID, DM20_GAZIMON_ID_LEN, DM20_GAZIMON_FQID, DM20_GAZIMON_FQID_LEN, DM20_GAZIMON_FQNAME, DM20_GAZIMON_FQNAME_LEN },
        { DM20_GAZIMON_NAME, DM20_GAZIMON_NAME_LEN, DM20_GAZIMON_ID, DM20_GAZIMON_ID_LEN, ALT_DM20_GAZIMON_FQID, ALT_DM20_GAZIMON_FQID_LEN, ALT_DM20_GAZIMON_FQNAME, ALT_DM20_GAZIMON_FQNAME_LEN },
        { DM20_GIROMON_NAME, DM20_GIROMON_NAME_LEN, DM20_GIROMON_ID, DM20_GIROMON_ID_LEN, DM20_GIROMON_FQID, DM20_GIROMON_FQID_LEN, DM20_GIROMON_FQNAME, DM20_GIROMON_FQNAME_LEN },
        { DM20_GIROMON_NAME, DM20_GIROMON_NAME_LEN, DM20_GIROMON_ID, DM20_GIROMON_ID_LEN, ALT_DM20_GIROMON_FQID, ALT_DM20_GIROMON_FQID_LEN, ALT_DM20_GIROMON_FQNAME, ALT_DM20_GIROMON_FQNAME_LEN },
        { DM20_GIZAMON_NAME, DM20_GIZAMON_NAME_LEN, DM20_GIZAMON_ID, DM20_GIZAMON_ID_LEN, DM20_GIZAMON_FQID, DM20_GIZAMON_FQID_LEN, DM20_GIZAMON_FQNAME, DM20_GIZAMON_FQNAME_LEN },
        { DM20_GIZAMON_NAME, DM20_GIZAMON_NAME_LEN, DM20_GIZAMON_ID, DM20_GIZAMON_ID_LEN, ALT_DM20_GIZAMON_FQID, ALT_DM20_GIZAMON_FQID_LEN, ALT_DM20_GIZAMON_FQNAME, ALT_DM20_GIZAMON_FQNAME_LEN },
        { DM20_GRACE_NOVAMON_NAME, DM20_GRACE_NOVAMON_NAME_LEN, DM20_GRACE_NOVAMON_ID, DM20_GRACE_NOVAMON_ID_LEN, DM20_GRACE_NOVAMON_FQID, DM20_GRACE_NOVAMON_FQID_LEN, DM20_GRACE_NOVAMON_FQNAME, DM20_GRACE_NOVAMON_FQNAME_LEN },
        { DM20_GRACE_NOVAMON_NAME, DM20_GRACE_NOVAMON_NAME_LEN, DM20_GRACE_NOVAMON_ID, DM20_GRACE_NOVAMON_ID_LEN, ALT_DM20_GRACE_NOVAMON_FQID, ALT_DM20_GRACE_NOVAMON_FQID_LEN, ALT_DM20_GRACE_NOVAMON_FQNAME, ALT_DM20_GRACE_NOVAMON_FQNAME_LEN },
        { DM20_GREYMON_NAME, DM20_GREYMON_NAME_LEN, DM20_GREYMON_ID, DM20_GREYMON_ID_LEN, DM20_GREYMON_FQID, DM20_GREYMON_FQID_LEN, DM20_GREYMON_FQNAME, DM20_GREYMON_FQNAME_LEN },
        { DM20_GREYMON_NAME, DM20_GREYMON_NAME_LEN, DM20_GREYMON_ID, DM20_GREYMON_ID_LEN, ALT_DM20_GREYMON_FQID, ALT_DM20_GREYMON_FQID_LEN, ALT_DM20_GREYMON_FQNAME, ALT_DM20_GREYMON_FQNAME_LEN },
        { DM20_GROUNDRAMON_NAME, DM20_GROUNDRAMON_NAME_LEN, DM20_GROUNDRAMON_ID, DM20_GROUNDRAMON_ID_LEN, DM20_GROUNDRAMON_FQID, DM20_GROUNDRAMON_FQID_LEN, DM20_GROUNDRAMON_FQNAME, DM20_GROUNDRAMON_FQNAME_LEN },
        { DM20_GROUNDRAMON_NAME, DM20_GROUNDRAMON_NAME_LEN, DM20_GROUNDRAMON_ID, DM20_GROUNDRAMON_ID_LEN, ALT_DM20_GROUNDRAMON_FQID, ALT_DM20_GROUNDRAMON_FQID_LEN, ALT_DM20_GROUNDRAMON_FQNAME, ALT_DM20_GROUNDRAMON_FQNAME_LEN },
        { DM20_HACKMON_NAME, DM20_HACKMON_NAME_LEN, DM20_HACKMON_ID, DM20_HACKMON_ID_LEN, DM20_HACKMON_FQID, DM20_HACKMON_FQID_LEN, DM20_HACKMON_FQNAME, DM20_HACKMON_FQNAME_LEN },
        { DM20_HACKMON_NAME, DM20_HACKMON_NAME_LEN, DM20_HACKMON_ID, DM20_HACKMON_ID_LEN, ALT_DM20_HACKMON_FQID, ALT_DM20_HACKMON_FQID_LEN, ALT_DM20_HACKMON_FQNAME, ALT_DM20_HACKMON_FQNAME_LEN },
        { DM20_HI_ANDROMON_NAME, DM20_HI_ANDROMON_NAME_LEN, DM20_HI_ANDROMON_ID, DM20_HI_ANDROMON_ID_LEN, DM20_HI_ANDROMON_FQID, DM20_HI_ANDROMON_FQID_LEN, DM20_HI_ANDROMON_FQNAME, DM20_HI_ANDROMON_FQNAME_LEN },
        { DM20_HI_ANDROMON_NAME, DM20_HI_ANDROMON_NAME_LEN, DM20_HI_ANDROMON_ID, DM20_HI_ANDROMON_ID_LEN, ALT_DM20_HI_ANDROMON_FQID, ALT_DM20_HI_ANDROMON_FQID_LEN, ALT_DM20_HI_ANDROMON_FQNAME, ALT_DM20_HI_ANDROMON_FQNAME_LEN },
        { DM20_JESMON_NAME, DM20_JESMON_NAME_LEN, DM20_JESMON_ID, DM20_JESMON_ID_LEN, DM20_JESMON_FQID, DM20_JESMON_FQID_LEN, DM20_JESMON_FQNAME, DM20_JESMON_FQNAME_LEN },
        { DM20_JESMON_NAME, DM20_JESMON_NAME_LEN, DM20_JESMON_ID, DM20_JESMON_ID_LEN, ALT_DM20_JESMON_FQID, ALT_DM20_JESMON_FQID_LEN, ALT_DM20_JESMON_FQNAME, ALT_DM20_JESMON_FQNAME_LEN },
        { DM20_KABUTERIMON_NAME, DM20_KABUTERIMON_NAME_LEN, DM20_KABUTERIMON_ID, DM20_KABUTERIMON_ID_LEN, DM20_KABUTERIMON_FQID, DM20_KABUTERIMON_FQID_LEN, DM20_KABUTERIMON_FQNAME, DM20_KABUTERIMON_FQNAME_LEN },
        { DM20_KABUTERIMON_NAME, DM20_KABUTERIMON_NAME_LEN, DM20_KABUTERIMON_ID, DM20_KABUTERIMON_ID_LEN, ALT_DM20_KABUTERIMON_FQID, ALT_DM20_KABUTERIMON_FQID_LEN, ALT_DM20_KABUTERIMON_FQNAME, ALT_DM20_KABUTERIMON_FQNAME_LEN },
        { DM20_KING_ETEMON_NAME, DM20_KING_ETEMON_NAME_LEN, DM20_KING_ETEMON_ID, DM20_KING_ETEMON_ID_LEN, DM20_KING_ETEMON_FQID, DM20_KING_ETEMON_FQID_LEN, DM20_KING_ETEMON_FQNAME, DM20_KING_ETEMON_FQNAME_LEN },
        { DM20_KING_ETEMON_NAME, DM20_KING_ETEMON_NAME_LEN, DM20_KING_ETEMON_ID, DM20_KING_ETEMON_ID_LEN, ALT_DM20_KING_ETEMON_FQID, ALT_DM20_KING_ETEMON_FQID_LEN, ALT_DM20_KING_ETEMON_FQNAME, ALT_DM20_KING_ETEMON_FQNAME_LEN },
        { DM20_KOROMON_NAME, DM20_KOROMON_NAME_LEN, DM20_KOROMON_ID, DM20_KOROMON_ID_LEN, DM20_KOROMON_FQID, DM20_KOROMON_FQID_LEN, DM20_KOROMON_FQNAME, DM20_KOROMON_FQNAME_LEN },
        { DM20_KOROMON_NAME, DM20_KOROMON_NAME_LEN, DM20_KOROMON_ID, DM20_KOROMON_ID_LEN, ALT_DM20_KOROMON_FQID, ALT_DM20_KOROMON_FQID_LEN, ALT_DM20_KOROMON_FQNAME, ALT_DM20_KOROMON_FQNAME_LEN },
        { DM20_KUNEMON_NAME, DM20_KUNEMON_NAME_LEN, DM20_KUNEMON_ID, DM20_KUNEMON_ID_LEN, DM20_KUNEMON_FQID, DM20_KUNEMON_FQID_LEN, DM20_KUNEMON_FQNAME, DM20_KUNEMON_FQNAME_LEN },
        { DM20_KUNEMON_NAME, DM20_KUNEMON_NAME_LEN, DM20_KUNEMON_ID, DM20_KUNEMON_ID_LEN, ALT_DM20_KUNEMON_FQID, ALT_DM20_KUNEMON_FQID_LEN, ALT_DM20_KUNEMON_FQNAME, ALT_DM20_KUNEMON_FQNAME_LEN },
        { DM20_KUWAGAMON_NAME, DM20_KUWAGAMON_NAME_LEN, DM20_KUWAGAMON_ID, DM20_KUWAGAMON_ID_LEN, DM20_KUWAGAMON_FQID, DM20_KUWAGAMON_FQID_LEN, DM20_KUWAGAMON_FQNAME, DM20_KUWAGAMON_FQNAME_LEN },
        { DM20_KUWAGAMON_NAME, DM20_KUWAGAMON_NAME_LEN, DM20_KUWAGAMON_ID, DM20_KUWAGAMON_ID_LEN, ALT_DM20_KUWAGAMON_FQID, ALT_DM20_KUWAGAMON_FQID_LEN, ALT_DM20_KUWAGAMON_FQNAME, ALT_DM20_KUWAGAMON_FQNAME_LEN },
        { DM20_LEKISMON_NAME, DM20_LEKISMON_NAME_LEN, DM20_LEKISMON_ID, DM20_LEKISMON_ID_LEN, DM20_LEKISMON_FQID, DM20_LEKISMON_FQID_LEN, DM20_LEKISMON_FQNAME, DM20_LEKISMON_FQNAME_LEN },
        { DM20_LEKISMON_NAME, DM20_LEKISMON_NAME_LEN, DM20_LEKISMON_ID, DM20_LEKISMON_ID_LEN, ALT_DM20_LEKISMON_FQID, ALT_DM20_LEKISMON_FQID_LEN, ALT_DM20_LEKISMON_FQNAME, ALT_DM20_LEKISMON_FQNAME_LEN },
        { DM20_LEOMON_NAME, DM20_LEOMON_NAME_LEN, DM20_LEOMON_ID, DM20_LEOMON_ID_LEN, DM20_LEOMON_FQID, DM20_LEOMON_FQID_LEN, DM20_LEOMON_FQNAME, DM20_LEOMON_FQNAME_LEN },
        { DM20_LEOMON_NAME, DM20_LEOMON_NAME_LEN, DM20_LEOMON_ID, DM20_LEOMON_ID_LEN, ALT_DM20_LEOMON_FQID, ALT_DM20_LEOMON_FQID_LEN, ALT_DM20_LEOMON_FQNAME, ALT_DM20_LEOMON_FQNAME_LEN },
        { DM20_LUNAMON_NAME, DM20_LUNAMON_NAME_LEN, DM20_LUNAMON_ID, DM20_LUNAMON_ID_LEN, DM20_LUNAMON_FQID, DM20_LUNAMON_FQID_LEN, DM20_LUNAMON_FQNAME, DM20_LUNAMON_FQNAME_LEN },
        { DM20_LUNAMON_NAME, DM20_LUNAMON_NAME_LEN, DM20_LUNAMON_ID, DM20_LUNAMON_ID_LEN, ALT_DM20_LUNAMON_FQID, ALT_DM20_LUNAMON_FQID_LEN, ALT_DM20_LUNAMON_FQNAME, ALT_DM20_LUNAMON_FQNAME_LEN },
        { DM20_MAMEMON_NAME, DM20_MAMEMON_NAME_LEN, DM20_MAMEMON_ID, DM20_MAMEMON_ID_LEN, DM20_MAMEMON_FQID, DM20_MAMEMON_FQID_LEN, DM20_MAMEMON_FQNAME, DM20_MAMEMON_FQNAME_LEN },
        { DM20_MAMEMON_NAME, DM20_MAMEMON_NAME_LEN, DM20_MAMEMON_ID, DM20_MAMEMON_ID_LEN, ALT_DM20_MAMEMON_FQID, ALT_DM20_MAMEMON_FQID_LEN, ALT_DM20_MAMEMON_FQNAME, ALT_DM20_MAMEMON_FQNAME_LEN },
        { DM20_MEGADRAMON_NAME, DM20_MEGADRAMON_NAME_LEN, DM20_MEGADRAMON_ID, DM20_MEGADRAMON_ID_LEN, DM20_MEGADRAMON_FQID, DM20_MEGADRAMON_FQID_LEN, DM20_MEGADRAMON_FQNAME, DM20_MEGADRAMON_FQNAME_LEN },
        { DM20_MEGADRAMON_NAME, DM20_MEGADRAMON_NAME_LEN, DM20_MEGADRAMON_ID, DM20_MEGADRAMON_ID_LEN, ALT_DM20_MEGADRAMON_FQID, ALT_DM20_MEGADRAMON_FQID_LEN, ALT_DM20_MEGADRAMON_FQNAME, ALT_DM20_MEGADRAMON_FQNAME_LEN },
        { DM20_MEICOOMON_NAME, DM20_MEICOOMON_NAME_LEN, DM20_MEICOOMON_ID, DM20_MEICOOMON_ID_LEN, DM20_MEICOOMON_FQID, DM20_MEICOOMON_FQID_LEN, DM20_MEICOOMON_FQNAME, DM20_MEICOOMON_FQNAME_LEN },
        { DM20_MEICOOMON_NAME, DM20_MEICOOMON_NAME_LEN, DM20_MEICOOMON_ID, DM20_MEICOOMON_ID_LEN, ALT_DM20_MEICOOMON_FQID, ALT_DM20_MEICOOMON_FQID_LEN, ALT_DM20_MEICOOMON_FQNAME, ALT_DM20_MEICOOMON_FQNAME_LEN },
        { DM20_MEICRACKMON_NAME, DM20_MEICRACKMON_NAME_LEN, DM20_MEICRACKMON_ID, DM20_MEICRACKMON_ID_LEN, DM20_MEICRACKMON_FQID, DM20_MEICRACKMON_FQID_LEN, DM20_MEICRACKMON_FQNAME, DM20_MEICRACKMON_FQNAME_LEN },
        { DM20_MEICRACKMON_NAME, DM20_MEICRACKMON_NAME_LEN, DM20_MEICRACKMON_ID, DM20_MEICRACKMON_ID_LEN, ALT_DM20_MEICRACKMON_FQID, ALT_DM20_MEICRACKMON_FQID_LEN, ALT_DM20_MEICRACKMON_FQNAME, ALT_DM20_MEICRACKMON_FQNAME_LEN },
        { DM20_MERAMON_NAME, DM20_MERAMON_NAME_LEN, DM20_MERAMON_ID, DM20_MERAMON_ID_LEN, DM20_MERAMON_FQID, DM20_MERAMON_FQID_LEN, DM20_MERAMON_FQNAME, DM20_MERAMON_FQNAME_LEN },
        { DM20_MERAMON_NAME, DM20_MERAMON_NAME_LEN, DM20_MERAMON_ID, DM20_MERAMON_ID_LEN, ALT_DM20_MERAMON_FQID, ALT_DM20_MERAMON_FQID_LEN, ALT_DM20_MERAMON_FQNAME, ALT_DM20_MERAMON_FQNAME_LEN },
        { DM20_METAL_GREYMON_NAME, DM20_METAL_GREYMON_NAME_LEN, DM20_METAL_GREYMON_ID, DM20_METAL_GREYMON_ID_LEN, DM20_METAL_GREYMON_FQID, DM20_METAL_GREYMON_FQID_LEN, DM20_METAL_GREYMON_FQNAME, DM20_METAL_GREYMON_FQNAME_LEN },
        { DM20_METAL_GREYMON_NAME, DM20_METAL_GREYMON_NAME_LEN, DM20_METAL_GREYMON_ID, DM20_METAL_GREYMON_ID_LEN, ALT_DM20_METAL_GREYMON_FQID, ALT_DM20_METAL_GREYMON_FQID_LEN, ALT_DM20_METAL_GREYMON_FQNAME, ALT_DM20_METAL_GREYMON_FQNAME_LEN },
        { DM20_METAL_MAMEMON_NAME, DM20_METAL_MAMEMON_NAME_LEN, DM20_METAL_MAMEMON_ID, DM20_METAL_MAMEMON_ID_LEN, DM20_METAL_MAMEMON_FQID, DM20_METAL_MAMEMON_FQID_LEN, DM20_METAL_MAMEMON_FQNAME, DM20_METAL_MAMEMON_FQNAME_LEN },
        { DM20_METAL_MAMEMON_NAME, DM20_METAL_MAMEMON_NAME_LEN, DM20_METAL_MAMEMON_ID, DM20_METAL_MAMEMON_ID_LEN, ALT_DM20_METAL_MAMEMON_FQID, ALT_DM20_METAL_MAMEMON_FQID_LEN, ALT_DM20_METAL_MAMEMON_FQNAME, ALT_DM20_METAL_MAMEMON_FQNAME_LEN },
        { DM20_METAL_TYRANOMON_NAME, DM20_METAL_TYRANOMON_NAME_LEN, DM20_METAL_TYRANOMON_ID, DM20_METAL_TYRANOMON_ID_LEN, DM20_METAL_TYRANOMON_FQID, DM20_METAL_TYRANOMON_FQID_LEN, DM20_METAL_TYRANOMON_FQNAME, DM20_METAL_TYRANOMON_FQNAME_LEN },
        { DM20_METAL_TYRANOMON_NAME, DM20_METAL_TYRANOMON_NAME_LEN, DM20_METAL_TYRANOMON_ID, DM20_METAL_TYRANOMON_ID_LEN, ALT_DM20_METAL_TYRANOMON_FQID, ALT_DM20_METAL_TYRANOMON_FQID_LEN, ALT_DM20_METAL_TYRANOMON_FQNAME, ALT_DM20_METAL_TYRANOMON_FQNAME_LEN },
        { DM20_MOJYAMON_NAME, DM20_MOJYAMON_NAME_LEN, DM20_MOJYAMON_ID, DM20_MOJYAMON_ID_LEN, DM20_MOJYAMON_FQID, DM20_MOJYAMON_FQID_LEN, DM20_MOJYAMON_FQNAME, DM20_MOJYAMON_FQNAME_LEN },
        { DM20_MOJYAMON_NAME, DM20_MOJYAMON_NAME_LEN, DM20_MOJYAMON_ID, DM20_MOJYAMON_ID_LEN, ALT_DM20_MOJYAMON_FQID, ALT_DM20_MOJYAMON_FQID_LEN, ALT_DM20_MOJYAMON_FQNAME, ALT_DM20_MOJYAMON_FQNAME_LEN },
        { DM20_MONOCHROMON_NAME, DM20_MONOCHROMON_NAME_LEN, DM20_MONOCHROMON_ID, DM20_MONOCHROMON_ID_LEN, DM20_MONOCHROMON_FQID, DM20_MONOCHROMON_FQID_LEN, DM20_MONOCHROMON_FQNAME, DM20_MONOCHROMON_FQNAME_LEN },
        { DM20_MONOCHROMON_NAME, DM20_MONOCHROMON_NAME_LEN, DM20_MONOCHROMON_ID, DM20_MONOCHROMON_ID_LEN, ALT_DM20_MONOCHROMON_FQID, ALT_DM20_MONOCHROMON_FQID_LEN, ALT_DM20_MONOCHROMON_FQNAME, ALT_DM20_MONOCHROMON_FQNAME_LEN },
        { DM20_MONZAEMON_NAME, DM20_MONZAEMON_NAME_LEN, DM20_MONZAEMON_ID, DM20_MONZAEMON_ID_LEN, DM20_MONZAEMON_FQID, DM20_MONZAEMON_FQID_LEN, DM20_MONZAEMON_FQNAME, DM20_MONZAEMON_FQNAME_LEN },
        { DM20_MONZAEMON_NAME, DM20_MONZAEMON_NAME_LEN, DM20_MONZAEMON_ID, DM20_MONZAEMON_ID_LEN, ALT_DM20_MONZAEMON_FQID, ALT_DM20_MONZAEMON_FQID_LEN, ALT_DM20_MONZAEMON_FQNAME, ALT_DM20_MONZAEMON_FQNAME_LEN },
        { DM20_MUGENDRAMON_NAME, DM20_MUGENDRAMON_NAME_LEN, DM20_MUGENDRAMON_ID, DM20_MUGENDRAMON_ID_LEN, DM20_MUGENDRAMON_FQID, DM20_MUGENDRAMON_FQID_LEN, DM20_MUGENDRAMON_FQNAME, DM20_MUGENDRAMON_FQNAME_LEN },
        { DM20_MUGENDRAMON_NAME, DM20_MUGENDRAMON_NAME_LEN, DM20_MUGENDRAMON_ID, DM20_MUGENDRAMON_ID_LEN, ALT_DM20_MUGENDRAMON_FQID, ALT_DM20_MUGENDRAMON_FQID_LEN, ALT_DM20_MUGENDRAMON_FQNAME, ALT_DM20_MUGENDRAMON_FQNAME_LEN },
        { DM20_NANIMON_NAME, DM20_NANIMON_NAME_LEN, DM20_NANIMON_ID, DM20_NANIMON_ID_LEN, DM20_NANIMON_FQID, DM20_NANIMON_FQID_LEN, DM20_NANIMON_FQNAME, DM20_NANIMON_FQNAME_LEN },
        { DM20_NANIMON_NAME, DM20_NANIMON_NAME_LEN, DM20_NANIMON_ID, DM20_NANIMON_ID_LEN, ALT_DM20_NANIMON_FQID, ALT_DM20_NANIMON_FQID_LEN, ALT_DM20_NANIMON_FQNAME, ALT_DM20_NANIMON_FQNAME_LEN },
        { DM20_NANOMON_NAME, DM20_NANOMON_NAME_LEN, DM20_NANOMON_ID, DM20_NANOMON_ID_LEN, DM20_NANOMON_FQID, DM20_NANOMON_FQID_LEN, DM20_NANOMON_FQNAME, DM20_NANOMON_FQNAME_LEN },
        { DM20_NANOMON_NAME, DM20_NANOMON_NAME_LEN, DM20_NANOMON_ID, DM20_NANOMON_ID_LEN, ALT_DM20_NANOMON_FQID, ALT_DM20_NANOMON_FQID_LEN, ALT_DM20_NANOMON_FQNAME, ALT_DM20_NANOMON_FQNAME_LEN },
        { DM20_NUMEMON_NAME, DM20_NUMEMON_NAME_LEN, DM20_NUMEMON_ID, DM20_NUMEMON_ID_LEN, DM20_NUMEMON_FQID, DM20_NUMEMON_FQID_LEN, DM20_NUMEMON_FQNAME, DM20_NUMEMON_FQNAME_LEN },
        { DM20_NUMEMON_NAME, DM20_NUMEMON_NAME_LEN, DM20_NUMEMON_ID, DM20_NUMEMON_ID_LEN, ALT_DM20_NUMEMON_FQID, ALT_DM20_NUMEMON_FQID_LEN, ALT_DM20_NUMEMON_FQNAME, ALT_DM20_NUMEMON_FQNAME_LEN },
        { DM20_NYAROMON_NAME, DM20_NYAROMON_NAME_LEN, DM20_NYAROMON_ID, DM20_NYAROMON_ID_LEN, DM20_NYAROMON_FQID, DM20_NYAROMON_FQID_LEN, DM20_NYAROMON_FQNAME, DM20_NYAROMON_FQNAME_LEN },
        { DM20_NYAROMON_NAME, DM20_NYAROMON_NAME_LEN, DM20_NYAROMON_ID, DM20_NYAROMON_ID_LEN, ALT_DM20_NYAROMON_FQID, ALT_DM20_NYAROMON_FQID_LEN, ALT_DM20_NYAROMON_FQNAME, ALT_DM20_NYAROMON_FQNAME_LEN },
        { DM20_OGREMON_NAME, DM20_OGREMON_NAME_LEN, DM20_OGREMON_ID, DM20_OGREMON_ID_LEN, DM20_OGREMON_FQID, DM20_OGREMON_FQID_LEN, DM20_OGREMON_FQNAME, DM20_OGREMON_FQNAME_LEN },
        { DM20_OGREMON_NAME, DM20_OGREMON_NAME_LEN, DM20_OGREMON_ID, DM20_OGREMON_ID_LEN, ALT_DM20_OGREMON_FQID, ALT_DM20_OGREMON_FQID_LEN, ALT_DM20_OGREMON_FQNAME, ALT_DM20_OGREMON_FQNAME_LEN },
        { DM20_OMEGAMON_ALTER_S_NAME, DM20_OMEGAMON_ALTER_S_NAME_LEN, DM20_OMEGAMON_ALTER_S_ID, DM20_OMEGAMON_ALTER_S_ID_LEN, DM20_OMEGAMON_ALTER_S_FQID, DM20_OMEGAMON_ALTER_S_FQID_LEN, DM20_OMEGAMON_ALTER_S_FQNAME, DM20_OMEGAMON_ALTER_S_FQNAME_LEN },
        { DM20_OMEGAMON_ALTER_S_NAME, DM20_OMEGAMON_ALTER_S_NAME_LEN, DM20_OMEGAMON_ALTER_S_ID, DM20_OMEGAMON_ALTER_S_ID_LEN, ALT_DM20_OMEGAMON_ALTER_S_FQID, ALT_DM20_OMEGAMON_ALTER_S_FQID_LEN, ALT_DM20_OMEGAMON_ALTER_S_FQNAME, ALT_DM20_OMEGAMON_ALTER_S_FQNAME_LEN },
        { DM20_OMEGAMON_NAME, DM20_OMEGAMON_NAME_LEN, DM20_OMEGAMON_ID, DM20_OMEGAMON_ID_LEN, DM20_OMEGAMON_FQID, DM20_OMEGAMON_FQID_LEN, DM20_OMEGAMON_FQNAME, DM20_OMEGAMON_FQNAME_LEN },
        { DM20_OMEGAMON_NAME, DM20_OMEGAMON_NAME_LEN, DM20_OMEGAMON_ID, DM20_OMEGAMON_ID_LEN, ALT_DM20_OMEGAMON_FQID, ALT_DM20_OMEGAMON_FQID_LEN, ALT_DM20_OMEGAMON_FQNAME, ALT_DM20_OMEGAMON_FQNAME_LEN },
        { DM20_PAGUMON_NAME, DM20_PAGUMON_NAME_LEN, DM20_PAGUMON_ID, DM20_PAGUMON_ID_LEN, DM20_PAGUMON_FQID, DM20_PAGUMON_FQID_LEN, DM20_PAGUMON_FQNAME, DM20_PAGUMON_FQNAME_LEN },
        { DM20_PAGUMON_NAME, DM20_PAGUMON_NAME_LEN, DM20_PAGUMON_ID, DM20_PAGUMON_ID_LEN, ALT_DM20_PAGUMON_FQID, ALT_DM20_PAGUMON_FQID_LEN, ALT_DM20_PAGUMON_FQNAME, ALT_DM20_PAGUMON_FQNAME_LEN },
        { DM20_PALMON_NAME, DM20_PALMON_NAME_LEN, DM20_PALMON_ID, DM20_PALMON_ID_LEN, DM20_PALMON_FQID, DM20_PALMON_FQID_LEN, DM20_PALMON_FQNAME, DM20_PALMON_FQNAME_LEN },
        { DM20_PALMON_NAME, DM20_PALMON_NAME_LEN, DM20_PALMON_ID, DM20_PALMON_ID_LEN, ALT_DM20_PALMON_FQID, ALT_DM20_PALMON_FQID_LEN, ALT_DM20_PALMON_FQNAME, ALT_DM20_PALMON_FQNAME_LEN },
        { DM20_PATAMON_NAME, DM20_PATAMON_NAME_LEN, DM20_PATAMON_ID, DM20_PATAMON_ID_LEN, DM20_PATAMON_FQID, DM20_PATAMON_FQID_LEN, DM20_PATAMON_FQNAME, DM20_PATAMON_FQNAME_LEN },
        { DM20_PATAMON_NAME, DM20_PATAMON_NAME_LEN, DM20_PATAMON_ID, DM20_PATAMON_ID_LEN, ALT_DM20_PATAMON_FQID, ALT_DM20_PATAMON_FQID_LEN, ALT_DM20_PATAMON_FQNAME, ALT_DM20_PATAMON_FQNAME_LEN },
        { DM20_PETITMON_NAME, DM20_PETITMON_NAME_LEN, DM20_PETITMON_ID, DM20_PETITMON_ID_LEN, DM20_PETITMON_FQID, DM20_PETITMON_FQID_LEN, DM20_PETITMON_FQNAME, DM20_PETITMON_FQNAME_LEN },
        { DM20_PETITMON_NAME, DM20_PETITMON_NAME_LEN, DM20_PETITMON_ID, DM20_PETITMON_ID_LEN, ALT_DM20_PETITMON_FQID, ALT_DM20_PETITMON_FQID_LEN, ALT_DM20_PETITMON_FQNAME, ALT_DM20_PETITMON_FQNAME_LEN },
        { DM20_PICCOLOMON_NAME, DM20_PICCOLOMON_NAME_LEN, DM20_PICCOLOMON_ID, DM20_PICCOLOMON_ID_LEN, DM20_PICCOLOMON_FQID, DM20_PICCOLOMON_FQID_LEN, DM20_PICCOLOMON_FQNAME, DM20_PICCOLOMON_FQNAME_LEN },
        { DM20_PICCOLOMON_NAME, DM20_PICCOLOMON_NAME_LEN, DM20_PICCOLOMON_ID, DM20_PICCOLOMON_ID_LEN, ALT_DM20_PICCOLOMON_FQID, ALT_DM20_PICCOLOMON_FQID_LEN, ALT_DM20_PICCOLOMON_FQNAME, ALT_DM20_PICCOLOMON_FQNAME_LEN },
        { DM20_PINOCHIMON_NAME, DM20_PINOCHIMON_NAME_LEN, DM20_PINOCHIMON_ID, DM20_PINOCHIMON_ID_LEN, DM20_PINOCHIMON_FQID, DM20_PINOCHIMON_FQID_LEN, DM20_PINOCHIMON_FQNAME, DM20_PINOCHIMON_FQNAME_LEN },
        { DM20_PINOCHIMON_NAME, DM20_PINOCHIMON_NAME_LEN, DM20_PINOCHIMON_ID, DM20_PINOCHIMON_ID_LEN, ALT_DM20_PINOCHIMON_FQID, ALT_DM20_PINOCHIMON_FQID_LEN, ALT_DM20_PINOCHIMON_FQNAME, ALT_DM20_PINOCHIMON_FQNAME_LEN },
        { DM20_PITCHMON_NAME, DM20_PITCHMON_NAME_LEN, DM20_PITCHMON_ID, DM20_PITCHMON_ID_LEN, DM20_PITCHMON_FQID, DM20_PITCHMON_FQID_LEN, DM20_PITCHMON_FQNAME, DM20_PITCHMON_FQNAME_LEN },
        { DM20_PITCHMON_NAME, DM20_PITCHMON_NAME_LEN, DM20_PITCHMON_ID, DM20_PITCHMON_ID_LEN, ALT_DM20_PITCHMON_FQID, ALT_DM20_PITCHMON_FQID_LEN, ALT_DM20_PITCHMON_FQNAME, ALT_DM20_PITCHMON_FQNAME_LEN },
        { DM20_PIYOMON_NAME, DM20_PIYOMON_NAME_LEN, DM20_PIYOMON_ID, DM20_PIYOMON_ID_LEN, DM20_PIYOMON_FQID, DM20_PIYOMON_FQID_LEN, DM20_PIYOMON_FQNAME, DM20_PIYOMON_FQNAME_LEN },
        { DM20_PIYOMON_NAME, DM20_PIYOMON_NAME_LEN, DM20_PIYOMON_ID, DM20_PIYOMON_ID_LEN, ALT_DM20_PIYOMON_FQID, ALT_DM20_PIYOMON_FQID_LEN, ALT_DM20_PIYOMON_FQNAME, ALT_DM20_PIYOMON_FQNAME_LEN },
        { DM20_PLOTMON_NAME, DM20_PLOTMON_NAME_LEN, DM20_PLOTMON_ID, DM20_PLOTMON_ID_LEN, DM20_PLOTMON_FQID, DM20_PLOTMON_FQID_LEN, DM20_PLOTMON_FQNAME, DM20_PLOTMON_FQNAME_LEN },
        { DM20_PLOTMON_NAME, DM20_PLOTMON_NAME_LEN, DM20_PLOTMON_ID, DM20_PLOTMON_ID_LEN, ALT_DM20_PLOTMON_FQID, ALT_DM20_PLOTMON_FQID_LEN, ALT_DM20_PLOTMON_FQNAME, ALT_DM20_PLOTMON_FQNAME_LEN },
        { DM20_POYOMON_NAME, DM20_POYOMON_NAME_LEN, DM20_POYOMON_ID, DM20_POYOMON_ID_LEN, DM20_POYOMON_FQID, DM20_POYOMON_FQID_LEN, DM20_POYOMON_FQNAME, DM20_POYOMON_FQNAME_LEN },
        { DM20_POYOMON_NAME, DM20_POYOMON_NAME_LEN, DM20_POYOMON_ID, DM20_POYOMON_ID_LEN, ALT_DM20_POYOMON_FQID, ALT_DM20_POYOMON_FQID_LEN, ALT_DM20_POYOMON_FQNAME, ALT_DM20_POYOMON_FQNAME_LEN },
        { DM20_PUKAMON_NAME, DM20_PUKAMON_NAME_LEN, DM20_PUKAMON_ID, DM20_PUKAMON_ID_LEN, DM20_PUKAMON_FQID, DM20_PUKAMON_FQID_LEN, DM20_PUKAMON_FQNAME, DM20_PUKAMON_FQNAME_LEN },
        { DM20_PUKAMON_NAME, DM20_PUKAMON_NAME_LEN, DM20_PUKAMON_ID, DM20_PUKAMON_ID_LEN, ALT_DM20_PUKAMON_FQID, ALT_DM20_PUKAMON_FQID_LEN, ALT_DM20_PUKAMON_FQNAME, ALT_DM20_PUKAMON_FQNAME_LEN },
        { DM20_PUNIMON_NAME, DM20_PUNIMON_NAME_LEN, DM20_PUNIMON_ID, DM20_PUNIMON_ID_LEN, DM20_PUNIMON_FQID, DM20_PUNIMON_FQID_LEN, DM20_PUNIMON_FQNAME, DM20_PUNIMON_FQNAME_LEN },
        { DM20_PUNIMON_NAME, DM20_PUNIMON_NAME_LEN, DM20_PUNIMON_ID, DM20_PUNIMON_ID_LEN, ALT_DM20_PUNIMON_FQID, ALT_DM20_PUNIMON_FQID_LEN, ALT_DM20_PUNIMON_FQNAME, ALT_DM20_PUNIMON_FQNAME_LEN },
        { DM20_RAREMON_NAME, DM20_RAREMON_NAME_LEN, DM20_RAREMON_ID, DM20_RAREMON_ID_LEN, DM20_RAREMON_FQID, DM20_RAREMON_FQID_LEN, DM20_RAREMON_FQNAME, DM20_RAREMON_FQNAME_LEN },
        { DM20_RAREMON_NAME, DM20_RAREMON_NAME_LEN, DM20_RAREMON_ID, DM20_RAREMON_ID_LEN, ALT_DM20_RAREMON_FQID, ALT_DM20_RAREMON_FQID_LEN, ALT_DM20_RAREMON_FQNAME, ALT_DM20_RAREMON_FQNAME_LEN },
        { DM20_RASIELMON_NAME, DM20_RASIELMON_NAME_LEN, DM20_RASIELMON_ID, DM20_RASIELMON_ID_LEN, DM20_RASIELMON_FQID, DM20_RASIELMON_FQID_LEN, DM20_RASIELMON_FQNAME, DM20_RASIELMON_FQNAME_LEN },
        { DM20_RASIELMON_NAME, DM20_RASIELMON_NAME_LEN, DM20_RASIELMON_ID, DM20_RASIELMON_ID_LEN, ALT_DM20_RASIELMON_FQID, ALT_DM20_RASIELMON_FQID_LEN, ALT_DM20_RASIELMON_FQNAME, ALT_DM20_RASIELMON_FQNAME_LEN },
        { DM20_RUST_TYRANOMON_NAME, DM20_RUST_TYRANOMON_NAME_LEN, DM20_RUST_TYRANOMON_ID, DM20_RUST_TYRANOMON_ID_LEN, DM20_RUST_TYRANOMON_FQID, DM20_RUST_TYRANOMON_FQID_LEN, DM20_RUST_TYRANOMON_FQNAME, DM20_RUST_TYRANOMON_FQNAME_LEN },
        { DM20_RUST_TYRANOMON_NAME, DM20_RUST_TYRANOMON_NAME_LEN, DM20_RUST_TYRANOMON_ID, DM20_RUST_TYRANOMON_ID_LEN, ALT_DM20_RUST_TYRANOMON_FQID, ALT_DM20_RUST_TYRANOMON_FQID_LEN, ALT_DM20_RUST_TYRANOMON_FQNAME, ALT_DM20_RUST_TYRANOMON_FQNAME_LEN },
        { DM20_SAKUMON_NAME, DM20_SAKUMON_NAME_LEN, DM20_SAKUMON_ID, DM20_SAKUMON_ID_LEN, DM20_SAKUMON_FQID, DM20_SAKUMON_FQID_LEN, DM20_SAKUMON_FQNAME, DM20_SAKUMON_FQNAME_LEN },
        { DM20_SAKUMON_NAME, DM20_SAKUMON_NAME_LEN, DM20_SAKUMON_ID, DM20_SAKUMON_ID_LEN, ALT_DM20_SAKUMON_FQID, ALT_DM20_SAKUMON_FQID_LEN, ALT_DM20_SAKUMON_FQNAME, ALT_DM20_SAKUMON_FQNAME_LEN },
        { DM20_SAKUTTOMON_NAME, DM20_SAKUTTOMON_NAME_LEN, DM20_SAKUTTOMON_ID, DM20_SAKUTTOMON_ID_LEN, DM20_SAKUTTOMON_FQID, DM20_SAKUTTOMON_FQID_LEN, DM20_SAKUTTOMON_FQNAME, DM20_SAKUTTOMON_FQNAME_LEN },
        { DM20_SAKUTTOMON_NAME, DM20_SAKUTTOMON_NAME_LEN, DM20_SAKUTTOMON_ID, DM20_SAKUTTOMON_ID_LEN, ALT_DM20_SAKUTTOMON_FQID, ALT_DM20_SAKUTTOMON_FQID_LEN, ALT_DM20_SAKUTTOMON_FQNAME, ALT_DM20_SAKUTTOMON_FQNAME_LEN },
        { DM20_SAVIOR_HACKMON_NAME, DM20_SAVIOR_HACKMON_NAME_LEN, DM20_SAVIOR_HACKMON_ID, DM20_SAVIOR_HACKMON_ID_LEN, DM20_SAVIOR_HACKMON_FQID, DM20_SAVIOR_HACKMON_FQID_LEN, DM20_SAVIOR_HACKMON_FQNAME, DM20_SAVIOR_HACKMON_FQNAME_LEN },
        { DM20_SAVIOR_HACKMON_NAME, DM20_SAVIOR_HACKMON_NAME_LEN, DM20_SAVIOR_HACKMON_ID, DM20_SAVIOR_HACKMON_ID_LEN, ALT_DM20_SAVIOR_HACKMON_FQID, ALT_DM20_SAVIOR_HACKMON_FQID_LEN, ALT_DM20_SAVIOR_HACKMON_FQNAME, ALT_DM20_SAVIOR_HACKMON_FQNAME_LEN },
        { DM20_SCUMON_NAME, DM20_SCUMON_NAME_LEN, DM20_SCUMON_ID, DM20_SCUMON_ID_LEN, DM20_SCUMON_FQID, DM20_SCUMON_FQID_LEN, DM20_SCUMON_FQNAME, DM20_SCUMON_FQNAME_LEN },
        { DM20_SCUMON_NAME, DM20_SCUMON_NAME_LEN, DM20_SCUMON_ID, DM20_SCUMON_ID_LEN, ALT_DM20_SCUMON_FQID, ALT_DM20_SCUMON_FQID_LEN, ALT_DM20_SCUMON_FQNAME, ALT_DM20_SCUMON_FQNAME_LEN },
        { DM20_SEADRAMON_NAME, DM20_SEADRAMON_NAME_LEN, DM20_SEADRAMON_ID, DM20_SEADRAMON_ID_LEN, DM20_SEADRAMON_FQID, DM20_SEADRAMON_FQID_LEN, DM20_SEADRAMON_FQNAME, DM20_SEADRAMON_FQNAME_LEN },
        { DM20_SEADRAMON_NAME, DM20_SEADRAMON_NAME_LEN, DM20_SEADRAMON_ID, DM20_SEADRAMON_ID_LEN, ALT_DM20_SEADRAMON_FQID, ALT_DM20_SEADRAMON_FQID_LEN, ALT_DM20_SEADRAMON_FQNAME, ALT_DM20_SEADRAMON_FQNAME_LEN },
        { DM20_SHELLMON_NAME, DM20_SHELLMON_NAME_LEN, DM20_SHELLMON_ID, DM20_SHELLMON_ID_LEN, DM20_SHELLMON_FQID, DM20_SHELLMON_FQID_LEN, DM20_SHELLMON_FQNAME, DM20_SHELLMON_FQNAME_LEN },
        { DM20_SHELLMON_NAME, DM20_SHELLMON_NAME_LEN, DM20_SHELLMON_ID, DM20_SHELLMON_ID_LEN, ALT_DM20_SHELLMON_FQID, ALT_DM20_SHELLMON_FQID_LEN, ALT_DM20_SHELLMON_FQNAME, ALT_DM20_SHELLMON_FQNAME_LEN },
        { DM20_SKULL_GREYMON_NAME, DM20_SKULL_GREYMON_NAME_LEN, DM20_SKULL_GREYMON_ID, DM20_SKULL_GREYMON_ID_LEN, DM20_SKULL_GREYMON_FQID, DM20_SKULL_GREYMON_FQID_LEN, DM20_SKULL_GREYMON_FQNAME, DM20_SKULL_GREYMON_FQNAME_LEN },
        { DM20_SKULL_GREYMON_NAME, DM20_SKULL_GREYMON_NAME_LEN, DM20_SKULL_GREYMON_ID, DM20_SKULL_GREYMON_ID_LEN, ALT_DM20_SKULL_GREYMON_FQID, ALT_DM20_SKULL_GREYMON_FQID_LEN, ALT_DM20_SKULL_GREYMON_FQNAME, ALT_DM20_SKULL_GREYMON_FQNAME_LEN },
        { DM20_SKULL_MAMMON_NAME, DM20_SKULL_MAMMON_NAME_LEN, DM20_SKULL_MAMMON_ID, DM20_SKULL_MAMMON_ID_LEN, DM20_SKULL_MAMMON_FQID, DM20_SKULL_MAMMON_FQID_LEN, DM20_SKULL_MAMMON_FQNAME, DM20_SKULL_MAMMON_FQNAME_LEN },
        { DM20_SKULL_MAMMON_NAME, DM20_SKULL_MAMMON_NAME_LEN, DM20_SKULL_MAMMON_ID, DM20_SKULL_MAMMON_ID_LEN, ALT_DM20_SKULL_MAMMON_FQID, ALT_DM20_SKULL_MAMMON_FQID_LEN, ALT_DM20_SKULL_MAMMON_FQNAME, ALT_DM20_SKULL_MAMMON_FQNAME_LEN },
        { DM20_SLAYERDRAMON_NAME, DM20_SLAYERDRAMON_NAME_LEN, DM20_SLAYERDRAMON_ID, DM20_SLAYERDRAMON_ID_LEN, DM20_SLAYERDRAMON_FQID, DM20_SLAYERDRAMON_FQID_LEN, DM20_SLAYERDRAMON_FQNAME, DM20_SLAYERDRAMON_FQNAME_LEN },
        { DM20_SLAYERDRAMON_NAME, DM20_SLAYERDRAMON_NAME_LEN, DM20_SLAYERDRAMON_ID, DM20_SLAYERDRAMON_ID_LEN, ALT_DM20_SLAYERDRAMON_FQID, ALT_DM20_SLAYERDRAMON_FQID_LEN, ALT_DM20_SLAYERDRAMON_FQNAME, ALT_DM20_SLAYERDRAMON_FQNAME_LEN },
        { DM20_TAICHIS_AGUMON_NAME, DM20_TAICHIS_AGUMON_NAME_LEN, DM20_TAICHIS_AGUMON_ID, DM20_TAICHIS_AGUMON_ID_LEN, DM20_TAICHIS_AGUMON_FQID, DM20_TAICHIS_AGUMON_FQID_LEN, DM20_TAICHIS_AGUMON_FQNAME, DM20_TAICHIS_AGUMON_FQNAME_LEN },
        { DM20_TAICHIS_AGUMON_NAME, DM20_TAICHIS_AGUMON_NAME_LEN, DM20_TAICHIS_AGUMON_ID, DM20_TAICHIS_AGUMON_ID_LEN, ALT_DM20_TAICHIS_AGUMON_FQID, ALT_DM20_TAICHIS_AGUMON_FQID_LEN, ALT_DM20_TAICHIS_AGUMON_FQNAME, ALT_DM20_TAICHIS_AGUMON_FQNAME_LEN },
        { DM20_TAICHIS_GREYMON_NAME, DM20_TAICHIS_GREYMON_NAME_LEN, DM20_TAICHIS_GREYMON_ID, DM20_TAICHIS_GREYMON_ID_LEN, DM20_TAICHIS_GREYMON_FQID, DM20_TAICHIS_GREYMON_FQID_LEN, DM20_TAICHIS_GREYMON_FQNAME, DM20_TAICHIS_GREYMON_FQNAME_LEN },
        { DM20_TAICHIS_GREYMON_NAME, DM20_TAICHIS_GREYMON_NAME_LEN, DM20_TAICHIS_GREYMON_ID, DM20_TAICHIS_GREYMON_ID_LEN, ALT_DM20_TAICHIS_GREYMON_FQID, ALT_DM20_TAICHIS_GREYMON_FQID_LEN, ALT_DM20_TAICHIS_GREYMON_FQNAME, ALT_DM20_TAICHIS_GREYMON_FQNAME_LEN },
        { DM20_TAICHIS_METAL_GREYMON_NAME, DM20_TAICHIS_METAL_GREYMON_NAME_LEN, DM20_TAICHIS_METAL_GREYMON_ID, DM20_TAICHIS_METAL_GREYMON_ID_LEN, DM20_TAICHIS_METAL_GREYMON_FQID, DM20_TAICHIS_METAL_GREYMON_FQID_LEN, DM20_TAICHIS_METAL_GREYMON_FQNAME, DM20_TAICHIS_METAL_GREYMON_FQNAME_LEN },
        { DM20_TAICHIS_METAL_GREYMON_NAME, DM20_TAICHIS_METAL_GREYMON_NAME_LEN, DM20_TAICHIS_METAL_GREYMON_ID, DM20_TAICHIS_METAL_GREYMON_ID_LEN, ALT_DM20_TAICHIS_METAL_GREYMON_FQID, ALT_DM20_TAICHIS_METAL_GREYMON_FQID_LEN, ALT_DM20_TAICHIS_METAL_GREYMON_FQNAME, ALT_DM20_TAICHIS_METAL_GREYMON_FQNAME_LEN },
        { DM20_TAICHIS_WAR_GREYMON_NAME, DM20_TAICHIS_WAR_GREYMON_NAME_LEN, DM20_TAICHIS_WAR_GREYMON_ID, DM20_TAICHIS_WAR_GREYMON_ID_LEN, DM20_TAICHIS_WAR_GREYMON_FQID, DM20_TAICHIS_WAR_GREYMON_FQID_LEN, DM20_TAICHIS_WAR_GREYMON_FQNAME, DM20_TAICHIS_WAR_GREYMON_FQNAME_LEN },
        { DM20_TAICHIS_WAR_GREYMON_NAME, DM20_TAICHIS_WAR_GREYMON_NAME_LEN, DM20_TAICHIS_WAR_GREYMON_ID, DM20_TAICHIS_WAR_GREYMON_ID_LEN, ALT_DM20_TAICHIS_WAR_GREYMON_FQID, ALT_DM20_TAICHIS_WAR_GREYMON_FQID_LEN, ALT_DM20_TAICHIS_WAR_GREYMON_FQNAME, ALT_DM20_TAICHIS_WAR_GREYMON_FQNAME_LEN },
        { DM20_TANEMON_NAME, DM20_TANEMON_NAME_LEN, DM20_TANEMON_ID, DM20_TANEMON_ID_LEN, DM20_TANEMON_FQID, DM20_TANEMON_FQID_LEN, DM20_TANEMON_FQNAME, DM20_TANEMON_FQNAME_LEN },
        { DM20_TANEMON_NAME, DM20_TANEMON_NAME_LEN, DM20_TANEMON_ID, DM20_TANEMON_ID_LEN, ALT_DM20_TANEMON_FQID, ALT_DM20_TANEMON_FQID_LEN, ALT_DM20_TANEMON_FQNAME, ALT_DM20_TANEMON_FQNAME_LEN },
        { DM20_TITAMON_NAME, DM20_TITAMON_NAME_LEN, DM20_TITAMON_ID, DM20_TITAMON_ID_LEN, DM20_TITAMON_FQID, DM20_TITAMON_FQID_LEN, DM20_TITAMON_FQNAME, DM20_TITAMON_FQNAME_LEN },
        { DM20_TITAMON_NAME, DM20_TITAMON_NAME_LEN, DM20_TITAMON_ID, DM20_TITAMON_ID_LEN, ALT_DM20_TITAMON_FQID, ALT_DM20_TITAMON_FQID_LEN, ALT_DM20_TITAMON_FQNAME, ALT_DM20_TITAMON_FQNAME_LEN },
        { DM20_TOKOMON_NAME, DM20_TOKOMON_NAME_LEN, DM20_TOKOMON_ID, DM20_TOKOMON_ID_LEN, DM20_TOKOMON_FQID, DM20_TOKOMON_FQID_LEN, DM20_TOKOMON_FQNAME, DM20_TOKOMON_FQNAME_LEN },
        { DM20_TOKOMON_NAME, DM20_TOKOMON_NAME_LEN, DM20_TOKOMON_ID, DM20_TOKOMON_ID_LEN, ALT_DM20_TOKOMON_FQID, ALT_DM20_TOKOMON_FQID_LEN, ALT_DM20_TOKOMON_FQNAME, ALT_DM20_TOKOMON_FQNAME_LEN },
        { DM20_TUNOMON_NAME, DM20_TUNOMON_NAME_LEN, DM20_TUNOMON_ID, DM20_TUNOMON_ID_LEN, DM20_TUNOMON_FQID, DM20_TUNOMON_FQID_LEN, DM20_TUNOMON_FQNAME, DM20_TUNOMON_FQNAME_LEN },
        { DM20_TUNOMON_NAME, DM20_TUNOMON_NAME_LEN, DM20_TUNOMON_ID, DM20_TUNOMON_ID_LEN, ALT_DM20_TUNOMON_FQID, ALT_DM20_TUNOMON_FQID_LEN, ALT_DM20_TUNOMON_FQNAME, ALT_DM20_TUNOMON_FQNAME_LEN },
        { DM20_TUSKMON_NAME, DM20_TUSKMON_NAME_LEN, DM20_TUSKMON_ID, DM20_TUSKMON_ID_LEN, DM20_TUSKMON_FQID, DM20_TUSKMON_FQID_LEN, DM20_TUSKMON_FQNAME, DM20_TUSKMON_FQNAME_LEN },
        { DM20_TUSKMON_NAME, DM20_TUSKMON_NAME_LEN, DM20_TUSKMON_ID, DM20_TUSKMON_ID_LEN, ALT_DM20_TUSKMON_FQID, ALT_DM20_TUSKMON_FQID_LEN, ALT_DM20_TUSKMON_FQNAME, ALT_DM20_TUSKMON_FQNAME_LEN },
        { DM20_TYRANOMON_NAME, DM20_TYRANOMON_NAME_LEN, DM20_TYRANOMON_ID, DM20_TYRANOMON_ID_LEN, DM20_TYRANOMON_FQID, DM20_TYRANOMON_FQID_LEN, DM20_TYRANOMON_FQNAME, DM20_TYRANOMON_FQNAME_LEN },
        { DM20_TYRANOMON_NAME, DM20_TYRANOMON_NAME_LEN, DM20_TYRANOMON_ID, DM20_TYRANOMON_ID_LEN, ALT_DM20_TYRANOMON_FQID, ALT_DM20_TYRANOMON_FQID_LEN, ALT_DM20_TYRANOMON_FQNAME, ALT_DM20_TYRANOMON_FQNAME_LEN },
        { DM20_UNIMON_NAME, DM20_UNIMON_NAME_LEN, DM20_UNIMON_ID, DM20_UNIMON_ID_LEN, DM20_UNIMON_FQID, DM20_UNIMON_FQID_LEN, DM20_UNIMON_FQNAME, DM20_UNIMON_FQNAME_LEN },
        { DM20_UNIMON_NAME, DM20_UNIMON_NAME_LEN, DM20_UNIMON_ID, DM20_UNIMON_ID_LEN, ALT_DM20_UNIMON_FQID, ALT_DM20_UNIMON_FQID_LEN, ALT_DM20_UNIMON_FQNAME, ALT_DM20_UNIMON_FQNAME_LEN },
        { DM20_VADEMON_NAME, DM20_VADEMON_NAME_LEN, DM20_VADEMON_ID, DM20_VADEMON_ID_LEN, DM20_VADEMON_FQID, DM20_VADEMON_FQID_LEN, DM20_VADEMON_FQNAME, DM20_VADEMON_FQNAME_LEN },
        { DM20_VADEMON_NAME, DM20_VADEMON_NAME_LEN, DM20_VADEMON_ID, DM20_VADEMON_ID_LEN, ALT_DM20_VADEMON_FQID, ALT_DM20_VADEMON_FQID_LEN, ALT_DM20_VADEMON_FQNAME, ALT_DM20_VADEMON_FQNAME_LEN },
        { DM20_VEGIMON_NAME, DM20_VEGIMON_NAME_LEN, DM20_VEGIMON_ID, DM20_VEGIMON_ID_LEN, DM20_VEGIMON_FQID, DM20_VEGIMON_FQID_LEN, DM20_VEGIMON_FQNAME, DM20_VEGIMON_FQNAME_LEN },
        { DM20_VEGIMON_NAME, DM20_VEGIMON_NAME_LEN, DM20_VEGIMON_ID, DM20_VEGIMON_ID_LEN, ALT_DM20_VEGIMON_FQID, ALT_DM20_VEGIMON_FQID_LEN, ALT_DM20_VEGIMON_FQNAME, ALT_DM20_VEGIMON_FQNAME_LEN },
        { DM20_WHAMON_NAME, DM20_WHAMON_NAME_LEN, DM20_WHAMON_ID, DM20_WHAMON_ID_LEN, DM20_WHAMON_FQID, DM20_WHAMON_FQID_LEN, DM20_WHAMON_FQNAME, DM20_WHAMON_FQNAME_LEN },
        { DM20_WHAMON_NAME, DM20_WHAMON_NAME_LEN, DM20_WHAMON_ID, DM20_WHAMON_ID_LEN, ALT_DM20_WHAMON_FQID, ALT_DM20_WHAMON_FQID_LEN, ALT_DM20_WHAMON_FQNAME, ALT_DM20_WHAMON_FQNAME_LEN },
        { DM20_WINGDRAMON_NAME, DM20_WINGDRAMON_NAME_LEN, DM20_WINGDRAMON_ID, DM20_WINGDRAMON_ID_LEN, DM20_WINGDRAMON_FQID, DM20_WINGDRAMON_FQID_LEN, DM20_WINGDRAMON_FQNAME, DM20_WINGDRAMON_FQNAME_LEN },
        { DM20_WINGDRAMON_NAME, DM20_WINGDRAMON_NAME_LEN, DM20_WINGDRAMON_ID, DM20_WINGDRAMON_ID_LEN, ALT_DM20_WINGDRAMON_FQID, ALT_DM20_WINGDRAMON_FQID_LEN, ALT_DM20_WINGDRAMON_FQNAME, ALT_DM20_WINGDRAMON_FQNAME_LEN },
        { DM20_YAMATOS_GABUMON_NAME, DM20_YAMATOS_GABUMON_NAME_LEN, DM20_YAMATOS_GABUMON_ID, DM20_YAMATOS_GABUMON_ID_LEN, DM20_YAMATOS_GABUMON_FQID, DM20_YAMATOS_GABUMON_FQID_LEN, DM20_YAMATOS_GABUMON_FQNAME, DM20_YAMATOS_GABUMON_FQNAME_LEN },
        { DM20_YAMATOS_GABUMON_NAME, DM20_YAMATOS_GABUMON_NAME_LEN, DM20_YAMATOS_GABUMON_ID, DM20_YAMATOS_GABUMON_ID_LEN, ALT_DM20_YAMATOS_GABUMON_FQID, ALT_DM20_YAMATOS_GABUMON_FQID_LEN, ALT_DM20_YAMATOS_GABUMON_FQNAME, ALT_DM20_YAMATOS_GABUMON_FQNAME_LEN },
        { DM20_YAMATOS_GARURUMON_NAME, DM20_YAMATOS_GARURUMON_NAME_LEN, DM20_YAMATOS_GARURUMON_ID, DM20_YAMATOS_GARURUMON_ID_LEN, DM20_YAMATOS_GARURUMON_FQID, DM20_YAMATOS_GARURUMON_FQID_LEN, DM20_YAMATOS_GARURUMON_FQNAME, DM20_YAMATOS_GARURUMON_FQNAME_LEN },
        { DM20_YAMATOS_GARURUMON_NAME, DM20_YAMATOS_GARURUMON_NAME_LEN, DM20_YAMATOS_GARURUMON_ID, DM20_YAMATOS_GARURUMON_ID_LEN, ALT_DM20_YAMATOS_GARURUMON_FQID, ALT_DM20_YAMATOS_GARURUMON_FQID_LEN, ALT_DM20_YAMATOS_GARURUMON_FQNAME, ALT_DM20_YAMATOS_GARURUMON_FQNAME_LEN },
        { DM20_YAMATOS_METAL_GARURUMON_NAME, DM20_YAMATOS_METAL_GARURUMON_NAME_LEN, DM20_YAMATOS_METAL_GARURUMON_ID, DM20_YAMATOS_METAL_GARURUMON_ID_LEN, DM20_YAMATOS_METAL_GARURUMON_FQID, DM20_YAMATOS_METAL_GARURUMON_FQID_LEN, DM20_YAMATOS_METAL_GARURUMON_FQNAME, DM20_YAMATOS_METAL_GARURUMON_FQNAME_LEN },
        { DM20_YAMATOS_METAL_GARURUMON_NAME, DM20_YAMATOS_METAL_GARURUMON_NAME_LEN, DM20_YAMATOS_METAL_GARURUMON_ID, DM20_YAMATOS_METAL_GARURUMON_ID_LEN, ALT_DM20_YAMATOS_METAL_GARURUMON_FQID, ALT_DM20_YAMATOS_METAL_GARURUMON_FQID_LEN, ALT_DM20_YAMATOS_METAL_GARURUMON_FQNAME, ALT_DM20_YAMATOS_METAL_GARURUMON_FQNAME_LEN },
        { DM20_YAMATOS_WERE_GARURUMON_NAME, DM20_YAMATOS_WERE_GARURUMON_NAME_LEN, DM20_YAMATOS_WERE_GARURUMON_ID, DM20_YAMATOS_WERE_GARURUMON_ID_LEN, DM20_YAMATOS_WERE_GARURUMON_FQID, DM20_YAMATOS_WERE_GARURUMON_FQID_LEN, DM20_YAMATOS_WERE_GARURUMON_FQNAME, DM20_YAMATOS_WERE_GARURUMON_FQNAME_LEN },
        { DM20_YAMATOS_WERE_GARURUMON_NAME, DM20_YAMATOS_WERE_GARURUMON_NAME_LEN, DM20_YAMATOS_WERE_GARURUMON_ID, DM20_YAMATOS_WERE_GARURUMON_ID_LEN, ALT_DM20_YAMATOS_WERE_GARURUMON_FQID, ALT_DM20_YAMATOS_WERE_GARURUMON_FQID_LEN, ALT_DM20_YAMATOS_WERE_GARURUMON_FQNAME, ALT_DM20_YAMATOS_WERE_GARURUMON_FQNAME_LEN },
        { DM20_YUKIDARUMON_NAME, DM20_YUKIDARUMON_NAME_LEN, DM20_YUKIDARUMON_ID, DM20_YUKIDARUMON_ID_LEN, DM20_YUKIDARUMON_FQID, DM20_YUKIDARUMON_FQID_LEN, DM20_YUKIDARUMON_FQNAME, DM20_YUKIDARUMON_FQNAME_LEN },
        { DM20_YUKIDARUMON_NAME, DM20_YUKIDARUMON_NAME_LEN, DM20_YUKIDARUMON_ID, DM20_YUKIDARUMON_ID_LEN, ALT_DM20_YUKIDARUMON_FQID, ALT_DM20_YUKIDARUMON_FQID_LEN, ALT_DM20_YUKIDARUMON_FQNAME, ALT_DM20_YUKIDARUMON_FQNAME_LEN },
        { DM20_YUKIMIBOTAMON_NAME, DM20_YUKIMIBOTAMON_NAME_LEN, DM20_YUKIMIBOTAMON_ID, DM20_YUKIMIBOTAMON_ID_LEN, DM20_YUKIMIBOTAMON_FQID, DM20_YUKIMIBOTAMON_FQID_LEN, DM20_YUKIMIBOTAMON_FQNAME, DM20_YUKIMIBOTAMON_FQNAME_LEN },
        { DM20_YUKIMIBOTAMON_NAME, DM20_YUKIMIBOTAMON_NAME_LEN, DM20_YUKIMIBOTAMON_ID, DM20_YUKIMIBOTAMON_ID_LEN, ALT_DM20_YUKIMIBOTAMON_FQID, ALT_DM20_YUKIMIBOTAMON_FQID_LEN, ALT_DM20_YUKIMIBOTAMON_FQNAME, ALT_DM20_YUKIMIBOTAMON_FQNAME_LEN },
        { DM20_YURAMON_NAME, DM20_YURAMON_NAME_LEN, DM20_YURAMON_ID, DM20_YURAMON_ID_LEN, DM20_YURAMON_FQID, DM20_YURAMON_FQID_LEN, DM20_YURAMON_FQNAME, DM20_YURAMON_FQNAME_LEN },
        { DM20_YURAMON_NAME, DM20_YURAMON_NAME_LEN, DM20_YURAMON_ID, DM20_YURAMON_ID_LEN, ALT_DM20_YURAMON_FQID, ALT_DM20_YURAMON_FQID_LEN, ALT_DM20_YURAMON_FQNAME, ALT_DM20_YURAMON_FQNAME_LEN },
        { DM20_ZUBAEAGERMON_NAME, DM20_ZUBAEAGERMON_NAME_LEN, DM20_ZUBAEAGERMON_ID, DM20_ZUBAEAGERMON_ID_LEN, DM20_ZUBAEAGERMON_FQID, DM20_ZUBAEAGERMON_FQID_LEN, DM20_ZUBAEAGERMON_FQNAME, DM20_ZUBAEAGERMON_FQNAME_LEN },
        { DM20_ZUBAEAGERMON_NAME, DM20_ZUBAEAGERMON_NAME_LEN, DM20_ZUBAEAGERMON_ID, DM20_ZUBAEAGERMON_ID_LEN, ALT_DM20_ZUBAEAGERMON_FQID, ALT_DM20_ZUBAEAGERMON_FQID_LEN, ALT_DM20_ZUBAEAGERMON_FQNAME, ALT_DM20_ZUBAEAGERMON_FQNAME_LEN },
        { DM20_ZUBAMON_NAME, DM20_ZUBAMON_NAME_LEN, DM20_ZUBAMON_ID, DM20_ZUBAMON_ID_LEN, DM20_ZUBAMON_FQID, DM20_ZUBAMON_FQID_LEN, DM20_ZUBAMON_FQNAME, DM20_ZUBAMON_FQNAME_LEN },
        { DM20_ZUBAMON_NAME, DM20_ZUBAMON_NAME_LEN, DM20_ZUBAMON_ID, DM20_ZUBAMON_ID_LEN, ALT_DM20_ZUBAMON_FQID, ALT_DM20_ZUBAMON_FQID_LEN, ALT_DM20_ZUBAMON_FQNAME, ALT_DM20_ZUBAMON_FQNAME_LEN },
        { DM20_ZURUMON_NAME, DM20_ZURUMON_NAME_LEN, DM20_ZURUMON_ID, DM20_ZURUMON_ID_LEN, DM20_ZURUMON_FQID, DM20_ZURUMON_FQID_LEN, DM20_ZURUMON_FQNAME, DM20_ZURUMON_FQNAME_LEN },
        { DM20_ZURUMON_NAME, DM20_ZURUMON_NAME_LEN, DM20_ZURUMON_ID, DM20_ZURUMON_ID_LEN, ALT_DM20_ZURUMON_FQID, ALT_DM20_ZURUMON_FQID_LEN, ALT_DM20_ZURUMON_FQNAME, ALT_DM20_ZURUMON_FQNAME_LEN },
        
    };
    static const size_t dm20_animation_names_table_size = LEN_ARRAY(dm20_animation_names_table);

    config_animation_entry_t get_config_animation_name_dm20(size_t index) {
        assert(LEN_ARRAY(dm20_animation_table) == DM20_ANIM_COUNT);
        assert(index < DM20_ANIM_COUNT);
        return dm20_animation_table[index].normal;
    }

    int config_parse_animation_name_dm20(config::config_t& config, const char *value) {
        assert(LEN_ARRAY(dm20_animation_table) == DM20_ANIM_COUNT);
        int ret = -1;
        for (size_t i = 0;ret < 0 && i < DM20_ANIM_COUNT;++i) {
            const auto& entry = dm20_animation_table[i].normal;
            const auto& alt = dm20_animation_table[i].alt;
            if (strcmp(value, entry.name) == 0 ||
                strcmp(value, entry.id) == 0 ||
                strcmp(value, entry.fqid) == 0 ||
                strcmp(value, entry.fqname) == 0 ||
                strcmp(value, alt.fqid) == 0 ||
                strcmp(value, alt.fqname) == 0) {
                config.animation_index = entry.anim_index;
                config.animation_dm_set = entry.set;
                config.animation_sprite_sheet_layout = entry.layout;
                ret = entry.anim_index;
                break;
            }
        }
        return ret;
    }
}

