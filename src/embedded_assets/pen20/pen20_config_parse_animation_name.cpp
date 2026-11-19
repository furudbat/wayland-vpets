#include "embedded_assets/embedded_image.h"
#include "embedded_assets/pen20/pen20.hpp"
#include "pen20_config_parse_animation_name.h"
#include "utils/memory.h"
#include "utils/system_memory.h"

namespace bongocat::assets {
    inline static constexpr char ALT_PEN20_AERO_V_DRAMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:aero_v_dramon";
    inline static constexpr const char* ALT_PEN20_AERO_V_DRAMON_FQID = ALT_PEN20_AERO_V_DRAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_AERO_V_DRAMON_FQID_LEN = sizeof(ALT_PEN20_AERO_V_DRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_AERO_V_DRAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Aero V-dramon";
    inline static constexpr const char* ALT_PEN20_AERO_V_DRAMON_FQNAME = ALT_PEN20_AERO_V_DRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_AERO_V_DRAMON_FQNAME_LEN = sizeof(ALT_PEN20_AERO_V_DRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_AGUMON_HAKASE_FQID_ARR[] CONFIG_STRING_SECTION = "pen:agumon_hakase";
    inline static constexpr const char* ALT_PEN20_AGUMON_HAKASE_FQID = ALT_PEN20_AGUMON_HAKASE_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_AGUMON_HAKASE_FQID_LEN = sizeof(ALT_PEN20_AGUMON_HAKASE_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_AGUMON_HAKASE_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Agumon Hakase";
    inline static constexpr const char* ALT_PEN20_AGUMON_HAKASE_FQNAME = ALT_PEN20_AGUMON_HAKASE_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_AGUMON_HAKASE_FQNAME_LEN = sizeof(ALT_PEN20_AGUMON_HAKASE_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_AGUMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:agumon";
    inline static constexpr const char* ALT_PEN20_AGUMON_FQID = ALT_PEN20_AGUMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_AGUMON_FQID_LEN = sizeof(ALT_PEN20_AGUMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_AGUMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Agumon";
    inline static constexpr const char* ALT_PEN20_AGUMON_FQNAME = ALT_PEN20_AGUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_AGUMON_FQNAME_LEN = sizeof(ALT_PEN20_AGUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_ALPHAMON_OURYUKEN_FQID_ARR[] CONFIG_STRING_SECTION = "pen:alphamon_ouryuken";
    inline static constexpr const char* ALT_PEN20_ALPHAMON_OURYUKEN_FQID = ALT_PEN20_ALPHAMON_OURYUKEN_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_ALPHAMON_OURYUKEN_FQID_LEN = sizeof(ALT_PEN20_ALPHAMON_OURYUKEN_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_ALPHAMON_OURYUKEN_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Alphamon Ouryuken";
    inline static constexpr const char* ALT_PEN20_ALPHAMON_OURYUKEN_FQNAME = ALT_PEN20_ALPHAMON_OURYUKEN_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_ALPHAMON_OURYUKEN_FQNAME_LEN = sizeof(ALT_PEN20_ALPHAMON_OURYUKEN_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_ALPHAMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:alphamon";
    inline static constexpr const char* ALT_PEN20_ALPHAMON_FQID = ALT_PEN20_ALPHAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_ALPHAMON_FQID_LEN = sizeof(ALT_PEN20_ALPHAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_ALPHAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Alphamon";
    inline static constexpr const char* ALT_PEN20_ALPHAMON_FQNAME = ALT_PEN20_ALPHAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_ALPHAMON_FQNAME_LEN = sizeof(ALT_PEN20_ALPHAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_ANDIRAMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:andiramon";
    inline static constexpr const char* ALT_PEN20_ANDIRAMON_FQID = ALT_PEN20_ANDIRAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_ANDIRAMON_FQID_LEN = sizeof(ALT_PEN20_ANDIRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_ANDIRAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Andiramon";
    inline static constexpr const char* ALT_PEN20_ANDIRAMON_FQNAME = ALT_PEN20_ANDIRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_ANDIRAMON_FQNAME_LEN = sizeof(ALT_PEN20_ANDIRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_ANDROMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:andromon";
    inline static constexpr const char* ALT_PEN20_ANDROMON_FQID = ALT_PEN20_ANDROMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_ANDROMON_FQID_LEN = sizeof(ALT_PEN20_ANDROMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_ANDROMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Andromon";
    inline static constexpr const char* ALT_PEN20_ANDROMON_FQNAME = ALT_PEN20_ANDROMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_ANDROMON_FQNAME_LEN = sizeof(ALT_PEN20_ANDROMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_ANGEMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:angemon";
    inline static constexpr const char* ALT_PEN20_ANGEMON_FQID = ALT_PEN20_ANGEMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_ANGEMON_FQID_LEN = sizeof(ALT_PEN20_ANGEMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_ANGEMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Angemon";
    inline static constexpr const char* ALT_PEN20_ANGEMON_FQNAME = ALT_PEN20_ANGEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_ANGEMON_FQNAME_LEN = sizeof(ALT_PEN20_ANGEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_ANGEWOMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:angewomon";
    inline static constexpr const char* ALT_PEN20_ANGEWOMON_FQID = ALT_PEN20_ANGEWOMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_ANGEWOMON_FQID_LEN = sizeof(ALT_PEN20_ANGEWOMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_ANGEWOMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Angewomon";
    inline static constexpr const char* ALT_PEN20_ANGEWOMON_FQNAME = ALT_PEN20_ANGEWOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_ANGEWOMON_FQNAME_LEN = sizeof(ALT_PEN20_ANGEWOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_ANOMALOCARIMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:anomalocarimon";
    inline static constexpr const char* ALT_PEN20_ANOMALOCARIMON_FQID = ALT_PEN20_ANOMALOCARIMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_ANOMALOCARIMON_FQID_LEN = sizeof(ALT_PEN20_ANOMALOCARIMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_ANOMALOCARIMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Anomalocarimon";
    inline static constexpr const char* ALT_PEN20_ANOMALOCARIMON_FQNAME = ALT_PEN20_ANOMALOCARIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_ANOMALOCARIMON_FQNAME_LEN = sizeof(ALT_PEN20_ANOMALOCARIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_ARRESTERDRAMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:arresterdramon";
    inline static constexpr const char* ALT_PEN20_ARRESTERDRAMON_FQID = ALT_PEN20_ARRESTERDRAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_ARRESTERDRAMON_FQID_LEN = sizeof(ALT_PEN20_ARRESTERDRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_ARRESTERDRAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Arresterdramon";
    inline static constexpr const char* ALT_PEN20_ARRESTERDRAMON_FQNAME = ALT_PEN20_ARRESTERDRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_ARRESTERDRAMON_FQNAME_LEN = sizeof(ALT_PEN20_ARRESTERDRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_ASTAMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:astamon";
    inline static constexpr const char* ALT_PEN20_ASTAMON_FQID = ALT_PEN20_ASTAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_ASTAMON_FQID_LEN = sizeof(ALT_PEN20_ASTAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_ASTAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Astamon";
    inline static constexpr const char* ALT_PEN20_ASTAMON_FQNAME = ALT_PEN20_ASTAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_ASTAMON_FQNAME_LEN = sizeof(ALT_PEN20_ASTAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_ASURAMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:asuramon";
    inline static constexpr const char* ALT_PEN20_ASURAMON_FQID = ALT_PEN20_ASURAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_ASURAMON_FQID_LEN = sizeof(ALT_PEN20_ASURAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_ASURAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Asuramon";
    inline static constexpr const char* ALT_PEN20_ASURAMON_FQNAME = ALT_PEN20_ASURAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_ASURAMON_FQNAME_LEN = sizeof(ALT_PEN20_ASURAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_ATLUR_KABUTERIMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:atlur_kabuterimon";
    inline static constexpr const char* ALT_PEN20_ATLUR_KABUTERIMON_FQID = ALT_PEN20_ATLUR_KABUTERIMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_ATLUR_KABUTERIMON_FQID_LEN = sizeof(ALT_PEN20_ATLUR_KABUTERIMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_ATLUR_KABUTERIMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Atlur Kabuterimon";
    inline static constexpr const char* ALT_PEN20_ATLUR_KABUTERIMON_FQNAME = ALT_PEN20_ATLUR_KABUTERIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_ATLUR_KABUTERIMON_FQNAME_LEN = sizeof(ALT_PEN20_ATLUR_KABUTERIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_BAALMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:baalmon";
    inline static constexpr const char* ALT_PEN20_BAALMON_FQID = ALT_PEN20_BAALMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_BAALMON_FQID_LEN = sizeof(ALT_PEN20_BAALMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_BAALMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Baalmon";
    inline static constexpr const char* ALT_PEN20_BAALMON_FQNAME = ALT_PEN20_BAALMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_BAALMON_FQNAME_LEN = sizeof(ALT_PEN20_BAALMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_BABYDMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:babydmon";
    inline static constexpr const char* ALT_PEN20_BABYDMON_FQID = ALT_PEN20_BABYDMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_BABYDMON_FQID_LEN = sizeof(ALT_PEN20_BABYDMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_BABYDMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Babydmon";
    inline static constexpr const char* ALT_PEN20_BABYDMON_FQNAME = ALT_PEN20_BABYDMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_BABYDMON_FQNAME_LEN = sizeof(ALT_PEN20_BABYDMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_BAKEMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:bakemon";
    inline static constexpr const char* ALT_PEN20_BAKEMON_FQID = ALT_PEN20_BAKEMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_BAKEMON_FQID_LEN = sizeof(ALT_PEN20_BAKEMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_BAKEMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Bakemon";
    inline static constexpr const char* ALT_PEN20_BAKEMON_FQNAME = ALT_PEN20_BAKEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_BAKEMON_FQNAME_LEN = sizeof(ALT_PEN20_BAKEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_BAKUMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:bakumon";
    inline static constexpr const char* ALT_PEN20_BAKUMON_FQID = ALT_PEN20_BAKUMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_BAKUMON_FQID_LEN = sizeof(ALT_PEN20_BAKUMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_BAKUMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Bakumon";
    inline static constexpr const char* ALT_PEN20_BAKUMON_FQNAME = ALT_PEN20_BAKUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_BAKUMON_FQNAME_LEN = sizeof(ALT_PEN20_BAKUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_BANCHO_LEOMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:bancho_leomon";
    inline static constexpr const char* ALT_PEN20_BANCHO_LEOMON_FQID = ALT_PEN20_BANCHO_LEOMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_BANCHO_LEOMON_FQID_LEN = sizeof(ALT_PEN20_BANCHO_LEOMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_BANCHO_LEOMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Bancho Leomon";
    inline static constexpr const char* ALT_PEN20_BANCHO_LEOMON_FQNAME = ALT_PEN20_BANCHO_LEOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_BANCHO_LEOMON_FQNAME_LEN = sizeof(ALT_PEN20_BANCHO_LEOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_BAO_HACKMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:bao_hackmon";
    inline static constexpr const char* ALT_PEN20_BAO_HACKMON_FQID = ALT_PEN20_BAO_HACKMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_BAO_HACKMON_FQID_LEN = sizeof(ALT_PEN20_BAO_HACKMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_BAO_HACKMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Bao Hackmon";
    inline static constexpr const char* ALT_PEN20_BAO_HACKMON_FQNAME = ALT_PEN20_BAO_HACKMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_BAO_HACKMON_FQNAME_LEN = sizeof(ALT_PEN20_BAO_HACKMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_BEELZEBUMON_BLAST_MODE_FQID_ARR[] CONFIG_STRING_SECTION = "pen:beelzebumon_blast_mode";
    inline static constexpr const char* ALT_PEN20_BEELZEBUMON_BLAST_MODE_FQID = ALT_PEN20_BEELZEBUMON_BLAST_MODE_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_BEELZEBUMON_BLAST_MODE_FQID_LEN = sizeof(ALT_PEN20_BEELZEBUMON_BLAST_MODE_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_BEELZEBUMON_BLAST_MODE_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Beelzebumon Blast Mode";
    inline static constexpr const char* ALT_PEN20_BEELZEBUMON_BLAST_MODE_FQNAME = ALT_PEN20_BEELZEBUMON_BLAST_MODE_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_BEELZEBUMON_BLAST_MODE_FQNAME_LEN = sizeof(ALT_PEN20_BEELZEBUMON_BLAST_MODE_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_BEOWOLFMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:beowolfmon";
    inline static constexpr const char* ALT_PEN20_BEOWOLFMON_FQID = ALT_PEN20_BEOWOLFMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_BEOWOLFMON_FQID_LEN = sizeof(ALT_PEN20_BEOWOLFMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_BEOWOLFMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Beowolfmon";
    inline static constexpr const char* ALT_PEN20_BEOWOLFMON_FQNAME = ALT_PEN20_BEOWOLFMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_BEOWOLFMON_FQNAME_LEN = sizeof(ALT_PEN20_BEOWOLFMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_BIG_MAMEMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:big_mamemon";
    inline static constexpr const char* ALT_PEN20_BIG_MAMEMON_FQID = ALT_PEN20_BIG_MAMEMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_BIG_MAMEMON_FQID_LEN = sizeof(ALT_PEN20_BIG_MAMEMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_BIG_MAMEMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Big Mamemon";
    inline static constexpr const char* ALT_PEN20_BIG_MAMEMON_FQNAME = ALT_PEN20_BIG_MAMEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_BIG_MAMEMON_FQNAME_LEN = sizeof(ALT_PEN20_BIG_MAMEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_BIRDRAMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:birdramon";
    inline static constexpr const char* ALT_PEN20_BIRDRAMON_FQID = ALT_PEN20_BIRDRAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_BIRDRAMON_FQID_LEN = sizeof(ALT_PEN20_BIRDRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_BIRDRAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Birdramon";
    inline static constexpr const char* ALT_PEN20_BIRDRAMON_FQNAME = ALT_PEN20_BIRDRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_BIRDRAMON_FQNAME_LEN = sizeof(ALT_PEN20_BIRDRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_BLOSSOMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:blossomon";
    inline static constexpr const char* ALT_PEN20_BLOSSOMON_FQID = ALT_PEN20_BLOSSOMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_BLOSSOMON_FQID_LEN = sizeof(ALT_PEN20_BLOSSOMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_BLOSSOMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Blossomon";
    inline static constexpr const char* ALT_PEN20_BLOSSOMON_FQNAME = ALT_PEN20_BLOSSOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_BLOSSOMON_FQNAME_LEN = sizeof(ALT_PEN20_BLOSSOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_BOLTMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:boltmon";
    inline static constexpr const char* ALT_PEN20_BOLTMON_FQID = ALT_PEN20_BOLTMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_BOLTMON_FQID_LEN = sizeof(ALT_PEN20_BOLTMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_BOLTMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Boltmon";
    inline static constexpr const char* ALT_PEN20_BOLTMON_FQNAME = ALT_PEN20_BOLTMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_BOLTMON_FQNAME_LEN = sizeof(ALT_PEN20_BOLTMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_BOTAMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:botamon";
    inline static constexpr const char* ALT_PEN20_BOTAMON_FQID = ALT_PEN20_BOTAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_BOTAMON_FQID_LEN = sizeof(ALT_PEN20_BOTAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_BOTAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Botamon";
    inline static constexpr const char* ALT_PEN20_BOTAMON_FQNAME = ALT_PEN20_BOTAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_BOTAMON_FQNAME_LEN = sizeof(ALT_PEN20_BOTAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_BREAKDRAMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:breakdramon";
    inline static constexpr const char* ALT_PEN20_BREAKDRAMON_FQID = ALT_PEN20_BREAKDRAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_BREAKDRAMON_FQID_LEN = sizeof(ALT_PEN20_BREAKDRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_BREAKDRAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Breakdramon";
    inline static constexpr const char* ALT_PEN20_BREAKDRAMON_FQNAME = ALT_PEN20_BREAKDRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_BREAKDRAMON_FQNAME_LEN = sizeof(ALT_PEN20_BREAKDRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_BRYWELUDRAMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:bryweludramon";
    inline static constexpr const char* ALT_PEN20_BRYWELUDRAMON_FQID = ALT_PEN20_BRYWELUDRAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_BRYWELUDRAMON_FQID_LEN = sizeof(ALT_PEN20_BRYWELUDRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_BRYWELUDRAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Bryweludramon";
    inline static constexpr const char* ALT_PEN20_BRYWELUDRAMON_FQNAME = ALT_PEN20_BRYWELUDRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_BRYWELUDRAMON_FQNAME_LEN = sizeof(ALT_PEN20_BRYWELUDRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_BUBBMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:bubbmon";
    inline static constexpr const char* ALT_PEN20_BUBBMON_FQID = ALT_PEN20_BUBBMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_BUBBMON_FQID_LEN = sizeof(ALT_PEN20_BUBBMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_BUBBMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Bubbmon";
    inline static constexpr const char* ALT_PEN20_BUBBMON_FQNAME = ALT_PEN20_BUBBMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_BUBBMON_FQNAME_LEN = sizeof(ALT_PEN20_BUBBMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_BUDMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:budmon";
    inline static constexpr const char* ALT_PEN20_BUDMON_FQID = ALT_PEN20_BUDMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_BUDMON_FQID_LEN = sizeof(ALT_PEN20_BUDMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_BUDMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Budmon";
    inline static constexpr const char* ALT_PEN20_BUDMON_FQNAME = ALT_PEN20_BUDMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_BUDMON_FQNAME_LEN = sizeof(ALT_PEN20_BUDMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_BUSHI_AGUMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:bushi_agumon";
    inline static constexpr const char* ALT_PEN20_BUSHI_AGUMON_FQID = ALT_PEN20_BUSHI_AGUMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_BUSHI_AGUMON_FQID_LEN = sizeof(ALT_PEN20_BUSHI_AGUMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_BUSHI_AGUMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Bushi Agumon";
    inline static constexpr const char* ALT_PEN20_BUSHI_AGUMON_FQNAME = ALT_PEN20_BUSHI_AGUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_BUSHI_AGUMON_FQNAME_LEN = sizeof(ALT_PEN20_BUSHI_AGUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_CANDMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:candmon";
    inline static constexpr const char* ALT_PEN20_CANDMON_FQID = ALT_PEN20_CANDMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_CANDMON_FQID_LEN = sizeof(ALT_PEN20_CANDMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_CANDMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Candmon";
    inline static constexpr const char* ALT_PEN20_CANDMON_FQNAME = ALT_PEN20_CANDMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_CANDMON_FQNAME_LEN = sizeof(ALT_PEN20_CANDMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_CAPRIMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:caprimon";
    inline static constexpr const char* ALT_PEN20_CAPRIMON_FQID = ALT_PEN20_CAPRIMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_CAPRIMON_FQID_LEN = sizeof(ALT_PEN20_CAPRIMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_CAPRIMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Caprimon";
    inline static constexpr const char* ALT_PEN20_CAPRIMON_FQNAME = ALT_PEN20_CAPRIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_CAPRIMON_FQNAME_LEN = sizeof(ALT_PEN20_CAPRIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_CHAOSMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:chaosmon";
    inline static constexpr const char* ALT_PEN20_CHAOSMON_FQID = ALT_PEN20_CHAOSMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_CHAOSMON_FQID_LEN = sizeof(ALT_PEN20_CHAOSMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_CHAOSMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Chaosmon";
    inline static constexpr const char* ALT_PEN20_CHAOSMON_FQNAME = ALT_PEN20_CHAOSMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_CHAOSMON_FQNAME_LEN = sizeof(ALT_PEN20_CHAOSMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_CHERUBIMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:cherubimon";
    inline static constexpr const char* ALT_PEN20_CHERUBIMON_FQID = ALT_PEN20_CHERUBIMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_CHERUBIMON_FQID_LEN = sizeof(ALT_PEN20_CHERUBIMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_CHERUBIMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Cherubimon";
    inline static constexpr const char* ALT_PEN20_CHERUBIMON_FQNAME = ALT_PEN20_CHERUBIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_CHERUBIMON_FQNAME_LEN = sizeof(ALT_PEN20_CHERUBIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_CHIBIMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:chibimon";
    inline static constexpr const char* ALT_PEN20_CHIBIMON_FQID = ALT_PEN20_CHIBIMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_CHIBIMON_FQID_LEN = sizeof(ALT_PEN20_CHIBIMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_CHIBIMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Chibimon";
    inline static constexpr const char* ALT_PEN20_CHIBIMON_FQNAME = ALT_PEN20_CHIBIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_CHIBIMON_FQNAME_LEN = sizeof(ALT_PEN20_CHIBIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_CHICOMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:chicomon";
    inline static constexpr const char* ALT_PEN20_CHICOMON_FQID = ALT_PEN20_CHICOMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_CHICOMON_FQID_LEN = sizeof(ALT_PEN20_CHICOMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_CHICOMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Chicomon";
    inline static constexpr const char* ALT_PEN20_CHICOMON_FQNAME = ALT_PEN20_CHICOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_CHICOMON_FQNAME_LEN = sizeof(ALT_PEN20_CHICOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_CHOCOMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:chocomon";
    inline static constexpr const char* ALT_PEN20_CHOCOMON_FQID = ALT_PEN20_CHOCOMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_CHOCOMON_FQID_LEN = sizeof(ALT_PEN20_CHOCOMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_CHOCOMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Chocomon";
    inline static constexpr const char* ALT_PEN20_CHOCOMON_FQNAME = ALT_PEN20_CHOCOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_CHOCOMON_FQNAME_LEN = sizeof(ALT_PEN20_CHOCOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_CHOROMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:choromon";
    inline static constexpr const char* ALT_PEN20_CHOROMON_FQID = ALT_PEN20_CHOROMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_CHOROMON_FQID_LEN = sizeof(ALT_PEN20_CHOROMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_CHOROMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Choromon";
    inline static constexpr const char* ALT_PEN20_CHOROMON_FQNAME = ALT_PEN20_CHOROMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_CHOROMON_FQNAME_LEN = sizeof(ALT_PEN20_CHOROMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_CLOCKMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:clockmon";
    inline static constexpr const char* ALT_PEN20_CLOCKMON_FQID = ALT_PEN20_CLOCKMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_CLOCKMON_FQID_LEN = sizeof(ALT_PEN20_CLOCKMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_CLOCKMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Clockmon";
    inline static constexpr const char* ALT_PEN20_CLOCKMON_FQNAME = ALT_PEN20_CLOCKMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_CLOCKMON_FQNAME_LEN = sizeof(ALT_PEN20_CLOCKMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_COCOMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:cocomon";
    inline static constexpr const char* ALT_PEN20_COCOMON_FQID = ALT_PEN20_COCOMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_COCOMON_FQID_LEN = sizeof(ALT_PEN20_COCOMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_COCOMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Cocomon";
    inline static constexpr const char* ALT_PEN20_COCOMON_FQNAME = ALT_PEN20_COCOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_COCOMON_FQNAME_LEN = sizeof(ALT_PEN20_COCOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_COELAMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:coelamon";
    inline static constexpr const char* ALT_PEN20_COELAMON_FQID = ALT_PEN20_COELAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_COELAMON_FQID_LEN = sizeof(ALT_PEN20_COELAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_COELAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Coelamon";
    inline static constexpr const char* ALT_PEN20_COELAMON_FQNAME = ALT_PEN20_COELAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_COELAMON_FQNAME_LEN = sizeof(ALT_PEN20_COELAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_COREDRAMON_BLUE_FQID_ARR[] CONFIG_STRING_SECTION = "pen:coredramon_blue";
    inline static constexpr const char* ALT_PEN20_COREDRAMON_BLUE_FQID = ALT_PEN20_COREDRAMON_BLUE_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_COREDRAMON_BLUE_FQID_LEN = sizeof(ALT_PEN20_COREDRAMON_BLUE_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_COREDRAMON_BLUE_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Coredramon (Blue)";
    inline static constexpr const char* ALT_PEN20_COREDRAMON_BLUE_FQNAME = ALT_PEN20_COREDRAMON_BLUE_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_COREDRAMON_BLUE_FQNAME_LEN = sizeof(ALT_PEN20_COREDRAMON_BLUE_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_COREDRAMON_GREEN_FQID_ARR[] CONFIG_STRING_SECTION = "pen:coredramon_green";
    inline static constexpr const char* ALT_PEN20_COREDRAMON_GREEN_FQID = ALT_PEN20_COREDRAMON_GREEN_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_COREDRAMON_GREEN_FQID_LEN = sizeof(ALT_PEN20_COREDRAMON_GREEN_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_COREDRAMON_GREEN_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Coredramon (Green)";
    inline static constexpr const char* ALT_PEN20_COREDRAMON_GREEN_FQNAME = ALT_PEN20_COREDRAMON_GREEN_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_COREDRAMON_GREEN_FQNAME_LEN = sizeof(ALT_PEN20_COREDRAMON_GREEN_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_COTSUCOMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:cotsucomon";
    inline static constexpr const char* ALT_PEN20_COTSUCOMON_FQID = ALT_PEN20_COTSUCOMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_COTSUCOMON_FQID_LEN = sizeof(ALT_PEN20_COTSUCOMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_COTSUCOMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Cotsucomon";
    inline static constexpr const char* ALT_PEN20_COTSUCOMON_FQNAME = ALT_PEN20_COTSUCOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_COTSUCOMON_FQNAME_LEN = sizeof(ALT_PEN20_COTSUCOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_CYBERDRAMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:cyberdramon";
    inline static constexpr const char* ALT_PEN20_CYBERDRAMON_FQID = ALT_PEN20_CYBERDRAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_CYBERDRAMON_FQID_LEN = sizeof(ALT_PEN20_CYBERDRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_CYBERDRAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Cyberdramon";
    inline static constexpr const char* ALT_PEN20_CYBERDRAMON_FQNAME = ALT_PEN20_CYBERDRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_CYBERDRAMON_FQNAME_LEN = sizeof(ALT_PEN20_CYBERDRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_DAGOMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:dagomon";
    inline static constexpr const char* ALT_PEN20_DAGOMON_FQID = ALT_PEN20_DAGOMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_DAGOMON_FQID_LEN = sizeof(ALT_PEN20_DAGOMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_DAGOMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Dagomon";
    inline static constexpr const char* ALT_PEN20_DAGOMON_FQNAME = ALT_PEN20_DAGOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_DAGOMON_FQNAME_LEN = sizeof(ALT_PEN20_DAGOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_DARKDRAMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:darkdramon";
    inline static constexpr const char* ALT_PEN20_DARKDRAMON_FQID = ALT_PEN20_DARKDRAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_DARKDRAMON_FQID_LEN = sizeof(ALT_PEN20_DARKDRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_DARKDRAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Darkdramon";
    inline static constexpr const char* ALT_PEN20_DARKDRAMON_FQNAME = ALT_PEN20_DARKDRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_DARKDRAMON_FQNAME_LEN = sizeof(ALT_PEN20_DARKDRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_DARK_KNIGHTMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:dark_knightmon";
    inline static constexpr const char* ALT_PEN20_DARK_KNIGHTMON_FQID = ALT_PEN20_DARK_KNIGHTMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_DARK_KNIGHTMON_FQID_LEN = sizeof(ALT_PEN20_DARK_KNIGHTMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_DARK_KNIGHTMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Dark Knightmon";
    inline static constexpr const char* ALT_PEN20_DARK_KNIGHTMON_FQNAME = ALT_PEN20_DARK_KNIGHTMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_DARK_KNIGHTMON_FQNAME_LEN = sizeof(ALT_PEN20_DARK_KNIGHTMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_DEATH_MERAMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:death_meramon";
    inline static constexpr const char* ALT_PEN20_DEATH_MERAMON_FQID = ALT_PEN20_DEATH_MERAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_DEATH_MERAMON_FQID_LEN = sizeof(ALT_PEN20_DEATH_MERAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_DEATH_MERAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Death Meramon";
    inline static constexpr const char* ALT_PEN20_DEATH_MERAMON_FQNAME = ALT_PEN20_DEATH_MERAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_DEATH_MERAMON_FQNAME_LEN = sizeof(ALT_PEN20_DEATH_MERAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_DELUMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:delumon";
    inline static constexpr const char* ALT_PEN20_DELUMON_FQID = ALT_PEN20_DELUMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_DELUMON_FQID_LEN = sizeof(ALT_PEN20_DELUMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_DELUMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Delumon";
    inline static constexpr const char* ALT_PEN20_DELUMON_FQNAME = ALT_PEN20_DELUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_DELUMON_FQNAME_LEN = sizeof(ALT_PEN20_DELUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_DEVIDRAMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:devidramon";
    inline static constexpr const char* ALT_PEN20_DEVIDRAMON_FQID = ALT_PEN20_DEVIDRAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_DEVIDRAMON_FQID_LEN = sizeof(ALT_PEN20_DEVIDRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_DEVIDRAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Devidramon";
    inline static constexpr const char* ALT_PEN20_DEVIDRAMON_FQNAME = ALT_PEN20_DEVIDRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_DEVIDRAMON_FQNAME_LEN = sizeof(ALT_PEN20_DEVIDRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_DEVIMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:devimon";
    inline static constexpr const char* ALT_PEN20_DEVIMON_FQID = ALT_PEN20_DEVIMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_DEVIMON_FQID_LEN = sizeof(ALT_PEN20_DEVIMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_DEVIMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Devimon";
    inline static constexpr const char* ALT_PEN20_DEVIMON_FQNAME = ALT_PEN20_DEVIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_DEVIMON_FQNAME_LEN = sizeof(ALT_PEN20_DEVIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_DODOMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:dodomon";
    inline static constexpr const char* ALT_PEN20_DODOMON_FQID = ALT_PEN20_DODOMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_DODOMON_FQID_LEN = sizeof(ALT_PEN20_DODOMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_DODOMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Dodomon";
    inline static constexpr const char* ALT_PEN20_DODOMON_FQNAME = ALT_PEN20_DODOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_DODOMON_FQNAME_LEN = sizeof(ALT_PEN20_DODOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_DOKUGUMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:dokugumon";
    inline static constexpr const char* ALT_PEN20_DOKUGUMON_FQID = ALT_PEN20_DOKUGUMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_DOKUGUMON_FQID_LEN = sizeof(ALT_PEN20_DOKUGUMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_DOKUGUMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Dokugumon";
    inline static constexpr const char* ALT_PEN20_DOKUGUMON_FQNAME = ALT_PEN20_DOKUGUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_DOKUGUMON_FQNAME_LEN = sizeof(ALT_PEN20_DOKUGUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_DORIMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:dorimon";
    inline static constexpr const char* ALT_PEN20_DORIMON_FQID = ALT_PEN20_DORIMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_DORIMON_FQID_LEN = sizeof(ALT_PEN20_DORIMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_DORIMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Dorimon";
    inline static constexpr const char* ALT_PEN20_DORIMON_FQNAME = ALT_PEN20_DORIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_DORIMON_FQNAME_LEN = sizeof(ALT_PEN20_DORIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_DORUGAMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:dorugamon";
    inline static constexpr const char* ALT_PEN20_DORUGAMON_FQID = ALT_PEN20_DORUGAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_DORUGAMON_FQID_LEN = sizeof(ALT_PEN20_DORUGAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_DORUGAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:DORUgamon";
    inline static constexpr const char* ALT_PEN20_DORUGAMON_FQNAME = ALT_PEN20_DORUGAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_DORUGAMON_FQNAME_LEN = sizeof(ALT_PEN20_DORUGAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_DORUGORAMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:dorugoramon";
    inline static constexpr const char* ALT_PEN20_DORUGORAMON_FQID = ALT_PEN20_DORUGORAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_DORUGORAMON_FQID_LEN = sizeof(ALT_PEN20_DORUGORAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_DORUGORAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:DORUgoramon";
    inline static constexpr const char* ALT_PEN20_DORUGORAMON_FQNAME = ALT_PEN20_DORUGORAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_DORUGORAMON_FQNAME_LEN = sizeof(ALT_PEN20_DORUGORAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_DORUGUREMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:doruguremon";
    inline static constexpr const char* ALT_PEN20_DORUGUREMON_FQID = ALT_PEN20_DORUGUREMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_DORUGUREMON_FQID_LEN = sizeof(ALT_PEN20_DORUGUREMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_DORUGUREMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:DORUguremon";
    inline static constexpr const char* ALT_PEN20_DORUGUREMON_FQNAME = ALT_PEN20_DORUGUREMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_DORUGUREMON_FQNAME_LEN = sizeof(ALT_PEN20_DORUGUREMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_DORUMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:dorumon";
    inline static constexpr const char* ALT_PEN20_DORUMON_FQID = ALT_PEN20_DORUMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_DORUMON_FQID_LEN = sizeof(ALT_PEN20_DORUMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_DORUMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:DORUmon";
    inline static constexpr const char* ALT_PEN20_DORUMON_FQNAME = ALT_PEN20_DORUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_DORUMON_FQNAME_LEN = sizeof(ALT_PEN20_DORUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_DRACOMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:dracomon";
    inline static constexpr const char* ALT_PEN20_DRACOMON_FQID = ALT_PEN20_DRACOMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_DRACOMON_FQID_LEN = sizeof(ALT_PEN20_DRACOMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_DRACOMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Dracomon";
    inline static constexpr const char* ALT_PEN20_DRACOMON_FQNAME = ALT_PEN20_DRACOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_DRACOMON_FQNAME_LEN = sizeof(ALT_PEN20_DRACOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_DURAMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:duramon";
    inline static constexpr const char* ALT_PEN20_DURAMON_FQID = ALT_PEN20_DURAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_DURAMON_FQID_LEN = sizeof(ALT_PEN20_DURAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_DURAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Duramon";
    inline static constexpr const char* ALT_PEN20_DURAMON_FQNAME = ALT_PEN20_DURAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_DURAMON_FQNAME_LEN = sizeof(ALT_PEN20_DURAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_DURANDAMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:durandamon";
    inline static constexpr const char* ALT_PEN20_DURANDAMON_FQID = ALT_PEN20_DURANDAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_DURANDAMON_FQID_LEN = sizeof(ALT_PEN20_DURANDAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_DURANDAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Durandamon";
    inline static constexpr const char* ALT_PEN20_DURANDAMON_FQNAME = ALT_PEN20_DURANDAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_DURANDAMON_FQNAME_LEN = sizeof(ALT_PEN20_DURANDAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_EBIDRAMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:ebidramon";
    inline static constexpr const char* ALT_PEN20_EBIDRAMON_FQID = ALT_PEN20_EBIDRAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_EBIDRAMON_FQID_LEN = sizeof(ALT_PEN20_EBIDRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_EBIDRAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Ebidramon";
    inline static constexpr const char* ALT_PEN20_EBIDRAMON_FQNAME = ALT_PEN20_EBIDRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_EBIDRAMON_FQNAME_LEN = sizeof(ALT_PEN20_EBIDRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_ETEMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:etemon";
    inline static constexpr const char* ALT_PEN20_ETEMON_FQID = ALT_PEN20_ETEMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_ETEMON_FQID_LEN = sizeof(ALT_PEN20_ETEMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_ETEMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Etemon";
    inline static constexpr const char* ALT_PEN20_ETEMON_FQNAME = ALT_PEN20_ETEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_ETEMON_FQNAME_LEN = sizeof(ALT_PEN20_ETEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_EXAMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:examon";
    inline static constexpr const char* ALT_PEN20_EXAMON_FQID = ALT_PEN20_EXAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_EXAMON_FQID_LEN = sizeof(ALT_PEN20_EXAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_EXAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Examon";
    inline static constexpr const char* ALT_PEN20_EXAMON_FQNAME = ALT_PEN20_EXAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_EXAMON_FQNAME_LEN = sizeof(ALT_PEN20_EXAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_FANTOMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:fantomon";
    inline static constexpr const char* ALT_PEN20_FANTOMON_FQID = ALT_PEN20_FANTOMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_FANTOMON_FQID_LEN = sizeof(ALT_PEN20_FANTOMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_FANTOMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Fantomon";
    inline static constexpr const char* ALT_PEN20_FANTOMON_FQNAME = ALT_PEN20_FANTOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_FANTOMON_FQNAME_LEN = sizeof(ALT_PEN20_FANTOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_FLORAMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:floramon";
    inline static constexpr const char* ALT_PEN20_FLORAMON_FQID = ALT_PEN20_FLORAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_FLORAMON_FQID_LEN = sizeof(ALT_PEN20_FLORAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_FLORAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Floramon";
    inline static constexpr const char* ALT_PEN20_FLORAMON_FQNAME = ALT_PEN20_FLORAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_FLORAMON_FQNAME_LEN = sizeof(ALT_PEN20_FLORAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_FUFUMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:fufumon";
    inline static constexpr const char* ALT_PEN20_FUFUMON_FQID = ALT_PEN20_FUFUMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_FUFUMON_FQID_LEN = sizeof(ALT_PEN20_FUFUMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_FUFUMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Fufumon";
    inline static constexpr const char* ALT_PEN20_FUFUMON_FQNAME = ALT_PEN20_FUFUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_FUFUMON_FQNAME_LEN = sizeof(ALT_PEN20_FUFUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_GABUMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:gabumon";
    inline static constexpr const char* ALT_PEN20_GABUMON_FQID = ALT_PEN20_GABUMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_GABUMON_FQID_LEN = sizeof(ALT_PEN20_GABUMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_GABUMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Gabumon";
    inline static constexpr const char* ALT_PEN20_GABUMON_FQNAME = ALT_PEN20_GABUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_GABUMON_FQNAME_LEN = sizeof(ALT_PEN20_GABUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_GALGOMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:galgomon";
    inline static constexpr const char* ALT_PEN20_GALGOMON_FQID = ALT_PEN20_GALGOMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_GALGOMON_FQID_LEN = sizeof(ALT_PEN20_GALGOMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_GALGOMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Galgomon";
    inline static constexpr const char* ALT_PEN20_GALGOMON_FQNAME = ALT_PEN20_GALGOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_GALGOMON_FQNAME_LEN = sizeof(ALT_PEN20_GALGOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_GANIMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:ganimon";
    inline static constexpr const char* ALT_PEN20_GANIMON_FQID = ALT_PEN20_GANIMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_GANIMON_FQID_LEN = sizeof(ALT_PEN20_GANIMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_GANIMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Ganimon";
    inline static constexpr const char* ALT_PEN20_GANIMON_FQNAME = ALT_PEN20_GANIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_GANIMON_FQNAME_LEN = sizeof(ALT_PEN20_GANIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_GARUDAMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:garudamon";
    inline static constexpr const char* ALT_PEN20_GARUDAMON_FQID = ALT_PEN20_GARUDAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_GARUDAMON_FQID_LEN = sizeof(ALT_PEN20_GARUDAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_GARUDAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Garudamon";
    inline static constexpr const char* ALT_PEN20_GARUDAMON_FQNAME = ALT_PEN20_GARUDAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_GARUDAMON_FQNAME_LEN = sizeof(ALT_PEN20_GARUDAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_GARURUMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:garurumon";
    inline static constexpr const char* ALT_PEN20_GARURUMON_FQID = ALT_PEN20_GARURUMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_GARURUMON_FQID_LEN = sizeof(ALT_PEN20_GARURUMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_GARURUMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Garurumon";
    inline static constexpr const char* ALT_PEN20_GARURUMON_FQNAME = ALT_PEN20_GARURUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_GARURUMON_FQNAME_LEN = sizeof(ALT_PEN20_GARURUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_GEKOMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:gekomon";
    inline static constexpr const char* ALT_PEN20_GEKOMON_FQID = ALT_PEN20_GEKOMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_GEKOMON_FQID_LEN = sizeof(ALT_PEN20_GEKOMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_GEKOMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Gekomon";
    inline static constexpr const char* ALT_PEN20_GEKOMON_FQNAME = ALT_PEN20_GEKOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_GEKOMON_FQNAME_LEN = sizeof(ALT_PEN20_GEKOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_GERBEMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:gerbemon";
    inline static constexpr const char* ALT_PEN20_GERBEMON_FQID = ALT_PEN20_GERBEMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_GERBEMON_FQID_LEN = sizeof(ALT_PEN20_GERBEMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_GERBEMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Gerbemon";
    inline static constexpr const char* ALT_PEN20_GERBEMON_FQNAME = ALT_PEN20_GERBEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_GERBEMON_FQNAME_LEN = sizeof(ALT_PEN20_GERBEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_GESOMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:gesomon";
    inline static constexpr const char* ALT_PEN20_GESOMON_FQID = ALT_PEN20_GESOMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_GESOMON_FQID_LEN = sizeof(ALT_PEN20_GESOMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_GESOMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Gesomon";
    inline static constexpr const char* ALT_PEN20_GESOMON_FQNAME = ALT_PEN20_GESOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_GESOMON_FQNAME_LEN = sizeof(ALT_PEN20_GESOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_GINRYUMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:ginryumon";
    inline static constexpr const char* ALT_PEN20_GINRYUMON_FQID = ALT_PEN20_GINRYUMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_GINRYUMON_FQID_LEN = sizeof(ALT_PEN20_GINRYUMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_GINRYUMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Ginryumon";
    inline static constexpr const char* ALT_PEN20_GINRYUMON_FQNAME = ALT_PEN20_GINRYUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_GINRYUMON_FQNAME_LEN = sizeof(ALT_PEN20_GINRYUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_GOMAMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:gomamon";
    inline static constexpr const char* ALT_PEN20_GOMAMON_FQID = ALT_PEN20_GOMAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_GOMAMON_FQID_LEN = sizeof(ALT_PEN20_GOMAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_GOMAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Gomamon";
    inline static constexpr const char* ALT_PEN20_GOMAMON_FQNAME = ALT_PEN20_GOMAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_GOMAMON_FQNAME_LEN = sizeof(ALT_PEN20_GOMAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_GOTTSUMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:gottsumon";
    inline static constexpr const char* ALT_PEN20_GOTTSUMON_FQID = ALT_PEN20_GOTTSUMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_GOTTSUMON_FQID_LEN = sizeof(ALT_PEN20_GOTTSUMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_GOTTSUMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Gottsumon";
    inline static constexpr const char* ALT_PEN20_GOTTSUMON_FQNAME = ALT_PEN20_GOTTSUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_GOTTSUMON_FQNAME_LEN = sizeof(ALT_PEN20_GOTTSUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_GREYMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:greymon";
    inline static constexpr const char* ALT_PEN20_GREYMON_FQID = ALT_PEN20_GREYMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_GREYMON_FQID_LEN = sizeof(ALT_PEN20_GREYMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_GREYMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Greymon";
    inline static constexpr const char* ALT_PEN20_GREYMON_FQNAME = ALT_PEN20_GREYMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_GREYMON_FQNAME_LEN = sizeof(ALT_PEN20_GREYMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_GRIFFOMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:griffomon";
    inline static constexpr const char* ALT_PEN20_GRIFFOMON_FQID = ALT_PEN20_GRIFFOMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_GRIFFOMON_FQID_LEN = sizeof(ALT_PEN20_GRIFFOMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_GRIFFOMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Griffomon";
    inline static constexpr const char* ALT_PEN20_GRIFFOMON_FQNAME = ALT_PEN20_GRIFFOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_GRIFFOMON_FQNAME_LEN = sizeof(ALT_PEN20_GRIFFOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_GROUNDRAMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:groundramon";
    inline static constexpr const char* ALT_PEN20_GROUNDRAMON_FQID = ALT_PEN20_GROUNDRAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_GROUNDRAMON_FQID_LEN = sizeof(ALT_PEN20_GROUNDRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_GROUNDRAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Groundramon";
    inline static constexpr const char* ALT_PEN20_GROUNDRAMON_FQNAME = ALT_PEN20_GROUNDRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_GROUNDRAMON_FQNAME_LEN = sizeof(ALT_PEN20_GROUNDRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_GROWMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:growmon";
    inline static constexpr const char* ALT_PEN20_GROWMON_FQID = ALT_PEN20_GROWMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_GROWMON_FQID_LEN = sizeof(ALT_PEN20_GROWMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_GROWMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Growmon";
    inline static constexpr const char* ALT_PEN20_GROWMON_FQNAME = ALT_PEN20_GROWMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_GROWMON_FQNAME_LEN = sizeof(ALT_PEN20_GROWMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_GUARDROMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:guardromon";
    inline static constexpr const char* ALT_PEN20_GUARDROMON_FQID = ALT_PEN20_GUARDROMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_GUARDROMON_FQID_LEN = sizeof(ALT_PEN20_GUARDROMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_GUARDROMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Guardromon";
    inline static constexpr const char* ALT_PEN20_GUARDROMON_FQNAME = ALT_PEN20_GUARDROMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_GUARDROMON_FQNAME_LEN = sizeof(ALT_PEN20_GUARDROMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_GUILMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:guilmon";
    inline static constexpr const char* ALT_PEN20_GUILMON_FQID = ALT_PEN20_GUILMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_GUILMON_FQID_LEN = sizeof(ALT_PEN20_GUILMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_GUILMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Guilmon";
    inline static constexpr const char* ALT_PEN20_GUILMON_FQNAME = ALT_PEN20_GUILMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_GUILMON_FQNAME_LEN = sizeof(ALT_PEN20_GUILMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_GUMMYMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:gummymon";
    inline static constexpr const char* ALT_PEN20_GUMMYMON_FQID = ALT_PEN20_GUMMYMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_GUMMYMON_FQID_LEN = sizeof(ALT_PEN20_GUMMYMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_GUMMYMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Gummymon";
    inline static constexpr const char* ALT_PEN20_GUMMYMON_FQNAME = ALT_PEN20_GUMMYMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_GUMMYMON_FQNAME_LEN = sizeof(ALT_PEN20_GUMMYMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_HACKMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:hackmon";
    inline static constexpr const char* ALT_PEN20_HACKMON_FQID = ALT_PEN20_HACKMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_HACKMON_FQID_LEN = sizeof(ALT_PEN20_HACKMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_HACKMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Hackmon";
    inline static constexpr const char* ALT_PEN20_HACKMON_FQNAME = ALT_PEN20_HACKMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_HACKMON_FQNAME_LEN = sizeof(ALT_PEN20_HACKMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_HAGURUMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:hagurumon";
    inline static constexpr const char* ALT_PEN20_HAGURUMON_FQID = ALT_PEN20_HAGURUMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_HAGURUMON_FQID_LEN = sizeof(ALT_PEN20_HAGURUMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_HAGURUMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Hagurumon";
    inline static constexpr const char* ALT_PEN20_HAGURUMON_FQNAME = ALT_PEN20_HAGURUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_HAGURUMON_FQNAME_LEN = sizeof(ALT_PEN20_HAGURUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_HANGYOMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:hangyomon";
    inline static constexpr const char* ALT_PEN20_HANGYOMON_FQID = ALT_PEN20_HANGYOMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_HANGYOMON_FQID_LEN = sizeof(ALT_PEN20_HANGYOMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_HANGYOMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Hangyomon";
    inline static constexpr const char* ALT_PEN20_HANGYOMON_FQNAME = ALT_PEN20_HANGYOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_HANGYOMON_FQNAME_LEN = sizeof(ALT_PEN20_HANGYOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_HANUMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:hanumon";
    inline static constexpr const char* ALT_PEN20_HANUMON_FQID = ALT_PEN20_HANUMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_HANUMON_FQID_LEN = sizeof(ALT_PEN20_HANUMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_HANUMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Hanumon";
    inline static constexpr const char* ALT_PEN20_HANUMON_FQNAME = ALT_PEN20_HANUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_HANUMON_FQNAME_LEN = sizeof(ALT_PEN20_HANUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_HERAKLE_KABUTERIMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:herakle_kabuterimon";
    inline static constexpr const char* ALT_PEN20_HERAKLE_KABUTERIMON_FQID = ALT_PEN20_HERAKLE_KABUTERIMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_HERAKLE_KABUTERIMON_FQID_LEN = sizeof(ALT_PEN20_HERAKLE_KABUTERIMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_HERAKLE_KABUTERIMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Herakle Kabuterimon";
    inline static constexpr const char* ALT_PEN20_HERAKLE_KABUTERIMON_FQNAME = ALT_PEN20_HERAKLE_KABUTERIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_HERAKLE_KABUTERIMON_FQNAME_LEN = sizeof(ALT_PEN20_HERAKLE_KABUTERIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_HISYARYUMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:hisyaryumon";
    inline static constexpr const char* ALT_PEN20_HISYARYUMON_FQID = ALT_PEN20_HISYARYUMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_HISYARYUMON_FQID_LEN = sizeof(ALT_PEN20_HISYARYUMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_HISYARYUMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Hisyaryumon";
    inline static constexpr const char* ALT_PEN20_HISYARYUMON_FQNAME = ALT_PEN20_HISYARYUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_HISYARYUMON_FQNAME_LEN = sizeof(ALT_PEN20_HISYARYUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_HOLY_ANGEMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:holy_angemon";
    inline static constexpr const char* ALT_PEN20_HOLY_ANGEMON_FQID = ALT_PEN20_HOLY_ANGEMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_HOLY_ANGEMON_FQID_LEN = sizeof(ALT_PEN20_HOLY_ANGEMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_HOLY_ANGEMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Holy Angemon";
    inline static constexpr const char* ALT_PEN20_HOLY_ANGEMON_FQNAME = ALT_PEN20_HOLY_ANGEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_HOLY_ANGEMON_FQNAME_LEN = sizeof(ALT_PEN20_HOLY_ANGEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_HOLYDRAMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:holydramon";
    inline static constexpr const char* ALT_PEN20_HOLYDRAMON_FQID = ALT_PEN20_HOLYDRAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_HOLYDRAMON_FQID_LEN = sizeof(ALT_PEN20_HOLYDRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_HOLYDRAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Holydramon";
    inline static constexpr const char* ALT_PEN20_HOLYDRAMON_FQNAME = ALT_PEN20_HOLYDRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_HOLYDRAMON_FQNAME_LEN = sizeof(ALT_PEN20_HOLYDRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_HOUOUMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:hououmon";
    inline static constexpr const char* ALT_PEN20_HOUOUMON_FQID = ALT_PEN20_HOUOUMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_HOUOUMON_FQID_LEN = sizeof(ALT_PEN20_HOUOUMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_HOUOUMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Hououmon";
    inline static constexpr const char* ALT_PEN20_HOUOUMON_FQNAME = ALT_PEN20_HOUOUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_HOUOUMON_FQNAME_LEN = sizeof(ALT_PEN20_HOUOUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_IGAMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:igamon";
    inline static constexpr const char* ALT_PEN20_IGAMON_FQID = ALT_PEN20_IGAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_IGAMON_FQID_LEN = sizeof(ALT_PEN20_IGAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_IGAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Igamon";
    inline static constexpr const char* ALT_PEN20_IGAMON_FQNAME = ALT_PEN20_IGAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_IGAMON_FQNAME_LEN = sizeof(ALT_PEN20_IGAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_IKKAKUMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:ikkakumon";
    inline static constexpr const char* ALT_PEN20_IKKAKUMON_FQID = ALT_PEN20_IKKAKUMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_IKKAKUMON_FQID_LEN = sizeof(ALT_PEN20_IKKAKUMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_IKKAKUMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Ikkakumon";
    inline static constexpr const char* ALT_PEN20_IKKAKUMON_FQNAME = ALT_PEN20_IKKAKUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_IKKAKUMON_FQNAME_LEN = sizeof(ALT_PEN20_IKKAKUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_IMPERIALDRAMON_FIGHTER_MODE_FQID_ARR[] CONFIG_STRING_SECTION = "pen:imperialdramon_fighter_mode";
    inline static constexpr const char* ALT_PEN20_IMPERIALDRAMON_FIGHTER_MODE_FQID = ALT_PEN20_IMPERIALDRAMON_FIGHTER_MODE_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_IMPERIALDRAMON_FIGHTER_MODE_FQID_LEN = sizeof(ALT_PEN20_IMPERIALDRAMON_FIGHTER_MODE_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_IMPERIALDRAMON_FIGHTER_MODE_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Imperialdramon Fighter Mode";
    inline static constexpr const char* ALT_PEN20_IMPERIALDRAMON_FIGHTER_MODE_FQNAME = ALT_PEN20_IMPERIALDRAMON_FIGHTER_MODE_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_IMPERIALDRAMON_FIGHTER_MODE_FQNAME_LEN = sizeof(ALT_PEN20_IMPERIALDRAMON_FIGHTER_MODE_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_IMPMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:impmon";
    inline static constexpr const char* ALT_PEN20_IMPMON_FQID = ALT_PEN20_IMPMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_IMPMON_FQID_LEN = sizeof(ALT_PEN20_IMPMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_IMPMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Impmon";
    inline static constexpr const char* ALT_PEN20_IMPMON_FQNAME = ALT_PEN20_IMPMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_IMPMON_FQNAME_LEN = sizeof(ALT_PEN20_IMPMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_JESMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:jesmon";
    inline static constexpr const char* ALT_PEN20_JESMON_FQID = ALT_PEN20_JESMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_JESMON_FQID_LEN = sizeof(ALT_PEN20_JESMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_JESMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Jesmon";
    inline static constexpr const char* ALT_PEN20_JESMON_FQNAME = ALT_PEN20_JESMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_JESMON_FQNAME_LEN = sizeof(ALT_PEN20_JESMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_JESMON_X_FQID_ARR[] CONFIG_STRING_SECTION = "pen:jesmon_x";
    inline static constexpr const char* ALT_PEN20_JESMON_X_FQID = ALT_PEN20_JESMON_X_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_JESMON_X_FQID_LEN = sizeof(ALT_PEN20_JESMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_JESMON_X_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Jesmon X";
    inline static constexpr const char* ALT_PEN20_JESMON_X_FQNAME = ALT_PEN20_JESMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_JESMON_X_FQNAME_LEN = sizeof(ALT_PEN20_JESMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_JYAGAMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:jyagamon";
    inline static constexpr const char* ALT_PEN20_JYAGAMON_FQID = ALT_PEN20_JYAGAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_JYAGAMON_FQID_LEN = sizeof(ALT_PEN20_JYAGAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_JYAGAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Jyagamon";
    inline static constexpr const char* ALT_PEN20_JYAGAMON_FQNAME = ALT_PEN20_JYAGAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_JYAGAMON_FQNAME_LEN = sizeof(ALT_PEN20_JYAGAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_JYUREIMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:jyureimon";
    inline static constexpr const char* ALT_PEN20_JYUREIMON_FQID = ALT_PEN20_JYUREIMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_JYUREIMON_FQID_LEN = sizeof(ALT_PEN20_JYUREIMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_JYUREIMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Jyureimon";
    inline static constexpr const char* ALT_PEN20_JYUREIMON_FQNAME = ALT_PEN20_JYUREIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_JYUREIMON_FQNAME_LEN = sizeof(ALT_PEN20_JYUREIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_KABUTERIMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:kabuterimon";
    inline static constexpr const char* ALT_PEN20_KABUTERIMON_FQID = ALT_PEN20_KABUTERIMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_KABUTERIMON_FQID_LEN = sizeof(ALT_PEN20_KABUTERIMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_KABUTERIMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Kabuterimon";
    inline static constexpr const char* ALT_PEN20_KABUTERIMON_FQNAME = ALT_PEN20_KABUTERIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_KABUTERIMON_FQNAME_LEN = sizeof(ALT_PEN20_KABUTERIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_KAKKINMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:kakkinmon";
    inline static constexpr const char* ALT_PEN20_KAKKINMON_FQID = ALT_PEN20_KAKKINMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_KAKKINMON_FQID_LEN = sizeof(ALT_PEN20_KAKKINMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_KAKKINMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Kakkinmon";
    inline static constexpr const char* ALT_PEN20_KAKKINMON_FQNAME = ALT_PEN20_KAKKINMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_KAKKINMON_FQNAME_LEN = sizeof(ALT_PEN20_KAKKINMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_KIWIMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:kiwimon";
    inline static constexpr const char* ALT_PEN20_KIWIMON_FQID = ALT_PEN20_KIWIMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_KIWIMON_FQID_LEN = sizeof(ALT_PEN20_KIWIMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_KIWIMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Kiwimon";
    inline static constexpr const char* ALT_PEN20_KIWIMON_FQNAME = ALT_PEN20_KIWIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_KIWIMON_FQNAME_LEN = sizeof(ALT_PEN20_KIWIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_KNIGHTMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:knightmon";
    inline static constexpr const char* ALT_PEN20_KNIGHTMON_FQID = ALT_PEN20_KNIGHTMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_KNIGHTMON_FQID_LEN = sizeof(ALT_PEN20_KNIGHTMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_KNIGHTMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Knightmon";
    inline static constexpr const char* ALT_PEN20_KNIGHTMON_FQNAME = ALT_PEN20_KNIGHTMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_KNIGHTMON_FQNAME_LEN = sizeof(ALT_PEN20_KNIGHTMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_KOKUWAMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:kokuwamon";
    inline static constexpr const char* ALT_PEN20_KOKUWAMON_FQID = ALT_PEN20_KOKUWAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_KOKUWAMON_FQID_LEN = sizeof(ALT_PEN20_KOKUWAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_KOKUWAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Kokuwamon";
    inline static constexpr const char* ALT_PEN20_KOKUWAMON_FQNAME = ALT_PEN20_KOKUWAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_KOKUWAMON_FQNAME_LEN = sizeof(ALT_PEN20_KOKUWAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_KOROMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:koromon";
    inline static constexpr const char* ALT_PEN20_KOROMON_FQID = ALT_PEN20_KOROMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_KOROMON_FQID_LEN = sizeof(ALT_PEN20_KOROMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_KOROMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Koromon";
    inline static constexpr const char* ALT_PEN20_KOROMON_FQNAME = ALT_PEN20_KOROMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_KOROMON_FQNAME_LEN = sizeof(ALT_PEN20_KOROMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_KUWAGAMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:kuwagamon";
    inline static constexpr const char* ALT_PEN20_KUWAGAMON_FQID = ALT_PEN20_KUWAGAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_KUWAGAMON_FQID_LEN = sizeof(ALT_PEN20_KUWAGAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_KUWAGAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Kuwagamon";
    inline static constexpr const char* ALT_PEN20_KUWAGAMON_FQNAME = ALT_PEN20_KUWAGAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_KUWAGAMON_FQNAME_LEN = sizeof(ALT_PEN20_KUWAGAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_KYOKYOMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:kyokyomon";
    inline static constexpr const char* ALT_PEN20_KYOKYOMON_FQID = ALT_PEN20_KYOKYOMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_KYOKYOMON_FQID_LEN = sizeof(ALT_PEN20_KYOKYOMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_KYOKYOMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Kyokyomon";
    inline static constexpr const char* ALT_PEN20_KYOKYOMON_FQNAME = ALT_PEN20_KYOKYOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_KYOKYOMON_FQNAME_LEN = sizeof(ALT_PEN20_KYOKYOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_LADY_DEVIMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:lady_devimon";
    inline static constexpr const char* ALT_PEN20_LADY_DEVIMON_FQID = ALT_PEN20_LADY_DEVIMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_LADY_DEVIMON_FQID_LEN = sizeof(ALT_PEN20_LADY_DEVIMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_LADY_DEVIMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Lady Devimon";
    inline static constexpr const char* ALT_PEN20_LADY_DEVIMON_FQNAME = ALT_PEN20_LADY_DEVIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_LADY_DEVIMON_FQNAME_LEN = sizeof(ALT_PEN20_LADY_DEVIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_LALAMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:lalamon";
    inline static constexpr const char* ALT_PEN20_LALAMON_FQID = ALT_PEN20_LALAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_LALAMON_FQID_LEN = sizeof(ALT_PEN20_LALAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_LALAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Lalamon";
    inline static constexpr const char* ALT_PEN20_LALAMON_FQNAME = ALT_PEN20_LALAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_LALAMON_FQNAME_LEN = sizeof(ALT_PEN20_LALAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_LAVOGARITAMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:lavogaritamon";
    inline static constexpr const char* ALT_PEN20_LAVOGARITAMON_FQID = ALT_PEN20_LAVOGARITAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_LAVOGARITAMON_FQID_LEN = sizeof(ALT_PEN20_LAVOGARITAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_LAVOGARITAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Lavogaritamon";
    inline static constexpr const char* ALT_PEN20_LAVOGARITAMON_FQNAME = ALT_PEN20_LAVOGARITAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_LAVOGARITAMON_FQNAME_LEN = sizeof(ALT_PEN20_LAVOGARITAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_LAVORVOMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:lavorvomon";
    inline static constexpr const char* ALT_PEN20_LAVORVOMON_FQID = ALT_PEN20_LAVORVOMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_LAVORVOMON_FQID_LEN = sizeof(ALT_PEN20_LAVORVOMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_LAVORVOMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Lavorvomon";
    inline static constexpr const char* ALT_PEN20_LAVORVOMON_FQNAME = ALT_PEN20_LAVORVOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_LAVORVOMON_FQNAME_LEN = sizeof(ALT_PEN20_LAVORVOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_LEOMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:leomon";
    inline static constexpr const char* ALT_PEN20_LEOMON_FQID = ALT_PEN20_LEOMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_LEOMON_FQID_LEN = sizeof(ALT_PEN20_LEOMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_LEOMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Leomon";
    inline static constexpr const char* ALT_PEN20_LEOMON_FQNAME = ALT_PEN20_LEOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_LEOMON_FQNAME_LEN = sizeof(ALT_PEN20_LEOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_LILAMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:lilamon";
    inline static constexpr const char* ALT_PEN20_LILAMON_FQID = ALT_PEN20_LILAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_LILAMON_FQID_LEN = sizeof(ALT_PEN20_LILAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_LILAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Lilamon";
    inline static constexpr const char* ALT_PEN20_LILAMON_FQNAME = ALT_PEN20_LILAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_LILAMON_FQNAME_LEN = sizeof(ALT_PEN20_LILAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_LILIMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:lilimon";
    inline static constexpr const char* ALT_PEN20_LILIMON_FQID = ALT_PEN20_LILIMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_LILIMON_FQID_LEN = sizeof(ALT_PEN20_LILIMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_LILIMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Lilimon";
    inline static constexpr const char* ALT_PEN20_LILIMON_FQNAME = ALT_PEN20_LILIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_LILIMON_FQNAME_LEN = sizeof(ALT_PEN20_LILIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_LOPMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:lopmon";
    inline static constexpr const char* ALT_PEN20_LOPMON_FQID = ALT_PEN20_LOPMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_LOPMON_FQID_LEN = sizeof(ALT_PEN20_LOPMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_LOPMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Lopmon";
    inline static constexpr const char* ALT_PEN20_LOPMON_FQNAME = ALT_PEN20_LOPMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_LOPMON_FQNAME_LEN = sizeof(ALT_PEN20_LOPMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_LOTUSMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:lotusmon";
    inline static constexpr const char* ALT_PEN20_LOTUSMON_FQID = ALT_PEN20_LOTUSMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_LOTUSMON_FQID_LEN = sizeof(ALT_PEN20_LOTUSMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_LOTUSMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Lotusmon";
    inline static constexpr const char* ALT_PEN20_LOTUSMON_FQNAME = ALT_PEN20_LOTUSMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_LOTUSMON_FQNAME_LEN = sizeof(ALT_PEN20_LOTUSMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_LUDOMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:ludomon";
    inline static constexpr const char* ALT_PEN20_LUDOMON_FQID = ALT_PEN20_LUDOMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_LUDOMON_FQID_LEN = sizeof(ALT_PEN20_LUDOMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_LUDOMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Ludomon";
    inline static constexpr const char* ALT_PEN20_LUDOMON_FQNAME = ALT_PEN20_LUDOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_LUDOMON_FQNAME_LEN = sizeof(ALT_PEN20_LUDOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_MAD_LEOMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:mad_leomon";
    inline static constexpr const char* ALT_PEN20_MAD_LEOMON_FQID = ALT_PEN20_MAD_LEOMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_MAD_LEOMON_FQID_LEN = sizeof(ALT_PEN20_MAD_LEOMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_MAD_LEOMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Mad Leomon";
    inline static constexpr const char* ALT_PEN20_MAD_LEOMON_FQNAME = ALT_PEN20_MAD_LEOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_MAD_LEOMON_FQNAME_LEN = sizeof(ALT_PEN20_MAD_LEOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_MAMMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:mammon";
    inline static constexpr const char* ALT_PEN20_MAMMON_FQID = ALT_PEN20_MAMMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_MAMMON_FQID_LEN = sizeof(ALT_PEN20_MAMMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_MAMMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Mammon";
    inline static constexpr const char* ALT_PEN20_MAMMON_FQNAME = ALT_PEN20_MAMMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_MAMMON_FQNAME_LEN = sizeof(ALT_PEN20_MAMMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_MANBOMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:manbomon";
    inline static constexpr const char* ALT_PEN20_MANBOMON_FQID = ALT_PEN20_MANBOMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_MANBOMON_FQID_LEN = sizeof(ALT_PEN20_MANBOMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_MANBOMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Manbomon";
    inline static constexpr const char* ALT_PEN20_MANBOMON_FQNAME = ALT_PEN20_MANBOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_MANBOMON_FQNAME_LEN = sizeof(ALT_PEN20_MANBOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_MARIN_ANGEMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:marin_angemon";
    inline static constexpr const char* ALT_PEN20_MARIN_ANGEMON_FQID = ALT_PEN20_MARIN_ANGEMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_MARIN_ANGEMON_FQID_LEN = sizeof(ALT_PEN20_MARIN_ANGEMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_MARIN_ANGEMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Marin Angemon";
    inline static constexpr const char* ALT_PEN20_MARIN_ANGEMON_FQNAME = ALT_PEN20_MARIN_ANGEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_MARIN_ANGEMON_FQNAME_LEN = sizeof(ALT_PEN20_MARIN_ANGEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_MARIN_DEVIMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:marin_devimon";
    inline static constexpr const char* ALT_PEN20_MARIN_DEVIMON_FQID = ALT_PEN20_MARIN_DEVIMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_MARIN_DEVIMON_FQID_LEN = sizeof(ALT_PEN20_MARIN_DEVIMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_MARIN_DEVIMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Marin Devimon";
    inline static constexpr const char* ALT_PEN20_MARIN_DEVIMON_FQNAME = ALT_PEN20_MARIN_DEVIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_MARIN_DEVIMON_FQNAME_LEN = sizeof(ALT_PEN20_MARIN_DEVIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_MASTEMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:mastemon";
    inline static constexpr const char* ALT_PEN20_MASTEMON_FQID = ALT_PEN20_MASTEMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_MASTEMON_FQID_LEN = sizeof(ALT_PEN20_MASTEMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_MASTEMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Mastemon";
    inline static constexpr const char* ALT_PEN20_MASTEMON_FQNAME = ALT_PEN20_MASTEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_MASTEMON_FQNAME_LEN = sizeof(ALT_PEN20_MASTEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_MECHANORIMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:mechanorimon";
    inline static constexpr const char* ALT_PEN20_MECHANORIMON_FQID = ALT_PEN20_MECHANORIMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_MECHANORIMON_FQID_LEN = sizeof(ALT_PEN20_MECHANORIMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_MECHANORIMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Mechanorimon";
    inline static constexpr const char* ALT_PEN20_MECHANORIMON_FQNAME = ALT_PEN20_MECHANORIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_MECHANORIMON_FQNAME_LEN = sizeof(ALT_PEN20_MECHANORIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_MEGADRAMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:megadramon";
    inline static constexpr const char* ALT_PEN20_MEGADRAMON_FQID = ALT_PEN20_MEGADRAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_MEGADRAMON_FQID_LEN = sizeof(ALT_PEN20_MEGADRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_MEGADRAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Megadramon";
    inline static constexpr const char* ALT_PEN20_MEGADRAMON_FQNAME = ALT_PEN20_MEGADRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_MEGADRAMON_FQNAME_LEN = sizeof(ALT_PEN20_MEGADRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_MEGALO_GROWMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:megalo_growmon";
    inline static constexpr const char* ALT_PEN20_MEGALO_GROWMON_FQID = ALT_PEN20_MEGALO_GROWMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_MEGALO_GROWMON_FQID_LEN = sizeof(ALT_PEN20_MEGALO_GROWMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_MEGALO_GROWMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Megalo Growmon";
    inline static constexpr const char* ALT_PEN20_MEGALO_GROWMON_FQNAME = ALT_PEN20_MEGALO_GROWMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_MEGALO_GROWMON_FQNAME_LEN = sizeof(ALT_PEN20_MEGALO_GROWMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_MEGA_SEADRAMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:mega_seadramon";
    inline static constexpr const char* ALT_PEN20_MEGA_SEADRAMON_FQID = ALT_PEN20_MEGA_SEADRAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_MEGA_SEADRAMON_FQID_LEN = sizeof(ALT_PEN20_MEGA_SEADRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_MEGA_SEADRAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Mega Seadramon";
    inline static constexpr const char* ALT_PEN20_MEGA_SEADRAMON_FQNAME = ALT_PEN20_MEGA_SEADRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_MEGA_SEADRAMON_FQNAME_LEN = sizeof(ALT_PEN20_MEGA_SEADRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_MEICOOMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:meicoomon";
    inline static constexpr const char* ALT_PEN20_MEICOOMON_FQID = ALT_PEN20_MEICOOMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_MEICOOMON_FQID_LEN = sizeof(ALT_PEN20_MEICOOMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_MEICOOMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Meicoomon";
    inline static constexpr const char* ALT_PEN20_MEICOOMON_FQNAME = ALT_PEN20_MEICOOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_MEICOOMON_FQNAME_LEN = sizeof(ALT_PEN20_MEICOOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_MEICRACKMON_VICIOUS_MODE_FQID_ARR[] CONFIG_STRING_SECTION = "pen:meicrackmon_vicious_mode";
    inline static constexpr const char* ALT_PEN20_MEICRACKMON_VICIOUS_MODE_FQID = ALT_PEN20_MEICRACKMON_VICIOUS_MODE_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_MEICRACKMON_VICIOUS_MODE_FQID_LEN = sizeof(ALT_PEN20_MEICRACKMON_VICIOUS_MODE_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_MEICRACKMON_VICIOUS_MODE_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Meicrackmon Vicious Mode";
    inline static constexpr const char* ALT_PEN20_MEICRACKMON_VICIOUS_MODE_FQNAME = ALT_PEN20_MEICRACKMON_VICIOUS_MODE_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_MEICRACKMON_VICIOUS_MODE_FQNAME_LEN = sizeof(ALT_PEN20_MEICRACKMON_VICIOUS_MODE_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_MERAMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:meramon";
    inline static constexpr const char* ALT_PEN20_MERAMON_FQID = ALT_PEN20_MERAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_MERAMON_FQID_LEN = sizeof(ALT_PEN20_MERAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_MERAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Meramon";
    inline static constexpr const char* ALT_PEN20_MERAMON_FQNAME = ALT_PEN20_MERAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_MERAMON_FQNAME_LEN = sizeof(ALT_PEN20_MERAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_METAL_ETEMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:metal_etemon";
    inline static constexpr const char* ALT_PEN20_METAL_ETEMON_FQID = ALT_PEN20_METAL_ETEMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_METAL_ETEMON_FQID_LEN = sizeof(ALT_PEN20_METAL_ETEMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_METAL_ETEMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Metal Etemon";
    inline static constexpr const char* ALT_PEN20_METAL_ETEMON_FQNAME = ALT_PEN20_METAL_ETEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_METAL_ETEMON_FQNAME_LEN = sizeof(ALT_PEN20_METAL_ETEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_METAL_GARURUMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:metal_garurumon";
    inline static constexpr const char* ALT_PEN20_METAL_GARURUMON_FQID = ALT_PEN20_METAL_GARURUMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_METAL_GARURUMON_FQID_LEN = sizeof(ALT_PEN20_METAL_GARURUMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_METAL_GARURUMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Metal Garurumon";
    inline static constexpr const char* ALT_PEN20_METAL_GARURUMON_FQNAME = ALT_PEN20_METAL_GARURUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_METAL_GARURUMON_FQNAME_LEN = sizeof(ALT_PEN20_METAL_GARURUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_METAL_GREYMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:metal_greymon";
    inline static constexpr const char* ALT_PEN20_METAL_GREYMON_FQID = ALT_PEN20_METAL_GREYMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_METAL_GREYMON_FQID_LEN = sizeof(ALT_PEN20_METAL_GREYMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_METAL_GREYMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Metal Greymon";
    inline static constexpr const char* ALT_PEN20_METAL_GREYMON_FQNAME = ALT_PEN20_METAL_GREYMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_METAL_GREYMON_FQNAME_LEN = sizeof(ALT_PEN20_METAL_GREYMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_METAL_MAMEMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:metal_mamemon";
    inline static constexpr const char* ALT_PEN20_METAL_MAMEMON_FQID = ALT_PEN20_METAL_MAMEMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_METAL_MAMEMON_FQID_LEN = sizeof(ALT_PEN20_METAL_MAMEMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_METAL_MAMEMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Metal Mamemon";
    inline static constexpr const char* ALT_PEN20_METAL_MAMEMON_FQNAME = ALT_PEN20_METAL_MAMEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_METAL_MAMEMON_FQNAME_LEN = sizeof(ALT_PEN20_METAL_MAMEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_METAL_SEADRAMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:metal_seadramon";
    inline static constexpr const char* ALT_PEN20_METAL_SEADRAMON_FQID = ALT_PEN20_METAL_SEADRAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_METAL_SEADRAMON_FQID_LEN = sizeof(ALT_PEN20_METAL_SEADRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_METAL_SEADRAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Metal Seadramon";
    inline static constexpr const char* ALT_PEN20_METAL_SEADRAMON_FQNAME = ALT_PEN20_METAL_SEADRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_METAL_SEADRAMON_FQNAME_LEN = sizeof(ALT_PEN20_METAL_SEADRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_MOCHIMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:mochimon";
    inline static constexpr const char* ALT_PEN20_MOCHIMON_FQID = ALT_PEN20_MOCHIMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_MOCHIMON_FQID_LEN = sizeof(ALT_PEN20_MOCHIMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_MOCHIMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Mochimon";
    inline static constexpr const char* ALT_PEN20_MOCHIMON_FQNAME = ALT_PEN20_MOCHIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_MOCHIMON_FQNAME_LEN = sizeof(ALT_PEN20_MOCHIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_MOKUMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:mokumon";
    inline static constexpr const char* ALT_PEN20_MOKUMON_FQID = ALT_PEN20_MOKUMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_MOKUMON_FQID_LEN = sizeof(ALT_PEN20_MOKUMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_MOKUMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Mokumon";
    inline static constexpr const char* ALT_PEN20_MOKUMON_FQNAME = ALT_PEN20_MOKUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_MOKUMON_FQNAME_LEN = sizeof(ALT_PEN20_MOKUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_MONOCHROMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:monochromon";
    inline static constexpr const char* ALT_PEN20_MONOCHROMON_FQID = ALT_PEN20_MONOCHROMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_MONOCHROMON_FQID_LEN = sizeof(ALT_PEN20_MONOCHROMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_MONOCHROMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Monochromon";
    inline static constexpr const char* ALT_PEN20_MONOCHROMON_FQNAME = ALT_PEN20_MONOCHROMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_MONOCHROMON_FQNAME_LEN = sizeof(ALT_PEN20_MONOCHROMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_MUGENDRAMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:mugendramon";
    inline static constexpr const char* ALT_PEN20_MUGENDRAMON_FQID = ALT_PEN20_MUGENDRAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_MUGENDRAMON_FQID_LEN = sizeof(ALT_PEN20_MUGENDRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_MUGENDRAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Mugendramon";
    inline static constexpr const char* ALT_PEN20_MUGENDRAMON_FQNAME = ALT_PEN20_MUGENDRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_MUGENDRAMON_FQNAME_LEN = sizeof(ALT_PEN20_MUGENDRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_MUSHMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:mushmon";
    inline static constexpr const char* ALT_PEN20_MUSHMON_FQID = ALT_PEN20_MUSHMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_MUSHMON_FQID_LEN = sizeof(ALT_PEN20_MUSHMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_MUSHMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Mushmon";
    inline static constexpr const char* ALT_PEN20_MUSHMON_FQNAME = ALT_PEN20_MUSHMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_MUSHMON_FQNAME_LEN = sizeof(ALT_PEN20_MUSHMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_NYAROMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:nyaromon";
    inline static constexpr const char* ALT_PEN20_NYAROMON_FQID = ALT_PEN20_NYAROMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_NYAROMON_FQID_LEN = sizeof(ALT_PEN20_NYAROMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_NYAROMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Nyaromon";
    inline static constexpr const char* ALT_PEN20_NYAROMON_FQNAME = ALT_PEN20_NYAROMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_NYAROMON_FQNAME_LEN = sizeof(ALT_PEN20_NYAROMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_NYOKIMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:nyokimon";
    inline static constexpr const char* ALT_PEN20_NYOKIMON_FQID = ALT_PEN20_NYOKIMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_NYOKIMON_FQID_LEN = sizeof(ALT_PEN20_NYOKIMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_NYOKIMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Nyokimon";
    inline static constexpr const char* ALT_PEN20_NYOKIMON_FQNAME = ALT_PEN20_NYOKIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_NYOKIMON_FQNAME_LEN = sizeof(ALT_PEN20_NYOKIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_OCTMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:octmon";
    inline static constexpr const char* ALT_PEN20_OCTMON_FQID = ALT_PEN20_OCTMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_OCTMON_FQID_LEN = sizeof(ALT_PEN20_OCTMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_OCTMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Octmon";
    inline static constexpr const char* ALT_PEN20_OCTMON_FQNAME = ALT_PEN20_OCTMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_OCTMON_FQNAME_LEN = sizeof(ALT_PEN20_OCTMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_OFANIMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:ofanimon";
    inline static constexpr const char* ALT_PEN20_OFANIMON_FQID = ALT_PEN20_OFANIMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_OFANIMON_FQID_LEN = sizeof(ALT_PEN20_OFANIMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_OFANIMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Ofanimon";
    inline static constexpr const char* ALT_PEN20_OFANIMON_FQNAME = ALT_PEN20_OFANIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_OFANIMON_FQNAME_LEN = sizeof(ALT_PEN20_OFANIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_OGUDOMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:ogudomon";
    inline static constexpr const char* ALT_PEN20_OGUDOMON_FQID = ALT_PEN20_OGUDOMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_OGUDOMON_FQID_LEN = sizeof(ALT_PEN20_OGUDOMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_OGUDOMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Ogudomon";
    inline static constexpr const char* ALT_PEN20_OGUDOMON_FQNAME = ALT_PEN20_OGUDOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_OGUDOMON_FQNAME_LEN = sizeof(ALT_PEN20_OGUDOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_OKUWAMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:okuwamon";
    inline static constexpr const char* ALT_PEN20_OKUWAMON_FQID = ALT_PEN20_OKUWAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_OKUWAMON_FQID_LEN = sizeof(ALT_PEN20_OKUWAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_OKUWAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Okuwamon";
    inline static constexpr const char* ALT_PEN20_OKUWAMON_FQNAME = ALT_PEN20_OKUWAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_OKUWAMON_FQNAME_LEN = sizeof(ALT_PEN20_OKUWAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_OMEGAMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:omegamon";
    inline static constexpr const char* ALT_PEN20_OMEGAMON_FQID = ALT_PEN20_OMEGAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_OMEGAMON_FQID_LEN = sizeof(ALT_PEN20_OMEGAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_OMEGAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Omegamon";
    inline static constexpr const char* ALT_PEN20_OMEGAMON_FQNAME = ALT_PEN20_OMEGAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_OMEGAMON_FQNAME_LEN = sizeof(ALT_PEN20_OMEGAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_ORDINEMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:ordinemon";
    inline static constexpr const char* ALT_PEN20_ORDINEMON_FQID = ALT_PEN20_ORDINEMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_ORDINEMON_FQID_LEN = sizeof(ALT_PEN20_ORDINEMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_ORDINEMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Ordinemon";
    inline static constexpr const char* ALT_PEN20_ORDINEMON_FQNAME = ALT_PEN20_ORDINEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_ORDINEMON_FQNAME_LEN = sizeof(ALT_PEN20_ORDINEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_OTAMAMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:otamamon";
    inline static constexpr const char* ALT_PEN20_OTAMAMON_FQID = ALT_PEN20_OTAMAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_OTAMAMON_FQID_LEN = sizeof(ALT_PEN20_OTAMAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_OTAMAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Otamamon";
    inline static constexpr const char* ALT_PEN20_OTAMAMON_FQNAME = ALT_PEN20_OTAMAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_OTAMAMON_FQNAME_LEN = sizeof(ALT_PEN20_OTAMAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_OURYUMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:ouryumon";
    inline static constexpr const char* ALT_PEN20_OURYUMON_FQID = ALT_PEN20_OURYUMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_OURYUMON_FQID_LEN = sizeof(ALT_PEN20_OURYUMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_OURYUMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Ouryumon";
    inline static constexpr const char* ALT_PEN20_OURYUMON_FQNAME = ALT_PEN20_OURYUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_OURYUMON_FQNAME_LEN = sizeof(ALT_PEN20_OURYUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_PAILDRAMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:paildramon";
    inline static constexpr const char* ALT_PEN20_PAILDRAMON_FQID = ALT_PEN20_PAILDRAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_PAILDRAMON_FQID_LEN = sizeof(ALT_PEN20_PAILDRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_PAILDRAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Paildramon";
    inline static constexpr const char* ALT_PEN20_PAILDRAMON_FQNAME = ALT_PEN20_PAILDRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_PAILDRAMON_FQNAME_LEN = sizeof(ALT_PEN20_PAILDRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_PALMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:palmon";
    inline static constexpr const char* ALT_PEN20_PALMON_FQID = ALT_PEN20_PALMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_PALMON_FQID_LEN = sizeof(ALT_PEN20_PALMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_PALMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Palmon";
    inline static constexpr const char* ALT_PEN20_PALMON_FQNAME = ALT_PEN20_PALMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_PALMON_FQNAME_LEN = sizeof(ALT_PEN20_PALMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_PETI_MERAMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:peti_meramon";
    inline static constexpr const char* ALT_PEN20_PETI_MERAMON_FQID = ALT_PEN20_PETI_MERAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_PETI_MERAMON_FQID_LEN = sizeof(ALT_PEN20_PETI_MERAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_PETI_MERAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Peti Meramon";
    inline static constexpr const char* ALT_PEN20_PETI_MERAMON_FQNAME = ALT_PEN20_PETI_MERAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_PETI_MERAMON_FQNAME_LEN = sizeof(ALT_PEN20_PETI_MERAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_PETITMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:petitmon";
    inline static constexpr const char* ALT_PEN20_PETITMON_FQID = ALT_PEN20_PETITMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_PETITMON_FQID_LEN = sizeof(ALT_PEN20_PETITMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_PETITMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Petitmon";
    inline static constexpr const char* ALT_PEN20_PETITMON_FQNAME = ALT_PEN20_PETITMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_PETITMON_FQNAME_LEN = sizeof(ALT_PEN20_PETITMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_PHASCOMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:phascomon";
    inline static constexpr const char* ALT_PEN20_PHASCOMON_FQID = ALT_PEN20_PHASCOMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_PHASCOMON_FQID_LEN = sizeof(ALT_PEN20_PHASCOMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_PHASCOMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Phascomon";
    inline static constexpr const char* ALT_PEN20_PHASCOMON_FQNAME = ALT_PEN20_PHASCOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_PHASCOMON_FQNAME_LEN = sizeof(ALT_PEN20_PHASCOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_PICCOLOMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:piccolomon";
    inline static constexpr const char* ALT_PEN20_PICCOLOMON_FQID = ALT_PEN20_PICCOLOMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_PICCOLOMON_FQID_LEN = sizeof(ALT_PEN20_PICCOLOMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_PICCOLOMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Piccolomon";
    inline static constexpr const char* ALT_PEN20_PICCOLOMON_FQNAME = ALT_PEN20_PICCOLOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_PICCOLOMON_FQNAME_LEN = sizeof(ALT_PEN20_PICCOLOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_PICO_DEVIMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:pico_devimon";
    inline static constexpr const char* ALT_PEN20_PICO_DEVIMON_FQID = ALT_PEN20_PICO_DEVIMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_PICO_DEVIMON_FQID_LEN = sizeof(ALT_PEN20_PICO_DEVIMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_PICO_DEVIMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Pico Devimon";
    inline static constexpr const char* ALT_PEN20_PICO_DEVIMON_FQNAME = ALT_PEN20_PICO_DEVIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_PICO_DEVIMON_FQNAME_LEN = sizeof(ALT_PEN20_PICO_DEVIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_PIEMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:piemon";
    inline static constexpr const char* ALT_PEN20_PIEMON_FQID = ALT_PEN20_PIEMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_PIEMON_FQID_LEN = sizeof(ALT_PEN20_PIEMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_PIEMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Piemon";
    inline static constexpr const char* ALT_PEN20_PIEMON_FQNAME = ALT_PEN20_PIEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_PIEMON_FQNAME_LEN = sizeof(ALT_PEN20_PIEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_PINOCHIMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:pinochimon";
    inline static constexpr const char* ALT_PEN20_PINOCHIMON_FQID = ALT_PEN20_PINOCHIMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_PINOCHIMON_FQID_LEN = sizeof(ALT_PEN20_PINOCHIMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_PINOCHIMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Pinochimon";
    inline static constexpr const char* ALT_PEN20_PINOCHIMON_FQNAME = ALT_PEN20_PINOCHIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_PINOCHIMON_FQNAME_LEN = sizeof(ALT_PEN20_PINOCHIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_PITCHMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:pitchmon";
    inline static constexpr const char* ALT_PEN20_PITCHMON_FQID = ALT_PEN20_PITCHMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_PITCHMON_FQID_LEN = sizeof(ALT_PEN20_PITCHMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_PITCHMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Pitchmon";
    inline static constexpr const char* ALT_PEN20_PITCHMON_FQNAME = ALT_PEN20_PITCHMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_PITCHMON_FQNAME_LEN = sizeof(ALT_PEN20_PITCHMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_PIYOMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:piyomon";
    inline static constexpr const char* ALT_PEN20_PIYOMON_FQID = ALT_PEN20_PIYOMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_PIYOMON_FQID_LEN = sizeof(ALT_PEN20_PIYOMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_PIYOMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Piyomon";
    inline static constexpr const char* ALT_PEN20_PIYOMON_FQNAME = ALT_PEN20_PIYOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_PIYOMON_FQNAME_LEN = sizeof(ALT_PEN20_PIYOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_PLESIOMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:plesiomon";
    inline static constexpr const char* ALT_PEN20_PLESIOMON_FQID = ALT_PEN20_PLESIOMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_PLESIOMON_FQID_LEN = sizeof(ALT_PEN20_PLESIOMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_PLESIOMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Plesiomon";
    inline static constexpr const char* ALT_PEN20_PLESIOMON_FQNAME = ALT_PEN20_PLESIOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_PLESIOMON_FQNAME_LEN = sizeof(ALT_PEN20_PLESIOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_PLOTMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:plotmon";
    inline static constexpr const char* ALT_PEN20_PLOTMON_FQID = ALT_PEN20_PLOTMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_PLOTMON_FQID_LEN = sizeof(ALT_PEN20_PLOTMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_PLOTMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Plotmon";
    inline static constexpr const char* ALT_PEN20_PLOTMON_FQNAME = ALT_PEN20_PLOTMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_PLOTMON_FQNAME_LEN = sizeof(ALT_PEN20_PLOTMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_PORCUPAMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:porcupamon";
    inline static constexpr const char* ALT_PEN20_PORCUPAMON_FQID = ALT_PEN20_PORCUPAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_PORCUPAMON_FQID_LEN = sizeof(ALT_PEN20_PORCUPAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_PORCUPAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Porcupamon";
    inline static constexpr const char* ALT_PEN20_PORCUPAMON_FQNAME = ALT_PEN20_PORCUPAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_PORCUPAMON_FQNAME_LEN = sizeof(ALT_PEN20_PORCUPAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_PUKAMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:pukamon";
    inline static constexpr const char* ALT_PEN20_PUKAMON_FQID = ALT_PEN20_PUKAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_PUKAMON_FQID_LEN = sizeof(ALT_PEN20_PUKAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_PUKAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Pukamon";
    inline static constexpr const char* ALT_PEN20_PUKAMON_FQNAME = ALT_PEN20_PUKAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_PUKAMON_FQNAME_LEN = sizeof(ALT_PEN20_PUKAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_PUKUMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:pukumon";
    inline static constexpr const char* ALT_PEN20_PUKUMON_FQID = ALT_PEN20_PUKUMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_PUKUMON_FQID_LEN = sizeof(ALT_PEN20_PUKUMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_PUKUMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Pukumon";
    inline static constexpr const char* ALT_PEN20_PUKUMON_FQNAME = ALT_PEN20_PUKUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_PUKUMON_FQNAME_LEN = sizeof(ALT_PEN20_PUKUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_PUMPMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:pumpmon";
    inline static constexpr const char* ALT_PEN20_PUMPMON_FQID = ALT_PEN20_PUMPMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_PUMPMON_FQID_LEN = sizeof(ALT_PEN20_PUMPMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_PUMPMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Pumpmon";
    inline static constexpr const char* ALT_PEN20_PUMPMON_FQNAME = ALT_PEN20_PUMPMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_PUMPMON_FQNAME_LEN = sizeof(ALT_PEN20_PUMPMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_PYOCOMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:pyocomon";
    inline static constexpr const char* ALT_PEN20_PYOCOMON_FQID = ALT_PEN20_PYOCOMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_PYOCOMON_FQID_LEN = sizeof(ALT_PEN20_PYOCOMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_PYOCOMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Pyocomon";
    inline static constexpr const char* ALT_PEN20_PYOCOMON_FQNAME = ALT_PEN20_PYOCOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_PYOCOMON_FQNAME_LEN = sizeof(ALT_PEN20_PYOCOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_RAFFLESIMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:rafflesimon";
    inline static constexpr const char* ALT_PEN20_RAFFLESIMON_FQID = ALT_PEN20_RAFFLESIMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_RAFFLESIMON_FQID_LEN = sizeof(ALT_PEN20_RAFFLESIMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_RAFFLESIMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Rafflesimon";
    inline static constexpr const char* ALT_PEN20_RAFFLESIMON_FQNAME = ALT_PEN20_RAFFLESIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_RAFFLESIMON_FQNAME_LEN = sizeof(ALT_PEN20_RAFFLESIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_RAGNA_LORDMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:ragna_lordmon";
    inline static constexpr const char* ALT_PEN20_RAGNA_LORDMON_FQID = ALT_PEN20_RAGNA_LORDMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_RAGNA_LORDMON_FQID_LEN = sizeof(ALT_PEN20_RAGNA_LORDMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_RAGNA_LORDMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Ragna Lordmon";
    inline static constexpr const char* ALT_PEN20_RAGNA_LORDMON_FQNAME = ALT_PEN20_RAGNA_LORDMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_RAGNA_LORDMON_FQNAME_LEN = sizeof(ALT_PEN20_RAGNA_LORDMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_RAGUELMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:raguelmon";
    inline static constexpr const char* ALT_PEN20_RAGUELMON_FQID = ALT_PEN20_RAGUELMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_RAGUELMON_FQID_LEN = sizeof(ALT_PEN20_RAGUELMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_RAGUELMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Raguelmon";
    inline static constexpr const char* ALT_PEN20_RAGUELMON_FQNAME = ALT_PEN20_RAGUELMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_RAGUELMON_FQNAME_LEN = sizeof(ALT_PEN20_RAGUELMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_RAIJI_LUDOMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:raiji_ludomon";
    inline static constexpr const char* ALT_PEN20_RAIJI_LUDOMON_FQID = ALT_PEN20_RAIJI_LUDOMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_RAIJI_LUDOMON_FQID_LEN = sizeof(ALT_PEN20_RAIJI_LUDOMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_RAIJI_LUDOMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Raiji Ludomon";
    inline static constexpr const char* ALT_PEN20_RAIJI_LUDOMON_FQNAME = ALT_PEN20_RAIJI_LUDOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_RAIJI_LUDOMON_FQNAME_LEN = sizeof(ALT_PEN20_RAIJI_LUDOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_RAPIDMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:rapidmon";
    inline static constexpr const char* ALT_PEN20_RAPIDMON_FQID = ALT_PEN20_RAPIDMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_RAPIDMON_FQID_LEN = sizeof(ALT_PEN20_RAPIDMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_RAPIDMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Rapidmon";
    inline static constexpr const char* ALT_PEN20_RAPIDMON_FQNAME = ALT_PEN20_RAPIDMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_RAPIDMON_FQNAME_LEN = sizeof(ALT_PEN20_RAPIDMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_RED_VEGIMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:red_vegimon";
    inline static constexpr const char* ALT_PEN20_RED_VEGIMON_FQID = ALT_PEN20_RED_VEGIMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_RED_VEGIMON_FQID_LEN = sizeof(ALT_PEN20_RED_VEGIMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_RED_VEGIMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Red Vegimon";
    inline static constexpr const char* ALT_PEN20_RED_VEGIMON_FQNAME = ALT_PEN20_RED_VEGIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_RED_VEGIMON_FQNAME_LEN = sizeof(ALT_PEN20_RED_VEGIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_REPPAMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:reppamon";
    inline static constexpr const char* ALT_PEN20_REPPAMON_FQID = ALT_PEN20_REPPAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_REPPAMON_FQID_LEN = sizeof(ALT_PEN20_REPPAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_REPPAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Reppamon";
    inline static constexpr const char* ALT_PEN20_REPPAMON_FQNAME = ALT_PEN20_REPPAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_REPPAMON_FQNAME_LEN = sizeof(ALT_PEN20_REPPAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_REVOLMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:revolmon";
    inline static constexpr const char* ALT_PEN20_REVOLMON_FQID = ALT_PEN20_REVOLMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_REVOLMON_FQID_LEN = sizeof(ALT_PEN20_REVOLMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_REVOLMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Revolmon";
    inline static constexpr const char* ALT_PEN20_REVOLMON_FQNAME = ALT_PEN20_REVOLMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_REVOLMON_FQNAME_LEN = sizeof(ALT_PEN20_REVOLMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_RIZE_GREYMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:rize_greymon";
    inline static constexpr const char* ALT_PEN20_RIZE_GREYMON_FQID = ALT_PEN20_RIZE_GREYMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_RIZE_GREYMON_FQID_LEN = sizeof(ALT_PEN20_RIZE_GREYMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_RIZE_GREYMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Rize Greymon";
    inline static constexpr const char* ALT_PEN20_RIZE_GREYMON_FQNAME = ALT_PEN20_RIZE_GREYMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_RIZE_GREYMON_FQNAME_LEN = sizeof(ALT_PEN20_RIZE_GREYMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_ROSEMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:rosemon";
    inline static constexpr const char* ALT_PEN20_ROSEMON_FQID = ALT_PEN20_ROSEMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_ROSEMON_FQID_LEN = sizeof(ALT_PEN20_ROSEMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_ROSEMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Rosemon";
    inline static constexpr const char* ALT_PEN20_ROSEMON_FQNAME = ALT_PEN20_ROSEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_ROSEMON_FQNAME_LEN = sizeof(ALT_PEN20_ROSEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_RUKAMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:rukamon";
    inline static constexpr const char* ALT_PEN20_RUKAMON_FQID = ALT_PEN20_RUKAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_RUKAMON_FQID_LEN = sizeof(ALT_PEN20_RUKAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_RUKAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Rukamon";
    inline static constexpr const char* ALT_PEN20_RUKAMON_FQNAME = ALT_PEN20_RUKAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_RUKAMON_FQNAME_LEN = sizeof(ALT_PEN20_RUKAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_RYUDAMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:ryudamon";
    inline static constexpr const char* ALT_PEN20_RYUDAMON_FQID = ALT_PEN20_RYUDAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_RYUDAMON_FQID_LEN = sizeof(ALT_PEN20_RYUDAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_RYUDAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Ryudamon";
    inline static constexpr const char* ALT_PEN20_RYUDAMON_FQNAME = ALT_PEN20_RYUDAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_RYUDAMON_FQNAME_LEN = sizeof(ALT_PEN20_RYUDAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_SABER_LEOMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:saber_leomon";
    inline static constexpr const char* ALT_PEN20_SABER_LEOMON_FQID = ALT_PEN20_SABER_LEOMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_SABER_LEOMON_FQID_LEN = sizeof(ALT_PEN20_SABER_LEOMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_SABER_LEOMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Saber Leomon";
    inline static constexpr const char* ALT_PEN20_SABER_LEOMON_FQNAME = ALT_PEN20_SABER_LEOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_SABER_LEOMON_FQNAME_LEN = sizeof(ALT_PEN20_SABER_LEOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_SAINT_GALGOMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:saint_galgomon";
    inline static constexpr const char* ALT_PEN20_SAINT_GALGOMON_FQID = ALT_PEN20_SAINT_GALGOMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_SAINT_GALGOMON_FQID_LEN = sizeof(ALT_PEN20_SAINT_GALGOMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_SAINT_GALGOMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Saint Galgomon";
    inline static constexpr const char* ALT_PEN20_SAINT_GALGOMON_FQNAME = ALT_PEN20_SAINT_GALGOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_SAINT_GALGOMON_FQNAME_LEN = sizeof(ALT_PEN20_SAINT_GALGOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_SAKUMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:sakumon";
    inline static constexpr const char* ALT_PEN20_SAKUMON_FQID = ALT_PEN20_SAKUMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_SAKUMON_FQID_LEN = sizeof(ALT_PEN20_SAKUMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_SAKUMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Sakumon";
    inline static constexpr const char* ALT_PEN20_SAKUMON_FQNAME = ALT_PEN20_SAKUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_SAKUMON_FQNAME_LEN = sizeof(ALT_PEN20_SAKUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_SAKUTTOMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:sakuttomon";
    inline static constexpr const char* ALT_PEN20_SAKUTTOMON_FQID = ALT_PEN20_SAKUTTOMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_SAKUTTOMON_FQID_LEN = sizeof(ALT_PEN20_SAKUTTOMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_SAKUTTOMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Sakuttomon";
    inline static constexpr const char* ALT_PEN20_SAKUTTOMON_FQNAME = ALT_PEN20_SAKUTTOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_SAKUTTOMON_FQNAME_LEN = sizeof(ALT_PEN20_SAKUTTOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_SAVIOR_HACKMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:savior_hackmon";
    inline static constexpr const char* ALT_PEN20_SAVIOR_HACKMON_FQID = ALT_PEN20_SAVIOR_HACKMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_SAVIOR_HACKMON_FQID_LEN = sizeof(ALT_PEN20_SAVIOR_HACKMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_SAVIOR_HACKMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Savior Hackmon";
    inline static constexpr const char* ALT_PEN20_SAVIOR_HACKMON_FQNAME = ALT_PEN20_SAVIOR_HACKMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_SAVIOR_HACKMON_FQNAME_LEN = sizeof(ALT_PEN20_SAVIOR_HACKMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_SEADRAMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:seadramon";
    inline static constexpr const char* ALT_PEN20_SEADRAMON_FQID = ALT_PEN20_SEADRAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_SEADRAMON_FQID_LEN = sizeof(ALT_PEN20_SEADRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_SEADRAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Seadramon";
    inline static constexpr const char* ALT_PEN20_SEADRAMON_FQNAME = ALT_PEN20_SEADRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_SEADRAMON_FQNAME_LEN = sizeof(ALT_PEN20_SEADRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_SERAPHIMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:seraphimon";
    inline static constexpr const char* ALT_PEN20_SERAPHIMON_FQID = ALT_PEN20_SERAPHIMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_SERAPHIMON_FQID_LEN = sizeof(ALT_PEN20_SERAPHIMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_SERAPHIMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Seraphimon";
    inline static constexpr const char* ALT_PEN20_SERAPHIMON_FQNAME = ALT_PEN20_SERAPHIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_SERAPHIMON_FQNAME_LEN = sizeof(ALT_PEN20_SERAPHIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_SHADRAMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:shadramon";
    inline static constexpr const char* ALT_PEN20_SHADRAMON_FQID = ALT_PEN20_SHADRAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_SHADRAMON_FQID_LEN = sizeof(ALT_PEN20_SHADRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_SHADRAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Shadramon";
    inline static constexpr const char* ALT_PEN20_SHADRAMON_FQNAME = ALT_PEN20_SHADRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_SHADRAMON_FQNAME_LEN = sizeof(ALT_PEN20_SHADRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_SHAKOMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:shakomon";
    inline static constexpr const char* ALT_PEN20_SHAKOMON_FQID = ALT_PEN20_SHAKOMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_SHAKOMON_FQID_LEN = sizeof(ALT_PEN20_SHAKOMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_SHAKOMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Shakomon";
    inline static constexpr const char* ALT_PEN20_SHAKOMON_FQNAME = ALT_PEN20_SHAKOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_SHAKOMON_FQNAME_LEN = sizeof(ALT_PEN20_SHAKOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_SKULL_MAMMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:skull_mammon";
    inline static constexpr const char* ALT_PEN20_SKULL_MAMMON_FQID = ALT_PEN20_SKULL_MAMMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_SKULL_MAMMON_FQID_LEN = sizeof(ALT_PEN20_SKULL_MAMMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_SKULL_MAMMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Skull Mammon";
    inline static constexpr const char* ALT_PEN20_SKULL_MAMMON_FQNAME = ALT_PEN20_SKULL_MAMMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_SKULL_MAMMON_FQNAME_LEN = sizeof(ALT_PEN20_SKULL_MAMMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_SLAYERDRAMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:slayerdramon";
    inline static constexpr const char* ALT_PEN20_SLAYERDRAMON_FQID = ALT_PEN20_SLAYERDRAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_SLAYERDRAMON_FQID_LEN = sizeof(ALT_PEN20_SLAYERDRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_SLAYERDRAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Slayerdramon";
    inline static constexpr const char* ALT_PEN20_SLAYERDRAMON_FQNAME = ALT_PEN20_SLAYERDRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_SLAYERDRAMON_FQNAME_LEN = sizeof(ALT_PEN20_SLAYERDRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_STARMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:starmon";
    inline static constexpr const char* ALT_PEN20_STARMON_FQID = ALT_PEN20_STARMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_STARMON_FQID_LEN = sizeof(ALT_PEN20_STARMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_STARMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Starmon";
    inline static constexpr const char* ALT_PEN20_STARMON_FQNAME = ALT_PEN20_STARMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_STARMON_FQNAME_LEN = sizeof(ALT_PEN20_STARMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_SUNFLOWMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:sunflowmon";
    inline static constexpr const char* ALT_PEN20_SUNFLOWMON_FQID = ALT_PEN20_SUNFLOWMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_SUNFLOWMON_FQID_LEN = sizeof(ALT_PEN20_SUNFLOWMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_SUNFLOWMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Sunflowmon";
    inline static constexpr const char* ALT_PEN20_SUNFLOWMON_FQNAME = ALT_PEN20_SUNFLOWMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_SUNFLOWMON_FQNAME_LEN = sizeof(ALT_PEN20_SUNFLOWMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_TAILMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:tailmon";
    inline static constexpr const char* ALT_PEN20_TAILMON_FQID = ALT_PEN20_TAILMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_TAILMON_FQID_LEN = sizeof(ALT_PEN20_TAILMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_TAILMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Tailmon";
    inline static constexpr const char* ALT_PEN20_TAILMON_FQNAME = ALT_PEN20_TAILMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_TAILMON_FQNAME_LEN = sizeof(ALT_PEN20_TAILMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_TANKMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:tankmon";
    inline static constexpr const char* ALT_PEN20_TANKMON_FQID = ALT_PEN20_TANKMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_TANKMON_FQID_LEN = sizeof(ALT_PEN20_TANKMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_TANKMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Tankmon";
    inline static constexpr const char* ALT_PEN20_TANKMON_FQNAME = ALT_PEN20_TANKMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_TANKMON_FQNAME_LEN = sizeof(ALT_PEN20_TANKMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_TARGETMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:targetmon";
    inline static constexpr const char* ALT_PEN20_TARGETMON_FQID = ALT_PEN20_TARGETMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_TARGETMON_FQID_LEN = sizeof(ALT_PEN20_TARGETMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_TARGETMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Targetmon";
    inline static constexpr const char* ALT_PEN20_TARGETMON_FQNAME = ALT_PEN20_TARGETMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_TARGETMON_FQNAME_LEN = sizeof(ALT_PEN20_TARGETMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_TENTOMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:tentomon";
    inline static constexpr const char* ALT_PEN20_TENTOMON_FQID = ALT_PEN20_TENTOMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_TENTOMON_FQID_LEN = sizeof(ALT_PEN20_TENTOMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_TENTOMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Tentomon";
    inline static constexpr const char* ALT_PEN20_TENTOMON_FQNAME = ALT_PEN20_TENTOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_TENTOMON_FQNAME_LEN = sizeof(ALT_PEN20_TENTOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_TERRIERMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:terriermon";
    inline static constexpr const char* ALT_PEN20_TERRIERMON_FQID = ALT_PEN20_TERRIERMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_TERRIERMON_FQID_LEN = sizeof(ALT_PEN20_TERRIERMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_TERRIERMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Terriermon";
    inline static constexpr const char* ALT_PEN20_TERRIERMON_FQNAME = ALT_PEN20_TERRIERMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_TERRIERMON_FQNAME_LEN = sizeof(ALT_PEN20_TERRIERMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_THUNDERBALLMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:thunderballmon";
    inline static constexpr const char* ALT_PEN20_THUNDERBALLMON_FQID = ALT_PEN20_THUNDERBALLMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_THUNDERBALLMON_FQID_LEN = sizeof(ALT_PEN20_THUNDERBALLMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_THUNDERBALLMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Thunderballmon";
    inline static constexpr const char* ALT_PEN20_THUNDERBALLMON_FQNAME = ALT_PEN20_THUNDERBALLMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_THUNDERBALLMON_FQNAME_LEN = sizeof(ALT_PEN20_THUNDERBALLMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_TIA_LUDOMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:tia_ludomon";
    inline static constexpr const char* ALT_PEN20_TIA_LUDOMON_FQID = ALT_PEN20_TIA_LUDOMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_TIA_LUDOMON_FQID_LEN = sizeof(ALT_PEN20_TIA_LUDOMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_TIA_LUDOMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Tia Ludomon";
    inline static constexpr const char* ALT_PEN20_TIA_LUDOMON_FQNAME = ALT_PEN20_TIA_LUDOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_TIA_LUDOMON_FQNAME_LEN = sizeof(ALT_PEN20_TIA_LUDOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_TOGEMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:togemon";
    inline static constexpr const char* ALT_PEN20_TOGEMON_FQID = ALT_PEN20_TOGEMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_TOGEMON_FQID_LEN = sizeof(ALT_PEN20_TOGEMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_TOGEMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Togemon";
    inline static constexpr const char* ALT_PEN20_TOGEMON_FQNAME = ALT_PEN20_TOGEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_TOGEMON_FQNAME_LEN = sizeof(ALT_PEN20_TOGEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_TONOSAMA_GEKOMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:tonosama_gekomon";
    inline static constexpr const char* ALT_PEN20_TONOSAMA_GEKOMON_FQID = ALT_PEN20_TONOSAMA_GEKOMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_TONOSAMA_GEKOMON_FQID_LEN = sizeof(ALT_PEN20_TONOSAMA_GEKOMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_TONOSAMA_GEKOMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Tonosama Gekomon";
    inline static constexpr const char* ALT_PEN20_TONOSAMA_GEKOMON_FQNAME = ALT_PEN20_TONOSAMA_GEKOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_TONOSAMA_GEKOMON_FQNAME_LEN = sizeof(ALT_PEN20_TONOSAMA_GEKOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_TORTAMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:tortamon";
    inline static constexpr const char* ALT_PEN20_TORTAMON_FQID = ALT_PEN20_TORTAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_TORTAMON_FQID_LEN = sizeof(ALT_PEN20_TORTAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_TORTAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Tortamon";
    inline static constexpr const char* ALT_PEN20_TORTAMON_FQNAME = ALT_PEN20_TORTAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_TORTAMON_FQNAME_LEN = sizeof(ALT_PEN20_TORTAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_TOY_AGUMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:toy_agumon";
    inline static constexpr const char* ALT_PEN20_TOY_AGUMON_FQID = ALT_PEN20_TOY_AGUMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_TOY_AGUMON_FQID_LEN = sizeof(ALT_PEN20_TOY_AGUMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_TOY_AGUMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Toy Agumon";
    inline static constexpr const char* ALT_PEN20_TOY_AGUMON_FQNAME = ALT_PEN20_TOY_AGUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_TOY_AGUMON_FQNAME_LEN = sizeof(ALT_PEN20_TOY_AGUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_TRICERAMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:triceramon";
    inline static constexpr const char* ALT_PEN20_TRICERAMON_FQID = ALT_PEN20_TRICERAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_TRICERAMON_FQID_LEN = sizeof(ALT_PEN20_TRICERAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_TRICERAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Triceramon";
    inline static constexpr const char* ALT_PEN20_TRICERAMON_FQNAME = ALT_PEN20_TRICERAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_TRICERAMON_FQNAME_LEN = sizeof(ALT_PEN20_TRICERAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_TROOPMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:troopmon";
    inline static constexpr const char* ALT_PEN20_TROOPMON_FQID = ALT_PEN20_TROOPMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_TROOPMON_FQID_LEN = sizeof(ALT_PEN20_TROOPMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_TROOPMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Troopmon";
    inline static constexpr const char* ALT_PEN20_TROOPMON_FQNAME = ALT_PEN20_TROOPMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_TROOPMON_FQNAME_LEN = sizeof(ALT_PEN20_TROOPMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_TURUIEMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:turuiemon";
    inline static constexpr const char* ALT_PEN20_TURUIEMON_FQID = ALT_PEN20_TURUIEMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_TURUIEMON_FQID_LEN = sizeof(ALT_PEN20_TURUIEMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_TURUIEMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Turuiemon";
    inline static constexpr const char* ALT_PEN20_TURUIEMON_FQNAME = ALT_PEN20_TURUIEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_TURUIEMON_FQNAME_LEN = sizeof(ALT_PEN20_TURUIEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_VAMDEMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:vamdemon";
    inline static constexpr const char* ALT_PEN20_VAMDEMON_FQID = ALT_PEN20_VAMDEMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_VAMDEMON_FQID_LEN = sizeof(ALT_PEN20_VAMDEMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_VAMDEMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Vamdemon";
    inline static constexpr const char* ALT_PEN20_VAMDEMON_FQNAME = ALT_PEN20_VAMDEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_VAMDEMON_FQNAME_LEN = sizeof(ALT_PEN20_VAMDEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_V_DRAMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:v_dramon";
    inline static constexpr const char* ALT_PEN20_V_DRAMON_FQID = ALT_PEN20_V_DRAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_V_DRAMON_FQID_LEN = sizeof(ALT_PEN20_V_DRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_V_DRAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:V-dramon";
    inline static constexpr const char* ALT_PEN20_V_DRAMON_FQNAME = ALT_PEN20_V_DRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_V_DRAMON_FQNAME_LEN = sizeof(ALT_PEN20_V_DRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_VENOM_VAMDEMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:venom_vamdemon";
    inline static constexpr const char* ALT_PEN20_VENOM_VAMDEMON_FQID = ALT_PEN20_VENOM_VAMDEMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_VENOM_VAMDEMON_FQID_LEN = sizeof(ALT_PEN20_VENOM_VAMDEMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_VENOM_VAMDEMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Venom Vamdemon";
    inline static constexpr const char* ALT_PEN20_VENOM_VAMDEMON_FQNAME = ALT_PEN20_VENOM_VAMDEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_VENOM_VAMDEMON_FQNAME_LEN = sizeof(ALT_PEN20_VENOM_VAMDEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_V_MON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:v_mon";
    inline static constexpr const char* ALT_PEN20_V_MON_FQID = ALT_PEN20_V_MON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_V_MON_FQID_LEN = sizeof(ALT_PEN20_V_MON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_V_MON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:V-mon";
    inline static constexpr const char* ALT_PEN20_V_MON_FQNAME = ALT_PEN20_V_MON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_V_MON_FQNAME_LEN = sizeof(ALT_PEN20_V_MON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_VOLCANICDRAMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:volcanicdramon";
    inline static constexpr const char* ALT_PEN20_VOLCANICDRAMON_FQID = ALT_PEN20_VOLCANICDRAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_VOLCANICDRAMON_FQID_LEN = sizeof(ALT_PEN20_VOLCANICDRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_VOLCANICDRAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Volcanicdramon";
    inline static constexpr const char* ALT_PEN20_VOLCANICDRAMON_FQNAME = ALT_PEN20_VOLCANICDRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_VOLCANICDRAMON_FQNAME_LEN = sizeof(ALT_PEN20_VOLCANICDRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_VOLTOBAUTAMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:voltobautamon";
    inline static constexpr const char* ALT_PEN20_VOLTOBAUTAMON_FQID = ALT_PEN20_VOLTOBAUTAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_VOLTOBAUTAMON_FQID_LEN = sizeof(ALT_PEN20_VOLTOBAUTAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_VOLTOBAUTAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Voltobautamon";
    inline static constexpr const char* ALT_PEN20_VOLTOBAUTAMON_FQNAME = ALT_PEN20_VOLTOBAUTAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_VOLTOBAUTAMON_FQNAME_LEN = sizeof(ALT_PEN20_VOLTOBAUTAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_VORVOMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:vorvomon";
    inline static constexpr const char* ALT_PEN20_VORVOMON_FQID = ALT_PEN20_VORVOMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_VORVOMON_FQID_LEN = sizeof(ALT_PEN20_VORVOMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_VORVOMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Vorvomon";
    inline static constexpr const char* ALT_PEN20_VORVOMON_FQNAME = ALT_PEN20_VORVOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_VORVOMON_FQNAME_LEN = sizeof(ALT_PEN20_VORVOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_WAR_GREYMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:war_greymon";
    inline static constexpr const char* ALT_PEN20_WAR_GREYMON_FQID = ALT_PEN20_WAR_GREYMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_WAR_GREYMON_FQID_LEN = sizeof(ALT_PEN20_WAR_GREYMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_WAR_GREYMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:War Greymon";
    inline static constexpr const char* ALT_PEN20_WAR_GREYMON_FQNAME = ALT_PEN20_WAR_GREYMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_WAR_GREYMON_FQNAME_LEN = sizeof(ALT_PEN20_WAR_GREYMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_WARU_MONZAEMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:waru_monzaemon";
    inline static constexpr const char* ALT_PEN20_WARU_MONZAEMON_FQID = ALT_PEN20_WARU_MONZAEMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_WARU_MONZAEMON_FQID_LEN = sizeof(ALT_PEN20_WARU_MONZAEMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_WARU_MONZAEMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Waru Monzaemon";
    inline static constexpr const char* ALT_PEN20_WARU_MONZAEMON_FQNAME = ALT_PEN20_WARU_MONZAEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_WARU_MONZAEMON_FQNAME_LEN = sizeof(ALT_PEN20_WARU_MONZAEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_WERE_GARURUMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:were_garurumon";
    inline static constexpr const char* ALT_PEN20_WERE_GARURUMON_FQID = ALT_PEN20_WERE_GARURUMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_WERE_GARURUMON_FQID_LEN = sizeof(ALT_PEN20_WERE_GARURUMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_WERE_GARURUMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Were Garurumon";
    inline static constexpr const char* ALT_PEN20_WERE_GARURUMON_FQNAME = ALT_PEN20_WERE_GARURUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_WERE_GARURUMON_FQNAME_LEN = sizeof(ALT_PEN20_WERE_GARURUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_WHAMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:whamon";
    inline static constexpr const char* ALT_PEN20_WHAMON_FQID = ALT_PEN20_WHAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_WHAMON_FQID_LEN = sizeof(ALT_PEN20_WHAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_WHAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Whamon";
    inline static constexpr const char* ALT_PEN20_WHAMON_FQNAME = ALT_PEN20_WHAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_WHAMON_FQNAME_LEN = sizeof(ALT_PEN20_WHAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_WINGDRAMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:wingdramon";
    inline static constexpr const char* ALT_PEN20_WINGDRAMON_FQID = ALT_PEN20_WINGDRAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_WINGDRAMON_FQID_LEN = sizeof(ALT_PEN20_WINGDRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_WINGDRAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Wingdramon";
    inline static constexpr const char* ALT_PEN20_WINGDRAMON_FQNAME = ALT_PEN20_WINGDRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_WINGDRAMON_FQNAME_LEN = sizeof(ALT_PEN20_WINGDRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_WIZARMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:wizarmon";
    inline static constexpr const char* ALT_PEN20_WIZARMON_FQID = ALT_PEN20_WIZARMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_WIZARMON_FQID_LEN = sizeof(ALT_PEN20_WIZARMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_WIZARMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Wizarmon";
    inline static constexpr const char* ALT_PEN20_WIZARMON_FQNAME = ALT_PEN20_WIZARMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_WIZARMON_FQNAME_LEN = sizeof(ALT_PEN20_WIZARMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_WOODMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:woodmon";
    inline static constexpr const char* ALT_PEN20_WOODMON_FQID = ALT_PEN20_WOODMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_WOODMON_FQID_LEN = sizeof(ALT_PEN20_WOODMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_WOODMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Woodmon";
    inline static constexpr const char* ALT_PEN20_WOODMON_FQNAME = ALT_PEN20_WOODMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_WOODMON_FQNAME_LEN = sizeof(ALT_PEN20_WOODMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_XV_MON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:xv_mon";
    inline static constexpr const char* ALT_PEN20_XV_MON_FQID = ALT_PEN20_XV_MON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_XV_MON_FQID_LEN = sizeof(ALT_PEN20_XV_MON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_XV_MON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:XV-mon";
    inline static constexpr const char* ALT_PEN20_XV_MON_FQNAME = ALT_PEN20_XV_MON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_XV_MON_FQNAME_LEN = sizeof(ALT_PEN20_XV_MON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_YUKIMI_BOTAMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:yukimi_botamon";
    inline static constexpr const char* ALT_PEN20_YUKIMI_BOTAMON_FQID = ALT_PEN20_YUKIMI_BOTAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_YUKIMI_BOTAMON_FQID_LEN = sizeof(ALT_PEN20_YUKIMI_BOTAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_YUKIMI_BOTAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Yukimi Botamon";
    inline static constexpr const char* ALT_PEN20_YUKIMI_BOTAMON_FQNAME = ALT_PEN20_YUKIMI_BOTAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_YUKIMI_BOTAMON_FQNAME_LEN = sizeof(ALT_PEN20_YUKIMI_BOTAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_ZERIMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:zerimon";
    inline static constexpr const char* ALT_PEN20_ZERIMON_FQID = ALT_PEN20_ZERIMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_ZERIMON_FQID_LEN = sizeof(ALT_PEN20_ZERIMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_ZERIMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Zerimon";
    inline static constexpr const char* ALT_PEN20_ZERIMON_FQNAME = ALT_PEN20_ZERIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_ZERIMON_FQNAME_LEN = sizeof(ALT_PEN20_ZERIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_ZUBAEAGERMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:zubaeagermon";
    inline static constexpr const char* ALT_PEN20_ZUBAEAGERMON_FQID = ALT_PEN20_ZUBAEAGERMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_ZUBAEAGERMON_FQID_LEN = sizeof(ALT_PEN20_ZUBAEAGERMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_ZUBAEAGERMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Zubaeagermon";
    inline static constexpr const char* ALT_PEN20_ZUBAEAGERMON_FQNAME = ALT_PEN20_ZUBAEAGERMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_ZUBAEAGERMON_FQNAME_LEN = sizeof(ALT_PEN20_ZUBAEAGERMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_ZUBAMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:zubamon";
    inline static constexpr const char* ALT_PEN20_ZUBAMON_FQID = ALT_PEN20_ZUBAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_ZUBAMON_FQID_LEN = sizeof(ALT_PEN20_ZUBAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_ZUBAMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Zubamon";
    inline static constexpr const char* ALT_PEN20_ZUBAMON_FQNAME = ALT_PEN20_ZUBAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_ZUBAMON_FQNAME_LEN = sizeof(ALT_PEN20_ZUBAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_ZUDOMON_FQID_ARR[] CONFIG_STRING_SECTION = "pen:zudomon";
    inline static constexpr const char* ALT_PEN20_ZUDOMON_FQID = ALT_PEN20_ZUDOMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_ZUDOMON_FQID_LEN = sizeof(ALT_PEN20_ZUDOMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_ZUDOMON_FQNAME_ARR[] CONFIG_STRING_SECTION = "pen:Zudomon";
    inline static constexpr const char* ALT_PEN20_ZUDOMON_FQNAME = ALT_PEN20_ZUDOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_ZUDOMON_FQNAME_LEN = sizeof(ALT_PEN20_ZUDOMON_FQNAME_ARR)-1;

    struct pen20_animation_table_entry_t {
        config_animation_entry_t normal;
        struct {
            const char *fqid{""};
            const char *fqname{""};
        } alt;
    };
    static const pen20_animation_table_entry_t pen20_animation_table[] = {
        { { PEN20_AERO_V_DRAMON_NAME, PEN20_AERO_V_DRAMON_ID, PEN20_AERO_V_DRAMON_FQID, PEN20_AERO_V_DRAMON_FQNAME, PEN20_AERO_V_DRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_AERO_V_DRAMON_FQID, ALT_PEN20_AERO_V_DRAMON_FQNAME } },  // Aero V-dramon
        { { PEN20_AGUMON_HAKASE_NAME, PEN20_AGUMON_HAKASE_ID, PEN20_AGUMON_HAKASE_FQID, PEN20_AGUMON_HAKASE_FQNAME, PEN20_AGUMON_HAKASE_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_AGUMON_HAKASE_FQID, ALT_PEN20_AGUMON_HAKASE_FQNAME } },  // Agumon Hakase
        { { PEN20_AGUMON_NAME, PEN20_AGUMON_ID, PEN20_AGUMON_FQID, PEN20_AGUMON_FQNAME, PEN20_AGUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_AGUMON_FQID, ALT_PEN20_AGUMON_FQNAME } },  // Agumon
        { { PEN20_ALPHAMON_OURYUKEN_NAME, PEN20_ALPHAMON_OURYUKEN_ID, PEN20_ALPHAMON_OURYUKEN_FQID, PEN20_ALPHAMON_OURYUKEN_FQNAME, PEN20_ALPHAMON_OURYUKEN_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_ALPHAMON_OURYUKEN_FQID, ALT_PEN20_ALPHAMON_OURYUKEN_FQNAME } },  // Alphamon Ouryuken
        { { PEN20_ALPHAMON_NAME, PEN20_ALPHAMON_ID, PEN20_ALPHAMON_FQID, PEN20_ALPHAMON_FQNAME, PEN20_ALPHAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_ALPHAMON_FQID, ALT_PEN20_ALPHAMON_FQNAME } },  // Alphamon
        { { PEN20_ANDIRAMON_NAME, PEN20_ANDIRAMON_ID, PEN20_ANDIRAMON_FQID, PEN20_ANDIRAMON_FQNAME, PEN20_ANDIRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_ANDIRAMON_FQID, ALT_PEN20_ANDIRAMON_FQNAME } },  // Andiramon
        { { PEN20_ANDROMON_NAME, PEN20_ANDROMON_ID, PEN20_ANDROMON_FQID, PEN20_ANDROMON_FQNAME, PEN20_ANDROMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_ANDROMON_FQID, ALT_PEN20_ANDROMON_FQNAME } },  // Andromon
        { { PEN20_ANGEMON_NAME, PEN20_ANGEMON_ID, PEN20_ANGEMON_FQID, PEN20_ANGEMON_FQNAME, PEN20_ANGEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_ANGEMON_FQID, ALT_PEN20_ANGEMON_FQNAME } },  // Angemon
        { { PEN20_ANGEWOMON_NAME, PEN20_ANGEWOMON_ID, PEN20_ANGEWOMON_FQID, PEN20_ANGEWOMON_FQNAME, PEN20_ANGEWOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_ANGEWOMON_FQID, ALT_PEN20_ANGEWOMON_FQNAME } },  // Angewomon
        { { PEN20_ANOMALOCARIMON_NAME, PEN20_ANOMALOCARIMON_ID, PEN20_ANOMALOCARIMON_FQID, PEN20_ANOMALOCARIMON_FQNAME, PEN20_ANOMALOCARIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_ANOMALOCARIMON_FQID, ALT_PEN20_ANOMALOCARIMON_FQNAME } },  // Anomalocarimon
        { { PEN20_ARRESTERDRAMON_NAME, PEN20_ARRESTERDRAMON_ID, PEN20_ARRESTERDRAMON_FQID, PEN20_ARRESTERDRAMON_FQNAME, PEN20_ARRESTERDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_ARRESTERDRAMON_FQID, ALT_PEN20_ARRESTERDRAMON_FQNAME } },  // Arresterdramon
        { { PEN20_ASTAMON_NAME, PEN20_ASTAMON_ID, PEN20_ASTAMON_FQID, PEN20_ASTAMON_FQNAME, PEN20_ASTAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_ASTAMON_FQID, ALT_PEN20_ASTAMON_FQNAME } },  // Astamon
        { { PEN20_ASURAMON_NAME, PEN20_ASURAMON_ID, PEN20_ASURAMON_FQID, PEN20_ASURAMON_FQNAME, PEN20_ASURAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_ASURAMON_FQID, ALT_PEN20_ASURAMON_FQNAME } },  // Asuramon
        { { PEN20_ATLUR_KABUTERIMON_NAME, PEN20_ATLUR_KABUTERIMON_ID, PEN20_ATLUR_KABUTERIMON_FQID, PEN20_ATLUR_KABUTERIMON_FQNAME, PEN20_ATLUR_KABUTERIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_ATLUR_KABUTERIMON_FQID, ALT_PEN20_ATLUR_KABUTERIMON_FQNAME } },  // Atlur Kabuterimon
        { { PEN20_BAALMON_NAME, PEN20_BAALMON_ID, PEN20_BAALMON_FQID, PEN20_BAALMON_FQNAME, PEN20_BAALMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_BAALMON_FQID, ALT_PEN20_BAALMON_FQNAME } },  // Baalmon
        { { PEN20_BABYDMON_NAME, PEN20_BABYDMON_ID, PEN20_BABYDMON_FQID, PEN20_BABYDMON_FQNAME, PEN20_BABYDMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_BABYDMON_FQID, ALT_PEN20_BABYDMON_FQNAME } },  // Babydmon
        { { PEN20_BAKEMON_NAME, PEN20_BAKEMON_ID, PEN20_BAKEMON_FQID, PEN20_BAKEMON_FQNAME, PEN20_BAKEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_BAKEMON_FQID, ALT_PEN20_BAKEMON_FQNAME } },  // Bakemon
        { { PEN20_BAKUMON_NAME, PEN20_BAKUMON_ID, PEN20_BAKUMON_FQID, PEN20_BAKUMON_FQNAME, PEN20_BAKUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_BAKUMON_FQID, ALT_PEN20_BAKUMON_FQNAME } },  // Bakumon
        { { PEN20_BANCHO_LEOMON_NAME, PEN20_BANCHO_LEOMON_ID, PEN20_BANCHO_LEOMON_FQID, PEN20_BANCHO_LEOMON_FQNAME, PEN20_BANCHO_LEOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_BANCHO_LEOMON_FQID, ALT_PEN20_BANCHO_LEOMON_FQNAME } },  // Bancho Leomon
        { { PEN20_BAO_HACKMON_NAME, PEN20_BAO_HACKMON_ID, PEN20_BAO_HACKMON_FQID, PEN20_BAO_HACKMON_FQNAME, PEN20_BAO_HACKMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_BAO_HACKMON_FQID, ALT_PEN20_BAO_HACKMON_FQNAME } },  // Bao Hackmon
        { { PEN20_BEELZEBUMON_BLAST_MODE_NAME, PEN20_BEELZEBUMON_BLAST_MODE_ID, PEN20_BEELZEBUMON_BLAST_MODE_FQID, PEN20_BEELZEBUMON_BLAST_MODE_FQNAME, PEN20_BEELZEBUMON_BLAST_MODE_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_BEELZEBUMON_BLAST_MODE_FQID, ALT_PEN20_BEELZEBUMON_BLAST_MODE_FQNAME } },  // Beelzebumon Blast Mode
        { { PEN20_BEOWOLFMON_NAME, PEN20_BEOWOLFMON_ID, PEN20_BEOWOLFMON_FQID, PEN20_BEOWOLFMON_FQNAME, PEN20_BEOWOLFMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_BEOWOLFMON_FQID, ALT_PEN20_BEOWOLFMON_FQNAME } },  // Beowolfmon
        { { PEN20_BIG_MAMEMON_NAME, PEN20_BIG_MAMEMON_ID, PEN20_BIG_MAMEMON_FQID, PEN20_BIG_MAMEMON_FQNAME, PEN20_BIG_MAMEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_BIG_MAMEMON_FQID, ALT_PEN20_BIG_MAMEMON_FQNAME } },  // Big Mamemon
        { { PEN20_BIRDRAMON_NAME, PEN20_BIRDRAMON_ID, PEN20_BIRDRAMON_FQID, PEN20_BIRDRAMON_FQNAME, PEN20_BIRDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_BIRDRAMON_FQID, ALT_PEN20_BIRDRAMON_FQNAME } },  // Birdramon
        { { PEN20_BLOSSOMON_NAME, PEN20_BLOSSOMON_ID, PEN20_BLOSSOMON_FQID, PEN20_BLOSSOMON_FQNAME, PEN20_BLOSSOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_BLOSSOMON_FQID, ALT_PEN20_BLOSSOMON_FQNAME } },  // Blossomon
        { { PEN20_BOLTMON_NAME, PEN20_BOLTMON_ID, PEN20_BOLTMON_FQID, PEN20_BOLTMON_FQNAME, PEN20_BOLTMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_BOLTMON_FQID, ALT_PEN20_BOLTMON_FQNAME } },  // Boltmon
        { { PEN20_BOTAMON_NAME, PEN20_BOTAMON_ID, PEN20_BOTAMON_FQID, PEN20_BOTAMON_FQNAME, PEN20_BOTAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_BOTAMON_FQID, ALT_PEN20_BOTAMON_FQNAME } },  // Botamon
        { { PEN20_BREAKDRAMON_NAME, PEN20_BREAKDRAMON_ID, PEN20_BREAKDRAMON_FQID, PEN20_BREAKDRAMON_FQNAME, PEN20_BREAKDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_BREAKDRAMON_FQID, ALT_PEN20_BREAKDRAMON_FQNAME } },  // Breakdramon
        { { PEN20_BRYWELUDRAMON_NAME, PEN20_BRYWELUDRAMON_ID, PEN20_BRYWELUDRAMON_FQID, PEN20_BRYWELUDRAMON_FQNAME, PEN20_BRYWELUDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_BRYWELUDRAMON_FQID, ALT_PEN20_BRYWELUDRAMON_FQNAME } },  // Bryweludramon
        { { PEN20_BUBBMON_NAME, PEN20_BUBBMON_ID, PEN20_BUBBMON_FQID, PEN20_BUBBMON_FQNAME, PEN20_BUBBMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_BUBBMON_FQID, ALT_PEN20_BUBBMON_FQNAME } },  // Bubbmon
        { { PEN20_BUDMON_NAME, PEN20_BUDMON_ID, PEN20_BUDMON_FQID, PEN20_BUDMON_FQNAME, PEN20_BUDMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_BUDMON_FQID, ALT_PEN20_BUDMON_FQNAME } },  // Budmon
        { { PEN20_BUSHI_AGUMON_NAME, PEN20_BUSHI_AGUMON_ID, PEN20_BUSHI_AGUMON_FQID, PEN20_BUSHI_AGUMON_FQNAME, PEN20_BUSHI_AGUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_BUSHI_AGUMON_FQID, ALT_PEN20_BUSHI_AGUMON_FQNAME } },  // Bushi Agumon
        { { PEN20_CANDMON_NAME, PEN20_CANDMON_ID, PEN20_CANDMON_FQID, PEN20_CANDMON_FQNAME, PEN20_CANDMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_CANDMON_FQID, ALT_PEN20_CANDMON_FQNAME } },  // Candmon
        { { PEN20_CAPRIMON_NAME, PEN20_CAPRIMON_ID, PEN20_CAPRIMON_FQID, PEN20_CAPRIMON_FQNAME, PEN20_CAPRIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_CAPRIMON_FQID, ALT_PEN20_CAPRIMON_FQNAME } },  // Caprimon
        { { PEN20_CHAOSMON_NAME, PEN20_CHAOSMON_ID, PEN20_CHAOSMON_FQID, PEN20_CHAOSMON_FQNAME, PEN20_CHAOSMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_CHAOSMON_FQID, ALT_PEN20_CHAOSMON_FQNAME } },  // Chaosmon
        { { PEN20_CHERUBIMON_NAME, PEN20_CHERUBIMON_ID, PEN20_CHERUBIMON_FQID, PEN20_CHERUBIMON_FQNAME, PEN20_CHERUBIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_CHERUBIMON_FQID, ALT_PEN20_CHERUBIMON_FQNAME } },  // Cherubimon
        { { PEN20_CHIBIMON_NAME, PEN20_CHIBIMON_ID, PEN20_CHIBIMON_FQID, PEN20_CHIBIMON_FQNAME, PEN20_CHIBIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_CHIBIMON_FQID, ALT_PEN20_CHIBIMON_FQNAME } },  // Chibimon
        { { PEN20_CHICOMON_NAME, PEN20_CHICOMON_ID, PEN20_CHICOMON_FQID, PEN20_CHICOMON_FQNAME, PEN20_CHICOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_CHICOMON_FQID, ALT_PEN20_CHICOMON_FQNAME } },  // Chicomon
        { { PEN20_CHOCOMON_NAME, PEN20_CHOCOMON_ID, PEN20_CHOCOMON_FQID, PEN20_CHOCOMON_FQNAME, PEN20_CHOCOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_CHOCOMON_FQID, ALT_PEN20_CHOCOMON_FQNAME } },  // Chocomon
        { { PEN20_CHOROMON_NAME, PEN20_CHOROMON_ID, PEN20_CHOROMON_FQID, PEN20_CHOROMON_FQNAME, PEN20_CHOROMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_CHOROMON_FQID, ALT_PEN20_CHOROMON_FQNAME } },  // Choromon
        { { PEN20_CLOCKMON_NAME, PEN20_CLOCKMON_ID, PEN20_CLOCKMON_FQID, PEN20_CLOCKMON_FQNAME, PEN20_CLOCKMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_CLOCKMON_FQID, ALT_PEN20_CLOCKMON_FQNAME } },  // Clockmon
        { { PEN20_COCOMON_NAME, PEN20_COCOMON_ID, PEN20_COCOMON_FQID, PEN20_COCOMON_FQNAME, PEN20_COCOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_COCOMON_FQID, ALT_PEN20_COCOMON_FQNAME } },  // Cocomon
        { { PEN20_COELAMON_NAME, PEN20_COELAMON_ID, PEN20_COELAMON_FQID, PEN20_COELAMON_FQNAME, PEN20_COELAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_COELAMON_FQID, ALT_PEN20_COELAMON_FQNAME } },  // Coelamon
        { { PEN20_COREDRAMON_BLUE_NAME, PEN20_COREDRAMON_BLUE_ID, PEN20_COREDRAMON_BLUE_FQID, PEN20_COREDRAMON_BLUE_FQNAME, PEN20_COREDRAMON_BLUE_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_COREDRAMON_BLUE_FQID, ALT_PEN20_COREDRAMON_BLUE_FQNAME } },  // Coredramon (Blue)
        { { PEN20_COREDRAMON_GREEN_NAME, PEN20_COREDRAMON_GREEN_ID, PEN20_COREDRAMON_GREEN_FQID, PEN20_COREDRAMON_GREEN_FQNAME, PEN20_COREDRAMON_GREEN_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_COREDRAMON_GREEN_FQID, ALT_PEN20_COREDRAMON_GREEN_FQNAME } },  // Coredramon (Green)
        { { PEN20_COTSUCOMON_NAME, PEN20_COTSUCOMON_ID, PEN20_COTSUCOMON_FQID, PEN20_COTSUCOMON_FQNAME, PEN20_COTSUCOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_COTSUCOMON_FQID, ALT_PEN20_COTSUCOMON_FQNAME } },  // Cotsucomon
        { { PEN20_CYBERDRAMON_NAME, PEN20_CYBERDRAMON_ID, PEN20_CYBERDRAMON_FQID, PEN20_CYBERDRAMON_FQNAME, PEN20_CYBERDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_CYBERDRAMON_FQID, ALT_PEN20_CYBERDRAMON_FQNAME } },  // Cyberdramon
        { { PEN20_DAGOMON_NAME, PEN20_DAGOMON_ID, PEN20_DAGOMON_FQID, PEN20_DAGOMON_FQNAME, PEN20_DAGOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_DAGOMON_FQID, ALT_PEN20_DAGOMON_FQNAME } },  // Dagomon
        { { PEN20_DARKDRAMON_NAME, PEN20_DARKDRAMON_ID, PEN20_DARKDRAMON_FQID, PEN20_DARKDRAMON_FQNAME, PEN20_DARKDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_DARKDRAMON_FQID, ALT_PEN20_DARKDRAMON_FQNAME } },  // Darkdramon
        { { PEN20_DARK_KNIGHTMON_NAME, PEN20_DARK_KNIGHTMON_ID, PEN20_DARK_KNIGHTMON_FQID, PEN20_DARK_KNIGHTMON_FQNAME, PEN20_DARK_KNIGHTMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_DARK_KNIGHTMON_FQID, ALT_PEN20_DARK_KNIGHTMON_FQNAME } },  // Dark Knightmon
        { { PEN20_DEATH_MERAMON_NAME, PEN20_DEATH_MERAMON_ID, PEN20_DEATH_MERAMON_FQID, PEN20_DEATH_MERAMON_FQNAME, PEN20_DEATH_MERAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_DEATH_MERAMON_FQID, ALT_PEN20_DEATH_MERAMON_FQNAME } },  // Death Meramon
        { { PEN20_DELUMON_NAME, PEN20_DELUMON_ID, PEN20_DELUMON_FQID, PEN20_DELUMON_FQNAME, PEN20_DELUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_DELUMON_FQID, ALT_PEN20_DELUMON_FQNAME } },  // Delumon
        { { PEN20_DEVIDRAMON_NAME, PEN20_DEVIDRAMON_ID, PEN20_DEVIDRAMON_FQID, PEN20_DEVIDRAMON_FQNAME, PEN20_DEVIDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_DEVIDRAMON_FQID, ALT_PEN20_DEVIDRAMON_FQNAME } },  // Devidramon
        { { PEN20_DEVIMON_NAME, PEN20_DEVIMON_ID, PEN20_DEVIMON_FQID, PEN20_DEVIMON_FQNAME, PEN20_DEVIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_DEVIMON_FQID, ALT_PEN20_DEVIMON_FQNAME } },  // Devimon
        { { PEN20_DODOMON_NAME, PEN20_DODOMON_ID, PEN20_DODOMON_FQID, PEN20_DODOMON_FQNAME, PEN20_DODOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_DODOMON_FQID, ALT_PEN20_DODOMON_FQNAME } },  // Dodomon
        { { PEN20_DOKUGUMON_NAME, PEN20_DOKUGUMON_ID, PEN20_DOKUGUMON_FQID, PEN20_DOKUGUMON_FQNAME, PEN20_DOKUGUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_DOKUGUMON_FQID, ALT_PEN20_DOKUGUMON_FQNAME } },  // Dokugumon
        { { PEN20_DORIMON_NAME, PEN20_DORIMON_ID, PEN20_DORIMON_FQID, PEN20_DORIMON_FQNAME, PEN20_DORIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_DORIMON_FQID, ALT_PEN20_DORIMON_FQNAME } },  // Dorimon
        { { PEN20_DORUGAMON_NAME, PEN20_DORUGAMON_ID, PEN20_DORUGAMON_FQID, PEN20_DORUGAMON_FQNAME, PEN20_DORUGAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_DORUGAMON_FQID, ALT_PEN20_DORUGAMON_FQNAME } },  // DORUgamon
        { { PEN20_DORUGORAMON_NAME, PEN20_DORUGORAMON_ID, PEN20_DORUGORAMON_FQID, PEN20_DORUGORAMON_FQNAME, PEN20_DORUGORAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_DORUGORAMON_FQID, ALT_PEN20_DORUGORAMON_FQNAME } },  // DORUgoramon
        { { PEN20_DORUGUREMON_NAME, PEN20_DORUGUREMON_ID, PEN20_DORUGUREMON_FQID, PEN20_DORUGUREMON_FQNAME, PEN20_DORUGUREMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_DORUGUREMON_FQID, ALT_PEN20_DORUGUREMON_FQNAME } },  // DORUguremon
        { { PEN20_DORUMON_NAME, PEN20_DORUMON_ID, PEN20_DORUMON_FQID, PEN20_DORUMON_FQNAME, PEN20_DORUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_DORUMON_FQID, ALT_PEN20_DORUMON_FQNAME } },  // DORUmon
        { { PEN20_DRACOMON_NAME, PEN20_DRACOMON_ID, PEN20_DRACOMON_FQID, PEN20_DRACOMON_FQNAME, PEN20_DRACOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_DRACOMON_FQID, ALT_PEN20_DRACOMON_FQNAME } },  // Dracomon
        { { PEN20_DURAMON_NAME, PEN20_DURAMON_ID, PEN20_DURAMON_FQID, PEN20_DURAMON_FQNAME, PEN20_DURAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_DURAMON_FQID, ALT_PEN20_DURAMON_FQNAME } },  // Duramon
        { { PEN20_DURANDAMON_NAME, PEN20_DURANDAMON_ID, PEN20_DURANDAMON_FQID, PEN20_DURANDAMON_FQNAME, PEN20_DURANDAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_DURANDAMON_FQID, ALT_PEN20_DURANDAMON_FQNAME } },  // Durandamon
        { { PEN20_EBIDRAMON_NAME, PEN20_EBIDRAMON_ID, PEN20_EBIDRAMON_FQID, PEN20_EBIDRAMON_FQNAME, PEN20_EBIDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_EBIDRAMON_FQID, ALT_PEN20_EBIDRAMON_FQNAME } },  // Ebidramon
        { { PEN20_ETEMON_NAME, PEN20_ETEMON_ID, PEN20_ETEMON_FQID, PEN20_ETEMON_FQNAME, PEN20_ETEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_ETEMON_FQID, ALT_PEN20_ETEMON_FQNAME } },  // Etemon
        { { PEN20_EXAMON_NAME, PEN20_EXAMON_ID, PEN20_EXAMON_FQID, PEN20_EXAMON_FQNAME, PEN20_EXAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_EXAMON_FQID, ALT_PEN20_EXAMON_FQNAME } },  // Examon
        { { PEN20_FANTOMON_NAME, PEN20_FANTOMON_ID, PEN20_FANTOMON_FQID, PEN20_FANTOMON_FQNAME, PEN20_FANTOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_FANTOMON_FQID, ALT_PEN20_FANTOMON_FQNAME } },  // Fantomon
        { { PEN20_FLORAMON_NAME, PEN20_FLORAMON_ID, PEN20_FLORAMON_FQID, PEN20_FLORAMON_FQNAME, PEN20_FLORAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_FLORAMON_FQID, ALT_PEN20_FLORAMON_FQNAME } },  // Floramon
        { { PEN20_FUFUMON_NAME, PEN20_FUFUMON_ID, PEN20_FUFUMON_FQID, PEN20_FUFUMON_FQNAME, PEN20_FUFUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_FUFUMON_FQID, ALT_PEN20_FUFUMON_FQNAME } },  // Fufumon
        { { PEN20_GABUMON_NAME, PEN20_GABUMON_ID, PEN20_GABUMON_FQID, PEN20_GABUMON_FQNAME, PEN20_GABUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_GABUMON_FQID, ALT_PEN20_GABUMON_FQNAME } },  // Gabumon
        { { PEN20_GALGOMON_NAME, PEN20_GALGOMON_ID, PEN20_GALGOMON_FQID, PEN20_GALGOMON_FQNAME, PEN20_GALGOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_GALGOMON_FQID, ALT_PEN20_GALGOMON_FQNAME } },  // Galgomon
        { { PEN20_GANIMON_NAME, PEN20_GANIMON_ID, PEN20_GANIMON_FQID, PEN20_GANIMON_FQNAME, PEN20_GANIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_GANIMON_FQID, ALT_PEN20_GANIMON_FQNAME } },  // Ganimon
        { { PEN20_GARUDAMON_NAME, PEN20_GARUDAMON_ID, PEN20_GARUDAMON_FQID, PEN20_GARUDAMON_FQNAME, PEN20_GARUDAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_GARUDAMON_FQID, ALT_PEN20_GARUDAMON_FQNAME } },  // Garudamon
        { { PEN20_GARURUMON_NAME, PEN20_GARURUMON_ID, PEN20_GARURUMON_FQID, PEN20_GARURUMON_FQNAME, PEN20_GARURUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_GARURUMON_FQID, ALT_PEN20_GARURUMON_FQNAME } },  // Garurumon
        { { PEN20_GEKOMON_NAME, PEN20_GEKOMON_ID, PEN20_GEKOMON_FQID, PEN20_GEKOMON_FQNAME, PEN20_GEKOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_GEKOMON_FQID, ALT_PEN20_GEKOMON_FQNAME } },  // Gekomon
        { { PEN20_GERBEMON_NAME, PEN20_GERBEMON_ID, PEN20_GERBEMON_FQID, PEN20_GERBEMON_FQNAME, PEN20_GERBEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_GERBEMON_FQID, ALT_PEN20_GERBEMON_FQNAME } },  // Gerbemon
        { { PEN20_GESOMON_NAME, PEN20_GESOMON_ID, PEN20_GESOMON_FQID, PEN20_GESOMON_FQNAME, PEN20_GESOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_GESOMON_FQID, ALT_PEN20_GESOMON_FQNAME } },  // Gesomon
        { { PEN20_GINRYUMON_NAME, PEN20_GINRYUMON_ID, PEN20_GINRYUMON_FQID, PEN20_GINRYUMON_FQNAME, PEN20_GINRYUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_GINRYUMON_FQID, ALT_PEN20_GINRYUMON_FQNAME } },  // Ginryumon
        { { PEN20_GOMAMON_NAME, PEN20_GOMAMON_ID, PEN20_GOMAMON_FQID, PEN20_GOMAMON_FQNAME, PEN20_GOMAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_GOMAMON_FQID, ALT_PEN20_GOMAMON_FQNAME } },  // Gomamon
        { { PEN20_GOTTSUMON_NAME, PEN20_GOTTSUMON_ID, PEN20_GOTTSUMON_FQID, PEN20_GOTTSUMON_FQNAME, PEN20_GOTTSUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_GOTTSUMON_FQID, ALT_PEN20_GOTTSUMON_FQNAME } },  // Gottsumon
        { { PEN20_GREYMON_NAME, PEN20_GREYMON_ID, PEN20_GREYMON_FQID, PEN20_GREYMON_FQNAME, PEN20_GREYMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_GREYMON_FQID, ALT_PEN20_GREYMON_FQNAME } },  // Greymon
        { { PEN20_GRIFFOMON_NAME, PEN20_GRIFFOMON_ID, PEN20_GRIFFOMON_FQID, PEN20_GRIFFOMON_FQNAME, PEN20_GRIFFOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_GRIFFOMON_FQID, ALT_PEN20_GRIFFOMON_FQNAME } },  // Griffomon
        { { PEN20_GROUNDRAMON_NAME, PEN20_GROUNDRAMON_ID, PEN20_GROUNDRAMON_FQID, PEN20_GROUNDRAMON_FQNAME, PEN20_GROUNDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_GROUNDRAMON_FQID, ALT_PEN20_GROUNDRAMON_FQNAME } },  // Groundramon
        { { PEN20_GROWMON_NAME, PEN20_GROWMON_ID, PEN20_GROWMON_FQID, PEN20_GROWMON_FQNAME, PEN20_GROWMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_GROWMON_FQID, ALT_PEN20_GROWMON_FQNAME } },  // Growmon
        { { PEN20_GUARDROMON_NAME, PEN20_GUARDROMON_ID, PEN20_GUARDROMON_FQID, PEN20_GUARDROMON_FQNAME, PEN20_GUARDROMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_GUARDROMON_FQID, ALT_PEN20_GUARDROMON_FQNAME } },  // Guardromon
        { { PEN20_GUILMON_NAME, PEN20_GUILMON_ID, PEN20_GUILMON_FQID, PEN20_GUILMON_FQNAME, PEN20_GUILMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_GUILMON_FQID, ALT_PEN20_GUILMON_FQNAME } },  // Guilmon
        { { PEN20_GUMMYMON_NAME, PEN20_GUMMYMON_ID, PEN20_GUMMYMON_FQID, PEN20_GUMMYMON_FQNAME, PEN20_GUMMYMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_GUMMYMON_FQID, ALT_PEN20_GUMMYMON_FQNAME } },  // Gummymon
        { { PEN20_HACKMON_NAME, PEN20_HACKMON_ID, PEN20_HACKMON_FQID, PEN20_HACKMON_FQNAME, PEN20_HACKMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_HACKMON_FQID, ALT_PEN20_HACKMON_FQNAME } },  // Hackmon
        { { PEN20_HAGURUMON_NAME, PEN20_HAGURUMON_ID, PEN20_HAGURUMON_FQID, PEN20_HAGURUMON_FQNAME, PEN20_HAGURUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_HAGURUMON_FQID, ALT_PEN20_HAGURUMON_FQNAME } },  // Hagurumon
        { { PEN20_HANGYOMON_NAME, PEN20_HANGYOMON_ID, PEN20_HANGYOMON_FQID, PEN20_HANGYOMON_FQNAME, PEN20_HANGYOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_HANGYOMON_FQID, ALT_PEN20_HANGYOMON_FQNAME } },  // Hangyomon
        { { PEN20_HANUMON_NAME, PEN20_HANUMON_ID, PEN20_HANUMON_FQID, PEN20_HANUMON_FQNAME, PEN20_HANUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_HANUMON_FQID, ALT_PEN20_HANUMON_FQNAME } },  // Hanumon
        { { PEN20_HERAKLE_KABUTERIMON_NAME, PEN20_HERAKLE_KABUTERIMON_ID, PEN20_HERAKLE_KABUTERIMON_FQID, PEN20_HERAKLE_KABUTERIMON_FQNAME, PEN20_HERAKLE_KABUTERIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_HERAKLE_KABUTERIMON_FQID, ALT_PEN20_HERAKLE_KABUTERIMON_FQNAME } },  // Herakle Kabuterimon
        { { PEN20_HISYARYUMON_NAME, PEN20_HISYARYUMON_ID, PEN20_HISYARYUMON_FQID, PEN20_HISYARYUMON_FQNAME, PEN20_HISYARYUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_HISYARYUMON_FQID, ALT_PEN20_HISYARYUMON_FQNAME } },  // Hisyaryumon
        { { PEN20_HOLY_ANGEMON_NAME, PEN20_HOLY_ANGEMON_ID, PEN20_HOLY_ANGEMON_FQID, PEN20_HOLY_ANGEMON_FQNAME, PEN20_HOLY_ANGEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_HOLY_ANGEMON_FQID, ALT_PEN20_HOLY_ANGEMON_FQNAME } },  // Holy Angemon
        { { PEN20_HOLYDRAMON_NAME, PEN20_HOLYDRAMON_ID, PEN20_HOLYDRAMON_FQID, PEN20_HOLYDRAMON_FQNAME, PEN20_HOLYDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_HOLYDRAMON_FQID, ALT_PEN20_HOLYDRAMON_FQNAME } },  // Holydramon
        { { PEN20_HOUOUMON_NAME, PEN20_HOUOUMON_ID, PEN20_HOUOUMON_FQID, PEN20_HOUOUMON_FQNAME, PEN20_HOUOUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_HOUOUMON_FQID, ALT_PEN20_HOUOUMON_FQNAME } },  // Hououmon
        { { PEN20_IGAMON_NAME, PEN20_IGAMON_ID, PEN20_IGAMON_FQID, PEN20_IGAMON_FQNAME, PEN20_IGAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_IGAMON_FQID, ALT_PEN20_IGAMON_FQNAME } },  // Igamon
        { { PEN20_IKKAKUMON_NAME, PEN20_IKKAKUMON_ID, PEN20_IKKAKUMON_FQID, PEN20_IKKAKUMON_FQNAME, PEN20_IKKAKUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_IKKAKUMON_FQID, ALT_PEN20_IKKAKUMON_FQNAME } },  // Ikkakumon
        { { PEN20_IMPERIALDRAMON_FIGHTER_MODE_NAME, PEN20_IMPERIALDRAMON_FIGHTER_MODE_ID, PEN20_IMPERIALDRAMON_FIGHTER_MODE_FQID, PEN20_IMPERIALDRAMON_FIGHTER_MODE_FQNAME, PEN20_IMPERIALDRAMON_FIGHTER_MODE_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_IMPERIALDRAMON_FIGHTER_MODE_FQID, ALT_PEN20_IMPERIALDRAMON_FIGHTER_MODE_FQNAME } },  // Imperialdramon Fighter Mode
        { { PEN20_IMPMON_NAME, PEN20_IMPMON_ID, PEN20_IMPMON_FQID, PEN20_IMPMON_FQNAME, PEN20_IMPMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_IMPMON_FQID, ALT_PEN20_IMPMON_FQNAME } },  // Impmon
        { { PEN20_JESMON_NAME, PEN20_JESMON_ID, PEN20_JESMON_FQID, PEN20_JESMON_FQNAME, PEN20_JESMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_JESMON_FQID, ALT_PEN20_JESMON_FQNAME } },  // Jesmon
        { { PEN20_JESMON_X_NAME, PEN20_JESMON_X_ID, PEN20_JESMON_X_FQID, PEN20_JESMON_X_FQNAME, PEN20_JESMON_X_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_JESMON_X_FQID, ALT_PEN20_JESMON_X_FQNAME } },  // Jesmon X
        { { PEN20_JYAGAMON_NAME, PEN20_JYAGAMON_ID, PEN20_JYAGAMON_FQID, PEN20_JYAGAMON_FQNAME, PEN20_JYAGAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_JYAGAMON_FQID, ALT_PEN20_JYAGAMON_FQNAME } },  // Jyagamon
        { { PEN20_JYUREIMON_NAME, PEN20_JYUREIMON_ID, PEN20_JYUREIMON_FQID, PEN20_JYUREIMON_FQNAME, PEN20_JYUREIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_JYUREIMON_FQID, ALT_PEN20_JYUREIMON_FQNAME } },  // Jyureimon
        { { PEN20_KABUTERIMON_NAME, PEN20_KABUTERIMON_ID, PEN20_KABUTERIMON_FQID, PEN20_KABUTERIMON_FQNAME, PEN20_KABUTERIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_KABUTERIMON_FQID, ALT_PEN20_KABUTERIMON_FQNAME } },  // Kabuterimon
        { { PEN20_KAKKINMON_NAME, PEN20_KAKKINMON_ID, PEN20_KAKKINMON_FQID, PEN20_KAKKINMON_FQNAME, PEN20_KAKKINMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_KAKKINMON_FQID, ALT_PEN20_KAKKINMON_FQNAME } },  // Kakkinmon
        { { PEN20_KIWIMON_NAME, PEN20_KIWIMON_ID, PEN20_KIWIMON_FQID, PEN20_KIWIMON_FQNAME, PEN20_KIWIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_KIWIMON_FQID, ALT_PEN20_KIWIMON_FQNAME } },  // Kiwimon
        { { PEN20_KNIGHTMON_NAME, PEN20_KNIGHTMON_ID, PEN20_KNIGHTMON_FQID, PEN20_KNIGHTMON_FQNAME, PEN20_KNIGHTMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_KNIGHTMON_FQID, ALT_PEN20_KNIGHTMON_FQNAME } },  // Knightmon
        { { PEN20_KOKUWAMON_NAME, PEN20_KOKUWAMON_ID, PEN20_KOKUWAMON_FQID, PEN20_KOKUWAMON_FQNAME, PEN20_KOKUWAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_KOKUWAMON_FQID, ALT_PEN20_KOKUWAMON_FQNAME } },  // Kokuwamon
        { { PEN20_KOROMON_NAME, PEN20_KOROMON_ID, PEN20_KOROMON_FQID, PEN20_KOROMON_FQNAME, PEN20_KOROMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_KOROMON_FQID, ALT_PEN20_KOROMON_FQNAME } },  // Koromon
        { { PEN20_KUWAGAMON_NAME, PEN20_KUWAGAMON_ID, PEN20_KUWAGAMON_FQID, PEN20_KUWAGAMON_FQNAME, PEN20_KUWAGAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_KUWAGAMON_FQID, ALT_PEN20_KUWAGAMON_FQNAME } },  // Kuwagamon
        { { PEN20_KYOKYOMON_NAME, PEN20_KYOKYOMON_ID, PEN20_KYOKYOMON_FQID, PEN20_KYOKYOMON_FQNAME, PEN20_KYOKYOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_KYOKYOMON_FQID, ALT_PEN20_KYOKYOMON_FQNAME } },  // Kyokyomon
        { { PEN20_LADY_DEVIMON_NAME, PEN20_LADY_DEVIMON_ID, PEN20_LADY_DEVIMON_FQID, PEN20_LADY_DEVIMON_FQNAME, PEN20_LADY_DEVIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_LADY_DEVIMON_FQID, ALT_PEN20_LADY_DEVIMON_FQNAME } },  // Lady Devimon
        { { PEN20_LALAMON_NAME, PEN20_LALAMON_ID, PEN20_LALAMON_FQID, PEN20_LALAMON_FQNAME, PEN20_LALAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_LALAMON_FQID, ALT_PEN20_LALAMON_FQNAME } },  // Lalamon
        { { PEN20_LAVOGARITAMON_NAME, PEN20_LAVOGARITAMON_ID, PEN20_LAVOGARITAMON_FQID, PEN20_LAVOGARITAMON_FQNAME, PEN20_LAVOGARITAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_LAVOGARITAMON_FQID, ALT_PEN20_LAVOGARITAMON_FQNAME } },  // Lavogaritamon
        { { PEN20_LAVORVOMON_NAME, PEN20_LAVORVOMON_ID, PEN20_LAVORVOMON_FQID, PEN20_LAVORVOMON_FQNAME, PEN20_LAVORVOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_LAVORVOMON_FQID, ALT_PEN20_LAVORVOMON_FQNAME } },  // Lavorvomon
        { { PEN20_LEOMON_NAME, PEN20_LEOMON_ID, PEN20_LEOMON_FQID, PEN20_LEOMON_FQNAME, PEN20_LEOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_LEOMON_FQID, ALT_PEN20_LEOMON_FQNAME } },  // Leomon
        { { PEN20_LILAMON_NAME, PEN20_LILAMON_ID, PEN20_LILAMON_FQID, PEN20_LILAMON_FQNAME, PEN20_LILAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_LILAMON_FQID, ALT_PEN20_LILAMON_FQNAME } },  // Lilamon
        { { PEN20_LILIMON_NAME, PEN20_LILIMON_ID, PEN20_LILIMON_FQID, PEN20_LILIMON_FQNAME, PEN20_LILIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_LILIMON_FQID, ALT_PEN20_LILIMON_FQNAME } },  // Lilimon
        { { PEN20_LOPMON_NAME, PEN20_LOPMON_ID, PEN20_LOPMON_FQID, PEN20_LOPMON_FQNAME, PEN20_LOPMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_LOPMON_FQID, ALT_PEN20_LOPMON_FQNAME } },  // Lopmon
        { { PEN20_LOTUSMON_NAME, PEN20_LOTUSMON_ID, PEN20_LOTUSMON_FQID, PEN20_LOTUSMON_FQNAME, PEN20_LOTUSMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_LOTUSMON_FQID, ALT_PEN20_LOTUSMON_FQNAME } },  // Lotusmon
        { { PEN20_LUDOMON_NAME, PEN20_LUDOMON_ID, PEN20_LUDOMON_FQID, PEN20_LUDOMON_FQNAME, PEN20_LUDOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_LUDOMON_FQID, ALT_PEN20_LUDOMON_FQNAME } },  // Ludomon
        { { PEN20_MAD_LEOMON_NAME, PEN20_MAD_LEOMON_ID, PEN20_MAD_LEOMON_FQID, PEN20_MAD_LEOMON_FQNAME, PEN20_MAD_LEOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_MAD_LEOMON_FQID, ALT_PEN20_MAD_LEOMON_FQNAME } },  // Mad Leomon
        { { PEN20_MAMMON_NAME, PEN20_MAMMON_ID, PEN20_MAMMON_FQID, PEN20_MAMMON_FQNAME, PEN20_MAMMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_MAMMON_FQID, ALT_PEN20_MAMMON_FQNAME } },  // Mammon
        { { PEN20_MANBOMON_NAME, PEN20_MANBOMON_ID, PEN20_MANBOMON_FQID, PEN20_MANBOMON_FQNAME, PEN20_MANBOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_MANBOMON_FQID, ALT_PEN20_MANBOMON_FQNAME } },  // Manbomon
        { { PEN20_MARIN_ANGEMON_NAME, PEN20_MARIN_ANGEMON_ID, PEN20_MARIN_ANGEMON_FQID, PEN20_MARIN_ANGEMON_FQNAME, PEN20_MARIN_ANGEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_MARIN_ANGEMON_FQID, ALT_PEN20_MARIN_ANGEMON_FQNAME } },  // Marin Angemon
        { { PEN20_MARIN_DEVIMON_NAME, PEN20_MARIN_DEVIMON_ID, PEN20_MARIN_DEVIMON_FQID, PEN20_MARIN_DEVIMON_FQNAME, PEN20_MARIN_DEVIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_MARIN_DEVIMON_FQID, ALT_PEN20_MARIN_DEVIMON_FQNAME } },  // Marin Devimon
        { { PEN20_MASTEMON_NAME, PEN20_MASTEMON_ID, PEN20_MASTEMON_FQID, PEN20_MASTEMON_FQNAME, PEN20_MASTEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_MASTEMON_FQID, ALT_PEN20_MASTEMON_FQNAME } },  // Mastemon
        { { PEN20_MECHANORIMON_NAME, PEN20_MECHANORIMON_ID, PEN20_MECHANORIMON_FQID, PEN20_MECHANORIMON_FQNAME, PEN20_MECHANORIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_MECHANORIMON_FQID, ALT_PEN20_MECHANORIMON_FQNAME } },  // Mechanorimon
        { { PEN20_MEGADRAMON_NAME, PEN20_MEGADRAMON_ID, PEN20_MEGADRAMON_FQID, PEN20_MEGADRAMON_FQNAME, PEN20_MEGADRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_MEGADRAMON_FQID, ALT_PEN20_MEGADRAMON_FQNAME } },  // Megadramon
        { { PEN20_MEGALO_GROWMON_NAME, PEN20_MEGALO_GROWMON_ID, PEN20_MEGALO_GROWMON_FQID, PEN20_MEGALO_GROWMON_FQNAME, PEN20_MEGALO_GROWMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_MEGALO_GROWMON_FQID, ALT_PEN20_MEGALO_GROWMON_FQNAME } },  // Megalo Growmon
        { { PEN20_MEGA_SEADRAMON_NAME, PEN20_MEGA_SEADRAMON_ID, PEN20_MEGA_SEADRAMON_FQID, PEN20_MEGA_SEADRAMON_FQNAME, PEN20_MEGA_SEADRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_MEGA_SEADRAMON_FQID, ALT_PEN20_MEGA_SEADRAMON_FQNAME } },  // Mega Seadramon
        { { PEN20_MEICOOMON_NAME, PEN20_MEICOOMON_ID, PEN20_MEICOOMON_FQID, PEN20_MEICOOMON_FQNAME, PEN20_MEICOOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_MEICOOMON_FQID, ALT_PEN20_MEICOOMON_FQNAME } },  // Meicoomon
        { { PEN20_MEICRACKMON_VICIOUS_MODE_NAME, PEN20_MEICRACKMON_VICIOUS_MODE_ID, PEN20_MEICRACKMON_VICIOUS_MODE_FQID, PEN20_MEICRACKMON_VICIOUS_MODE_FQNAME, PEN20_MEICRACKMON_VICIOUS_MODE_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_MEICRACKMON_VICIOUS_MODE_FQID, ALT_PEN20_MEICRACKMON_VICIOUS_MODE_FQNAME } },  // Meicrackmon Vicious Mode
        { { PEN20_MERAMON_NAME, PEN20_MERAMON_ID, PEN20_MERAMON_FQID, PEN20_MERAMON_FQNAME, PEN20_MERAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_MERAMON_FQID, ALT_PEN20_MERAMON_FQNAME } },  // Meramon
        { { PEN20_METAL_ETEMON_NAME, PEN20_METAL_ETEMON_ID, PEN20_METAL_ETEMON_FQID, PEN20_METAL_ETEMON_FQNAME, PEN20_METAL_ETEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_METAL_ETEMON_FQID, ALT_PEN20_METAL_ETEMON_FQNAME } },  // Metal Etemon
        { { PEN20_METAL_GARURUMON_NAME, PEN20_METAL_GARURUMON_ID, PEN20_METAL_GARURUMON_FQID, PEN20_METAL_GARURUMON_FQNAME, PEN20_METAL_GARURUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_METAL_GARURUMON_FQID, ALT_PEN20_METAL_GARURUMON_FQNAME } },  // Metal Garurumon
        { { PEN20_METAL_GREYMON_NAME, PEN20_METAL_GREYMON_ID, PEN20_METAL_GREYMON_FQID, PEN20_METAL_GREYMON_FQNAME, PEN20_METAL_GREYMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_METAL_GREYMON_FQID, ALT_PEN20_METAL_GREYMON_FQNAME } },  // Metal Greymon
        { { PEN20_METAL_MAMEMON_NAME, PEN20_METAL_MAMEMON_ID, PEN20_METAL_MAMEMON_FQID, PEN20_METAL_MAMEMON_FQNAME, PEN20_METAL_MAMEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_METAL_MAMEMON_FQID, ALT_PEN20_METAL_MAMEMON_FQNAME } },  // Metal Mamemon
        { { PEN20_METAL_SEADRAMON_NAME, PEN20_METAL_SEADRAMON_ID, PEN20_METAL_SEADRAMON_FQID, PEN20_METAL_SEADRAMON_FQNAME, PEN20_METAL_SEADRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_METAL_SEADRAMON_FQID, ALT_PEN20_METAL_SEADRAMON_FQNAME } },  // Metal Seadramon
        { { PEN20_MOCHIMON_NAME, PEN20_MOCHIMON_ID, PEN20_MOCHIMON_FQID, PEN20_MOCHIMON_FQNAME, PEN20_MOCHIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_MOCHIMON_FQID, ALT_PEN20_MOCHIMON_FQNAME } },  // Mochimon
        { { PEN20_MOKUMON_NAME, PEN20_MOKUMON_ID, PEN20_MOKUMON_FQID, PEN20_MOKUMON_FQNAME, PEN20_MOKUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_MOKUMON_FQID, ALT_PEN20_MOKUMON_FQNAME } },  // Mokumon
        { { PEN20_MONOCHROMON_NAME, PEN20_MONOCHROMON_ID, PEN20_MONOCHROMON_FQID, PEN20_MONOCHROMON_FQNAME, PEN20_MONOCHROMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_MONOCHROMON_FQID, ALT_PEN20_MONOCHROMON_FQNAME } },  // Monochromon
        { { PEN20_MUGENDRAMON_NAME, PEN20_MUGENDRAMON_ID, PEN20_MUGENDRAMON_FQID, PEN20_MUGENDRAMON_FQNAME, PEN20_MUGENDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_MUGENDRAMON_FQID, ALT_PEN20_MUGENDRAMON_FQNAME } },  // Mugendramon
        { { PEN20_MUSHMON_NAME, PEN20_MUSHMON_ID, PEN20_MUSHMON_FQID, PEN20_MUSHMON_FQNAME, PEN20_MUSHMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_MUSHMON_FQID, ALT_PEN20_MUSHMON_FQNAME } },  // Mushmon
        { { PEN20_NYAROMON_NAME, PEN20_NYAROMON_ID, PEN20_NYAROMON_FQID, PEN20_NYAROMON_FQNAME, PEN20_NYAROMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_NYAROMON_FQID, ALT_PEN20_NYAROMON_FQNAME } },  // Nyaromon
        { { PEN20_NYOKIMON_NAME, PEN20_NYOKIMON_ID, PEN20_NYOKIMON_FQID, PEN20_NYOKIMON_FQNAME, PEN20_NYOKIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_NYOKIMON_FQID, ALT_PEN20_NYOKIMON_FQNAME } },  // Nyokimon
        { { PEN20_OCTMON_NAME, PEN20_OCTMON_ID, PEN20_OCTMON_FQID, PEN20_OCTMON_FQNAME, PEN20_OCTMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_OCTMON_FQID, ALT_PEN20_OCTMON_FQNAME } },  // Octmon
        { { PEN20_OFANIMON_NAME, PEN20_OFANIMON_ID, PEN20_OFANIMON_FQID, PEN20_OFANIMON_FQNAME, PEN20_OFANIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_OFANIMON_FQID, ALT_PEN20_OFANIMON_FQNAME } },  // Ofanimon
        { { PEN20_OGUDOMON_NAME, PEN20_OGUDOMON_ID, PEN20_OGUDOMON_FQID, PEN20_OGUDOMON_FQNAME, PEN20_OGUDOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_OGUDOMON_FQID, ALT_PEN20_OGUDOMON_FQNAME } },  // Ogudomon
        { { PEN20_OKUWAMON_NAME, PEN20_OKUWAMON_ID, PEN20_OKUWAMON_FQID, PEN20_OKUWAMON_FQNAME, PEN20_OKUWAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_OKUWAMON_FQID, ALT_PEN20_OKUWAMON_FQNAME } },  // Okuwamon
        { { PEN20_OMEGAMON_NAME, PEN20_OMEGAMON_ID, PEN20_OMEGAMON_FQID, PEN20_OMEGAMON_FQNAME, PEN20_OMEGAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_OMEGAMON_FQID, ALT_PEN20_OMEGAMON_FQNAME } },  // Omegamon
        { { PEN20_ORDINEMON_NAME, PEN20_ORDINEMON_ID, PEN20_ORDINEMON_FQID, PEN20_ORDINEMON_FQNAME, PEN20_ORDINEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_ORDINEMON_FQID, ALT_PEN20_ORDINEMON_FQNAME } },  // Ordinemon
        { { PEN20_OTAMAMON_NAME, PEN20_OTAMAMON_ID, PEN20_OTAMAMON_FQID, PEN20_OTAMAMON_FQNAME, PEN20_OTAMAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_OTAMAMON_FQID, ALT_PEN20_OTAMAMON_FQNAME } },  // Otamamon
        { { PEN20_OURYUMON_NAME, PEN20_OURYUMON_ID, PEN20_OURYUMON_FQID, PEN20_OURYUMON_FQNAME, PEN20_OURYUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_OURYUMON_FQID, ALT_PEN20_OURYUMON_FQNAME } },  // Ouryumon
        { { PEN20_PAILDRAMON_NAME, PEN20_PAILDRAMON_ID, PEN20_PAILDRAMON_FQID, PEN20_PAILDRAMON_FQNAME, PEN20_PAILDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_PAILDRAMON_FQID, ALT_PEN20_PAILDRAMON_FQNAME } },  // Paildramon
        { { PEN20_PALMON_NAME, PEN20_PALMON_ID, PEN20_PALMON_FQID, PEN20_PALMON_FQNAME, PEN20_PALMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_PALMON_FQID, ALT_PEN20_PALMON_FQNAME } },  // Palmon
        { { PEN20_PETI_MERAMON_NAME, PEN20_PETI_MERAMON_ID, PEN20_PETI_MERAMON_FQID, PEN20_PETI_MERAMON_FQNAME, PEN20_PETI_MERAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_PETI_MERAMON_FQID, ALT_PEN20_PETI_MERAMON_FQNAME } },  // Peti Meramon
        { { PEN20_PETITMON_NAME, PEN20_PETITMON_ID, PEN20_PETITMON_FQID, PEN20_PETITMON_FQNAME, PEN20_PETITMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_PETITMON_FQID, ALT_PEN20_PETITMON_FQNAME } },  // Petitmon
        { { PEN20_PHASCOMON_NAME, PEN20_PHASCOMON_ID, PEN20_PHASCOMON_FQID, PEN20_PHASCOMON_FQNAME, PEN20_PHASCOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_PHASCOMON_FQID, ALT_PEN20_PHASCOMON_FQNAME } },  // Phascomon
        { { PEN20_PICCOLOMON_NAME, PEN20_PICCOLOMON_ID, PEN20_PICCOLOMON_FQID, PEN20_PICCOLOMON_FQNAME, PEN20_PICCOLOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_PICCOLOMON_FQID, ALT_PEN20_PICCOLOMON_FQNAME } },  // Piccolomon
        { { PEN20_PICO_DEVIMON_NAME, PEN20_PICO_DEVIMON_ID, PEN20_PICO_DEVIMON_FQID, PEN20_PICO_DEVIMON_FQNAME, PEN20_PICO_DEVIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_PICO_DEVIMON_FQID, ALT_PEN20_PICO_DEVIMON_FQNAME } },  // Pico Devimon
        { { PEN20_PIEMON_NAME, PEN20_PIEMON_ID, PEN20_PIEMON_FQID, PEN20_PIEMON_FQNAME, PEN20_PIEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_PIEMON_FQID, ALT_PEN20_PIEMON_FQNAME } },  // Piemon
        { { PEN20_PINOCHIMON_NAME, PEN20_PINOCHIMON_ID, PEN20_PINOCHIMON_FQID, PEN20_PINOCHIMON_FQNAME, PEN20_PINOCHIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_PINOCHIMON_FQID, ALT_PEN20_PINOCHIMON_FQNAME } },  // Pinochimon
        { { PEN20_PITCHMON_NAME, PEN20_PITCHMON_ID, PEN20_PITCHMON_FQID, PEN20_PITCHMON_FQNAME, PEN20_PITCHMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_PITCHMON_FQID, ALT_PEN20_PITCHMON_FQNAME } },  // Pitchmon
        { { PEN20_PIYOMON_NAME, PEN20_PIYOMON_ID, PEN20_PIYOMON_FQID, PEN20_PIYOMON_FQNAME, PEN20_PIYOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_PIYOMON_FQID, ALT_PEN20_PIYOMON_FQNAME } },  // Piyomon
        { { PEN20_PLESIOMON_NAME, PEN20_PLESIOMON_ID, PEN20_PLESIOMON_FQID, PEN20_PLESIOMON_FQNAME, PEN20_PLESIOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_PLESIOMON_FQID, ALT_PEN20_PLESIOMON_FQNAME } },  // Plesiomon
        { { PEN20_PLOTMON_NAME, PEN20_PLOTMON_ID, PEN20_PLOTMON_FQID, PEN20_PLOTMON_FQNAME, PEN20_PLOTMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_PLOTMON_FQID, ALT_PEN20_PLOTMON_FQNAME } },  // Plotmon
        { { PEN20_PORCUPAMON_NAME, PEN20_PORCUPAMON_ID, PEN20_PORCUPAMON_FQID, PEN20_PORCUPAMON_FQNAME, PEN20_PORCUPAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_PORCUPAMON_FQID, ALT_PEN20_PORCUPAMON_FQNAME } },  // Porcupamon
        { { PEN20_PUKAMON_NAME, PEN20_PUKAMON_ID, PEN20_PUKAMON_FQID, PEN20_PUKAMON_FQNAME, PEN20_PUKAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_PUKAMON_FQID, ALT_PEN20_PUKAMON_FQNAME } },  // Pukamon
        { { PEN20_PUKUMON_NAME, PEN20_PUKUMON_ID, PEN20_PUKUMON_FQID, PEN20_PUKUMON_FQNAME, PEN20_PUKUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_PUKUMON_FQID, ALT_PEN20_PUKUMON_FQNAME } },  // Pukumon
        { { PEN20_PUMPMON_NAME, PEN20_PUMPMON_ID, PEN20_PUMPMON_FQID, PEN20_PUMPMON_FQNAME, PEN20_PUMPMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_PUMPMON_FQID, ALT_PEN20_PUMPMON_FQNAME } },  // Pumpmon
        { { PEN20_PYOCOMON_NAME, PEN20_PYOCOMON_ID, PEN20_PYOCOMON_FQID, PEN20_PYOCOMON_FQNAME, PEN20_PYOCOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_PYOCOMON_FQID, ALT_PEN20_PYOCOMON_FQNAME } },  // Pyocomon
        { { PEN20_RAFFLESIMON_NAME, PEN20_RAFFLESIMON_ID, PEN20_RAFFLESIMON_FQID, PEN20_RAFFLESIMON_FQNAME, PEN20_RAFFLESIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_RAFFLESIMON_FQID, ALT_PEN20_RAFFLESIMON_FQNAME } },  // Rafflesimon
        { { PEN20_RAGNA_LORDMON_NAME, PEN20_RAGNA_LORDMON_ID, PEN20_RAGNA_LORDMON_FQID, PEN20_RAGNA_LORDMON_FQNAME, PEN20_RAGNA_LORDMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_RAGNA_LORDMON_FQID, ALT_PEN20_RAGNA_LORDMON_FQNAME } },  // Ragna Lordmon
        { { PEN20_RAGUELMON_NAME, PEN20_RAGUELMON_ID, PEN20_RAGUELMON_FQID, PEN20_RAGUELMON_FQNAME, PEN20_RAGUELMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_RAGUELMON_FQID, ALT_PEN20_RAGUELMON_FQNAME } },  // Raguelmon
        { { PEN20_RAIJI_LUDOMON_NAME, PEN20_RAIJI_LUDOMON_ID, PEN20_RAIJI_LUDOMON_FQID, PEN20_RAIJI_LUDOMON_FQNAME, PEN20_RAIJI_LUDOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_RAIJI_LUDOMON_FQID, ALT_PEN20_RAIJI_LUDOMON_FQNAME } },  // Raiji Ludomon
        { { PEN20_RAPIDMON_NAME, PEN20_RAPIDMON_ID, PEN20_RAPIDMON_FQID, PEN20_RAPIDMON_FQNAME, PEN20_RAPIDMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_RAPIDMON_FQID, ALT_PEN20_RAPIDMON_FQNAME } },  // Rapidmon
        { { PEN20_RED_VEGIMON_NAME, PEN20_RED_VEGIMON_ID, PEN20_RED_VEGIMON_FQID, PEN20_RED_VEGIMON_FQNAME, PEN20_RED_VEGIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_RED_VEGIMON_FQID, ALT_PEN20_RED_VEGIMON_FQNAME } },  // Red Vegimon
        { { PEN20_REPPAMON_NAME, PEN20_REPPAMON_ID, PEN20_REPPAMON_FQID, PEN20_REPPAMON_FQNAME, PEN20_REPPAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_REPPAMON_FQID, ALT_PEN20_REPPAMON_FQNAME } },  // Reppamon
        { { PEN20_REVOLMON_NAME, PEN20_REVOLMON_ID, PEN20_REVOLMON_FQID, PEN20_REVOLMON_FQNAME, PEN20_REVOLMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_REVOLMON_FQID, ALT_PEN20_REVOLMON_FQNAME } },  // Revolmon
        { { PEN20_RIZE_GREYMON_NAME, PEN20_RIZE_GREYMON_ID, PEN20_RIZE_GREYMON_FQID, PEN20_RIZE_GREYMON_FQNAME, PEN20_RIZE_GREYMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_RIZE_GREYMON_FQID, ALT_PEN20_RIZE_GREYMON_FQNAME } },  // Rize Greymon
        { { PEN20_ROSEMON_NAME, PEN20_ROSEMON_ID, PEN20_ROSEMON_FQID, PEN20_ROSEMON_FQNAME, PEN20_ROSEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_ROSEMON_FQID, ALT_PEN20_ROSEMON_FQNAME } },  // Rosemon
        { { PEN20_RUKAMON_NAME, PEN20_RUKAMON_ID, PEN20_RUKAMON_FQID, PEN20_RUKAMON_FQNAME, PEN20_RUKAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_RUKAMON_FQID, ALT_PEN20_RUKAMON_FQNAME } },  // Rukamon
        { { PEN20_RYUDAMON_NAME, PEN20_RYUDAMON_ID, PEN20_RYUDAMON_FQID, PEN20_RYUDAMON_FQNAME, PEN20_RYUDAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_RYUDAMON_FQID, ALT_PEN20_RYUDAMON_FQNAME } },  // Ryudamon
        { { PEN20_SABER_LEOMON_NAME, PEN20_SABER_LEOMON_ID, PEN20_SABER_LEOMON_FQID, PEN20_SABER_LEOMON_FQNAME, PEN20_SABER_LEOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_SABER_LEOMON_FQID, ALT_PEN20_SABER_LEOMON_FQNAME } },  // Saber Leomon
        { { PEN20_SAINT_GALGOMON_NAME, PEN20_SAINT_GALGOMON_ID, PEN20_SAINT_GALGOMON_FQID, PEN20_SAINT_GALGOMON_FQNAME, PEN20_SAINT_GALGOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_SAINT_GALGOMON_FQID, ALT_PEN20_SAINT_GALGOMON_FQNAME } },  // Saint Galgomon
        { { PEN20_SAKUMON_NAME, PEN20_SAKUMON_ID, PEN20_SAKUMON_FQID, PEN20_SAKUMON_FQNAME, PEN20_SAKUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_SAKUMON_FQID, ALT_PEN20_SAKUMON_FQNAME } },  // Sakumon
        { { PEN20_SAKUTTOMON_NAME, PEN20_SAKUTTOMON_ID, PEN20_SAKUTTOMON_FQID, PEN20_SAKUTTOMON_FQNAME, PEN20_SAKUTTOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_SAKUTTOMON_FQID, ALT_PEN20_SAKUTTOMON_FQNAME } },  // Sakuttomon
        { { PEN20_SAVIOR_HACKMON_NAME, PEN20_SAVIOR_HACKMON_ID, PEN20_SAVIOR_HACKMON_FQID, PEN20_SAVIOR_HACKMON_FQNAME, PEN20_SAVIOR_HACKMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_SAVIOR_HACKMON_FQID, ALT_PEN20_SAVIOR_HACKMON_FQNAME } },  // Savior Hackmon
        { { PEN20_SEADRAMON_NAME, PEN20_SEADRAMON_ID, PEN20_SEADRAMON_FQID, PEN20_SEADRAMON_FQNAME, PEN20_SEADRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_SEADRAMON_FQID, ALT_PEN20_SEADRAMON_FQNAME } },  // Seadramon
        { { PEN20_SERAPHIMON_NAME, PEN20_SERAPHIMON_ID, PEN20_SERAPHIMON_FQID, PEN20_SERAPHIMON_FQNAME, PEN20_SERAPHIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_SERAPHIMON_FQID, ALT_PEN20_SERAPHIMON_FQNAME } },  // Seraphimon
        { { PEN20_SHADRAMON_NAME, PEN20_SHADRAMON_ID, PEN20_SHADRAMON_FQID, PEN20_SHADRAMON_FQNAME, PEN20_SHADRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_SHADRAMON_FQID, ALT_PEN20_SHADRAMON_FQNAME } },  // Shadramon
        { { PEN20_SHAKOMON_NAME, PEN20_SHAKOMON_ID, PEN20_SHAKOMON_FQID, PEN20_SHAKOMON_FQNAME, PEN20_SHAKOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_SHAKOMON_FQID, ALT_PEN20_SHAKOMON_FQNAME } },  // Shakomon
        { { PEN20_SKULL_MAMMON_NAME, PEN20_SKULL_MAMMON_ID, PEN20_SKULL_MAMMON_FQID, PEN20_SKULL_MAMMON_FQNAME, PEN20_SKULL_MAMMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_SKULL_MAMMON_FQID, ALT_PEN20_SKULL_MAMMON_FQNAME } },  // Skull Mammon
        { { PEN20_SLAYERDRAMON_NAME, PEN20_SLAYERDRAMON_ID, PEN20_SLAYERDRAMON_FQID, PEN20_SLAYERDRAMON_FQNAME, PEN20_SLAYERDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_SLAYERDRAMON_FQID, ALT_PEN20_SLAYERDRAMON_FQNAME } },  // Slayerdramon
        { { PEN20_STARMON_NAME, PEN20_STARMON_ID, PEN20_STARMON_FQID, PEN20_STARMON_FQNAME, PEN20_STARMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_STARMON_FQID, ALT_PEN20_STARMON_FQNAME } },  // Starmon
        { { PEN20_SUNFLOWMON_NAME, PEN20_SUNFLOWMON_ID, PEN20_SUNFLOWMON_FQID, PEN20_SUNFLOWMON_FQNAME, PEN20_SUNFLOWMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_SUNFLOWMON_FQID, ALT_PEN20_SUNFLOWMON_FQNAME } },  // Sunflowmon
        { { PEN20_TAILMON_NAME, PEN20_TAILMON_ID, PEN20_TAILMON_FQID, PEN20_TAILMON_FQNAME, PEN20_TAILMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_TAILMON_FQID, ALT_PEN20_TAILMON_FQNAME } },  // Tailmon
        { { PEN20_TANKMON_NAME, PEN20_TANKMON_ID, PEN20_TANKMON_FQID, PEN20_TANKMON_FQNAME, PEN20_TANKMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_TANKMON_FQID, ALT_PEN20_TANKMON_FQNAME } },  // Tankmon
        { { PEN20_TARGETMON_NAME, PEN20_TARGETMON_ID, PEN20_TARGETMON_FQID, PEN20_TARGETMON_FQNAME, PEN20_TARGETMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_TARGETMON_FQID, ALT_PEN20_TARGETMON_FQNAME } },  // Targetmon
        { { PEN20_TENTOMON_NAME, PEN20_TENTOMON_ID, PEN20_TENTOMON_FQID, PEN20_TENTOMON_FQNAME, PEN20_TENTOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_TENTOMON_FQID, ALT_PEN20_TENTOMON_FQNAME } },  // Tentomon
        { { PEN20_TERRIERMON_NAME, PEN20_TERRIERMON_ID, PEN20_TERRIERMON_FQID, PEN20_TERRIERMON_FQNAME, PEN20_TERRIERMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_TERRIERMON_FQID, ALT_PEN20_TERRIERMON_FQNAME } },  // Terriermon
        { { PEN20_THUNDERBALLMON_NAME, PEN20_THUNDERBALLMON_ID, PEN20_THUNDERBALLMON_FQID, PEN20_THUNDERBALLMON_FQNAME, PEN20_THUNDERBALLMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_THUNDERBALLMON_FQID, ALT_PEN20_THUNDERBALLMON_FQNAME } },  // Thunderballmon
        { { PEN20_TIA_LUDOMON_NAME, PEN20_TIA_LUDOMON_ID, PEN20_TIA_LUDOMON_FQID, PEN20_TIA_LUDOMON_FQNAME, PEN20_TIA_LUDOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_TIA_LUDOMON_FQID, ALT_PEN20_TIA_LUDOMON_FQNAME } },  // Tia Ludomon
        { { PEN20_TOGEMON_NAME, PEN20_TOGEMON_ID, PEN20_TOGEMON_FQID, PEN20_TOGEMON_FQNAME, PEN20_TOGEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_TOGEMON_FQID, ALT_PEN20_TOGEMON_FQNAME } },  // Togemon
        { { PEN20_TONOSAMA_GEKOMON_NAME, PEN20_TONOSAMA_GEKOMON_ID, PEN20_TONOSAMA_GEKOMON_FQID, PEN20_TONOSAMA_GEKOMON_FQNAME, PEN20_TONOSAMA_GEKOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_TONOSAMA_GEKOMON_FQID, ALT_PEN20_TONOSAMA_GEKOMON_FQNAME } },  // Tonosama Gekomon
        { { PEN20_TORTAMON_NAME, PEN20_TORTAMON_ID, PEN20_TORTAMON_FQID, PEN20_TORTAMON_FQNAME, PEN20_TORTAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_TORTAMON_FQID, ALT_PEN20_TORTAMON_FQNAME } },  // Tortamon
        { { PEN20_TOY_AGUMON_NAME, PEN20_TOY_AGUMON_ID, PEN20_TOY_AGUMON_FQID, PEN20_TOY_AGUMON_FQNAME, PEN20_TOY_AGUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_TOY_AGUMON_FQID, ALT_PEN20_TOY_AGUMON_FQNAME } },  // Toy Agumon
        { { PEN20_TRICERAMON_NAME, PEN20_TRICERAMON_ID, PEN20_TRICERAMON_FQID, PEN20_TRICERAMON_FQNAME, PEN20_TRICERAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_TRICERAMON_FQID, ALT_PEN20_TRICERAMON_FQNAME } },  // Triceramon
        { { PEN20_TROOPMON_NAME, PEN20_TROOPMON_ID, PEN20_TROOPMON_FQID, PEN20_TROOPMON_FQNAME, PEN20_TROOPMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_TROOPMON_FQID, ALT_PEN20_TROOPMON_FQNAME } },  // Troopmon
        { { PEN20_TURUIEMON_NAME, PEN20_TURUIEMON_ID, PEN20_TURUIEMON_FQID, PEN20_TURUIEMON_FQNAME, PEN20_TURUIEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_TURUIEMON_FQID, ALT_PEN20_TURUIEMON_FQNAME } },  // Turuiemon
        { { PEN20_VAMDEMON_NAME, PEN20_VAMDEMON_ID, PEN20_VAMDEMON_FQID, PEN20_VAMDEMON_FQNAME, PEN20_VAMDEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_VAMDEMON_FQID, ALT_PEN20_VAMDEMON_FQNAME } },  // Vamdemon
        { { PEN20_V_DRAMON_NAME, PEN20_V_DRAMON_ID, PEN20_V_DRAMON_FQID, PEN20_V_DRAMON_FQNAME, PEN20_V_DRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_V_DRAMON_FQID, ALT_PEN20_V_DRAMON_FQNAME } },  // V-dramon
        { { PEN20_VENOM_VAMDEMON_NAME, PEN20_VENOM_VAMDEMON_ID, PEN20_VENOM_VAMDEMON_FQID, PEN20_VENOM_VAMDEMON_FQNAME, PEN20_VENOM_VAMDEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_VENOM_VAMDEMON_FQID, ALT_PEN20_VENOM_VAMDEMON_FQNAME } },  // Venom Vamdemon
        { { PEN20_V_MON_NAME, PEN20_V_MON_ID, PEN20_V_MON_FQID, PEN20_V_MON_FQNAME, PEN20_V_MON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_V_MON_FQID, ALT_PEN20_V_MON_FQNAME } },  // V-mon
        { { PEN20_VOLCANICDRAMON_NAME, PEN20_VOLCANICDRAMON_ID, PEN20_VOLCANICDRAMON_FQID, PEN20_VOLCANICDRAMON_FQNAME, PEN20_VOLCANICDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_VOLCANICDRAMON_FQID, ALT_PEN20_VOLCANICDRAMON_FQNAME } },  // Volcanicdramon
        { { PEN20_VOLTOBAUTAMON_NAME, PEN20_VOLTOBAUTAMON_ID, PEN20_VOLTOBAUTAMON_FQID, PEN20_VOLTOBAUTAMON_FQNAME, PEN20_VOLTOBAUTAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_VOLTOBAUTAMON_FQID, ALT_PEN20_VOLTOBAUTAMON_FQNAME } },  // Voltobautamon
        { { PEN20_VORVOMON_NAME, PEN20_VORVOMON_ID, PEN20_VORVOMON_FQID, PEN20_VORVOMON_FQNAME, PEN20_VORVOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_VORVOMON_FQID, ALT_PEN20_VORVOMON_FQNAME } },  // Vorvomon
        { { PEN20_WAR_GREYMON_NAME, PEN20_WAR_GREYMON_ID, PEN20_WAR_GREYMON_FQID, PEN20_WAR_GREYMON_FQNAME, PEN20_WAR_GREYMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_WAR_GREYMON_FQID, ALT_PEN20_WAR_GREYMON_FQNAME } },  // War Greymon
        { { PEN20_WARU_MONZAEMON_NAME, PEN20_WARU_MONZAEMON_ID, PEN20_WARU_MONZAEMON_FQID, PEN20_WARU_MONZAEMON_FQNAME, PEN20_WARU_MONZAEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_WARU_MONZAEMON_FQID, ALT_PEN20_WARU_MONZAEMON_FQNAME } },  // Waru Monzaemon
        { { PEN20_WERE_GARURUMON_NAME, PEN20_WERE_GARURUMON_ID, PEN20_WERE_GARURUMON_FQID, PEN20_WERE_GARURUMON_FQNAME, PEN20_WERE_GARURUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_WERE_GARURUMON_FQID, ALT_PEN20_WERE_GARURUMON_FQNAME } },  // Were Garurumon
        { { PEN20_WHAMON_NAME, PEN20_WHAMON_ID, PEN20_WHAMON_FQID, PEN20_WHAMON_FQNAME, PEN20_WHAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_WHAMON_FQID, ALT_PEN20_WHAMON_FQNAME } },  // Whamon
        { { PEN20_WINGDRAMON_NAME, PEN20_WINGDRAMON_ID, PEN20_WINGDRAMON_FQID, PEN20_WINGDRAMON_FQNAME, PEN20_WINGDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_WINGDRAMON_FQID, ALT_PEN20_WINGDRAMON_FQNAME } },  // Wingdramon
        { { PEN20_WIZARMON_NAME, PEN20_WIZARMON_ID, PEN20_WIZARMON_FQID, PEN20_WIZARMON_FQNAME, PEN20_WIZARMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_WIZARMON_FQID, ALT_PEN20_WIZARMON_FQNAME } },  // Wizarmon
        { { PEN20_WOODMON_NAME, PEN20_WOODMON_ID, PEN20_WOODMON_FQID, PEN20_WOODMON_FQNAME, PEN20_WOODMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_WOODMON_FQID, ALT_PEN20_WOODMON_FQNAME } },  // Woodmon
        { { PEN20_XV_MON_NAME, PEN20_XV_MON_ID, PEN20_XV_MON_FQID, PEN20_XV_MON_FQNAME, PEN20_XV_MON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_XV_MON_FQID, ALT_PEN20_XV_MON_FQNAME } },  // XV-mon
        { { PEN20_YUKIMI_BOTAMON_NAME, PEN20_YUKIMI_BOTAMON_ID, PEN20_YUKIMI_BOTAMON_FQID, PEN20_YUKIMI_BOTAMON_FQNAME, PEN20_YUKIMI_BOTAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_YUKIMI_BOTAMON_FQID, ALT_PEN20_YUKIMI_BOTAMON_FQNAME } },  // Yukimi Botamon
        { { PEN20_ZERIMON_NAME, PEN20_ZERIMON_ID, PEN20_ZERIMON_FQID, PEN20_ZERIMON_FQNAME, PEN20_ZERIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_ZERIMON_FQID, ALT_PEN20_ZERIMON_FQNAME } },  // Zerimon
        { { PEN20_ZUBAEAGERMON_NAME, PEN20_ZUBAEAGERMON_ID, PEN20_ZUBAEAGERMON_FQID, PEN20_ZUBAEAGERMON_FQNAME, PEN20_ZUBAEAGERMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_ZUBAEAGERMON_FQID, ALT_PEN20_ZUBAEAGERMON_FQNAME } },  // Zubaeagermon
        { { PEN20_ZUBAMON_NAME, PEN20_ZUBAMON_ID, PEN20_ZUBAMON_FQID, PEN20_ZUBAMON_FQNAME, PEN20_ZUBAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_ZUBAMON_FQID, ALT_PEN20_ZUBAMON_FQNAME } },  // Zubamon
        { { PEN20_ZUDOMON_NAME, PEN20_ZUDOMON_ID, PEN20_ZUDOMON_FQID, PEN20_ZUDOMON_FQNAME, PEN20_ZUDOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm }, { ALT_PEN20_ZUDOMON_FQID, ALT_PEN20_ZUDOMON_FQNAME } },  // Zudomon
        
    };
    static const config_animation_names_entry_t pen20_animation_names_table[] = {
        { PEN20_AERO_V_DRAMON_NAME, PEN20_AERO_V_DRAMON_NAME_LEN, PEN20_AERO_V_DRAMON_ID, PEN20_AERO_V_DRAMON_ID_LEN, PEN20_AERO_V_DRAMON_FQID, PEN20_AERO_V_DRAMON_FQID_LEN, PEN20_AERO_V_DRAMON_FQNAME, PEN20_AERO_V_DRAMON_FQNAME_LEN },
        { PEN20_AERO_V_DRAMON_NAME, PEN20_AERO_V_DRAMON_NAME_LEN, PEN20_AERO_V_DRAMON_ID, PEN20_AERO_V_DRAMON_ID_LEN, ALT_PEN20_AERO_V_DRAMON_FQID, ALT_PEN20_AERO_V_DRAMON_FQID_LEN, ALT_PEN20_AERO_V_DRAMON_FQNAME, ALT_PEN20_AERO_V_DRAMON_FQNAME_LEN },
        { PEN20_AGUMON_HAKASE_NAME, PEN20_AGUMON_HAKASE_NAME_LEN, PEN20_AGUMON_HAKASE_ID, PEN20_AGUMON_HAKASE_ID_LEN, PEN20_AGUMON_HAKASE_FQID, PEN20_AGUMON_HAKASE_FQID_LEN, PEN20_AGUMON_HAKASE_FQNAME, PEN20_AGUMON_HAKASE_FQNAME_LEN },
        { PEN20_AGUMON_HAKASE_NAME, PEN20_AGUMON_HAKASE_NAME_LEN, PEN20_AGUMON_HAKASE_ID, PEN20_AGUMON_HAKASE_ID_LEN, ALT_PEN20_AGUMON_HAKASE_FQID, ALT_PEN20_AGUMON_HAKASE_FQID_LEN, ALT_PEN20_AGUMON_HAKASE_FQNAME, ALT_PEN20_AGUMON_HAKASE_FQNAME_LEN },
        { PEN20_AGUMON_NAME, PEN20_AGUMON_NAME_LEN, PEN20_AGUMON_ID, PEN20_AGUMON_ID_LEN, PEN20_AGUMON_FQID, PEN20_AGUMON_FQID_LEN, PEN20_AGUMON_FQNAME, PEN20_AGUMON_FQNAME_LEN },
        { PEN20_AGUMON_NAME, PEN20_AGUMON_NAME_LEN, PEN20_AGUMON_ID, PEN20_AGUMON_ID_LEN, ALT_PEN20_AGUMON_FQID, ALT_PEN20_AGUMON_FQID_LEN, ALT_PEN20_AGUMON_FQNAME, ALT_PEN20_AGUMON_FQNAME_LEN },
        { PEN20_ALPHAMON_OURYUKEN_NAME, PEN20_ALPHAMON_OURYUKEN_NAME_LEN, PEN20_ALPHAMON_OURYUKEN_ID, PEN20_ALPHAMON_OURYUKEN_ID_LEN, PEN20_ALPHAMON_OURYUKEN_FQID, PEN20_ALPHAMON_OURYUKEN_FQID_LEN, PEN20_ALPHAMON_OURYUKEN_FQNAME, PEN20_ALPHAMON_OURYUKEN_FQNAME_LEN },
        { PEN20_ALPHAMON_OURYUKEN_NAME, PEN20_ALPHAMON_OURYUKEN_NAME_LEN, PEN20_ALPHAMON_OURYUKEN_ID, PEN20_ALPHAMON_OURYUKEN_ID_LEN, ALT_PEN20_ALPHAMON_OURYUKEN_FQID, ALT_PEN20_ALPHAMON_OURYUKEN_FQID_LEN, ALT_PEN20_ALPHAMON_OURYUKEN_FQNAME, ALT_PEN20_ALPHAMON_OURYUKEN_FQNAME_LEN },
        { PEN20_ALPHAMON_NAME, PEN20_ALPHAMON_NAME_LEN, PEN20_ALPHAMON_ID, PEN20_ALPHAMON_ID_LEN, PEN20_ALPHAMON_FQID, PEN20_ALPHAMON_FQID_LEN, PEN20_ALPHAMON_FQNAME, PEN20_ALPHAMON_FQNAME_LEN },
        { PEN20_ALPHAMON_NAME, PEN20_ALPHAMON_NAME_LEN, PEN20_ALPHAMON_ID, PEN20_ALPHAMON_ID_LEN, ALT_PEN20_ALPHAMON_FQID, ALT_PEN20_ALPHAMON_FQID_LEN, ALT_PEN20_ALPHAMON_FQNAME, ALT_PEN20_ALPHAMON_FQNAME_LEN },
        { PEN20_ANDIRAMON_NAME, PEN20_ANDIRAMON_NAME_LEN, PEN20_ANDIRAMON_ID, PEN20_ANDIRAMON_ID_LEN, PEN20_ANDIRAMON_FQID, PEN20_ANDIRAMON_FQID_LEN, PEN20_ANDIRAMON_FQNAME, PEN20_ANDIRAMON_FQNAME_LEN },
        { PEN20_ANDIRAMON_NAME, PEN20_ANDIRAMON_NAME_LEN, PEN20_ANDIRAMON_ID, PEN20_ANDIRAMON_ID_LEN, ALT_PEN20_ANDIRAMON_FQID, ALT_PEN20_ANDIRAMON_FQID_LEN, ALT_PEN20_ANDIRAMON_FQNAME, ALT_PEN20_ANDIRAMON_FQNAME_LEN },
        { PEN20_ANDROMON_NAME, PEN20_ANDROMON_NAME_LEN, PEN20_ANDROMON_ID, PEN20_ANDROMON_ID_LEN, PEN20_ANDROMON_FQID, PEN20_ANDROMON_FQID_LEN, PEN20_ANDROMON_FQNAME, PEN20_ANDROMON_FQNAME_LEN },
        { PEN20_ANDROMON_NAME, PEN20_ANDROMON_NAME_LEN, PEN20_ANDROMON_ID, PEN20_ANDROMON_ID_LEN, ALT_PEN20_ANDROMON_FQID, ALT_PEN20_ANDROMON_FQID_LEN, ALT_PEN20_ANDROMON_FQNAME, ALT_PEN20_ANDROMON_FQNAME_LEN },
        { PEN20_ANGEMON_NAME, PEN20_ANGEMON_NAME_LEN, PEN20_ANGEMON_ID, PEN20_ANGEMON_ID_LEN, PEN20_ANGEMON_FQID, PEN20_ANGEMON_FQID_LEN, PEN20_ANGEMON_FQNAME, PEN20_ANGEMON_FQNAME_LEN },
        { PEN20_ANGEMON_NAME, PEN20_ANGEMON_NAME_LEN, PEN20_ANGEMON_ID, PEN20_ANGEMON_ID_LEN, ALT_PEN20_ANGEMON_FQID, ALT_PEN20_ANGEMON_FQID_LEN, ALT_PEN20_ANGEMON_FQNAME, ALT_PEN20_ANGEMON_FQNAME_LEN },
        { PEN20_ANGEWOMON_NAME, PEN20_ANGEWOMON_NAME_LEN, PEN20_ANGEWOMON_ID, PEN20_ANGEWOMON_ID_LEN, PEN20_ANGEWOMON_FQID, PEN20_ANGEWOMON_FQID_LEN, PEN20_ANGEWOMON_FQNAME, PEN20_ANGEWOMON_FQNAME_LEN },
        { PEN20_ANGEWOMON_NAME, PEN20_ANGEWOMON_NAME_LEN, PEN20_ANGEWOMON_ID, PEN20_ANGEWOMON_ID_LEN, ALT_PEN20_ANGEWOMON_FQID, ALT_PEN20_ANGEWOMON_FQID_LEN, ALT_PEN20_ANGEWOMON_FQNAME, ALT_PEN20_ANGEWOMON_FQNAME_LEN },
        { PEN20_ANOMALOCARIMON_NAME, PEN20_ANOMALOCARIMON_NAME_LEN, PEN20_ANOMALOCARIMON_ID, PEN20_ANOMALOCARIMON_ID_LEN, PEN20_ANOMALOCARIMON_FQID, PEN20_ANOMALOCARIMON_FQID_LEN, PEN20_ANOMALOCARIMON_FQNAME, PEN20_ANOMALOCARIMON_FQNAME_LEN },
        { PEN20_ANOMALOCARIMON_NAME, PEN20_ANOMALOCARIMON_NAME_LEN, PEN20_ANOMALOCARIMON_ID, PEN20_ANOMALOCARIMON_ID_LEN, ALT_PEN20_ANOMALOCARIMON_FQID, ALT_PEN20_ANOMALOCARIMON_FQID_LEN, ALT_PEN20_ANOMALOCARIMON_FQNAME, ALT_PEN20_ANOMALOCARIMON_FQNAME_LEN },
        { PEN20_ARRESTERDRAMON_NAME, PEN20_ARRESTERDRAMON_NAME_LEN, PEN20_ARRESTERDRAMON_ID, PEN20_ARRESTERDRAMON_ID_LEN, PEN20_ARRESTERDRAMON_FQID, PEN20_ARRESTERDRAMON_FQID_LEN, PEN20_ARRESTERDRAMON_FQNAME, PEN20_ARRESTERDRAMON_FQNAME_LEN },
        { PEN20_ARRESTERDRAMON_NAME, PEN20_ARRESTERDRAMON_NAME_LEN, PEN20_ARRESTERDRAMON_ID, PEN20_ARRESTERDRAMON_ID_LEN, ALT_PEN20_ARRESTERDRAMON_FQID, ALT_PEN20_ARRESTERDRAMON_FQID_LEN, ALT_PEN20_ARRESTERDRAMON_FQNAME, ALT_PEN20_ARRESTERDRAMON_FQNAME_LEN },
        { PEN20_ASTAMON_NAME, PEN20_ASTAMON_NAME_LEN, PEN20_ASTAMON_ID, PEN20_ASTAMON_ID_LEN, PEN20_ASTAMON_FQID, PEN20_ASTAMON_FQID_LEN, PEN20_ASTAMON_FQNAME, PEN20_ASTAMON_FQNAME_LEN },
        { PEN20_ASTAMON_NAME, PEN20_ASTAMON_NAME_LEN, PEN20_ASTAMON_ID, PEN20_ASTAMON_ID_LEN, ALT_PEN20_ASTAMON_FQID, ALT_PEN20_ASTAMON_FQID_LEN, ALT_PEN20_ASTAMON_FQNAME, ALT_PEN20_ASTAMON_FQNAME_LEN },
        { PEN20_ASURAMON_NAME, PEN20_ASURAMON_NAME_LEN, PEN20_ASURAMON_ID, PEN20_ASURAMON_ID_LEN, PEN20_ASURAMON_FQID, PEN20_ASURAMON_FQID_LEN, PEN20_ASURAMON_FQNAME, PEN20_ASURAMON_FQNAME_LEN },
        { PEN20_ASURAMON_NAME, PEN20_ASURAMON_NAME_LEN, PEN20_ASURAMON_ID, PEN20_ASURAMON_ID_LEN, ALT_PEN20_ASURAMON_FQID, ALT_PEN20_ASURAMON_FQID_LEN, ALT_PEN20_ASURAMON_FQNAME, ALT_PEN20_ASURAMON_FQNAME_LEN },
        { PEN20_ATLUR_KABUTERIMON_NAME, PEN20_ATLUR_KABUTERIMON_NAME_LEN, PEN20_ATLUR_KABUTERIMON_ID, PEN20_ATLUR_KABUTERIMON_ID_LEN, PEN20_ATLUR_KABUTERIMON_FQID, PEN20_ATLUR_KABUTERIMON_FQID_LEN, PEN20_ATLUR_KABUTERIMON_FQNAME, PEN20_ATLUR_KABUTERIMON_FQNAME_LEN },
        { PEN20_ATLUR_KABUTERIMON_NAME, PEN20_ATLUR_KABUTERIMON_NAME_LEN, PEN20_ATLUR_KABUTERIMON_ID, PEN20_ATLUR_KABUTERIMON_ID_LEN, ALT_PEN20_ATLUR_KABUTERIMON_FQID, ALT_PEN20_ATLUR_KABUTERIMON_FQID_LEN, ALT_PEN20_ATLUR_KABUTERIMON_FQNAME, ALT_PEN20_ATLUR_KABUTERIMON_FQNAME_LEN },
        { PEN20_BAALMON_NAME, PEN20_BAALMON_NAME_LEN, PEN20_BAALMON_ID, PEN20_BAALMON_ID_LEN, PEN20_BAALMON_FQID, PEN20_BAALMON_FQID_LEN, PEN20_BAALMON_FQNAME, PEN20_BAALMON_FQNAME_LEN },
        { PEN20_BAALMON_NAME, PEN20_BAALMON_NAME_LEN, PEN20_BAALMON_ID, PEN20_BAALMON_ID_LEN, ALT_PEN20_BAALMON_FQID, ALT_PEN20_BAALMON_FQID_LEN, ALT_PEN20_BAALMON_FQNAME, ALT_PEN20_BAALMON_FQNAME_LEN },
        { PEN20_BABYDMON_NAME, PEN20_BABYDMON_NAME_LEN, PEN20_BABYDMON_ID, PEN20_BABYDMON_ID_LEN, PEN20_BABYDMON_FQID, PEN20_BABYDMON_FQID_LEN, PEN20_BABYDMON_FQNAME, PEN20_BABYDMON_FQNAME_LEN },
        { PEN20_BABYDMON_NAME, PEN20_BABYDMON_NAME_LEN, PEN20_BABYDMON_ID, PEN20_BABYDMON_ID_LEN, ALT_PEN20_BABYDMON_FQID, ALT_PEN20_BABYDMON_FQID_LEN, ALT_PEN20_BABYDMON_FQNAME, ALT_PEN20_BABYDMON_FQNAME_LEN },
        { PEN20_BAKEMON_NAME, PEN20_BAKEMON_NAME_LEN, PEN20_BAKEMON_ID, PEN20_BAKEMON_ID_LEN, PEN20_BAKEMON_FQID, PEN20_BAKEMON_FQID_LEN, PEN20_BAKEMON_FQNAME, PEN20_BAKEMON_FQNAME_LEN },
        { PEN20_BAKEMON_NAME, PEN20_BAKEMON_NAME_LEN, PEN20_BAKEMON_ID, PEN20_BAKEMON_ID_LEN, ALT_PEN20_BAKEMON_FQID, ALT_PEN20_BAKEMON_FQID_LEN, ALT_PEN20_BAKEMON_FQNAME, ALT_PEN20_BAKEMON_FQNAME_LEN },
        { PEN20_BAKUMON_NAME, PEN20_BAKUMON_NAME_LEN, PEN20_BAKUMON_ID, PEN20_BAKUMON_ID_LEN, PEN20_BAKUMON_FQID, PEN20_BAKUMON_FQID_LEN, PEN20_BAKUMON_FQNAME, PEN20_BAKUMON_FQNAME_LEN },
        { PEN20_BAKUMON_NAME, PEN20_BAKUMON_NAME_LEN, PEN20_BAKUMON_ID, PEN20_BAKUMON_ID_LEN, ALT_PEN20_BAKUMON_FQID, ALT_PEN20_BAKUMON_FQID_LEN, ALT_PEN20_BAKUMON_FQNAME, ALT_PEN20_BAKUMON_FQNAME_LEN },
        { PEN20_BANCHO_LEOMON_NAME, PEN20_BANCHO_LEOMON_NAME_LEN, PEN20_BANCHO_LEOMON_ID, PEN20_BANCHO_LEOMON_ID_LEN, PEN20_BANCHO_LEOMON_FQID, PEN20_BANCHO_LEOMON_FQID_LEN, PEN20_BANCHO_LEOMON_FQNAME, PEN20_BANCHO_LEOMON_FQNAME_LEN },
        { PEN20_BANCHO_LEOMON_NAME, PEN20_BANCHO_LEOMON_NAME_LEN, PEN20_BANCHO_LEOMON_ID, PEN20_BANCHO_LEOMON_ID_LEN, ALT_PEN20_BANCHO_LEOMON_FQID, ALT_PEN20_BANCHO_LEOMON_FQID_LEN, ALT_PEN20_BANCHO_LEOMON_FQNAME, ALT_PEN20_BANCHO_LEOMON_FQNAME_LEN },
        { PEN20_BAO_HACKMON_NAME, PEN20_BAO_HACKMON_NAME_LEN, PEN20_BAO_HACKMON_ID, PEN20_BAO_HACKMON_ID_LEN, PEN20_BAO_HACKMON_FQID, PEN20_BAO_HACKMON_FQID_LEN, PEN20_BAO_HACKMON_FQNAME, PEN20_BAO_HACKMON_FQNAME_LEN },
        { PEN20_BAO_HACKMON_NAME, PEN20_BAO_HACKMON_NAME_LEN, PEN20_BAO_HACKMON_ID, PEN20_BAO_HACKMON_ID_LEN, ALT_PEN20_BAO_HACKMON_FQID, ALT_PEN20_BAO_HACKMON_FQID_LEN, ALT_PEN20_BAO_HACKMON_FQNAME, ALT_PEN20_BAO_HACKMON_FQNAME_LEN },
        { PEN20_BEELZEBUMON_BLAST_MODE_NAME, PEN20_BEELZEBUMON_BLAST_MODE_NAME_LEN, PEN20_BEELZEBUMON_BLAST_MODE_ID, PEN20_BEELZEBUMON_BLAST_MODE_ID_LEN, PEN20_BEELZEBUMON_BLAST_MODE_FQID, PEN20_BEELZEBUMON_BLAST_MODE_FQID_LEN, PEN20_BEELZEBUMON_BLAST_MODE_FQNAME, PEN20_BEELZEBUMON_BLAST_MODE_FQNAME_LEN },
        { PEN20_BEELZEBUMON_BLAST_MODE_NAME, PEN20_BEELZEBUMON_BLAST_MODE_NAME_LEN, PEN20_BEELZEBUMON_BLAST_MODE_ID, PEN20_BEELZEBUMON_BLAST_MODE_ID_LEN, ALT_PEN20_BEELZEBUMON_BLAST_MODE_FQID, ALT_PEN20_BEELZEBUMON_BLAST_MODE_FQID_LEN, ALT_PEN20_BEELZEBUMON_BLAST_MODE_FQNAME, ALT_PEN20_BEELZEBUMON_BLAST_MODE_FQNAME_LEN },
        { PEN20_BEOWOLFMON_NAME, PEN20_BEOWOLFMON_NAME_LEN, PEN20_BEOWOLFMON_ID, PEN20_BEOWOLFMON_ID_LEN, PEN20_BEOWOLFMON_FQID, PEN20_BEOWOLFMON_FQID_LEN, PEN20_BEOWOLFMON_FQNAME, PEN20_BEOWOLFMON_FQNAME_LEN },
        { PEN20_BEOWOLFMON_NAME, PEN20_BEOWOLFMON_NAME_LEN, PEN20_BEOWOLFMON_ID, PEN20_BEOWOLFMON_ID_LEN, ALT_PEN20_BEOWOLFMON_FQID, ALT_PEN20_BEOWOLFMON_FQID_LEN, ALT_PEN20_BEOWOLFMON_FQNAME, ALT_PEN20_BEOWOLFMON_FQNAME_LEN },
        { PEN20_BIG_MAMEMON_NAME, PEN20_BIG_MAMEMON_NAME_LEN, PEN20_BIG_MAMEMON_ID, PEN20_BIG_MAMEMON_ID_LEN, PEN20_BIG_MAMEMON_FQID, PEN20_BIG_MAMEMON_FQID_LEN, PEN20_BIG_MAMEMON_FQNAME, PEN20_BIG_MAMEMON_FQNAME_LEN },
        { PEN20_BIG_MAMEMON_NAME, PEN20_BIG_MAMEMON_NAME_LEN, PEN20_BIG_MAMEMON_ID, PEN20_BIG_MAMEMON_ID_LEN, ALT_PEN20_BIG_MAMEMON_FQID, ALT_PEN20_BIG_MAMEMON_FQID_LEN, ALT_PEN20_BIG_MAMEMON_FQNAME, ALT_PEN20_BIG_MAMEMON_FQNAME_LEN },
        { PEN20_BIRDRAMON_NAME, PEN20_BIRDRAMON_NAME_LEN, PEN20_BIRDRAMON_ID, PEN20_BIRDRAMON_ID_LEN, PEN20_BIRDRAMON_FQID, PEN20_BIRDRAMON_FQID_LEN, PEN20_BIRDRAMON_FQNAME, PEN20_BIRDRAMON_FQNAME_LEN },
        { PEN20_BIRDRAMON_NAME, PEN20_BIRDRAMON_NAME_LEN, PEN20_BIRDRAMON_ID, PEN20_BIRDRAMON_ID_LEN, ALT_PEN20_BIRDRAMON_FQID, ALT_PEN20_BIRDRAMON_FQID_LEN, ALT_PEN20_BIRDRAMON_FQNAME, ALT_PEN20_BIRDRAMON_FQNAME_LEN },
        { PEN20_BLOSSOMON_NAME, PEN20_BLOSSOMON_NAME_LEN, PEN20_BLOSSOMON_ID, PEN20_BLOSSOMON_ID_LEN, PEN20_BLOSSOMON_FQID, PEN20_BLOSSOMON_FQID_LEN, PEN20_BLOSSOMON_FQNAME, PEN20_BLOSSOMON_FQNAME_LEN },
        { PEN20_BLOSSOMON_NAME, PEN20_BLOSSOMON_NAME_LEN, PEN20_BLOSSOMON_ID, PEN20_BLOSSOMON_ID_LEN, ALT_PEN20_BLOSSOMON_FQID, ALT_PEN20_BLOSSOMON_FQID_LEN, ALT_PEN20_BLOSSOMON_FQNAME, ALT_PEN20_BLOSSOMON_FQNAME_LEN },
        { PEN20_BOLTMON_NAME, PEN20_BOLTMON_NAME_LEN, PEN20_BOLTMON_ID, PEN20_BOLTMON_ID_LEN, PEN20_BOLTMON_FQID, PEN20_BOLTMON_FQID_LEN, PEN20_BOLTMON_FQNAME, PEN20_BOLTMON_FQNAME_LEN },
        { PEN20_BOLTMON_NAME, PEN20_BOLTMON_NAME_LEN, PEN20_BOLTMON_ID, PEN20_BOLTMON_ID_LEN, ALT_PEN20_BOLTMON_FQID, ALT_PEN20_BOLTMON_FQID_LEN, ALT_PEN20_BOLTMON_FQNAME, ALT_PEN20_BOLTMON_FQNAME_LEN },
        { PEN20_BOTAMON_NAME, PEN20_BOTAMON_NAME_LEN, PEN20_BOTAMON_ID, PEN20_BOTAMON_ID_LEN, PEN20_BOTAMON_FQID, PEN20_BOTAMON_FQID_LEN, PEN20_BOTAMON_FQNAME, PEN20_BOTAMON_FQNAME_LEN },
        { PEN20_BOTAMON_NAME, PEN20_BOTAMON_NAME_LEN, PEN20_BOTAMON_ID, PEN20_BOTAMON_ID_LEN, ALT_PEN20_BOTAMON_FQID, ALT_PEN20_BOTAMON_FQID_LEN, ALT_PEN20_BOTAMON_FQNAME, ALT_PEN20_BOTAMON_FQNAME_LEN },
        { PEN20_BREAKDRAMON_NAME, PEN20_BREAKDRAMON_NAME_LEN, PEN20_BREAKDRAMON_ID, PEN20_BREAKDRAMON_ID_LEN, PEN20_BREAKDRAMON_FQID, PEN20_BREAKDRAMON_FQID_LEN, PEN20_BREAKDRAMON_FQNAME, PEN20_BREAKDRAMON_FQNAME_LEN },
        { PEN20_BREAKDRAMON_NAME, PEN20_BREAKDRAMON_NAME_LEN, PEN20_BREAKDRAMON_ID, PEN20_BREAKDRAMON_ID_LEN, ALT_PEN20_BREAKDRAMON_FQID, ALT_PEN20_BREAKDRAMON_FQID_LEN, ALT_PEN20_BREAKDRAMON_FQNAME, ALT_PEN20_BREAKDRAMON_FQNAME_LEN },
        { PEN20_BRYWELUDRAMON_NAME, PEN20_BRYWELUDRAMON_NAME_LEN, PEN20_BRYWELUDRAMON_ID, PEN20_BRYWELUDRAMON_ID_LEN, PEN20_BRYWELUDRAMON_FQID, PEN20_BRYWELUDRAMON_FQID_LEN, PEN20_BRYWELUDRAMON_FQNAME, PEN20_BRYWELUDRAMON_FQNAME_LEN },
        { PEN20_BRYWELUDRAMON_NAME, PEN20_BRYWELUDRAMON_NAME_LEN, PEN20_BRYWELUDRAMON_ID, PEN20_BRYWELUDRAMON_ID_LEN, ALT_PEN20_BRYWELUDRAMON_FQID, ALT_PEN20_BRYWELUDRAMON_FQID_LEN, ALT_PEN20_BRYWELUDRAMON_FQNAME, ALT_PEN20_BRYWELUDRAMON_FQNAME_LEN },
        { PEN20_BUBBMON_NAME, PEN20_BUBBMON_NAME_LEN, PEN20_BUBBMON_ID, PEN20_BUBBMON_ID_LEN, PEN20_BUBBMON_FQID, PEN20_BUBBMON_FQID_LEN, PEN20_BUBBMON_FQNAME, PEN20_BUBBMON_FQNAME_LEN },
        { PEN20_BUBBMON_NAME, PEN20_BUBBMON_NAME_LEN, PEN20_BUBBMON_ID, PEN20_BUBBMON_ID_LEN, ALT_PEN20_BUBBMON_FQID, ALT_PEN20_BUBBMON_FQID_LEN, ALT_PEN20_BUBBMON_FQNAME, ALT_PEN20_BUBBMON_FQNAME_LEN },
        { PEN20_BUDMON_NAME, PEN20_BUDMON_NAME_LEN, PEN20_BUDMON_ID, PEN20_BUDMON_ID_LEN, PEN20_BUDMON_FQID, PEN20_BUDMON_FQID_LEN, PEN20_BUDMON_FQNAME, PEN20_BUDMON_FQNAME_LEN },
        { PEN20_BUDMON_NAME, PEN20_BUDMON_NAME_LEN, PEN20_BUDMON_ID, PEN20_BUDMON_ID_LEN, ALT_PEN20_BUDMON_FQID, ALT_PEN20_BUDMON_FQID_LEN, ALT_PEN20_BUDMON_FQNAME, ALT_PEN20_BUDMON_FQNAME_LEN },
        { PEN20_BUSHI_AGUMON_NAME, PEN20_BUSHI_AGUMON_NAME_LEN, PEN20_BUSHI_AGUMON_ID, PEN20_BUSHI_AGUMON_ID_LEN, PEN20_BUSHI_AGUMON_FQID, PEN20_BUSHI_AGUMON_FQID_LEN, PEN20_BUSHI_AGUMON_FQNAME, PEN20_BUSHI_AGUMON_FQNAME_LEN },
        { PEN20_BUSHI_AGUMON_NAME, PEN20_BUSHI_AGUMON_NAME_LEN, PEN20_BUSHI_AGUMON_ID, PEN20_BUSHI_AGUMON_ID_LEN, ALT_PEN20_BUSHI_AGUMON_FQID, ALT_PEN20_BUSHI_AGUMON_FQID_LEN, ALT_PEN20_BUSHI_AGUMON_FQNAME, ALT_PEN20_BUSHI_AGUMON_FQNAME_LEN },
        { PEN20_CANDMON_NAME, PEN20_CANDMON_NAME_LEN, PEN20_CANDMON_ID, PEN20_CANDMON_ID_LEN, PEN20_CANDMON_FQID, PEN20_CANDMON_FQID_LEN, PEN20_CANDMON_FQNAME, PEN20_CANDMON_FQNAME_LEN },
        { PEN20_CANDMON_NAME, PEN20_CANDMON_NAME_LEN, PEN20_CANDMON_ID, PEN20_CANDMON_ID_LEN, ALT_PEN20_CANDMON_FQID, ALT_PEN20_CANDMON_FQID_LEN, ALT_PEN20_CANDMON_FQNAME, ALT_PEN20_CANDMON_FQNAME_LEN },
        { PEN20_CAPRIMON_NAME, PEN20_CAPRIMON_NAME_LEN, PEN20_CAPRIMON_ID, PEN20_CAPRIMON_ID_LEN, PEN20_CAPRIMON_FQID, PEN20_CAPRIMON_FQID_LEN, PEN20_CAPRIMON_FQNAME, PEN20_CAPRIMON_FQNAME_LEN },
        { PEN20_CAPRIMON_NAME, PEN20_CAPRIMON_NAME_LEN, PEN20_CAPRIMON_ID, PEN20_CAPRIMON_ID_LEN, ALT_PEN20_CAPRIMON_FQID, ALT_PEN20_CAPRIMON_FQID_LEN, ALT_PEN20_CAPRIMON_FQNAME, ALT_PEN20_CAPRIMON_FQNAME_LEN },
        { PEN20_CHAOSMON_NAME, PEN20_CHAOSMON_NAME_LEN, PEN20_CHAOSMON_ID, PEN20_CHAOSMON_ID_LEN, PEN20_CHAOSMON_FQID, PEN20_CHAOSMON_FQID_LEN, PEN20_CHAOSMON_FQNAME, PEN20_CHAOSMON_FQNAME_LEN },
        { PEN20_CHAOSMON_NAME, PEN20_CHAOSMON_NAME_LEN, PEN20_CHAOSMON_ID, PEN20_CHAOSMON_ID_LEN, ALT_PEN20_CHAOSMON_FQID, ALT_PEN20_CHAOSMON_FQID_LEN, ALT_PEN20_CHAOSMON_FQNAME, ALT_PEN20_CHAOSMON_FQNAME_LEN },
        { PEN20_CHERUBIMON_NAME, PEN20_CHERUBIMON_NAME_LEN, PEN20_CHERUBIMON_ID, PEN20_CHERUBIMON_ID_LEN, PEN20_CHERUBIMON_FQID, PEN20_CHERUBIMON_FQID_LEN, PEN20_CHERUBIMON_FQNAME, PEN20_CHERUBIMON_FQNAME_LEN },
        { PEN20_CHERUBIMON_NAME, PEN20_CHERUBIMON_NAME_LEN, PEN20_CHERUBIMON_ID, PEN20_CHERUBIMON_ID_LEN, ALT_PEN20_CHERUBIMON_FQID, ALT_PEN20_CHERUBIMON_FQID_LEN, ALT_PEN20_CHERUBIMON_FQNAME, ALT_PEN20_CHERUBIMON_FQNAME_LEN },
        { PEN20_CHIBIMON_NAME, PEN20_CHIBIMON_NAME_LEN, PEN20_CHIBIMON_ID, PEN20_CHIBIMON_ID_LEN, PEN20_CHIBIMON_FQID, PEN20_CHIBIMON_FQID_LEN, PEN20_CHIBIMON_FQNAME, PEN20_CHIBIMON_FQNAME_LEN },
        { PEN20_CHIBIMON_NAME, PEN20_CHIBIMON_NAME_LEN, PEN20_CHIBIMON_ID, PEN20_CHIBIMON_ID_LEN, ALT_PEN20_CHIBIMON_FQID, ALT_PEN20_CHIBIMON_FQID_LEN, ALT_PEN20_CHIBIMON_FQNAME, ALT_PEN20_CHIBIMON_FQNAME_LEN },
        { PEN20_CHICOMON_NAME, PEN20_CHICOMON_NAME_LEN, PEN20_CHICOMON_ID, PEN20_CHICOMON_ID_LEN, PEN20_CHICOMON_FQID, PEN20_CHICOMON_FQID_LEN, PEN20_CHICOMON_FQNAME, PEN20_CHICOMON_FQNAME_LEN },
        { PEN20_CHICOMON_NAME, PEN20_CHICOMON_NAME_LEN, PEN20_CHICOMON_ID, PEN20_CHICOMON_ID_LEN, ALT_PEN20_CHICOMON_FQID, ALT_PEN20_CHICOMON_FQID_LEN, ALT_PEN20_CHICOMON_FQNAME, ALT_PEN20_CHICOMON_FQNAME_LEN },
        { PEN20_CHOCOMON_NAME, PEN20_CHOCOMON_NAME_LEN, PEN20_CHOCOMON_ID, PEN20_CHOCOMON_ID_LEN, PEN20_CHOCOMON_FQID, PEN20_CHOCOMON_FQID_LEN, PEN20_CHOCOMON_FQNAME, PEN20_CHOCOMON_FQNAME_LEN },
        { PEN20_CHOCOMON_NAME, PEN20_CHOCOMON_NAME_LEN, PEN20_CHOCOMON_ID, PEN20_CHOCOMON_ID_LEN, ALT_PEN20_CHOCOMON_FQID, ALT_PEN20_CHOCOMON_FQID_LEN, ALT_PEN20_CHOCOMON_FQNAME, ALT_PEN20_CHOCOMON_FQNAME_LEN },
        { PEN20_CHOROMON_NAME, PEN20_CHOROMON_NAME_LEN, PEN20_CHOROMON_ID, PEN20_CHOROMON_ID_LEN, PEN20_CHOROMON_FQID, PEN20_CHOROMON_FQID_LEN, PEN20_CHOROMON_FQNAME, PEN20_CHOROMON_FQNAME_LEN },
        { PEN20_CHOROMON_NAME, PEN20_CHOROMON_NAME_LEN, PEN20_CHOROMON_ID, PEN20_CHOROMON_ID_LEN, ALT_PEN20_CHOROMON_FQID, ALT_PEN20_CHOROMON_FQID_LEN, ALT_PEN20_CHOROMON_FQNAME, ALT_PEN20_CHOROMON_FQNAME_LEN },
        { PEN20_CLOCKMON_NAME, PEN20_CLOCKMON_NAME_LEN, PEN20_CLOCKMON_ID, PEN20_CLOCKMON_ID_LEN, PEN20_CLOCKMON_FQID, PEN20_CLOCKMON_FQID_LEN, PEN20_CLOCKMON_FQNAME, PEN20_CLOCKMON_FQNAME_LEN },
        { PEN20_CLOCKMON_NAME, PEN20_CLOCKMON_NAME_LEN, PEN20_CLOCKMON_ID, PEN20_CLOCKMON_ID_LEN, ALT_PEN20_CLOCKMON_FQID, ALT_PEN20_CLOCKMON_FQID_LEN, ALT_PEN20_CLOCKMON_FQNAME, ALT_PEN20_CLOCKMON_FQNAME_LEN },
        { PEN20_COCOMON_NAME, PEN20_COCOMON_NAME_LEN, PEN20_COCOMON_ID, PEN20_COCOMON_ID_LEN, PEN20_COCOMON_FQID, PEN20_COCOMON_FQID_LEN, PEN20_COCOMON_FQNAME, PEN20_COCOMON_FQNAME_LEN },
        { PEN20_COCOMON_NAME, PEN20_COCOMON_NAME_LEN, PEN20_COCOMON_ID, PEN20_COCOMON_ID_LEN, ALT_PEN20_COCOMON_FQID, ALT_PEN20_COCOMON_FQID_LEN, ALT_PEN20_COCOMON_FQNAME, ALT_PEN20_COCOMON_FQNAME_LEN },
        { PEN20_COELAMON_NAME, PEN20_COELAMON_NAME_LEN, PEN20_COELAMON_ID, PEN20_COELAMON_ID_LEN, PEN20_COELAMON_FQID, PEN20_COELAMON_FQID_LEN, PEN20_COELAMON_FQNAME, PEN20_COELAMON_FQNAME_LEN },
        { PEN20_COELAMON_NAME, PEN20_COELAMON_NAME_LEN, PEN20_COELAMON_ID, PEN20_COELAMON_ID_LEN, ALT_PEN20_COELAMON_FQID, ALT_PEN20_COELAMON_FQID_LEN, ALT_PEN20_COELAMON_FQNAME, ALT_PEN20_COELAMON_FQNAME_LEN },
        { PEN20_COREDRAMON_BLUE_NAME, PEN20_COREDRAMON_BLUE_NAME_LEN, PEN20_COREDRAMON_BLUE_ID, PEN20_COREDRAMON_BLUE_ID_LEN, PEN20_COREDRAMON_BLUE_FQID, PEN20_COREDRAMON_BLUE_FQID_LEN, PEN20_COREDRAMON_BLUE_FQNAME, PEN20_COREDRAMON_BLUE_FQNAME_LEN },
        { PEN20_COREDRAMON_BLUE_NAME, PEN20_COREDRAMON_BLUE_NAME_LEN, PEN20_COREDRAMON_BLUE_ID, PEN20_COREDRAMON_BLUE_ID_LEN, ALT_PEN20_COREDRAMON_BLUE_FQID, ALT_PEN20_COREDRAMON_BLUE_FQID_LEN, ALT_PEN20_COREDRAMON_BLUE_FQNAME, ALT_PEN20_COREDRAMON_BLUE_FQNAME_LEN },
        { PEN20_COREDRAMON_GREEN_NAME, PEN20_COREDRAMON_GREEN_NAME_LEN, PEN20_COREDRAMON_GREEN_ID, PEN20_COREDRAMON_GREEN_ID_LEN, PEN20_COREDRAMON_GREEN_FQID, PEN20_COREDRAMON_GREEN_FQID_LEN, PEN20_COREDRAMON_GREEN_FQNAME, PEN20_COREDRAMON_GREEN_FQNAME_LEN },
        { PEN20_COREDRAMON_GREEN_NAME, PEN20_COREDRAMON_GREEN_NAME_LEN, PEN20_COREDRAMON_GREEN_ID, PEN20_COREDRAMON_GREEN_ID_LEN, ALT_PEN20_COREDRAMON_GREEN_FQID, ALT_PEN20_COREDRAMON_GREEN_FQID_LEN, ALT_PEN20_COREDRAMON_GREEN_FQNAME, ALT_PEN20_COREDRAMON_GREEN_FQNAME_LEN },
        { PEN20_COTSUCOMON_NAME, PEN20_COTSUCOMON_NAME_LEN, PEN20_COTSUCOMON_ID, PEN20_COTSUCOMON_ID_LEN, PEN20_COTSUCOMON_FQID, PEN20_COTSUCOMON_FQID_LEN, PEN20_COTSUCOMON_FQNAME, PEN20_COTSUCOMON_FQNAME_LEN },
        { PEN20_COTSUCOMON_NAME, PEN20_COTSUCOMON_NAME_LEN, PEN20_COTSUCOMON_ID, PEN20_COTSUCOMON_ID_LEN, ALT_PEN20_COTSUCOMON_FQID, ALT_PEN20_COTSUCOMON_FQID_LEN, ALT_PEN20_COTSUCOMON_FQNAME, ALT_PEN20_COTSUCOMON_FQNAME_LEN },
        { PEN20_CYBERDRAMON_NAME, PEN20_CYBERDRAMON_NAME_LEN, PEN20_CYBERDRAMON_ID, PEN20_CYBERDRAMON_ID_LEN, PEN20_CYBERDRAMON_FQID, PEN20_CYBERDRAMON_FQID_LEN, PEN20_CYBERDRAMON_FQNAME, PEN20_CYBERDRAMON_FQNAME_LEN },
        { PEN20_CYBERDRAMON_NAME, PEN20_CYBERDRAMON_NAME_LEN, PEN20_CYBERDRAMON_ID, PEN20_CYBERDRAMON_ID_LEN, ALT_PEN20_CYBERDRAMON_FQID, ALT_PEN20_CYBERDRAMON_FQID_LEN, ALT_PEN20_CYBERDRAMON_FQNAME, ALT_PEN20_CYBERDRAMON_FQNAME_LEN },
        { PEN20_DAGOMON_NAME, PEN20_DAGOMON_NAME_LEN, PEN20_DAGOMON_ID, PEN20_DAGOMON_ID_LEN, PEN20_DAGOMON_FQID, PEN20_DAGOMON_FQID_LEN, PEN20_DAGOMON_FQNAME, PEN20_DAGOMON_FQNAME_LEN },
        { PEN20_DAGOMON_NAME, PEN20_DAGOMON_NAME_LEN, PEN20_DAGOMON_ID, PEN20_DAGOMON_ID_LEN, ALT_PEN20_DAGOMON_FQID, ALT_PEN20_DAGOMON_FQID_LEN, ALT_PEN20_DAGOMON_FQNAME, ALT_PEN20_DAGOMON_FQNAME_LEN },
        { PEN20_DARKDRAMON_NAME, PEN20_DARKDRAMON_NAME_LEN, PEN20_DARKDRAMON_ID, PEN20_DARKDRAMON_ID_LEN, PEN20_DARKDRAMON_FQID, PEN20_DARKDRAMON_FQID_LEN, PEN20_DARKDRAMON_FQNAME, PEN20_DARKDRAMON_FQNAME_LEN },
        { PEN20_DARKDRAMON_NAME, PEN20_DARKDRAMON_NAME_LEN, PEN20_DARKDRAMON_ID, PEN20_DARKDRAMON_ID_LEN, ALT_PEN20_DARKDRAMON_FQID, ALT_PEN20_DARKDRAMON_FQID_LEN, ALT_PEN20_DARKDRAMON_FQNAME, ALT_PEN20_DARKDRAMON_FQNAME_LEN },
        { PEN20_DARK_KNIGHTMON_NAME, PEN20_DARK_KNIGHTMON_NAME_LEN, PEN20_DARK_KNIGHTMON_ID, PEN20_DARK_KNIGHTMON_ID_LEN, PEN20_DARK_KNIGHTMON_FQID, PEN20_DARK_KNIGHTMON_FQID_LEN, PEN20_DARK_KNIGHTMON_FQNAME, PEN20_DARK_KNIGHTMON_FQNAME_LEN },
        { PEN20_DARK_KNIGHTMON_NAME, PEN20_DARK_KNIGHTMON_NAME_LEN, PEN20_DARK_KNIGHTMON_ID, PEN20_DARK_KNIGHTMON_ID_LEN, ALT_PEN20_DARK_KNIGHTMON_FQID, ALT_PEN20_DARK_KNIGHTMON_FQID_LEN, ALT_PEN20_DARK_KNIGHTMON_FQNAME, ALT_PEN20_DARK_KNIGHTMON_FQNAME_LEN },
        { PEN20_DEATH_MERAMON_NAME, PEN20_DEATH_MERAMON_NAME_LEN, PEN20_DEATH_MERAMON_ID, PEN20_DEATH_MERAMON_ID_LEN, PEN20_DEATH_MERAMON_FQID, PEN20_DEATH_MERAMON_FQID_LEN, PEN20_DEATH_MERAMON_FQNAME, PEN20_DEATH_MERAMON_FQNAME_LEN },
        { PEN20_DEATH_MERAMON_NAME, PEN20_DEATH_MERAMON_NAME_LEN, PEN20_DEATH_MERAMON_ID, PEN20_DEATH_MERAMON_ID_LEN, ALT_PEN20_DEATH_MERAMON_FQID, ALT_PEN20_DEATH_MERAMON_FQID_LEN, ALT_PEN20_DEATH_MERAMON_FQNAME, ALT_PEN20_DEATH_MERAMON_FQNAME_LEN },
        { PEN20_DELUMON_NAME, PEN20_DELUMON_NAME_LEN, PEN20_DELUMON_ID, PEN20_DELUMON_ID_LEN, PEN20_DELUMON_FQID, PEN20_DELUMON_FQID_LEN, PEN20_DELUMON_FQNAME, PEN20_DELUMON_FQNAME_LEN },
        { PEN20_DELUMON_NAME, PEN20_DELUMON_NAME_LEN, PEN20_DELUMON_ID, PEN20_DELUMON_ID_LEN, ALT_PEN20_DELUMON_FQID, ALT_PEN20_DELUMON_FQID_LEN, ALT_PEN20_DELUMON_FQNAME, ALT_PEN20_DELUMON_FQNAME_LEN },
        { PEN20_DEVIDRAMON_NAME, PEN20_DEVIDRAMON_NAME_LEN, PEN20_DEVIDRAMON_ID, PEN20_DEVIDRAMON_ID_LEN, PEN20_DEVIDRAMON_FQID, PEN20_DEVIDRAMON_FQID_LEN, PEN20_DEVIDRAMON_FQNAME, PEN20_DEVIDRAMON_FQNAME_LEN },
        { PEN20_DEVIDRAMON_NAME, PEN20_DEVIDRAMON_NAME_LEN, PEN20_DEVIDRAMON_ID, PEN20_DEVIDRAMON_ID_LEN, ALT_PEN20_DEVIDRAMON_FQID, ALT_PEN20_DEVIDRAMON_FQID_LEN, ALT_PEN20_DEVIDRAMON_FQNAME, ALT_PEN20_DEVIDRAMON_FQNAME_LEN },
        { PEN20_DEVIMON_NAME, PEN20_DEVIMON_NAME_LEN, PEN20_DEVIMON_ID, PEN20_DEVIMON_ID_LEN, PEN20_DEVIMON_FQID, PEN20_DEVIMON_FQID_LEN, PEN20_DEVIMON_FQNAME, PEN20_DEVIMON_FQNAME_LEN },
        { PEN20_DEVIMON_NAME, PEN20_DEVIMON_NAME_LEN, PEN20_DEVIMON_ID, PEN20_DEVIMON_ID_LEN, ALT_PEN20_DEVIMON_FQID, ALT_PEN20_DEVIMON_FQID_LEN, ALT_PEN20_DEVIMON_FQNAME, ALT_PEN20_DEVIMON_FQNAME_LEN },
        { PEN20_DODOMON_NAME, PEN20_DODOMON_NAME_LEN, PEN20_DODOMON_ID, PEN20_DODOMON_ID_LEN, PEN20_DODOMON_FQID, PEN20_DODOMON_FQID_LEN, PEN20_DODOMON_FQNAME, PEN20_DODOMON_FQNAME_LEN },
        { PEN20_DODOMON_NAME, PEN20_DODOMON_NAME_LEN, PEN20_DODOMON_ID, PEN20_DODOMON_ID_LEN, ALT_PEN20_DODOMON_FQID, ALT_PEN20_DODOMON_FQID_LEN, ALT_PEN20_DODOMON_FQNAME, ALT_PEN20_DODOMON_FQNAME_LEN },
        { PEN20_DOKUGUMON_NAME, PEN20_DOKUGUMON_NAME_LEN, PEN20_DOKUGUMON_ID, PEN20_DOKUGUMON_ID_LEN, PEN20_DOKUGUMON_FQID, PEN20_DOKUGUMON_FQID_LEN, PEN20_DOKUGUMON_FQNAME, PEN20_DOKUGUMON_FQNAME_LEN },
        { PEN20_DOKUGUMON_NAME, PEN20_DOKUGUMON_NAME_LEN, PEN20_DOKUGUMON_ID, PEN20_DOKUGUMON_ID_LEN, ALT_PEN20_DOKUGUMON_FQID, ALT_PEN20_DOKUGUMON_FQID_LEN, ALT_PEN20_DOKUGUMON_FQNAME, ALT_PEN20_DOKUGUMON_FQNAME_LEN },
        { PEN20_DORIMON_NAME, PEN20_DORIMON_NAME_LEN, PEN20_DORIMON_ID, PEN20_DORIMON_ID_LEN, PEN20_DORIMON_FQID, PEN20_DORIMON_FQID_LEN, PEN20_DORIMON_FQNAME, PEN20_DORIMON_FQNAME_LEN },
        { PEN20_DORIMON_NAME, PEN20_DORIMON_NAME_LEN, PEN20_DORIMON_ID, PEN20_DORIMON_ID_LEN, ALT_PEN20_DORIMON_FQID, ALT_PEN20_DORIMON_FQID_LEN, ALT_PEN20_DORIMON_FQNAME, ALT_PEN20_DORIMON_FQNAME_LEN },
        { PEN20_DORUGAMON_NAME, PEN20_DORUGAMON_NAME_LEN, PEN20_DORUGAMON_ID, PEN20_DORUGAMON_ID_LEN, PEN20_DORUGAMON_FQID, PEN20_DORUGAMON_FQID_LEN, PEN20_DORUGAMON_FQNAME, PEN20_DORUGAMON_FQNAME_LEN },
        { PEN20_DORUGAMON_NAME, PEN20_DORUGAMON_NAME_LEN, PEN20_DORUGAMON_ID, PEN20_DORUGAMON_ID_LEN, ALT_PEN20_DORUGAMON_FQID, ALT_PEN20_DORUGAMON_FQID_LEN, ALT_PEN20_DORUGAMON_FQNAME, ALT_PEN20_DORUGAMON_FQNAME_LEN },
        { PEN20_DORUGORAMON_NAME, PEN20_DORUGORAMON_NAME_LEN, PEN20_DORUGORAMON_ID, PEN20_DORUGORAMON_ID_LEN, PEN20_DORUGORAMON_FQID, PEN20_DORUGORAMON_FQID_LEN, PEN20_DORUGORAMON_FQNAME, PEN20_DORUGORAMON_FQNAME_LEN },
        { PEN20_DORUGORAMON_NAME, PEN20_DORUGORAMON_NAME_LEN, PEN20_DORUGORAMON_ID, PEN20_DORUGORAMON_ID_LEN, ALT_PEN20_DORUGORAMON_FQID, ALT_PEN20_DORUGORAMON_FQID_LEN, ALT_PEN20_DORUGORAMON_FQNAME, ALT_PEN20_DORUGORAMON_FQNAME_LEN },
        { PEN20_DORUGUREMON_NAME, PEN20_DORUGUREMON_NAME_LEN, PEN20_DORUGUREMON_ID, PEN20_DORUGUREMON_ID_LEN, PEN20_DORUGUREMON_FQID, PEN20_DORUGUREMON_FQID_LEN, PEN20_DORUGUREMON_FQNAME, PEN20_DORUGUREMON_FQNAME_LEN },
        { PEN20_DORUGUREMON_NAME, PEN20_DORUGUREMON_NAME_LEN, PEN20_DORUGUREMON_ID, PEN20_DORUGUREMON_ID_LEN, ALT_PEN20_DORUGUREMON_FQID, ALT_PEN20_DORUGUREMON_FQID_LEN, ALT_PEN20_DORUGUREMON_FQNAME, ALT_PEN20_DORUGUREMON_FQNAME_LEN },
        { PEN20_DORUMON_NAME, PEN20_DORUMON_NAME_LEN, PEN20_DORUMON_ID, PEN20_DORUMON_ID_LEN, PEN20_DORUMON_FQID, PEN20_DORUMON_FQID_LEN, PEN20_DORUMON_FQNAME, PEN20_DORUMON_FQNAME_LEN },
        { PEN20_DORUMON_NAME, PEN20_DORUMON_NAME_LEN, PEN20_DORUMON_ID, PEN20_DORUMON_ID_LEN, ALT_PEN20_DORUMON_FQID, ALT_PEN20_DORUMON_FQID_LEN, ALT_PEN20_DORUMON_FQNAME, ALT_PEN20_DORUMON_FQNAME_LEN },
        { PEN20_DRACOMON_NAME, PEN20_DRACOMON_NAME_LEN, PEN20_DRACOMON_ID, PEN20_DRACOMON_ID_LEN, PEN20_DRACOMON_FQID, PEN20_DRACOMON_FQID_LEN, PEN20_DRACOMON_FQNAME, PEN20_DRACOMON_FQNAME_LEN },
        { PEN20_DRACOMON_NAME, PEN20_DRACOMON_NAME_LEN, PEN20_DRACOMON_ID, PEN20_DRACOMON_ID_LEN, ALT_PEN20_DRACOMON_FQID, ALT_PEN20_DRACOMON_FQID_LEN, ALT_PEN20_DRACOMON_FQNAME, ALT_PEN20_DRACOMON_FQNAME_LEN },
        { PEN20_DURAMON_NAME, PEN20_DURAMON_NAME_LEN, PEN20_DURAMON_ID, PEN20_DURAMON_ID_LEN, PEN20_DURAMON_FQID, PEN20_DURAMON_FQID_LEN, PEN20_DURAMON_FQNAME, PEN20_DURAMON_FQNAME_LEN },
        { PEN20_DURAMON_NAME, PEN20_DURAMON_NAME_LEN, PEN20_DURAMON_ID, PEN20_DURAMON_ID_LEN, ALT_PEN20_DURAMON_FQID, ALT_PEN20_DURAMON_FQID_LEN, ALT_PEN20_DURAMON_FQNAME, ALT_PEN20_DURAMON_FQNAME_LEN },
        { PEN20_DURANDAMON_NAME, PEN20_DURANDAMON_NAME_LEN, PEN20_DURANDAMON_ID, PEN20_DURANDAMON_ID_LEN, PEN20_DURANDAMON_FQID, PEN20_DURANDAMON_FQID_LEN, PEN20_DURANDAMON_FQNAME, PEN20_DURANDAMON_FQNAME_LEN },
        { PEN20_DURANDAMON_NAME, PEN20_DURANDAMON_NAME_LEN, PEN20_DURANDAMON_ID, PEN20_DURANDAMON_ID_LEN, ALT_PEN20_DURANDAMON_FQID, ALT_PEN20_DURANDAMON_FQID_LEN, ALT_PEN20_DURANDAMON_FQNAME, ALT_PEN20_DURANDAMON_FQNAME_LEN },
        { PEN20_EBIDRAMON_NAME, PEN20_EBIDRAMON_NAME_LEN, PEN20_EBIDRAMON_ID, PEN20_EBIDRAMON_ID_LEN, PEN20_EBIDRAMON_FQID, PEN20_EBIDRAMON_FQID_LEN, PEN20_EBIDRAMON_FQNAME, PEN20_EBIDRAMON_FQNAME_LEN },
        { PEN20_EBIDRAMON_NAME, PEN20_EBIDRAMON_NAME_LEN, PEN20_EBIDRAMON_ID, PEN20_EBIDRAMON_ID_LEN, ALT_PEN20_EBIDRAMON_FQID, ALT_PEN20_EBIDRAMON_FQID_LEN, ALT_PEN20_EBIDRAMON_FQNAME, ALT_PEN20_EBIDRAMON_FQNAME_LEN },
        { PEN20_ETEMON_NAME, PEN20_ETEMON_NAME_LEN, PEN20_ETEMON_ID, PEN20_ETEMON_ID_LEN, PEN20_ETEMON_FQID, PEN20_ETEMON_FQID_LEN, PEN20_ETEMON_FQNAME, PEN20_ETEMON_FQNAME_LEN },
        { PEN20_ETEMON_NAME, PEN20_ETEMON_NAME_LEN, PEN20_ETEMON_ID, PEN20_ETEMON_ID_LEN, ALT_PEN20_ETEMON_FQID, ALT_PEN20_ETEMON_FQID_LEN, ALT_PEN20_ETEMON_FQNAME, ALT_PEN20_ETEMON_FQNAME_LEN },
        { PEN20_EXAMON_NAME, PEN20_EXAMON_NAME_LEN, PEN20_EXAMON_ID, PEN20_EXAMON_ID_LEN, PEN20_EXAMON_FQID, PEN20_EXAMON_FQID_LEN, PEN20_EXAMON_FQNAME, PEN20_EXAMON_FQNAME_LEN },
        { PEN20_EXAMON_NAME, PEN20_EXAMON_NAME_LEN, PEN20_EXAMON_ID, PEN20_EXAMON_ID_LEN, ALT_PEN20_EXAMON_FQID, ALT_PEN20_EXAMON_FQID_LEN, ALT_PEN20_EXAMON_FQNAME, ALT_PEN20_EXAMON_FQNAME_LEN },
        { PEN20_FANTOMON_NAME, PEN20_FANTOMON_NAME_LEN, PEN20_FANTOMON_ID, PEN20_FANTOMON_ID_LEN, PEN20_FANTOMON_FQID, PEN20_FANTOMON_FQID_LEN, PEN20_FANTOMON_FQNAME, PEN20_FANTOMON_FQNAME_LEN },
        { PEN20_FANTOMON_NAME, PEN20_FANTOMON_NAME_LEN, PEN20_FANTOMON_ID, PEN20_FANTOMON_ID_LEN, ALT_PEN20_FANTOMON_FQID, ALT_PEN20_FANTOMON_FQID_LEN, ALT_PEN20_FANTOMON_FQNAME, ALT_PEN20_FANTOMON_FQNAME_LEN },
        { PEN20_FLORAMON_NAME, PEN20_FLORAMON_NAME_LEN, PEN20_FLORAMON_ID, PEN20_FLORAMON_ID_LEN, PEN20_FLORAMON_FQID, PEN20_FLORAMON_FQID_LEN, PEN20_FLORAMON_FQNAME, PEN20_FLORAMON_FQNAME_LEN },
        { PEN20_FLORAMON_NAME, PEN20_FLORAMON_NAME_LEN, PEN20_FLORAMON_ID, PEN20_FLORAMON_ID_LEN, ALT_PEN20_FLORAMON_FQID, ALT_PEN20_FLORAMON_FQID_LEN, ALT_PEN20_FLORAMON_FQNAME, ALT_PEN20_FLORAMON_FQNAME_LEN },
        { PEN20_FUFUMON_NAME, PEN20_FUFUMON_NAME_LEN, PEN20_FUFUMON_ID, PEN20_FUFUMON_ID_LEN, PEN20_FUFUMON_FQID, PEN20_FUFUMON_FQID_LEN, PEN20_FUFUMON_FQNAME, PEN20_FUFUMON_FQNAME_LEN },
        { PEN20_FUFUMON_NAME, PEN20_FUFUMON_NAME_LEN, PEN20_FUFUMON_ID, PEN20_FUFUMON_ID_LEN, ALT_PEN20_FUFUMON_FQID, ALT_PEN20_FUFUMON_FQID_LEN, ALT_PEN20_FUFUMON_FQNAME, ALT_PEN20_FUFUMON_FQNAME_LEN },
        { PEN20_GABUMON_NAME, PEN20_GABUMON_NAME_LEN, PEN20_GABUMON_ID, PEN20_GABUMON_ID_LEN, PEN20_GABUMON_FQID, PEN20_GABUMON_FQID_LEN, PEN20_GABUMON_FQNAME, PEN20_GABUMON_FQNAME_LEN },
        { PEN20_GABUMON_NAME, PEN20_GABUMON_NAME_LEN, PEN20_GABUMON_ID, PEN20_GABUMON_ID_LEN, ALT_PEN20_GABUMON_FQID, ALT_PEN20_GABUMON_FQID_LEN, ALT_PEN20_GABUMON_FQNAME, ALT_PEN20_GABUMON_FQNAME_LEN },
        { PEN20_GALGOMON_NAME, PEN20_GALGOMON_NAME_LEN, PEN20_GALGOMON_ID, PEN20_GALGOMON_ID_LEN, PEN20_GALGOMON_FQID, PEN20_GALGOMON_FQID_LEN, PEN20_GALGOMON_FQNAME, PEN20_GALGOMON_FQNAME_LEN },
        { PEN20_GALGOMON_NAME, PEN20_GALGOMON_NAME_LEN, PEN20_GALGOMON_ID, PEN20_GALGOMON_ID_LEN, ALT_PEN20_GALGOMON_FQID, ALT_PEN20_GALGOMON_FQID_LEN, ALT_PEN20_GALGOMON_FQNAME, ALT_PEN20_GALGOMON_FQNAME_LEN },
        { PEN20_GANIMON_NAME, PEN20_GANIMON_NAME_LEN, PEN20_GANIMON_ID, PEN20_GANIMON_ID_LEN, PEN20_GANIMON_FQID, PEN20_GANIMON_FQID_LEN, PEN20_GANIMON_FQNAME, PEN20_GANIMON_FQNAME_LEN },
        { PEN20_GANIMON_NAME, PEN20_GANIMON_NAME_LEN, PEN20_GANIMON_ID, PEN20_GANIMON_ID_LEN, ALT_PEN20_GANIMON_FQID, ALT_PEN20_GANIMON_FQID_LEN, ALT_PEN20_GANIMON_FQNAME, ALT_PEN20_GANIMON_FQNAME_LEN },
        { PEN20_GARUDAMON_NAME, PEN20_GARUDAMON_NAME_LEN, PEN20_GARUDAMON_ID, PEN20_GARUDAMON_ID_LEN, PEN20_GARUDAMON_FQID, PEN20_GARUDAMON_FQID_LEN, PEN20_GARUDAMON_FQNAME, PEN20_GARUDAMON_FQNAME_LEN },
        { PEN20_GARUDAMON_NAME, PEN20_GARUDAMON_NAME_LEN, PEN20_GARUDAMON_ID, PEN20_GARUDAMON_ID_LEN, ALT_PEN20_GARUDAMON_FQID, ALT_PEN20_GARUDAMON_FQID_LEN, ALT_PEN20_GARUDAMON_FQNAME, ALT_PEN20_GARUDAMON_FQNAME_LEN },
        { PEN20_GARURUMON_NAME, PEN20_GARURUMON_NAME_LEN, PEN20_GARURUMON_ID, PEN20_GARURUMON_ID_LEN, PEN20_GARURUMON_FQID, PEN20_GARURUMON_FQID_LEN, PEN20_GARURUMON_FQNAME, PEN20_GARURUMON_FQNAME_LEN },
        { PEN20_GARURUMON_NAME, PEN20_GARURUMON_NAME_LEN, PEN20_GARURUMON_ID, PEN20_GARURUMON_ID_LEN, ALT_PEN20_GARURUMON_FQID, ALT_PEN20_GARURUMON_FQID_LEN, ALT_PEN20_GARURUMON_FQNAME, ALT_PEN20_GARURUMON_FQNAME_LEN },
        { PEN20_GEKOMON_NAME, PEN20_GEKOMON_NAME_LEN, PEN20_GEKOMON_ID, PEN20_GEKOMON_ID_LEN, PEN20_GEKOMON_FQID, PEN20_GEKOMON_FQID_LEN, PEN20_GEKOMON_FQNAME, PEN20_GEKOMON_FQNAME_LEN },
        { PEN20_GEKOMON_NAME, PEN20_GEKOMON_NAME_LEN, PEN20_GEKOMON_ID, PEN20_GEKOMON_ID_LEN, ALT_PEN20_GEKOMON_FQID, ALT_PEN20_GEKOMON_FQID_LEN, ALT_PEN20_GEKOMON_FQNAME, ALT_PEN20_GEKOMON_FQNAME_LEN },
        { PEN20_GERBEMON_NAME, PEN20_GERBEMON_NAME_LEN, PEN20_GERBEMON_ID, PEN20_GERBEMON_ID_LEN, PEN20_GERBEMON_FQID, PEN20_GERBEMON_FQID_LEN, PEN20_GERBEMON_FQNAME, PEN20_GERBEMON_FQNAME_LEN },
        { PEN20_GERBEMON_NAME, PEN20_GERBEMON_NAME_LEN, PEN20_GERBEMON_ID, PEN20_GERBEMON_ID_LEN, ALT_PEN20_GERBEMON_FQID, ALT_PEN20_GERBEMON_FQID_LEN, ALT_PEN20_GERBEMON_FQNAME, ALT_PEN20_GERBEMON_FQNAME_LEN },
        { PEN20_GESOMON_NAME, PEN20_GESOMON_NAME_LEN, PEN20_GESOMON_ID, PEN20_GESOMON_ID_LEN, PEN20_GESOMON_FQID, PEN20_GESOMON_FQID_LEN, PEN20_GESOMON_FQNAME, PEN20_GESOMON_FQNAME_LEN },
        { PEN20_GESOMON_NAME, PEN20_GESOMON_NAME_LEN, PEN20_GESOMON_ID, PEN20_GESOMON_ID_LEN, ALT_PEN20_GESOMON_FQID, ALT_PEN20_GESOMON_FQID_LEN, ALT_PEN20_GESOMON_FQNAME, ALT_PEN20_GESOMON_FQNAME_LEN },
        { PEN20_GINRYUMON_NAME, PEN20_GINRYUMON_NAME_LEN, PEN20_GINRYUMON_ID, PEN20_GINRYUMON_ID_LEN, PEN20_GINRYUMON_FQID, PEN20_GINRYUMON_FQID_LEN, PEN20_GINRYUMON_FQNAME, PEN20_GINRYUMON_FQNAME_LEN },
        { PEN20_GINRYUMON_NAME, PEN20_GINRYUMON_NAME_LEN, PEN20_GINRYUMON_ID, PEN20_GINRYUMON_ID_LEN, ALT_PEN20_GINRYUMON_FQID, ALT_PEN20_GINRYUMON_FQID_LEN, ALT_PEN20_GINRYUMON_FQNAME, ALT_PEN20_GINRYUMON_FQNAME_LEN },
        { PEN20_GOMAMON_NAME, PEN20_GOMAMON_NAME_LEN, PEN20_GOMAMON_ID, PEN20_GOMAMON_ID_LEN, PEN20_GOMAMON_FQID, PEN20_GOMAMON_FQID_LEN, PEN20_GOMAMON_FQNAME, PEN20_GOMAMON_FQNAME_LEN },
        { PEN20_GOMAMON_NAME, PEN20_GOMAMON_NAME_LEN, PEN20_GOMAMON_ID, PEN20_GOMAMON_ID_LEN, ALT_PEN20_GOMAMON_FQID, ALT_PEN20_GOMAMON_FQID_LEN, ALT_PEN20_GOMAMON_FQNAME, ALT_PEN20_GOMAMON_FQNAME_LEN },
        { PEN20_GOTTSUMON_NAME, PEN20_GOTTSUMON_NAME_LEN, PEN20_GOTTSUMON_ID, PEN20_GOTTSUMON_ID_LEN, PEN20_GOTTSUMON_FQID, PEN20_GOTTSUMON_FQID_LEN, PEN20_GOTTSUMON_FQNAME, PEN20_GOTTSUMON_FQNAME_LEN },
        { PEN20_GOTTSUMON_NAME, PEN20_GOTTSUMON_NAME_LEN, PEN20_GOTTSUMON_ID, PEN20_GOTTSUMON_ID_LEN, ALT_PEN20_GOTTSUMON_FQID, ALT_PEN20_GOTTSUMON_FQID_LEN, ALT_PEN20_GOTTSUMON_FQNAME, ALT_PEN20_GOTTSUMON_FQNAME_LEN },
        { PEN20_GREYMON_NAME, PEN20_GREYMON_NAME_LEN, PEN20_GREYMON_ID, PEN20_GREYMON_ID_LEN, PEN20_GREYMON_FQID, PEN20_GREYMON_FQID_LEN, PEN20_GREYMON_FQNAME, PEN20_GREYMON_FQNAME_LEN },
        { PEN20_GREYMON_NAME, PEN20_GREYMON_NAME_LEN, PEN20_GREYMON_ID, PEN20_GREYMON_ID_LEN, ALT_PEN20_GREYMON_FQID, ALT_PEN20_GREYMON_FQID_LEN, ALT_PEN20_GREYMON_FQNAME, ALT_PEN20_GREYMON_FQNAME_LEN },
        { PEN20_GRIFFOMON_NAME, PEN20_GRIFFOMON_NAME_LEN, PEN20_GRIFFOMON_ID, PEN20_GRIFFOMON_ID_LEN, PEN20_GRIFFOMON_FQID, PEN20_GRIFFOMON_FQID_LEN, PEN20_GRIFFOMON_FQNAME, PEN20_GRIFFOMON_FQNAME_LEN },
        { PEN20_GRIFFOMON_NAME, PEN20_GRIFFOMON_NAME_LEN, PEN20_GRIFFOMON_ID, PEN20_GRIFFOMON_ID_LEN, ALT_PEN20_GRIFFOMON_FQID, ALT_PEN20_GRIFFOMON_FQID_LEN, ALT_PEN20_GRIFFOMON_FQNAME, ALT_PEN20_GRIFFOMON_FQNAME_LEN },
        { PEN20_GROUNDRAMON_NAME, PEN20_GROUNDRAMON_NAME_LEN, PEN20_GROUNDRAMON_ID, PEN20_GROUNDRAMON_ID_LEN, PEN20_GROUNDRAMON_FQID, PEN20_GROUNDRAMON_FQID_LEN, PEN20_GROUNDRAMON_FQNAME, PEN20_GROUNDRAMON_FQNAME_LEN },
        { PEN20_GROUNDRAMON_NAME, PEN20_GROUNDRAMON_NAME_LEN, PEN20_GROUNDRAMON_ID, PEN20_GROUNDRAMON_ID_LEN, ALT_PEN20_GROUNDRAMON_FQID, ALT_PEN20_GROUNDRAMON_FQID_LEN, ALT_PEN20_GROUNDRAMON_FQNAME, ALT_PEN20_GROUNDRAMON_FQNAME_LEN },
        { PEN20_GROWMON_NAME, PEN20_GROWMON_NAME_LEN, PEN20_GROWMON_ID, PEN20_GROWMON_ID_LEN, PEN20_GROWMON_FQID, PEN20_GROWMON_FQID_LEN, PEN20_GROWMON_FQNAME, PEN20_GROWMON_FQNAME_LEN },
        { PEN20_GROWMON_NAME, PEN20_GROWMON_NAME_LEN, PEN20_GROWMON_ID, PEN20_GROWMON_ID_LEN, ALT_PEN20_GROWMON_FQID, ALT_PEN20_GROWMON_FQID_LEN, ALT_PEN20_GROWMON_FQNAME, ALT_PEN20_GROWMON_FQNAME_LEN },
        { PEN20_GUARDROMON_NAME, PEN20_GUARDROMON_NAME_LEN, PEN20_GUARDROMON_ID, PEN20_GUARDROMON_ID_LEN, PEN20_GUARDROMON_FQID, PEN20_GUARDROMON_FQID_LEN, PEN20_GUARDROMON_FQNAME, PEN20_GUARDROMON_FQNAME_LEN },
        { PEN20_GUARDROMON_NAME, PEN20_GUARDROMON_NAME_LEN, PEN20_GUARDROMON_ID, PEN20_GUARDROMON_ID_LEN, ALT_PEN20_GUARDROMON_FQID, ALT_PEN20_GUARDROMON_FQID_LEN, ALT_PEN20_GUARDROMON_FQNAME, ALT_PEN20_GUARDROMON_FQNAME_LEN },
        { PEN20_GUILMON_NAME, PEN20_GUILMON_NAME_LEN, PEN20_GUILMON_ID, PEN20_GUILMON_ID_LEN, PEN20_GUILMON_FQID, PEN20_GUILMON_FQID_LEN, PEN20_GUILMON_FQNAME, PEN20_GUILMON_FQNAME_LEN },
        { PEN20_GUILMON_NAME, PEN20_GUILMON_NAME_LEN, PEN20_GUILMON_ID, PEN20_GUILMON_ID_LEN, ALT_PEN20_GUILMON_FQID, ALT_PEN20_GUILMON_FQID_LEN, ALT_PEN20_GUILMON_FQNAME, ALT_PEN20_GUILMON_FQNAME_LEN },
        { PEN20_GUMMYMON_NAME, PEN20_GUMMYMON_NAME_LEN, PEN20_GUMMYMON_ID, PEN20_GUMMYMON_ID_LEN, PEN20_GUMMYMON_FQID, PEN20_GUMMYMON_FQID_LEN, PEN20_GUMMYMON_FQNAME, PEN20_GUMMYMON_FQNAME_LEN },
        { PEN20_GUMMYMON_NAME, PEN20_GUMMYMON_NAME_LEN, PEN20_GUMMYMON_ID, PEN20_GUMMYMON_ID_LEN, ALT_PEN20_GUMMYMON_FQID, ALT_PEN20_GUMMYMON_FQID_LEN, ALT_PEN20_GUMMYMON_FQNAME, ALT_PEN20_GUMMYMON_FQNAME_LEN },
        { PEN20_HACKMON_NAME, PEN20_HACKMON_NAME_LEN, PEN20_HACKMON_ID, PEN20_HACKMON_ID_LEN, PEN20_HACKMON_FQID, PEN20_HACKMON_FQID_LEN, PEN20_HACKMON_FQNAME, PEN20_HACKMON_FQNAME_LEN },
        { PEN20_HACKMON_NAME, PEN20_HACKMON_NAME_LEN, PEN20_HACKMON_ID, PEN20_HACKMON_ID_LEN, ALT_PEN20_HACKMON_FQID, ALT_PEN20_HACKMON_FQID_LEN, ALT_PEN20_HACKMON_FQNAME, ALT_PEN20_HACKMON_FQNAME_LEN },
        { PEN20_HAGURUMON_NAME, PEN20_HAGURUMON_NAME_LEN, PEN20_HAGURUMON_ID, PEN20_HAGURUMON_ID_LEN, PEN20_HAGURUMON_FQID, PEN20_HAGURUMON_FQID_LEN, PEN20_HAGURUMON_FQNAME, PEN20_HAGURUMON_FQNAME_LEN },
        { PEN20_HAGURUMON_NAME, PEN20_HAGURUMON_NAME_LEN, PEN20_HAGURUMON_ID, PEN20_HAGURUMON_ID_LEN, ALT_PEN20_HAGURUMON_FQID, ALT_PEN20_HAGURUMON_FQID_LEN, ALT_PEN20_HAGURUMON_FQNAME, ALT_PEN20_HAGURUMON_FQNAME_LEN },
        { PEN20_HANGYOMON_NAME, PEN20_HANGYOMON_NAME_LEN, PEN20_HANGYOMON_ID, PEN20_HANGYOMON_ID_LEN, PEN20_HANGYOMON_FQID, PEN20_HANGYOMON_FQID_LEN, PEN20_HANGYOMON_FQNAME, PEN20_HANGYOMON_FQNAME_LEN },
        { PEN20_HANGYOMON_NAME, PEN20_HANGYOMON_NAME_LEN, PEN20_HANGYOMON_ID, PEN20_HANGYOMON_ID_LEN, ALT_PEN20_HANGYOMON_FQID, ALT_PEN20_HANGYOMON_FQID_LEN, ALT_PEN20_HANGYOMON_FQNAME, ALT_PEN20_HANGYOMON_FQNAME_LEN },
        { PEN20_HANUMON_NAME, PEN20_HANUMON_NAME_LEN, PEN20_HANUMON_ID, PEN20_HANUMON_ID_LEN, PEN20_HANUMON_FQID, PEN20_HANUMON_FQID_LEN, PEN20_HANUMON_FQNAME, PEN20_HANUMON_FQNAME_LEN },
        { PEN20_HANUMON_NAME, PEN20_HANUMON_NAME_LEN, PEN20_HANUMON_ID, PEN20_HANUMON_ID_LEN, ALT_PEN20_HANUMON_FQID, ALT_PEN20_HANUMON_FQID_LEN, ALT_PEN20_HANUMON_FQNAME, ALT_PEN20_HANUMON_FQNAME_LEN },
        { PEN20_HERAKLE_KABUTERIMON_NAME, PEN20_HERAKLE_KABUTERIMON_NAME_LEN, PEN20_HERAKLE_KABUTERIMON_ID, PEN20_HERAKLE_KABUTERIMON_ID_LEN, PEN20_HERAKLE_KABUTERIMON_FQID, PEN20_HERAKLE_KABUTERIMON_FQID_LEN, PEN20_HERAKLE_KABUTERIMON_FQNAME, PEN20_HERAKLE_KABUTERIMON_FQNAME_LEN },
        { PEN20_HERAKLE_KABUTERIMON_NAME, PEN20_HERAKLE_KABUTERIMON_NAME_LEN, PEN20_HERAKLE_KABUTERIMON_ID, PEN20_HERAKLE_KABUTERIMON_ID_LEN, ALT_PEN20_HERAKLE_KABUTERIMON_FQID, ALT_PEN20_HERAKLE_KABUTERIMON_FQID_LEN, ALT_PEN20_HERAKLE_KABUTERIMON_FQNAME, ALT_PEN20_HERAKLE_KABUTERIMON_FQNAME_LEN },
        { PEN20_HISYARYUMON_NAME, PEN20_HISYARYUMON_NAME_LEN, PEN20_HISYARYUMON_ID, PEN20_HISYARYUMON_ID_LEN, PEN20_HISYARYUMON_FQID, PEN20_HISYARYUMON_FQID_LEN, PEN20_HISYARYUMON_FQNAME, PEN20_HISYARYUMON_FQNAME_LEN },
        { PEN20_HISYARYUMON_NAME, PEN20_HISYARYUMON_NAME_LEN, PEN20_HISYARYUMON_ID, PEN20_HISYARYUMON_ID_LEN, ALT_PEN20_HISYARYUMON_FQID, ALT_PEN20_HISYARYUMON_FQID_LEN, ALT_PEN20_HISYARYUMON_FQNAME, ALT_PEN20_HISYARYUMON_FQNAME_LEN },
        { PEN20_HOLY_ANGEMON_NAME, PEN20_HOLY_ANGEMON_NAME_LEN, PEN20_HOLY_ANGEMON_ID, PEN20_HOLY_ANGEMON_ID_LEN, PEN20_HOLY_ANGEMON_FQID, PEN20_HOLY_ANGEMON_FQID_LEN, PEN20_HOLY_ANGEMON_FQNAME, PEN20_HOLY_ANGEMON_FQNAME_LEN },
        { PEN20_HOLY_ANGEMON_NAME, PEN20_HOLY_ANGEMON_NAME_LEN, PEN20_HOLY_ANGEMON_ID, PEN20_HOLY_ANGEMON_ID_LEN, ALT_PEN20_HOLY_ANGEMON_FQID, ALT_PEN20_HOLY_ANGEMON_FQID_LEN, ALT_PEN20_HOLY_ANGEMON_FQNAME, ALT_PEN20_HOLY_ANGEMON_FQNAME_LEN },
        { PEN20_HOLYDRAMON_NAME, PEN20_HOLYDRAMON_NAME_LEN, PEN20_HOLYDRAMON_ID, PEN20_HOLYDRAMON_ID_LEN, PEN20_HOLYDRAMON_FQID, PEN20_HOLYDRAMON_FQID_LEN, PEN20_HOLYDRAMON_FQNAME, PEN20_HOLYDRAMON_FQNAME_LEN },
        { PEN20_HOLYDRAMON_NAME, PEN20_HOLYDRAMON_NAME_LEN, PEN20_HOLYDRAMON_ID, PEN20_HOLYDRAMON_ID_LEN, ALT_PEN20_HOLYDRAMON_FQID, ALT_PEN20_HOLYDRAMON_FQID_LEN, ALT_PEN20_HOLYDRAMON_FQNAME, ALT_PEN20_HOLYDRAMON_FQNAME_LEN },
        { PEN20_HOUOUMON_NAME, PEN20_HOUOUMON_NAME_LEN, PEN20_HOUOUMON_ID, PEN20_HOUOUMON_ID_LEN, PEN20_HOUOUMON_FQID, PEN20_HOUOUMON_FQID_LEN, PEN20_HOUOUMON_FQNAME, PEN20_HOUOUMON_FQNAME_LEN },
        { PEN20_HOUOUMON_NAME, PEN20_HOUOUMON_NAME_LEN, PEN20_HOUOUMON_ID, PEN20_HOUOUMON_ID_LEN, ALT_PEN20_HOUOUMON_FQID, ALT_PEN20_HOUOUMON_FQID_LEN, ALT_PEN20_HOUOUMON_FQNAME, ALT_PEN20_HOUOUMON_FQNAME_LEN },
        { PEN20_IGAMON_NAME, PEN20_IGAMON_NAME_LEN, PEN20_IGAMON_ID, PEN20_IGAMON_ID_LEN, PEN20_IGAMON_FQID, PEN20_IGAMON_FQID_LEN, PEN20_IGAMON_FQNAME, PEN20_IGAMON_FQNAME_LEN },
        { PEN20_IGAMON_NAME, PEN20_IGAMON_NAME_LEN, PEN20_IGAMON_ID, PEN20_IGAMON_ID_LEN, ALT_PEN20_IGAMON_FQID, ALT_PEN20_IGAMON_FQID_LEN, ALT_PEN20_IGAMON_FQNAME, ALT_PEN20_IGAMON_FQNAME_LEN },
        { PEN20_IKKAKUMON_NAME, PEN20_IKKAKUMON_NAME_LEN, PEN20_IKKAKUMON_ID, PEN20_IKKAKUMON_ID_LEN, PEN20_IKKAKUMON_FQID, PEN20_IKKAKUMON_FQID_LEN, PEN20_IKKAKUMON_FQNAME, PEN20_IKKAKUMON_FQNAME_LEN },
        { PEN20_IKKAKUMON_NAME, PEN20_IKKAKUMON_NAME_LEN, PEN20_IKKAKUMON_ID, PEN20_IKKAKUMON_ID_LEN, ALT_PEN20_IKKAKUMON_FQID, ALT_PEN20_IKKAKUMON_FQID_LEN, ALT_PEN20_IKKAKUMON_FQNAME, ALT_PEN20_IKKAKUMON_FQNAME_LEN },
        { PEN20_IMPERIALDRAMON_FIGHTER_MODE_NAME, PEN20_IMPERIALDRAMON_FIGHTER_MODE_NAME_LEN, PEN20_IMPERIALDRAMON_FIGHTER_MODE_ID, PEN20_IMPERIALDRAMON_FIGHTER_MODE_ID_LEN, PEN20_IMPERIALDRAMON_FIGHTER_MODE_FQID, PEN20_IMPERIALDRAMON_FIGHTER_MODE_FQID_LEN, PEN20_IMPERIALDRAMON_FIGHTER_MODE_FQNAME, PEN20_IMPERIALDRAMON_FIGHTER_MODE_FQNAME_LEN },
        { PEN20_IMPERIALDRAMON_FIGHTER_MODE_NAME, PEN20_IMPERIALDRAMON_FIGHTER_MODE_NAME_LEN, PEN20_IMPERIALDRAMON_FIGHTER_MODE_ID, PEN20_IMPERIALDRAMON_FIGHTER_MODE_ID_LEN, ALT_PEN20_IMPERIALDRAMON_FIGHTER_MODE_FQID, ALT_PEN20_IMPERIALDRAMON_FIGHTER_MODE_FQID_LEN, ALT_PEN20_IMPERIALDRAMON_FIGHTER_MODE_FQNAME, ALT_PEN20_IMPERIALDRAMON_FIGHTER_MODE_FQNAME_LEN },
        { PEN20_IMPMON_NAME, PEN20_IMPMON_NAME_LEN, PEN20_IMPMON_ID, PEN20_IMPMON_ID_LEN, PEN20_IMPMON_FQID, PEN20_IMPMON_FQID_LEN, PEN20_IMPMON_FQNAME, PEN20_IMPMON_FQNAME_LEN },
        { PEN20_IMPMON_NAME, PEN20_IMPMON_NAME_LEN, PEN20_IMPMON_ID, PEN20_IMPMON_ID_LEN, ALT_PEN20_IMPMON_FQID, ALT_PEN20_IMPMON_FQID_LEN, ALT_PEN20_IMPMON_FQNAME, ALT_PEN20_IMPMON_FQNAME_LEN },
        { PEN20_JESMON_NAME, PEN20_JESMON_NAME_LEN, PEN20_JESMON_ID, PEN20_JESMON_ID_LEN, PEN20_JESMON_FQID, PEN20_JESMON_FQID_LEN, PEN20_JESMON_FQNAME, PEN20_JESMON_FQNAME_LEN },
        { PEN20_JESMON_NAME, PEN20_JESMON_NAME_LEN, PEN20_JESMON_ID, PEN20_JESMON_ID_LEN, ALT_PEN20_JESMON_FQID, ALT_PEN20_JESMON_FQID_LEN, ALT_PEN20_JESMON_FQNAME, ALT_PEN20_JESMON_FQNAME_LEN },
        { PEN20_JESMON_X_NAME, PEN20_JESMON_X_NAME_LEN, PEN20_JESMON_X_ID, PEN20_JESMON_X_ID_LEN, PEN20_JESMON_X_FQID, PEN20_JESMON_X_FQID_LEN, PEN20_JESMON_X_FQNAME, PEN20_JESMON_X_FQNAME_LEN },
        { PEN20_JESMON_X_NAME, PEN20_JESMON_X_NAME_LEN, PEN20_JESMON_X_ID, PEN20_JESMON_X_ID_LEN, ALT_PEN20_JESMON_X_FQID, ALT_PEN20_JESMON_X_FQID_LEN, ALT_PEN20_JESMON_X_FQNAME, ALT_PEN20_JESMON_X_FQNAME_LEN },
        { PEN20_JYAGAMON_NAME, PEN20_JYAGAMON_NAME_LEN, PEN20_JYAGAMON_ID, PEN20_JYAGAMON_ID_LEN, PEN20_JYAGAMON_FQID, PEN20_JYAGAMON_FQID_LEN, PEN20_JYAGAMON_FQNAME, PEN20_JYAGAMON_FQNAME_LEN },
        { PEN20_JYAGAMON_NAME, PEN20_JYAGAMON_NAME_LEN, PEN20_JYAGAMON_ID, PEN20_JYAGAMON_ID_LEN, ALT_PEN20_JYAGAMON_FQID, ALT_PEN20_JYAGAMON_FQID_LEN, ALT_PEN20_JYAGAMON_FQNAME, ALT_PEN20_JYAGAMON_FQNAME_LEN },
        { PEN20_JYUREIMON_NAME, PEN20_JYUREIMON_NAME_LEN, PEN20_JYUREIMON_ID, PEN20_JYUREIMON_ID_LEN, PEN20_JYUREIMON_FQID, PEN20_JYUREIMON_FQID_LEN, PEN20_JYUREIMON_FQNAME, PEN20_JYUREIMON_FQNAME_LEN },
        { PEN20_JYUREIMON_NAME, PEN20_JYUREIMON_NAME_LEN, PEN20_JYUREIMON_ID, PEN20_JYUREIMON_ID_LEN, ALT_PEN20_JYUREIMON_FQID, ALT_PEN20_JYUREIMON_FQID_LEN, ALT_PEN20_JYUREIMON_FQNAME, ALT_PEN20_JYUREIMON_FQNAME_LEN },
        { PEN20_KABUTERIMON_NAME, PEN20_KABUTERIMON_NAME_LEN, PEN20_KABUTERIMON_ID, PEN20_KABUTERIMON_ID_LEN, PEN20_KABUTERIMON_FQID, PEN20_KABUTERIMON_FQID_LEN, PEN20_KABUTERIMON_FQNAME, PEN20_KABUTERIMON_FQNAME_LEN },
        { PEN20_KABUTERIMON_NAME, PEN20_KABUTERIMON_NAME_LEN, PEN20_KABUTERIMON_ID, PEN20_KABUTERIMON_ID_LEN, ALT_PEN20_KABUTERIMON_FQID, ALT_PEN20_KABUTERIMON_FQID_LEN, ALT_PEN20_KABUTERIMON_FQNAME, ALT_PEN20_KABUTERIMON_FQNAME_LEN },
        { PEN20_KAKKINMON_NAME, PEN20_KAKKINMON_NAME_LEN, PEN20_KAKKINMON_ID, PEN20_KAKKINMON_ID_LEN, PEN20_KAKKINMON_FQID, PEN20_KAKKINMON_FQID_LEN, PEN20_KAKKINMON_FQNAME, PEN20_KAKKINMON_FQNAME_LEN },
        { PEN20_KAKKINMON_NAME, PEN20_KAKKINMON_NAME_LEN, PEN20_KAKKINMON_ID, PEN20_KAKKINMON_ID_LEN, ALT_PEN20_KAKKINMON_FQID, ALT_PEN20_KAKKINMON_FQID_LEN, ALT_PEN20_KAKKINMON_FQNAME, ALT_PEN20_KAKKINMON_FQNAME_LEN },
        { PEN20_KIWIMON_NAME, PEN20_KIWIMON_NAME_LEN, PEN20_KIWIMON_ID, PEN20_KIWIMON_ID_LEN, PEN20_KIWIMON_FQID, PEN20_KIWIMON_FQID_LEN, PEN20_KIWIMON_FQNAME, PEN20_KIWIMON_FQNAME_LEN },
        { PEN20_KIWIMON_NAME, PEN20_KIWIMON_NAME_LEN, PEN20_KIWIMON_ID, PEN20_KIWIMON_ID_LEN, ALT_PEN20_KIWIMON_FQID, ALT_PEN20_KIWIMON_FQID_LEN, ALT_PEN20_KIWIMON_FQNAME, ALT_PEN20_KIWIMON_FQNAME_LEN },
        { PEN20_KNIGHTMON_NAME, PEN20_KNIGHTMON_NAME_LEN, PEN20_KNIGHTMON_ID, PEN20_KNIGHTMON_ID_LEN, PEN20_KNIGHTMON_FQID, PEN20_KNIGHTMON_FQID_LEN, PEN20_KNIGHTMON_FQNAME, PEN20_KNIGHTMON_FQNAME_LEN },
        { PEN20_KNIGHTMON_NAME, PEN20_KNIGHTMON_NAME_LEN, PEN20_KNIGHTMON_ID, PEN20_KNIGHTMON_ID_LEN, ALT_PEN20_KNIGHTMON_FQID, ALT_PEN20_KNIGHTMON_FQID_LEN, ALT_PEN20_KNIGHTMON_FQNAME, ALT_PEN20_KNIGHTMON_FQNAME_LEN },
        { PEN20_KOKUWAMON_NAME, PEN20_KOKUWAMON_NAME_LEN, PEN20_KOKUWAMON_ID, PEN20_KOKUWAMON_ID_LEN, PEN20_KOKUWAMON_FQID, PEN20_KOKUWAMON_FQID_LEN, PEN20_KOKUWAMON_FQNAME, PEN20_KOKUWAMON_FQNAME_LEN },
        { PEN20_KOKUWAMON_NAME, PEN20_KOKUWAMON_NAME_LEN, PEN20_KOKUWAMON_ID, PEN20_KOKUWAMON_ID_LEN, ALT_PEN20_KOKUWAMON_FQID, ALT_PEN20_KOKUWAMON_FQID_LEN, ALT_PEN20_KOKUWAMON_FQNAME, ALT_PEN20_KOKUWAMON_FQNAME_LEN },
        { PEN20_KOROMON_NAME, PEN20_KOROMON_NAME_LEN, PEN20_KOROMON_ID, PEN20_KOROMON_ID_LEN, PEN20_KOROMON_FQID, PEN20_KOROMON_FQID_LEN, PEN20_KOROMON_FQNAME, PEN20_KOROMON_FQNAME_LEN },
        { PEN20_KOROMON_NAME, PEN20_KOROMON_NAME_LEN, PEN20_KOROMON_ID, PEN20_KOROMON_ID_LEN, ALT_PEN20_KOROMON_FQID, ALT_PEN20_KOROMON_FQID_LEN, ALT_PEN20_KOROMON_FQNAME, ALT_PEN20_KOROMON_FQNAME_LEN },
        { PEN20_KUWAGAMON_NAME, PEN20_KUWAGAMON_NAME_LEN, PEN20_KUWAGAMON_ID, PEN20_KUWAGAMON_ID_LEN, PEN20_KUWAGAMON_FQID, PEN20_KUWAGAMON_FQID_LEN, PEN20_KUWAGAMON_FQNAME, PEN20_KUWAGAMON_FQNAME_LEN },
        { PEN20_KUWAGAMON_NAME, PEN20_KUWAGAMON_NAME_LEN, PEN20_KUWAGAMON_ID, PEN20_KUWAGAMON_ID_LEN, ALT_PEN20_KUWAGAMON_FQID, ALT_PEN20_KUWAGAMON_FQID_LEN, ALT_PEN20_KUWAGAMON_FQNAME, ALT_PEN20_KUWAGAMON_FQNAME_LEN },
        { PEN20_KYOKYOMON_NAME, PEN20_KYOKYOMON_NAME_LEN, PEN20_KYOKYOMON_ID, PEN20_KYOKYOMON_ID_LEN, PEN20_KYOKYOMON_FQID, PEN20_KYOKYOMON_FQID_LEN, PEN20_KYOKYOMON_FQNAME, PEN20_KYOKYOMON_FQNAME_LEN },
        { PEN20_KYOKYOMON_NAME, PEN20_KYOKYOMON_NAME_LEN, PEN20_KYOKYOMON_ID, PEN20_KYOKYOMON_ID_LEN, ALT_PEN20_KYOKYOMON_FQID, ALT_PEN20_KYOKYOMON_FQID_LEN, ALT_PEN20_KYOKYOMON_FQNAME, ALT_PEN20_KYOKYOMON_FQNAME_LEN },
        { PEN20_LADY_DEVIMON_NAME, PEN20_LADY_DEVIMON_NAME_LEN, PEN20_LADY_DEVIMON_ID, PEN20_LADY_DEVIMON_ID_LEN, PEN20_LADY_DEVIMON_FQID, PEN20_LADY_DEVIMON_FQID_LEN, PEN20_LADY_DEVIMON_FQNAME, PEN20_LADY_DEVIMON_FQNAME_LEN },
        { PEN20_LADY_DEVIMON_NAME, PEN20_LADY_DEVIMON_NAME_LEN, PEN20_LADY_DEVIMON_ID, PEN20_LADY_DEVIMON_ID_LEN, ALT_PEN20_LADY_DEVIMON_FQID, ALT_PEN20_LADY_DEVIMON_FQID_LEN, ALT_PEN20_LADY_DEVIMON_FQNAME, ALT_PEN20_LADY_DEVIMON_FQNAME_LEN },
        { PEN20_LALAMON_NAME, PEN20_LALAMON_NAME_LEN, PEN20_LALAMON_ID, PEN20_LALAMON_ID_LEN, PEN20_LALAMON_FQID, PEN20_LALAMON_FQID_LEN, PEN20_LALAMON_FQNAME, PEN20_LALAMON_FQNAME_LEN },
        { PEN20_LALAMON_NAME, PEN20_LALAMON_NAME_LEN, PEN20_LALAMON_ID, PEN20_LALAMON_ID_LEN, ALT_PEN20_LALAMON_FQID, ALT_PEN20_LALAMON_FQID_LEN, ALT_PEN20_LALAMON_FQNAME, ALT_PEN20_LALAMON_FQNAME_LEN },
        { PEN20_LAVOGARITAMON_NAME, PEN20_LAVOGARITAMON_NAME_LEN, PEN20_LAVOGARITAMON_ID, PEN20_LAVOGARITAMON_ID_LEN, PEN20_LAVOGARITAMON_FQID, PEN20_LAVOGARITAMON_FQID_LEN, PEN20_LAVOGARITAMON_FQNAME, PEN20_LAVOGARITAMON_FQNAME_LEN },
        { PEN20_LAVOGARITAMON_NAME, PEN20_LAVOGARITAMON_NAME_LEN, PEN20_LAVOGARITAMON_ID, PEN20_LAVOGARITAMON_ID_LEN, ALT_PEN20_LAVOGARITAMON_FQID, ALT_PEN20_LAVOGARITAMON_FQID_LEN, ALT_PEN20_LAVOGARITAMON_FQNAME, ALT_PEN20_LAVOGARITAMON_FQNAME_LEN },
        { PEN20_LAVORVOMON_NAME, PEN20_LAVORVOMON_NAME_LEN, PEN20_LAVORVOMON_ID, PEN20_LAVORVOMON_ID_LEN, PEN20_LAVORVOMON_FQID, PEN20_LAVORVOMON_FQID_LEN, PEN20_LAVORVOMON_FQNAME, PEN20_LAVORVOMON_FQNAME_LEN },
        { PEN20_LAVORVOMON_NAME, PEN20_LAVORVOMON_NAME_LEN, PEN20_LAVORVOMON_ID, PEN20_LAVORVOMON_ID_LEN, ALT_PEN20_LAVORVOMON_FQID, ALT_PEN20_LAVORVOMON_FQID_LEN, ALT_PEN20_LAVORVOMON_FQNAME, ALT_PEN20_LAVORVOMON_FQNAME_LEN },
        { PEN20_LEOMON_NAME, PEN20_LEOMON_NAME_LEN, PEN20_LEOMON_ID, PEN20_LEOMON_ID_LEN, PEN20_LEOMON_FQID, PEN20_LEOMON_FQID_LEN, PEN20_LEOMON_FQNAME, PEN20_LEOMON_FQNAME_LEN },
        { PEN20_LEOMON_NAME, PEN20_LEOMON_NAME_LEN, PEN20_LEOMON_ID, PEN20_LEOMON_ID_LEN, ALT_PEN20_LEOMON_FQID, ALT_PEN20_LEOMON_FQID_LEN, ALT_PEN20_LEOMON_FQNAME, ALT_PEN20_LEOMON_FQNAME_LEN },
        { PEN20_LILAMON_NAME, PEN20_LILAMON_NAME_LEN, PEN20_LILAMON_ID, PEN20_LILAMON_ID_LEN, PEN20_LILAMON_FQID, PEN20_LILAMON_FQID_LEN, PEN20_LILAMON_FQNAME, PEN20_LILAMON_FQNAME_LEN },
        { PEN20_LILAMON_NAME, PEN20_LILAMON_NAME_LEN, PEN20_LILAMON_ID, PEN20_LILAMON_ID_LEN, ALT_PEN20_LILAMON_FQID, ALT_PEN20_LILAMON_FQID_LEN, ALT_PEN20_LILAMON_FQNAME, ALT_PEN20_LILAMON_FQNAME_LEN },
        { PEN20_LILIMON_NAME, PEN20_LILIMON_NAME_LEN, PEN20_LILIMON_ID, PEN20_LILIMON_ID_LEN, PEN20_LILIMON_FQID, PEN20_LILIMON_FQID_LEN, PEN20_LILIMON_FQNAME, PEN20_LILIMON_FQNAME_LEN },
        { PEN20_LILIMON_NAME, PEN20_LILIMON_NAME_LEN, PEN20_LILIMON_ID, PEN20_LILIMON_ID_LEN, ALT_PEN20_LILIMON_FQID, ALT_PEN20_LILIMON_FQID_LEN, ALT_PEN20_LILIMON_FQNAME, ALT_PEN20_LILIMON_FQNAME_LEN },
        { PEN20_LOPMON_NAME, PEN20_LOPMON_NAME_LEN, PEN20_LOPMON_ID, PEN20_LOPMON_ID_LEN, PEN20_LOPMON_FQID, PEN20_LOPMON_FQID_LEN, PEN20_LOPMON_FQNAME, PEN20_LOPMON_FQNAME_LEN },
        { PEN20_LOPMON_NAME, PEN20_LOPMON_NAME_LEN, PEN20_LOPMON_ID, PEN20_LOPMON_ID_LEN, ALT_PEN20_LOPMON_FQID, ALT_PEN20_LOPMON_FQID_LEN, ALT_PEN20_LOPMON_FQNAME, ALT_PEN20_LOPMON_FQNAME_LEN },
        { PEN20_LOTUSMON_NAME, PEN20_LOTUSMON_NAME_LEN, PEN20_LOTUSMON_ID, PEN20_LOTUSMON_ID_LEN, PEN20_LOTUSMON_FQID, PEN20_LOTUSMON_FQID_LEN, PEN20_LOTUSMON_FQNAME, PEN20_LOTUSMON_FQNAME_LEN },
        { PEN20_LOTUSMON_NAME, PEN20_LOTUSMON_NAME_LEN, PEN20_LOTUSMON_ID, PEN20_LOTUSMON_ID_LEN, ALT_PEN20_LOTUSMON_FQID, ALT_PEN20_LOTUSMON_FQID_LEN, ALT_PEN20_LOTUSMON_FQNAME, ALT_PEN20_LOTUSMON_FQNAME_LEN },
        { PEN20_LUDOMON_NAME, PEN20_LUDOMON_NAME_LEN, PEN20_LUDOMON_ID, PEN20_LUDOMON_ID_LEN, PEN20_LUDOMON_FQID, PEN20_LUDOMON_FQID_LEN, PEN20_LUDOMON_FQNAME, PEN20_LUDOMON_FQNAME_LEN },
        { PEN20_LUDOMON_NAME, PEN20_LUDOMON_NAME_LEN, PEN20_LUDOMON_ID, PEN20_LUDOMON_ID_LEN, ALT_PEN20_LUDOMON_FQID, ALT_PEN20_LUDOMON_FQID_LEN, ALT_PEN20_LUDOMON_FQNAME, ALT_PEN20_LUDOMON_FQNAME_LEN },
        { PEN20_MAD_LEOMON_NAME, PEN20_MAD_LEOMON_NAME_LEN, PEN20_MAD_LEOMON_ID, PEN20_MAD_LEOMON_ID_LEN, PEN20_MAD_LEOMON_FQID, PEN20_MAD_LEOMON_FQID_LEN, PEN20_MAD_LEOMON_FQNAME, PEN20_MAD_LEOMON_FQNAME_LEN },
        { PEN20_MAD_LEOMON_NAME, PEN20_MAD_LEOMON_NAME_LEN, PEN20_MAD_LEOMON_ID, PEN20_MAD_LEOMON_ID_LEN, ALT_PEN20_MAD_LEOMON_FQID, ALT_PEN20_MAD_LEOMON_FQID_LEN, ALT_PEN20_MAD_LEOMON_FQNAME, ALT_PEN20_MAD_LEOMON_FQNAME_LEN },
        { PEN20_MAMMON_NAME, PEN20_MAMMON_NAME_LEN, PEN20_MAMMON_ID, PEN20_MAMMON_ID_LEN, PEN20_MAMMON_FQID, PEN20_MAMMON_FQID_LEN, PEN20_MAMMON_FQNAME, PEN20_MAMMON_FQNAME_LEN },
        { PEN20_MAMMON_NAME, PEN20_MAMMON_NAME_LEN, PEN20_MAMMON_ID, PEN20_MAMMON_ID_LEN, ALT_PEN20_MAMMON_FQID, ALT_PEN20_MAMMON_FQID_LEN, ALT_PEN20_MAMMON_FQNAME, ALT_PEN20_MAMMON_FQNAME_LEN },
        { PEN20_MANBOMON_NAME, PEN20_MANBOMON_NAME_LEN, PEN20_MANBOMON_ID, PEN20_MANBOMON_ID_LEN, PEN20_MANBOMON_FQID, PEN20_MANBOMON_FQID_LEN, PEN20_MANBOMON_FQNAME, PEN20_MANBOMON_FQNAME_LEN },
        { PEN20_MANBOMON_NAME, PEN20_MANBOMON_NAME_LEN, PEN20_MANBOMON_ID, PEN20_MANBOMON_ID_LEN, ALT_PEN20_MANBOMON_FQID, ALT_PEN20_MANBOMON_FQID_LEN, ALT_PEN20_MANBOMON_FQNAME, ALT_PEN20_MANBOMON_FQNAME_LEN },
        { PEN20_MARIN_ANGEMON_NAME, PEN20_MARIN_ANGEMON_NAME_LEN, PEN20_MARIN_ANGEMON_ID, PEN20_MARIN_ANGEMON_ID_LEN, PEN20_MARIN_ANGEMON_FQID, PEN20_MARIN_ANGEMON_FQID_LEN, PEN20_MARIN_ANGEMON_FQNAME, PEN20_MARIN_ANGEMON_FQNAME_LEN },
        { PEN20_MARIN_ANGEMON_NAME, PEN20_MARIN_ANGEMON_NAME_LEN, PEN20_MARIN_ANGEMON_ID, PEN20_MARIN_ANGEMON_ID_LEN, ALT_PEN20_MARIN_ANGEMON_FQID, ALT_PEN20_MARIN_ANGEMON_FQID_LEN, ALT_PEN20_MARIN_ANGEMON_FQNAME, ALT_PEN20_MARIN_ANGEMON_FQNAME_LEN },
        { PEN20_MARIN_DEVIMON_NAME, PEN20_MARIN_DEVIMON_NAME_LEN, PEN20_MARIN_DEVIMON_ID, PEN20_MARIN_DEVIMON_ID_LEN, PEN20_MARIN_DEVIMON_FQID, PEN20_MARIN_DEVIMON_FQID_LEN, PEN20_MARIN_DEVIMON_FQNAME, PEN20_MARIN_DEVIMON_FQNAME_LEN },
        { PEN20_MARIN_DEVIMON_NAME, PEN20_MARIN_DEVIMON_NAME_LEN, PEN20_MARIN_DEVIMON_ID, PEN20_MARIN_DEVIMON_ID_LEN, ALT_PEN20_MARIN_DEVIMON_FQID, ALT_PEN20_MARIN_DEVIMON_FQID_LEN, ALT_PEN20_MARIN_DEVIMON_FQNAME, ALT_PEN20_MARIN_DEVIMON_FQNAME_LEN },
        { PEN20_MASTEMON_NAME, PEN20_MASTEMON_NAME_LEN, PEN20_MASTEMON_ID, PEN20_MASTEMON_ID_LEN, PEN20_MASTEMON_FQID, PEN20_MASTEMON_FQID_LEN, PEN20_MASTEMON_FQNAME, PEN20_MASTEMON_FQNAME_LEN },
        { PEN20_MASTEMON_NAME, PEN20_MASTEMON_NAME_LEN, PEN20_MASTEMON_ID, PEN20_MASTEMON_ID_LEN, ALT_PEN20_MASTEMON_FQID, ALT_PEN20_MASTEMON_FQID_LEN, ALT_PEN20_MASTEMON_FQNAME, ALT_PEN20_MASTEMON_FQNAME_LEN },
        { PEN20_MECHANORIMON_NAME, PEN20_MECHANORIMON_NAME_LEN, PEN20_MECHANORIMON_ID, PEN20_MECHANORIMON_ID_LEN, PEN20_MECHANORIMON_FQID, PEN20_MECHANORIMON_FQID_LEN, PEN20_MECHANORIMON_FQNAME, PEN20_MECHANORIMON_FQNAME_LEN },
        { PEN20_MECHANORIMON_NAME, PEN20_MECHANORIMON_NAME_LEN, PEN20_MECHANORIMON_ID, PEN20_MECHANORIMON_ID_LEN, ALT_PEN20_MECHANORIMON_FQID, ALT_PEN20_MECHANORIMON_FQID_LEN, ALT_PEN20_MECHANORIMON_FQNAME, ALT_PEN20_MECHANORIMON_FQNAME_LEN },
        { PEN20_MEGADRAMON_NAME, PEN20_MEGADRAMON_NAME_LEN, PEN20_MEGADRAMON_ID, PEN20_MEGADRAMON_ID_LEN, PEN20_MEGADRAMON_FQID, PEN20_MEGADRAMON_FQID_LEN, PEN20_MEGADRAMON_FQNAME, PEN20_MEGADRAMON_FQNAME_LEN },
        { PEN20_MEGADRAMON_NAME, PEN20_MEGADRAMON_NAME_LEN, PEN20_MEGADRAMON_ID, PEN20_MEGADRAMON_ID_LEN, ALT_PEN20_MEGADRAMON_FQID, ALT_PEN20_MEGADRAMON_FQID_LEN, ALT_PEN20_MEGADRAMON_FQNAME, ALT_PEN20_MEGADRAMON_FQNAME_LEN },
        { PEN20_MEGALO_GROWMON_NAME, PEN20_MEGALO_GROWMON_NAME_LEN, PEN20_MEGALO_GROWMON_ID, PEN20_MEGALO_GROWMON_ID_LEN, PEN20_MEGALO_GROWMON_FQID, PEN20_MEGALO_GROWMON_FQID_LEN, PEN20_MEGALO_GROWMON_FQNAME, PEN20_MEGALO_GROWMON_FQNAME_LEN },
        { PEN20_MEGALO_GROWMON_NAME, PEN20_MEGALO_GROWMON_NAME_LEN, PEN20_MEGALO_GROWMON_ID, PEN20_MEGALO_GROWMON_ID_LEN, ALT_PEN20_MEGALO_GROWMON_FQID, ALT_PEN20_MEGALO_GROWMON_FQID_LEN, ALT_PEN20_MEGALO_GROWMON_FQNAME, ALT_PEN20_MEGALO_GROWMON_FQNAME_LEN },
        { PEN20_MEGA_SEADRAMON_NAME, PEN20_MEGA_SEADRAMON_NAME_LEN, PEN20_MEGA_SEADRAMON_ID, PEN20_MEGA_SEADRAMON_ID_LEN, PEN20_MEGA_SEADRAMON_FQID, PEN20_MEGA_SEADRAMON_FQID_LEN, PEN20_MEGA_SEADRAMON_FQNAME, PEN20_MEGA_SEADRAMON_FQNAME_LEN },
        { PEN20_MEGA_SEADRAMON_NAME, PEN20_MEGA_SEADRAMON_NAME_LEN, PEN20_MEGA_SEADRAMON_ID, PEN20_MEGA_SEADRAMON_ID_LEN, ALT_PEN20_MEGA_SEADRAMON_FQID, ALT_PEN20_MEGA_SEADRAMON_FQID_LEN, ALT_PEN20_MEGA_SEADRAMON_FQNAME, ALT_PEN20_MEGA_SEADRAMON_FQNAME_LEN },
        { PEN20_MEICOOMON_NAME, PEN20_MEICOOMON_NAME_LEN, PEN20_MEICOOMON_ID, PEN20_MEICOOMON_ID_LEN, PEN20_MEICOOMON_FQID, PEN20_MEICOOMON_FQID_LEN, PEN20_MEICOOMON_FQNAME, PEN20_MEICOOMON_FQNAME_LEN },
        { PEN20_MEICOOMON_NAME, PEN20_MEICOOMON_NAME_LEN, PEN20_MEICOOMON_ID, PEN20_MEICOOMON_ID_LEN, ALT_PEN20_MEICOOMON_FQID, ALT_PEN20_MEICOOMON_FQID_LEN, ALT_PEN20_MEICOOMON_FQNAME, ALT_PEN20_MEICOOMON_FQNAME_LEN },
        { PEN20_MEICRACKMON_VICIOUS_MODE_NAME, PEN20_MEICRACKMON_VICIOUS_MODE_NAME_LEN, PEN20_MEICRACKMON_VICIOUS_MODE_ID, PEN20_MEICRACKMON_VICIOUS_MODE_ID_LEN, PEN20_MEICRACKMON_VICIOUS_MODE_FQID, PEN20_MEICRACKMON_VICIOUS_MODE_FQID_LEN, PEN20_MEICRACKMON_VICIOUS_MODE_FQNAME, PEN20_MEICRACKMON_VICIOUS_MODE_FQNAME_LEN },
        { PEN20_MEICRACKMON_VICIOUS_MODE_NAME, PEN20_MEICRACKMON_VICIOUS_MODE_NAME_LEN, PEN20_MEICRACKMON_VICIOUS_MODE_ID, PEN20_MEICRACKMON_VICIOUS_MODE_ID_LEN, ALT_PEN20_MEICRACKMON_VICIOUS_MODE_FQID, ALT_PEN20_MEICRACKMON_VICIOUS_MODE_FQID_LEN, ALT_PEN20_MEICRACKMON_VICIOUS_MODE_FQNAME, ALT_PEN20_MEICRACKMON_VICIOUS_MODE_FQNAME_LEN },
        { PEN20_MERAMON_NAME, PEN20_MERAMON_NAME_LEN, PEN20_MERAMON_ID, PEN20_MERAMON_ID_LEN, PEN20_MERAMON_FQID, PEN20_MERAMON_FQID_LEN, PEN20_MERAMON_FQNAME, PEN20_MERAMON_FQNAME_LEN },
        { PEN20_MERAMON_NAME, PEN20_MERAMON_NAME_LEN, PEN20_MERAMON_ID, PEN20_MERAMON_ID_LEN, ALT_PEN20_MERAMON_FQID, ALT_PEN20_MERAMON_FQID_LEN, ALT_PEN20_MERAMON_FQNAME, ALT_PEN20_MERAMON_FQNAME_LEN },
        { PEN20_METAL_ETEMON_NAME, PEN20_METAL_ETEMON_NAME_LEN, PEN20_METAL_ETEMON_ID, PEN20_METAL_ETEMON_ID_LEN, PEN20_METAL_ETEMON_FQID, PEN20_METAL_ETEMON_FQID_LEN, PEN20_METAL_ETEMON_FQNAME, PEN20_METAL_ETEMON_FQNAME_LEN },
        { PEN20_METAL_ETEMON_NAME, PEN20_METAL_ETEMON_NAME_LEN, PEN20_METAL_ETEMON_ID, PEN20_METAL_ETEMON_ID_LEN, ALT_PEN20_METAL_ETEMON_FQID, ALT_PEN20_METAL_ETEMON_FQID_LEN, ALT_PEN20_METAL_ETEMON_FQNAME, ALT_PEN20_METAL_ETEMON_FQNAME_LEN },
        { PEN20_METAL_GARURUMON_NAME, PEN20_METAL_GARURUMON_NAME_LEN, PEN20_METAL_GARURUMON_ID, PEN20_METAL_GARURUMON_ID_LEN, PEN20_METAL_GARURUMON_FQID, PEN20_METAL_GARURUMON_FQID_LEN, PEN20_METAL_GARURUMON_FQNAME, PEN20_METAL_GARURUMON_FQNAME_LEN },
        { PEN20_METAL_GARURUMON_NAME, PEN20_METAL_GARURUMON_NAME_LEN, PEN20_METAL_GARURUMON_ID, PEN20_METAL_GARURUMON_ID_LEN, ALT_PEN20_METAL_GARURUMON_FQID, ALT_PEN20_METAL_GARURUMON_FQID_LEN, ALT_PEN20_METAL_GARURUMON_FQNAME, ALT_PEN20_METAL_GARURUMON_FQNAME_LEN },
        { PEN20_METAL_GREYMON_NAME, PEN20_METAL_GREYMON_NAME_LEN, PEN20_METAL_GREYMON_ID, PEN20_METAL_GREYMON_ID_LEN, PEN20_METAL_GREYMON_FQID, PEN20_METAL_GREYMON_FQID_LEN, PEN20_METAL_GREYMON_FQNAME, PEN20_METAL_GREYMON_FQNAME_LEN },
        { PEN20_METAL_GREYMON_NAME, PEN20_METAL_GREYMON_NAME_LEN, PEN20_METAL_GREYMON_ID, PEN20_METAL_GREYMON_ID_LEN, ALT_PEN20_METAL_GREYMON_FQID, ALT_PEN20_METAL_GREYMON_FQID_LEN, ALT_PEN20_METAL_GREYMON_FQNAME, ALT_PEN20_METAL_GREYMON_FQNAME_LEN },
        { PEN20_METAL_MAMEMON_NAME, PEN20_METAL_MAMEMON_NAME_LEN, PEN20_METAL_MAMEMON_ID, PEN20_METAL_MAMEMON_ID_LEN, PEN20_METAL_MAMEMON_FQID, PEN20_METAL_MAMEMON_FQID_LEN, PEN20_METAL_MAMEMON_FQNAME, PEN20_METAL_MAMEMON_FQNAME_LEN },
        { PEN20_METAL_MAMEMON_NAME, PEN20_METAL_MAMEMON_NAME_LEN, PEN20_METAL_MAMEMON_ID, PEN20_METAL_MAMEMON_ID_LEN, ALT_PEN20_METAL_MAMEMON_FQID, ALT_PEN20_METAL_MAMEMON_FQID_LEN, ALT_PEN20_METAL_MAMEMON_FQNAME, ALT_PEN20_METAL_MAMEMON_FQNAME_LEN },
        { PEN20_METAL_SEADRAMON_NAME, PEN20_METAL_SEADRAMON_NAME_LEN, PEN20_METAL_SEADRAMON_ID, PEN20_METAL_SEADRAMON_ID_LEN, PEN20_METAL_SEADRAMON_FQID, PEN20_METAL_SEADRAMON_FQID_LEN, PEN20_METAL_SEADRAMON_FQNAME, PEN20_METAL_SEADRAMON_FQNAME_LEN },
        { PEN20_METAL_SEADRAMON_NAME, PEN20_METAL_SEADRAMON_NAME_LEN, PEN20_METAL_SEADRAMON_ID, PEN20_METAL_SEADRAMON_ID_LEN, ALT_PEN20_METAL_SEADRAMON_FQID, ALT_PEN20_METAL_SEADRAMON_FQID_LEN, ALT_PEN20_METAL_SEADRAMON_FQNAME, ALT_PEN20_METAL_SEADRAMON_FQNAME_LEN },
        { PEN20_MOCHIMON_NAME, PEN20_MOCHIMON_NAME_LEN, PEN20_MOCHIMON_ID, PEN20_MOCHIMON_ID_LEN, PEN20_MOCHIMON_FQID, PEN20_MOCHIMON_FQID_LEN, PEN20_MOCHIMON_FQNAME, PEN20_MOCHIMON_FQNAME_LEN },
        { PEN20_MOCHIMON_NAME, PEN20_MOCHIMON_NAME_LEN, PEN20_MOCHIMON_ID, PEN20_MOCHIMON_ID_LEN, ALT_PEN20_MOCHIMON_FQID, ALT_PEN20_MOCHIMON_FQID_LEN, ALT_PEN20_MOCHIMON_FQNAME, ALT_PEN20_MOCHIMON_FQNAME_LEN },
        { PEN20_MOKUMON_NAME, PEN20_MOKUMON_NAME_LEN, PEN20_MOKUMON_ID, PEN20_MOKUMON_ID_LEN, PEN20_MOKUMON_FQID, PEN20_MOKUMON_FQID_LEN, PEN20_MOKUMON_FQNAME, PEN20_MOKUMON_FQNAME_LEN },
        { PEN20_MOKUMON_NAME, PEN20_MOKUMON_NAME_LEN, PEN20_MOKUMON_ID, PEN20_MOKUMON_ID_LEN, ALT_PEN20_MOKUMON_FQID, ALT_PEN20_MOKUMON_FQID_LEN, ALT_PEN20_MOKUMON_FQNAME, ALT_PEN20_MOKUMON_FQNAME_LEN },
        { PEN20_MONOCHROMON_NAME, PEN20_MONOCHROMON_NAME_LEN, PEN20_MONOCHROMON_ID, PEN20_MONOCHROMON_ID_LEN, PEN20_MONOCHROMON_FQID, PEN20_MONOCHROMON_FQID_LEN, PEN20_MONOCHROMON_FQNAME, PEN20_MONOCHROMON_FQNAME_LEN },
        { PEN20_MONOCHROMON_NAME, PEN20_MONOCHROMON_NAME_LEN, PEN20_MONOCHROMON_ID, PEN20_MONOCHROMON_ID_LEN, ALT_PEN20_MONOCHROMON_FQID, ALT_PEN20_MONOCHROMON_FQID_LEN, ALT_PEN20_MONOCHROMON_FQNAME, ALT_PEN20_MONOCHROMON_FQNAME_LEN },
        { PEN20_MUGENDRAMON_NAME, PEN20_MUGENDRAMON_NAME_LEN, PEN20_MUGENDRAMON_ID, PEN20_MUGENDRAMON_ID_LEN, PEN20_MUGENDRAMON_FQID, PEN20_MUGENDRAMON_FQID_LEN, PEN20_MUGENDRAMON_FQNAME, PEN20_MUGENDRAMON_FQNAME_LEN },
        { PEN20_MUGENDRAMON_NAME, PEN20_MUGENDRAMON_NAME_LEN, PEN20_MUGENDRAMON_ID, PEN20_MUGENDRAMON_ID_LEN, ALT_PEN20_MUGENDRAMON_FQID, ALT_PEN20_MUGENDRAMON_FQID_LEN, ALT_PEN20_MUGENDRAMON_FQNAME, ALT_PEN20_MUGENDRAMON_FQNAME_LEN },
        { PEN20_MUSHMON_NAME, PEN20_MUSHMON_NAME_LEN, PEN20_MUSHMON_ID, PEN20_MUSHMON_ID_LEN, PEN20_MUSHMON_FQID, PEN20_MUSHMON_FQID_LEN, PEN20_MUSHMON_FQNAME, PEN20_MUSHMON_FQNAME_LEN },
        { PEN20_MUSHMON_NAME, PEN20_MUSHMON_NAME_LEN, PEN20_MUSHMON_ID, PEN20_MUSHMON_ID_LEN, ALT_PEN20_MUSHMON_FQID, ALT_PEN20_MUSHMON_FQID_LEN, ALT_PEN20_MUSHMON_FQNAME, ALT_PEN20_MUSHMON_FQNAME_LEN },
        { PEN20_NYAROMON_NAME, PEN20_NYAROMON_NAME_LEN, PEN20_NYAROMON_ID, PEN20_NYAROMON_ID_LEN, PEN20_NYAROMON_FQID, PEN20_NYAROMON_FQID_LEN, PEN20_NYAROMON_FQNAME, PEN20_NYAROMON_FQNAME_LEN },
        { PEN20_NYAROMON_NAME, PEN20_NYAROMON_NAME_LEN, PEN20_NYAROMON_ID, PEN20_NYAROMON_ID_LEN, ALT_PEN20_NYAROMON_FQID, ALT_PEN20_NYAROMON_FQID_LEN, ALT_PEN20_NYAROMON_FQNAME, ALT_PEN20_NYAROMON_FQNAME_LEN },
        { PEN20_NYOKIMON_NAME, PEN20_NYOKIMON_NAME_LEN, PEN20_NYOKIMON_ID, PEN20_NYOKIMON_ID_LEN, PEN20_NYOKIMON_FQID, PEN20_NYOKIMON_FQID_LEN, PEN20_NYOKIMON_FQNAME, PEN20_NYOKIMON_FQNAME_LEN },
        { PEN20_NYOKIMON_NAME, PEN20_NYOKIMON_NAME_LEN, PEN20_NYOKIMON_ID, PEN20_NYOKIMON_ID_LEN, ALT_PEN20_NYOKIMON_FQID, ALT_PEN20_NYOKIMON_FQID_LEN, ALT_PEN20_NYOKIMON_FQNAME, ALT_PEN20_NYOKIMON_FQNAME_LEN },
        { PEN20_OCTMON_NAME, PEN20_OCTMON_NAME_LEN, PEN20_OCTMON_ID, PEN20_OCTMON_ID_LEN, PEN20_OCTMON_FQID, PEN20_OCTMON_FQID_LEN, PEN20_OCTMON_FQNAME, PEN20_OCTMON_FQNAME_LEN },
        { PEN20_OCTMON_NAME, PEN20_OCTMON_NAME_LEN, PEN20_OCTMON_ID, PEN20_OCTMON_ID_LEN, ALT_PEN20_OCTMON_FQID, ALT_PEN20_OCTMON_FQID_LEN, ALT_PEN20_OCTMON_FQNAME, ALT_PEN20_OCTMON_FQNAME_LEN },
        { PEN20_OFANIMON_NAME, PEN20_OFANIMON_NAME_LEN, PEN20_OFANIMON_ID, PEN20_OFANIMON_ID_LEN, PEN20_OFANIMON_FQID, PEN20_OFANIMON_FQID_LEN, PEN20_OFANIMON_FQNAME, PEN20_OFANIMON_FQNAME_LEN },
        { PEN20_OFANIMON_NAME, PEN20_OFANIMON_NAME_LEN, PEN20_OFANIMON_ID, PEN20_OFANIMON_ID_LEN, ALT_PEN20_OFANIMON_FQID, ALT_PEN20_OFANIMON_FQID_LEN, ALT_PEN20_OFANIMON_FQNAME, ALT_PEN20_OFANIMON_FQNAME_LEN },
        { PEN20_OGUDOMON_NAME, PEN20_OGUDOMON_NAME_LEN, PEN20_OGUDOMON_ID, PEN20_OGUDOMON_ID_LEN, PEN20_OGUDOMON_FQID, PEN20_OGUDOMON_FQID_LEN, PEN20_OGUDOMON_FQNAME, PEN20_OGUDOMON_FQNAME_LEN },
        { PEN20_OGUDOMON_NAME, PEN20_OGUDOMON_NAME_LEN, PEN20_OGUDOMON_ID, PEN20_OGUDOMON_ID_LEN, ALT_PEN20_OGUDOMON_FQID, ALT_PEN20_OGUDOMON_FQID_LEN, ALT_PEN20_OGUDOMON_FQNAME, ALT_PEN20_OGUDOMON_FQNAME_LEN },
        { PEN20_OKUWAMON_NAME, PEN20_OKUWAMON_NAME_LEN, PEN20_OKUWAMON_ID, PEN20_OKUWAMON_ID_LEN, PEN20_OKUWAMON_FQID, PEN20_OKUWAMON_FQID_LEN, PEN20_OKUWAMON_FQNAME, PEN20_OKUWAMON_FQNAME_LEN },
        { PEN20_OKUWAMON_NAME, PEN20_OKUWAMON_NAME_LEN, PEN20_OKUWAMON_ID, PEN20_OKUWAMON_ID_LEN, ALT_PEN20_OKUWAMON_FQID, ALT_PEN20_OKUWAMON_FQID_LEN, ALT_PEN20_OKUWAMON_FQNAME, ALT_PEN20_OKUWAMON_FQNAME_LEN },
        { PEN20_OMEGAMON_NAME, PEN20_OMEGAMON_NAME_LEN, PEN20_OMEGAMON_ID, PEN20_OMEGAMON_ID_LEN, PEN20_OMEGAMON_FQID, PEN20_OMEGAMON_FQID_LEN, PEN20_OMEGAMON_FQNAME, PEN20_OMEGAMON_FQNAME_LEN },
        { PEN20_OMEGAMON_NAME, PEN20_OMEGAMON_NAME_LEN, PEN20_OMEGAMON_ID, PEN20_OMEGAMON_ID_LEN, ALT_PEN20_OMEGAMON_FQID, ALT_PEN20_OMEGAMON_FQID_LEN, ALT_PEN20_OMEGAMON_FQNAME, ALT_PEN20_OMEGAMON_FQNAME_LEN },
        { PEN20_ORDINEMON_NAME, PEN20_ORDINEMON_NAME_LEN, PEN20_ORDINEMON_ID, PEN20_ORDINEMON_ID_LEN, PEN20_ORDINEMON_FQID, PEN20_ORDINEMON_FQID_LEN, PEN20_ORDINEMON_FQNAME, PEN20_ORDINEMON_FQNAME_LEN },
        { PEN20_ORDINEMON_NAME, PEN20_ORDINEMON_NAME_LEN, PEN20_ORDINEMON_ID, PEN20_ORDINEMON_ID_LEN, ALT_PEN20_ORDINEMON_FQID, ALT_PEN20_ORDINEMON_FQID_LEN, ALT_PEN20_ORDINEMON_FQNAME, ALT_PEN20_ORDINEMON_FQNAME_LEN },
        { PEN20_OTAMAMON_NAME, PEN20_OTAMAMON_NAME_LEN, PEN20_OTAMAMON_ID, PEN20_OTAMAMON_ID_LEN, PEN20_OTAMAMON_FQID, PEN20_OTAMAMON_FQID_LEN, PEN20_OTAMAMON_FQNAME, PEN20_OTAMAMON_FQNAME_LEN },
        { PEN20_OTAMAMON_NAME, PEN20_OTAMAMON_NAME_LEN, PEN20_OTAMAMON_ID, PEN20_OTAMAMON_ID_LEN, ALT_PEN20_OTAMAMON_FQID, ALT_PEN20_OTAMAMON_FQID_LEN, ALT_PEN20_OTAMAMON_FQNAME, ALT_PEN20_OTAMAMON_FQNAME_LEN },
        { PEN20_OURYUMON_NAME, PEN20_OURYUMON_NAME_LEN, PEN20_OURYUMON_ID, PEN20_OURYUMON_ID_LEN, PEN20_OURYUMON_FQID, PEN20_OURYUMON_FQID_LEN, PEN20_OURYUMON_FQNAME, PEN20_OURYUMON_FQNAME_LEN },
        { PEN20_OURYUMON_NAME, PEN20_OURYUMON_NAME_LEN, PEN20_OURYUMON_ID, PEN20_OURYUMON_ID_LEN, ALT_PEN20_OURYUMON_FQID, ALT_PEN20_OURYUMON_FQID_LEN, ALT_PEN20_OURYUMON_FQNAME, ALT_PEN20_OURYUMON_FQNAME_LEN },
        { PEN20_PAILDRAMON_NAME, PEN20_PAILDRAMON_NAME_LEN, PEN20_PAILDRAMON_ID, PEN20_PAILDRAMON_ID_LEN, PEN20_PAILDRAMON_FQID, PEN20_PAILDRAMON_FQID_LEN, PEN20_PAILDRAMON_FQNAME, PEN20_PAILDRAMON_FQNAME_LEN },
        { PEN20_PAILDRAMON_NAME, PEN20_PAILDRAMON_NAME_LEN, PEN20_PAILDRAMON_ID, PEN20_PAILDRAMON_ID_LEN, ALT_PEN20_PAILDRAMON_FQID, ALT_PEN20_PAILDRAMON_FQID_LEN, ALT_PEN20_PAILDRAMON_FQNAME, ALT_PEN20_PAILDRAMON_FQNAME_LEN },
        { PEN20_PALMON_NAME, PEN20_PALMON_NAME_LEN, PEN20_PALMON_ID, PEN20_PALMON_ID_LEN, PEN20_PALMON_FQID, PEN20_PALMON_FQID_LEN, PEN20_PALMON_FQNAME, PEN20_PALMON_FQNAME_LEN },
        { PEN20_PALMON_NAME, PEN20_PALMON_NAME_LEN, PEN20_PALMON_ID, PEN20_PALMON_ID_LEN, ALT_PEN20_PALMON_FQID, ALT_PEN20_PALMON_FQID_LEN, ALT_PEN20_PALMON_FQNAME, ALT_PEN20_PALMON_FQNAME_LEN },
        { PEN20_PETI_MERAMON_NAME, PEN20_PETI_MERAMON_NAME_LEN, PEN20_PETI_MERAMON_ID, PEN20_PETI_MERAMON_ID_LEN, PEN20_PETI_MERAMON_FQID, PEN20_PETI_MERAMON_FQID_LEN, PEN20_PETI_MERAMON_FQNAME, PEN20_PETI_MERAMON_FQNAME_LEN },
        { PEN20_PETI_MERAMON_NAME, PEN20_PETI_MERAMON_NAME_LEN, PEN20_PETI_MERAMON_ID, PEN20_PETI_MERAMON_ID_LEN, ALT_PEN20_PETI_MERAMON_FQID, ALT_PEN20_PETI_MERAMON_FQID_LEN, ALT_PEN20_PETI_MERAMON_FQNAME, ALT_PEN20_PETI_MERAMON_FQNAME_LEN },
        { PEN20_PETITMON_NAME, PEN20_PETITMON_NAME_LEN, PEN20_PETITMON_ID, PEN20_PETITMON_ID_LEN, PEN20_PETITMON_FQID, PEN20_PETITMON_FQID_LEN, PEN20_PETITMON_FQNAME, PEN20_PETITMON_FQNAME_LEN },
        { PEN20_PETITMON_NAME, PEN20_PETITMON_NAME_LEN, PEN20_PETITMON_ID, PEN20_PETITMON_ID_LEN, ALT_PEN20_PETITMON_FQID, ALT_PEN20_PETITMON_FQID_LEN, ALT_PEN20_PETITMON_FQNAME, ALT_PEN20_PETITMON_FQNAME_LEN },
        { PEN20_PHASCOMON_NAME, PEN20_PHASCOMON_NAME_LEN, PEN20_PHASCOMON_ID, PEN20_PHASCOMON_ID_LEN, PEN20_PHASCOMON_FQID, PEN20_PHASCOMON_FQID_LEN, PEN20_PHASCOMON_FQNAME, PEN20_PHASCOMON_FQNAME_LEN },
        { PEN20_PHASCOMON_NAME, PEN20_PHASCOMON_NAME_LEN, PEN20_PHASCOMON_ID, PEN20_PHASCOMON_ID_LEN, ALT_PEN20_PHASCOMON_FQID, ALT_PEN20_PHASCOMON_FQID_LEN, ALT_PEN20_PHASCOMON_FQNAME, ALT_PEN20_PHASCOMON_FQNAME_LEN },
        { PEN20_PICCOLOMON_NAME, PEN20_PICCOLOMON_NAME_LEN, PEN20_PICCOLOMON_ID, PEN20_PICCOLOMON_ID_LEN, PEN20_PICCOLOMON_FQID, PEN20_PICCOLOMON_FQID_LEN, PEN20_PICCOLOMON_FQNAME, PEN20_PICCOLOMON_FQNAME_LEN },
        { PEN20_PICCOLOMON_NAME, PEN20_PICCOLOMON_NAME_LEN, PEN20_PICCOLOMON_ID, PEN20_PICCOLOMON_ID_LEN, ALT_PEN20_PICCOLOMON_FQID, ALT_PEN20_PICCOLOMON_FQID_LEN, ALT_PEN20_PICCOLOMON_FQNAME, ALT_PEN20_PICCOLOMON_FQNAME_LEN },
        { PEN20_PICO_DEVIMON_NAME, PEN20_PICO_DEVIMON_NAME_LEN, PEN20_PICO_DEVIMON_ID, PEN20_PICO_DEVIMON_ID_LEN, PEN20_PICO_DEVIMON_FQID, PEN20_PICO_DEVIMON_FQID_LEN, PEN20_PICO_DEVIMON_FQNAME, PEN20_PICO_DEVIMON_FQNAME_LEN },
        { PEN20_PICO_DEVIMON_NAME, PEN20_PICO_DEVIMON_NAME_LEN, PEN20_PICO_DEVIMON_ID, PEN20_PICO_DEVIMON_ID_LEN, ALT_PEN20_PICO_DEVIMON_FQID, ALT_PEN20_PICO_DEVIMON_FQID_LEN, ALT_PEN20_PICO_DEVIMON_FQNAME, ALT_PEN20_PICO_DEVIMON_FQNAME_LEN },
        { PEN20_PIEMON_NAME, PEN20_PIEMON_NAME_LEN, PEN20_PIEMON_ID, PEN20_PIEMON_ID_LEN, PEN20_PIEMON_FQID, PEN20_PIEMON_FQID_LEN, PEN20_PIEMON_FQNAME, PEN20_PIEMON_FQNAME_LEN },
        { PEN20_PIEMON_NAME, PEN20_PIEMON_NAME_LEN, PEN20_PIEMON_ID, PEN20_PIEMON_ID_LEN, ALT_PEN20_PIEMON_FQID, ALT_PEN20_PIEMON_FQID_LEN, ALT_PEN20_PIEMON_FQNAME, ALT_PEN20_PIEMON_FQNAME_LEN },
        { PEN20_PINOCHIMON_NAME, PEN20_PINOCHIMON_NAME_LEN, PEN20_PINOCHIMON_ID, PEN20_PINOCHIMON_ID_LEN, PEN20_PINOCHIMON_FQID, PEN20_PINOCHIMON_FQID_LEN, PEN20_PINOCHIMON_FQNAME, PEN20_PINOCHIMON_FQNAME_LEN },
        { PEN20_PINOCHIMON_NAME, PEN20_PINOCHIMON_NAME_LEN, PEN20_PINOCHIMON_ID, PEN20_PINOCHIMON_ID_LEN, ALT_PEN20_PINOCHIMON_FQID, ALT_PEN20_PINOCHIMON_FQID_LEN, ALT_PEN20_PINOCHIMON_FQNAME, ALT_PEN20_PINOCHIMON_FQNAME_LEN },
        { PEN20_PITCHMON_NAME, PEN20_PITCHMON_NAME_LEN, PEN20_PITCHMON_ID, PEN20_PITCHMON_ID_LEN, PEN20_PITCHMON_FQID, PEN20_PITCHMON_FQID_LEN, PEN20_PITCHMON_FQNAME, PEN20_PITCHMON_FQNAME_LEN },
        { PEN20_PITCHMON_NAME, PEN20_PITCHMON_NAME_LEN, PEN20_PITCHMON_ID, PEN20_PITCHMON_ID_LEN, ALT_PEN20_PITCHMON_FQID, ALT_PEN20_PITCHMON_FQID_LEN, ALT_PEN20_PITCHMON_FQNAME, ALT_PEN20_PITCHMON_FQNAME_LEN },
        { PEN20_PIYOMON_NAME, PEN20_PIYOMON_NAME_LEN, PEN20_PIYOMON_ID, PEN20_PIYOMON_ID_LEN, PEN20_PIYOMON_FQID, PEN20_PIYOMON_FQID_LEN, PEN20_PIYOMON_FQNAME, PEN20_PIYOMON_FQNAME_LEN },
        { PEN20_PIYOMON_NAME, PEN20_PIYOMON_NAME_LEN, PEN20_PIYOMON_ID, PEN20_PIYOMON_ID_LEN, ALT_PEN20_PIYOMON_FQID, ALT_PEN20_PIYOMON_FQID_LEN, ALT_PEN20_PIYOMON_FQNAME, ALT_PEN20_PIYOMON_FQNAME_LEN },
        { PEN20_PLESIOMON_NAME, PEN20_PLESIOMON_NAME_LEN, PEN20_PLESIOMON_ID, PEN20_PLESIOMON_ID_LEN, PEN20_PLESIOMON_FQID, PEN20_PLESIOMON_FQID_LEN, PEN20_PLESIOMON_FQNAME, PEN20_PLESIOMON_FQNAME_LEN },
        { PEN20_PLESIOMON_NAME, PEN20_PLESIOMON_NAME_LEN, PEN20_PLESIOMON_ID, PEN20_PLESIOMON_ID_LEN, ALT_PEN20_PLESIOMON_FQID, ALT_PEN20_PLESIOMON_FQID_LEN, ALT_PEN20_PLESIOMON_FQNAME, ALT_PEN20_PLESIOMON_FQNAME_LEN },
        { PEN20_PLOTMON_NAME, PEN20_PLOTMON_NAME_LEN, PEN20_PLOTMON_ID, PEN20_PLOTMON_ID_LEN, PEN20_PLOTMON_FQID, PEN20_PLOTMON_FQID_LEN, PEN20_PLOTMON_FQNAME, PEN20_PLOTMON_FQNAME_LEN },
        { PEN20_PLOTMON_NAME, PEN20_PLOTMON_NAME_LEN, PEN20_PLOTMON_ID, PEN20_PLOTMON_ID_LEN, ALT_PEN20_PLOTMON_FQID, ALT_PEN20_PLOTMON_FQID_LEN, ALT_PEN20_PLOTMON_FQNAME, ALT_PEN20_PLOTMON_FQNAME_LEN },
        { PEN20_PORCUPAMON_NAME, PEN20_PORCUPAMON_NAME_LEN, PEN20_PORCUPAMON_ID, PEN20_PORCUPAMON_ID_LEN, PEN20_PORCUPAMON_FQID, PEN20_PORCUPAMON_FQID_LEN, PEN20_PORCUPAMON_FQNAME, PEN20_PORCUPAMON_FQNAME_LEN },
        { PEN20_PORCUPAMON_NAME, PEN20_PORCUPAMON_NAME_LEN, PEN20_PORCUPAMON_ID, PEN20_PORCUPAMON_ID_LEN, ALT_PEN20_PORCUPAMON_FQID, ALT_PEN20_PORCUPAMON_FQID_LEN, ALT_PEN20_PORCUPAMON_FQNAME, ALT_PEN20_PORCUPAMON_FQNAME_LEN },
        { PEN20_PUKAMON_NAME, PEN20_PUKAMON_NAME_LEN, PEN20_PUKAMON_ID, PEN20_PUKAMON_ID_LEN, PEN20_PUKAMON_FQID, PEN20_PUKAMON_FQID_LEN, PEN20_PUKAMON_FQNAME, PEN20_PUKAMON_FQNAME_LEN },
        { PEN20_PUKAMON_NAME, PEN20_PUKAMON_NAME_LEN, PEN20_PUKAMON_ID, PEN20_PUKAMON_ID_LEN, ALT_PEN20_PUKAMON_FQID, ALT_PEN20_PUKAMON_FQID_LEN, ALT_PEN20_PUKAMON_FQNAME, ALT_PEN20_PUKAMON_FQNAME_LEN },
        { PEN20_PUKUMON_NAME, PEN20_PUKUMON_NAME_LEN, PEN20_PUKUMON_ID, PEN20_PUKUMON_ID_LEN, PEN20_PUKUMON_FQID, PEN20_PUKUMON_FQID_LEN, PEN20_PUKUMON_FQNAME, PEN20_PUKUMON_FQNAME_LEN },
        { PEN20_PUKUMON_NAME, PEN20_PUKUMON_NAME_LEN, PEN20_PUKUMON_ID, PEN20_PUKUMON_ID_LEN, ALT_PEN20_PUKUMON_FQID, ALT_PEN20_PUKUMON_FQID_LEN, ALT_PEN20_PUKUMON_FQNAME, ALT_PEN20_PUKUMON_FQNAME_LEN },
        { PEN20_PUMPMON_NAME, PEN20_PUMPMON_NAME_LEN, PEN20_PUMPMON_ID, PEN20_PUMPMON_ID_LEN, PEN20_PUMPMON_FQID, PEN20_PUMPMON_FQID_LEN, PEN20_PUMPMON_FQNAME, PEN20_PUMPMON_FQNAME_LEN },
        { PEN20_PUMPMON_NAME, PEN20_PUMPMON_NAME_LEN, PEN20_PUMPMON_ID, PEN20_PUMPMON_ID_LEN, ALT_PEN20_PUMPMON_FQID, ALT_PEN20_PUMPMON_FQID_LEN, ALT_PEN20_PUMPMON_FQNAME, ALT_PEN20_PUMPMON_FQNAME_LEN },
        { PEN20_PYOCOMON_NAME, PEN20_PYOCOMON_NAME_LEN, PEN20_PYOCOMON_ID, PEN20_PYOCOMON_ID_LEN, PEN20_PYOCOMON_FQID, PEN20_PYOCOMON_FQID_LEN, PEN20_PYOCOMON_FQNAME, PEN20_PYOCOMON_FQNAME_LEN },
        { PEN20_PYOCOMON_NAME, PEN20_PYOCOMON_NAME_LEN, PEN20_PYOCOMON_ID, PEN20_PYOCOMON_ID_LEN, ALT_PEN20_PYOCOMON_FQID, ALT_PEN20_PYOCOMON_FQID_LEN, ALT_PEN20_PYOCOMON_FQNAME, ALT_PEN20_PYOCOMON_FQNAME_LEN },
        { PEN20_RAFFLESIMON_NAME, PEN20_RAFFLESIMON_NAME_LEN, PEN20_RAFFLESIMON_ID, PEN20_RAFFLESIMON_ID_LEN, PEN20_RAFFLESIMON_FQID, PEN20_RAFFLESIMON_FQID_LEN, PEN20_RAFFLESIMON_FQNAME, PEN20_RAFFLESIMON_FQNAME_LEN },
        { PEN20_RAFFLESIMON_NAME, PEN20_RAFFLESIMON_NAME_LEN, PEN20_RAFFLESIMON_ID, PEN20_RAFFLESIMON_ID_LEN, ALT_PEN20_RAFFLESIMON_FQID, ALT_PEN20_RAFFLESIMON_FQID_LEN, ALT_PEN20_RAFFLESIMON_FQNAME, ALT_PEN20_RAFFLESIMON_FQNAME_LEN },
        { PEN20_RAGNA_LORDMON_NAME, PEN20_RAGNA_LORDMON_NAME_LEN, PEN20_RAGNA_LORDMON_ID, PEN20_RAGNA_LORDMON_ID_LEN, PEN20_RAGNA_LORDMON_FQID, PEN20_RAGNA_LORDMON_FQID_LEN, PEN20_RAGNA_LORDMON_FQNAME, PEN20_RAGNA_LORDMON_FQNAME_LEN },
        { PEN20_RAGNA_LORDMON_NAME, PEN20_RAGNA_LORDMON_NAME_LEN, PEN20_RAGNA_LORDMON_ID, PEN20_RAGNA_LORDMON_ID_LEN, ALT_PEN20_RAGNA_LORDMON_FQID, ALT_PEN20_RAGNA_LORDMON_FQID_LEN, ALT_PEN20_RAGNA_LORDMON_FQNAME, ALT_PEN20_RAGNA_LORDMON_FQNAME_LEN },
        { PEN20_RAGUELMON_NAME, PEN20_RAGUELMON_NAME_LEN, PEN20_RAGUELMON_ID, PEN20_RAGUELMON_ID_LEN, PEN20_RAGUELMON_FQID, PEN20_RAGUELMON_FQID_LEN, PEN20_RAGUELMON_FQNAME, PEN20_RAGUELMON_FQNAME_LEN },
        { PEN20_RAGUELMON_NAME, PEN20_RAGUELMON_NAME_LEN, PEN20_RAGUELMON_ID, PEN20_RAGUELMON_ID_LEN, ALT_PEN20_RAGUELMON_FQID, ALT_PEN20_RAGUELMON_FQID_LEN, ALT_PEN20_RAGUELMON_FQNAME, ALT_PEN20_RAGUELMON_FQNAME_LEN },
        { PEN20_RAIJI_LUDOMON_NAME, PEN20_RAIJI_LUDOMON_NAME_LEN, PEN20_RAIJI_LUDOMON_ID, PEN20_RAIJI_LUDOMON_ID_LEN, PEN20_RAIJI_LUDOMON_FQID, PEN20_RAIJI_LUDOMON_FQID_LEN, PEN20_RAIJI_LUDOMON_FQNAME, PEN20_RAIJI_LUDOMON_FQNAME_LEN },
        { PEN20_RAIJI_LUDOMON_NAME, PEN20_RAIJI_LUDOMON_NAME_LEN, PEN20_RAIJI_LUDOMON_ID, PEN20_RAIJI_LUDOMON_ID_LEN, ALT_PEN20_RAIJI_LUDOMON_FQID, ALT_PEN20_RAIJI_LUDOMON_FQID_LEN, ALT_PEN20_RAIJI_LUDOMON_FQNAME, ALT_PEN20_RAIJI_LUDOMON_FQNAME_LEN },
        { PEN20_RAPIDMON_NAME, PEN20_RAPIDMON_NAME_LEN, PEN20_RAPIDMON_ID, PEN20_RAPIDMON_ID_LEN, PEN20_RAPIDMON_FQID, PEN20_RAPIDMON_FQID_LEN, PEN20_RAPIDMON_FQNAME, PEN20_RAPIDMON_FQNAME_LEN },
        { PEN20_RAPIDMON_NAME, PEN20_RAPIDMON_NAME_LEN, PEN20_RAPIDMON_ID, PEN20_RAPIDMON_ID_LEN, ALT_PEN20_RAPIDMON_FQID, ALT_PEN20_RAPIDMON_FQID_LEN, ALT_PEN20_RAPIDMON_FQNAME, ALT_PEN20_RAPIDMON_FQNAME_LEN },
        { PEN20_RED_VEGIMON_NAME, PEN20_RED_VEGIMON_NAME_LEN, PEN20_RED_VEGIMON_ID, PEN20_RED_VEGIMON_ID_LEN, PEN20_RED_VEGIMON_FQID, PEN20_RED_VEGIMON_FQID_LEN, PEN20_RED_VEGIMON_FQNAME, PEN20_RED_VEGIMON_FQNAME_LEN },
        { PEN20_RED_VEGIMON_NAME, PEN20_RED_VEGIMON_NAME_LEN, PEN20_RED_VEGIMON_ID, PEN20_RED_VEGIMON_ID_LEN, ALT_PEN20_RED_VEGIMON_FQID, ALT_PEN20_RED_VEGIMON_FQID_LEN, ALT_PEN20_RED_VEGIMON_FQNAME, ALT_PEN20_RED_VEGIMON_FQNAME_LEN },
        { PEN20_REPPAMON_NAME, PEN20_REPPAMON_NAME_LEN, PEN20_REPPAMON_ID, PEN20_REPPAMON_ID_LEN, PEN20_REPPAMON_FQID, PEN20_REPPAMON_FQID_LEN, PEN20_REPPAMON_FQNAME, PEN20_REPPAMON_FQNAME_LEN },
        { PEN20_REPPAMON_NAME, PEN20_REPPAMON_NAME_LEN, PEN20_REPPAMON_ID, PEN20_REPPAMON_ID_LEN, ALT_PEN20_REPPAMON_FQID, ALT_PEN20_REPPAMON_FQID_LEN, ALT_PEN20_REPPAMON_FQNAME, ALT_PEN20_REPPAMON_FQNAME_LEN },
        { PEN20_REVOLMON_NAME, PEN20_REVOLMON_NAME_LEN, PEN20_REVOLMON_ID, PEN20_REVOLMON_ID_LEN, PEN20_REVOLMON_FQID, PEN20_REVOLMON_FQID_LEN, PEN20_REVOLMON_FQNAME, PEN20_REVOLMON_FQNAME_LEN },
        { PEN20_REVOLMON_NAME, PEN20_REVOLMON_NAME_LEN, PEN20_REVOLMON_ID, PEN20_REVOLMON_ID_LEN, ALT_PEN20_REVOLMON_FQID, ALT_PEN20_REVOLMON_FQID_LEN, ALT_PEN20_REVOLMON_FQNAME, ALT_PEN20_REVOLMON_FQNAME_LEN },
        { PEN20_RIZE_GREYMON_NAME, PEN20_RIZE_GREYMON_NAME_LEN, PEN20_RIZE_GREYMON_ID, PEN20_RIZE_GREYMON_ID_LEN, PEN20_RIZE_GREYMON_FQID, PEN20_RIZE_GREYMON_FQID_LEN, PEN20_RIZE_GREYMON_FQNAME, PEN20_RIZE_GREYMON_FQNAME_LEN },
        { PEN20_RIZE_GREYMON_NAME, PEN20_RIZE_GREYMON_NAME_LEN, PEN20_RIZE_GREYMON_ID, PEN20_RIZE_GREYMON_ID_LEN, ALT_PEN20_RIZE_GREYMON_FQID, ALT_PEN20_RIZE_GREYMON_FQID_LEN, ALT_PEN20_RIZE_GREYMON_FQNAME, ALT_PEN20_RIZE_GREYMON_FQNAME_LEN },
        { PEN20_ROSEMON_NAME, PEN20_ROSEMON_NAME_LEN, PEN20_ROSEMON_ID, PEN20_ROSEMON_ID_LEN, PEN20_ROSEMON_FQID, PEN20_ROSEMON_FQID_LEN, PEN20_ROSEMON_FQNAME, PEN20_ROSEMON_FQNAME_LEN },
        { PEN20_ROSEMON_NAME, PEN20_ROSEMON_NAME_LEN, PEN20_ROSEMON_ID, PEN20_ROSEMON_ID_LEN, ALT_PEN20_ROSEMON_FQID, ALT_PEN20_ROSEMON_FQID_LEN, ALT_PEN20_ROSEMON_FQNAME, ALT_PEN20_ROSEMON_FQNAME_LEN },
        { PEN20_RUKAMON_NAME, PEN20_RUKAMON_NAME_LEN, PEN20_RUKAMON_ID, PEN20_RUKAMON_ID_LEN, PEN20_RUKAMON_FQID, PEN20_RUKAMON_FQID_LEN, PEN20_RUKAMON_FQNAME, PEN20_RUKAMON_FQNAME_LEN },
        { PEN20_RUKAMON_NAME, PEN20_RUKAMON_NAME_LEN, PEN20_RUKAMON_ID, PEN20_RUKAMON_ID_LEN, ALT_PEN20_RUKAMON_FQID, ALT_PEN20_RUKAMON_FQID_LEN, ALT_PEN20_RUKAMON_FQNAME, ALT_PEN20_RUKAMON_FQNAME_LEN },
        { PEN20_RYUDAMON_NAME, PEN20_RYUDAMON_NAME_LEN, PEN20_RYUDAMON_ID, PEN20_RYUDAMON_ID_LEN, PEN20_RYUDAMON_FQID, PEN20_RYUDAMON_FQID_LEN, PEN20_RYUDAMON_FQNAME, PEN20_RYUDAMON_FQNAME_LEN },
        { PEN20_RYUDAMON_NAME, PEN20_RYUDAMON_NAME_LEN, PEN20_RYUDAMON_ID, PEN20_RYUDAMON_ID_LEN, ALT_PEN20_RYUDAMON_FQID, ALT_PEN20_RYUDAMON_FQID_LEN, ALT_PEN20_RYUDAMON_FQNAME, ALT_PEN20_RYUDAMON_FQNAME_LEN },
        { PEN20_SABER_LEOMON_NAME, PEN20_SABER_LEOMON_NAME_LEN, PEN20_SABER_LEOMON_ID, PEN20_SABER_LEOMON_ID_LEN, PEN20_SABER_LEOMON_FQID, PEN20_SABER_LEOMON_FQID_LEN, PEN20_SABER_LEOMON_FQNAME, PEN20_SABER_LEOMON_FQNAME_LEN },
        { PEN20_SABER_LEOMON_NAME, PEN20_SABER_LEOMON_NAME_LEN, PEN20_SABER_LEOMON_ID, PEN20_SABER_LEOMON_ID_LEN, ALT_PEN20_SABER_LEOMON_FQID, ALT_PEN20_SABER_LEOMON_FQID_LEN, ALT_PEN20_SABER_LEOMON_FQNAME, ALT_PEN20_SABER_LEOMON_FQNAME_LEN },
        { PEN20_SAINT_GALGOMON_NAME, PEN20_SAINT_GALGOMON_NAME_LEN, PEN20_SAINT_GALGOMON_ID, PEN20_SAINT_GALGOMON_ID_LEN, PEN20_SAINT_GALGOMON_FQID, PEN20_SAINT_GALGOMON_FQID_LEN, PEN20_SAINT_GALGOMON_FQNAME, PEN20_SAINT_GALGOMON_FQNAME_LEN },
        { PEN20_SAINT_GALGOMON_NAME, PEN20_SAINT_GALGOMON_NAME_LEN, PEN20_SAINT_GALGOMON_ID, PEN20_SAINT_GALGOMON_ID_LEN, ALT_PEN20_SAINT_GALGOMON_FQID, ALT_PEN20_SAINT_GALGOMON_FQID_LEN, ALT_PEN20_SAINT_GALGOMON_FQNAME, ALT_PEN20_SAINT_GALGOMON_FQNAME_LEN },
        { PEN20_SAKUMON_NAME, PEN20_SAKUMON_NAME_LEN, PEN20_SAKUMON_ID, PEN20_SAKUMON_ID_LEN, PEN20_SAKUMON_FQID, PEN20_SAKUMON_FQID_LEN, PEN20_SAKUMON_FQNAME, PEN20_SAKUMON_FQNAME_LEN },
        { PEN20_SAKUMON_NAME, PEN20_SAKUMON_NAME_LEN, PEN20_SAKUMON_ID, PEN20_SAKUMON_ID_LEN, ALT_PEN20_SAKUMON_FQID, ALT_PEN20_SAKUMON_FQID_LEN, ALT_PEN20_SAKUMON_FQNAME, ALT_PEN20_SAKUMON_FQNAME_LEN },
        { PEN20_SAKUTTOMON_NAME, PEN20_SAKUTTOMON_NAME_LEN, PEN20_SAKUTTOMON_ID, PEN20_SAKUTTOMON_ID_LEN, PEN20_SAKUTTOMON_FQID, PEN20_SAKUTTOMON_FQID_LEN, PEN20_SAKUTTOMON_FQNAME, PEN20_SAKUTTOMON_FQNAME_LEN },
        { PEN20_SAKUTTOMON_NAME, PEN20_SAKUTTOMON_NAME_LEN, PEN20_SAKUTTOMON_ID, PEN20_SAKUTTOMON_ID_LEN, ALT_PEN20_SAKUTTOMON_FQID, ALT_PEN20_SAKUTTOMON_FQID_LEN, ALT_PEN20_SAKUTTOMON_FQNAME, ALT_PEN20_SAKUTTOMON_FQNAME_LEN },
        { PEN20_SAVIOR_HACKMON_NAME, PEN20_SAVIOR_HACKMON_NAME_LEN, PEN20_SAVIOR_HACKMON_ID, PEN20_SAVIOR_HACKMON_ID_LEN, PEN20_SAVIOR_HACKMON_FQID, PEN20_SAVIOR_HACKMON_FQID_LEN, PEN20_SAVIOR_HACKMON_FQNAME, PEN20_SAVIOR_HACKMON_FQNAME_LEN },
        { PEN20_SAVIOR_HACKMON_NAME, PEN20_SAVIOR_HACKMON_NAME_LEN, PEN20_SAVIOR_HACKMON_ID, PEN20_SAVIOR_HACKMON_ID_LEN, ALT_PEN20_SAVIOR_HACKMON_FQID, ALT_PEN20_SAVIOR_HACKMON_FQID_LEN, ALT_PEN20_SAVIOR_HACKMON_FQNAME, ALT_PEN20_SAVIOR_HACKMON_FQNAME_LEN },
        { PEN20_SEADRAMON_NAME, PEN20_SEADRAMON_NAME_LEN, PEN20_SEADRAMON_ID, PEN20_SEADRAMON_ID_LEN, PEN20_SEADRAMON_FQID, PEN20_SEADRAMON_FQID_LEN, PEN20_SEADRAMON_FQNAME, PEN20_SEADRAMON_FQNAME_LEN },
        { PEN20_SEADRAMON_NAME, PEN20_SEADRAMON_NAME_LEN, PEN20_SEADRAMON_ID, PEN20_SEADRAMON_ID_LEN, ALT_PEN20_SEADRAMON_FQID, ALT_PEN20_SEADRAMON_FQID_LEN, ALT_PEN20_SEADRAMON_FQNAME, ALT_PEN20_SEADRAMON_FQNAME_LEN },
        { PEN20_SERAPHIMON_NAME, PEN20_SERAPHIMON_NAME_LEN, PEN20_SERAPHIMON_ID, PEN20_SERAPHIMON_ID_LEN, PEN20_SERAPHIMON_FQID, PEN20_SERAPHIMON_FQID_LEN, PEN20_SERAPHIMON_FQNAME, PEN20_SERAPHIMON_FQNAME_LEN },
        { PEN20_SERAPHIMON_NAME, PEN20_SERAPHIMON_NAME_LEN, PEN20_SERAPHIMON_ID, PEN20_SERAPHIMON_ID_LEN, ALT_PEN20_SERAPHIMON_FQID, ALT_PEN20_SERAPHIMON_FQID_LEN, ALT_PEN20_SERAPHIMON_FQNAME, ALT_PEN20_SERAPHIMON_FQNAME_LEN },
        { PEN20_SHADRAMON_NAME, PEN20_SHADRAMON_NAME_LEN, PEN20_SHADRAMON_ID, PEN20_SHADRAMON_ID_LEN, PEN20_SHADRAMON_FQID, PEN20_SHADRAMON_FQID_LEN, PEN20_SHADRAMON_FQNAME, PEN20_SHADRAMON_FQNAME_LEN },
        { PEN20_SHADRAMON_NAME, PEN20_SHADRAMON_NAME_LEN, PEN20_SHADRAMON_ID, PEN20_SHADRAMON_ID_LEN, ALT_PEN20_SHADRAMON_FQID, ALT_PEN20_SHADRAMON_FQID_LEN, ALT_PEN20_SHADRAMON_FQNAME, ALT_PEN20_SHADRAMON_FQNAME_LEN },
        { PEN20_SHAKOMON_NAME, PEN20_SHAKOMON_NAME_LEN, PEN20_SHAKOMON_ID, PEN20_SHAKOMON_ID_LEN, PEN20_SHAKOMON_FQID, PEN20_SHAKOMON_FQID_LEN, PEN20_SHAKOMON_FQNAME, PEN20_SHAKOMON_FQNAME_LEN },
        { PEN20_SHAKOMON_NAME, PEN20_SHAKOMON_NAME_LEN, PEN20_SHAKOMON_ID, PEN20_SHAKOMON_ID_LEN, ALT_PEN20_SHAKOMON_FQID, ALT_PEN20_SHAKOMON_FQID_LEN, ALT_PEN20_SHAKOMON_FQNAME, ALT_PEN20_SHAKOMON_FQNAME_LEN },
        { PEN20_SKULL_MAMMON_NAME, PEN20_SKULL_MAMMON_NAME_LEN, PEN20_SKULL_MAMMON_ID, PEN20_SKULL_MAMMON_ID_LEN, PEN20_SKULL_MAMMON_FQID, PEN20_SKULL_MAMMON_FQID_LEN, PEN20_SKULL_MAMMON_FQNAME, PEN20_SKULL_MAMMON_FQNAME_LEN },
        { PEN20_SKULL_MAMMON_NAME, PEN20_SKULL_MAMMON_NAME_LEN, PEN20_SKULL_MAMMON_ID, PEN20_SKULL_MAMMON_ID_LEN, ALT_PEN20_SKULL_MAMMON_FQID, ALT_PEN20_SKULL_MAMMON_FQID_LEN, ALT_PEN20_SKULL_MAMMON_FQNAME, ALT_PEN20_SKULL_MAMMON_FQNAME_LEN },
        { PEN20_SLAYERDRAMON_NAME, PEN20_SLAYERDRAMON_NAME_LEN, PEN20_SLAYERDRAMON_ID, PEN20_SLAYERDRAMON_ID_LEN, PEN20_SLAYERDRAMON_FQID, PEN20_SLAYERDRAMON_FQID_LEN, PEN20_SLAYERDRAMON_FQNAME, PEN20_SLAYERDRAMON_FQNAME_LEN },
        { PEN20_SLAYERDRAMON_NAME, PEN20_SLAYERDRAMON_NAME_LEN, PEN20_SLAYERDRAMON_ID, PEN20_SLAYERDRAMON_ID_LEN, ALT_PEN20_SLAYERDRAMON_FQID, ALT_PEN20_SLAYERDRAMON_FQID_LEN, ALT_PEN20_SLAYERDRAMON_FQNAME, ALT_PEN20_SLAYERDRAMON_FQNAME_LEN },
        { PEN20_STARMON_NAME, PEN20_STARMON_NAME_LEN, PEN20_STARMON_ID, PEN20_STARMON_ID_LEN, PEN20_STARMON_FQID, PEN20_STARMON_FQID_LEN, PEN20_STARMON_FQNAME, PEN20_STARMON_FQNAME_LEN },
        { PEN20_STARMON_NAME, PEN20_STARMON_NAME_LEN, PEN20_STARMON_ID, PEN20_STARMON_ID_LEN, ALT_PEN20_STARMON_FQID, ALT_PEN20_STARMON_FQID_LEN, ALT_PEN20_STARMON_FQNAME, ALT_PEN20_STARMON_FQNAME_LEN },
        { PEN20_SUNFLOWMON_NAME, PEN20_SUNFLOWMON_NAME_LEN, PEN20_SUNFLOWMON_ID, PEN20_SUNFLOWMON_ID_LEN, PEN20_SUNFLOWMON_FQID, PEN20_SUNFLOWMON_FQID_LEN, PEN20_SUNFLOWMON_FQNAME, PEN20_SUNFLOWMON_FQNAME_LEN },
        { PEN20_SUNFLOWMON_NAME, PEN20_SUNFLOWMON_NAME_LEN, PEN20_SUNFLOWMON_ID, PEN20_SUNFLOWMON_ID_LEN, ALT_PEN20_SUNFLOWMON_FQID, ALT_PEN20_SUNFLOWMON_FQID_LEN, ALT_PEN20_SUNFLOWMON_FQNAME, ALT_PEN20_SUNFLOWMON_FQNAME_LEN },
        { PEN20_TAILMON_NAME, PEN20_TAILMON_NAME_LEN, PEN20_TAILMON_ID, PEN20_TAILMON_ID_LEN, PEN20_TAILMON_FQID, PEN20_TAILMON_FQID_LEN, PEN20_TAILMON_FQNAME, PEN20_TAILMON_FQNAME_LEN },
        { PEN20_TAILMON_NAME, PEN20_TAILMON_NAME_LEN, PEN20_TAILMON_ID, PEN20_TAILMON_ID_LEN, ALT_PEN20_TAILMON_FQID, ALT_PEN20_TAILMON_FQID_LEN, ALT_PEN20_TAILMON_FQNAME, ALT_PEN20_TAILMON_FQNAME_LEN },
        { PEN20_TANKMON_NAME, PEN20_TANKMON_NAME_LEN, PEN20_TANKMON_ID, PEN20_TANKMON_ID_LEN, PEN20_TANKMON_FQID, PEN20_TANKMON_FQID_LEN, PEN20_TANKMON_FQNAME, PEN20_TANKMON_FQNAME_LEN },
        { PEN20_TANKMON_NAME, PEN20_TANKMON_NAME_LEN, PEN20_TANKMON_ID, PEN20_TANKMON_ID_LEN, ALT_PEN20_TANKMON_FQID, ALT_PEN20_TANKMON_FQID_LEN, ALT_PEN20_TANKMON_FQNAME, ALT_PEN20_TANKMON_FQNAME_LEN },
        { PEN20_TARGETMON_NAME, PEN20_TARGETMON_NAME_LEN, PEN20_TARGETMON_ID, PEN20_TARGETMON_ID_LEN, PEN20_TARGETMON_FQID, PEN20_TARGETMON_FQID_LEN, PEN20_TARGETMON_FQNAME, PEN20_TARGETMON_FQNAME_LEN },
        { PEN20_TARGETMON_NAME, PEN20_TARGETMON_NAME_LEN, PEN20_TARGETMON_ID, PEN20_TARGETMON_ID_LEN, ALT_PEN20_TARGETMON_FQID, ALT_PEN20_TARGETMON_FQID_LEN, ALT_PEN20_TARGETMON_FQNAME, ALT_PEN20_TARGETMON_FQNAME_LEN },
        { PEN20_TENTOMON_NAME, PEN20_TENTOMON_NAME_LEN, PEN20_TENTOMON_ID, PEN20_TENTOMON_ID_LEN, PEN20_TENTOMON_FQID, PEN20_TENTOMON_FQID_LEN, PEN20_TENTOMON_FQNAME, PEN20_TENTOMON_FQNAME_LEN },
        { PEN20_TENTOMON_NAME, PEN20_TENTOMON_NAME_LEN, PEN20_TENTOMON_ID, PEN20_TENTOMON_ID_LEN, ALT_PEN20_TENTOMON_FQID, ALT_PEN20_TENTOMON_FQID_LEN, ALT_PEN20_TENTOMON_FQNAME, ALT_PEN20_TENTOMON_FQNAME_LEN },
        { PEN20_TERRIERMON_NAME, PEN20_TERRIERMON_NAME_LEN, PEN20_TERRIERMON_ID, PEN20_TERRIERMON_ID_LEN, PEN20_TERRIERMON_FQID, PEN20_TERRIERMON_FQID_LEN, PEN20_TERRIERMON_FQNAME, PEN20_TERRIERMON_FQNAME_LEN },
        { PEN20_TERRIERMON_NAME, PEN20_TERRIERMON_NAME_LEN, PEN20_TERRIERMON_ID, PEN20_TERRIERMON_ID_LEN, ALT_PEN20_TERRIERMON_FQID, ALT_PEN20_TERRIERMON_FQID_LEN, ALT_PEN20_TERRIERMON_FQNAME, ALT_PEN20_TERRIERMON_FQNAME_LEN },
        { PEN20_THUNDERBALLMON_NAME, PEN20_THUNDERBALLMON_NAME_LEN, PEN20_THUNDERBALLMON_ID, PEN20_THUNDERBALLMON_ID_LEN, PEN20_THUNDERBALLMON_FQID, PEN20_THUNDERBALLMON_FQID_LEN, PEN20_THUNDERBALLMON_FQNAME, PEN20_THUNDERBALLMON_FQNAME_LEN },
        { PEN20_THUNDERBALLMON_NAME, PEN20_THUNDERBALLMON_NAME_LEN, PEN20_THUNDERBALLMON_ID, PEN20_THUNDERBALLMON_ID_LEN, ALT_PEN20_THUNDERBALLMON_FQID, ALT_PEN20_THUNDERBALLMON_FQID_LEN, ALT_PEN20_THUNDERBALLMON_FQNAME, ALT_PEN20_THUNDERBALLMON_FQNAME_LEN },
        { PEN20_TIA_LUDOMON_NAME, PEN20_TIA_LUDOMON_NAME_LEN, PEN20_TIA_LUDOMON_ID, PEN20_TIA_LUDOMON_ID_LEN, PEN20_TIA_LUDOMON_FQID, PEN20_TIA_LUDOMON_FQID_LEN, PEN20_TIA_LUDOMON_FQNAME, PEN20_TIA_LUDOMON_FQNAME_LEN },
        { PEN20_TIA_LUDOMON_NAME, PEN20_TIA_LUDOMON_NAME_LEN, PEN20_TIA_LUDOMON_ID, PEN20_TIA_LUDOMON_ID_LEN, ALT_PEN20_TIA_LUDOMON_FQID, ALT_PEN20_TIA_LUDOMON_FQID_LEN, ALT_PEN20_TIA_LUDOMON_FQNAME, ALT_PEN20_TIA_LUDOMON_FQNAME_LEN },
        { PEN20_TOGEMON_NAME, PEN20_TOGEMON_NAME_LEN, PEN20_TOGEMON_ID, PEN20_TOGEMON_ID_LEN, PEN20_TOGEMON_FQID, PEN20_TOGEMON_FQID_LEN, PEN20_TOGEMON_FQNAME, PEN20_TOGEMON_FQNAME_LEN },
        { PEN20_TOGEMON_NAME, PEN20_TOGEMON_NAME_LEN, PEN20_TOGEMON_ID, PEN20_TOGEMON_ID_LEN, ALT_PEN20_TOGEMON_FQID, ALT_PEN20_TOGEMON_FQID_LEN, ALT_PEN20_TOGEMON_FQNAME, ALT_PEN20_TOGEMON_FQNAME_LEN },
        { PEN20_TONOSAMA_GEKOMON_NAME, PEN20_TONOSAMA_GEKOMON_NAME_LEN, PEN20_TONOSAMA_GEKOMON_ID, PEN20_TONOSAMA_GEKOMON_ID_LEN, PEN20_TONOSAMA_GEKOMON_FQID, PEN20_TONOSAMA_GEKOMON_FQID_LEN, PEN20_TONOSAMA_GEKOMON_FQNAME, PEN20_TONOSAMA_GEKOMON_FQNAME_LEN },
        { PEN20_TONOSAMA_GEKOMON_NAME, PEN20_TONOSAMA_GEKOMON_NAME_LEN, PEN20_TONOSAMA_GEKOMON_ID, PEN20_TONOSAMA_GEKOMON_ID_LEN, ALT_PEN20_TONOSAMA_GEKOMON_FQID, ALT_PEN20_TONOSAMA_GEKOMON_FQID_LEN, ALT_PEN20_TONOSAMA_GEKOMON_FQNAME, ALT_PEN20_TONOSAMA_GEKOMON_FQNAME_LEN },
        { PEN20_TORTAMON_NAME, PEN20_TORTAMON_NAME_LEN, PEN20_TORTAMON_ID, PEN20_TORTAMON_ID_LEN, PEN20_TORTAMON_FQID, PEN20_TORTAMON_FQID_LEN, PEN20_TORTAMON_FQNAME, PEN20_TORTAMON_FQNAME_LEN },
        { PEN20_TORTAMON_NAME, PEN20_TORTAMON_NAME_LEN, PEN20_TORTAMON_ID, PEN20_TORTAMON_ID_LEN, ALT_PEN20_TORTAMON_FQID, ALT_PEN20_TORTAMON_FQID_LEN, ALT_PEN20_TORTAMON_FQNAME, ALT_PEN20_TORTAMON_FQNAME_LEN },
        { PEN20_TOY_AGUMON_NAME, PEN20_TOY_AGUMON_NAME_LEN, PEN20_TOY_AGUMON_ID, PEN20_TOY_AGUMON_ID_LEN, PEN20_TOY_AGUMON_FQID, PEN20_TOY_AGUMON_FQID_LEN, PEN20_TOY_AGUMON_FQNAME, PEN20_TOY_AGUMON_FQNAME_LEN },
        { PEN20_TOY_AGUMON_NAME, PEN20_TOY_AGUMON_NAME_LEN, PEN20_TOY_AGUMON_ID, PEN20_TOY_AGUMON_ID_LEN, ALT_PEN20_TOY_AGUMON_FQID, ALT_PEN20_TOY_AGUMON_FQID_LEN, ALT_PEN20_TOY_AGUMON_FQNAME, ALT_PEN20_TOY_AGUMON_FQNAME_LEN },
        { PEN20_TRICERAMON_NAME, PEN20_TRICERAMON_NAME_LEN, PEN20_TRICERAMON_ID, PEN20_TRICERAMON_ID_LEN, PEN20_TRICERAMON_FQID, PEN20_TRICERAMON_FQID_LEN, PEN20_TRICERAMON_FQNAME, PEN20_TRICERAMON_FQNAME_LEN },
        { PEN20_TRICERAMON_NAME, PEN20_TRICERAMON_NAME_LEN, PEN20_TRICERAMON_ID, PEN20_TRICERAMON_ID_LEN, ALT_PEN20_TRICERAMON_FQID, ALT_PEN20_TRICERAMON_FQID_LEN, ALT_PEN20_TRICERAMON_FQNAME, ALT_PEN20_TRICERAMON_FQNAME_LEN },
        { PEN20_TROOPMON_NAME, PEN20_TROOPMON_NAME_LEN, PEN20_TROOPMON_ID, PEN20_TROOPMON_ID_LEN, PEN20_TROOPMON_FQID, PEN20_TROOPMON_FQID_LEN, PEN20_TROOPMON_FQNAME, PEN20_TROOPMON_FQNAME_LEN },
        { PEN20_TROOPMON_NAME, PEN20_TROOPMON_NAME_LEN, PEN20_TROOPMON_ID, PEN20_TROOPMON_ID_LEN, ALT_PEN20_TROOPMON_FQID, ALT_PEN20_TROOPMON_FQID_LEN, ALT_PEN20_TROOPMON_FQNAME, ALT_PEN20_TROOPMON_FQNAME_LEN },
        { PEN20_TURUIEMON_NAME, PEN20_TURUIEMON_NAME_LEN, PEN20_TURUIEMON_ID, PEN20_TURUIEMON_ID_LEN, PEN20_TURUIEMON_FQID, PEN20_TURUIEMON_FQID_LEN, PEN20_TURUIEMON_FQNAME, PEN20_TURUIEMON_FQNAME_LEN },
        { PEN20_TURUIEMON_NAME, PEN20_TURUIEMON_NAME_LEN, PEN20_TURUIEMON_ID, PEN20_TURUIEMON_ID_LEN, ALT_PEN20_TURUIEMON_FQID, ALT_PEN20_TURUIEMON_FQID_LEN, ALT_PEN20_TURUIEMON_FQNAME, ALT_PEN20_TURUIEMON_FQNAME_LEN },
        { PEN20_VAMDEMON_NAME, PEN20_VAMDEMON_NAME_LEN, PEN20_VAMDEMON_ID, PEN20_VAMDEMON_ID_LEN, PEN20_VAMDEMON_FQID, PEN20_VAMDEMON_FQID_LEN, PEN20_VAMDEMON_FQNAME, PEN20_VAMDEMON_FQNAME_LEN },
        { PEN20_VAMDEMON_NAME, PEN20_VAMDEMON_NAME_LEN, PEN20_VAMDEMON_ID, PEN20_VAMDEMON_ID_LEN, ALT_PEN20_VAMDEMON_FQID, ALT_PEN20_VAMDEMON_FQID_LEN, ALT_PEN20_VAMDEMON_FQNAME, ALT_PEN20_VAMDEMON_FQNAME_LEN },
        { PEN20_V_DRAMON_NAME, PEN20_V_DRAMON_NAME_LEN, PEN20_V_DRAMON_ID, PEN20_V_DRAMON_ID_LEN, PEN20_V_DRAMON_FQID, PEN20_V_DRAMON_FQID_LEN, PEN20_V_DRAMON_FQNAME, PEN20_V_DRAMON_FQNAME_LEN },
        { PEN20_V_DRAMON_NAME, PEN20_V_DRAMON_NAME_LEN, PEN20_V_DRAMON_ID, PEN20_V_DRAMON_ID_LEN, ALT_PEN20_V_DRAMON_FQID, ALT_PEN20_V_DRAMON_FQID_LEN, ALT_PEN20_V_DRAMON_FQNAME, ALT_PEN20_V_DRAMON_FQNAME_LEN },
        { PEN20_VENOM_VAMDEMON_NAME, PEN20_VENOM_VAMDEMON_NAME_LEN, PEN20_VENOM_VAMDEMON_ID, PEN20_VENOM_VAMDEMON_ID_LEN, PEN20_VENOM_VAMDEMON_FQID, PEN20_VENOM_VAMDEMON_FQID_LEN, PEN20_VENOM_VAMDEMON_FQNAME, PEN20_VENOM_VAMDEMON_FQNAME_LEN },
        { PEN20_VENOM_VAMDEMON_NAME, PEN20_VENOM_VAMDEMON_NAME_LEN, PEN20_VENOM_VAMDEMON_ID, PEN20_VENOM_VAMDEMON_ID_LEN, ALT_PEN20_VENOM_VAMDEMON_FQID, ALT_PEN20_VENOM_VAMDEMON_FQID_LEN, ALT_PEN20_VENOM_VAMDEMON_FQNAME, ALT_PEN20_VENOM_VAMDEMON_FQNAME_LEN },
        { PEN20_V_MON_NAME, PEN20_V_MON_NAME_LEN, PEN20_V_MON_ID, PEN20_V_MON_ID_LEN, PEN20_V_MON_FQID, PEN20_V_MON_FQID_LEN, PEN20_V_MON_FQNAME, PEN20_V_MON_FQNAME_LEN },
        { PEN20_V_MON_NAME, PEN20_V_MON_NAME_LEN, PEN20_V_MON_ID, PEN20_V_MON_ID_LEN, ALT_PEN20_V_MON_FQID, ALT_PEN20_V_MON_FQID_LEN, ALT_PEN20_V_MON_FQNAME, ALT_PEN20_V_MON_FQNAME_LEN },
        { PEN20_VOLCANICDRAMON_NAME, PEN20_VOLCANICDRAMON_NAME_LEN, PEN20_VOLCANICDRAMON_ID, PEN20_VOLCANICDRAMON_ID_LEN, PEN20_VOLCANICDRAMON_FQID, PEN20_VOLCANICDRAMON_FQID_LEN, PEN20_VOLCANICDRAMON_FQNAME, PEN20_VOLCANICDRAMON_FQNAME_LEN },
        { PEN20_VOLCANICDRAMON_NAME, PEN20_VOLCANICDRAMON_NAME_LEN, PEN20_VOLCANICDRAMON_ID, PEN20_VOLCANICDRAMON_ID_LEN, ALT_PEN20_VOLCANICDRAMON_FQID, ALT_PEN20_VOLCANICDRAMON_FQID_LEN, ALT_PEN20_VOLCANICDRAMON_FQNAME, ALT_PEN20_VOLCANICDRAMON_FQNAME_LEN },
        { PEN20_VOLTOBAUTAMON_NAME, PEN20_VOLTOBAUTAMON_NAME_LEN, PEN20_VOLTOBAUTAMON_ID, PEN20_VOLTOBAUTAMON_ID_LEN, PEN20_VOLTOBAUTAMON_FQID, PEN20_VOLTOBAUTAMON_FQID_LEN, PEN20_VOLTOBAUTAMON_FQNAME, PEN20_VOLTOBAUTAMON_FQNAME_LEN },
        { PEN20_VOLTOBAUTAMON_NAME, PEN20_VOLTOBAUTAMON_NAME_LEN, PEN20_VOLTOBAUTAMON_ID, PEN20_VOLTOBAUTAMON_ID_LEN, ALT_PEN20_VOLTOBAUTAMON_FQID, ALT_PEN20_VOLTOBAUTAMON_FQID_LEN, ALT_PEN20_VOLTOBAUTAMON_FQNAME, ALT_PEN20_VOLTOBAUTAMON_FQNAME_LEN },
        { PEN20_VORVOMON_NAME, PEN20_VORVOMON_NAME_LEN, PEN20_VORVOMON_ID, PEN20_VORVOMON_ID_LEN, PEN20_VORVOMON_FQID, PEN20_VORVOMON_FQID_LEN, PEN20_VORVOMON_FQNAME, PEN20_VORVOMON_FQNAME_LEN },
        { PEN20_VORVOMON_NAME, PEN20_VORVOMON_NAME_LEN, PEN20_VORVOMON_ID, PEN20_VORVOMON_ID_LEN, ALT_PEN20_VORVOMON_FQID, ALT_PEN20_VORVOMON_FQID_LEN, ALT_PEN20_VORVOMON_FQNAME, ALT_PEN20_VORVOMON_FQNAME_LEN },
        { PEN20_WAR_GREYMON_NAME, PEN20_WAR_GREYMON_NAME_LEN, PEN20_WAR_GREYMON_ID, PEN20_WAR_GREYMON_ID_LEN, PEN20_WAR_GREYMON_FQID, PEN20_WAR_GREYMON_FQID_LEN, PEN20_WAR_GREYMON_FQNAME, PEN20_WAR_GREYMON_FQNAME_LEN },
        { PEN20_WAR_GREYMON_NAME, PEN20_WAR_GREYMON_NAME_LEN, PEN20_WAR_GREYMON_ID, PEN20_WAR_GREYMON_ID_LEN, ALT_PEN20_WAR_GREYMON_FQID, ALT_PEN20_WAR_GREYMON_FQID_LEN, ALT_PEN20_WAR_GREYMON_FQNAME, ALT_PEN20_WAR_GREYMON_FQNAME_LEN },
        { PEN20_WARU_MONZAEMON_NAME, PEN20_WARU_MONZAEMON_NAME_LEN, PEN20_WARU_MONZAEMON_ID, PEN20_WARU_MONZAEMON_ID_LEN, PEN20_WARU_MONZAEMON_FQID, PEN20_WARU_MONZAEMON_FQID_LEN, PEN20_WARU_MONZAEMON_FQNAME, PEN20_WARU_MONZAEMON_FQNAME_LEN },
        { PEN20_WARU_MONZAEMON_NAME, PEN20_WARU_MONZAEMON_NAME_LEN, PEN20_WARU_MONZAEMON_ID, PEN20_WARU_MONZAEMON_ID_LEN, ALT_PEN20_WARU_MONZAEMON_FQID, ALT_PEN20_WARU_MONZAEMON_FQID_LEN, ALT_PEN20_WARU_MONZAEMON_FQNAME, ALT_PEN20_WARU_MONZAEMON_FQNAME_LEN },
        { PEN20_WERE_GARURUMON_NAME, PEN20_WERE_GARURUMON_NAME_LEN, PEN20_WERE_GARURUMON_ID, PEN20_WERE_GARURUMON_ID_LEN, PEN20_WERE_GARURUMON_FQID, PEN20_WERE_GARURUMON_FQID_LEN, PEN20_WERE_GARURUMON_FQNAME, PEN20_WERE_GARURUMON_FQNAME_LEN },
        { PEN20_WERE_GARURUMON_NAME, PEN20_WERE_GARURUMON_NAME_LEN, PEN20_WERE_GARURUMON_ID, PEN20_WERE_GARURUMON_ID_LEN, ALT_PEN20_WERE_GARURUMON_FQID, ALT_PEN20_WERE_GARURUMON_FQID_LEN, ALT_PEN20_WERE_GARURUMON_FQNAME, ALT_PEN20_WERE_GARURUMON_FQNAME_LEN },
        { PEN20_WHAMON_NAME, PEN20_WHAMON_NAME_LEN, PEN20_WHAMON_ID, PEN20_WHAMON_ID_LEN, PEN20_WHAMON_FQID, PEN20_WHAMON_FQID_LEN, PEN20_WHAMON_FQNAME, PEN20_WHAMON_FQNAME_LEN },
        { PEN20_WHAMON_NAME, PEN20_WHAMON_NAME_LEN, PEN20_WHAMON_ID, PEN20_WHAMON_ID_LEN, ALT_PEN20_WHAMON_FQID, ALT_PEN20_WHAMON_FQID_LEN, ALT_PEN20_WHAMON_FQNAME, ALT_PEN20_WHAMON_FQNAME_LEN },
        { PEN20_WINGDRAMON_NAME, PEN20_WINGDRAMON_NAME_LEN, PEN20_WINGDRAMON_ID, PEN20_WINGDRAMON_ID_LEN, PEN20_WINGDRAMON_FQID, PEN20_WINGDRAMON_FQID_LEN, PEN20_WINGDRAMON_FQNAME, PEN20_WINGDRAMON_FQNAME_LEN },
        { PEN20_WINGDRAMON_NAME, PEN20_WINGDRAMON_NAME_LEN, PEN20_WINGDRAMON_ID, PEN20_WINGDRAMON_ID_LEN, ALT_PEN20_WINGDRAMON_FQID, ALT_PEN20_WINGDRAMON_FQID_LEN, ALT_PEN20_WINGDRAMON_FQNAME, ALT_PEN20_WINGDRAMON_FQNAME_LEN },
        { PEN20_WIZARMON_NAME, PEN20_WIZARMON_NAME_LEN, PEN20_WIZARMON_ID, PEN20_WIZARMON_ID_LEN, PEN20_WIZARMON_FQID, PEN20_WIZARMON_FQID_LEN, PEN20_WIZARMON_FQNAME, PEN20_WIZARMON_FQNAME_LEN },
        { PEN20_WIZARMON_NAME, PEN20_WIZARMON_NAME_LEN, PEN20_WIZARMON_ID, PEN20_WIZARMON_ID_LEN, ALT_PEN20_WIZARMON_FQID, ALT_PEN20_WIZARMON_FQID_LEN, ALT_PEN20_WIZARMON_FQNAME, ALT_PEN20_WIZARMON_FQNAME_LEN },
        { PEN20_WOODMON_NAME, PEN20_WOODMON_NAME_LEN, PEN20_WOODMON_ID, PEN20_WOODMON_ID_LEN, PEN20_WOODMON_FQID, PEN20_WOODMON_FQID_LEN, PEN20_WOODMON_FQNAME, PEN20_WOODMON_FQNAME_LEN },
        { PEN20_WOODMON_NAME, PEN20_WOODMON_NAME_LEN, PEN20_WOODMON_ID, PEN20_WOODMON_ID_LEN, ALT_PEN20_WOODMON_FQID, ALT_PEN20_WOODMON_FQID_LEN, ALT_PEN20_WOODMON_FQNAME, ALT_PEN20_WOODMON_FQNAME_LEN },
        { PEN20_XV_MON_NAME, PEN20_XV_MON_NAME_LEN, PEN20_XV_MON_ID, PEN20_XV_MON_ID_LEN, PEN20_XV_MON_FQID, PEN20_XV_MON_FQID_LEN, PEN20_XV_MON_FQNAME, PEN20_XV_MON_FQNAME_LEN },
        { PEN20_XV_MON_NAME, PEN20_XV_MON_NAME_LEN, PEN20_XV_MON_ID, PEN20_XV_MON_ID_LEN, ALT_PEN20_XV_MON_FQID, ALT_PEN20_XV_MON_FQID_LEN, ALT_PEN20_XV_MON_FQNAME, ALT_PEN20_XV_MON_FQNAME_LEN },
        { PEN20_YUKIMI_BOTAMON_NAME, PEN20_YUKIMI_BOTAMON_NAME_LEN, PEN20_YUKIMI_BOTAMON_ID, PEN20_YUKIMI_BOTAMON_ID_LEN, PEN20_YUKIMI_BOTAMON_FQID, PEN20_YUKIMI_BOTAMON_FQID_LEN, PEN20_YUKIMI_BOTAMON_FQNAME, PEN20_YUKIMI_BOTAMON_FQNAME_LEN },
        { PEN20_YUKIMI_BOTAMON_NAME, PEN20_YUKIMI_BOTAMON_NAME_LEN, PEN20_YUKIMI_BOTAMON_ID, PEN20_YUKIMI_BOTAMON_ID_LEN, ALT_PEN20_YUKIMI_BOTAMON_FQID, ALT_PEN20_YUKIMI_BOTAMON_FQID_LEN, ALT_PEN20_YUKIMI_BOTAMON_FQNAME, ALT_PEN20_YUKIMI_BOTAMON_FQNAME_LEN },
        { PEN20_ZERIMON_NAME, PEN20_ZERIMON_NAME_LEN, PEN20_ZERIMON_ID, PEN20_ZERIMON_ID_LEN, PEN20_ZERIMON_FQID, PEN20_ZERIMON_FQID_LEN, PEN20_ZERIMON_FQNAME, PEN20_ZERIMON_FQNAME_LEN },
        { PEN20_ZERIMON_NAME, PEN20_ZERIMON_NAME_LEN, PEN20_ZERIMON_ID, PEN20_ZERIMON_ID_LEN, ALT_PEN20_ZERIMON_FQID, ALT_PEN20_ZERIMON_FQID_LEN, ALT_PEN20_ZERIMON_FQNAME, ALT_PEN20_ZERIMON_FQNAME_LEN },
        { PEN20_ZUBAEAGERMON_NAME, PEN20_ZUBAEAGERMON_NAME_LEN, PEN20_ZUBAEAGERMON_ID, PEN20_ZUBAEAGERMON_ID_LEN, PEN20_ZUBAEAGERMON_FQID, PEN20_ZUBAEAGERMON_FQID_LEN, PEN20_ZUBAEAGERMON_FQNAME, PEN20_ZUBAEAGERMON_FQNAME_LEN },
        { PEN20_ZUBAEAGERMON_NAME, PEN20_ZUBAEAGERMON_NAME_LEN, PEN20_ZUBAEAGERMON_ID, PEN20_ZUBAEAGERMON_ID_LEN, ALT_PEN20_ZUBAEAGERMON_FQID, ALT_PEN20_ZUBAEAGERMON_FQID_LEN, ALT_PEN20_ZUBAEAGERMON_FQNAME, ALT_PEN20_ZUBAEAGERMON_FQNAME_LEN },
        { PEN20_ZUBAMON_NAME, PEN20_ZUBAMON_NAME_LEN, PEN20_ZUBAMON_ID, PEN20_ZUBAMON_ID_LEN, PEN20_ZUBAMON_FQID, PEN20_ZUBAMON_FQID_LEN, PEN20_ZUBAMON_FQNAME, PEN20_ZUBAMON_FQNAME_LEN },
        { PEN20_ZUBAMON_NAME, PEN20_ZUBAMON_NAME_LEN, PEN20_ZUBAMON_ID, PEN20_ZUBAMON_ID_LEN, ALT_PEN20_ZUBAMON_FQID, ALT_PEN20_ZUBAMON_FQID_LEN, ALT_PEN20_ZUBAMON_FQNAME, ALT_PEN20_ZUBAMON_FQNAME_LEN },
        { PEN20_ZUDOMON_NAME, PEN20_ZUDOMON_NAME_LEN, PEN20_ZUDOMON_ID, PEN20_ZUDOMON_ID_LEN, PEN20_ZUDOMON_FQID, PEN20_ZUDOMON_FQID_LEN, PEN20_ZUDOMON_FQNAME, PEN20_ZUDOMON_FQNAME_LEN },
        { PEN20_ZUDOMON_NAME, PEN20_ZUDOMON_NAME_LEN, PEN20_ZUDOMON_ID, PEN20_ZUDOMON_ID_LEN, ALT_PEN20_ZUDOMON_FQID, ALT_PEN20_ZUDOMON_FQID_LEN, ALT_PEN20_ZUDOMON_FQNAME, ALT_PEN20_ZUDOMON_FQNAME_LEN },
        
    };
    static const size_t pen20_animation_names_table_size = LEN_ARRAY(pen20_animation_names_table);

    config_animation_entry_t get_config_animation_name_pen20(size_t index) {
        assert(LEN_ARRAY(pen20_animation_table) == PEN20_ANIM_COUNT);
        assert(index < PEN20_ANIM_COUNT);
        return pen20_animation_table[index].normal;
    }

    int config_parse_animation_name_pen20(config::config_t& config, const char *value) {
        assert(LEN_ARRAY(pen20_animation_table) == PEN20_ANIM_COUNT);
        int ret = -1;
        for (size_t i = 0;ret < 0 && i < PEN20_ANIM_COUNT;++i) {
            const auto& entry = pen20_animation_table[i].normal;
            const auto& alt = pen20_animation_table[i].alt;
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

