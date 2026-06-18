#include "embedded_assets/embedded_image.h"
#include "embedded_assets/dmall/dmall.hpp"
#include "dmall_config_parse_animation_name.h"
#include "utils/memory.h"
#include "utils/system_memory.h"

namespace bongocat::assets {
    static const config_animation_entry_t dmall_animation_table[] = {
        { DMALL_AEGISDRAMON_NAME, DMALL_AEGISDRAMON_ID, DMALL_AEGISDRAMON_FQID, DMALL_AEGISDRAMON_FQNAME, DMALL_AEGISDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_AERO_V_DRAMON_NAME, DMALL_AERO_V_DRAMON_ID, DMALL_AERO_V_DRAMON_FQID, DMALL_AERO_V_DRAMON_FQNAME, DMALL_AERO_V_DRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_AGUMON_2006_NAME, DMALL_AGUMON_2006_ID, DMALL_AGUMON_2006_FQID, DMALL_AGUMON_2006_FQNAME, DMALL_AGUMON_2006_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_AGUMON_BLACK_NAME, DMALL_AGUMON_BLACK_ID, DMALL_AGUMON_BLACK_FQID, DMALL_AGUMON_BLACK_FQNAME, DMALL_AGUMON_BLACK_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_AGUMON_BLACK_X_NAME, DMALL_AGUMON_BLACK_X_ID, DMALL_AGUMON_BLACK_X_FQID, DMALL_AGUMON_BLACK_X_FQNAME, DMALL_AGUMON_BLACK_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_AGUMON_NAME, DMALL_AGUMON_ID, DMALL_AGUMON_FQID, DMALL_AGUMON_FQNAME, DMALL_AGUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_AGUMON_X_NAME, DMALL_AGUMON_X_ID, DMALL_AGUMON_X_FQID, DMALL_AGUMON_X_FQNAME, DMALL_AGUMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_AGUMON_YUKI_NO_KIZUNA_NAME, DMALL_AGUMON_YUKI_NO_KIZUNA_ID, DMALL_AGUMON_YUKI_NO_KIZUNA_FQID, DMALL_AGUMON_YUKI_NO_KIZUNA_FQNAME, DMALL_AGUMON_YUKI_NO_KIZUNA_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_AIRDRAMON_NAME, DMALL_AIRDRAMON_ID, DMALL_AIRDRAMON_FQID, DMALL_AIRDRAMON_FQNAME, DMALL_AIRDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_ALGOMON_ADULT_NAME, DMALL_ALGOMON_ADULT_ID, DMALL_ALGOMON_ADULT_FQID, DMALL_ALGOMON_ADULT_FQNAME, DMALL_ALGOMON_ADULT_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_ALGOMON_BABYII_NAME, DMALL_ALGOMON_BABYII_ID, DMALL_ALGOMON_BABYII_FQID, DMALL_ALGOMON_BABYII_FQNAME, DMALL_ALGOMON_BABYII_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_ALGOMON_BABYI_NAME, DMALL_ALGOMON_BABYI_ID, DMALL_ALGOMON_BABYI_FQID, DMALL_ALGOMON_BABYI_FQNAME, DMALL_ALGOMON_BABYI_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_ALGOMON_CHILD_NAME, DMALL_ALGOMON_CHILD_ID, DMALL_ALGOMON_CHILD_FQID, DMALL_ALGOMON_CHILD_FQNAME, DMALL_ALGOMON_CHILD_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_ALGOMON_ULTIMATE_NAME, DMALL_ALGOMON_ULTIMATE_ID, DMALL_ALGOMON_ULTIMATE_FQID, DMALL_ALGOMON_ULTIMATE_FQNAME, DMALL_ALGOMON_ULTIMATE_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_ALLOMON_X_NAME, DMALL_ALLOMON_X_ID, DMALL_ALLOMON_X_FQID, DMALL_ALLOMON_X_FQNAME, DMALL_ALLOMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_ALPHAMON_OURYUKEN_NAME, DMALL_ALPHAMON_OURYUKEN_ID, DMALL_ALPHAMON_OURYUKEN_FQID, DMALL_ALPHAMON_OURYUKEN_FQNAME, DMALL_ALPHAMON_OURYUKEN_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_ALPHAMON_NAME, DMALL_ALPHAMON_ID, DMALL_ALPHAMON_FQID, DMALL_ALPHAMON_FQNAME, DMALL_ALPHAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_ALRAUMON_NAME, DMALL_ALRAUMON_ID, DMALL_ALRAUMON_FQID, DMALL_ALRAUMON_FQNAME, DMALL_ALRAUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_ANCIENT_BEATMON_NAME, DMALL_ANCIENT_BEATMON_ID, DMALL_ANCIENT_BEATMON_FQID, DMALL_ANCIENT_BEATMON_FQNAME, DMALL_ANCIENT_BEATMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_ANCIENT_MEGATHERIUMON_NAME, DMALL_ANCIENT_MEGATHERIUMON_ID, DMALL_ANCIENT_MEGATHERIUMON_FQID, DMALL_ANCIENT_MEGATHERIUMON_FQNAME, DMALL_ANCIENT_MEGATHERIUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_ANCIENT_MERMAIMON_NAME, DMALL_ANCIENT_MERMAIMON_ID, DMALL_ANCIENT_MERMAIMON_FQID, DMALL_ANCIENT_MERMAIMON_FQNAME, DMALL_ANCIENT_MERMAIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_ANCIENT_SPHINXMON_NAME, DMALL_ANCIENT_SPHINXMON_ID, DMALL_ANCIENT_SPHINXMON_FQID, DMALL_ANCIENT_SPHINXMON_FQNAME, DMALL_ANCIENT_SPHINXMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_ANDIRAMON_DATA_NAME, DMALL_ANDIRAMON_DATA_ID, DMALL_ANDIRAMON_DATA_FQID, DMALL_ANDIRAMON_DATA_FQNAME, DMALL_ANDIRAMON_DATA_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_ANDIRAMON_VIRUS_NAME, DMALL_ANDIRAMON_VIRUS_ID, DMALL_ANDIRAMON_VIRUS_FQID, DMALL_ANDIRAMON_VIRUS_FQNAME, DMALL_ANDIRAMON_VIRUS_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_ANDROMON_NAME, DMALL_ANDROMON_ID, DMALL_ANDROMON_FQID, DMALL_ANDROMON_FQNAME, DMALL_ANDROMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_ANGEMON_NAME, DMALL_ANGEMON_ID, DMALL_ANGEMON_FQID, DMALL_ANGEMON_FQNAME, DMALL_ANGEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_ANGEWOMON_NAME, DMALL_ANGEWOMON_ID, DMALL_ANGEWOMON_FQID, DMALL_ANGEWOMON_FQNAME, DMALL_ANGEWOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_ANGEWOMON_X_NAME, DMALL_ANGEWOMON_X_ID, DMALL_ANGEWOMON_X_FQID, DMALL_ANGEWOMON_X_FQNAME, DMALL_ANGEWOMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_ANOMALOCARIMON_NAME, DMALL_ANOMALOCARIMON_ID, DMALL_ANOMALOCARIMON_FQID, DMALL_ANOMALOCARIMON_FQNAME, DMALL_ANOMALOCARIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_ANOMALOCARIMON_X_NAME, DMALL_ANOMALOCARIMON_X_ID, DMALL_ANOMALOCARIMON_X_FQID, DMALL_ANOMALOCARIMON_X_FQNAME, DMALL_ANOMALOCARIMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_APOCALYMON_NAME, DMALL_APOCALYMON_ID, DMALL_APOCALYMON_FQID, DMALL_APOCALYMON_FQNAME, DMALL_APOCALYMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_APOLLOMON_NAME, DMALL_APOLLOMON_ID, DMALL_APOLLOMON_FQID, DMALL_APOLLOMON_FQNAME, DMALL_APOLLOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_ARCHNEMON_NAME, DMALL_ARCHNEMON_ID, DMALL_ARCHNEMON_FQID, DMALL_ARCHNEMON_FQNAME, DMALL_ARCHNEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_ARKADIMON_BABY_NAME, DMALL_ARKADIMON_BABY_ID, DMALL_ARKADIMON_BABY_FQID, DMALL_ARKADIMON_BABY_FQNAME, DMALL_ARKADIMON_BABY_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_ARKADIMON_CHILD_NAME, DMALL_ARKADIMON_CHILD_ID, DMALL_ARKADIMON_CHILD_FQID, DMALL_ARKADIMON_CHILD_FQNAME, DMALL_ARKADIMON_CHILD_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_ARMADIMON_NAME, DMALL_ARMADIMON_ID, DMALL_ARMADIMON_FQID, DMALL_ARMADIMON_FQNAME, DMALL_ARMADIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_ARMAGEMON_NAME, DMALL_ARMAGEMON_ID, DMALL_ARMAGEMON_FQID, DMALL_ARMAGEMON_FQNAME, DMALL_ARMAGEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_ASTAMON_NAME, DMALL_ASTAMON_ID, DMALL_ASTAMON_FQID, DMALL_ASTAMON_FQNAME, DMALL_ASTAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_ASURAMON_NAME, DMALL_ASURAMON_ID, DMALL_ASURAMON_FQID, DMALL_ASURAMON_FQNAME, DMALL_ASURAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_ATLUR_KABUTERIMON_BLUE_NAME, DMALL_ATLUR_KABUTERIMON_BLUE_ID, DMALL_ATLUR_KABUTERIMON_BLUE_FQID, DMALL_ATLUR_KABUTERIMON_BLUE_FQNAME, DMALL_ATLUR_KABUTERIMON_BLUE_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_ATLUR_KABUTERIMON_RED_NAME, DMALL_ATLUR_KABUTERIMON_RED_ID, DMALL_ATLUR_KABUTERIMON_RED_FQID, DMALL_ATLUR_KABUTERIMON_RED_FQNAME, DMALL_ATLUR_KABUTERIMON_RED_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_AXEKNIGHTMON_NAME, DMALL_AXEKNIGHTMON_ID, DMALL_AXEKNIGHTMON_FQID, DMALL_AXEKNIGHTMON_FQNAME, DMALL_AXEKNIGHTMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_BAALMON_NAME, DMALL_BAALMON_ID, DMALL_BAALMON_FQID, DMALL_BAALMON_FQNAME, DMALL_BAALMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_BABOONGAMON_NAME, DMALL_BABOONGAMON_ID, DMALL_BABOONGAMON_FQID, DMALL_BABOONGAMON_FQNAME, DMALL_BABOONGAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_BABYDMON_NAME, DMALL_BABYDMON_ID, DMALL_BABYDMON_FQID, DMALL_BABYDMON_FQNAME, DMALL_BABYDMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_BAGRAMON_NAME, DMALL_BAGRAMON_ID, DMALL_BAGRAMON_FQID, DMALL_BAGRAMON_FQNAME, DMALL_BAGRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_BAKEMON_NAME, DMALL_BAKEMON_ID, DMALL_BAKEMON_FQID, DMALL_BAKEMON_FQNAME, DMALL_BAKEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_BAKUMON_NAME, DMALL_BAKUMON_ID, DMALL_BAKUMON_FQID, DMALL_BAKUMON_FQNAME, DMALL_BAKUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_BANCHO_LEOMON_NAME, DMALL_BANCHO_LEOMON_ID, DMALL_BANCHO_LEOMON_FQID, DMALL_BANCHO_LEOMON_FQNAME, DMALL_BANCHO_LEOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_BANCHO_LILIMON_NAME, DMALL_BANCHO_LILIMON_ID, DMALL_BANCHO_LILIMON_FQID, DMALL_BANCHO_LILIMON_FQNAME, DMALL_BANCHO_LILIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_BANCHO_MAMEMON_NAME, DMALL_BANCHO_MAMEMON_ID, DMALL_BANCHO_MAMEMON_FQID, DMALL_BANCHO_MAMEMON_FQNAME, DMALL_BANCHO_MAMEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_BARBAMON_NAME, DMALL_BARBAMON_ID, DMALL_BARBAMON_FQID, DMALL_BARBAMON_FQNAME, DMALL_BARBAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_BARBAMON_X_NAME, DMALL_BARBAMON_X_ID, DMALL_BARBAMON_X_FQID, DMALL_BARBAMON_X_FQNAME, DMALL_BARBAMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_BEARMON_NAME, DMALL_BEARMON_ID, DMALL_BEARMON_FQID, DMALL_BEARMON_FQNAME, DMALL_BEARMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_BEEL_STARMON_X_NAME, DMALL_BEEL_STARMON_X_ID, DMALL_BEEL_STARMON_X_FQID, DMALL_BEEL_STARMON_X_FQNAME, DMALL_BEEL_STARMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_BEELZEBUMON_BLAST_MODE_NAME, DMALL_BEELZEBUMON_BLAST_MODE_ID, DMALL_BEELZEBUMON_BLAST_MODE_FQID, DMALL_BEELZEBUMON_BLAST_MODE_FQNAME, DMALL_BEELZEBUMON_BLAST_MODE_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_BEELZEBUMON_NAME, DMALL_BEELZEBUMON_ID, DMALL_BEELZEBUMON_FQID, DMALL_BEELZEBUMON_FQNAME, DMALL_BEELZEBUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_BEELZEBUMON_X_NAME, DMALL_BEELZEBUMON_X_ID, DMALL_BEELZEBUMON_X_FQID, DMALL_BEELZEBUMON_X_FQNAME, DMALL_BEELZEBUMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_BELIAL_VAMDEMON_NAME, DMALL_BELIAL_VAMDEMON_ID, DMALL_BELIAL_VAMDEMON_FQID, DMALL_BELIAL_VAMDEMON_FQNAME, DMALL_BELIAL_VAMDEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_BELPHEMON_RAGE_MODE_NAME, DMALL_BELPHEMON_RAGE_MODE_ID, DMALL_BELPHEMON_RAGE_MODE_FQID, DMALL_BELPHEMON_RAGE_MODE_FQNAME, DMALL_BELPHEMON_RAGE_MODE_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_BELPHEMON_X_NAME, DMALL_BELPHEMON_X_ID, DMALL_BELPHEMON_X_FQID, DMALL_BELPHEMON_X_FQNAME, DMALL_BELPHEMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_BEOWOLFMON_NAME, DMALL_BEOWOLFMON_ID, DMALL_BEOWOLFMON_FQID, DMALL_BEOWOLFMON_FQNAME, DMALL_BEOWOLFMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_BIBIMON_NAME, DMALL_BIBIMON_ID, DMALL_BIBIMON_FQID, DMALL_BIBIMON_FQNAME, DMALL_BIBIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_BIG_MAMEMON_NAME, DMALL_BIG_MAMEMON_ID, DMALL_BIG_MAMEMON_FQID, DMALL_BIG_MAMEMON_FQNAME, DMALL_BIG_MAMEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_BIRDRAMON_NAME, DMALL_BIRDRAMON_ID, DMALL_BIRDRAMON_FQID, DMALL_BIRDRAMON_FQNAME, DMALL_BIRDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_BITMON_NAME, DMALL_BITMON_ID, DMALL_BITMON_FQID, DMALL_BITMON_FQNAME, DMALL_BITMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_BLACK_GALGOMON_NAME, DMALL_BLACK_GALGOMON_ID, DMALL_BLACK_GALGOMON_FQID, DMALL_BLACK_GALGOMON_FQNAME, DMALL_BLACK_GALGOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_BLACK_GAOGAMON_NAME, DMALL_BLACK_GAOGAMON_ID, DMALL_BLACK_GAOGAMON_FQID, DMALL_BLACK_GAOGAMON_FQNAME, DMALL_BLACK_GAOGAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_BLACK_GROWMON_NAME, DMALL_BLACK_GROWMON_ID, DMALL_BLACK_GROWMON_FQID, DMALL_BLACK_GROWMON_FQNAME, DMALL_BLACK_GROWMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_BLACK_GUILMON_NAME, DMALL_BLACK_GUILMON_ID, DMALL_BLACK_GUILMON_FQID, DMALL_BLACK_GUILMON_FQNAME, DMALL_BLACK_GUILMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_BLACK_KING_NUMEMON_NAME, DMALL_BLACK_KING_NUMEMON_ID, DMALL_BLACK_KING_NUMEMON_FQID, DMALL_BLACK_KING_NUMEMON_FQNAME, DMALL_BLACK_KING_NUMEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_BLACK_MACH_GAOGAMON_NAME, DMALL_BLACK_MACH_GAOGAMON_ID, DMALL_BLACK_MACH_GAOGAMON_FQID, DMALL_BLACK_MACH_GAOGAMON_FQNAME, DMALL_BLACK_MACH_GAOGAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_BLACK_MEGALO_GROWMON_NAME, DMALL_BLACK_MEGALO_GROWMON_ID, DMALL_BLACK_MEGALO_GROWMON_FQID, DMALL_BLACK_MEGALO_GROWMON_FQNAME, DMALL_BLACK_MEGALO_GROWMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_BLACK_RAPIDMON_NAME, DMALL_BLACK_RAPIDMON_ID, DMALL_BLACK_RAPIDMON_FQID, DMALL_BLACK_RAPIDMON_FQNAME, DMALL_BLACK_RAPIDMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_BLACK_SAINT_GALGOMON_NAME, DMALL_BLACK_SAINT_GALGOMON_ID, DMALL_BLACK_SAINT_GALGOMON_FQID, DMALL_BLACK_SAINT_GALGOMON_FQNAME, DMALL_BLACK_SAINT_GALGOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_BLACK_SERAPHIMON_NAME, DMALL_BLACK_SERAPHIMON_ID, DMALL_BLACK_SERAPHIMON_FQID, DMALL_BLACK_SERAPHIMON_FQNAME, DMALL_BLACK_SERAPHIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_BLACK_TAILMON_NAME, DMALL_BLACK_TAILMON_ID, DMALL_BLACK_TAILMON_FQID, DMALL_BLACK_TAILMON_FQNAME, DMALL_BLACK_TAILMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_BLACK_WAR_GREYMON_NAME, DMALL_BLACK_WAR_GREYMON_ID, DMALL_BLACK_WAR_GREYMON_FQID, DMALL_BLACK_WAR_GREYMON_FQNAME, DMALL_BLACK_WAR_GREYMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_BLACK_WAR_GREYMON_X_NAME, DMALL_BLACK_WAR_GREYMON_X_ID, DMALL_BLACK_WAR_GREYMON_X_FQID, DMALL_BLACK_WAR_GREYMON_X_FQNAME, DMALL_BLACK_WAR_GREYMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_BLITZ_GREYMON_NAME, DMALL_BLITZ_GREYMON_ID, DMALL_BLITZ_GREYMON_FQID, DMALL_BLITZ_GREYMON_FQNAME, DMALL_BLITZ_GREYMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_BLOOM_LORDMON_NAME, DMALL_BLOOM_LORDMON_ID, DMALL_BLOOM_LORDMON_FQID, DMALL_BLOOM_LORDMON_FQNAME, DMALL_BLOOM_LORDMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_BLOSSOMON_NAME, DMALL_BLOSSOMON_ID, DMALL_BLOSSOMON_FQID, DMALL_BLOSSOMON_FQNAME, DMALL_BLOSSOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_BLUCOMON_NAME, DMALL_BLUCOMON_ID, DMALL_BLUCOMON_FQID, DMALL_BLUCOMON_FQNAME, DMALL_BLUCOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_BLUE_MERAMON_NAME, DMALL_BLUE_MERAMON_ID, DMALL_BLUE_MERAMON_FQID, DMALL_BLUE_MERAMON_FQNAME, DMALL_BLUE_MERAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_BOLTMON_NAME, DMALL_BOLTMON_ID, DMALL_BOLTMON_FQID, DMALL_BOLTMON_FQNAME, DMALL_BOLTMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_BOMBMON_NAME, DMALL_BOMBMON_ID, DMALL_BOMBMON_FQID, DMALL_BOMBMON_FQNAME, DMALL_BOMBMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_BOMMON_NAME, DMALL_BOMMON_ID, DMALL_BOMMON_FQID, DMALL_BOMMON_FQNAME, DMALL_BOMMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_BOUTMON_NAME, DMALL_BOUTMON_ID, DMALL_BOUTMON_FQID, DMALL_BOUTMON_FQNAME, DMALL_BOUTMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_BRYWELUDRAMON_NAME, DMALL_BRYWELUDRAMON_ID, DMALL_BRYWELUDRAMON_FQID, DMALL_BRYWELUDRAMON_FQNAME, DMALL_BRYWELUDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_BUBBMON_NAME, DMALL_BUBBMON_ID, DMALL_BUBBMON_FQID, DMALL_BUBBMON_FQNAME, DMALL_BUBBMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_BUDMON_NAME, DMALL_BUDMON_ID, DMALL_BUDMON_FQID, DMALL_BUDMON_FQNAME, DMALL_BUDMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_BURGERMON_MAMA_NAME, DMALL_BURGERMON_MAMA_ID, DMALL_BURGERMON_MAMA_FQID, DMALL_BURGERMON_MAMA_FQNAME, DMALL_BURGERMON_MAMA_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_BURGERMON_PAPA_NAME, DMALL_BURGERMON_PAPA_ID, DMALL_BURGERMON_PAPA_FQID, DMALL_BURGERMON_PAPA_FQNAME, DMALL_BURGERMON_PAPA_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_CANDMON_NAME, DMALL_CANDMON_ID, DMALL_CANDMON_FQID, DMALL_CANDMON_FQNAME, DMALL_CANDMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_CANNONBEEMON_NAME, DMALL_CANNONBEEMON_ID, DMALL_CANNONBEEMON_FQID, DMALL_CANNONBEEMON_FQNAME, DMALL_CANNONBEEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_CAPRIMON_NAME, DMALL_CAPRIMON_ID, DMALL_CAPRIMON_FQID, DMALL_CAPRIMON_FQNAME, DMALL_CAPRIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_CATCHMAMEMON_NAME, DMALL_CATCHMAMEMON_ID, DMALL_CATCHMAMEMON_FQID, DMALL_CATCHMAMEMON_FQNAME, DMALL_CATCHMAMEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_CATURAMON_NAME, DMALL_CATURAMON_ID, DMALL_CATURAMON_FQID, DMALL_CATURAMON_FQNAME, DMALL_CATURAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_CENTALMON_NAME, DMALL_CENTALMON_ID, DMALL_CENTALMON_FQID, DMALL_CENTALMON_FQNAME, DMALL_CENTALMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_CERBERUMON_X_NAME, DMALL_CERBERUMON_X_ID, DMALL_CERBERUMON_X_FQID, DMALL_CERBERUMON_X_FQNAME, DMALL_CERBERUMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_CHAMBLEMON_NAME, DMALL_CHAMBLEMON_ID, DMALL_CHAMBLEMON_FQID, DMALL_CHAMBLEMON_FQNAME, DMALL_CHAMBLEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_CHAOSDRAMON_NAME, DMALL_CHAOSDRAMON_ID, DMALL_CHAOSDRAMON_FQID, DMALL_CHAOSDRAMON_FQNAME, DMALL_CHAOSDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_CHAOSDRAMON_X_NAME, DMALL_CHAOSDRAMON_X_ID, DMALL_CHAOSDRAMON_X_FQID, DMALL_CHAOSDRAMON_X_FQNAME, DMALL_CHAOSDRAMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_CHAOS_DUKEMON_CORE_NAME, DMALL_CHAOS_DUKEMON_CORE_ID, DMALL_CHAOS_DUKEMON_CORE_FQID, DMALL_CHAOS_DUKEMON_CORE_FQNAME, DMALL_CHAOS_DUKEMON_CORE_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_CHAOS_DUKEMON_NAME, DMALL_CHAOS_DUKEMON_ID, DMALL_CHAOS_DUKEMON_FQID, DMALL_CHAOS_DUKEMON_FQNAME, DMALL_CHAOS_DUKEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_CHAOSMON_NAME, DMALL_CHAOSMON_ID, DMALL_CHAOSMON_FQID, DMALL_CHAOSMON_FQNAME, DMALL_CHAOSMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_CHERUBIMON_VICE_NAME, DMALL_CHERUBIMON_VICE_ID, DMALL_CHERUBIMON_VICE_FQID, DMALL_CHERUBIMON_VICE_FQNAME, DMALL_CHERUBIMON_VICE_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_CHERUBIMON_VICE_X_NAME, DMALL_CHERUBIMON_VICE_X_ID, DMALL_CHERUBIMON_VICE_X_FQID, DMALL_CHERUBIMON_VICE_X_FQNAME, DMALL_CHERUBIMON_VICE_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_CHERUBIMON_VIRTUE_NAME, DMALL_CHERUBIMON_VIRTUE_ID, DMALL_CHERUBIMON_VIRTUE_FQID, DMALL_CHERUBIMON_VIRTUE_FQNAME, DMALL_CHERUBIMON_VIRTUE_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_CHERUBIMON_VIRTUE_X_NAME, DMALL_CHERUBIMON_VIRTUE_X_ID, DMALL_CHERUBIMON_VIRTUE_X_FQID, DMALL_CHERUBIMON_VIRTUE_X_FQNAME, DMALL_CHERUBIMON_VIRTUE_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_CHIBICKMON_NAME, DMALL_CHIBICKMON_ID, DMALL_CHIBICKMON_FQID, DMALL_CHIBICKMON_FQNAME, DMALL_CHIBICKMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_CHIBIMON_NAME, DMALL_CHIBIMON_ID, DMALL_CHIBIMON_FQID, DMALL_CHIBIMON_FQNAME, DMALL_CHIBIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_CHICCHIMON_NAME, DMALL_CHICCHIMON_ID, DMALL_CHICCHIMON_FQID, DMALL_CHICCHIMON_FQNAME, DMALL_CHICCHIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_CHICOMON_NAME, DMALL_CHICOMON_ID, DMALL_CHICOMON_FQID, DMALL_CHICOMON_FQNAME, DMALL_CHICOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_CHIMAIRAMON_NAME, DMALL_CHIMAIRAMON_ID, DMALL_CHIMAIRAMON_FQID, DMALL_CHIMAIRAMON_FQNAME, DMALL_CHIMAIRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_CHOCOMON_NAME, DMALL_CHOCOMON_ID, DMALL_CHOCOMON_FQID, DMALL_CHOCOMON_FQNAME, DMALL_CHOCOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_CHO_HAKKAIMON_NAME, DMALL_CHO_HAKKAIMON_ID, DMALL_CHO_HAKKAIMON_FQID, DMALL_CHO_HAKKAIMON_FQNAME, DMALL_CHO_HAKKAIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_CHOROMON_NAME, DMALL_CHOROMON_ID, DMALL_CHOROMON_FQID, DMALL_CHOROMON_FQNAME, DMALL_CHOROMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_CLEAR_AGUMON_NAME, DMALL_CLEAR_AGUMON_ID, DMALL_CLEAR_AGUMON_FQID, DMALL_CLEAR_AGUMON_FQNAME, DMALL_CLEAR_AGUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_CLOCKMON_NAME, DMALL_CLOCKMON_ID, DMALL_CLOCKMON_FQID, DMALL_CLOCKMON_FQNAME, DMALL_CLOCKMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_COCOMON_NAME, DMALL_COCOMON_ID, DMALL_COCOMON_FQID, DMALL_COCOMON_FQNAME, DMALL_COCOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_COELAMON_NAME, DMALL_COELAMON_ID, DMALL_COELAMON_FQID, DMALL_COELAMON_FQNAME, DMALL_COELAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_COMMANDRAMON_NAME, DMALL_COMMANDRAMON_ID, DMALL_COMMANDRAMON_FQID, DMALL_COMMANDRAMON_FQNAME, DMALL_COMMANDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_CORONAMON_NAME, DMALL_CORONAMON_ID, DMALL_CORONAMON_FQID, DMALL_CORONAMON_FQNAME, DMALL_CORONAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_COTSUCOMON_NAME, DMALL_COTSUCOMON_ID, DMALL_COTSUCOMON_FQID, DMALL_COTSUCOMON_FQNAME, DMALL_COTSUCOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_CRANIUMMON_NAME, DMALL_CRANIUMMON_ID, DMALL_CRANIUMMON_FQID, DMALL_CRANIUMMON_FQNAME, DMALL_CRANIUMMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_CRANIUMMON_X_NAME, DMALL_CRANIUMMON_X_ID, DMALL_CRANIUMMON_X_FQID, DMALL_CRANIUMMON_X_FQNAME, DMALL_CRANIUMMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_CRESCEMON_NAME, DMALL_CRESCEMON_ID, DMALL_CRESCEMON_FQID, DMALL_CRESCEMON_FQNAME, DMALL_CRESCEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_CRES_GARURUMON_NAME, DMALL_CRES_GARURUMON_ID, DMALL_CRES_GARURUMON_FQID, DMALL_CRES_GARURUMON_FQNAME, DMALL_CRES_GARURUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_CRYS_PALEDRAMON_NAME, DMALL_CRYS_PALEDRAMON_ID, DMALL_CRYS_PALEDRAMON_FQID, DMALL_CRYS_PALEDRAMON_FQNAME, DMALL_CRYS_PALEDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_CTHYLLAMON_NAME, DMALL_CTHYLLAMON_ID, DMALL_CTHYLLAMON_FQID, DMALL_CTHYLLAMON_FQNAME, DMALL_CTHYLLAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_CUPIMON_NAME, DMALL_CUPIMON_ID, DMALL_CUPIMON_FQID, DMALL_CUPIMON_FQNAME, DMALL_CUPIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_CURIMON_NAME, DMALL_CURIMON_ID, DMALL_CURIMON_FQID, DMALL_CURIMON_FQNAME, DMALL_CURIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_CYBERDRAMON_NAME, DMALL_CYBERDRAMON_ID, DMALL_CYBERDRAMON_FQID, DMALL_CYBERDRAMON_FQNAME, DMALL_CYBERDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_CYBERDRAMON_X_NAME, DMALL_CYBERDRAMON_X_ID, DMALL_CYBERDRAMON_X_FQID, DMALL_CYBERDRAMON_X_FQNAME, DMALL_CYBERDRAMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_CYCLOMON_NAME, DMALL_CYCLOMON_ID, DMALL_CYCLOMON_FQID, DMALL_CYCLOMON_FQNAME, DMALL_CYCLOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_DAGOMON_NAME, DMALL_DAGOMON_ID, DMALL_DAGOMON_FQID, DMALL_DAGOMON_FQNAME, DMALL_DAGOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_DAMEMON_NAME, DMALL_DAMEMON_ID, DMALL_DAMEMON_FQID, DMALL_DAMEMON_FQNAME, DMALL_DAMEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_DARKDRAMON_NAME, DMALL_DARKDRAMON_ID, DMALL_DARKDRAMON_FQID, DMALL_DARKDRAMON_FQNAME, DMALL_DARKDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_DARK_KNIGHTMON_NAME, DMALL_DARK_KNIGHTMON_ID, DMALL_DARK_KNIGHTMON_FQID, DMALL_DARK_KNIGHTMON_FQNAME, DMALL_DARK_KNIGHTMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_DARKNESS_BAGRAMON_NAME, DMALL_DARKNESS_BAGRAMON_ID, DMALL_DARKNESS_BAGRAMON_FQID, DMALL_DARKNESS_BAGRAMON_FQNAME, DMALL_DARKNESS_BAGRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_DARK_SUPERSTARMON_NAME, DMALL_DARK_SUPERSTARMON_ID, DMALL_DARK_SUPERSTARMON_FQID, DMALL_DARK_SUPERSTARMON_FQNAME, DMALL_DARK_SUPERSTARMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_DARK_TYRANOMON_X_NAME, DMALL_DARK_TYRANOMON_X_ID, DMALL_DARK_TYRANOMON_X_FQID, DMALL_DARK_TYRANOMON_X_FQNAME, DMALL_DARK_TYRANOMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_DEATH_MERAMON_NAME, DMALL_DEATH_MERAMON_ID, DMALL_DEATH_MERAMON_FQID, DMALL_DEATH_MERAMON_FQNAME, DMALL_DEATH_MERAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_DEATHMON_BLACK_NAME, DMALL_DEATHMON_BLACK_ID, DMALL_DEATHMON_BLACK_FQID, DMALL_DEATHMON_BLACK_FQNAME, DMALL_DEATHMON_BLACK_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_DEATHMON_NAME, DMALL_DEATHMON_ID, DMALL_DEATHMON_FQID, DMALL_DEATHMON_FQNAME, DMALL_DEATHMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_DEATH_X_DORUGAMON_NAME, DMALL_DEATH_X_DORUGAMON_ID, DMALL_DEATH_X_DORUGAMON_FQID, DMALL_DEATH_X_DORUGAMON_FQNAME, DMALL_DEATH_X_DORUGAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_DELUMON_NAME, DMALL_DELUMON_ID, DMALL_DELUMON_FQID, DMALL_DELUMON_FQNAME, DMALL_DELUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_DEMON_NAME, DMALL_DEMON_ID, DMALL_DEMON_FQID, DMALL_DEMON_FQNAME, DMALL_DEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_DEMON_X_NAME, DMALL_DEMON_X_ID, DMALL_DEMON_X_FQID, DMALL_DEMON_X_FQNAME, DMALL_DEMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_DEVIMON_NAME, DMALL_DEVIMON_ID, DMALL_DEVIMON_FQID, DMALL_DEVIMON_FQNAME, DMALL_DEVIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_DIABLOMON_NAME, DMALL_DIABLOMON_ID, DMALL_DIABLOMON_FQID, DMALL_DIABLOMON_FQNAME, DMALL_DIABLOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_DIABLOMON_X_NAME, DMALL_DIABLOMON_X_ID, DMALL_DIABLOMON_X_FQID, DMALL_DIABLOMON_X_FQNAME, DMALL_DIABLOMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_DIANAMON_NAME, DMALL_DIANAMON_ID, DMALL_DIANAMON_FQID, DMALL_DIANAMON_FQNAME, DMALL_DIANAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_DIGINORIMON_NAME, DMALL_DIGINORIMON_ID, DMALL_DIGINORIMON_FQID, DMALL_DIGINORIMON_FQNAME, DMALL_DIGINORIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_DIGITAMAMON_NAME, DMALL_DIGITAMAMON_ID, DMALL_DIGITAMAMON_FQID, DMALL_DIGITAMAMON_FQNAME, DMALL_DIGITAMAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_DINOHUMON_NAME, DMALL_DINOHUMON_ID, DMALL_DINOHUMON_FQID, DMALL_DINOHUMON_FQNAME, DMALL_DINOHUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_DINOREXMON_NAME, DMALL_DINOREXMON_ID, DMALL_DINOREXMON_FQID, DMALL_DINOREXMON_FQNAME, DMALL_DINOREXMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_DINOTIGERMON_NAME, DMALL_DINOTIGERMON_ID, DMALL_DINOTIGERMON_FQID, DMALL_DINOTIGERMON_FQNAME, DMALL_DINOTIGERMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_DOBERMON_NAME, DMALL_DOBERMON_ID, DMALL_DOBERMON_FQID, DMALL_DOBERMON_FQNAME, DMALL_DOBERMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_DODOMON_NAME, DMALL_DODOMON_ID, DMALL_DODOMON_FQID, DMALL_DODOMON_FQNAME, DMALL_DODOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_DOGMON_NAME, DMALL_DOGMON_ID, DMALL_DOGMON_FQID, DMALL_DOGMON_FQNAME, DMALL_DOGMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_DOKIMON_NAME, DMALL_DOKIMON_ID, DMALL_DOKIMON_FQID, DMALL_DOKIMON_FQNAME, DMALL_DOKIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_DOKUGUMON_NAME, DMALL_DOKUGUMON_ID, DMALL_DOKUGUMON_FQID, DMALL_DOKUGUMON_FQNAME, DMALL_DOKUGUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_DOKUNEMON_NAME, DMALL_DOKUNEMON_ID, DMALL_DOKUNEMON_FQID, DMALL_DOKUNEMON_FQNAME, DMALL_DOKUNEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_DORIMON_NAME, DMALL_DORIMON_ID, DMALL_DORIMON_FQID, DMALL_DORIMON_FQNAME, DMALL_DORIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_DORUGAMON_NAME, DMALL_DORUGAMON_ID, DMALL_DORUGAMON_FQID, DMALL_DORUGAMON_FQNAME, DMALL_DORUGAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_DORUGORAMON_NAME, DMALL_DORUGORAMON_ID, DMALL_DORUGORAMON_FQID, DMALL_DORUGORAMON_FQNAME, DMALL_DORUGORAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_DORUGUREMON_NAME, DMALL_DORUGUREMON_ID, DMALL_DORUGUREMON_FQID, DMALL_DORUGUREMON_FQNAME, DMALL_DORUGUREMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_DORUMON_NAME, DMALL_DORUMON_ID, DMALL_DORUMON_FQID, DMALL_DORUMON_FQNAME, DMALL_DORUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_DRACOMON_X_NAME, DMALL_DRACOMON_X_ID, DMALL_DRACOMON_X_FQID, DMALL_DRACOMON_X_FQNAME, DMALL_DRACOMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_DRACUMON_NAME, DMALL_DRACUMON_ID, DMALL_DRACUMON_FQID, DMALL_DRACUMON_FQNAME, DMALL_DRACUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_DRIMOGEMON_NAME, DMALL_DRIMOGEMON_ID, DMALL_DRIMOGEMON_FQID, DMALL_DRIMOGEMON_FQNAME, DMALL_DRIMOGEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_DUFTMON_NAME, DMALL_DUFTMON_ID, DMALL_DUFTMON_FQID, DMALL_DUFTMON_FQNAME, DMALL_DUFTMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_DUFTMON_X_NAME, DMALL_DUFTMON_X_ID, DMALL_DUFTMON_X_FQID, DMALL_DUFTMON_X_FQNAME, DMALL_DUFTMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_DUKEMON_NAME, DMALL_DUKEMON_ID, DMALL_DUKEMON_FQID, DMALL_DUKEMON_FQNAME, DMALL_DUKEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_DUKEMON_X_NAME, DMALL_DUKEMON_X_ID, DMALL_DUKEMON_X_FQID, DMALL_DUKEMON_X_FQNAME, DMALL_DUKEMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_DURAMON_NAME, DMALL_DURAMON_ID, DMALL_DURAMON_FQID, DMALL_DURAMON_FQNAME, DMALL_DURAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_DUSKMON_NAME, DMALL_DUSKMON_ID, DMALL_DUSKMON_FQID, DMALL_DUSKMON_FQNAME, DMALL_DUSKMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_DYNASMON_X_NAME, DMALL_DYNASMON_X_ID, DMALL_DYNASMON_X_FQID, DMALL_DYNASMON_X_FQNAME, DMALL_DYNASMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_EBEMON_NAME, DMALL_EBEMON_ID, DMALL_EBEMON_FQID, DMALL_EBEMON_FQNAME, DMALL_EBEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_EBEMON_X_NAME, DMALL_EBEMON_X_ID, DMALL_EBEMON_X_FQID, DMALL_EBEMON_X_FQNAME, DMALL_EBEMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_EBIDRAMON_NAME, DMALL_EBIDRAMON_ID, DMALL_EBIDRAMON_FQID, DMALL_EBIDRAMON_FQNAME, DMALL_EBIDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_EKAKIMON_NAME, DMALL_EKAKIMON_ID, DMALL_EKAKIMON_FQID, DMALL_EKAKIMON_FQNAME, DMALL_EKAKIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_ELECMON_NAME, DMALL_ELECMON_ID, DMALL_ELECMON_FQID, DMALL_ELECMON_FQNAME, DMALL_ELECMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_ELECMON_VIOLET_NAME, DMALL_ELECMON_VIOLET_ID, DMALL_ELECMON_VIOLET_FQID, DMALL_ELECMON_VIOLET_FQNAME, DMALL_ELECMON_VIOLET_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_ENTMON_NAME, DMALL_ENTMON_ID, DMALL_ENTMON_FQID, DMALL_ENTMON_FQNAME, DMALL_ENTMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_ETEMON_NAME, DMALL_ETEMON_ID, DMALL_ETEMON_FQID, DMALL_ETEMON_FQNAME, DMALL_ETEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_EXAMON_X_NAME, DMALL_EXAMON_X_ID, DMALL_EXAMON_X_FQID, DMALL_EXAMON_X_FQNAME, DMALL_EXAMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_FILMON_NAME, DMALL_FILMON_ID, DMALL_FILMON_FQID, DMALL_FILMON_FQNAME, DMALL_FILMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_FIRAMON_NAME, DMALL_FIRAMON_ID, DMALL_FIRAMON_FQID, DMALL_FIRAMON_FQNAME, DMALL_FIRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_FLAREMON_NAME, DMALL_FLAREMON_ID, DMALL_FLAREMON_FQID, DMALL_FLAREMON_FQNAME, DMALL_FLAREMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_FLORAMON_NAME, DMALL_FLORAMON_ID, DMALL_FLORAMON_FQID, DMALL_FLORAMON_FQNAME, DMALL_FLORAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_FUFUMON_NAME, DMALL_FUFUMON_ID, DMALL_FUFUMON_FQID, DMALL_FUFUMON_FQNAME, DMALL_FUFUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_FUGAMON_NAME, DMALL_FUGAMON_ID, DMALL_FUGAMON_FQID, DMALL_FUGAMON_FQNAME, DMALL_FUGAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_FUNBEEMON_NAME, DMALL_FUNBEEMON_ID, DMALL_FUNBEEMON_FQID, DMALL_FUNBEEMON_FQNAME, DMALL_FUNBEEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_GABUMON_X_NAME, DMALL_GABUMON_X_ID, DMALL_GABUMON_X_FQID, DMALL_GABUMON_X_FQNAME, DMALL_GABUMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_GAIOUMON_NAME, DMALL_GAIOUMON_ID, DMALL_GAIOUMON_FQID, DMALL_GAIOUMON_FQNAME, DMALL_GAIOUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_GALGOMON_NAME, DMALL_GALGOMON_ID, DMALL_GALGOMON_FQID, DMALL_GALGOMON_FQNAME, DMALL_GALGOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_GAMMAMON_NAME, DMALL_GAMMAMON_ID, DMALL_GAMMAMON_FQID, DMALL_GAMMAMON_FQNAME, DMALL_GAMMAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_GANIMON_NAME, DMALL_GANIMON_ID, DMALL_GANIMON_FQID, DMALL_GANIMON_FQNAME, DMALL_GANIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_GANKOOMON_NAME, DMALL_GANKOOMON_ID, DMALL_GANKOOMON_FQID, DMALL_GANKOOMON_FQNAME, DMALL_GANKOOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_GANKOOMON_X_NAME, DMALL_GANKOOMON_X_ID, DMALL_GANKOOMON_X_FQID, DMALL_GANKOOMON_X_FQNAME, DMALL_GANKOOMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_GAOGAMON_NAME, DMALL_GAOGAMON_ID, DMALL_GAOGAMON_FQID, DMALL_GAOGAMON_FQNAME, DMALL_GAOGAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_GAOMON_NAME, DMALL_GAOMON_ID, DMALL_GAOMON_FQID, DMALL_GAOMON_FQNAME, DMALL_GAOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_GARUDAMON_NAME, DMALL_GARUDAMON_ID, DMALL_GARUDAMON_FQID, DMALL_GARUDAMON_FQNAME, DMALL_GARUDAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_GARUDAMON_X_NAME, DMALL_GARUDAMON_X_ID, DMALL_GARUDAMON_X_FQID, DMALL_GARUDAMON_X_FQNAME, DMALL_GARUDAMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_GARURUMON_BLACK_NAME, DMALL_GARURUMON_BLACK_ID, DMALL_GARURUMON_BLACK_FQID, DMALL_GARURUMON_BLACK_FQNAME, DMALL_GARURUMON_BLACK_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_GARURUMON_NAME, DMALL_GARURUMON_ID, DMALL_GARURUMON_FQID, DMALL_GARURUMON_FQNAME, DMALL_GARURUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_GAWAPPAMON_NAME, DMALL_GAWAPPAMON_ID, DMALL_GAWAPPAMON_FQID, DMALL_GAWAPPAMON_FQNAME, DMALL_GAWAPPAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_GAZIMON_NAME, DMALL_GAZIMON_ID, DMALL_GAZIMON_FQID, DMALL_GAZIMON_FQNAME, DMALL_GAZIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_GAZIMON_X_NAME, DMALL_GAZIMON_X_ID, DMALL_GAZIMON_X_FQID, DMALL_GAZIMON_X_FQNAME, DMALL_GAZIMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_GEKOMON_NAME, DMALL_GEKOMON_ID, DMALL_GEKOMON_FQID, DMALL_GEKOMON_FQNAME, DMALL_GEKOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_GEO_GREYMON_NAME, DMALL_GEO_GREYMON_ID, DMALL_GEO_GREYMON_FQID, DMALL_GEO_GREYMON_FQNAME, DMALL_GEO_GREYMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_GERBEMON_NAME, DMALL_GERBEMON_ID, DMALL_GERBEMON_FQID, DMALL_GERBEMON_FQNAME, DMALL_GERBEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_GEREMON_NAME, DMALL_GEREMON_ID, DMALL_GEREMON_FQID, DMALL_GEREMON_FQNAME, DMALL_GEREMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_GESOMON_NAME, DMALL_GESOMON_ID, DMALL_GESOMON_FQID, DMALL_GESOMON_FQNAME, DMALL_GESOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_GHOSTMON_NAME, DMALL_GHOSTMON_ID, DMALL_GHOSTMON_FQID, DMALL_GHOSTMON_FQNAME, DMALL_GHOSTMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_GIGADRAMON_NAME, DMALL_GIGADRAMON_ID, DMALL_GIGADRAMON_FQID, DMALL_GIGADRAMON_FQNAME, DMALL_GIGADRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_GIGA_SEADRAMON_NAME, DMALL_GIGA_SEADRAMON_ID, DMALL_GIGA_SEADRAMON_FQID, DMALL_GIGA_SEADRAMON_FQNAME, DMALL_GIGA_SEADRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_GIGIMON_NAME, DMALL_GIGIMON_ID, DMALL_GIGIMON_FQID, DMALL_GIGIMON_FQNAME, DMALL_GIGIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_GINRYUMON_NAME, DMALL_GINRYUMON_ID, DMALL_GINRYUMON_FQID, DMALL_GINRYUMON_FQNAME, DMALL_GINRYUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_GIROMON_NAME, DMALL_GIROMON_ID, DMALL_GIROMON_FQID, DMALL_GIROMON_FQNAME, DMALL_GIROMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_GIZAMON_NAME, DMALL_GIZAMON_ID, DMALL_GIZAMON_FQID, DMALL_GIZAMON_FQNAME, DMALL_GIZAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_GODDRAMON_X_NAME, DMALL_GODDRAMON_X_ID, DMALL_GODDRAMON_X_FQID, DMALL_GODDRAMON_X_FQNAME, DMALL_GODDRAMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_GOGMAMON_NAME, DMALL_GOGMAMON_ID, DMALL_GOGMAMON_FQID, DMALL_GOGMAMON_FQNAME, DMALL_GOGMAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_GOKIMON_NAME, DMALL_GOKIMON_ID, DMALL_GOKIMON_FQID, DMALL_GOKIMON_FQNAME, DMALL_GOKIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_GOKUMON_NAME, DMALL_GOKUMON_ID, DMALL_GOKUMON_FQID, DMALL_GOKUMON_FQNAME, DMALL_GOKUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_GOLD_NUMEMON_NAME, DMALL_GOLD_NUMEMON_ID, DMALL_GOLD_NUMEMON_FQID, DMALL_GOLD_NUMEMON_FQNAME, DMALL_GOLD_NUMEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_GOLD_V_DRAMON_NAME, DMALL_GOLD_V_DRAMON_ID, DMALL_GOLD_V_DRAMON_FQID, DMALL_GOLD_V_DRAMON_FQNAME, DMALL_GOLD_V_DRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_GOMAMON_NAME, DMALL_GOMAMON_ID, DMALL_GOMAMON_FQID, DMALL_GOMAMON_FQNAME, DMALL_GOMAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_GOMAMON_X_NAME, DMALL_GOMAMON_X_ID, DMALL_GOMAMON_X_FQID, DMALL_GOMAMON_X_FQNAME, DMALL_GOMAMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_GOROMON_NAME, DMALL_GOROMON_ID, DMALL_GOROMON_FQID, DMALL_GOROMON_FQNAME, DMALL_GOROMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_GOTSUMON_NAME, DMALL_GOTSUMON_ID, DMALL_GOTSUMON_FQID, DMALL_GOTSUMON_FQNAME, DMALL_GOTSUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_GRACE_NOVAMON_NAME, DMALL_GRACE_NOVAMON_ID, DMALL_GRACE_NOVAMON_FQID, DMALL_GRACE_NOVAMON_FQNAME, DMALL_GRACE_NOVAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_GRADEMON_NAME, DMALL_GRADEMON_ID, DMALL_GRADEMON_FQID, DMALL_GRADEMON_FQNAME, DMALL_GRADEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_GRAND_DRACUMON_NAME, DMALL_GRAND_DRACUMON_ID, DMALL_GRAND_DRACUMON_FQID, DMALL_GRAND_DRACUMON_FQNAME, DMALL_GRAND_DRACUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_GRANDIS_KUWAGAMON_NAME, DMALL_GRANDIS_KUWAGAMON_ID, DMALL_GRANDIS_KUWAGAMON_FQID, DMALL_GRANDIS_KUWAGAMON_FQNAME, DMALL_GRANDIS_KUWAGAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_GRAND_LOCOMON_NAME, DMALL_GRAND_LOCOMON_ID, DMALL_GRAND_LOCOMON_FQID, DMALL_GRAND_LOCOMON_FQNAME, DMALL_GRAND_LOCOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_GRAPPLEOMON_NAME, DMALL_GRAPPLEOMON_ID, DMALL_GRAPPLEOMON_FQID, DMALL_GRAPPLEOMON_FQNAME, DMALL_GRAPPLEOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_GREAT_KING_SCUMON_NAME, DMALL_GREAT_KING_SCUMON_ID, DMALL_GREAT_KING_SCUMON_FQID, DMALL_GREAT_KING_SCUMON_FQNAME, DMALL_GREAT_KING_SCUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_GREYMON_2010_NAME, DMALL_GREYMON_2010_ID, DMALL_GREYMON_2010_FQID, DMALL_GREYMON_2010_FQNAME, DMALL_GREYMON_2010_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_GREYMON_BLUE_NAME, DMALL_GREYMON_BLUE_ID, DMALL_GREYMON_BLUE_FQID, DMALL_GREYMON_BLUE_FQNAME, DMALL_GREYMON_BLUE_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_GREYMON_NAME, DMALL_GREYMON_ID, DMALL_GREYMON_FQID, DMALL_GREYMON_FQNAME, DMALL_GREYMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_GREYMON_X_NAME, DMALL_GREYMON_X_ID, DMALL_GREYMON_X_FQID, DMALL_GREYMON_X_FQNAME, DMALL_GREYMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_GRIFFOMON_NAME, DMALL_GRIFFOMON_ID, DMALL_GRIFFOMON_FQID, DMALL_GRIFFOMON_FQNAME, DMALL_GRIFFOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_GROWMON_ORANGE_NAME, DMALL_GROWMON_ORANGE_ID, DMALL_GROWMON_ORANGE_FQID, DMALL_GROWMON_ORANGE_FQNAME, DMALL_GROWMON_ORANGE_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_GROWMON_NAME, DMALL_GROWMON_ID, DMALL_GROWMON_FQID, DMALL_GROWMON_FQNAME, DMALL_GROWMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_GROWMON_X_NAME, DMALL_GROWMON_X_ID, DMALL_GROWMON_X_FQID, DMALL_GROWMON_X_FQNAME, DMALL_GROWMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_GRYZMON_NAME, DMALL_GRYZMON_ID, DMALL_GRYZMON_FQID, DMALL_GRYZMON_FQNAME, DMALL_GRYZMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_GUARDROMON_GOLD_NAME, DMALL_GUARDROMON_GOLD_ID, DMALL_GUARDROMON_GOLD_FQID, DMALL_GUARDROMON_GOLD_FQNAME, DMALL_GUARDROMON_GOLD_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_GUARDROMON_NAME, DMALL_GUARDROMON_ID, DMALL_GUARDROMON_FQID, DMALL_GUARDROMON_FQNAME, DMALL_GUARDROMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_GUILMON_NAME, DMALL_GUILMON_ID, DMALL_GUILMON_FQID, DMALL_GUILMON_FQNAME, DMALL_GUILMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_GUILMON_X_NAME, DMALL_GUILMON_X_ID, DMALL_GUILMON_X_FQID, DMALL_GUILMON_X_FQNAME, DMALL_GUILMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_GUMMYMON_NAME, DMALL_GUMMYMON_ID, DMALL_GUMMYMON_FQID, DMALL_GUMMYMON_FQNAME, DMALL_GUMMYMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_GUNDRAMON_NAME, DMALL_GUNDRAMON_ID, DMALL_GUNDRAMON_FQID, DMALL_GUNDRAMON_FQNAME, DMALL_GUNDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_GURURUMON_NAME, DMALL_GURURUMON_ID, DMALL_GURURUMON_FQID, DMALL_GURURUMON_FQNAME, DMALL_GURURUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_GUSOKUMON_NAME, DMALL_GUSOKUMON_ID, DMALL_GUSOKUMON_FQID, DMALL_GUSOKUMON_FQNAME, DMALL_GUSOKUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_HACKMON_NAME, DMALL_HACKMON_ID, DMALL_HACKMON_FQID, DMALL_HACKMON_FQNAME, DMALL_HACKMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_HAGURUMON_NAME, DMALL_HAGURUMON_ID, DMALL_HAGURUMON_FQID, DMALL_HAGURUMON_FQNAME, DMALL_HAGURUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_HANGYOMON_NAME, DMALL_HANGYOMON_ID, DMALL_HANGYOMON_FQID, DMALL_HANGYOMON_FQNAME, DMALL_HANGYOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_HANUMON_NAME, DMALL_HANUMON_ID, DMALL_HANUMON_FQID, DMALL_HANUMON_FQNAME, DMALL_HANUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_HERAKLE_KABUTERIMON_NAME, DMALL_HERAKLE_KABUTERIMON_ID, DMALL_HERAKLE_KABUTERIMON_FQID, DMALL_HERAKLE_KABUTERIMON_FQNAME, DMALL_HERAKLE_KABUTERIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_HERISSMON_NAME, DMALL_HERISSMON_ID, DMALL_HERISSMON_FQID, DMALL_HERISSMON_FQNAME, DMALL_HERISSMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_HEXEBLAUMON_NAME, DMALL_HEXEBLAUMON_ID, DMALL_HEXEBLAUMON_FQID, DMALL_HEXEBLAUMON_FQNAME, DMALL_HEXEBLAUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_HI_ANDROMON_NAME, DMALL_HI_ANDROMON_ID, DMALL_HI_ANDROMON_FQID, DMALL_HI_ANDROMON_FQNAME, DMALL_HI_ANDROMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_HISYARYUMON_NAME, DMALL_HISYARYUMON_ID, DMALL_HISYARYUMON_FQID, DMALL_HISYARYUMON_FQNAME, DMALL_HISYARYUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_HIYARIMON_NAME, DMALL_HIYARIMON_ID, DMALL_HIYARIMON_FQID, DMALL_HIYARIMON_FQNAME, DMALL_HIYARIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_HOLY_ANGEMON_NAME, DMALL_HOLY_ANGEMON_ID, DMALL_HOLY_ANGEMON_FQID, DMALL_HOLY_ANGEMON_FQNAME, DMALL_HOLY_ANGEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_HOLY_DIGITAMAMON_NAME, DMALL_HOLY_DIGITAMAMON_ID, DMALL_HOLY_DIGITAMAMON_FQID, DMALL_HOLY_DIGITAMAMON_FQNAME, DMALL_HOLY_DIGITAMAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_HOLYDRAMON_NAME, DMALL_HOLYDRAMON_ID, DMALL_HOLYDRAMON_FQID, DMALL_HOLYDRAMON_FQNAME, DMALL_HOLYDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_HOLYDRAMON_X_NAME, DMALL_HOLYDRAMON_X_ID, DMALL_HOLYDRAMON_X_FQID, DMALL_HOLYDRAMON_X_FQNAME, DMALL_HOLYDRAMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_HOOKMON_NAME, DMALL_HOOKMON_ID, DMALL_HOOKMON_FQID, DMALL_HOOKMON_FQNAME, DMALL_HOOKMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_HOUOUMON_NAME, DMALL_HOUOUMON_ID, DMALL_HOUOUMON_FQID, DMALL_HOUOUMON_FQNAME, DMALL_HOUOUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_HOUOUMON_X_NAME, DMALL_HOUOUMON_X_ID, DMALL_HOUOUMON_X_FQID, DMALL_HOUOUMON_X_FQNAME, DMALL_HOUOUMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_HYOKOMON_NAME, DMALL_HYOKOMON_ID, DMALL_HYOKOMON_FQID, DMALL_HYOKOMON_FQNAME, DMALL_HYOKOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_HYOUGAMON_NAME, DMALL_HYOUGAMON_ID, DMALL_HYOUGAMON_FQID, DMALL_HYOUGAMON_FQNAME, DMALL_HYOUGAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_ICE_DEVIMON_NAME, DMALL_ICE_DEVIMON_ID, DMALL_ICE_DEVIMON_FQID, DMALL_ICE_DEVIMON_FQNAME, DMALL_ICE_DEVIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_ICEMON_NAME, DMALL_ICEMON_ID, DMALL_ICEMON_FQID, DMALL_ICEMON_FQNAME, DMALL_ICEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_IGAMON_NAME, DMALL_IGAMON_ID, DMALL_IGAMON_FQID, DMALL_IGAMON_FQNAME, DMALL_IGAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_IKKAKUMON_NAME, DMALL_IKKAKUMON_ID, DMALL_IKKAKUMON_FQID, DMALL_IKKAKUMON_FQNAME, DMALL_IKKAKUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_IMPERIALDRAMON_FIGHTER_MODE_BLACK_NAME, DMALL_IMPERIALDRAMON_FIGHTER_MODE_BLACK_ID, DMALL_IMPERIALDRAMON_FIGHTER_MODE_BLACK_FQID, DMALL_IMPERIALDRAMON_FIGHTER_MODE_BLACK_FQNAME, DMALL_IMPERIALDRAMON_FIGHTER_MODE_BLACK_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_IMPERIALDRAMON_FIGHTER_MODE_NAME, DMALL_IMPERIALDRAMON_FIGHTER_MODE_ID, DMALL_IMPERIALDRAMON_FIGHTER_MODE_FQID, DMALL_IMPERIALDRAMON_FIGHTER_MODE_FQNAME, DMALL_IMPERIALDRAMON_FIGHTER_MODE_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_IMPERIALDRAMON_PALADIN_MODE_NAME, DMALL_IMPERIALDRAMON_PALADIN_MODE_ID, DMALL_IMPERIALDRAMON_PALADIN_MODE_FQID, DMALL_IMPERIALDRAMON_PALADIN_MODE_FQNAME, DMALL_IMPERIALDRAMON_PALADIN_MODE_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_IMPMON_NAME, DMALL_IMPMON_ID, DMALL_IMPMON_FQID, DMALL_IMPMON_FQNAME, DMALL_IMPMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_IMPMON_X_NAME, DMALL_IMPMON_X_ID, DMALL_IMPMON_X_FQID, DMALL_IMPMON_X_FQNAME, DMALL_IMPMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_INSEKIMON_NAME, DMALL_INSEKIMON_ID, DMALL_INSEKIMON_FQID, DMALL_INSEKIMON_FQNAME, DMALL_INSEKIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_JAZAMON_NAME, DMALL_JAZAMON_ID, DMALL_JAZAMON_FQID, DMALL_JAZAMON_FQNAME, DMALL_JAZAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_JAZARDMON_NAME, DMALL_JAZARDMON_ID, DMALL_JAZARDMON_FQID, DMALL_JAZARDMON_FQNAME, DMALL_JAZARDMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_JAZARICHMON_NAME, DMALL_JAZARICHMON_ID, DMALL_JAZARICHMON_FQID, DMALL_JAZARICHMON_FQNAME, DMALL_JAZARICHMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_JESMON_GX_NAME, DMALL_JESMON_GX_ID, DMALL_JESMON_GX_FQID, DMALL_JESMON_GX_FQNAME, DMALL_JESMON_GX_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_JESMON_NAME, DMALL_JESMON_ID, DMALL_JESMON_FQID, DMALL_JESMON_FQNAME, DMALL_JESMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_JESMON_X_NAME, DMALL_JESMON_X_ID, DMALL_JESMON_X_FQID, DMALL_JESMON_X_FQNAME, DMALL_JESMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_JUNKMON_NAME, DMALL_JUNKMON_ID, DMALL_JUNKMON_FQID, DMALL_JUNKMON_FQNAME, DMALL_JUNKMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_JUSTIMON_X_NAME, DMALL_JUSTIMON_X_ID, DMALL_JUSTIMON_X_FQID, DMALL_JUSTIMON_X_FQNAME, DMALL_JUSTIMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_JYAGAMON_NAME, DMALL_JYAGAMON_ID, DMALL_JYAGAMON_FQID, DMALL_JYAGAMON_FQNAME, DMALL_JYAGAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_JYARIMON_NAME, DMALL_JYARIMON_ID, DMALL_JYARIMON_FQID, DMALL_JYARIMON_FQNAME, DMALL_JYARIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_JYUREIMON_NAME, DMALL_JYUREIMON_ID, DMALL_JYUREIMON_FQID, DMALL_JYUREIMON_FQNAME, DMALL_JYUREIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_KABUTERIMON_NAME, DMALL_KABUTERIMON_ID, DMALL_KABUTERIMON_FQID, DMALL_KABUTERIMON_FQNAME, DMALL_KABUTERIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_KAISER_GREYMON_NAME, DMALL_KAISER_GREYMON_ID, DMALL_KAISER_GREYMON_FQID, DMALL_KAISER_GREYMON_FQNAME, DMALL_KAISER_GREYMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_KAISER_LEOMON_NAME, DMALL_KAISER_LEOMON_ID, DMALL_KAISER_LEOMON_FQID, DMALL_KAISER_LEOMON_FQNAME, DMALL_KAISER_LEOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_KAKKINMON_NAME, DMALL_KAKKINMON_ID, DMALL_KAKKINMON_FQID, DMALL_KAKKINMON_FQNAME, DMALL_KAKKINMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_KARATSUKI_NUMEMON_NAME, DMALL_KARATSUKI_NUMEMON_ID, DMALL_KARATSUKI_NUMEMON_FQID, DMALL_KARATSUKI_NUMEMON_FQNAME, DMALL_KARATSUKI_NUMEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_KAZUCHIMON_NAME, DMALL_KAZUCHIMON_ID, DMALL_KAZUCHIMON_FQID, DMALL_KAZUCHIMON_FQNAME, DMALL_KAZUCHIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_KERAMON_NAME, DMALL_KERAMON_ID, DMALL_KERAMON_FQID, DMALL_KERAMON_FQNAME, DMALL_KERAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_KERAMON_X_NAME, DMALL_KERAMON_X_ID, DMALL_KERAMON_X_FQID, DMALL_KERAMON_X_FQNAME, DMALL_KERAMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_KETOMON_NAME, DMALL_KETOMON_ID, DMALL_KETOMON_FQID, DMALL_KETOMON_FQNAME, DMALL_KETOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_KIIMON_NAME, DMALL_KIIMON_ID, DMALL_KIIMON_FQID, DMALL_KIIMON_FQNAME, DMALL_KIIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_KING_ETEMON_NAME, DMALL_KING_ETEMON_ID, DMALL_KING_ETEMON_FQID, DMALL_KING_ETEMON_FQNAME, DMALL_KING_ETEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_KIWIMON_NAME, DMALL_KIWIMON_ID, DMALL_KIWIMON_FQID, DMALL_KIWIMON_FQNAME, DMALL_KIWIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_KNIGHTMON_NAME, DMALL_KNIGHTMON_ID, DMALL_KNIGHTMON_FQID, DMALL_KNIGHTMON_FQNAME, DMALL_KNIGHTMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_KOEMON_NAME, DMALL_KOEMON_ID, DMALL_KOEMON_FQID, DMALL_KOEMON_FQNAME, DMALL_KOEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_KOKABUTERIMON_NAME, DMALL_KOKABUTERIMON_ID, DMALL_KOKABUTERIMON_FQID, DMALL_KOKABUTERIMON_FQNAME, DMALL_KOKABUTERIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_KOKUWAMON_NAME, DMALL_KOKUWAMON_ID, DMALL_KOKUWAMON_FQID, DMALL_KOKUWAMON_FQNAME, DMALL_KOKUWAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_KOKUWAMON_X_NAME, DMALL_KOKUWAMON_X_ID, DMALL_KOKUWAMON_X_FQID, DMALL_KOKUWAMON_X_FQNAME, DMALL_KOKUWAMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_KOROMON_NAME, DMALL_KOROMON_ID, DMALL_KOROMON_FQID, DMALL_KOROMON_FQNAME, DMALL_KOROMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_KOUGAMON_NAME, DMALL_KOUGAMON_ID, DMALL_KOUGAMON_FQID, DMALL_KOUGAMON_FQNAME, DMALL_KOUGAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_KOZENIMON_NAME, DMALL_KOZENIMON_ID, DMALL_KOZENIMON_FQID, DMALL_KOZENIMON_FQNAME, DMALL_KOZENIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_KUNEMON_NAME, DMALL_KUNEMON_ID, DMALL_KUNEMON_FQID, DMALL_KUNEMON_FQNAME, DMALL_KUNEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_KURAMON_NAME, DMALL_KURAMON_ID, DMALL_KURAMON_FQID, DMALL_KURAMON_FQNAME, DMALL_KURAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_KUWAGAMON_NAME, DMALL_KUWAGAMON_ID, DMALL_KUWAGAMON_FQID, DMALL_KUWAGAMON_FQNAME, DMALL_KUWAGAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_KUWAGAMON_X_NAME, DMALL_KUWAGAMON_X_ID, DMALL_KUWAGAMON_X_FQID, DMALL_KUWAGAMON_X_FQNAME, DMALL_KUWAGAMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_KUZUHAMON_NAME, DMALL_KUZUHAMON_ID, DMALL_KUZUHAMON_FQID, DMALL_KUZUHAMON_FQNAME, DMALL_KUZUHAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_KYOKYOMON_NAME, DMALL_KYOKYOMON_ID, DMALL_KYOKYOMON_FQID, DMALL_KYOKYOMON_FQNAME, DMALL_KYOKYOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_KYUBIMON_NAME, DMALL_KYUBIMON_ID, DMALL_KYUBIMON_FQID, DMALL_KYUBIMON_FQNAME, DMALL_KYUBIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_KYUBIMON_SILVER_NAME, DMALL_KYUBIMON_SILVER_ID, DMALL_KYUBIMON_SILVER_FQID, DMALL_KYUBIMON_SILVER_FQNAME, DMALL_KYUBIMON_SILVER_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_LABRAMON_NAME, DMALL_LABRAMON_ID, DMALL_LABRAMON_FQID, DMALL_LABRAMON_FQNAME, DMALL_LABRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_LADYDEVIMON_NAME, DMALL_LADYDEVIMON_ID, DMALL_LADYDEVIMON_FQID, DMALL_LADYDEVIMON_FQNAME, DMALL_LADYDEVIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_LADYDEVIMON_X_NAME, DMALL_LADYDEVIMON_X_ID, DMALL_LADYDEVIMON_X_FQID, DMALL_LADYDEVIMON_X_FQNAME, DMALL_LADYDEVIMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_LALAMON_NAME, DMALL_LALAMON_ID, DMALL_LALAMON_FQID, DMALL_LALAMON_FQNAME, DMALL_LALAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_LAVOGARITAMON_NAME, DMALL_LAVOGARITAMON_ID, DMALL_LAVOGARITAMON_FQID, DMALL_LAVOGARITAMON_FQNAME, DMALL_LAVOGARITAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_LAVORVOMON_NAME, DMALL_LAVORVOMON_ID, DMALL_LAVORVOMON_FQID, DMALL_LAVORVOMON_FQNAME, DMALL_LAVORVOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_LEAFMON_NAME, DMALL_LEAFMON_ID, DMALL_LEAFMON_FQID, DMALL_LEAFMON_FQNAME, DMALL_LEAFMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_LEKISMON_NAME, DMALL_LEKISMON_ID, DMALL_LEKISMON_FQID, DMALL_LEKISMON_FQNAME, DMALL_LEKISMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_LEOMON_NAME, DMALL_LEOMON_ID, DMALL_LEOMON_FQID, DMALL_LEOMON_FQNAME, DMALL_LEOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_LEOMON_X_NAME, DMALL_LEOMON_X_ID, DMALL_LEOMON_X_FQID, DMALL_LEOMON_X_FQNAME, DMALL_LEOMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_LEVIAMON_NAME, DMALL_LEVIAMON_ID, DMALL_LEVIAMON_FQID, DMALL_LEVIAMON_FQNAME, DMALL_LEVIAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_LEVIAMON_X_NAME, DMALL_LEVIAMON_X_ID, DMALL_LEVIAMON_X_FQID, DMALL_LEVIAMON_X_FQNAME, DMALL_LEVIAMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_LILAMON_NAME, DMALL_LILAMON_ID, DMALL_LILAMON_FQID, DMALL_LILAMON_FQNAME, DMALL_LILAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_LILIMON_NAME, DMALL_LILIMON_ID, DMALL_LILIMON_FQID, DMALL_LILIMON_FQNAME, DMALL_LILIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_LILIMON_X_NAME, DMALL_LILIMON_X_ID, DMALL_LILIMON_X_FQID, DMALL_LILIMON_X_FQNAME, DMALL_LILIMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_LILITHMON_NAME, DMALL_LILITHMON_ID, DMALL_LILITHMON_FQID, DMALL_LILITHMON_FQNAME, DMALL_LILITHMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_LILITHMON_X_NAME, DMALL_LILITHMON_X_ID, DMALL_LILITHMON_X_FQID, DMALL_LILITHMON_X_FQNAME, DMALL_LILITHMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_LOPMON_NAME, DMALL_LOPMON_ID, DMALL_LOPMON_FQID, DMALL_LOPMON_FQNAME, DMALL_LOPMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_LOPMON_X_NAME, DMALL_LOPMON_X_ID, DMALL_LOPMON_X_FQID, DMALL_LOPMON_X_FQNAME, DMALL_LOPMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_LORDKNIGHTMON_X_NAME, DMALL_LORDKNIGHTMON_X_ID, DMALL_LORDKNIGHTMON_X_FQID, DMALL_LORDKNIGHTMON_X_FQNAME, DMALL_LORDKNIGHTMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_LOTUSMON_NAME, DMALL_LOTUSMON_ID, DMALL_LOTUSMON_FQID, DMALL_LOTUSMON_FQNAME, DMALL_LOTUSMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_LUCEMON_FALLDOWN_MODE_NAME, DMALL_LUCEMON_FALLDOWN_MODE_ID, DMALL_LUCEMON_FALLDOWN_MODE_FQID, DMALL_LUCEMON_FALLDOWN_MODE_FQNAME, DMALL_LUCEMON_FALLDOWN_MODE_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_LUCEMON_NAME, DMALL_LUCEMON_ID, DMALL_LUCEMON_FQID, DMALL_LUCEMON_FQNAME, DMALL_LUCEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_LUCEMON_SATAN_MODE_NAME, DMALL_LUCEMON_SATAN_MODE_ID, DMALL_LUCEMON_SATAN_MODE_FQID, DMALL_LUCEMON_SATAN_MODE_FQNAME, DMALL_LUCEMON_SATAN_MODE_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_LUCEMON_X_NAME, DMALL_LUCEMON_X_ID, DMALL_LUCEMON_X_FQID, DMALL_LUCEMON_X_FQNAME, DMALL_LUCEMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_LUDOMON_NAME, DMALL_LUDOMON_ID, DMALL_LUDOMON_FQID, DMALL_LUDOMON_FQNAME, DMALL_LUDOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_LUNAMON_NAME, DMALL_LUNAMON_ID, DMALL_LUNAMON_FQID, DMALL_LUNAMON_FQNAME, DMALL_LUNAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_LYNXMON_NAME, DMALL_LYNXMON_ID, DMALL_LYNXMON_FQID, DMALL_LYNXMON_FQNAME, DMALL_LYNXMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_MACH_GAOGAMON_NAME, DMALL_MACH_GAOGAMON_ID, DMALL_MACH_GAOGAMON_FQID, DMALL_MACH_GAOGAMON_FQNAME, DMALL_MACH_GAOGAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_MAD_LEOMON_NAME, DMALL_MAD_LEOMON_ID, DMALL_MAD_LEOMON_FQID, DMALL_MAD_LEOMON_FQNAME, DMALL_MAD_LEOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_MAGNAMON_X_NAME, DMALL_MAGNAMON_X_ID, DMALL_MAGNAMON_X_FQID, DMALL_MAGNAMON_X_FQNAME, DMALL_MAGNAMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_MAMBOMON_NAME, DMALL_MAMBOMON_ID, DMALL_MAMBOMON_FQID, DMALL_MAMBOMON_FQNAME, DMALL_MAMBOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_MAMEMON_NAME, DMALL_MAMEMON_ID, DMALL_MAMEMON_FQID, DMALL_MAMEMON_FQNAME, DMALL_MAMEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_MAMEMON_X_NAME, DMALL_MAMEMON_X_ID, DMALL_MAMEMON_X_FQID, DMALL_MAMEMON_X_FQNAME, DMALL_MAMEMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_MAMETYRAMON_NAME, DMALL_MAMETYRAMON_ID, DMALL_MAMETYRAMON_FQID, DMALL_MAMETYRAMON_FQNAME, DMALL_MAMETYRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_MAMMON_NAME, DMALL_MAMMON_ID, DMALL_MAMMON_FQID, DMALL_MAMMON_FQNAME, DMALL_MAMMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_MAMMON_X_NAME, DMALL_MAMMON_X_ID, DMALL_MAMMON_X_FQID, DMALL_MAMMON_X_FQNAME, DMALL_MAMMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_MANTARAYMON_X_NAME, DMALL_MANTARAYMON_X_ID, DMALL_MANTARAYMON_X_FQID, DMALL_MANTARAYMON_X_FQNAME, DMALL_MANTARAYMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_MANTICOREMON_NAME, DMALL_MANTICOREMON_ID, DMALL_MANTICOREMON_FQID, DMALL_MANTICOREMON_FQNAME, DMALL_MANTICOREMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_MARIN_ANGEMON_NAME, DMALL_MARIN_ANGEMON_ID, DMALL_MARIN_ANGEMON_FQID, DMALL_MARIN_ANGEMON_FQNAME, DMALL_MARIN_ANGEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_MARIN_CHIMAIRAMON_NAME, DMALL_MARIN_CHIMAIRAMON_ID, DMALL_MARIN_CHIMAIRAMON_FQID, DMALL_MARIN_CHIMAIRAMON_FQNAME, DMALL_MARIN_CHIMAIRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_MARIN_DEVIMON_NAME, DMALL_MARIN_DEVIMON_ID, DMALL_MARIN_DEVIMON_FQID, DMALL_MARIN_DEVIMON_FQNAME, DMALL_MARIN_DEVIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_MASTEMON_NAME, DMALL_MASTEMON_ID, DMALL_MASTEMON_FQID, DMALL_MASTEMON_FQNAME, DMALL_MASTEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_MECHANORIMON_NAME, DMALL_MECHANORIMON_ID, DMALL_MECHANORIMON_FQID, DMALL_MECHANORIMON_FQNAME, DMALL_MECHANORIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_MEGADRAMON_NAME, DMALL_MEGADRAMON_ID, DMALL_MEGADRAMON_FQID, DMALL_MEGADRAMON_FQNAME, DMALL_MEGADRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_MEGALO_GROWMON_ORANGE_NAME, DMALL_MEGALO_GROWMON_ORANGE_ID, DMALL_MEGALO_GROWMON_ORANGE_FQID, DMALL_MEGALO_GROWMON_ORANGE_FQNAME, DMALL_MEGALO_GROWMON_ORANGE_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_MEGALO_GROWMON_NAME, DMALL_MEGALO_GROWMON_ID, DMALL_MEGALO_GROWMON_FQID, DMALL_MEGALO_GROWMON_FQNAME, DMALL_MEGALO_GROWMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_MEGALO_GROWMON_X_NAME, DMALL_MEGALO_GROWMON_X_ID, DMALL_MEGALO_GROWMON_X_FQID, DMALL_MEGALO_GROWMON_X_FQNAME, DMALL_MEGALO_GROWMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_MEGA_SEADRAMON_NAME, DMALL_MEGA_SEADRAMON_ID, DMALL_MEGA_SEADRAMON_FQID, DMALL_MEGA_SEADRAMON_FQNAME, DMALL_MEGA_SEADRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_MEGA_SEADRAMON_X_NAME, DMALL_MEGA_SEADRAMON_X_ID, DMALL_MEGA_SEADRAMON_X_FQID, DMALL_MEGA_SEADRAMON_X_FQNAME, DMALL_MEGA_SEADRAMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_MEGIDRAMON_NAME, DMALL_MEGIDRAMON_ID, DMALL_MEGIDRAMON_FQID, DMALL_MEGIDRAMON_FQNAME, DMALL_MEGIDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_MEGIDRAMON_X_NAME, DMALL_MEGIDRAMON_X_ID, DMALL_MEGIDRAMON_X_FQID, DMALL_MEGIDRAMON_X_FQNAME, DMALL_MEGIDRAMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_MEICOOMON_BABY_NAME, DMALL_MEICOOMON_BABY_ID, DMALL_MEICOOMON_BABY_FQID, DMALL_MEICOOMON_BABY_FQNAME, DMALL_MEICOOMON_BABY_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_MEICOOMON_CHILD_NAME, DMALL_MEICOOMON_CHILD_ID, DMALL_MEICOOMON_CHILD_FQID, DMALL_MEICOOMON_CHILD_FQNAME, DMALL_MEICOOMON_CHILD_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_MEICOOMON_NAME, DMALL_MEICOOMON_ID, DMALL_MEICOOMON_FQID, DMALL_MEICOOMON_FQNAME, DMALL_MEICOOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_MEICRACKMON_NAME, DMALL_MEICRACKMON_ID, DMALL_MEICRACKMON_FQID, DMALL_MEICRACKMON_FQNAME, DMALL_MEICRACKMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_MEICRACKMON_VICIOUS_MODE_NAME, DMALL_MEICRACKMON_VICIOUS_MODE_ID, DMALL_MEICRACKMON_VICIOUS_MODE_FQID, DMALL_MEICRACKMON_VICIOUS_MODE_FQNAME, DMALL_MEICRACKMON_VICIOUS_MODE_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_MEPHISMON_NAME, DMALL_MEPHISMON_ID, DMALL_MEPHISMON_FQID, DMALL_MEPHISMON_FQNAME, DMALL_MEPHISMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_MEPHISMON_X_NAME, DMALL_MEPHISMON_X_ID, DMALL_MEPHISMON_X_FQID, DMALL_MEPHISMON_X_FQNAME, DMALL_MEPHISMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_MERAMON_NAME, DMALL_MERAMON_ID, DMALL_MERAMON_FQID, DMALL_MERAMON_FQNAME, DMALL_MERAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_MERAMON_X_NAME, DMALL_MERAMON_X_ID, DMALL_MERAMON_X_FQID, DMALL_MERAMON_X_FQNAME, DMALL_MERAMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_MERMAIMON_NAME, DMALL_MERMAIMON_ID, DMALL_MERMAIMON_FQID, DMALL_MERMAIMON_FQNAME, DMALL_MERMAIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_METAL_ETEMON_NAME, DMALL_METAL_ETEMON_ID, DMALL_METAL_ETEMON_FQID, DMALL_METAL_ETEMON_FQNAME, DMALL_METAL_ETEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_METAL_GARURUMON_BLACK_NAME, DMALL_METAL_GARURUMON_BLACK_ID, DMALL_METAL_GARURUMON_BLACK_FQID, DMALL_METAL_GARURUMON_BLACK_FQNAME, DMALL_METAL_GARURUMON_BLACK_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_METAL_GARURUMON_NAME, DMALL_METAL_GARURUMON_ID, DMALL_METAL_GARURUMON_FQID, DMALL_METAL_GARURUMON_FQNAME, DMALL_METAL_GARURUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_METAL_GARURUMON_X_NAME, DMALL_METAL_GARURUMON_X_ID, DMALL_METAL_GARURUMON_X_FQID, DMALL_METAL_GARURUMON_X_FQNAME, DMALL_METAL_GARURUMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_METAL_GREYMON_NAME, DMALL_METAL_GREYMON_ID, DMALL_METAL_GREYMON_FQID, DMALL_METAL_GREYMON_FQNAME, DMALL_METAL_GREYMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_METAL_GREYMON_VIRUS_NAME, DMALL_METAL_GREYMON_VIRUS_ID, DMALL_METAL_GREYMON_VIRUS_FQID, DMALL_METAL_GREYMON_VIRUS_FQNAME, DMALL_METAL_GREYMON_VIRUS_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_METAL_GREYMON_VIRUS_X_NAME, DMALL_METAL_GREYMON_VIRUS_X_ID, DMALL_METAL_GREYMON_VIRUS_X_FQID, DMALL_METAL_GREYMON_VIRUS_X_FQNAME, DMALL_METAL_GREYMON_VIRUS_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_METALGREYMON_X_NAME, DMALL_METALGREYMON_X_ID, DMALL_METALGREYMON_X_FQID, DMALL_METALGREYMON_X_FQNAME, DMALL_METALGREYMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_METALLICDRAMON_NAME, DMALL_METALLICDRAMON_ID, DMALL_METALLICDRAMON_FQID, DMALL_METALLICDRAMON_FQNAME, DMALL_METALLICDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_METAL_MAMEMON_NAME, DMALL_METAL_MAMEMON_ID, DMALL_METAL_MAMEMON_FQID, DMALL_METAL_MAMEMON_FQNAME, DMALL_METAL_MAMEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_METAL_MAMEMON_X_NAME, DMALL_METAL_MAMEMON_X_ID, DMALL_METAL_MAMEMON_X_FQID, DMALL_METAL_MAMEMON_X_FQNAME, DMALL_METAL_MAMEMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_METAL_PHANTOMON_NAME, DMALL_METAL_PHANTOMON_ID, DMALL_METAL_PHANTOMON_FQID, DMALL_METAL_PHANTOMON_FQNAME, DMALL_METAL_PHANTOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_METAL_PIRANIMON_NAME, DMALL_METAL_PIRANIMON_ID, DMALL_METAL_PIRANIMON_FQID, DMALL_METAL_PIRANIMON_FQNAME, DMALL_METAL_PIRANIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_METAL_SEADRAMON_NAME, DMALL_METAL_SEADRAMON_ID, DMALL_METAL_SEADRAMON_FQID, DMALL_METAL_SEADRAMON_FQNAME, DMALL_METAL_SEADRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_METAL_TYRANOMON_NAME, DMALL_METAL_TYRANOMON_ID, DMALL_METAL_TYRANOMON_FQID, DMALL_METAL_TYRANOMON_FQNAME, DMALL_METAL_TYRANOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_METAL_TYRANOMON_X_NAME, DMALL_METAL_TYRANOMON_X_ID, DMALL_METAL_TYRANOMON_X_FQID, DMALL_METAL_TYRANOMON_X_FQNAME, DMALL_METAL_TYRANOMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_MIKEMON_NAME, DMALL_MIKEMON_ID, DMALL_MIKEMON_FQID, DMALL_MIKEMON_FQNAME, DMALL_MIKEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_MILLENNIUMON_NAME, DMALL_MILLENNIUMON_ID, DMALL_MILLENNIUMON_FQID, DMALL_MILLENNIUMON_FQNAME, DMALL_MILLENNIUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_MIMICMON_NAME, DMALL_MIMICMON_ID, DMALL_MIMICMON_FQID, DMALL_MIMICMON_FQNAME, DMALL_MIMICMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_MINERVAMON_X_NAME, DMALL_MINERVAMON_X_ID, DMALL_MINERVAMON_X_FQID, DMALL_MINERVAMON_X_FQNAME, DMALL_MINERVAMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_MINOMON_NAME, DMALL_MINOMON_ID, DMALL_MINOMON_FQID, DMALL_MINOMON_FQNAME, DMALL_MINOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_MOCHIMON_NAME, DMALL_MOCHIMON_ID, DMALL_MOCHIMON_FQID, DMALL_MOCHIMON_FQNAME, DMALL_MOCHIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_MOKUMON_NAME, DMALL_MOKUMON_ID, DMALL_MOKUMON_FQID, DMALL_MOKUMON_FQNAME, DMALL_MOKUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_MONIMON_NAME, DMALL_MONIMON_ID, DMALL_MONIMON_FQID, DMALL_MONIMON_FQNAME, DMALL_MONIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_MONOCHROMON_NAME, DMALL_MONOCHROMON_ID, DMALL_MONOCHROMON_FQID, DMALL_MONOCHROMON_FQNAME, DMALL_MONOCHROMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_MONOCHROMON_X_NAME, DMALL_MONOCHROMON_X_ID, DMALL_MONOCHROMON_X_FQID, DMALL_MONOCHROMON_X_FQNAME, DMALL_MONOCHROMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_MONZAEMON_NAME, DMALL_MONZAEMON_ID, DMALL_MONZAEMON_FQID, DMALL_MONZAEMON_FQNAME, DMALL_MONZAEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_MONZAEMON_X_NAME, DMALL_MONZAEMON_X_ID, DMALL_MONZAEMON_X_FQID, DMALL_MONZAEMON_X_FQNAME, DMALL_MONZAEMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_MOONMON_NAME, DMALL_MOONMON_ID, DMALL_MOONMON_FQID, DMALL_MOONMON_FQNAME, DMALL_MOONMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_MORI_SHELLMON_NAME, DMALL_MORI_SHELLMON_ID, DMALL_MORI_SHELLMON_FQID, DMALL_MORI_SHELLMON_FQNAME, DMALL_MORI_SHELLMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_MORPHOMON_NAME, DMALL_MORPHOMON_ID, DMALL_MORPHOMON_FQID, DMALL_MORPHOMON_FQNAME, DMALL_MORPHOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_MUCHOMON_NAME, DMALL_MUCHOMON_ID, DMALL_MUCHOMON_FQID, DMALL_MUCHOMON_FQNAME, DMALL_MUCHOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_MUGENDRAMON_NAME, DMALL_MUGENDRAMON_ID, DMALL_MUGENDRAMON_FQID, DMALL_MUGENDRAMON_FQNAME, DMALL_MUGENDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_MUSHMON_NAME, DMALL_MUSHMON_ID, DMALL_MUSHMON_FQID, DMALL_MUSHMON_FQNAME, DMALL_MUSHMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_NANOMON_NAME, DMALL_NANOMON_ID, DMALL_NANOMON_FQID, DMALL_NANOMON_FQNAME, DMALL_NANOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_NEFERTIMON_X_NAME, DMALL_NEFERTIMON_X_ID, DMALL_NEFERTIMON_X_FQID, DMALL_NEFERTIMON_X_FQNAME, DMALL_NEFERTIMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_NEO_DEVIMON_NAME, DMALL_NEO_DEVIMON_ID, DMALL_NEO_DEVIMON_FQID, DMALL_NEO_DEVIMON_FQNAME, DMALL_NEO_DEVIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_NISE_DRIMOGEMON_NAME, DMALL_NISE_DRIMOGEMON_ID, DMALL_NISE_DRIMOGEMON_FQID, DMALL_NISE_DRIMOGEMON_FQNAME, DMALL_NISE_DRIMOGEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_NOBLE_PUMPMON_NAME, DMALL_NOBLE_PUMPMON_ID, DMALL_NOBLE_PUMPMON_FQID, DMALL_NOBLE_PUMPMON_FQNAME, DMALL_NOBLE_PUMPMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_NUMEMON_NAME, DMALL_NUMEMON_ID, DMALL_NUMEMON_FQID, DMALL_NUMEMON_FQNAME, DMALL_NUMEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_NUMEMON_X_NAME, DMALL_NUMEMON_X_ID, DMALL_NUMEMON_X_FQID, DMALL_NUMEMON_X_FQNAME, DMALL_NUMEMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_NYAROMON_NAME, DMALL_NYAROMON_ID, DMALL_NYAROMON_FQID, DMALL_NYAROMON_FQNAME, DMALL_NYAROMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_NYOKIMON_NAME, DMALL_NYOKIMON_ID, DMALL_NYOKIMON_FQID, DMALL_NYOKIMON_FQNAME, DMALL_NYOKIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_OFANIMON_CORE_NAME, DMALL_OFANIMON_CORE_ID, DMALL_OFANIMON_CORE_FQID, DMALL_OFANIMON_CORE_FQNAME, DMALL_OFANIMON_CORE_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_OFANIMON_FALLDOWN_MODE_NAME, DMALL_OFANIMON_FALLDOWN_MODE_ID, DMALL_OFANIMON_FALLDOWN_MODE_FQID, DMALL_OFANIMON_FALLDOWN_MODE_FQNAME, DMALL_OFANIMON_FALLDOWN_MODE_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_OGREMON_NAME, DMALL_OGREMON_ID, DMALL_OGREMON_FQID, DMALL_OGREMON_FQNAME, DMALL_OGREMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_OGREMON_X_NAME, DMALL_OGREMON_X_ID, DMALL_OGREMON_X_FQID, DMALL_OGREMON_X_FQNAME, DMALL_OGREMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_OGUDOMON_NAME, DMALL_OGUDOMON_ID, DMALL_OGUDOMON_FQID, DMALL_OGUDOMON_FQNAME, DMALL_OGUDOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_OGUDOMON_X_NAME, DMALL_OGUDOMON_X_ID, DMALL_OGUDOMON_X_FQID, DMALL_OGUDOMON_X_FQNAME, DMALL_OGUDOMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_OKUWAMON_NAME, DMALL_OKUWAMON_ID, DMALL_OKUWAMON_FQID, DMALL_OKUWAMON_FQNAME, DMALL_OKUWAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_OKUWAMON_X_NAME, DMALL_OKUWAMON_X_ID, DMALL_OKUWAMON_X_FQID, DMALL_OKUWAMON_X_FQNAME, DMALL_OKUWAMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_OMEGAMON_ALTER_S_NAME, DMALL_OMEGAMON_ALTER_S_ID, DMALL_OMEGAMON_ALTER_S_FQID, DMALL_OMEGAMON_ALTER_S_FQNAME, DMALL_OMEGAMON_ALTER_S_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_OMEGAMON_NAME, DMALL_OMEGAMON_ID, DMALL_OMEGAMON_FQID, DMALL_OMEGAMON_FQNAME, DMALL_OMEGAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_OMEGAMON_X_NAME, DMALL_OMEGAMON_X_ID, DMALL_OMEGAMON_X_FQID, DMALL_OMEGAMON_X_FQNAME, DMALL_OMEGAMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_OMEGAMON_ZWART_NAME, DMALL_OMEGAMON_ZWART_ID, DMALL_OMEGAMON_ZWART_FQID, DMALL_OMEGAMON_ZWART_FQNAME, DMALL_OMEGAMON_ZWART_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_OMEGA_SHOUTMON_X_NAME, DMALL_OMEGA_SHOUTMON_X_ID, DMALL_OMEGA_SHOUTMON_X_FQID, DMALL_OMEGA_SHOUTMON_X_FQNAME, DMALL_OMEGA_SHOUTMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_OMEKAMON_NAME, DMALL_OMEKAMON_ID, DMALL_OMEKAMON_FQID, DMALL_OMEKAMON_FQNAME, DMALL_OMEKAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_OPHANIMON_NAME, DMALL_OPHANIMON_ID, DMALL_OPHANIMON_FQID, DMALL_OPHANIMON_FQNAME, DMALL_OPHANIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_OPHANIMON_X_NAME, DMALL_OPHANIMON_X_ID, DMALL_OPHANIMON_X_FQID, DMALL_OPHANIMON_X_FQNAME, DMALL_OPHANIMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_ORDINEMON_NAME, DMALL_ORDINEMON_ID, DMALL_ORDINEMON_FQID, DMALL_ORDINEMON_FQNAME, DMALL_ORDINEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_OROCHIMON_NAME, DMALL_OROCHIMON_ID, DMALL_OROCHIMON_FQID, DMALL_OROCHIMON_FQNAME, DMALL_OROCHIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_OTAMAMON_NAME, DMALL_OTAMAMON_ID, DMALL_OTAMAMON_FQID, DMALL_OTAMAMON_FQNAME, DMALL_OTAMAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_OTAMAMON_RED_NAME, DMALL_OTAMAMON_RED_ID, DMALL_OTAMAMON_RED_FQID, DMALL_OTAMAMON_RED_FQNAME, DMALL_OTAMAMON_RED_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_OTAMAMON_X_NAME, DMALL_OTAMAMON_X_ID, DMALL_OTAMAMON_X_FQID, DMALL_OTAMAMON_X_FQNAME, DMALL_OTAMAMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_OURYUMON_NAME, DMALL_OURYUMON_ID, DMALL_OURYUMON_FQID, DMALL_OURYUMON_FQNAME, DMALL_OURYUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_PAFUMON_NAME, DMALL_PAFUMON_ID, DMALL_PAFUMON_FQID, DMALL_PAFUMON_FQNAME, DMALL_PAFUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_PAGUMON_NAME, DMALL_PAGUMON_ID, DMALL_PAGUMON_FQID, DMALL_PAGUMON_FQNAME, DMALL_PAGUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_PAILDRAMON_NAME, DMALL_PAILDRAMON_ID, DMALL_PAILDRAMON_FQID, DMALL_PAILDRAMON_FQNAME, DMALL_PAILDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_PALEDRAMON_NAME, DMALL_PALEDRAMON_ID, DMALL_PALEDRAMON_FQID, DMALL_PALEDRAMON_FQNAME, DMALL_PALEDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_PALMON_NAME, DMALL_PALMON_ID, DMALL_PALMON_FQID, DMALL_PALMON_FQNAME, DMALL_PALMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_PALMON_X_NAME, DMALL_PALMON_X_ID, DMALL_PALMON_X_FQID, DMALL_PALMON_X_FQNAME, DMALL_PALMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_PANDAMON_NAME, DMALL_PANDAMON_ID, DMALL_PANDAMON_FQID, DMALL_PANDAMON_FQNAME, DMALL_PANDAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_PANJYAMON_NAME, DMALL_PANJYAMON_ID, DMALL_PANJYAMON_FQID, DMALL_PANJYAMON_FQNAME, DMALL_PANJYAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_PANJYAMON_X_NAME, DMALL_PANJYAMON_X_ID, DMALL_PANJYAMON_X_FQID, DMALL_PANJYAMON_X_FQNAME, DMALL_PANJYAMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_PAOMON_NAME, DMALL_PAOMON_ID, DMALL_PAOMON_FQID, DMALL_PAOMON_FQNAME, DMALL_PAOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_PARASAURMON_NAME, DMALL_PARASAURMON_ID, DMALL_PARASAURMON_FQID, DMALL_PARASAURMON_FQNAME, DMALL_PARASAURMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_PEGASMON_X_NAME, DMALL_PEGASMON_X_ID, DMALL_PEGASMON_X_FQID, DMALL_PEGASMON_X_FQNAME, DMALL_PEGASMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_PENMON_NAME, DMALL_PENMON_ID, DMALL_PENMON_FQID, DMALL_PENMON_FQNAME, DMALL_PENMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_PETIMERAMON_NAME, DMALL_PETIMERAMON_ID, DMALL_PETIMERAMON_FQID, DMALL_PETIMERAMON_FQNAME, DMALL_PETIMERAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_PETITMAMON_NAME, DMALL_PETITMAMON_ID, DMALL_PETITMAMON_FQID, DMALL_PETITMAMON_FQNAME, DMALL_PETITMAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_PETITMON_NAME, DMALL_PETITMON_ID, DMALL_PETITMON_FQID, DMALL_PETITMON_FQNAME, DMALL_PETITMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_PHANTOMON_NAME, DMALL_PHANTOMON_ID, DMALL_PHANTOMON_FQID, DMALL_PHANTOMON_FQNAME, DMALL_PHANTOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_PHASCOMON_NAME, DMALL_PHASCOMON_ID, DMALL_PHASCOMON_FQID, DMALL_PHASCOMON_FQNAME, DMALL_PHASCOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_PICCOLOMON_NAME, DMALL_PICCOLOMON_ID, DMALL_PICCOLOMON_FQID, DMALL_PICCOLOMON_FQNAME, DMALL_PICCOLOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_PICKMON_NAME, DMALL_PICKMON_ID, DMALL_PICKMON_FQID, DMALL_PICKMON_FQNAME, DMALL_PICKMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_PICO_DEVIMON_NAME, DMALL_PICO_DEVIMON_ID, DMALL_PICO_DEVIMON_FQID, DMALL_PICO_DEVIMON_FQNAME, DMALL_PICO_DEVIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_PIDMON_NAME, DMALL_PIDMON_ID, DMALL_PIDMON_FQID, DMALL_PIDMON_FQNAME, DMALL_PIDMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_PIEMON_NAME, DMALL_PIEMON_ID, DMALL_PIEMON_FQID, DMALL_PIEMON_FQNAME, DMALL_PIEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_PINOCHIMON_NAME, DMALL_PINOCHIMON_ID, DMALL_PINOCHIMON_FQID, DMALL_PINOCHIMON_FQNAME, DMALL_PINOCHIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_PIPIMON_NAME, DMALL_PIPIMON_ID, DMALL_PIPIMON_FQID, DMALL_PIPIMON_FQNAME, DMALL_PIPIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_PIRANIMON_NAME, DMALL_PIRANIMON_ID, DMALL_PIRANIMON_FQID, DMALL_PIRANIMON_FQNAME, DMALL_PIRANIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_PITCHMON_NAME, DMALL_PITCHMON_ID, DMALL_PITCHMON_FQID, DMALL_PITCHMON_FQNAME, DMALL_PITCHMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_PIYOMON_NAME, DMALL_PIYOMON_ID, DMALL_PIYOMON_FQID, DMALL_PIYOMON_FQNAME, DMALL_PIYOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_PLATINUM_NUMEMON_NAME, DMALL_PLATINUM_NUMEMON_ID, DMALL_PLATINUM_NUMEMON_FQID, DMALL_PLATINUM_NUMEMON_FQNAME, DMALL_PLATINUM_NUMEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_PLATINUM_SCUMON_NAME, DMALL_PLATINUM_SCUMON_ID, DMALL_PLATINUM_SCUMON_FQID, DMALL_PLATINUM_SCUMON_FQNAME, DMALL_PLATINUM_SCUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_PLESIOMON_NAME, DMALL_PLESIOMON_ID, DMALL_PLESIOMON_FQID, DMALL_PLESIOMON_FQNAME, DMALL_PLESIOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_PLESIOMON_X_NAME, DMALL_PLESIOMON_X_ID, DMALL_PLESIOMON_X_FQID, DMALL_PLESIOMON_X_FQNAME, DMALL_PLESIOMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_PLOTMON_NAME, DMALL_PLOTMON_ID, DMALL_PLOTMON_FQID, DMALL_PLOTMON_FQNAME, DMALL_PLOTMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_PLOTMON_X_NAME, DMALL_PLOTMON_X_ID, DMALL_PLOTMON_X_FQID, DMALL_PLOTMON_X_FQNAME, DMALL_PLOTMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_POKOMON_NAME, DMALL_POKOMON_ID, DMALL_POKOMON_FQID, DMALL_POKOMON_FQNAME, DMALL_POKOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_POPOMON_NAME, DMALL_POPOMON_ID, DMALL_POPOMON_FQID, DMALL_POPOMON_FQNAME, DMALL_POPOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_PORCUPAMON_NAME, DMALL_PORCUPAMON_ID, DMALL_PORCUPAMON_FQID, DMALL_PORCUPAMON_FQNAME, DMALL_PORCUPAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_POROMON_NAME, DMALL_POROMON_ID, DMALL_POROMON_FQID, DMALL_POROMON_FQNAME, DMALL_POROMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_PRINCE_MAMEMON_NAME, DMALL_PRINCE_MAMEMON_ID, DMALL_PRINCE_MAMEMON_FQID, DMALL_PRINCE_MAMEMON_FQNAME, DMALL_PRINCE_MAMEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_PRINCE_MAMEMON_X_NAME, DMALL_PRINCE_MAMEMON_X_ID, DMALL_PRINCE_MAMEMON_X_FQID, DMALL_PRINCE_MAMEMON_X_FQNAME, DMALL_PRINCE_MAMEMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_PTERANOMON_X_NAME, DMALL_PTERANOMON_X_ID, DMALL_PTERANOMON_X_FQID, DMALL_PTERANOMON_X_FQNAME, DMALL_PTERANOMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_PUKAMON_NAME, DMALL_PUKAMON_ID, DMALL_PUKAMON_FQID, DMALL_PUKAMON_FQNAME, DMALL_PUKAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_PUKUMON_NAME, DMALL_PUKUMON_ID, DMALL_PUKUMON_FQID, DMALL_PUKUMON_FQNAME, DMALL_PUKUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_PULSEMON_NAME, DMALL_PULSEMON_ID, DMALL_PULSEMON_FQID, DMALL_PULSEMON_FQNAME, DMALL_PULSEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_PUMPMON_NAME, DMALL_PUMPMON_ID, DMALL_PUMPMON_FQID, DMALL_PUMPMON_FQNAME, DMALL_PUMPMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_PUPUMON_NAME, DMALL_PUPUMON_ID, DMALL_PUPUMON_FQID, DMALL_PUPUMON_FQNAME, DMALL_PUPUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_PUROROMON_NAME, DMALL_PUROROMON_ID, DMALL_PUROROMON_FQID, DMALL_PUROROMON_FQNAME, DMALL_PUROROMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_PURURUMON_NAME, DMALL_PURURUMON_ID, DMALL_PURURUMON_FQID, DMALL_PURURUMON_FQNAME, DMALL_PURURUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_PUSUMON_NAME, DMALL_PUSUMON_ID, DMALL_PUSUMON_FQID, DMALL_PUSUMON_FQNAME, DMALL_PUSUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_PUSURIMON_NAME, DMALL_PUSURIMON_ID, DMALL_PUSURIMON_FQID, DMALL_PUSURIMON_FQNAME, DMALL_PUSURIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_PUTTIMON_NAME, DMALL_PUTTIMON_ID, DMALL_PUTTIMON_FQID, DMALL_PUTTIMON_FQNAME, DMALL_PUTTIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_PUYOMON_NAME, DMALL_PUYOMON_ID, DMALL_PUYOMON_FQID, DMALL_PUYOMON_FQNAME, DMALL_PUYOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_PYOCOMON_NAME, DMALL_PYOCOMON_ID, DMALL_PYOCOMON_FQID, DMALL_PYOCOMON_FQNAME, DMALL_PYOCOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_PYONMON_NAME, DMALL_PYONMON_ID, DMALL_PYONMON_FQID, DMALL_PYONMON_FQNAME, DMALL_PYONMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_RAFFLESIMON_NAME, DMALL_RAFFLESIMON_ID, DMALL_RAFFLESIMON_FQID, DMALL_RAFFLESIMON_FQNAME, DMALL_RAFFLESIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_RAGNA_LORDMON_NAME, DMALL_RAGNA_LORDMON_ID, DMALL_RAGNA_LORDMON_FQID, DMALL_RAGNA_LORDMON_FQNAME, DMALL_RAGNA_LORDMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_RAGUELMON_NAME, DMALL_RAGUELMON_ID, DMALL_RAGUELMON_FQID, DMALL_RAGUELMON_FQNAME, DMALL_RAGUELMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_RAIDENMON_NAME, DMALL_RAIDENMON_ID, DMALL_RAIDENMON_FQID, DMALL_RAIDENMON_FQNAME, DMALL_RAIDENMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_RAIHIMON_NAME, DMALL_RAIHIMON_ID, DMALL_RAIHIMON_FQID, DMALL_RAIHIMON_FQNAME, DMALL_RAIHIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_RAIJI_LUDOMON_NAME, DMALL_RAIJI_LUDOMON_ID, DMALL_RAIJI_LUDOMON_FQID, DMALL_RAIJI_LUDOMON_FQNAME, DMALL_RAIJI_LUDOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_RAPIDMON_ARMOR_NAME, DMALL_RAPIDMON_ARMOR_ID, DMALL_RAPIDMON_ARMOR_FQID, DMALL_RAPIDMON_ARMOR_FQNAME, DMALL_RAPIDMON_ARMOR_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_RAPIDMON_NAME, DMALL_RAPIDMON_ID, DMALL_RAPIDMON_FQID, DMALL_RAPIDMON_FQNAME, DMALL_RAPIDMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_RAPIDMON_X_NAME, DMALL_RAPIDMON_X_ID, DMALL_RAPIDMON_X_FQID, DMALL_RAPIDMON_X_FQNAME, DMALL_RAPIDMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_RAPTORDRAMON_NAME, DMALL_RAPTORDRAMON_ID, DMALL_RAPTORDRAMON_FQID, DMALL_RAPTORDRAMON_FQNAME, DMALL_RAPTORDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_RASENMON_FURY_MODE_NAME, DMALL_RASENMON_FURY_MODE_ID, DMALL_RASENMON_FURY_MODE_FQID, DMALL_RASENMON_FURY_MODE_FQNAME, DMALL_RASENMON_FURY_MODE_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_RASENMON_NAME, DMALL_RASENMON_ID, DMALL_RASENMON_FQID, DMALL_RASENMON_FQNAME, DMALL_RASENMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_RASIELMON_NAME, DMALL_RASIELMON_ID, DMALL_RASIELMON_FQID, DMALL_RASIELMON_FQNAME, DMALL_RASIELMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_REBELLIMON_NAME, DMALL_REBELLIMON_ID, DMALL_REBELLIMON_FQID, DMALL_REBELLIMON_FQNAME, DMALL_REBELLIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_RED_V_DRAMON_NAME, DMALL_RED_V_DRAMON_ID, DMALL_RED_V_DRAMON_FQID, DMALL_RED_V_DRAMON_FQNAME, DMALL_RED_V_DRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_RED_VEGIMON_NAME, DMALL_RED_VEGIMON_ID, DMALL_RED_VEGIMON_FQID, DMALL_RED_VEGIMON_FQNAME, DMALL_RED_VEGIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_REGALECUSMON_NAME, DMALL_REGALECUSMON_ID, DMALL_REGALECUSMON_FQID, DMALL_REGALECUSMON_FQNAME, DMALL_REGALECUSMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_RELEMON_NAME, DMALL_RELEMON_ID, DMALL_RELEMON_FQID, DMALL_RELEMON_FQNAME, DMALL_RELEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_RENAMON_NAME, DMALL_RENAMON_ID, DMALL_RENAMON_FQID, DMALL_RENAMON_FQNAME, DMALL_RENAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_RENAMON_X_NAME, DMALL_RENAMON_X_ID, DMALL_RENAMON_X_FQID, DMALL_RENAMON_X_FQNAME, DMALL_RENAMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_REPPAMON_NAME, DMALL_REPPAMON_ID, DMALL_REPPAMON_FQID, DMALL_REPPAMON_FQNAME, DMALL_REPPAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_RHINOMON_NAME, DMALL_RHINOMON_ID, DMALL_RHINOMON_FQID, DMALL_RHINOMON_FQNAME, DMALL_RHINOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_RHINOMON_X_NAME, DMALL_RHINOMON_X_ID, DMALL_RHINOMON_X_FQID, DMALL_RHINOMON_X_FQNAME, DMALL_RHINOMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_RIZE_GREYMON_NAME, DMALL_RIZE_GREYMON_ID, DMALL_RIZE_GREYMON_FQID, DMALL_RIZE_GREYMON_FQNAME, DMALL_RIZE_GREYMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_RIZEGREYMON_X_NAME, DMALL_RIZEGREYMON_X_ID, DMALL_RIZEGREYMON_X_FQID, DMALL_RIZEGREYMON_X_FQNAME, DMALL_RIZEGREYMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_ROSEMON_BURST_MODE_NAME, DMALL_ROSEMON_BURST_MODE_ID, DMALL_ROSEMON_BURST_MODE_FQID, DMALL_ROSEMON_BURST_MODE_FQNAME, DMALL_ROSEMON_BURST_MODE_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_ROSEMON_NAME, DMALL_ROSEMON_ID, DMALL_ROSEMON_FQID, DMALL_ROSEMON_FQNAME, DMALL_ROSEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_ROSEMON_X_NAME, DMALL_ROSEMON_X_ID, DMALL_ROSEMON_X_FQID, DMALL_ROSEMON_X_FQNAME, DMALL_ROSEMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_RUKAMON_NAME, DMALL_RUKAMON_ID, DMALL_RUKAMON_FQID, DMALL_RUKAMON_FQNAME, DMALL_RUKAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_RUST_TYRANNOMON_NAME, DMALL_RUST_TYRANNOMON_ID, DMALL_RUST_TYRANNOMON_FQID, DMALL_RUST_TYRANNOMON_FQNAME, DMALL_RUST_TYRANNOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_RYUDAMON_NAME, DMALL_RYUDAMON_ID, DMALL_RYUDAMON_FQID, DMALL_RYUDAMON_FQNAME, DMALL_RYUDAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_SABERDRAMON_NAME, DMALL_SABERDRAMON_ID, DMALL_SABERDRAMON_FQID, DMALL_SABERDRAMON_FQNAME, DMALL_SABERDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_SABER_LEOMON_NAME, DMALL_SABER_LEOMON_ID, DMALL_SABER_LEOMON_FQID, DMALL_SABER_LEOMON_FQNAME, DMALL_SABER_LEOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_SAGOMON_NAME, DMALL_SAGOMON_ID, DMALL_SAGOMON_FQID, DMALL_SAGOMON_FQNAME, DMALL_SAGOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_SAINT_GALGOMON_NAME, DMALL_SAINT_GALGOMON_ID, DMALL_SAINT_GALGOMON_FQID, DMALL_SAINT_GALGOMON_FQNAME, DMALL_SAINT_GALGOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_SAKUYAMON_NAME, DMALL_SAKUYAMON_ID, DMALL_SAKUYAMON_FQID, DMALL_SAKUYAMON_FQNAME, DMALL_SAKUYAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_SAKUYAMON_X_NAME, DMALL_SAKUYAMON_X_ID, DMALL_SAKUYAMON_X_FQID, DMALL_SAKUYAMON_X_FQNAME, DMALL_SAKUYAMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_SAND_YANMAMON_NAME, DMALL_SAND_YANMAMON_ID, DMALL_SAND_YANMAMON_FQID, DMALL_SAND_YANMAMON_FQNAME, DMALL_SAND_YANMAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_SANGLOUPMON_NAME, DMALL_SANGLOUPMON_ID, DMALL_SANGLOUPMON_FQID, DMALL_SANGLOUPMON_FQNAME, DMALL_SANGLOUPMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_SANGOMON_NAME, DMALL_SANGOMON_ID, DMALL_SANGOMON_FQID, DMALL_SANGOMON_FQNAME, DMALL_SANGOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_SAVIORHACKMON_NAME, DMALL_SAVIORHACKMON_ID, DMALL_SAVIORHACKMON_FQID, DMALL_SAVIORHACKMON_FQNAME, DMALL_SAVIORHACKMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_SCORPIOMON_NAME, DMALL_SCORPIOMON_ID, DMALL_SCORPIOMON_FQID, DMALL_SCORPIOMON_FQNAME, DMALL_SCORPIOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_SCUMON_NAME, DMALL_SCUMON_ID, DMALL_SCUMON_FQID, DMALL_SCUMON_FQNAME, DMALL_SCUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_SEADRAMON_NAME, DMALL_SEADRAMON_ID, DMALL_SEADRAMON_FQID, DMALL_SEADRAMON_FQNAME, DMALL_SEADRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_SEADRAMON_X_NAME, DMALL_SEADRAMON_X_ID, DMALL_SEADRAMON_X_FQID, DMALL_SEADRAMON_X_FQNAME, DMALL_SEADRAMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_SERAPHIMON_NAME, DMALL_SERAPHIMON_ID, DMALL_SERAPHIMON_FQID, DMALL_SERAPHIMON_FQNAME, DMALL_SERAPHIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_SHADRAMON_NAME, DMALL_SHADRAMON_ID, DMALL_SHADRAMON_FQID, DMALL_SHADRAMON_FQNAME, DMALL_SHADRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_SHAKOMON_NAME, DMALL_SHAKOMON_ID, DMALL_SHAKOMON_FQID, DMALL_SHAKOMON_FQNAME, DMALL_SHAKOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_SHAKOMON_X_NAME, DMALL_SHAKOMON_X_ID, DMALL_SHAKOMON_X_FQID, DMALL_SHAKOMON_X_FQNAME, DMALL_SHAKOMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_SHAWUJINMON_NAME, DMALL_SHAWUJINMON_ID, DMALL_SHAWUJINMON_FQID, DMALL_SHAWUJINMON_FQNAME, DMALL_SHAWUJINMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_SHEEPMON_NAME, DMALL_SHEEPMON_ID, DMALL_SHEEPMON_FQID, DMALL_SHEEPMON_FQNAME, DMALL_SHEEPMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_SHELLMON_NAME, DMALL_SHELLMON_ID, DMALL_SHELLMON_FQID, DMALL_SHELLMON_FQNAME, DMALL_SHELLMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_SHIMA_UNIMON_NAME, DMALL_SHIMA_UNIMON_ID, DMALL_SHIMA_UNIMON_FQID, DMALL_SHIMA_UNIMON_FQNAME, DMALL_SHIMA_UNIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_SHIN_MONZAEMON_NAME, DMALL_SHIN_MONZAEMON_ID, DMALL_SHIN_MONZAEMON_FQID, DMALL_SHIN_MONZAEMON_FQNAME, DMALL_SHIN_MONZAEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_SHOOTMON_NAME, DMALL_SHOOTMON_ID, DMALL_SHOOTMON_FQID, DMALL_SHOOTMON_FQNAME, DMALL_SHOOTMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_SIESAMON_X_NAME, DMALL_SIESAMON_X_ID, DMALL_SIESAMON_X_FQID, DMALL_SIESAMON_X_FQNAME, DMALL_SIESAMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_SIRENMON_NAME, DMALL_SIRENMON_ID, DMALL_SIRENMON_FQID, DMALL_SIRENMON_FQNAME, DMALL_SIRENMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_SISTERMON_BLANC_NAME, DMALL_SISTERMON_BLANC_ID, DMALL_SISTERMON_BLANC_FQID, DMALL_SISTERMON_BLANC_FQNAME, DMALL_SISTERMON_BLANC_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_SKULL_BALUCHIMON_NAME, DMALL_SKULL_BALUCHIMON_ID, DMALL_SKULL_BALUCHIMON_FQID, DMALL_SKULL_BALUCHIMON_FQNAME, DMALL_SKULL_BALUCHIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_SKULL_GREYMON_NAME, DMALL_SKULL_GREYMON_ID, DMALL_SKULL_GREYMON_FQID, DMALL_SKULL_GREYMON_FQNAME, DMALL_SKULL_GREYMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_SKULLKNIGHTMON_NAME, DMALL_SKULLKNIGHTMON_ID, DMALL_SKULLKNIGHTMON_FQID, DMALL_SKULLKNIGHTMON_FQNAME, DMALL_SKULLKNIGHTMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_SKULL_MAMMON_NAME, DMALL_SKULL_MAMMON_ID, DMALL_SKULL_MAMMON_FQID, DMALL_SKULL_MAMMON_FQNAME, DMALL_SKULL_MAMMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_SKULL_MAMMON_X_NAME, DMALL_SKULL_MAMMON_X_ID, DMALL_SKULL_MAMMON_X_FQID, DMALL_SKULL_MAMMON_X_FQNAME, DMALL_SKULL_MAMMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_SLEIPMON_X_NAME, DMALL_SLEIPMON_X_ID, DMALL_SLEIPMON_X_FQID, DMALL_SLEIPMON_X_FQNAME, DMALL_SLEIPMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_SOLARMON_NAME, DMALL_SOLARMON_ID, DMALL_SOLARMON_FQID, DMALL_SOLARMON_FQNAME, DMALL_SOLARMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_SORCERYMON_NAME, DMALL_SORCERYMON_ID, DMALL_SORCERYMON_FQID, DMALL_SORCERYMON_FQNAME, DMALL_SORCERYMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_SOULMON_NAME, DMALL_SOULMON_ID, DMALL_SOULMON_FQID, DMALL_SOULMON_FQNAME, DMALL_SOULMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_STARMON_NAME, DMALL_STARMON_ID, DMALL_STARMON_FQID, DMALL_STARMON_FQNAME, DMALL_STARMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_STIFFILMON_NAME, DMALL_STIFFILMON_ID, DMALL_STIFFILMON_FQID, DMALL_STIFFILMON_FQNAME, DMALL_STIFFILMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_SUBMARINMON_NAME, DMALL_SUBMARINMON_ID, DMALL_SUBMARINMON_FQID, DMALL_SUBMARINMON_FQNAME, DMALL_SUBMARINMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_SUNAMON_NAME, DMALL_SUNAMON_ID, DMALL_SUNAMON_FQID, DMALL_SUNAMON_FQNAME, DMALL_SUNAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_SUNARIZAMON_NAME, DMALL_SUNARIZAMON_ID, DMALL_SUNARIZAMON_FQID, DMALL_SUNARIZAMON_FQNAME, DMALL_SUNARIZAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_SUNFLOWMON_NAME, DMALL_SUNFLOWMON_ID, DMALL_SUNFLOWMON_FQID, DMALL_SUNFLOWMON_FQNAME, DMALL_SUNFLOWMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_SUNMON_NAME, DMALL_SUNMON_ID, DMALL_SUNMON_FQID, DMALL_SUNMON_FQNAME, DMALL_SUNMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_SUPERSTARMON_NAME, DMALL_SUPERSTARMON_ID, DMALL_SUPERSTARMON_FQID, DMALL_SUPERSTARMON_FQNAME, DMALL_SUPERSTARMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_SUSANOOMON_NAME, DMALL_SUSANOOMON_ID, DMALL_SUSANOOMON_FQID, DMALL_SUSANOOMON_FQNAME, DMALL_SUSANOOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_SWIMMON_NAME, DMALL_SWIMMON_ID, DMALL_SWIMMON_FQID, DMALL_SWIMMON_FQNAME, DMALL_SWIMMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_TAILMON_NAME, DMALL_TAILMON_ID, DMALL_TAILMON_FQID, DMALL_TAILMON_FQNAME, DMALL_TAILMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_TAILMON_X_NAME, DMALL_TAILMON_X_ID, DMALL_TAILMON_X_FQID, DMALL_TAILMON_X_FQNAME, DMALL_TAILMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_TANEMON_NAME, DMALL_TANEMON_ID, DMALL_TANEMON_FQID, DMALL_TANEMON_FQNAME, DMALL_TANEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_TANKMON_NAME, DMALL_TANKMON_ID, DMALL_TANKMON_FQID, DMALL_TANKMON_FQNAME, DMALL_TANKMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_TARGETMON_NAME, DMALL_TARGETMON_ID, DMALL_TARGETMON_FQID, DMALL_TARGETMON_FQNAME, DMALL_TARGETMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_TEKKAMON_NAME, DMALL_TEKKAMON_ID, DMALL_TEKKAMON_FQID, DMALL_TEKKAMON_FQNAME, DMALL_TEKKAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_TENTOMON_NAME, DMALL_TENTOMON_ID, DMALL_TENTOMON_FQID, DMALL_TENTOMON_FQNAME, DMALL_TENTOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_TERRIERMON_NAME, DMALL_TERRIERMON_ID, DMALL_TERRIERMON_FQID, DMALL_TERRIERMON_FQNAME, DMALL_TERRIERMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_TERRIERMON_X_NAME, DMALL_TERRIERMON_X_ID, DMALL_TERRIERMON_X_FQID, DMALL_TERRIERMON_X_FQNAME, DMALL_TERRIERMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_THUNDERBALLMON_NAME, DMALL_THUNDERBALLMON_ID, DMALL_THUNDERBALLMON_FQID, DMALL_THUNDERBALLMON_FQNAME, DMALL_THUNDERBALLMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_TIA_LUDOMON_NAME, DMALL_TIA_LUDOMON_ID, DMALL_TIA_LUDOMON_FQID, DMALL_TIA_LUDOMON_FQNAME, DMALL_TIA_LUDOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_TIGER_VESPAMON_NAME, DMALL_TIGER_VESPAMON_ID, DMALL_TIGER_VESPAMON_FQID, DMALL_TIGER_VESPAMON_FQNAME, DMALL_TIGER_VESPAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_TINKERMON_NAME, DMALL_TINKERMON_ID, DMALL_TINKERMON_FQID, DMALL_TINKERMON_FQNAME, DMALL_TINKERMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_TITAMON_NAME, DMALL_TITAMON_ID, DMALL_TITAMON_FQID, DMALL_TITAMON_FQNAME, DMALL_TITAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_TOBIUMON_NAME, DMALL_TOBIUMON_ID, DMALL_TOBIUMON_FQID, DMALL_TOBIUMON_FQNAME, DMALL_TOBIUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_TOBUCATMON_NAME, DMALL_TOBUCATMON_ID, DMALL_TOBUCATMON_FQID, DMALL_TOBUCATMON_FQNAME, DMALL_TOBUCATMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_TOGEMON_NAME, DMALL_TOGEMON_ID, DMALL_TOGEMON_FQID, DMALL_TOGEMON_FQNAME, DMALL_TOGEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_TOGEMON_X_NAME, DMALL_TOGEMON_X_ID, DMALL_TOGEMON_X_FQID, DMALL_TOGEMON_X_FQNAME, DMALL_TOGEMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_TOKOMON_X_NAME, DMALL_TOKOMON_X_ID, DMALL_TOKOMON_X_FQID, DMALL_TOKOMON_X_FQNAME, DMALL_TOKOMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_TONOSAMA_GEKOMON_NAME, DMALL_TONOSAMA_GEKOMON_ID, DMALL_TONOSAMA_GEKOMON_FQID, DMALL_TONOSAMA_GEKOMON_FQNAME, DMALL_TONOSAMA_GEKOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_TORIKARA_BALLMON_NAME, DMALL_TORIKARA_BALLMON_ID, DMALL_TORIKARA_BALLMON_FQID, DMALL_TORIKARA_BALLMON_FQNAME, DMALL_TORIKARA_BALLMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_TORTAMON_NAME, DMALL_TORTAMON_ID, DMALL_TORTAMON_FQID, DMALL_TORTAMON_FQNAME, DMALL_TORTAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_TOYAGUMON_BLACK_NAME, DMALL_TOYAGUMON_BLACK_ID, DMALL_TOYAGUMON_BLACK_FQID, DMALL_TOYAGUMON_BLACK_FQNAME, DMALL_TOYAGUMON_BLACK_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_TOYAGUMON_NAME, DMALL_TOYAGUMON_ID, DMALL_TOYAGUMON_FQID, DMALL_TOYAGUMON_FQNAME, DMALL_TOYAGUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_TRICERAMON_NAME, DMALL_TRICERAMON_ID, DMALL_TRICERAMON_FQID, DMALL_TRICERAMON_FQNAME, DMALL_TRICERAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_TRICERAMON_X_NAME, DMALL_TRICERAMON_X_ID, DMALL_TRICERAMON_X_FQID, DMALL_TRICERAMON_X_FQNAME, DMALL_TRICERAMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_TROOPMON_NAME, DMALL_TROOPMON_ID, DMALL_TROOPMON_FQID, DMALL_TROOPMON_FQNAME, DMALL_TROOPMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_TSUBUMON_NAME, DMALL_TSUBUMON_ID, DMALL_TSUBUMON_FQID, DMALL_TSUBUMON_FQNAME, DMALL_TSUBUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_TSUCHIDARUMON_NAME, DMALL_TSUCHIDARUMON_ID, DMALL_TSUCHIDARUMON_FQID, DMALL_TSUCHIDARUMON_FQNAME, DMALL_TSUCHIDARUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_TSUMEMON_NAME, DMALL_TSUMEMON_ID, DMALL_TSUMEMON_FQID, DMALL_TSUMEMON_FQNAME, DMALL_TSUMEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_TSUNOMON_NAME, DMALL_TSUNOMON_ID, DMALL_TSUNOMON_FQID, DMALL_TSUNOMON_FQNAME, DMALL_TSUNOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_TUNOMON_NAME, DMALL_TUNOMON_ID, DMALL_TUNOMON_FQID, DMALL_TUNOMON_FQNAME, DMALL_TUNOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_TURUIEMON_NAME, DMALL_TURUIEMON_ID, DMALL_TURUIEMON_FQID, DMALL_TURUIEMON_FQNAME, DMALL_TURUIEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_TYLOMON_X_NAME, DMALL_TYLOMON_X_ID, DMALL_TYLOMON_X_FQID, DMALL_TYLOMON_X_FQNAME, DMALL_TYLOMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_TYRANNOMON_NAME, DMALL_TYRANNOMON_ID, DMALL_TYRANNOMON_FQID, DMALL_TYRANNOMON_FQNAME, DMALL_TYRANNOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_TYRANNOMON_X_NAME, DMALL_TYRANNOMON_X_ID, DMALL_TYRANNOMON_X_FQID, DMALL_TYRANNOMON_X_FQNAME, DMALL_TYRANNOMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_TYRANOMON_NAME, DMALL_TYRANOMON_ID, DMALL_TYRANOMON_FQID, DMALL_TYRANOMON_FQNAME, DMALL_TYRANOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_TYRANOMON_X_NAME, DMALL_TYRANOMON_X_ID, DMALL_TYRANOMON_X_FQID, DMALL_TYRANOMON_X_FQNAME, DMALL_TYRANOMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_ULFORCE_V_DRAMON_NAME, DMALL_ULFORCE_V_DRAMON_ID, DMALL_ULFORCE_V_DRAMON_FQID, DMALL_ULFORCE_V_DRAMON_FQNAME, DMALL_ULFORCE_V_DRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_ULFORCE_V_DRAMON_X_NAME, DMALL_ULFORCE_V_DRAMON_X_ID, DMALL_ULFORCE_V_DRAMON_X_FQID, DMALL_ULFORCE_V_DRAMON_X_FQNAME, DMALL_ULFORCE_V_DRAMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_ULTIMATE_BRACHIMON_NAME, DMALL_ULTIMATE_BRACHIMON_ID, DMALL_ULTIMATE_BRACHIMON_FQID, DMALL_ULTIMATE_BRACHIMON_FQNAME, DMALL_ULTIMATE_BRACHIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_UPAMON_NAME, DMALL_UPAMON_ID, DMALL_UPAMON_FQID, DMALL_UPAMON_FQNAME, DMALL_UPAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_VADEMON_NAME, DMALL_VADEMON_ID, DMALL_VADEMON_FQID, DMALL_VADEMON_FQNAME, DMALL_VADEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_VALDURMON_NAME, DMALL_VALDURMON_ID, DMALL_VALDURMON_FQID, DMALL_VALDURMON_FQNAME, DMALL_VALDURMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_VAMDEMON_NAME, DMALL_VAMDEMON_ID, DMALL_VAMDEMON_FQID, DMALL_VAMDEMON_FQNAME, DMALL_VAMDEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_VAMDEMON_X_NAME, DMALL_VAMDEMON_X_ID, DMALL_VAMDEMON_X_FQID, DMALL_VAMDEMON_X_FQNAME, DMALL_VAMDEMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_V_DRAMON_BLACK_NAME, DMALL_V_DRAMON_BLACK_ID, DMALL_V_DRAMON_BLACK_FQID, DMALL_V_DRAMON_BLACK_FQNAME, DMALL_V_DRAMON_BLACK_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_V_DRAMON_NAME, DMALL_V_DRAMON_ID, DMALL_V_DRAMON_FQID, DMALL_V_DRAMON_FQNAME, DMALL_V_DRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_VEGIMON_NAME, DMALL_VEGIMON_ID, DMALL_VEGIMON_FQID, DMALL_VEGIMON_FQNAME, DMALL_VEGIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_VELGRMON_NAME, DMALL_VELGRMON_ID, DMALL_VELGRMON_FQID, DMALL_VELGRMON_FQNAME, DMALL_VELGRMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_VENOM_VAMDEMON_NAME, DMALL_VENOM_VAMDEMON_ID, DMALL_VENOM_VAMDEMON_FQID, DMALL_VENOM_VAMDEMON_FQNAME, DMALL_VENOM_VAMDEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_VERMILLIMON_NAME, DMALL_VERMILLIMON_ID, DMALL_VERMILLIMON_FQID, DMALL_VERMILLIMON_FQNAME, DMALL_VERMILLIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_V_MON_NAME, DMALL_V_MON_ID, DMALL_V_MON_FQID, DMALL_V_MON_FQNAME, DMALL_V_MON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_VOLCANICDRAMON_NAME, DMALL_VOLCANICDRAMON_ID, DMALL_VOLCANICDRAMON_FQID, DMALL_VOLCANICDRAMON_FQNAME, DMALL_VOLCANICDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_VOLTO_BAUTAMON_NAME, DMALL_VOLTO_BAUTAMON_ID, DMALL_VOLTO_BAUTAMON_FQID, DMALL_VOLTO_BAUTAMON_FQNAME, DMALL_VOLTO_BAUTAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_VORVOMON_NAME, DMALL_VORVOMON_ID, DMALL_VORVOMON_FQID, DMALL_VORVOMON_FQNAME, DMALL_VORVOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_WANYAMON_NAME, DMALL_WANYAMON_ID, DMALL_WANYAMON_FQID, DMALL_WANYAMON_FQNAME, DMALL_WANYAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_WAR_GREYMON_NAME, DMALL_WAR_GREYMON_ID, DMALL_WAR_GREYMON_FQID, DMALL_WAR_GREYMON_FQNAME, DMALL_WAR_GREYMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_WAR_GREYMON_X_NAME, DMALL_WAR_GREYMON_X_ID, DMALL_WAR_GREYMON_X_FQID, DMALL_WAR_GREYMON_X_FQNAME, DMALL_WAR_GREYMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_WARU_MONZAEMON_NAME, DMALL_WARU_MONZAEMON_ID, DMALL_WARU_MONZAEMON_FQID, DMALL_WARU_MONZAEMON_FQNAME, DMALL_WARU_MONZAEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_WARU_SEADRAMON_NAME, DMALL_WARU_SEADRAMON_ID, DMALL_WARU_SEADRAMON_FQID, DMALL_WARU_SEADRAMON_FQNAME, DMALL_WARU_SEADRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_WASPMON_NAME, DMALL_WASPMON_ID, DMALL_WASPMON_FQID, DMALL_WASPMON_FQNAME, DMALL_WASPMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_WEREGARURUMON_BLACK_NAME, DMALL_WEREGARURUMON_BLACK_ID, DMALL_WEREGARURUMON_BLACK_FQID, DMALL_WEREGARURUMON_BLACK_FQNAME, DMALL_WEREGARURUMON_BLACK_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_WERE_GARURUMON_NAME, DMALL_WERE_GARURUMON_ID, DMALL_WERE_GARURUMON_FQID, DMALL_WERE_GARURUMON_FQNAME, DMALL_WERE_GARURUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_WERE_GARURUMON_X_NAME, DMALL_WERE_GARURUMON_X_ID, DMALL_WERE_GARURUMON_X_FQID, DMALL_WERE_GARURUMON_X_FQNAME, DMALL_WERE_GARURUMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_WHAMON_NAME, DMALL_WHAMON_ID, DMALL_WHAMON_FQID, DMALL_WHAMON_FQNAME, DMALL_WHAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_WIZARMON_NAME, DMALL_WIZARMON_ID, DMALL_WIZARMON_FQID, DMALL_WIZARMON_FQNAME, DMALL_WIZARMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_WIZARMON_X_NAME, DMALL_WIZARMON_X_ID, DMALL_WIZARMON_X_FQID, DMALL_WIZARMON_X_FQNAME, DMALL_WIZARMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_WOODMON_NAME, DMALL_WOODMON_ID, DMALL_WOODMON_FQID, DMALL_WOODMON_FQNAME, DMALL_WOODMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_WORMMON_NAME, DMALL_WORMMON_ID, DMALL_WORMMON_FQID, DMALL_WORMMON_FQNAME, DMALL_WORMMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_XIAOMON_NAME, DMALL_XIAOMON_ID, DMALL_XIAOMON_FQID, DMALL_XIAOMON_FQNAME, DMALL_XIAOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_XV_MON_BLACK_NAME, DMALL_XV_MON_BLACK_ID, DMALL_XV_MON_BLACK_FQID, DMALL_XV_MON_BLACK_FQNAME, DMALL_XV_MON_BLACK_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_XV_MON_NAME, DMALL_XV_MON_ID, DMALL_XV_MON_FQID, DMALL_XV_MON_FQNAME, DMALL_XV_MON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_YAAMON_NAME, DMALL_YAAMON_ID, DMALL_YAAMON_FQID, DMALL_YAAMON_FQNAME, DMALL_YAAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_YANMAMON_NAME, DMALL_YANMAMON_ID, DMALL_YANMAMON_FQID, DMALL_YANMAMON_FQNAME, DMALL_YANMAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_YATAGARAMON_2006_NAME, DMALL_YATAGARAMON_2006_ID, DMALL_YATAGARAMON_2006_FQID, DMALL_YATAGARAMON_2006_FQNAME, DMALL_YATAGARAMON_2006_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_YATAGARAMON_NAME, DMALL_YATAGARAMON_ID, DMALL_YATAGARAMON_FQID, DMALL_YATAGARAMON_FQNAME, DMALL_YATAGARAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_YOUKOMON_NAME, DMALL_YOUKOMON_ID, DMALL_YOUKOMON_FQID, DMALL_YOUKOMON_FQNAME, DMALL_YOUKOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_YUKI_AGUMON_NAME, DMALL_YUKI_AGUMON_ID, DMALL_YUKI_AGUMON_FQID, DMALL_YUKI_AGUMON_FQNAME, DMALL_YUKI_AGUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_YUKIDARUMON_NAME, DMALL_YUKIDARUMON_ID, DMALL_YUKIDARUMON_FQID, DMALL_YUKIDARUMON_FQNAME, DMALL_YUKIDARUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_YUKIMI_BOTAMON_NAME, DMALL_YUKIMI_BOTAMON_ID, DMALL_YUKIMI_BOTAMON_FQID, DMALL_YUKIMI_BOTAMON_FQNAME, DMALL_YUKIMI_BOTAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_YURAMON_NAME, DMALL_YURAMON_ID, DMALL_YURAMON_FQID, DMALL_YURAMON_FQNAME, DMALL_YURAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_ZASSOUMON_NAME, DMALL_ZASSOUMON_ID, DMALL_ZASSOUMON_FQID, DMALL_ZASSOUMON_FQNAME, DMALL_ZASSOUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_ZENIMON_NAME, DMALL_ZENIMON_ID, DMALL_ZENIMON_FQID, DMALL_ZENIMON_FQNAME, DMALL_ZENIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_ZERIMON_NAME, DMALL_ZERIMON_ID, DMALL_ZERIMON_FQID, DMALL_ZERIMON_FQNAME, DMALL_ZERIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_ZUDOMON_NAME, DMALL_ZUDOMON_ID, DMALL_ZUDOMON_FQID, DMALL_ZUDOMON_FQNAME, DMALL_ZUDOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        { DMALL_ZURUMON_NAME, DMALL_ZURUMON_ID, DMALL_ZURUMON_FQID, DMALL_ZURUMON_FQNAME, DMALL_ZURUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },
        
    };
            inline static constexpr char ALT_DMALL_AEGISDRAMON_FQID_ARR[] = "dmall:aegisdramon";
    inline static constexpr const char* ALT_DMALL_AEGISDRAMON_FQID = ALT_DMALL_AEGISDRAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_AEGISDRAMON_FQID_LEN = sizeof(ALT_DMALL_AEGISDRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_AEGISDRAMON_FQNAME_ARR[] = "dmall:Aegisdramon";
    inline static constexpr const char* ALT_DMALL_AEGISDRAMON_FQNAME = ALT_DMALL_AEGISDRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_AEGISDRAMON_FQNAME_LEN = sizeof(ALT_DMALL_AEGISDRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_AERO_V_DRAMON_FQID_ARR[] = "dmall:aero_v_dramon";
    inline static constexpr const char* ALT_DMALL_AERO_V_DRAMON_FQID = ALT_DMALL_AERO_V_DRAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_AERO_V_DRAMON_FQID_LEN = sizeof(ALT_DMALL_AERO_V_DRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_AERO_V_DRAMON_FQNAME_ARR[] = "dmall:Aero V-dramon";
    inline static constexpr const char* ALT_DMALL_AERO_V_DRAMON_FQNAME = ALT_DMALL_AERO_V_DRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_AERO_V_DRAMON_FQNAME_LEN = sizeof(ALT_DMALL_AERO_V_DRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_AGUMON_2006_FQID_ARR[] = "dmall:agumon_2006";
    inline static constexpr const char* ALT_DMALL_AGUMON_2006_FQID = ALT_DMALL_AGUMON_2006_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_AGUMON_2006_FQID_LEN = sizeof(ALT_DMALL_AGUMON_2006_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_AGUMON_2006_FQNAME_ARR[] = "dmall:Agumon (2006)";
    inline static constexpr const char* ALT_DMALL_AGUMON_2006_FQNAME = ALT_DMALL_AGUMON_2006_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_AGUMON_2006_FQNAME_LEN = sizeof(ALT_DMALL_AGUMON_2006_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_AGUMON_BLACK_FQID_ARR[] = "dmall:agumon_black";
    inline static constexpr const char* ALT_DMALL_AGUMON_BLACK_FQID = ALT_DMALL_AGUMON_BLACK_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_AGUMON_BLACK_FQID_LEN = sizeof(ALT_DMALL_AGUMON_BLACK_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_AGUMON_BLACK_FQNAME_ARR[] = "dmall:Agumon (Black)";
    inline static constexpr const char* ALT_DMALL_AGUMON_BLACK_FQNAME = ALT_DMALL_AGUMON_BLACK_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_AGUMON_BLACK_FQNAME_LEN = sizeof(ALT_DMALL_AGUMON_BLACK_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_AGUMON_BLACK_X_FQID_ARR[] = "dmall:agumon_black_x";
    inline static constexpr const char* ALT_DMALL_AGUMON_BLACK_X_FQID = ALT_DMALL_AGUMON_BLACK_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_AGUMON_BLACK_X_FQID_LEN = sizeof(ALT_DMALL_AGUMON_BLACK_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_AGUMON_BLACK_X_FQNAME_ARR[] = "dmall:Agumon (Black) X";
    inline static constexpr const char* ALT_DMALL_AGUMON_BLACK_X_FQNAME = ALT_DMALL_AGUMON_BLACK_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_AGUMON_BLACK_X_FQNAME_LEN = sizeof(ALT_DMALL_AGUMON_BLACK_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_AGUMON_FQID_ARR[] = "dmall:agumon";
    inline static constexpr const char* ALT_DMALL_AGUMON_FQID = ALT_DMALL_AGUMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_AGUMON_FQID_LEN = sizeof(ALT_DMALL_AGUMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_AGUMON_FQNAME_ARR[] = "dmall:Agumon";
    inline static constexpr const char* ALT_DMALL_AGUMON_FQNAME = ALT_DMALL_AGUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_AGUMON_FQNAME_LEN = sizeof(ALT_DMALL_AGUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_AGUMON_X_FQID_ARR[] = "dmall:agumon_x";
    inline static constexpr const char* ALT_DMALL_AGUMON_X_FQID = ALT_DMALL_AGUMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_AGUMON_X_FQID_LEN = sizeof(ALT_DMALL_AGUMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_AGUMON_X_FQNAME_ARR[] = "dmall:Agumon X";
    inline static constexpr const char* ALT_DMALL_AGUMON_X_FQNAME = ALT_DMALL_AGUMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_AGUMON_X_FQNAME_LEN = sizeof(ALT_DMALL_AGUMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_AGUMON_YUKI_NO_KIZUNA_FQID_ARR[] = "dmall:agumon_yuki_no_kizuna";
    inline static constexpr const char* ALT_DMALL_AGUMON_YUKI_NO_KIZUNA_FQID = ALT_DMALL_AGUMON_YUKI_NO_KIZUNA_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_AGUMON_YUKI_NO_KIZUNA_FQID_LEN = sizeof(ALT_DMALL_AGUMON_YUKI_NO_KIZUNA_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_AGUMON_YUKI_NO_KIZUNA_FQNAME_ARR[] = "dmall:Agumon - Yuki no Kizuna";
    inline static constexpr const char* ALT_DMALL_AGUMON_YUKI_NO_KIZUNA_FQNAME = ALT_DMALL_AGUMON_YUKI_NO_KIZUNA_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_AGUMON_YUKI_NO_KIZUNA_FQNAME_LEN = sizeof(ALT_DMALL_AGUMON_YUKI_NO_KIZUNA_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_AIRDRAMON_FQID_ARR[] = "dmall:airdramon";
    inline static constexpr const char* ALT_DMALL_AIRDRAMON_FQID = ALT_DMALL_AIRDRAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_AIRDRAMON_FQID_LEN = sizeof(ALT_DMALL_AIRDRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_AIRDRAMON_FQNAME_ARR[] = "dmall:Airdramon";
    inline static constexpr const char* ALT_DMALL_AIRDRAMON_FQNAME = ALT_DMALL_AIRDRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_AIRDRAMON_FQNAME_LEN = sizeof(ALT_DMALL_AIRDRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_ALGOMON_ADULT_FQID_ARR[] = "dmall:algomon_adult";
    inline static constexpr const char* ALT_DMALL_ALGOMON_ADULT_FQID = ALT_DMALL_ALGOMON_ADULT_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_ALGOMON_ADULT_FQID_LEN = sizeof(ALT_DMALL_ALGOMON_ADULT_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_ALGOMON_ADULT_FQNAME_ARR[] = "dmall:Algomon (Adult)";
    inline static constexpr const char* ALT_DMALL_ALGOMON_ADULT_FQNAME = ALT_DMALL_ALGOMON_ADULT_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_ALGOMON_ADULT_FQNAME_LEN = sizeof(ALT_DMALL_ALGOMON_ADULT_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_ALGOMON_BABYII_FQID_ARR[] = "dmall:algomon_babyii";
    inline static constexpr const char* ALT_DMALL_ALGOMON_BABYII_FQID = ALT_DMALL_ALGOMON_BABYII_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_ALGOMON_BABYII_FQID_LEN = sizeof(ALT_DMALL_ALGOMON_BABYII_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_ALGOMON_BABYII_FQNAME_ARR[] = "dmall:Algomon (BabyII)";
    inline static constexpr const char* ALT_DMALL_ALGOMON_BABYII_FQNAME = ALT_DMALL_ALGOMON_BABYII_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_ALGOMON_BABYII_FQNAME_LEN = sizeof(ALT_DMALL_ALGOMON_BABYII_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_ALGOMON_BABYI_FQID_ARR[] = "dmall:algomon_babyi";
    inline static constexpr const char* ALT_DMALL_ALGOMON_BABYI_FQID = ALT_DMALL_ALGOMON_BABYI_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_ALGOMON_BABYI_FQID_LEN = sizeof(ALT_DMALL_ALGOMON_BABYI_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_ALGOMON_BABYI_FQNAME_ARR[] = "dmall:Algomon (BabyI)";
    inline static constexpr const char* ALT_DMALL_ALGOMON_BABYI_FQNAME = ALT_DMALL_ALGOMON_BABYI_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_ALGOMON_BABYI_FQNAME_LEN = sizeof(ALT_DMALL_ALGOMON_BABYI_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_ALGOMON_CHILD_FQID_ARR[] = "dmall:algomon_child";
    inline static constexpr const char* ALT_DMALL_ALGOMON_CHILD_FQID = ALT_DMALL_ALGOMON_CHILD_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_ALGOMON_CHILD_FQID_LEN = sizeof(ALT_DMALL_ALGOMON_CHILD_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_ALGOMON_CHILD_FQNAME_ARR[] = "dmall:Algomon (Child)";
    inline static constexpr const char* ALT_DMALL_ALGOMON_CHILD_FQNAME = ALT_DMALL_ALGOMON_CHILD_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_ALGOMON_CHILD_FQNAME_LEN = sizeof(ALT_DMALL_ALGOMON_CHILD_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_ALGOMON_ULTIMATE_FQID_ARR[] = "dmall:algomon_ultimate";
    inline static constexpr const char* ALT_DMALL_ALGOMON_ULTIMATE_FQID = ALT_DMALL_ALGOMON_ULTIMATE_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_ALGOMON_ULTIMATE_FQID_LEN = sizeof(ALT_DMALL_ALGOMON_ULTIMATE_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_ALGOMON_ULTIMATE_FQNAME_ARR[] = "dmall:Algomon (Ultimate)";
    inline static constexpr const char* ALT_DMALL_ALGOMON_ULTIMATE_FQNAME = ALT_DMALL_ALGOMON_ULTIMATE_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_ALGOMON_ULTIMATE_FQNAME_LEN = sizeof(ALT_DMALL_ALGOMON_ULTIMATE_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_ALLOMON_X_FQID_ARR[] = "dmall:allomon_x";
    inline static constexpr const char* ALT_DMALL_ALLOMON_X_FQID = ALT_DMALL_ALLOMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_ALLOMON_X_FQID_LEN = sizeof(ALT_DMALL_ALLOMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_ALLOMON_X_FQNAME_ARR[] = "dmall:Allomon X";
    inline static constexpr const char* ALT_DMALL_ALLOMON_X_FQNAME = ALT_DMALL_ALLOMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_ALLOMON_X_FQNAME_LEN = sizeof(ALT_DMALL_ALLOMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_ALPHAMON_OURYUKEN_FQID_ARR[] = "dmall:alphamon_ouryuken";
    inline static constexpr const char* ALT_DMALL_ALPHAMON_OURYUKEN_FQID = ALT_DMALL_ALPHAMON_OURYUKEN_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_ALPHAMON_OURYUKEN_FQID_LEN = sizeof(ALT_DMALL_ALPHAMON_OURYUKEN_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_ALPHAMON_OURYUKEN_FQNAME_ARR[] = "dmall:Alphamon Ouryuken";
    inline static constexpr const char* ALT_DMALL_ALPHAMON_OURYUKEN_FQNAME = ALT_DMALL_ALPHAMON_OURYUKEN_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_ALPHAMON_OURYUKEN_FQNAME_LEN = sizeof(ALT_DMALL_ALPHAMON_OURYUKEN_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_ALPHAMON_FQID_ARR[] = "dmall:alphamon";
    inline static constexpr const char* ALT_DMALL_ALPHAMON_FQID = ALT_DMALL_ALPHAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_ALPHAMON_FQID_LEN = sizeof(ALT_DMALL_ALPHAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_ALPHAMON_FQNAME_ARR[] = "dmall:Alphamon";
    inline static constexpr const char* ALT_DMALL_ALPHAMON_FQNAME = ALT_DMALL_ALPHAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_ALPHAMON_FQNAME_LEN = sizeof(ALT_DMALL_ALPHAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_ALRAUMON_FQID_ARR[] = "dmall:alraumon";
    inline static constexpr const char* ALT_DMALL_ALRAUMON_FQID = ALT_DMALL_ALRAUMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_ALRAUMON_FQID_LEN = sizeof(ALT_DMALL_ALRAUMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_ALRAUMON_FQNAME_ARR[] = "dmall:Alraumon";
    inline static constexpr const char* ALT_DMALL_ALRAUMON_FQNAME = ALT_DMALL_ALRAUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_ALRAUMON_FQNAME_LEN = sizeof(ALT_DMALL_ALRAUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_ANCIENT_BEATMON_FQID_ARR[] = "dmall:ancient_beatmon";
    inline static constexpr const char* ALT_DMALL_ANCIENT_BEATMON_FQID = ALT_DMALL_ANCIENT_BEATMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_ANCIENT_BEATMON_FQID_LEN = sizeof(ALT_DMALL_ANCIENT_BEATMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_ANCIENT_BEATMON_FQNAME_ARR[] = "dmall:Ancient Beatmon";
    inline static constexpr const char* ALT_DMALL_ANCIENT_BEATMON_FQNAME = ALT_DMALL_ANCIENT_BEATMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_ANCIENT_BEATMON_FQNAME_LEN = sizeof(ALT_DMALL_ANCIENT_BEATMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_ANCIENT_MEGATHERIUMON_FQID_ARR[] = "dmall:ancient_megatheriumon";
    inline static constexpr const char* ALT_DMALL_ANCIENT_MEGATHERIUMON_FQID = ALT_DMALL_ANCIENT_MEGATHERIUMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_ANCIENT_MEGATHERIUMON_FQID_LEN = sizeof(ALT_DMALL_ANCIENT_MEGATHERIUMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_ANCIENT_MEGATHERIUMON_FQNAME_ARR[] = "dmall:Ancient Megatheriumon";
    inline static constexpr const char* ALT_DMALL_ANCIENT_MEGATHERIUMON_FQNAME = ALT_DMALL_ANCIENT_MEGATHERIUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_ANCIENT_MEGATHERIUMON_FQNAME_LEN = sizeof(ALT_DMALL_ANCIENT_MEGATHERIUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_ANCIENT_MERMAIMON_FQID_ARR[] = "dmall:ancient_mermaimon";
    inline static constexpr const char* ALT_DMALL_ANCIENT_MERMAIMON_FQID = ALT_DMALL_ANCIENT_MERMAIMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_ANCIENT_MERMAIMON_FQID_LEN = sizeof(ALT_DMALL_ANCIENT_MERMAIMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_ANCIENT_MERMAIMON_FQNAME_ARR[] = "dmall:Ancient Mermaimon";
    inline static constexpr const char* ALT_DMALL_ANCIENT_MERMAIMON_FQNAME = ALT_DMALL_ANCIENT_MERMAIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_ANCIENT_MERMAIMON_FQNAME_LEN = sizeof(ALT_DMALL_ANCIENT_MERMAIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_ANCIENT_SPHINXMON_FQID_ARR[] = "dmall:ancient_sphinxmon";
    inline static constexpr const char* ALT_DMALL_ANCIENT_SPHINXMON_FQID = ALT_DMALL_ANCIENT_SPHINXMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_ANCIENT_SPHINXMON_FQID_LEN = sizeof(ALT_DMALL_ANCIENT_SPHINXMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_ANCIENT_SPHINXMON_FQNAME_ARR[] = "dmall:Ancient Sphinxmon";
    inline static constexpr const char* ALT_DMALL_ANCIENT_SPHINXMON_FQNAME = ALT_DMALL_ANCIENT_SPHINXMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_ANCIENT_SPHINXMON_FQNAME_LEN = sizeof(ALT_DMALL_ANCIENT_SPHINXMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_ANDIRAMON_DATA_FQID_ARR[] = "dmall:andiramon_data";
    inline static constexpr const char* ALT_DMALL_ANDIRAMON_DATA_FQID = ALT_DMALL_ANDIRAMON_DATA_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_ANDIRAMON_DATA_FQID_LEN = sizeof(ALT_DMALL_ANDIRAMON_DATA_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_ANDIRAMON_DATA_FQNAME_ARR[] = "dmall:Andiramon (Data)";
    inline static constexpr const char* ALT_DMALL_ANDIRAMON_DATA_FQNAME = ALT_DMALL_ANDIRAMON_DATA_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_ANDIRAMON_DATA_FQNAME_LEN = sizeof(ALT_DMALL_ANDIRAMON_DATA_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_ANDIRAMON_VIRUS_FQID_ARR[] = "dmall:andiramon_virus";
    inline static constexpr const char* ALT_DMALL_ANDIRAMON_VIRUS_FQID = ALT_DMALL_ANDIRAMON_VIRUS_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_ANDIRAMON_VIRUS_FQID_LEN = sizeof(ALT_DMALL_ANDIRAMON_VIRUS_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_ANDIRAMON_VIRUS_FQNAME_ARR[] = "dmall:Andiramon (Virus)";
    inline static constexpr const char* ALT_DMALL_ANDIRAMON_VIRUS_FQNAME = ALT_DMALL_ANDIRAMON_VIRUS_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_ANDIRAMON_VIRUS_FQNAME_LEN = sizeof(ALT_DMALL_ANDIRAMON_VIRUS_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_ANDROMON_FQID_ARR[] = "dmall:andromon";
    inline static constexpr const char* ALT_DMALL_ANDROMON_FQID = ALT_DMALL_ANDROMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_ANDROMON_FQID_LEN = sizeof(ALT_DMALL_ANDROMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_ANDROMON_FQNAME_ARR[] = "dmall:Andromon";
    inline static constexpr const char* ALT_DMALL_ANDROMON_FQNAME = ALT_DMALL_ANDROMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_ANDROMON_FQNAME_LEN = sizeof(ALT_DMALL_ANDROMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_ANGEMON_FQID_ARR[] = "dmall:angemon";
    inline static constexpr const char* ALT_DMALL_ANGEMON_FQID = ALT_DMALL_ANGEMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_ANGEMON_FQID_LEN = sizeof(ALT_DMALL_ANGEMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_ANGEMON_FQNAME_ARR[] = "dmall:Angemon";
    inline static constexpr const char* ALT_DMALL_ANGEMON_FQNAME = ALT_DMALL_ANGEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_ANGEMON_FQNAME_LEN = sizeof(ALT_DMALL_ANGEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_ANGEWOMON_FQID_ARR[] = "dmall:angewomon";
    inline static constexpr const char* ALT_DMALL_ANGEWOMON_FQID = ALT_DMALL_ANGEWOMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_ANGEWOMON_FQID_LEN = sizeof(ALT_DMALL_ANGEWOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_ANGEWOMON_FQNAME_ARR[] = "dmall:Angewomon";
    inline static constexpr const char* ALT_DMALL_ANGEWOMON_FQNAME = ALT_DMALL_ANGEWOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_ANGEWOMON_FQNAME_LEN = sizeof(ALT_DMALL_ANGEWOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_ANGEWOMON_X_FQID_ARR[] = "dmall:angewomon_x";
    inline static constexpr const char* ALT_DMALL_ANGEWOMON_X_FQID = ALT_DMALL_ANGEWOMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_ANGEWOMON_X_FQID_LEN = sizeof(ALT_DMALL_ANGEWOMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_ANGEWOMON_X_FQNAME_ARR[] = "dmall:Angewomon X";
    inline static constexpr const char* ALT_DMALL_ANGEWOMON_X_FQNAME = ALT_DMALL_ANGEWOMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_ANGEWOMON_X_FQNAME_LEN = sizeof(ALT_DMALL_ANGEWOMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_ANOMALOCARIMON_FQID_ARR[] = "dmall:anomalocarimon";
    inline static constexpr const char* ALT_DMALL_ANOMALOCARIMON_FQID = ALT_DMALL_ANOMALOCARIMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_ANOMALOCARIMON_FQID_LEN = sizeof(ALT_DMALL_ANOMALOCARIMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_ANOMALOCARIMON_FQNAME_ARR[] = "dmall:Anomalocarimon";
    inline static constexpr const char* ALT_DMALL_ANOMALOCARIMON_FQNAME = ALT_DMALL_ANOMALOCARIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_ANOMALOCARIMON_FQNAME_LEN = sizeof(ALT_DMALL_ANOMALOCARIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_ANOMALOCARIMON_X_FQID_ARR[] = "dmall:anomalocarimon_x";
    inline static constexpr const char* ALT_DMALL_ANOMALOCARIMON_X_FQID = ALT_DMALL_ANOMALOCARIMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_ANOMALOCARIMON_X_FQID_LEN = sizeof(ALT_DMALL_ANOMALOCARIMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_ANOMALOCARIMON_X_FQNAME_ARR[] = "dmall:Anomalocarimon X";
    inline static constexpr const char* ALT_DMALL_ANOMALOCARIMON_X_FQNAME = ALT_DMALL_ANOMALOCARIMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_ANOMALOCARIMON_X_FQNAME_LEN = sizeof(ALT_DMALL_ANOMALOCARIMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_APOCALYMON_FQID_ARR[] = "dmall:apocalymon";
    inline static constexpr const char* ALT_DMALL_APOCALYMON_FQID = ALT_DMALL_APOCALYMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_APOCALYMON_FQID_LEN = sizeof(ALT_DMALL_APOCALYMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_APOCALYMON_FQNAME_ARR[] = "dmall:Apocalymon";
    inline static constexpr const char* ALT_DMALL_APOCALYMON_FQNAME = ALT_DMALL_APOCALYMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_APOCALYMON_FQNAME_LEN = sizeof(ALT_DMALL_APOCALYMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_APOLLOMON_FQID_ARR[] = "dmall:apollomon";
    inline static constexpr const char* ALT_DMALL_APOLLOMON_FQID = ALT_DMALL_APOLLOMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_APOLLOMON_FQID_LEN = sizeof(ALT_DMALL_APOLLOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_APOLLOMON_FQNAME_ARR[] = "dmall:Apollomon";
    inline static constexpr const char* ALT_DMALL_APOLLOMON_FQNAME = ALT_DMALL_APOLLOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_APOLLOMON_FQNAME_LEN = sizeof(ALT_DMALL_APOLLOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_ARCHNEMON_FQID_ARR[] = "dmall:archnemon";
    inline static constexpr const char* ALT_DMALL_ARCHNEMON_FQID = ALT_DMALL_ARCHNEMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_ARCHNEMON_FQID_LEN = sizeof(ALT_DMALL_ARCHNEMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_ARCHNEMON_FQNAME_ARR[] = "dmall:Archnemon";
    inline static constexpr const char* ALT_DMALL_ARCHNEMON_FQNAME = ALT_DMALL_ARCHNEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_ARCHNEMON_FQNAME_LEN = sizeof(ALT_DMALL_ARCHNEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_ARKADIMON_BABY_FQID_ARR[] = "dmall:arkadimon_baby";
    inline static constexpr const char* ALT_DMALL_ARKADIMON_BABY_FQID = ALT_DMALL_ARKADIMON_BABY_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_ARKADIMON_BABY_FQID_LEN = sizeof(ALT_DMALL_ARKADIMON_BABY_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_ARKADIMON_BABY_FQNAME_ARR[] = "dmall:Arkadimon (Baby)";
    inline static constexpr const char* ALT_DMALL_ARKADIMON_BABY_FQNAME = ALT_DMALL_ARKADIMON_BABY_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_ARKADIMON_BABY_FQNAME_LEN = sizeof(ALT_DMALL_ARKADIMON_BABY_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_ARKADIMON_CHILD_FQID_ARR[] = "dmall:arkadimon_child";
    inline static constexpr const char* ALT_DMALL_ARKADIMON_CHILD_FQID = ALT_DMALL_ARKADIMON_CHILD_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_ARKADIMON_CHILD_FQID_LEN = sizeof(ALT_DMALL_ARKADIMON_CHILD_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_ARKADIMON_CHILD_FQNAME_ARR[] = "dmall:Arkadimon (Child)";
    inline static constexpr const char* ALT_DMALL_ARKADIMON_CHILD_FQNAME = ALT_DMALL_ARKADIMON_CHILD_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_ARKADIMON_CHILD_FQNAME_LEN = sizeof(ALT_DMALL_ARKADIMON_CHILD_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_ARMADIMON_FQID_ARR[] = "dmall:armadimon";
    inline static constexpr const char* ALT_DMALL_ARMADIMON_FQID = ALT_DMALL_ARMADIMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_ARMADIMON_FQID_LEN = sizeof(ALT_DMALL_ARMADIMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_ARMADIMON_FQNAME_ARR[] = "dmall:Armadimon";
    inline static constexpr const char* ALT_DMALL_ARMADIMON_FQNAME = ALT_DMALL_ARMADIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_ARMADIMON_FQNAME_LEN = sizeof(ALT_DMALL_ARMADIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_ARMAGEMON_FQID_ARR[] = "dmall:armagemon";
    inline static constexpr const char* ALT_DMALL_ARMAGEMON_FQID = ALT_DMALL_ARMAGEMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_ARMAGEMON_FQID_LEN = sizeof(ALT_DMALL_ARMAGEMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_ARMAGEMON_FQNAME_ARR[] = "dmall:Armagemon";
    inline static constexpr const char* ALT_DMALL_ARMAGEMON_FQNAME = ALT_DMALL_ARMAGEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_ARMAGEMON_FQNAME_LEN = sizeof(ALT_DMALL_ARMAGEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_ASTAMON_FQID_ARR[] = "dmall:astamon";
    inline static constexpr const char* ALT_DMALL_ASTAMON_FQID = ALT_DMALL_ASTAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_ASTAMON_FQID_LEN = sizeof(ALT_DMALL_ASTAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_ASTAMON_FQNAME_ARR[] = "dmall:Astamon";
    inline static constexpr const char* ALT_DMALL_ASTAMON_FQNAME = ALT_DMALL_ASTAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_ASTAMON_FQNAME_LEN = sizeof(ALT_DMALL_ASTAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_ASURAMON_FQID_ARR[] = "dmall:asuramon";
    inline static constexpr const char* ALT_DMALL_ASURAMON_FQID = ALT_DMALL_ASURAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_ASURAMON_FQID_LEN = sizeof(ALT_DMALL_ASURAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_ASURAMON_FQNAME_ARR[] = "dmall:Asuramon";
    inline static constexpr const char* ALT_DMALL_ASURAMON_FQNAME = ALT_DMALL_ASURAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_ASURAMON_FQNAME_LEN = sizeof(ALT_DMALL_ASURAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_ATLUR_KABUTERIMON_BLUE_FQID_ARR[] = "dmall:atlur_kabuterimon_blue";
    inline static constexpr const char* ALT_DMALL_ATLUR_KABUTERIMON_BLUE_FQID = ALT_DMALL_ATLUR_KABUTERIMON_BLUE_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_ATLUR_KABUTERIMON_BLUE_FQID_LEN = sizeof(ALT_DMALL_ATLUR_KABUTERIMON_BLUE_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_ATLUR_KABUTERIMON_BLUE_FQNAME_ARR[] = "dmall:Atlur Kabuterimon (Blue)";
    inline static constexpr const char* ALT_DMALL_ATLUR_KABUTERIMON_BLUE_FQNAME = ALT_DMALL_ATLUR_KABUTERIMON_BLUE_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_ATLUR_KABUTERIMON_BLUE_FQNAME_LEN = sizeof(ALT_DMALL_ATLUR_KABUTERIMON_BLUE_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_ATLUR_KABUTERIMON_RED_FQID_ARR[] = "dmall:atlur_kabuterimon_red";
    inline static constexpr const char* ALT_DMALL_ATLUR_KABUTERIMON_RED_FQID = ALT_DMALL_ATLUR_KABUTERIMON_RED_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_ATLUR_KABUTERIMON_RED_FQID_LEN = sizeof(ALT_DMALL_ATLUR_KABUTERIMON_RED_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_ATLUR_KABUTERIMON_RED_FQNAME_ARR[] = "dmall:Atlur Kabuterimon (Red)";
    inline static constexpr const char* ALT_DMALL_ATLUR_KABUTERIMON_RED_FQNAME = ALT_DMALL_ATLUR_KABUTERIMON_RED_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_ATLUR_KABUTERIMON_RED_FQNAME_LEN = sizeof(ALT_DMALL_ATLUR_KABUTERIMON_RED_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_AXEKNIGHTMON_FQID_ARR[] = "dmall:axeknightmon";
    inline static constexpr const char* ALT_DMALL_AXEKNIGHTMON_FQID = ALT_DMALL_AXEKNIGHTMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_AXEKNIGHTMON_FQID_LEN = sizeof(ALT_DMALL_AXEKNIGHTMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_AXEKNIGHTMON_FQNAME_ARR[] = "dmall:AxeKnightmon";
    inline static constexpr const char* ALT_DMALL_AXEKNIGHTMON_FQNAME = ALT_DMALL_AXEKNIGHTMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_AXEKNIGHTMON_FQNAME_LEN = sizeof(ALT_DMALL_AXEKNIGHTMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_BAALMON_FQID_ARR[] = "dmall:baalmon";
    inline static constexpr const char* ALT_DMALL_BAALMON_FQID = ALT_DMALL_BAALMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_BAALMON_FQID_LEN = sizeof(ALT_DMALL_BAALMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_BAALMON_FQNAME_ARR[] = "dmall:Baalmon";
    inline static constexpr const char* ALT_DMALL_BAALMON_FQNAME = ALT_DMALL_BAALMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_BAALMON_FQNAME_LEN = sizeof(ALT_DMALL_BAALMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_BABOONGAMON_FQID_ARR[] = "dmall:baboongamon";
    inline static constexpr const char* ALT_DMALL_BABOONGAMON_FQID = ALT_DMALL_BABOONGAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_BABOONGAMON_FQID_LEN = sizeof(ALT_DMALL_BABOONGAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_BABOONGAMON_FQNAME_ARR[] = "dmall:Baboongamon";
    inline static constexpr const char* ALT_DMALL_BABOONGAMON_FQNAME = ALT_DMALL_BABOONGAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_BABOONGAMON_FQNAME_LEN = sizeof(ALT_DMALL_BABOONGAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_BABYDMON_FQID_ARR[] = "dmall:babydmon";
    inline static constexpr const char* ALT_DMALL_BABYDMON_FQID = ALT_DMALL_BABYDMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_BABYDMON_FQID_LEN = sizeof(ALT_DMALL_BABYDMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_BABYDMON_FQNAME_ARR[] = "dmall:Babydmon";
    inline static constexpr const char* ALT_DMALL_BABYDMON_FQNAME = ALT_DMALL_BABYDMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_BABYDMON_FQNAME_LEN = sizeof(ALT_DMALL_BABYDMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_BAGRAMON_FQID_ARR[] = "dmall:bagramon";
    inline static constexpr const char* ALT_DMALL_BAGRAMON_FQID = ALT_DMALL_BAGRAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_BAGRAMON_FQID_LEN = sizeof(ALT_DMALL_BAGRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_BAGRAMON_FQNAME_ARR[] = "dmall:Bagramon";
    inline static constexpr const char* ALT_DMALL_BAGRAMON_FQNAME = ALT_DMALL_BAGRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_BAGRAMON_FQNAME_LEN = sizeof(ALT_DMALL_BAGRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_BAKEMON_FQID_ARR[] = "dmall:bakemon";
    inline static constexpr const char* ALT_DMALL_BAKEMON_FQID = ALT_DMALL_BAKEMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_BAKEMON_FQID_LEN = sizeof(ALT_DMALL_BAKEMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_BAKEMON_FQNAME_ARR[] = "dmall:Bakemon";
    inline static constexpr const char* ALT_DMALL_BAKEMON_FQNAME = ALT_DMALL_BAKEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_BAKEMON_FQNAME_LEN = sizeof(ALT_DMALL_BAKEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_BAKUMON_FQID_ARR[] = "dmall:bakumon";
    inline static constexpr const char* ALT_DMALL_BAKUMON_FQID = ALT_DMALL_BAKUMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_BAKUMON_FQID_LEN = sizeof(ALT_DMALL_BAKUMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_BAKUMON_FQNAME_ARR[] = "dmall:Bakumon";
    inline static constexpr const char* ALT_DMALL_BAKUMON_FQNAME = ALT_DMALL_BAKUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_BAKUMON_FQNAME_LEN = sizeof(ALT_DMALL_BAKUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_BANCHO_LEOMON_FQID_ARR[] = "dmall:bancho_leomon";
    inline static constexpr const char* ALT_DMALL_BANCHO_LEOMON_FQID = ALT_DMALL_BANCHO_LEOMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_BANCHO_LEOMON_FQID_LEN = sizeof(ALT_DMALL_BANCHO_LEOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_BANCHO_LEOMON_FQNAME_ARR[] = "dmall:Bancho Leomon";
    inline static constexpr const char* ALT_DMALL_BANCHO_LEOMON_FQNAME = ALT_DMALL_BANCHO_LEOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_BANCHO_LEOMON_FQNAME_LEN = sizeof(ALT_DMALL_BANCHO_LEOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_BANCHO_LILIMON_FQID_ARR[] = "dmall:bancho_lilimon";
    inline static constexpr const char* ALT_DMALL_BANCHO_LILIMON_FQID = ALT_DMALL_BANCHO_LILIMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_BANCHO_LILIMON_FQID_LEN = sizeof(ALT_DMALL_BANCHO_LILIMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_BANCHO_LILIMON_FQNAME_ARR[] = "dmall:Bancho Lilimon";
    inline static constexpr const char* ALT_DMALL_BANCHO_LILIMON_FQNAME = ALT_DMALL_BANCHO_LILIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_BANCHO_LILIMON_FQNAME_LEN = sizeof(ALT_DMALL_BANCHO_LILIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_BANCHO_MAMEMON_FQID_ARR[] = "dmall:bancho_mamemon";
    inline static constexpr const char* ALT_DMALL_BANCHO_MAMEMON_FQID = ALT_DMALL_BANCHO_MAMEMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_BANCHO_MAMEMON_FQID_LEN = sizeof(ALT_DMALL_BANCHO_MAMEMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_BANCHO_MAMEMON_FQNAME_ARR[] = "dmall:Bancho Mamemon";
    inline static constexpr const char* ALT_DMALL_BANCHO_MAMEMON_FQNAME = ALT_DMALL_BANCHO_MAMEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_BANCHO_MAMEMON_FQNAME_LEN = sizeof(ALT_DMALL_BANCHO_MAMEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_BARBAMON_FQID_ARR[] = "dmall:barbamon";
    inline static constexpr const char* ALT_DMALL_BARBAMON_FQID = ALT_DMALL_BARBAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_BARBAMON_FQID_LEN = sizeof(ALT_DMALL_BARBAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_BARBAMON_FQNAME_ARR[] = "dmall:Barbamon";
    inline static constexpr const char* ALT_DMALL_BARBAMON_FQNAME = ALT_DMALL_BARBAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_BARBAMON_FQNAME_LEN = sizeof(ALT_DMALL_BARBAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_BARBAMON_X_FQID_ARR[] = "dmall:barbamon_x";
    inline static constexpr const char* ALT_DMALL_BARBAMON_X_FQID = ALT_DMALL_BARBAMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_BARBAMON_X_FQID_LEN = sizeof(ALT_DMALL_BARBAMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_BARBAMON_X_FQNAME_ARR[] = "dmall:Barbamon X";
    inline static constexpr const char* ALT_DMALL_BARBAMON_X_FQNAME = ALT_DMALL_BARBAMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_BARBAMON_X_FQNAME_LEN = sizeof(ALT_DMALL_BARBAMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_BEARMON_FQID_ARR[] = "dmall:bearmon";
    inline static constexpr const char* ALT_DMALL_BEARMON_FQID = ALT_DMALL_BEARMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_BEARMON_FQID_LEN = sizeof(ALT_DMALL_BEARMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_BEARMON_FQNAME_ARR[] = "dmall:Bearmon";
    inline static constexpr const char* ALT_DMALL_BEARMON_FQNAME = ALT_DMALL_BEARMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_BEARMON_FQNAME_LEN = sizeof(ALT_DMALL_BEARMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_BEEL_STARMON_X_FQID_ARR[] = "dmall:beel_starmon_x";
    inline static constexpr const char* ALT_DMALL_BEEL_STARMON_X_FQID = ALT_DMALL_BEEL_STARMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_BEEL_STARMON_X_FQID_LEN = sizeof(ALT_DMALL_BEEL_STARMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_BEEL_STARMON_X_FQNAME_ARR[] = "dmall:Beel Starmon X";
    inline static constexpr const char* ALT_DMALL_BEEL_STARMON_X_FQNAME = ALT_DMALL_BEEL_STARMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_BEEL_STARMON_X_FQNAME_LEN = sizeof(ALT_DMALL_BEEL_STARMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_BEELZEBUMON_BLAST_MODE_FQID_ARR[] = "dmall:beelzebumon_blast_mode";
    inline static constexpr const char* ALT_DMALL_BEELZEBUMON_BLAST_MODE_FQID = ALT_DMALL_BEELZEBUMON_BLAST_MODE_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_BEELZEBUMON_BLAST_MODE_FQID_LEN = sizeof(ALT_DMALL_BEELZEBUMON_BLAST_MODE_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_BEELZEBUMON_BLAST_MODE_FQNAME_ARR[] = "dmall:Beelzebumon Blast Mode";
    inline static constexpr const char* ALT_DMALL_BEELZEBUMON_BLAST_MODE_FQNAME = ALT_DMALL_BEELZEBUMON_BLAST_MODE_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_BEELZEBUMON_BLAST_MODE_FQNAME_LEN = sizeof(ALT_DMALL_BEELZEBUMON_BLAST_MODE_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_BEELZEBUMON_FQID_ARR[] = "dmall:beelzebumon";
    inline static constexpr const char* ALT_DMALL_BEELZEBUMON_FQID = ALT_DMALL_BEELZEBUMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_BEELZEBUMON_FQID_LEN = sizeof(ALT_DMALL_BEELZEBUMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_BEELZEBUMON_FQNAME_ARR[] = "dmall:Beelzebumon";
    inline static constexpr const char* ALT_DMALL_BEELZEBUMON_FQNAME = ALT_DMALL_BEELZEBUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_BEELZEBUMON_FQNAME_LEN = sizeof(ALT_DMALL_BEELZEBUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_BEELZEBUMON_X_FQID_ARR[] = "dmall:beelzebumon_x";
    inline static constexpr const char* ALT_DMALL_BEELZEBUMON_X_FQID = ALT_DMALL_BEELZEBUMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_BEELZEBUMON_X_FQID_LEN = sizeof(ALT_DMALL_BEELZEBUMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_BEELZEBUMON_X_FQNAME_ARR[] = "dmall:Beelzebumon X";
    inline static constexpr const char* ALT_DMALL_BEELZEBUMON_X_FQNAME = ALT_DMALL_BEELZEBUMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_BEELZEBUMON_X_FQNAME_LEN = sizeof(ALT_DMALL_BEELZEBUMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_BELIAL_VAMDEMON_FQID_ARR[] = "dmall:belial_vamdemon";
    inline static constexpr const char* ALT_DMALL_BELIAL_VAMDEMON_FQID = ALT_DMALL_BELIAL_VAMDEMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_BELIAL_VAMDEMON_FQID_LEN = sizeof(ALT_DMALL_BELIAL_VAMDEMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_BELIAL_VAMDEMON_FQNAME_ARR[] = "dmall:Belial Vamdemon";
    inline static constexpr const char* ALT_DMALL_BELIAL_VAMDEMON_FQNAME = ALT_DMALL_BELIAL_VAMDEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_BELIAL_VAMDEMON_FQNAME_LEN = sizeof(ALT_DMALL_BELIAL_VAMDEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_BELPHEMON_RAGE_MODE_FQID_ARR[] = "dmall:belphemon_rage_mode";
    inline static constexpr const char* ALT_DMALL_BELPHEMON_RAGE_MODE_FQID = ALT_DMALL_BELPHEMON_RAGE_MODE_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_BELPHEMON_RAGE_MODE_FQID_LEN = sizeof(ALT_DMALL_BELPHEMON_RAGE_MODE_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_BELPHEMON_RAGE_MODE_FQNAME_ARR[] = "dmall:Belphemon Rage Mode";
    inline static constexpr const char* ALT_DMALL_BELPHEMON_RAGE_MODE_FQNAME = ALT_DMALL_BELPHEMON_RAGE_MODE_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_BELPHEMON_RAGE_MODE_FQNAME_LEN = sizeof(ALT_DMALL_BELPHEMON_RAGE_MODE_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_BELPHEMON_X_FQID_ARR[] = "dmall:belphemon_x";
    inline static constexpr const char* ALT_DMALL_BELPHEMON_X_FQID = ALT_DMALL_BELPHEMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_BELPHEMON_X_FQID_LEN = sizeof(ALT_DMALL_BELPHEMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_BELPHEMON_X_FQNAME_ARR[] = "dmall:Belphemon X";
    inline static constexpr const char* ALT_DMALL_BELPHEMON_X_FQNAME = ALT_DMALL_BELPHEMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_BELPHEMON_X_FQNAME_LEN = sizeof(ALT_DMALL_BELPHEMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_BEOWOLFMON_FQID_ARR[] = "dmall:beowolfmon";
    inline static constexpr const char* ALT_DMALL_BEOWOLFMON_FQID = ALT_DMALL_BEOWOLFMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_BEOWOLFMON_FQID_LEN = sizeof(ALT_DMALL_BEOWOLFMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_BEOWOLFMON_FQNAME_ARR[] = "dmall:Beowolfmon";
    inline static constexpr const char* ALT_DMALL_BEOWOLFMON_FQNAME = ALT_DMALL_BEOWOLFMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_BEOWOLFMON_FQNAME_LEN = sizeof(ALT_DMALL_BEOWOLFMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_BIBIMON_FQID_ARR[] = "dmall:bibimon";
    inline static constexpr const char* ALT_DMALL_BIBIMON_FQID = ALT_DMALL_BIBIMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_BIBIMON_FQID_LEN = sizeof(ALT_DMALL_BIBIMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_BIBIMON_FQNAME_ARR[] = "dmall:Bibimon";
    inline static constexpr const char* ALT_DMALL_BIBIMON_FQNAME = ALT_DMALL_BIBIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_BIBIMON_FQNAME_LEN = sizeof(ALT_DMALL_BIBIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_BIG_MAMEMON_FQID_ARR[] = "dmall:big_mamemon";
    inline static constexpr const char* ALT_DMALL_BIG_MAMEMON_FQID = ALT_DMALL_BIG_MAMEMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_BIG_MAMEMON_FQID_LEN = sizeof(ALT_DMALL_BIG_MAMEMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_BIG_MAMEMON_FQNAME_ARR[] = "dmall:Big Mamemon";
    inline static constexpr const char* ALT_DMALL_BIG_MAMEMON_FQNAME = ALT_DMALL_BIG_MAMEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_BIG_MAMEMON_FQNAME_LEN = sizeof(ALT_DMALL_BIG_MAMEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_BIRDRAMON_FQID_ARR[] = "dmall:birdramon";
    inline static constexpr const char* ALT_DMALL_BIRDRAMON_FQID = ALT_DMALL_BIRDRAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_BIRDRAMON_FQID_LEN = sizeof(ALT_DMALL_BIRDRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_BIRDRAMON_FQNAME_ARR[] = "dmall:Birdramon";
    inline static constexpr const char* ALT_DMALL_BIRDRAMON_FQNAME = ALT_DMALL_BIRDRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_BIRDRAMON_FQNAME_LEN = sizeof(ALT_DMALL_BIRDRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_BITMON_FQID_ARR[] = "dmall:bitmon";
    inline static constexpr const char* ALT_DMALL_BITMON_FQID = ALT_DMALL_BITMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_BITMON_FQID_LEN = sizeof(ALT_DMALL_BITMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_BITMON_FQNAME_ARR[] = "dmall:Bitmon";
    inline static constexpr const char* ALT_DMALL_BITMON_FQNAME = ALT_DMALL_BITMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_BITMON_FQNAME_LEN = sizeof(ALT_DMALL_BITMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_BLACK_GALGOMON_FQID_ARR[] = "dmall:black_galgomon";
    inline static constexpr const char* ALT_DMALL_BLACK_GALGOMON_FQID = ALT_DMALL_BLACK_GALGOMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_BLACK_GALGOMON_FQID_LEN = sizeof(ALT_DMALL_BLACK_GALGOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_BLACK_GALGOMON_FQNAME_ARR[] = "dmall:Black Galgomon";
    inline static constexpr const char* ALT_DMALL_BLACK_GALGOMON_FQNAME = ALT_DMALL_BLACK_GALGOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_BLACK_GALGOMON_FQNAME_LEN = sizeof(ALT_DMALL_BLACK_GALGOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_BLACK_GAOGAMON_FQID_ARR[] = "dmall:black_gaogamon";
    inline static constexpr const char* ALT_DMALL_BLACK_GAOGAMON_FQID = ALT_DMALL_BLACK_GAOGAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_BLACK_GAOGAMON_FQID_LEN = sizeof(ALT_DMALL_BLACK_GAOGAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_BLACK_GAOGAMON_FQNAME_ARR[] = "dmall:Black Gaogamon";
    inline static constexpr const char* ALT_DMALL_BLACK_GAOGAMON_FQNAME = ALT_DMALL_BLACK_GAOGAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_BLACK_GAOGAMON_FQNAME_LEN = sizeof(ALT_DMALL_BLACK_GAOGAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_BLACK_GROWMON_FQID_ARR[] = "dmall:black_growmon";
    inline static constexpr const char* ALT_DMALL_BLACK_GROWMON_FQID = ALT_DMALL_BLACK_GROWMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_BLACK_GROWMON_FQID_LEN = sizeof(ALT_DMALL_BLACK_GROWMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_BLACK_GROWMON_FQNAME_ARR[] = "dmall:Black Growmon";
    inline static constexpr const char* ALT_DMALL_BLACK_GROWMON_FQNAME = ALT_DMALL_BLACK_GROWMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_BLACK_GROWMON_FQNAME_LEN = sizeof(ALT_DMALL_BLACK_GROWMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_BLACK_GUILMON_FQID_ARR[] = "dmall:black_guilmon";
    inline static constexpr const char* ALT_DMALL_BLACK_GUILMON_FQID = ALT_DMALL_BLACK_GUILMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_BLACK_GUILMON_FQID_LEN = sizeof(ALT_DMALL_BLACK_GUILMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_BLACK_GUILMON_FQNAME_ARR[] = "dmall:Black Guilmon";
    inline static constexpr const char* ALT_DMALL_BLACK_GUILMON_FQNAME = ALT_DMALL_BLACK_GUILMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_BLACK_GUILMON_FQNAME_LEN = sizeof(ALT_DMALL_BLACK_GUILMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_BLACK_KING_NUMEMON_FQID_ARR[] = "dmall:black_king_numemon";
    inline static constexpr const char* ALT_DMALL_BLACK_KING_NUMEMON_FQID = ALT_DMALL_BLACK_KING_NUMEMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_BLACK_KING_NUMEMON_FQID_LEN = sizeof(ALT_DMALL_BLACK_KING_NUMEMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_BLACK_KING_NUMEMON_FQNAME_ARR[] = "dmall:Black King Numemon";
    inline static constexpr const char* ALT_DMALL_BLACK_KING_NUMEMON_FQNAME = ALT_DMALL_BLACK_KING_NUMEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_BLACK_KING_NUMEMON_FQNAME_LEN = sizeof(ALT_DMALL_BLACK_KING_NUMEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_BLACK_MACH_GAOGAMON_FQID_ARR[] = "dmall:black_mach_gaogamon";
    inline static constexpr const char* ALT_DMALL_BLACK_MACH_GAOGAMON_FQID = ALT_DMALL_BLACK_MACH_GAOGAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_BLACK_MACH_GAOGAMON_FQID_LEN = sizeof(ALT_DMALL_BLACK_MACH_GAOGAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_BLACK_MACH_GAOGAMON_FQNAME_ARR[] = "dmall:Black Mach Gaogamon";
    inline static constexpr const char* ALT_DMALL_BLACK_MACH_GAOGAMON_FQNAME = ALT_DMALL_BLACK_MACH_GAOGAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_BLACK_MACH_GAOGAMON_FQNAME_LEN = sizeof(ALT_DMALL_BLACK_MACH_GAOGAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_BLACK_MEGALO_GROWMON_FQID_ARR[] = "dmall:black_megalo_growmon";
    inline static constexpr const char* ALT_DMALL_BLACK_MEGALO_GROWMON_FQID = ALT_DMALL_BLACK_MEGALO_GROWMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_BLACK_MEGALO_GROWMON_FQID_LEN = sizeof(ALT_DMALL_BLACK_MEGALO_GROWMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_BLACK_MEGALO_GROWMON_FQNAME_ARR[] = "dmall:Black Megalo Growmon";
    inline static constexpr const char* ALT_DMALL_BLACK_MEGALO_GROWMON_FQNAME = ALT_DMALL_BLACK_MEGALO_GROWMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_BLACK_MEGALO_GROWMON_FQNAME_LEN = sizeof(ALT_DMALL_BLACK_MEGALO_GROWMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_BLACK_RAPIDMON_FQID_ARR[] = "dmall:black_rapidmon";
    inline static constexpr const char* ALT_DMALL_BLACK_RAPIDMON_FQID = ALT_DMALL_BLACK_RAPIDMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_BLACK_RAPIDMON_FQID_LEN = sizeof(ALT_DMALL_BLACK_RAPIDMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_BLACK_RAPIDMON_FQNAME_ARR[] = "dmall:Black Rapidmon";
    inline static constexpr const char* ALT_DMALL_BLACK_RAPIDMON_FQNAME = ALT_DMALL_BLACK_RAPIDMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_BLACK_RAPIDMON_FQNAME_LEN = sizeof(ALT_DMALL_BLACK_RAPIDMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_BLACK_SAINT_GALGOMON_FQID_ARR[] = "dmall:black_saint_galgomon";
    inline static constexpr const char* ALT_DMALL_BLACK_SAINT_GALGOMON_FQID = ALT_DMALL_BLACK_SAINT_GALGOMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_BLACK_SAINT_GALGOMON_FQID_LEN = sizeof(ALT_DMALL_BLACK_SAINT_GALGOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_BLACK_SAINT_GALGOMON_FQNAME_ARR[] = "dmall:Black Saint Galgomon";
    inline static constexpr const char* ALT_DMALL_BLACK_SAINT_GALGOMON_FQNAME = ALT_DMALL_BLACK_SAINT_GALGOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_BLACK_SAINT_GALGOMON_FQNAME_LEN = sizeof(ALT_DMALL_BLACK_SAINT_GALGOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_BLACK_SERAPHIMON_FQID_ARR[] = "dmall:black_seraphimon";
    inline static constexpr const char* ALT_DMALL_BLACK_SERAPHIMON_FQID = ALT_DMALL_BLACK_SERAPHIMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_BLACK_SERAPHIMON_FQID_LEN = sizeof(ALT_DMALL_BLACK_SERAPHIMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_BLACK_SERAPHIMON_FQNAME_ARR[] = "dmall:Black Seraphimon";
    inline static constexpr const char* ALT_DMALL_BLACK_SERAPHIMON_FQNAME = ALT_DMALL_BLACK_SERAPHIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_BLACK_SERAPHIMON_FQNAME_LEN = sizeof(ALT_DMALL_BLACK_SERAPHIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_BLACK_TAILMON_FQID_ARR[] = "dmall:black_tailmon";
    inline static constexpr const char* ALT_DMALL_BLACK_TAILMON_FQID = ALT_DMALL_BLACK_TAILMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_BLACK_TAILMON_FQID_LEN = sizeof(ALT_DMALL_BLACK_TAILMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_BLACK_TAILMON_FQNAME_ARR[] = "dmall:Black Tailmon";
    inline static constexpr const char* ALT_DMALL_BLACK_TAILMON_FQNAME = ALT_DMALL_BLACK_TAILMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_BLACK_TAILMON_FQNAME_LEN = sizeof(ALT_DMALL_BLACK_TAILMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_BLACK_WAR_GREYMON_FQID_ARR[] = "dmall:black_war_greymon";
    inline static constexpr const char* ALT_DMALL_BLACK_WAR_GREYMON_FQID = ALT_DMALL_BLACK_WAR_GREYMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_BLACK_WAR_GREYMON_FQID_LEN = sizeof(ALT_DMALL_BLACK_WAR_GREYMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_BLACK_WAR_GREYMON_FQNAME_ARR[] = "dmall:Black War Greymon";
    inline static constexpr const char* ALT_DMALL_BLACK_WAR_GREYMON_FQNAME = ALT_DMALL_BLACK_WAR_GREYMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_BLACK_WAR_GREYMON_FQNAME_LEN = sizeof(ALT_DMALL_BLACK_WAR_GREYMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_BLACK_WAR_GREYMON_X_FQID_ARR[] = "dmall:black_war_greymon_x";
    inline static constexpr const char* ALT_DMALL_BLACK_WAR_GREYMON_X_FQID = ALT_DMALL_BLACK_WAR_GREYMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_BLACK_WAR_GREYMON_X_FQID_LEN = sizeof(ALT_DMALL_BLACK_WAR_GREYMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_BLACK_WAR_GREYMON_X_FQNAME_ARR[] = "dmall:Black War Greymon X";
    inline static constexpr const char* ALT_DMALL_BLACK_WAR_GREYMON_X_FQNAME = ALT_DMALL_BLACK_WAR_GREYMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_BLACK_WAR_GREYMON_X_FQNAME_LEN = sizeof(ALT_DMALL_BLACK_WAR_GREYMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_BLITZ_GREYMON_FQID_ARR[] = "dmall:blitz_greymon";
    inline static constexpr const char* ALT_DMALL_BLITZ_GREYMON_FQID = ALT_DMALL_BLITZ_GREYMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_BLITZ_GREYMON_FQID_LEN = sizeof(ALT_DMALL_BLITZ_GREYMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_BLITZ_GREYMON_FQNAME_ARR[] = "dmall:Blitz Greymon";
    inline static constexpr const char* ALT_DMALL_BLITZ_GREYMON_FQNAME = ALT_DMALL_BLITZ_GREYMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_BLITZ_GREYMON_FQNAME_LEN = sizeof(ALT_DMALL_BLITZ_GREYMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_BLOOM_LORDMON_FQID_ARR[] = "dmall:bloom_lordmon";
    inline static constexpr const char* ALT_DMALL_BLOOM_LORDMON_FQID = ALT_DMALL_BLOOM_LORDMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_BLOOM_LORDMON_FQID_LEN = sizeof(ALT_DMALL_BLOOM_LORDMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_BLOOM_LORDMON_FQNAME_ARR[] = "dmall:Bloom Lordmon";
    inline static constexpr const char* ALT_DMALL_BLOOM_LORDMON_FQNAME = ALT_DMALL_BLOOM_LORDMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_BLOOM_LORDMON_FQNAME_LEN = sizeof(ALT_DMALL_BLOOM_LORDMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_BLOSSOMON_FQID_ARR[] = "dmall:blossomon";
    inline static constexpr const char* ALT_DMALL_BLOSSOMON_FQID = ALT_DMALL_BLOSSOMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_BLOSSOMON_FQID_LEN = sizeof(ALT_DMALL_BLOSSOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_BLOSSOMON_FQNAME_ARR[] = "dmall:Blossomon";
    inline static constexpr const char* ALT_DMALL_BLOSSOMON_FQNAME = ALT_DMALL_BLOSSOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_BLOSSOMON_FQNAME_LEN = sizeof(ALT_DMALL_BLOSSOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_BLUCOMON_FQID_ARR[] = "dmall:blucomon";
    inline static constexpr const char* ALT_DMALL_BLUCOMON_FQID = ALT_DMALL_BLUCOMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_BLUCOMON_FQID_LEN = sizeof(ALT_DMALL_BLUCOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_BLUCOMON_FQNAME_ARR[] = "dmall:Blucomon";
    inline static constexpr const char* ALT_DMALL_BLUCOMON_FQNAME = ALT_DMALL_BLUCOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_BLUCOMON_FQNAME_LEN = sizeof(ALT_DMALL_BLUCOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_BLUE_MERAMON_FQID_ARR[] = "dmall:blue_meramon";
    inline static constexpr const char* ALT_DMALL_BLUE_MERAMON_FQID = ALT_DMALL_BLUE_MERAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_BLUE_MERAMON_FQID_LEN = sizeof(ALT_DMALL_BLUE_MERAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_BLUE_MERAMON_FQNAME_ARR[] = "dmall:Blue Meramon";
    inline static constexpr const char* ALT_DMALL_BLUE_MERAMON_FQNAME = ALT_DMALL_BLUE_MERAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_BLUE_MERAMON_FQNAME_LEN = sizeof(ALT_DMALL_BLUE_MERAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_BOLTMON_FQID_ARR[] = "dmall:boltmon";
    inline static constexpr const char* ALT_DMALL_BOLTMON_FQID = ALT_DMALL_BOLTMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_BOLTMON_FQID_LEN = sizeof(ALT_DMALL_BOLTMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_BOLTMON_FQNAME_ARR[] = "dmall:Boltmon";
    inline static constexpr const char* ALT_DMALL_BOLTMON_FQNAME = ALT_DMALL_BOLTMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_BOLTMON_FQNAME_LEN = sizeof(ALT_DMALL_BOLTMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_BOMBMON_FQID_ARR[] = "dmall:bombmon";
    inline static constexpr const char* ALT_DMALL_BOMBMON_FQID = ALT_DMALL_BOMBMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_BOMBMON_FQID_LEN = sizeof(ALT_DMALL_BOMBMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_BOMBMON_FQNAME_ARR[] = "dmall:Bombmon";
    inline static constexpr const char* ALT_DMALL_BOMBMON_FQNAME = ALT_DMALL_BOMBMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_BOMBMON_FQNAME_LEN = sizeof(ALT_DMALL_BOMBMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_BOMMON_FQID_ARR[] = "dmall:bommon";
    inline static constexpr const char* ALT_DMALL_BOMMON_FQID = ALT_DMALL_BOMMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_BOMMON_FQID_LEN = sizeof(ALT_DMALL_BOMMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_BOMMON_FQNAME_ARR[] = "dmall:Bommon";
    inline static constexpr const char* ALT_DMALL_BOMMON_FQNAME = ALT_DMALL_BOMMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_BOMMON_FQNAME_LEN = sizeof(ALT_DMALL_BOMMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_BOUTMON_FQID_ARR[] = "dmall:boutmon";
    inline static constexpr const char* ALT_DMALL_BOUTMON_FQID = ALT_DMALL_BOUTMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_BOUTMON_FQID_LEN = sizeof(ALT_DMALL_BOUTMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_BOUTMON_FQNAME_ARR[] = "dmall:Boutmon";
    inline static constexpr const char* ALT_DMALL_BOUTMON_FQNAME = ALT_DMALL_BOUTMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_BOUTMON_FQNAME_LEN = sizeof(ALT_DMALL_BOUTMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_BRYWELUDRAMON_FQID_ARR[] = "dmall:bryweludramon";
    inline static constexpr const char* ALT_DMALL_BRYWELUDRAMON_FQID = ALT_DMALL_BRYWELUDRAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_BRYWELUDRAMON_FQID_LEN = sizeof(ALT_DMALL_BRYWELUDRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_BRYWELUDRAMON_FQNAME_ARR[] = "dmall:Bryweludramon";
    inline static constexpr const char* ALT_DMALL_BRYWELUDRAMON_FQNAME = ALT_DMALL_BRYWELUDRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_BRYWELUDRAMON_FQNAME_LEN = sizeof(ALT_DMALL_BRYWELUDRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_BUBBMON_FQID_ARR[] = "dmall:bubbmon";
    inline static constexpr const char* ALT_DMALL_BUBBMON_FQID = ALT_DMALL_BUBBMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_BUBBMON_FQID_LEN = sizeof(ALT_DMALL_BUBBMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_BUBBMON_FQNAME_ARR[] = "dmall:Bubbmon";
    inline static constexpr const char* ALT_DMALL_BUBBMON_FQNAME = ALT_DMALL_BUBBMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_BUBBMON_FQNAME_LEN = sizeof(ALT_DMALL_BUBBMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_BUDMON_FQID_ARR[] = "dmall:budmon";
    inline static constexpr const char* ALT_DMALL_BUDMON_FQID = ALT_DMALL_BUDMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_BUDMON_FQID_LEN = sizeof(ALT_DMALL_BUDMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_BUDMON_FQNAME_ARR[] = "dmall:Budmon";
    inline static constexpr const char* ALT_DMALL_BUDMON_FQNAME = ALT_DMALL_BUDMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_BUDMON_FQNAME_LEN = sizeof(ALT_DMALL_BUDMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_BURGERMON_MAMA_FQID_ARR[] = "dmall:burgermon_mama";
    inline static constexpr const char* ALT_DMALL_BURGERMON_MAMA_FQID = ALT_DMALL_BURGERMON_MAMA_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_BURGERMON_MAMA_FQID_LEN = sizeof(ALT_DMALL_BURGERMON_MAMA_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_BURGERMON_MAMA_FQNAME_ARR[] = "dmall:Burgermon (Mama)";
    inline static constexpr const char* ALT_DMALL_BURGERMON_MAMA_FQNAME = ALT_DMALL_BURGERMON_MAMA_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_BURGERMON_MAMA_FQNAME_LEN = sizeof(ALT_DMALL_BURGERMON_MAMA_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_BURGERMON_PAPA_FQID_ARR[] = "dmall:burgermon_papa";
    inline static constexpr const char* ALT_DMALL_BURGERMON_PAPA_FQID = ALT_DMALL_BURGERMON_PAPA_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_BURGERMON_PAPA_FQID_LEN = sizeof(ALT_DMALL_BURGERMON_PAPA_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_BURGERMON_PAPA_FQNAME_ARR[] = "dmall:Burgermon (Papa)";
    inline static constexpr const char* ALT_DMALL_BURGERMON_PAPA_FQNAME = ALT_DMALL_BURGERMON_PAPA_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_BURGERMON_PAPA_FQNAME_LEN = sizeof(ALT_DMALL_BURGERMON_PAPA_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_CANDMON_FQID_ARR[] = "dmall:candmon";
    inline static constexpr const char* ALT_DMALL_CANDMON_FQID = ALT_DMALL_CANDMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_CANDMON_FQID_LEN = sizeof(ALT_DMALL_CANDMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_CANDMON_FQNAME_ARR[] = "dmall:Candmon";
    inline static constexpr const char* ALT_DMALL_CANDMON_FQNAME = ALT_DMALL_CANDMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_CANDMON_FQNAME_LEN = sizeof(ALT_DMALL_CANDMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_CANNONBEEMON_FQID_ARR[] = "dmall:cannonbeemon";
    inline static constexpr const char* ALT_DMALL_CANNONBEEMON_FQID = ALT_DMALL_CANNONBEEMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_CANNONBEEMON_FQID_LEN = sizeof(ALT_DMALL_CANNONBEEMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_CANNONBEEMON_FQNAME_ARR[] = "dmall:Cannonbeemon";
    inline static constexpr const char* ALT_DMALL_CANNONBEEMON_FQNAME = ALT_DMALL_CANNONBEEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_CANNONBEEMON_FQNAME_LEN = sizeof(ALT_DMALL_CANNONBEEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_CAPRIMON_FQID_ARR[] = "dmall:caprimon";
    inline static constexpr const char* ALT_DMALL_CAPRIMON_FQID = ALT_DMALL_CAPRIMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_CAPRIMON_FQID_LEN = sizeof(ALT_DMALL_CAPRIMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_CAPRIMON_FQNAME_ARR[] = "dmall:Caprimon";
    inline static constexpr const char* ALT_DMALL_CAPRIMON_FQNAME = ALT_DMALL_CAPRIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_CAPRIMON_FQNAME_LEN = sizeof(ALT_DMALL_CAPRIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_CATCHMAMEMON_FQID_ARR[] = "dmall:catchmamemon";
    inline static constexpr const char* ALT_DMALL_CATCHMAMEMON_FQID = ALT_DMALL_CATCHMAMEMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_CATCHMAMEMON_FQID_LEN = sizeof(ALT_DMALL_CATCHMAMEMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_CATCHMAMEMON_FQNAME_ARR[] = "dmall:CatchMamemon";
    inline static constexpr const char* ALT_DMALL_CATCHMAMEMON_FQNAME = ALT_DMALL_CATCHMAMEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_CATCHMAMEMON_FQNAME_LEN = sizeof(ALT_DMALL_CATCHMAMEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_CATURAMON_FQID_ARR[] = "dmall:caturamon";
    inline static constexpr const char* ALT_DMALL_CATURAMON_FQID = ALT_DMALL_CATURAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_CATURAMON_FQID_LEN = sizeof(ALT_DMALL_CATURAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_CATURAMON_FQNAME_ARR[] = "dmall:Caturamon";
    inline static constexpr const char* ALT_DMALL_CATURAMON_FQNAME = ALT_DMALL_CATURAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_CATURAMON_FQNAME_LEN = sizeof(ALT_DMALL_CATURAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_CENTALMON_FQID_ARR[] = "dmall:centalmon";
    inline static constexpr const char* ALT_DMALL_CENTALMON_FQID = ALT_DMALL_CENTALMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_CENTALMON_FQID_LEN = sizeof(ALT_DMALL_CENTALMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_CENTALMON_FQNAME_ARR[] = "dmall:Centalmon";
    inline static constexpr const char* ALT_DMALL_CENTALMON_FQNAME = ALT_DMALL_CENTALMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_CENTALMON_FQNAME_LEN = sizeof(ALT_DMALL_CENTALMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_CERBERUMON_X_FQID_ARR[] = "dmall:cerberumon_x";
    inline static constexpr const char* ALT_DMALL_CERBERUMON_X_FQID = ALT_DMALL_CERBERUMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_CERBERUMON_X_FQID_LEN = sizeof(ALT_DMALL_CERBERUMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_CERBERUMON_X_FQNAME_ARR[] = "dmall:Cerberumon X";
    inline static constexpr const char* ALT_DMALL_CERBERUMON_X_FQNAME = ALT_DMALL_CERBERUMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_CERBERUMON_X_FQNAME_LEN = sizeof(ALT_DMALL_CERBERUMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_CHAMBLEMON_FQID_ARR[] = "dmall:chamblemon";
    inline static constexpr const char* ALT_DMALL_CHAMBLEMON_FQID = ALT_DMALL_CHAMBLEMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_CHAMBLEMON_FQID_LEN = sizeof(ALT_DMALL_CHAMBLEMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_CHAMBLEMON_FQNAME_ARR[] = "dmall:Chamblemon";
    inline static constexpr const char* ALT_DMALL_CHAMBLEMON_FQNAME = ALT_DMALL_CHAMBLEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_CHAMBLEMON_FQNAME_LEN = sizeof(ALT_DMALL_CHAMBLEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_CHAOSDRAMON_FQID_ARR[] = "dmall:chaosdramon";
    inline static constexpr const char* ALT_DMALL_CHAOSDRAMON_FQID = ALT_DMALL_CHAOSDRAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_CHAOSDRAMON_FQID_LEN = sizeof(ALT_DMALL_CHAOSDRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_CHAOSDRAMON_FQNAME_ARR[] = "dmall:Chaosdramon";
    inline static constexpr const char* ALT_DMALL_CHAOSDRAMON_FQNAME = ALT_DMALL_CHAOSDRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_CHAOSDRAMON_FQNAME_LEN = sizeof(ALT_DMALL_CHAOSDRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_CHAOSDRAMON_X_FQID_ARR[] = "dmall:chaosdramon_x";
    inline static constexpr const char* ALT_DMALL_CHAOSDRAMON_X_FQID = ALT_DMALL_CHAOSDRAMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_CHAOSDRAMON_X_FQID_LEN = sizeof(ALT_DMALL_CHAOSDRAMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_CHAOSDRAMON_X_FQNAME_ARR[] = "dmall:Chaosdramon X";
    inline static constexpr const char* ALT_DMALL_CHAOSDRAMON_X_FQNAME = ALT_DMALL_CHAOSDRAMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_CHAOSDRAMON_X_FQNAME_LEN = sizeof(ALT_DMALL_CHAOSDRAMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_CHAOS_DUKEMON_CORE_FQID_ARR[] = "dmall:chaos_dukemon_core";
    inline static constexpr const char* ALT_DMALL_CHAOS_DUKEMON_CORE_FQID = ALT_DMALL_CHAOS_DUKEMON_CORE_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_CHAOS_DUKEMON_CORE_FQID_LEN = sizeof(ALT_DMALL_CHAOS_DUKEMON_CORE_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_CHAOS_DUKEMON_CORE_FQNAME_ARR[] = "dmall:Chaos Dukemon Core";
    inline static constexpr const char* ALT_DMALL_CHAOS_DUKEMON_CORE_FQNAME = ALT_DMALL_CHAOS_DUKEMON_CORE_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_CHAOS_DUKEMON_CORE_FQNAME_LEN = sizeof(ALT_DMALL_CHAOS_DUKEMON_CORE_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_CHAOS_DUKEMON_FQID_ARR[] = "dmall:chaos_dukemon";
    inline static constexpr const char* ALT_DMALL_CHAOS_DUKEMON_FQID = ALT_DMALL_CHAOS_DUKEMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_CHAOS_DUKEMON_FQID_LEN = sizeof(ALT_DMALL_CHAOS_DUKEMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_CHAOS_DUKEMON_FQNAME_ARR[] = "dmall:Chaos Dukemon";
    inline static constexpr const char* ALT_DMALL_CHAOS_DUKEMON_FQNAME = ALT_DMALL_CHAOS_DUKEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_CHAOS_DUKEMON_FQNAME_LEN = sizeof(ALT_DMALL_CHAOS_DUKEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_CHAOSMON_FQID_ARR[] = "dmall:chaosmon";
    inline static constexpr const char* ALT_DMALL_CHAOSMON_FQID = ALT_DMALL_CHAOSMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_CHAOSMON_FQID_LEN = sizeof(ALT_DMALL_CHAOSMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_CHAOSMON_FQNAME_ARR[] = "dmall:Chaosmon";
    inline static constexpr const char* ALT_DMALL_CHAOSMON_FQNAME = ALT_DMALL_CHAOSMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_CHAOSMON_FQNAME_LEN = sizeof(ALT_DMALL_CHAOSMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_CHERUBIMON_VICE_FQID_ARR[] = "dmall:cherubimon_vice";
    inline static constexpr const char* ALT_DMALL_CHERUBIMON_VICE_FQID = ALT_DMALL_CHERUBIMON_VICE_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_CHERUBIMON_VICE_FQID_LEN = sizeof(ALT_DMALL_CHERUBIMON_VICE_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_CHERUBIMON_VICE_FQNAME_ARR[] = "dmall:Cherubimon (Vice)";
    inline static constexpr const char* ALT_DMALL_CHERUBIMON_VICE_FQNAME = ALT_DMALL_CHERUBIMON_VICE_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_CHERUBIMON_VICE_FQNAME_LEN = sizeof(ALT_DMALL_CHERUBIMON_VICE_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_CHERUBIMON_VICE_X_FQID_ARR[] = "dmall:cherubimon_vice_x";
    inline static constexpr const char* ALT_DMALL_CHERUBIMON_VICE_X_FQID = ALT_DMALL_CHERUBIMON_VICE_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_CHERUBIMON_VICE_X_FQID_LEN = sizeof(ALT_DMALL_CHERUBIMON_VICE_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_CHERUBIMON_VICE_X_FQNAME_ARR[] = "dmall:Cherubimon (Vice) X";
    inline static constexpr const char* ALT_DMALL_CHERUBIMON_VICE_X_FQNAME = ALT_DMALL_CHERUBIMON_VICE_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_CHERUBIMON_VICE_X_FQNAME_LEN = sizeof(ALT_DMALL_CHERUBIMON_VICE_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_CHERUBIMON_VIRTUE_FQID_ARR[] = "dmall:cherubimon_virtue";
    inline static constexpr const char* ALT_DMALL_CHERUBIMON_VIRTUE_FQID = ALT_DMALL_CHERUBIMON_VIRTUE_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_CHERUBIMON_VIRTUE_FQID_LEN = sizeof(ALT_DMALL_CHERUBIMON_VIRTUE_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_CHERUBIMON_VIRTUE_FQNAME_ARR[] = "dmall:Cherubimon (Virtue)";
    inline static constexpr const char* ALT_DMALL_CHERUBIMON_VIRTUE_FQNAME = ALT_DMALL_CHERUBIMON_VIRTUE_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_CHERUBIMON_VIRTUE_FQNAME_LEN = sizeof(ALT_DMALL_CHERUBIMON_VIRTUE_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_CHERUBIMON_VIRTUE_X_FQID_ARR[] = "dmall:cherubimon_virtue_x";
    inline static constexpr const char* ALT_DMALL_CHERUBIMON_VIRTUE_X_FQID = ALT_DMALL_CHERUBIMON_VIRTUE_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_CHERUBIMON_VIRTUE_X_FQID_LEN = sizeof(ALT_DMALL_CHERUBIMON_VIRTUE_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_CHERUBIMON_VIRTUE_X_FQNAME_ARR[] = "dmall:Cherubimon (Virtue) X";
    inline static constexpr const char* ALT_DMALL_CHERUBIMON_VIRTUE_X_FQNAME = ALT_DMALL_CHERUBIMON_VIRTUE_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_CHERUBIMON_VIRTUE_X_FQNAME_LEN = sizeof(ALT_DMALL_CHERUBIMON_VIRTUE_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_CHIBICKMON_FQID_ARR[] = "dmall:chibickmon";
    inline static constexpr const char* ALT_DMALL_CHIBICKMON_FQID = ALT_DMALL_CHIBICKMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_CHIBICKMON_FQID_LEN = sizeof(ALT_DMALL_CHIBICKMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_CHIBICKMON_FQNAME_ARR[] = "dmall:Chibickmon";
    inline static constexpr const char* ALT_DMALL_CHIBICKMON_FQNAME = ALT_DMALL_CHIBICKMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_CHIBICKMON_FQNAME_LEN = sizeof(ALT_DMALL_CHIBICKMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_CHIBIMON_FQID_ARR[] = "dmall:chibimon";
    inline static constexpr const char* ALT_DMALL_CHIBIMON_FQID = ALT_DMALL_CHIBIMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_CHIBIMON_FQID_LEN = sizeof(ALT_DMALL_CHIBIMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_CHIBIMON_FQNAME_ARR[] = "dmall:Chibimon";
    inline static constexpr const char* ALT_DMALL_CHIBIMON_FQNAME = ALT_DMALL_CHIBIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_CHIBIMON_FQNAME_LEN = sizeof(ALT_DMALL_CHIBIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_CHICCHIMON_FQID_ARR[] = "dmall:chicchimon";
    inline static constexpr const char* ALT_DMALL_CHICCHIMON_FQID = ALT_DMALL_CHICCHIMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_CHICCHIMON_FQID_LEN = sizeof(ALT_DMALL_CHICCHIMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_CHICCHIMON_FQNAME_ARR[] = "dmall:Chicchimon";
    inline static constexpr const char* ALT_DMALL_CHICCHIMON_FQNAME = ALT_DMALL_CHICCHIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_CHICCHIMON_FQNAME_LEN = sizeof(ALT_DMALL_CHICCHIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_CHICOMON_FQID_ARR[] = "dmall:chicomon";
    inline static constexpr const char* ALT_DMALL_CHICOMON_FQID = ALT_DMALL_CHICOMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_CHICOMON_FQID_LEN = sizeof(ALT_DMALL_CHICOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_CHICOMON_FQNAME_ARR[] = "dmall:Chicomon";
    inline static constexpr const char* ALT_DMALL_CHICOMON_FQNAME = ALT_DMALL_CHICOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_CHICOMON_FQNAME_LEN = sizeof(ALT_DMALL_CHICOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_CHIMAIRAMON_FQID_ARR[] = "dmall:chimairamon";
    inline static constexpr const char* ALT_DMALL_CHIMAIRAMON_FQID = ALT_DMALL_CHIMAIRAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_CHIMAIRAMON_FQID_LEN = sizeof(ALT_DMALL_CHIMAIRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_CHIMAIRAMON_FQNAME_ARR[] = "dmall:Chimairamon";
    inline static constexpr const char* ALT_DMALL_CHIMAIRAMON_FQNAME = ALT_DMALL_CHIMAIRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_CHIMAIRAMON_FQNAME_LEN = sizeof(ALT_DMALL_CHIMAIRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_CHOCOMON_FQID_ARR[] = "dmall:chocomon";
    inline static constexpr const char* ALT_DMALL_CHOCOMON_FQID = ALT_DMALL_CHOCOMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_CHOCOMON_FQID_LEN = sizeof(ALT_DMALL_CHOCOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_CHOCOMON_FQNAME_ARR[] = "dmall:Chocomon";
    inline static constexpr const char* ALT_DMALL_CHOCOMON_FQNAME = ALT_DMALL_CHOCOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_CHOCOMON_FQNAME_LEN = sizeof(ALT_DMALL_CHOCOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_CHO_HAKKAIMON_FQID_ARR[] = "dmall:cho_hakkaimon";
    inline static constexpr const char* ALT_DMALL_CHO_HAKKAIMON_FQID = ALT_DMALL_CHO_HAKKAIMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_CHO_HAKKAIMON_FQID_LEN = sizeof(ALT_DMALL_CHO_HAKKAIMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_CHO_HAKKAIMON_FQNAME_ARR[] = "dmall:Cho Hakkaimon";
    inline static constexpr const char* ALT_DMALL_CHO_HAKKAIMON_FQNAME = ALT_DMALL_CHO_HAKKAIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_CHO_HAKKAIMON_FQNAME_LEN = sizeof(ALT_DMALL_CHO_HAKKAIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_CHOROMON_FQID_ARR[] = "dmall:choromon";
    inline static constexpr const char* ALT_DMALL_CHOROMON_FQID = ALT_DMALL_CHOROMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_CHOROMON_FQID_LEN = sizeof(ALT_DMALL_CHOROMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_CHOROMON_FQNAME_ARR[] = "dmall:Choromon";
    inline static constexpr const char* ALT_DMALL_CHOROMON_FQNAME = ALT_DMALL_CHOROMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_CHOROMON_FQNAME_LEN = sizeof(ALT_DMALL_CHOROMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_CLEAR_AGUMON_FQID_ARR[] = "dmall:clear_agumon";
    inline static constexpr const char* ALT_DMALL_CLEAR_AGUMON_FQID = ALT_DMALL_CLEAR_AGUMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_CLEAR_AGUMON_FQID_LEN = sizeof(ALT_DMALL_CLEAR_AGUMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_CLEAR_AGUMON_FQNAME_ARR[] = "dmall:Clear Agumon";
    inline static constexpr const char* ALT_DMALL_CLEAR_AGUMON_FQNAME = ALT_DMALL_CLEAR_AGUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_CLEAR_AGUMON_FQNAME_LEN = sizeof(ALT_DMALL_CLEAR_AGUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_CLOCKMON_FQID_ARR[] = "dmall:clockmon";
    inline static constexpr const char* ALT_DMALL_CLOCKMON_FQID = ALT_DMALL_CLOCKMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_CLOCKMON_FQID_LEN = sizeof(ALT_DMALL_CLOCKMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_CLOCKMON_FQNAME_ARR[] = "dmall:Clockmon";
    inline static constexpr const char* ALT_DMALL_CLOCKMON_FQNAME = ALT_DMALL_CLOCKMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_CLOCKMON_FQNAME_LEN = sizeof(ALT_DMALL_CLOCKMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_COCOMON_FQID_ARR[] = "dmall:cocomon";
    inline static constexpr const char* ALT_DMALL_COCOMON_FQID = ALT_DMALL_COCOMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_COCOMON_FQID_LEN = sizeof(ALT_DMALL_COCOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_COCOMON_FQNAME_ARR[] = "dmall:Cocomon";
    inline static constexpr const char* ALT_DMALL_COCOMON_FQNAME = ALT_DMALL_COCOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_COCOMON_FQNAME_LEN = sizeof(ALT_DMALL_COCOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_COELAMON_FQID_ARR[] = "dmall:coelamon";
    inline static constexpr const char* ALT_DMALL_COELAMON_FQID = ALT_DMALL_COELAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_COELAMON_FQID_LEN = sizeof(ALT_DMALL_COELAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_COELAMON_FQNAME_ARR[] = "dmall:Coelamon";
    inline static constexpr const char* ALT_DMALL_COELAMON_FQNAME = ALT_DMALL_COELAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_COELAMON_FQNAME_LEN = sizeof(ALT_DMALL_COELAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_COMMANDRAMON_FQID_ARR[] = "dmall:commandramon";
    inline static constexpr const char* ALT_DMALL_COMMANDRAMON_FQID = ALT_DMALL_COMMANDRAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_COMMANDRAMON_FQID_LEN = sizeof(ALT_DMALL_COMMANDRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_COMMANDRAMON_FQNAME_ARR[] = "dmall:Commandramon";
    inline static constexpr const char* ALT_DMALL_COMMANDRAMON_FQNAME = ALT_DMALL_COMMANDRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_COMMANDRAMON_FQNAME_LEN = sizeof(ALT_DMALL_COMMANDRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_CORONAMON_FQID_ARR[] = "dmall:coronamon";
    inline static constexpr const char* ALT_DMALL_CORONAMON_FQID = ALT_DMALL_CORONAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_CORONAMON_FQID_LEN = sizeof(ALT_DMALL_CORONAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_CORONAMON_FQNAME_ARR[] = "dmall:Coronamon";
    inline static constexpr const char* ALT_DMALL_CORONAMON_FQNAME = ALT_DMALL_CORONAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_CORONAMON_FQNAME_LEN = sizeof(ALT_DMALL_CORONAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_COTSUCOMON_FQID_ARR[] = "dmall:cotsucomon";
    inline static constexpr const char* ALT_DMALL_COTSUCOMON_FQID = ALT_DMALL_COTSUCOMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_COTSUCOMON_FQID_LEN = sizeof(ALT_DMALL_COTSUCOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_COTSUCOMON_FQNAME_ARR[] = "dmall:Cotsucomon";
    inline static constexpr const char* ALT_DMALL_COTSUCOMON_FQNAME = ALT_DMALL_COTSUCOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_COTSUCOMON_FQNAME_LEN = sizeof(ALT_DMALL_COTSUCOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_CRANIUMMON_FQID_ARR[] = "dmall:craniummon";
    inline static constexpr const char* ALT_DMALL_CRANIUMMON_FQID = ALT_DMALL_CRANIUMMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_CRANIUMMON_FQID_LEN = sizeof(ALT_DMALL_CRANIUMMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_CRANIUMMON_FQNAME_ARR[] = "dmall:Craniummon";
    inline static constexpr const char* ALT_DMALL_CRANIUMMON_FQNAME = ALT_DMALL_CRANIUMMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_CRANIUMMON_FQNAME_LEN = sizeof(ALT_DMALL_CRANIUMMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_CRANIUMMON_X_FQID_ARR[] = "dmall:craniummon_x";
    inline static constexpr const char* ALT_DMALL_CRANIUMMON_X_FQID = ALT_DMALL_CRANIUMMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_CRANIUMMON_X_FQID_LEN = sizeof(ALT_DMALL_CRANIUMMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_CRANIUMMON_X_FQNAME_ARR[] = "dmall:Craniummon X";
    inline static constexpr const char* ALT_DMALL_CRANIUMMON_X_FQNAME = ALT_DMALL_CRANIUMMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_CRANIUMMON_X_FQNAME_LEN = sizeof(ALT_DMALL_CRANIUMMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_CRESCEMON_FQID_ARR[] = "dmall:crescemon";
    inline static constexpr const char* ALT_DMALL_CRESCEMON_FQID = ALT_DMALL_CRESCEMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_CRESCEMON_FQID_LEN = sizeof(ALT_DMALL_CRESCEMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_CRESCEMON_FQNAME_ARR[] = "dmall:Crescemon";
    inline static constexpr const char* ALT_DMALL_CRESCEMON_FQNAME = ALT_DMALL_CRESCEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_CRESCEMON_FQNAME_LEN = sizeof(ALT_DMALL_CRESCEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_CRES_GARURUMON_FQID_ARR[] = "dmall:cres_garurumon";
    inline static constexpr const char* ALT_DMALL_CRES_GARURUMON_FQID = ALT_DMALL_CRES_GARURUMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_CRES_GARURUMON_FQID_LEN = sizeof(ALT_DMALL_CRES_GARURUMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_CRES_GARURUMON_FQNAME_ARR[] = "dmall:Cres Garurumon";
    inline static constexpr const char* ALT_DMALL_CRES_GARURUMON_FQNAME = ALT_DMALL_CRES_GARURUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_CRES_GARURUMON_FQNAME_LEN = sizeof(ALT_DMALL_CRES_GARURUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_CRYS_PALEDRAMON_FQID_ARR[] = "dmall:crys_paledramon";
    inline static constexpr const char* ALT_DMALL_CRYS_PALEDRAMON_FQID = ALT_DMALL_CRYS_PALEDRAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_CRYS_PALEDRAMON_FQID_LEN = sizeof(ALT_DMALL_CRYS_PALEDRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_CRYS_PALEDRAMON_FQNAME_ARR[] = "dmall:Crys Paledramon";
    inline static constexpr const char* ALT_DMALL_CRYS_PALEDRAMON_FQNAME = ALT_DMALL_CRYS_PALEDRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_CRYS_PALEDRAMON_FQNAME_LEN = sizeof(ALT_DMALL_CRYS_PALEDRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_CTHYLLAMON_FQID_ARR[] = "dmall:cthyllamon";
    inline static constexpr const char* ALT_DMALL_CTHYLLAMON_FQID = ALT_DMALL_CTHYLLAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_CTHYLLAMON_FQID_LEN = sizeof(ALT_DMALL_CTHYLLAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_CTHYLLAMON_FQNAME_ARR[] = "dmall:Cthyllamon";
    inline static constexpr const char* ALT_DMALL_CTHYLLAMON_FQNAME = ALT_DMALL_CTHYLLAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_CTHYLLAMON_FQNAME_LEN = sizeof(ALT_DMALL_CTHYLLAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_CUPIMON_FQID_ARR[] = "dmall:cupimon";
    inline static constexpr const char* ALT_DMALL_CUPIMON_FQID = ALT_DMALL_CUPIMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_CUPIMON_FQID_LEN = sizeof(ALT_DMALL_CUPIMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_CUPIMON_FQNAME_ARR[] = "dmall:Cupimon";
    inline static constexpr const char* ALT_DMALL_CUPIMON_FQNAME = ALT_DMALL_CUPIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_CUPIMON_FQNAME_LEN = sizeof(ALT_DMALL_CUPIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_CURIMON_FQID_ARR[] = "dmall:curimon";
    inline static constexpr const char* ALT_DMALL_CURIMON_FQID = ALT_DMALL_CURIMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_CURIMON_FQID_LEN = sizeof(ALT_DMALL_CURIMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_CURIMON_FQNAME_ARR[] = "dmall:Curimon";
    inline static constexpr const char* ALT_DMALL_CURIMON_FQNAME = ALT_DMALL_CURIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_CURIMON_FQNAME_LEN = sizeof(ALT_DMALL_CURIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_CYBERDRAMON_FQID_ARR[] = "dmall:cyberdramon";
    inline static constexpr const char* ALT_DMALL_CYBERDRAMON_FQID = ALT_DMALL_CYBERDRAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_CYBERDRAMON_FQID_LEN = sizeof(ALT_DMALL_CYBERDRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_CYBERDRAMON_FQNAME_ARR[] = "dmall:Cyberdramon";
    inline static constexpr const char* ALT_DMALL_CYBERDRAMON_FQNAME = ALT_DMALL_CYBERDRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_CYBERDRAMON_FQNAME_LEN = sizeof(ALT_DMALL_CYBERDRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_CYBERDRAMON_X_FQID_ARR[] = "dmall:cyberdramon_x";
    inline static constexpr const char* ALT_DMALL_CYBERDRAMON_X_FQID = ALT_DMALL_CYBERDRAMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_CYBERDRAMON_X_FQID_LEN = sizeof(ALT_DMALL_CYBERDRAMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_CYBERDRAMON_X_FQNAME_ARR[] = "dmall:Cyberdramon X";
    inline static constexpr const char* ALT_DMALL_CYBERDRAMON_X_FQNAME = ALT_DMALL_CYBERDRAMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_CYBERDRAMON_X_FQNAME_LEN = sizeof(ALT_DMALL_CYBERDRAMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_CYCLOMON_FQID_ARR[] = "dmall:cyclomon";
    inline static constexpr const char* ALT_DMALL_CYCLOMON_FQID = ALT_DMALL_CYCLOMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_CYCLOMON_FQID_LEN = sizeof(ALT_DMALL_CYCLOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_CYCLOMON_FQNAME_ARR[] = "dmall:Cyclomon";
    inline static constexpr const char* ALT_DMALL_CYCLOMON_FQNAME = ALT_DMALL_CYCLOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_CYCLOMON_FQNAME_LEN = sizeof(ALT_DMALL_CYCLOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_DAGOMON_FQID_ARR[] = "dmall:dagomon";
    inline static constexpr const char* ALT_DMALL_DAGOMON_FQID = ALT_DMALL_DAGOMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_DAGOMON_FQID_LEN = sizeof(ALT_DMALL_DAGOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_DAGOMON_FQNAME_ARR[] = "dmall:Dagomon";
    inline static constexpr const char* ALT_DMALL_DAGOMON_FQNAME = ALT_DMALL_DAGOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_DAGOMON_FQNAME_LEN = sizeof(ALT_DMALL_DAGOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_DAMEMON_FQID_ARR[] = "dmall:damemon";
    inline static constexpr const char* ALT_DMALL_DAMEMON_FQID = ALT_DMALL_DAMEMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_DAMEMON_FQID_LEN = sizeof(ALT_DMALL_DAMEMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_DAMEMON_FQNAME_ARR[] = "dmall:Damemon";
    inline static constexpr const char* ALT_DMALL_DAMEMON_FQNAME = ALT_DMALL_DAMEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_DAMEMON_FQNAME_LEN = sizeof(ALT_DMALL_DAMEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_DARKDRAMON_FQID_ARR[] = "dmall:darkdramon";
    inline static constexpr const char* ALT_DMALL_DARKDRAMON_FQID = ALT_DMALL_DARKDRAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_DARKDRAMON_FQID_LEN = sizeof(ALT_DMALL_DARKDRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_DARKDRAMON_FQNAME_ARR[] = "dmall:Darkdramon";
    inline static constexpr const char* ALT_DMALL_DARKDRAMON_FQNAME = ALT_DMALL_DARKDRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_DARKDRAMON_FQNAME_LEN = sizeof(ALT_DMALL_DARKDRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_DARK_KNIGHTMON_FQID_ARR[] = "dmall:dark_knightmon";
    inline static constexpr const char* ALT_DMALL_DARK_KNIGHTMON_FQID = ALT_DMALL_DARK_KNIGHTMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_DARK_KNIGHTMON_FQID_LEN = sizeof(ALT_DMALL_DARK_KNIGHTMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_DARK_KNIGHTMON_FQNAME_ARR[] = "dmall:Dark Knightmon";
    inline static constexpr const char* ALT_DMALL_DARK_KNIGHTMON_FQNAME = ALT_DMALL_DARK_KNIGHTMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_DARK_KNIGHTMON_FQNAME_LEN = sizeof(ALT_DMALL_DARK_KNIGHTMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_DARKNESS_BAGRAMON_FQID_ARR[] = "dmall:darkness_bagramon";
    inline static constexpr const char* ALT_DMALL_DARKNESS_BAGRAMON_FQID = ALT_DMALL_DARKNESS_BAGRAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_DARKNESS_BAGRAMON_FQID_LEN = sizeof(ALT_DMALL_DARKNESS_BAGRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_DARKNESS_BAGRAMON_FQNAME_ARR[] = "dmall:Darkness Bagramon";
    inline static constexpr const char* ALT_DMALL_DARKNESS_BAGRAMON_FQNAME = ALT_DMALL_DARKNESS_BAGRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_DARKNESS_BAGRAMON_FQNAME_LEN = sizeof(ALT_DMALL_DARKNESS_BAGRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_DARK_SUPERSTARMON_FQID_ARR[] = "dmall:dark_superstarmon";
    inline static constexpr const char* ALT_DMALL_DARK_SUPERSTARMON_FQID = ALT_DMALL_DARK_SUPERSTARMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_DARK_SUPERSTARMON_FQID_LEN = sizeof(ALT_DMALL_DARK_SUPERSTARMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_DARK_SUPERSTARMON_FQNAME_ARR[] = "dmall:Dark Superstarmon";
    inline static constexpr const char* ALT_DMALL_DARK_SUPERSTARMON_FQNAME = ALT_DMALL_DARK_SUPERSTARMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_DARK_SUPERSTARMON_FQNAME_LEN = sizeof(ALT_DMALL_DARK_SUPERSTARMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_DARK_TYRANOMON_X_FQID_ARR[] = "dmall:dark_tyranomon_x";
    inline static constexpr const char* ALT_DMALL_DARK_TYRANOMON_X_FQID = ALT_DMALL_DARK_TYRANOMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_DARK_TYRANOMON_X_FQID_LEN = sizeof(ALT_DMALL_DARK_TYRANOMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_DARK_TYRANOMON_X_FQNAME_ARR[] = "dmall:Dark Tyranomon X";
    inline static constexpr const char* ALT_DMALL_DARK_TYRANOMON_X_FQNAME = ALT_DMALL_DARK_TYRANOMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_DARK_TYRANOMON_X_FQNAME_LEN = sizeof(ALT_DMALL_DARK_TYRANOMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_DEATH_MERAMON_FQID_ARR[] = "dmall:death_meramon";
    inline static constexpr const char* ALT_DMALL_DEATH_MERAMON_FQID = ALT_DMALL_DEATH_MERAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_DEATH_MERAMON_FQID_LEN = sizeof(ALT_DMALL_DEATH_MERAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_DEATH_MERAMON_FQNAME_ARR[] = "dmall:Death Meramon";
    inline static constexpr const char* ALT_DMALL_DEATH_MERAMON_FQNAME = ALT_DMALL_DEATH_MERAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_DEATH_MERAMON_FQNAME_LEN = sizeof(ALT_DMALL_DEATH_MERAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_DEATHMON_BLACK_FQID_ARR[] = "dmall:deathmon_black";
    inline static constexpr const char* ALT_DMALL_DEATHMON_BLACK_FQID = ALT_DMALL_DEATHMON_BLACK_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_DEATHMON_BLACK_FQID_LEN = sizeof(ALT_DMALL_DEATHMON_BLACK_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_DEATHMON_BLACK_FQNAME_ARR[] = "dmall:Deathmon (Black)";
    inline static constexpr const char* ALT_DMALL_DEATHMON_BLACK_FQNAME = ALT_DMALL_DEATHMON_BLACK_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_DEATHMON_BLACK_FQNAME_LEN = sizeof(ALT_DMALL_DEATHMON_BLACK_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_DEATHMON_FQID_ARR[] = "dmall:deathmon";
    inline static constexpr const char* ALT_DMALL_DEATHMON_FQID = ALT_DMALL_DEATHMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_DEATHMON_FQID_LEN = sizeof(ALT_DMALL_DEATHMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_DEATHMON_FQNAME_ARR[] = "dmall:Deathmon";
    inline static constexpr const char* ALT_DMALL_DEATHMON_FQNAME = ALT_DMALL_DEATHMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_DEATHMON_FQNAME_LEN = sizeof(ALT_DMALL_DEATHMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_DEATH_X_DORUGAMON_FQID_ARR[] = "dmall:death_x_dorugamon";
    inline static constexpr const char* ALT_DMALL_DEATH_X_DORUGAMON_FQID = ALT_DMALL_DEATH_X_DORUGAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_DEATH_X_DORUGAMON_FQID_LEN = sizeof(ALT_DMALL_DEATH_X_DORUGAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_DEATH_X_DORUGAMON_FQNAME_ARR[] = "dmall:Death-X-DORUgamon";
    inline static constexpr const char* ALT_DMALL_DEATH_X_DORUGAMON_FQNAME = ALT_DMALL_DEATH_X_DORUGAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_DEATH_X_DORUGAMON_FQNAME_LEN = sizeof(ALT_DMALL_DEATH_X_DORUGAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_DELUMON_FQID_ARR[] = "dmall:delumon";
    inline static constexpr const char* ALT_DMALL_DELUMON_FQID = ALT_DMALL_DELUMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_DELUMON_FQID_LEN = sizeof(ALT_DMALL_DELUMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_DELUMON_FQNAME_ARR[] = "dmall:Delumon";
    inline static constexpr const char* ALT_DMALL_DELUMON_FQNAME = ALT_DMALL_DELUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_DELUMON_FQNAME_LEN = sizeof(ALT_DMALL_DELUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_DEMON_FQID_ARR[] = "dmall:demon";
    inline static constexpr const char* ALT_DMALL_DEMON_FQID = ALT_DMALL_DEMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_DEMON_FQID_LEN = sizeof(ALT_DMALL_DEMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_DEMON_FQNAME_ARR[] = "dmall:Demon";
    inline static constexpr const char* ALT_DMALL_DEMON_FQNAME = ALT_DMALL_DEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_DEMON_FQNAME_LEN = sizeof(ALT_DMALL_DEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_DEMON_X_FQID_ARR[] = "dmall:demon_x";
    inline static constexpr const char* ALT_DMALL_DEMON_X_FQID = ALT_DMALL_DEMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_DEMON_X_FQID_LEN = sizeof(ALT_DMALL_DEMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_DEMON_X_FQNAME_ARR[] = "dmall:Demon X";
    inline static constexpr const char* ALT_DMALL_DEMON_X_FQNAME = ALT_DMALL_DEMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_DEMON_X_FQNAME_LEN = sizeof(ALT_DMALL_DEMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_DEVIMON_FQID_ARR[] = "dmall:devimon";
    inline static constexpr const char* ALT_DMALL_DEVIMON_FQID = ALT_DMALL_DEVIMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_DEVIMON_FQID_LEN = sizeof(ALT_DMALL_DEVIMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_DEVIMON_FQNAME_ARR[] = "dmall:Devimon";
    inline static constexpr const char* ALT_DMALL_DEVIMON_FQNAME = ALT_DMALL_DEVIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_DEVIMON_FQNAME_LEN = sizeof(ALT_DMALL_DEVIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_DIABLOMON_FQID_ARR[] = "dmall:diablomon";
    inline static constexpr const char* ALT_DMALL_DIABLOMON_FQID = ALT_DMALL_DIABLOMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_DIABLOMON_FQID_LEN = sizeof(ALT_DMALL_DIABLOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_DIABLOMON_FQNAME_ARR[] = "dmall:Diablomon";
    inline static constexpr const char* ALT_DMALL_DIABLOMON_FQNAME = ALT_DMALL_DIABLOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_DIABLOMON_FQNAME_LEN = sizeof(ALT_DMALL_DIABLOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_DIABLOMON_X_FQID_ARR[] = "dmall:diablomon_x";
    inline static constexpr const char* ALT_DMALL_DIABLOMON_X_FQID = ALT_DMALL_DIABLOMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_DIABLOMON_X_FQID_LEN = sizeof(ALT_DMALL_DIABLOMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_DIABLOMON_X_FQNAME_ARR[] = "dmall:Diablomon X";
    inline static constexpr const char* ALT_DMALL_DIABLOMON_X_FQNAME = ALT_DMALL_DIABLOMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_DIABLOMON_X_FQNAME_LEN = sizeof(ALT_DMALL_DIABLOMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_DIANAMON_FQID_ARR[] = "dmall:dianamon";
    inline static constexpr const char* ALT_DMALL_DIANAMON_FQID = ALT_DMALL_DIANAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_DIANAMON_FQID_LEN = sizeof(ALT_DMALL_DIANAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_DIANAMON_FQNAME_ARR[] = "dmall:Dianamon";
    inline static constexpr const char* ALT_DMALL_DIANAMON_FQNAME = ALT_DMALL_DIANAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_DIANAMON_FQNAME_LEN = sizeof(ALT_DMALL_DIANAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_DIGINORIMON_FQID_ARR[] = "dmall:diginorimon";
    inline static constexpr const char* ALT_DMALL_DIGINORIMON_FQID = ALT_DMALL_DIGINORIMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_DIGINORIMON_FQID_LEN = sizeof(ALT_DMALL_DIGINORIMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_DIGINORIMON_FQNAME_ARR[] = "dmall:Diginorimon";
    inline static constexpr const char* ALT_DMALL_DIGINORIMON_FQNAME = ALT_DMALL_DIGINORIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_DIGINORIMON_FQNAME_LEN = sizeof(ALT_DMALL_DIGINORIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_DIGITAMAMON_FQID_ARR[] = "dmall:digitamamon";
    inline static constexpr const char* ALT_DMALL_DIGITAMAMON_FQID = ALT_DMALL_DIGITAMAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_DIGITAMAMON_FQID_LEN = sizeof(ALT_DMALL_DIGITAMAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_DIGITAMAMON_FQNAME_ARR[] = "dmall:Digitamamon";
    inline static constexpr const char* ALT_DMALL_DIGITAMAMON_FQNAME = ALT_DMALL_DIGITAMAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_DIGITAMAMON_FQNAME_LEN = sizeof(ALT_DMALL_DIGITAMAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_DINOHUMON_FQID_ARR[] = "dmall:dinohumon";
    inline static constexpr const char* ALT_DMALL_DINOHUMON_FQID = ALT_DMALL_DINOHUMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_DINOHUMON_FQID_LEN = sizeof(ALT_DMALL_DINOHUMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_DINOHUMON_FQNAME_ARR[] = "dmall:Dinohumon";
    inline static constexpr const char* ALT_DMALL_DINOHUMON_FQNAME = ALT_DMALL_DINOHUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_DINOHUMON_FQNAME_LEN = sizeof(ALT_DMALL_DINOHUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_DINOREXMON_FQID_ARR[] = "dmall:dinorexmon";
    inline static constexpr const char* ALT_DMALL_DINOREXMON_FQID = ALT_DMALL_DINOREXMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_DINOREXMON_FQID_LEN = sizeof(ALT_DMALL_DINOREXMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_DINOREXMON_FQNAME_ARR[] = "dmall:Dinorexmon";
    inline static constexpr const char* ALT_DMALL_DINOREXMON_FQNAME = ALT_DMALL_DINOREXMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_DINOREXMON_FQNAME_LEN = sizeof(ALT_DMALL_DINOREXMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_DINOTIGERMON_FQID_ARR[] = "dmall:dinotigermon";
    inline static constexpr const char* ALT_DMALL_DINOTIGERMON_FQID = ALT_DMALL_DINOTIGERMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_DINOTIGERMON_FQID_LEN = sizeof(ALT_DMALL_DINOTIGERMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_DINOTIGERMON_FQNAME_ARR[] = "dmall:Dinotigermon";
    inline static constexpr const char* ALT_DMALL_DINOTIGERMON_FQNAME = ALT_DMALL_DINOTIGERMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_DINOTIGERMON_FQNAME_LEN = sizeof(ALT_DMALL_DINOTIGERMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_DOBERMON_FQID_ARR[] = "dmall:dobermon";
    inline static constexpr const char* ALT_DMALL_DOBERMON_FQID = ALT_DMALL_DOBERMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_DOBERMON_FQID_LEN = sizeof(ALT_DMALL_DOBERMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_DOBERMON_FQNAME_ARR[] = "dmall:Dobermon";
    inline static constexpr const char* ALT_DMALL_DOBERMON_FQNAME = ALT_DMALL_DOBERMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_DOBERMON_FQNAME_LEN = sizeof(ALT_DMALL_DOBERMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_DODOMON_FQID_ARR[] = "dmall:dodomon";
    inline static constexpr const char* ALT_DMALL_DODOMON_FQID = ALT_DMALL_DODOMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_DODOMON_FQID_LEN = sizeof(ALT_DMALL_DODOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_DODOMON_FQNAME_ARR[] = "dmall:Dodomon";
    inline static constexpr const char* ALT_DMALL_DODOMON_FQNAME = ALT_DMALL_DODOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_DODOMON_FQNAME_LEN = sizeof(ALT_DMALL_DODOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_DOGMON_FQID_ARR[] = "dmall:dogmon";
    inline static constexpr const char* ALT_DMALL_DOGMON_FQID = ALT_DMALL_DOGMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_DOGMON_FQID_LEN = sizeof(ALT_DMALL_DOGMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_DOGMON_FQNAME_ARR[] = "dmall:Dogmon";
    inline static constexpr const char* ALT_DMALL_DOGMON_FQNAME = ALT_DMALL_DOGMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_DOGMON_FQNAME_LEN = sizeof(ALT_DMALL_DOGMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_DOKIMON_FQID_ARR[] = "dmall:dokimon";
    inline static constexpr const char* ALT_DMALL_DOKIMON_FQID = ALT_DMALL_DOKIMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_DOKIMON_FQID_LEN = sizeof(ALT_DMALL_DOKIMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_DOKIMON_FQNAME_ARR[] = "dmall:Dokimon";
    inline static constexpr const char* ALT_DMALL_DOKIMON_FQNAME = ALT_DMALL_DOKIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_DOKIMON_FQNAME_LEN = sizeof(ALT_DMALL_DOKIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_DOKUGUMON_FQID_ARR[] = "dmall:dokugumon";
    inline static constexpr const char* ALT_DMALL_DOKUGUMON_FQID = ALT_DMALL_DOKUGUMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_DOKUGUMON_FQID_LEN = sizeof(ALT_DMALL_DOKUGUMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_DOKUGUMON_FQNAME_ARR[] = "dmall:Dokugumon";
    inline static constexpr const char* ALT_DMALL_DOKUGUMON_FQNAME = ALT_DMALL_DOKUGUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_DOKUGUMON_FQNAME_LEN = sizeof(ALT_DMALL_DOKUGUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_DOKUNEMON_FQID_ARR[] = "dmall:dokunemon";
    inline static constexpr const char* ALT_DMALL_DOKUNEMON_FQID = ALT_DMALL_DOKUNEMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_DOKUNEMON_FQID_LEN = sizeof(ALT_DMALL_DOKUNEMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_DOKUNEMON_FQNAME_ARR[] = "dmall:Dokunemon";
    inline static constexpr const char* ALT_DMALL_DOKUNEMON_FQNAME = ALT_DMALL_DOKUNEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_DOKUNEMON_FQNAME_LEN = sizeof(ALT_DMALL_DOKUNEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_DORIMON_FQID_ARR[] = "dmall:dorimon";
    inline static constexpr const char* ALT_DMALL_DORIMON_FQID = ALT_DMALL_DORIMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_DORIMON_FQID_LEN = sizeof(ALT_DMALL_DORIMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_DORIMON_FQNAME_ARR[] = "dmall:Dorimon";
    inline static constexpr const char* ALT_DMALL_DORIMON_FQNAME = ALT_DMALL_DORIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_DORIMON_FQNAME_LEN = sizeof(ALT_DMALL_DORIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_DORUGAMON_FQID_ARR[] = "dmall:dorugamon";
    inline static constexpr const char* ALT_DMALL_DORUGAMON_FQID = ALT_DMALL_DORUGAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_DORUGAMON_FQID_LEN = sizeof(ALT_DMALL_DORUGAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_DORUGAMON_FQNAME_ARR[] = "dmall:DORUgamon";
    inline static constexpr const char* ALT_DMALL_DORUGAMON_FQNAME = ALT_DMALL_DORUGAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_DORUGAMON_FQNAME_LEN = sizeof(ALT_DMALL_DORUGAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_DORUGORAMON_FQID_ARR[] = "dmall:dorugoramon";
    inline static constexpr const char* ALT_DMALL_DORUGORAMON_FQID = ALT_DMALL_DORUGORAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_DORUGORAMON_FQID_LEN = sizeof(ALT_DMALL_DORUGORAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_DORUGORAMON_FQNAME_ARR[] = "dmall:DORUgoramon";
    inline static constexpr const char* ALT_DMALL_DORUGORAMON_FQNAME = ALT_DMALL_DORUGORAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_DORUGORAMON_FQNAME_LEN = sizeof(ALT_DMALL_DORUGORAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_DORUGUREMON_FQID_ARR[] = "dmall:doruguremon";
    inline static constexpr const char* ALT_DMALL_DORUGUREMON_FQID = ALT_DMALL_DORUGUREMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_DORUGUREMON_FQID_LEN = sizeof(ALT_DMALL_DORUGUREMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_DORUGUREMON_FQNAME_ARR[] = "dmall:DORUguremon";
    inline static constexpr const char* ALT_DMALL_DORUGUREMON_FQNAME = ALT_DMALL_DORUGUREMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_DORUGUREMON_FQNAME_LEN = sizeof(ALT_DMALL_DORUGUREMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_DORUMON_FQID_ARR[] = "dmall:dorumon";
    inline static constexpr const char* ALT_DMALL_DORUMON_FQID = ALT_DMALL_DORUMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_DORUMON_FQID_LEN = sizeof(ALT_DMALL_DORUMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_DORUMON_FQNAME_ARR[] = "dmall:DORUmon";
    inline static constexpr const char* ALT_DMALL_DORUMON_FQNAME = ALT_DMALL_DORUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_DORUMON_FQNAME_LEN = sizeof(ALT_DMALL_DORUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_DRACOMON_X_FQID_ARR[] = "dmall:dracomon_x";
    inline static constexpr const char* ALT_DMALL_DRACOMON_X_FQID = ALT_DMALL_DRACOMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_DRACOMON_X_FQID_LEN = sizeof(ALT_DMALL_DRACOMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_DRACOMON_X_FQNAME_ARR[] = "dmall:Dracomon X";
    inline static constexpr const char* ALT_DMALL_DRACOMON_X_FQNAME = ALT_DMALL_DRACOMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_DRACOMON_X_FQNAME_LEN = sizeof(ALT_DMALL_DRACOMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_DRACUMON_FQID_ARR[] = "dmall:dracumon";
    inline static constexpr const char* ALT_DMALL_DRACUMON_FQID = ALT_DMALL_DRACUMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_DRACUMON_FQID_LEN = sizeof(ALT_DMALL_DRACUMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_DRACUMON_FQNAME_ARR[] = "dmall:Dracumon";
    inline static constexpr const char* ALT_DMALL_DRACUMON_FQNAME = ALT_DMALL_DRACUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_DRACUMON_FQNAME_LEN = sizeof(ALT_DMALL_DRACUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_DRIMOGEMON_FQID_ARR[] = "dmall:drimogemon";
    inline static constexpr const char* ALT_DMALL_DRIMOGEMON_FQID = ALT_DMALL_DRIMOGEMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_DRIMOGEMON_FQID_LEN = sizeof(ALT_DMALL_DRIMOGEMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_DRIMOGEMON_FQNAME_ARR[] = "dmall:Drimogemon";
    inline static constexpr const char* ALT_DMALL_DRIMOGEMON_FQNAME = ALT_DMALL_DRIMOGEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_DRIMOGEMON_FQNAME_LEN = sizeof(ALT_DMALL_DRIMOGEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_DUFTMON_FQID_ARR[] = "dmall:duftmon";
    inline static constexpr const char* ALT_DMALL_DUFTMON_FQID = ALT_DMALL_DUFTMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_DUFTMON_FQID_LEN = sizeof(ALT_DMALL_DUFTMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_DUFTMON_FQNAME_ARR[] = "dmall:Duftmon";
    inline static constexpr const char* ALT_DMALL_DUFTMON_FQNAME = ALT_DMALL_DUFTMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_DUFTMON_FQNAME_LEN = sizeof(ALT_DMALL_DUFTMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_DUFTMON_X_FQID_ARR[] = "dmall:duftmon_x";
    inline static constexpr const char* ALT_DMALL_DUFTMON_X_FQID = ALT_DMALL_DUFTMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_DUFTMON_X_FQID_LEN = sizeof(ALT_DMALL_DUFTMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_DUFTMON_X_FQNAME_ARR[] = "dmall:Duftmon X";
    inline static constexpr const char* ALT_DMALL_DUFTMON_X_FQNAME = ALT_DMALL_DUFTMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_DUFTMON_X_FQNAME_LEN = sizeof(ALT_DMALL_DUFTMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_DUKEMON_FQID_ARR[] = "dmall:dukemon";
    inline static constexpr const char* ALT_DMALL_DUKEMON_FQID = ALT_DMALL_DUKEMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_DUKEMON_FQID_LEN = sizeof(ALT_DMALL_DUKEMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_DUKEMON_FQNAME_ARR[] = "dmall:Dukemon";
    inline static constexpr const char* ALT_DMALL_DUKEMON_FQNAME = ALT_DMALL_DUKEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_DUKEMON_FQNAME_LEN = sizeof(ALT_DMALL_DUKEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_DUKEMON_X_FQID_ARR[] = "dmall:dukemon_x";
    inline static constexpr const char* ALT_DMALL_DUKEMON_X_FQID = ALT_DMALL_DUKEMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_DUKEMON_X_FQID_LEN = sizeof(ALT_DMALL_DUKEMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_DUKEMON_X_FQNAME_ARR[] = "dmall:Dukemon X";
    inline static constexpr const char* ALT_DMALL_DUKEMON_X_FQNAME = ALT_DMALL_DUKEMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_DUKEMON_X_FQNAME_LEN = sizeof(ALT_DMALL_DUKEMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_DURAMON_FQID_ARR[] = "dmall:duramon";
    inline static constexpr const char* ALT_DMALL_DURAMON_FQID = ALT_DMALL_DURAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_DURAMON_FQID_LEN = sizeof(ALT_DMALL_DURAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_DURAMON_FQNAME_ARR[] = "dmall:Duramon";
    inline static constexpr const char* ALT_DMALL_DURAMON_FQNAME = ALT_DMALL_DURAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_DURAMON_FQNAME_LEN = sizeof(ALT_DMALL_DURAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_DUSKMON_FQID_ARR[] = "dmall:duskmon";
    inline static constexpr const char* ALT_DMALL_DUSKMON_FQID = ALT_DMALL_DUSKMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_DUSKMON_FQID_LEN = sizeof(ALT_DMALL_DUSKMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_DUSKMON_FQNAME_ARR[] = "dmall:Duskmon";
    inline static constexpr const char* ALT_DMALL_DUSKMON_FQNAME = ALT_DMALL_DUSKMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_DUSKMON_FQNAME_LEN = sizeof(ALT_DMALL_DUSKMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_DYNASMON_X_FQID_ARR[] = "dmall:dynasmon_x";
    inline static constexpr const char* ALT_DMALL_DYNASMON_X_FQID = ALT_DMALL_DYNASMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_DYNASMON_X_FQID_LEN = sizeof(ALT_DMALL_DYNASMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_DYNASMON_X_FQNAME_ARR[] = "dmall:Dynasmon X";
    inline static constexpr const char* ALT_DMALL_DYNASMON_X_FQNAME = ALT_DMALL_DYNASMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_DYNASMON_X_FQNAME_LEN = sizeof(ALT_DMALL_DYNASMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_EBEMON_FQID_ARR[] = "dmall:ebemon";
    inline static constexpr const char* ALT_DMALL_EBEMON_FQID = ALT_DMALL_EBEMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_EBEMON_FQID_LEN = sizeof(ALT_DMALL_EBEMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_EBEMON_FQNAME_ARR[] = "dmall:Ebemon";
    inline static constexpr const char* ALT_DMALL_EBEMON_FQNAME = ALT_DMALL_EBEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_EBEMON_FQNAME_LEN = sizeof(ALT_DMALL_EBEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_EBEMON_X_FQID_ARR[] = "dmall:ebemon_x";
    inline static constexpr const char* ALT_DMALL_EBEMON_X_FQID = ALT_DMALL_EBEMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_EBEMON_X_FQID_LEN = sizeof(ALT_DMALL_EBEMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_EBEMON_X_FQNAME_ARR[] = "dmall:Ebemon X";
    inline static constexpr const char* ALT_DMALL_EBEMON_X_FQNAME = ALT_DMALL_EBEMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_EBEMON_X_FQNAME_LEN = sizeof(ALT_DMALL_EBEMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_EBIDRAMON_FQID_ARR[] = "dmall:ebidramon";
    inline static constexpr const char* ALT_DMALL_EBIDRAMON_FQID = ALT_DMALL_EBIDRAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_EBIDRAMON_FQID_LEN = sizeof(ALT_DMALL_EBIDRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_EBIDRAMON_FQNAME_ARR[] = "dmall:Ebidramon";
    inline static constexpr const char* ALT_DMALL_EBIDRAMON_FQNAME = ALT_DMALL_EBIDRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_EBIDRAMON_FQNAME_LEN = sizeof(ALT_DMALL_EBIDRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_EKAKIMON_FQID_ARR[] = "dmall:ekakimon";
    inline static constexpr const char* ALT_DMALL_EKAKIMON_FQID = ALT_DMALL_EKAKIMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_EKAKIMON_FQID_LEN = sizeof(ALT_DMALL_EKAKIMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_EKAKIMON_FQNAME_ARR[] = "dmall:Ekakimon";
    inline static constexpr const char* ALT_DMALL_EKAKIMON_FQNAME = ALT_DMALL_EKAKIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_EKAKIMON_FQNAME_LEN = sizeof(ALT_DMALL_EKAKIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_ELECMON_FQID_ARR[] = "dmall:elecmon";
    inline static constexpr const char* ALT_DMALL_ELECMON_FQID = ALT_DMALL_ELECMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_ELECMON_FQID_LEN = sizeof(ALT_DMALL_ELECMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_ELECMON_FQNAME_ARR[] = "dmall:Elecmon";
    inline static constexpr const char* ALT_DMALL_ELECMON_FQNAME = ALT_DMALL_ELECMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_ELECMON_FQNAME_LEN = sizeof(ALT_DMALL_ELECMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_ELECMON_VIOLET_FQID_ARR[] = "dmall:elecmon_violet";
    inline static constexpr const char* ALT_DMALL_ELECMON_VIOLET_FQID = ALT_DMALL_ELECMON_VIOLET_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_ELECMON_VIOLET_FQID_LEN = sizeof(ALT_DMALL_ELECMON_VIOLET_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_ELECMON_VIOLET_FQNAME_ARR[] = "dmall:Elecmon (Violet)";
    inline static constexpr const char* ALT_DMALL_ELECMON_VIOLET_FQNAME = ALT_DMALL_ELECMON_VIOLET_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_ELECMON_VIOLET_FQNAME_LEN = sizeof(ALT_DMALL_ELECMON_VIOLET_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_ENTMON_FQID_ARR[] = "dmall:entmon";
    inline static constexpr const char* ALT_DMALL_ENTMON_FQID = ALT_DMALL_ENTMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_ENTMON_FQID_LEN = sizeof(ALT_DMALL_ENTMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_ENTMON_FQNAME_ARR[] = "dmall:Entmon";
    inline static constexpr const char* ALT_DMALL_ENTMON_FQNAME = ALT_DMALL_ENTMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_ENTMON_FQNAME_LEN = sizeof(ALT_DMALL_ENTMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_ETEMON_FQID_ARR[] = "dmall:etemon";
    inline static constexpr const char* ALT_DMALL_ETEMON_FQID = ALT_DMALL_ETEMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_ETEMON_FQID_LEN = sizeof(ALT_DMALL_ETEMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_ETEMON_FQNAME_ARR[] = "dmall:Etemon";
    inline static constexpr const char* ALT_DMALL_ETEMON_FQNAME = ALT_DMALL_ETEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_ETEMON_FQNAME_LEN = sizeof(ALT_DMALL_ETEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_EXAMON_X_FQID_ARR[] = "dmall:examon_x";
    inline static constexpr const char* ALT_DMALL_EXAMON_X_FQID = ALT_DMALL_EXAMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_EXAMON_X_FQID_LEN = sizeof(ALT_DMALL_EXAMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_EXAMON_X_FQNAME_ARR[] = "dmall:Examon X";
    inline static constexpr const char* ALT_DMALL_EXAMON_X_FQNAME = ALT_DMALL_EXAMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_EXAMON_X_FQNAME_LEN = sizeof(ALT_DMALL_EXAMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_FILMON_FQID_ARR[] = "dmall:filmon";
    inline static constexpr const char* ALT_DMALL_FILMON_FQID = ALT_DMALL_FILMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_FILMON_FQID_LEN = sizeof(ALT_DMALL_FILMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_FILMON_FQNAME_ARR[] = "dmall:Filmon";
    inline static constexpr const char* ALT_DMALL_FILMON_FQNAME = ALT_DMALL_FILMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_FILMON_FQNAME_LEN = sizeof(ALT_DMALL_FILMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_FIRAMON_FQID_ARR[] = "dmall:firamon";
    inline static constexpr const char* ALT_DMALL_FIRAMON_FQID = ALT_DMALL_FIRAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_FIRAMON_FQID_LEN = sizeof(ALT_DMALL_FIRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_FIRAMON_FQNAME_ARR[] = "dmall:Firamon";
    inline static constexpr const char* ALT_DMALL_FIRAMON_FQNAME = ALT_DMALL_FIRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_FIRAMON_FQNAME_LEN = sizeof(ALT_DMALL_FIRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_FLAREMON_FQID_ARR[] = "dmall:flaremon";
    inline static constexpr const char* ALT_DMALL_FLAREMON_FQID = ALT_DMALL_FLAREMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_FLAREMON_FQID_LEN = sizeof(ALT_DMALL_FLAREMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_FLAREMON_FQNAME_ARR[] = "dmall:Flaremon";
    inline static constexpr const char* ALT_DMALL_FLAREMON_FQNAME = ALT_DMALL_FLAREMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_FLAREMON_FQNAME_LEN = sizeof(ALT_DMALL_FLAREMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_FLORAMON_FQID_ARR[] = "dmall:floramon";
    inline static constexpr const char* ALT_DMALL_FLORAMON_FQID = ALT_DMALL_FLORAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_FLORAMON_FQID_LEN = sizeof(ALT_DMALL_FLORAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_FLORAMON_FQNAME_ARR[] = "dmall:Floramon";
    inline static constexpr const char* ALT_DMALL_FLORAMON_FQNAME = ALT_DMALL_FLORAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_FLORAMON_FQNAME_LEN = sizeof(ALT_DMALL_FLORAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_FUFUMON_FQID_ARR[] = "dmall:fufumon";
    inline static constexpr const char* ALT_DMALL_FUFUMON_FQID = ALT_DMALL_FUFUMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_FUFUMON_FQID_LEN = sizeof(ALT_DMALL_FUFUMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_FUFUMON_FQNAME_ARR[] = "dmall:Fufumon";
    inline static constexpr const char* ALT_DMALL_FUFUMON_FQNAME = ALT_DMALL_FUFUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_FUFUMON_FQNAME_LEN = sizeof(ALT_DMALL_FUFUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_FUGAMON_FQID_ARR[] = "dmall:fugamon";
    inline static constexpr const char* ALT_DMALL_FUGAMON_FQID = ALT_DMALL_FUGAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_FUGAMON_FQID_LEN = sizeof(ALT_DMALL_FUGAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_FUGAMON_FQNAME_ARR[] = "dmall:Fugamon";
    inline static constexpr const char* ALT_DMALL_FUGAMON_FQNAME = ALT_DMALL_FUGAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_FUGAMON_FQNAME_LEN = sizeof(ALT_DMALL_FUGAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_FUNBEEMON_FQID_ARR[] = "dmall:funbeemon";
    inline static constexpr const char* ALT_DMALL_FUNBEEMON_FQID = ALT_DMALL_FUNBEEMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_FUNBEEMON_FQID_LEN = sizeof(ALT_DMALL_FUNBEEMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_FUNBEEMON_FQNAME_ARR[] = "dmall:Funbeemon";
    inline static constexpr const char* ALT_DMALL_FUNBEEMON_FQNAME = ALT_DMALL_FUNBEEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_FUNBEEMON_FQNAME_LEN = sizeof(ALT_DMALL_FUNBEEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_GABUMON_X_FQID_ARR[] = "dmall:gabumon_x";
    inline static constexpr const char* ALT_DMALL_GABUMON_X_FQID = ALT_DMALL_GABUMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_GABUMON_X_FQID_LEN = sizeof(ALT_DMALL_GABUMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_GABUMON_X_FQNAME_ARR[] = "dmall:Gabumon X";
    inline static constexpr const char* ALT_DMALL_GABUMON_X_FQNAME = ALT_DMALL_GABUMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_GABUMON_X_FQNAME_LEN = sizeof(ALT_DMALL_GABUMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_GAIOUMON_FQID_ARR[] = "dmall:gaioumon";
    inline static constexpr const char* ALT_DMALL_GAIOUMON_FQID = ALT_DMALL_GAIOUMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_GAIOUMON_FQID_LEN = sizeof(ALT_DMALL_GAIOUMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_GAIOUMON_FQNAME_ARR[] = "dmall:Gaioumon";
    inline static constexpr const char* ALT_DMALL_GAIOUMON_FQNAME = ALT_DMALL_GAIOUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_GAIOUMON_FQNAME_LEN = sizeof(ALT_DMALL_GAIOUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_GALGOMON_FQID_ARR[] = "dmall:galgomon";
    inline static constexpr const char* ALT_DMALL_GALGOMON_FQID = ALT_DMALL_GALGOMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_GALGOMON_FQID_LEN = sizeof(ALT_DMALL_GALGOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_GALGOMON_FQNAME_ARR[] = "dmall:Galgomon";
    inline static constexpr const char* ALT_DMALL_GALGOMON_FQNAME = ALT_DMALL_GALGOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_GALGOMON_FQNAME_LEN = sizeof(ALT_DMALL_GALGOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_GAMMAMON_FQID_ARR[] = "dmall:gammamon";
    inline static constexpr const char* ALT_DMALL_GAMMAMON_FQID = ALT_DMALL_GAMMAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_GAMMAMON_FQID_LEN = sizeof(ALT_DMALL_GAMMAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_GAMMAMON_FQNAME_ARR[] = "dmall:Gammamon";
    inline static constexpr const char* ALT_DMALL_GAMMAMON_FQNAME = ALT_DMALL_GAMMAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_GAMMAMON_FQNAME_LEN = sizeof(ALT_DMALL_GAMMAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_GANIMON_FQID_ARR[] = "dmall:ganimon";
    inline static constexpr const char* ALT_DMALL_GANIMON_FQID = ALT_DMALL_GANIMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_GANIMON_FQID_LEN = sizeof(ALT_DMALL_GANIMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_GANIMON_FQNAME_ARR[] = "dmall:Ganimon";
    inline static constexpr const char* ALT_DMALL_GANIMON_FQNAME = ALT_DMALL_GANIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_GANIMON_FQNAME_LEN = sizeof(ALT_DMALL_GANIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_GANKOOMON_FQID_ARR[] = "dmall:gankoomon";
    inline static constexpr const char* ALT_DMALL_GANKOOMON_FQID = ALT_DMALL_GANKOOMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_GANKOOMON_FQID_LEN = sizeof(ALT_DMALL_GANKOOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_GANKOOMON_FQNAME_ARR[] = "dmall:Gankoomon";
    inline static constexpr const char* ALT_DMALL_GANKOOMON_FQNAME = ALT_DMALL_GANKOOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_GANKOOMON_FQNAME_LEN = sizeof(ALT_DMALL_GANKOOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_GANKOOMON_X_FQID_ARR[] = "dmall:gankoomon_x";
    inline static constexpr const char* ALT_DMALL_GANKOOMON_X_FQID = ALT_DMALL_GANKOOMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_GANKOOMON_X_FQID_LEN = sizeof(ALT_DMALL_GANKOOMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_GANKOOMON_X_FQNAME_ARR[] = "dmall:Gankoomon X";
    inline static constexpr const char* ALT_DMALL_GANKOOMON_X_FQNAME = ALT_DMALL_GANKOOMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_GANKOOMON_X_FQNAME_LEN = sizeof(ALT_DMALL_GANKOOMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_GAOGAMON_FQID_ARR[] = "dmall:gaogamon";
    inline static constexpr const char* ALT_DMALL_GAOGAMON_FQID = ALT_DMALL_GAOGAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_GAOGAMON_FQID_LEN = sizeof(ALT_DMALL_GAOGAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_GAOGAMON_FQNAME_ARR[] = "dmall:Gaogamon";
    inline static constexpr const char* ALT_DMALL_GAOGAMON_FQNAME = ALT_DMALL_GAOGAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_GAOGAMON_FQNAME_LEN = sizeof(ALT_DMALL_GAOGAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_GAOMON_FQID_ARR[] = "dmall:gaomon";
    inline static constexpr const char* ALT_DMALL_GAOMON_FQID = ALT_DMALL_GAOMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_GAOMON_FQID_LEN = sizeof(ALT_DMALL_GAOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_GAOMON_FQNAME_ARR[] = "dmall:Gaomon";
    inline static constexpr const char* ALT_DMALL_GAOMON_FQNAME = ALT_DMALL_GAOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_GAOMON_FQNAME_LEN = sizeof(ALT_DMALL_GAOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_GARUDAMON_FQID_ARR[] = "dmall:garudamon";
    inline static constexpr const char* ALT_DMALL_GARUDAMON_FQID = ALT_DMALL_GARUDAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_GARUDAMON_FQID_LEN = sizeof(ALT_DMALL_GARUDAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_GARUDAMON_FQNAME_ARR[] = "dmall:Garudamon";
    inline static constexpr const char* ALT_DMALL_GARUDAMON_FQNAME = ALT_DMALL_GARUDAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_GARUDAMON_FQNAME_LEN = sizeof(ALT_DMALL_GARUDAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_GARUDAMON_X_FQID_ARR[] = "dmall:garudamon_x";
    inline static constexpr const char* ALT_DMALL_GARUDAMON_X_FQID = ALT_DMALL_GARUDAMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_GARUDAMON_X_FQID_LEN = sizeof(ALT_DMALL_GARUDAMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_GARUDAMON_X_FQNAME_ARR[] = "dmall:Garudamon X";
    inline static constexpr const char* ALT_DMALL_GARUDAMON_X_FQNAME = ALT_DMALL_GARUDAMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_GARUDAMON_X_FQNAME_LEN = sizeof(ALT_DMALL_GARUDAMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_GARURUMON_BLACK_FQID_ARR[] = "dmall:garurumon_black";
    inline static constexpr const char* ALT_DMALL_GARURUMON_BLACK_FQID = ALT_DMALL_GARURUMON_BLACK_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_GARURUMON_BLACK_FQID_LEN = sizeof(ALT_DMALL_GARURUMON_BLACK_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_GARURUMON_BLACK_FQNAME_ARR[] = "dmall:Garurumon (Black)";
    inline static constexpr const char* ALT_DMALL_GARURUMON_BLACK_FQNAME = ALT_DMALL_GARURUMON_BLACK_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_GARURUMON_BLACK_FQNAME_LEN = sizeof(ALT_DMALL_GARURUMON_BLACK_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_GARURUMON_FQID_ARR[] = "dmall:garurumon";
    inline static constexpr const char* ALT_DMALL_GARURUMON_FQID = ALT_DMALL_GARURUMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_GARURUMON_FQID_LEN = sizeof(ALT_DMALL_GARURUMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_GARURUMON_FQNAME_ARR[] = "dmall:Garurumon";
    inline static constexpr const char* ALT_DMALL_GARURUMON_FQNAME = ALT_DMALL_GARURUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_GARURUMON_FQNAME_LEN = sizeof(ALT_DMALL_GARURUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_GAWAPPAMON_FQID_ARR[] = "dmall:gawappamon";
    inline static constexpr const char* ALT_DMALL_GAWAPPAMON_FQID = ALT_DMALL_GAWAPPAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_GAWAPPAMON_FQID_LEN = sizeof(ALT_DMALL_GAWAPPAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_GAWAPPAMON_FQNAME_ARR[] = "dmall:Gawappamon";
    inline static constexpr const char* ALT_DMALL_GAWAPPAMON_FQNAME = ALT_DMALL_GAWAPPAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_GAWAPPAMON_FQNAME_LEN = sizeof(ALT_DMALL_GAWAPPAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_GAZIMON_FQID_ARR[] = "dmall:gazimon";
    inline static constexpr const char* ALT_DMALL_GAZIMON_FQID = ALT_DMALL_GAZIMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_GAZIMON_FQID_LEN = sizeof(ALT_DMALL_GAZIMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_GAZIMON_FQNAME_ARR[] = "dmall:Gazimon";
    inline static constexpr const char* ALT_DMALL_GAZIMON_FQNAME = ALT_DMALL_GAZIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_GAZIMON_FQNAME_LEN = sizeof(ALT_DMALL_GAZIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_GAZIMON_X_FQID_ARR[] = "dmall:gazimon_x";
    inline static constexpr const char* ALT_DMALL_GAZIMON_X_FQID = ALT_DMALL_GAZIMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_GAZIMON_X_FQID_LEN = sizeof(ALT_DMALL_GAZIMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_GAZIMON_X_FQNAME_ARR[] = "dmall:Gazimon X";
    inline static constexpr const char* ALT_DMALL_GAZIMON_X_FQNAME = ALT_DMALL_GAZIMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_GAZIMON_X_FQNAME_LEN = sizeof(ALT_DMALL_GAZIMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_GEKOMON_FQID_ARR[] = "dmall:gekomon";
    inline static constexpr const char* ALT_DMALL_GEKOMON_FQID = ALT_DMALL_GEKOMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_GEKOMON_FQID_LEN = sizeof(ALT_DMALL_GEKOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_GEKOMON_FQNAME_ARR[] = "dmall:Gekomon";
    inline static constexpr const char* ALT_DMALL_GEKOMON_FQNAME = ALT_DMALL_GEKOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_GEKOMON_FQNAME_LEN = sizeof(ALT_DMALL_GEKOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_GEO_GREYMON_FQID_ARR[] = "dmall:geo_greymon";
    inline static constexpr const char* ALT_DMALL_GEO_GREYMON_FQID = ALT_DMALL_GEO_GREYMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_GEO_GREYMON_FQID_LEN = sizeof(ALT_DMALL_GEO_GREYMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_GEO_GREYMON_FQNAME_ARR[] = "dmall:Geo Greymon";
    inline static constexpr const char* ALT_DMALL_GEO_GREYMON_FQNAME = ALT_DMALL_GEO_GREYMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_GEO_GREYMON_FQNAME_LEN = sizeof(ALT_DMALL_GEO_GREYMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_GERBEMON_FQID_ARR[] = "dmall:gerbemon";
    inline static constexpr const char* ALT_DMALL_GERBEMON_FQID = ALT_DMALL_GERBEMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_GERBEMON_FQID_LEN = sizeof(ALT_DMALL_GERBEMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_GERBEMON_FQNAME_ARR[] = "dmall:Gerbemon";
    inline static constexpr const char* ALT_DMALL_GERBEMON_FQNAME = ALT_DMALL_GERBEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_GERBEMON_FQNAME_LEN = sizeof(ALT_DMALL_GERBEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_GEREMON_FQID_ARR[] = "dmall:geremon";
    inline static constexpr const char* ALT_DMALL_GEREMON_FQID = ALT_DMALL_GEREMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_GEREMON_FQID_LEN = sizeof(ALT_DMALL_GEREMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_GEREMON_FQNAME_ARR[] = "dmall:Geremon";
    inline static constexpr const char* ALT_DMALL_GEREMON_FQNAME = ALT_DMALL_GEREMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_GEREMON_FQNAME_LEN = sizeof(ALT_DMALL_GEREMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_GESOMON_FQID_ARR[] = "dmall:gesomon";
    inline static constexpr const char* ALT_DMALL_GESOMON_FQID = ALT_DMALL_GESOMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_GESOMON_FQID_LEN = sizeof(ALT_DMALL_GESOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_GESOMON_FQNAME_ARR[] = "dmall:Gesomon";
    inline static constexpr const char* ALT_DMALL_GESOMON_FQNAME = ALT_DMALL_GESOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_GESOMON_FQNAME_LEN = sizeof(ALT_DMALL_GESOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_GHOSTMON_FQID_ARR[] = "dmall:ghostmon";
    inline static constexpr const char* ALT_DMALL_GHOSTMON_FQID = ALT_DMALL_GHOSTMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_GHOSTMON_FQID_LEN = sizeof(ALT_DMALL_GHOSTMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_GHOSTMON_FQNAME_ARR[] = "dmall:Ghostmon";
    inline static constexpr const char* ALT_DMALL_GHOSTMON_FQNAME = ALT_DMALL_GHOSTMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_GHOSTMON_FQNAME_LEN = sizeof(ALT_DMALL_GHOSTMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_GIGADRAMON_FQID_ARR[] = "dmall:gigadramon";
    inline static constexpr const char* ALT_DMALL_GIGADRAMON_FQID = ALT_DMALL_GIGADRAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_GIGADRAMON_FQID_LEN = sizeof(ALT_DMALL_GIGADRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_GIGADRAMON_FQNAME_ARR[] = "dmall:Gigadramon";
    inline static constexpr const char* ALT_DMALL_GIGADRAMON_FQNAME = ALT_DMALL_GIGADRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_GIGADRAMON_FQNAME_LEN = sizeof(ALT_DMALL_GIGADRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_GIGA_SEADRAMON_FQID_ARR[] = "dmall:giga_seadramon";
    inline static constexpr const char* ALT_DMALL_GIGA_SEADRAMON_FQID = ALT_DMALL_GIGA_SEADRAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_GIGA_SEADRAMON_FQID_LEN = sizeof(ALT_DMALL_GIGA_SEADRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_GIGA_SEADRAMON_FQNAME_ARR[] = "dmall:Giga Seadramon";
    inline static constexpr const char* ALT_DMALL_GIGA_SEADRAMON_FQNAME = ALT_DMALL_GIGA_SEADRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_GIGA_SEADRAMON_FQNAME_LEN = sizeof(ALT_DMALL_GIGA_SEADRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_GIGIMON_FQID_ARR[] = "dmall:gigimon";
    inline static constexpr const char* ALT_DMALL_GIGIMON_FQID = ALT_DMALL_GIGIMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_GIGIMON_FQID_LEN = sizeof(ALT_DMALL_GIGIMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_GIGIMON_FQNAME_ARR[] = "dmall:Gigimon";
    inline static constexpr const char* ALT_DMALL_GIGIMON_FQNAME = ALT_DMALL_GIGIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_GIGIMON_FQNAME_LEN = sizeof(ALT_DMALL_GIGIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_GINRYUMON_FQID_ARR[] = "dmall:ginryumon";
    inline static constexpr const char* ALT_DMALL_GINRYUMON_FQID = ALT_DMALL_GINRYUMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_GINRYUMON_FQID_LEN = sizeof(ALT_DMALL_GINRYUMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_GINRYUMON_FQNAME_ARR[] = "dmall:Ginryumon";
    inline static constexpr const char* ALT_DMALL_GINRYUMON_FQNAME = ALT_DMALL_GINRYUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_GINRYUMON_FQNAME_LEN = sizeof(ALT_DMALL_GINRYUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_GIROMON_FQID_ARR[] = "dmall:giromon";
    inline static constexpr const char* ALT_DMALL_GIROMON_FQID = ALT_DMALL_GIROMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_GIROMON_FQID_LEN = sizeof(ALT_DMALL_GIROMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_GIROMON_FQNAME_ARR[] = "dmall:Giromon";
    inline static constexpr const char* ALT_DMALL_GIROMON_FQNAME = ALT_DMALL_GIROMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_GIROMON_FQNAME_LEN = sizeof(ALT_DMALL_GIROMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_GIZAMON_FQID_ARR[] = "dmall:gizamon";
    inline static constexpr const char* ALT_DMALL_GIZAMON_FQID = ALT_DMALL_GIZAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_GIZAMON_FQID_LEN = sizeof(ALT_DMALL_GIZAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_GIZAMON_FQNAME_ARR[] = "dmall:Gizamon";
    inline static constexpr const char* ALT_DMALL_GIZAMON_FQNAME = ALT_DMALL_GIZAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_GIZAMON_FQNAME_LEN = sizeof(ALT_DMALL_GIZAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_GODDRAMON_X_FQID_ARR[] = "dmall:goddramon_x";
    inline static constexpr const char* ALT_DMALL_GODDRAMON_X_FQID = ALT_DMALL_GODDRAMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_GODDRAMON_X_FQID_LEN = sizeof(ALT_DMALL_GODDRAMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_GODDRAMON_X_FQNAME_ARR[] = "dmall:Goddramon X";
    inline static constexpr const char* ALT_DMALL_GODDRAMON_X_FQNAME = ALT_DMALL_GODDRAMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_GODDRAMON_X_FQNAME_LEN = sizeof(ALT_DMALL_GODDRAMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_GOGMAMON_FQID_ARR[] = "dmall:gogmamon";
    inline static constexpr const char* ALT_DMALL_GOGMAMON_FQID = ALT_DMALL_GOGMAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_GOGMAMON_FQID_LEN = sizeof(ALT_DMALL_GOGMAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_GOGMAMON_FQNAME_ARR[] = "dmall:Gogmamon";
    inline static constexpr const char* ALT_DMALL_GOGMAMON_FQNAME = ALT_DMALL_GOGMAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_GOGMAMON_FQNAME_LEN = sizeof(ALT_DMALL_GOGMAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_GOKIMON_FQID_ARR[] = "dmall:gokimon";
    inline static constexpr const char* ALT_DMALL_GOKIMON_FQID = ALT_DMALL_GOKIMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_GOKIMON_FQID_LEN = sizeof(ALT_DMALL_GOKIMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_GOKIMON_FQNAME_ARR[] = "dmall:Gokimon";
    inline static constexpr const char* ALT_DMALL_GOKIMON_FQNAME = ALT_DMALL_GOKIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_GOKIMON_FQNAME_LEN = sizeof(ALT_DMALL_GOKIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_GOKUMON_FQID_ARR[] = "dmall:gokumon";
    inline static constexpr const char* ALT_DMALL_GOKUMON_FQID = ALT_DMALL_GOKUMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_GOKUMON_FQID_LEN = sizeof(ALT_DMALL_GOKUMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_GOKUMON_FQNAME_ARR[] = "dmall:Gokumon";
    inline static constexpr const char* ALT_DMALL_GOKUMON_FQNAME = ALT_DMALL_GOKUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_GOKUMON_FQNAME_LEN = sizeof(ALT_DMALL_GOKUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_GOLD_NUMEMON_FQID_ARR[] = "dmall:gold_numemon";
    inline static constexpr const char* ALT_DMALL_GOLD_NUMEMON_FQID = ALT_DMALL_GOLD_NUMEMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_GOLD_NUMEMON_FQID_LEN = sizeof(ALT_DMALL_GOLD_NUMEMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_GOLD_NUMEMON_FQNAME_ARR[] = "dmall:Gold Numemon";
    inline static constexpr const char* ALT_DMALL_GOLD_NUMEMON_FQNAME = ALT_DMALL_GOLD_NUMEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_GOLD_NUMEMON_FQNAME_LEN = sizeof(ALT_DMALL_GOLD_NUMEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_GOLD_V_DRAMON_FQID_ARR[] = "dmall:gold_v_dramon";
    inline static constexpr const char* ALT_DMALL_GOLD_V_DRAMON_FQID = ALT_DMALL_GOLD_V_DRAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_GOLD_V_DRAMON_FQID_LEN = sizeof(ALT_DMALL_GOLD_V_DRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_GOLD_V_DRAMON_FQNAME_ARR[] = "dmall:Gold V-dramon";
    inline static constexpr const char* ALT_DMALL_GOLD_V_DRAMON_FQNAME = ALT_DMALL_GOLD_V_DRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_GOLD_V_DRAMON_FQNAME_LEN = sizeof(ALT_DMALL_GOLD_V_DRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_GOMAMON_FQID_ARR[] = "dmall:gomamon";
    inline static constexpr const char* ALT_DMALL_GOMAMON_FQID = ALT_DMALL_GOMAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_GOMAMON_FQID_LEN = sizeof(ALT_DMALL_GOMAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_GOMAMON_FQNAME_ARR[] = "dmall:Gomamon";
    inline static constexpr const char* ALT_DMALL_GOMAMON_FQNAME = ALT_DMALL_GOMAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_GOMAMON_FQNAME_LEN = sizeof(ALT_DMALL_GOMAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_GOMAMON_X_FQID_ARR[] = "dmall:gomamon_x";
    inline static constexpr const char* ALT_DMALL_GOMAMON_X_FQID = ALT_DMALL_GOMAMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_GOMAMON_X_FQID_LEN = sizeof(ALT_DMALL_GOMAMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_GOMAMON_X_FQNAME_ARR[] = "dmall:Gomamon X";
    inline static constexpr const char* ALT_DMALL_GOMAMON_X_FQNAME = ALT_DMALL_GOMAMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_GOMAMON_X_FQNAME_LEN = sizeof(ALT_DMALL_GOMAMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_GOROMON_FQID_ARR[] = "dmall:goromon";
    inline static constexpr const char* ALT_DMALL_GOROMON_FQID = ALT_DMALL_GOROMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_GOROMON_FQID_LEN = sizeof(ALT_DMALL_GOROMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_GOROMON_FQNAME_ARR[] = "dmall:Goromon";
    inline static constexpr const char* ALT_DMALL_GOROMON_FQNAME = ALT_DMALL_GOROMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_GOROMON_FQNAME_LEN = sizeof(ALT_DMALL_GOROMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_GOTSUMON_FQID_ARR[] = "dmall:gotsumon";
    inline static constexpr const char* ALT_DMALL_GOTSUMON_FQID = ALT_DMALL_GOTSUMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_GOTSUMON_FQID_LEN = sizeof(ALT_DMALL_GOTSUMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_GOTSUMON_FQNAME_ARR[] = "dmall:Gotsumon";
    inline static constexpr const char* ALT_DMALL_GOTSUMON_FQNAME = ALT_DMALL_GOTSUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_GOTSUMON_FQNAME_LEN = sizeof(ALT_DMALL_GOTSUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_GRACE_NOVAMON_FQID_ARR[] = "dmall:grace_novamon";
    inline static constexpr const char* ALT_DMALL_GRACE_NOVAMON_FQID = ALT_DMALL_GRACE_NOVAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_GRACE_NOVAMON_FQID_LEN = sizeof(ALT_DMALL_GRACE_NOVAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_GRACE_NOVAMON_FQNAME_ARR[] = "dmall:Grace Novamon";
    inline static constexpr const char* ALT_DMALL_GRACE_NOVAMON_FQNAME = ALT_DMALL_GRACE_NOVAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_GRACE_NOVAMON_FQNAME_LEN = sizeof(ALT_DMALL_GRACE_NOVAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_GRADEMON_FQID_ARR[] = "dmall:grademon";
    inline static constexpr const char* ALT_DMALL_GRADEMON_FQID = ALT_DMALL_GRADEMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_GRADEMON_FQID_LEN = sizeof(ALT_DMALL_GRADEMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_GRADEMON_FQNAME_ARR[] = "dmall:Grademon";
    inline static constexpr const char* ALT_DMALL_GRADEMON_FQNAME = ALT_DMALL_GRADEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_GRADEMON_FQNAME_LEN = sizeof(ALT_DMALL_GRADEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_GRAND_DRACUMON_FQID_ARR[] = "dmall:grand_dracumon";
    inline static constexpr const char* ALT_DMALL_GRAND_DRACUMON_FQID = ALT_DMALL_GRAND_DRACUMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_GRAND_DRACUMON_FQID_LEN = sizeof(ALT_DMALL_GRAND_DRACUMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_GRAND_DRACUMON_FQNAME_ARR[] = "dmall:Grand Dracumon";
    inline static constexpr const char* ALT_DMALL_GRAND_DRACUMON_FQNAME = ALT_DMALL_GRAND_DRACUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_GRAND_DRACUMON_FQNAME_LEN = sizeof(ALT_DMALL_GRAND_DRACUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_GRANDIS_KUWAGAMON_FQID_ARR[] = "dmall:grandis_kuwagamon";
    inline static constexpr const char* ALT_DMALL_GRANDIS_KUWAGAMON_FQID = ALT_DMALL_GRANDIS_KUWAGAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_GRANDIS_KUWAGAMON_FQID_LEN = sizeof(ALT_DMALL_GRANDIS_KUWAGAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_GRANDIS_KUWAGAMON_FQNAME_ARR[] = "dmall:Grandis Kuwagamon";
    inline static constexpr const char* ALT_DMALL_GRANDIS_KUWAGAMON_FQNAME = ALT_DMALL_GRANDIS_KUWAGAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_GRANDIS_KUWAGAMON_FQNAME_LEN = sizeof(ALT_DMALL_GRANDIS_KUWAGAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_GRAND_LOCOMON_FQID_ARR[] = "dmall:grand_locomon";
    inline static constexpr const char* ALT_DMALL_GRAND_LOCOMON_FQID = ALT_DMALL_GRAND_LOCOMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_GRAND_LOCOMON_FQID_LEN = sizeof(ALT_DMALL_GRAND_LOCOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_GRAND_LOCOMON_FQNAME_ARR[] = "dmall:Grand Locomon";
    inline static constexpr const char* ALT_DMALL_GRAND_LOCOMON_FQNAME = ALT_DMALL_GRAND_LOCOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_GRAND_LOCOMON_FQNAME_LEN = sizeof(ALT_DMALL_GRAND_LOCOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_GRAPPLEOMON_FQID_ARR[] = "dmall:grappleomon";
    inline static constexpr const char* ALT_DMALL_GRAPPLEOMON_FQID = ALT_DMALL_GRAPPLEOMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_GRAPPLEOMON_FQID_LEN = sizeof(ALT_DMALL_GRAPPLEOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_GRAPPLEOMON_FQNAME_ARR[] = "dmall:Grappleomon";
    inline static constexpr const char* ALT_DMALL_GRAPPLEOMON_FQNAME = ALT_DMALL_GRAPPLEOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_GRAPPLEOMON_FQNAME_LEN = sizeof(ALT_DMALL_GRAPPLEOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_GREAT_KING_SCUMON_FQID_ARR[] = "dmall:great_king_scumon";
    inline static constexpr const char* ALT_DMALL_GREAT_KING_SCUMON_FQID = ALT_DMALL_GREAT_KING_SCUMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_GREAT_KING_SCUMON_FQID_LEN = sizeof(ALT_DMALL_GREAT_KING_SCUMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_GREAT_KING_SCUMON_FQNAME_ARR[] = "dmall:Great King Scumon";
    inline static constexpr const char* ALT_DMALL_GREAT_KING_SCUMON_FQNAME = ALT_DMALL_GREAT_KING_SCUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_GREAT_KING_SCUMON_FQNAME_LEN = sizeof(ALT_DMALL_GREAT_KING_SCUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_GREYMON_2010_FQID_ARR[] = "dmall:greymon_2010";
    inline static constexpr const char* ALT_DMALL_GREYMON_2010_FQID = ALT_DMALL_GREYMON_2010_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_GREYMON_2010_FQID_LEN = sizeof(ALT_DMALL_GREYMON_2010_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_GREYMON_2010_FQNAME_ARR[] = "dmall:Greymon (2010)";
    inline static constexpr const char* ALT_DMALL_GREYMON_2010_FQNAME = ALT_DMALL_GREYMON_2010_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_GREYMON_2010_FQNAME_LEN = sizeof(ALT_DMALL_GREYMON_2010_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_GREYMON_BLUE_FQID_ARR[] = "dmall:greymon_blue";
    inline static constexpr const char* ALT_DMALL_GREYMON_BLUE_FQID = ALT_DMALL_GREYMON_BLUE_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_GREYMON_BLUE_FQID_LEN = sizeof(ALT_DMALL_GREYMON_BLUE_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_GREYMON_BLUE_FQNAME_ARR[] = "dmall:Greymon (Blue)";
    inline static constexpr const char* ALT_DMALL_GREYMON_BLUE_FQNAME = ALT_DMALL_GREYMON_BLUE_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_GREYMON_BLUE_FQNAME_LEN = sizeof(ALT_DMALL_GREYMON_BLUE_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_GREYMON_FQID_ARR[] = "dmall:greymon";
    inline static constexpr const char* ALT_DMALL_GREYMON_FQID = ALT_DMALL_GREYMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_GREYMON_FQID_LEN = sizeof(ALT_DMALL_GREYMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_GREYMON_FQNAME_ARR[] = "dmall:Greymon";
    inline static constexpr const char* ALT_DMALL_GREYMON_FQNAME = ALT_DMALL_GREYMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_GREYMON_FQNAME_LEN = sizeof(ALT_DMALL_GREYMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_GREYMON_X_FQID_ARR[] = "dmall:greymon_x";
    inline static constexpr const char* ALT_DMALL_GREYMON_X_FQID = ALT_DMALL_GREYMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_GREYMON_X_FQID_LEN = sizeof(ALT_DMALL_GREYMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_GREYMON_X_FQNAME_ARR[] = "dmall:Greymon X";
    inline static constexpr const char* ALT_DMALL_GREYMON_X_FQNAME = ALT_DMALL_GREYMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_GREYMON_X_FQNAME_LEN = sizeof(ALT_DMALL_GREYMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_GRIFFOMON_FQID_ARR[] = "dmall:griffomon";
    inline static constexpr const char* ALT_DMALL_GRIFFOMON_FQID = ALT_DMALL_GRIFFOMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_GRIFFOMON_FQID_LEN = sizeof(ALT_DMALL_GRIFFOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_GRIFFOMON_FQNAME_ARR[] = "dmall:Griffomon";
    inline static constexpr const char* ALT_DMALL_GRIFFOMON_FQNAME = ALT_DMALL_GRIFFOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_GRIFFOMON_FQNAME_LEN = sizeof(ALT_DMALL_GRIFFOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_GROWMON_ORANGE_FQID_ARR[] = "dmall:growmon_orange";
    inline static constexpr const char* ALT_DMALL_GROWMON_ORANGE_FQID = ALT_DMALL_GROWMON_ORANGE_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_GROWMON_ORANGE_FQID_LEN = sizeof(ALT_DMALL_GROWMON_ORANGE_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_GROWMON_ORANGE_FQNAME_ARR[] = "dmall:Growmon (Orange)";
    inline static constexpr const char* ALT_DMALL_GROWMON_ORANGE_FQNAME = ALT_DMALL_GROWMON_ORANGE_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_GROWMON_ORANGE_FQNAME_LEN = sizeof(ALT_DMALL_GROWMON_ORANGE_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_GROWMON_FQID_ARR[] = "dmall:growmon";
    inline static constexpr const char* ALT_DMALL_GROWMON_FQID = ALT_DMALL_GROWMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_GROWMON_FQID_LEN = sizeof(ALT_DMALL_GROWMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_GROWMON_FQNAME_ARR[] = "dmall:Growmon";
    inline static constexpr const char* ALT_DMALL_GROWMON_FQNAME = ALT_DMALL_GROWMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_GROWMON_FQNAME_LEN = sizeof(ALT_DMALL_GROWMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_GROWMON_X_FQID_ARR[] = "dmall:growmon_x";
    inline static constexpr const char* ALT_DMALL_GROWMON_X_FQID = ALT_DMALL_GROWMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_GROWMON_X_FQID_LEN = sizeof(ALT_DMALL_GROWMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_GROWMON_X_FQNAME_ARR[] = "dmall:Growmon X";
    inline static constexpr const char* ALT_DMALL_GROWMON_X_FQNAME = ALT_DMALL_GROWMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_GROWMON_X_FQNAME_LEN = sizeof(ALT_DMALL_GROWMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_GRYZMON_FQID_ARR[] = "dmall:gryzmon";
    inline static constexpr const char* ALT_DMALL_GRYZMON_FQID = ALT_DMALL_GRYZMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_GRYZMON_FQID_LEN = sizeof(ALT_DMALL_GRYZMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_GRYZMON_FQNAME_ARR[] = "dmall:Gryzmon";
    inline static constexpr const char* ALT_DMALL_GRYZMON_FQNAME = ALT_DMALL_GRYZMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_GRYZMON_FQNAME_LEN = sizeof(ALT_DMALL_GRYZMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_GUARDROMON_GOLD_FQID_ARR[] = "dmall:guardromon_gold";
    inline static constexpr const char* ALT_DMALL_GUARDROMON_GOLD_FQID = ALT_DMALL_GUARDROMON_GOLD_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_GUARDROMON_GOLD_FQID_LEN = sizeof(ALT_DMALL_GUARDROMON_GOLD_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_GUARDROMON_GOLD_FQNAME_ARR[] = "dmall:Guardromon (Gold)";
    inline static constexpr const char* ALT_DMALL_GUARDROMON_GOLD_FQNAME = ALT_DMALL_GUARDROMON_GOLD_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_GUARDROMON_GOLD_FQNAME_LEN = sizeof(ALT_DMALL_GUARDROMON_GOLD_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_GUARDROMON_FQID_ARR[] = "dmall:guardromon";
    inline static constexpr const char* ALT_DMALL_GUARDROMON_FQID = ALT_DMALL_GUARDROMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_GUARDROMON_FQID_LEN = sizeof(ALT_DMALL_GUARDROMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_GUARDROMON_FQNAME_ARR[] = "dmall:Guardromon";
    inline static constexpr const char* ALT_DMALL_GUARDROMON_FQNAME = ALT_DMALL_GUARDROMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_GUARDROMON_FQNAME_LEN = sizeof(ALT_DMALL_GUARDROMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_GUILMON_FQID_ARR[] = "dmall:guilmon";
    inline static constexpr const char* ALT_DMALL_GUILMON_FQID = ALT_DMALL_GUILMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_GUILMON_FQID_LEN = sizeof(ALT_DMALL_GUILMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_GUILMON_FQNAME_ARR[] = "dmall:Guilmon";
    inline static constexpr const char* ALT_DMALL_GUILMON_FQNAME = ALT_DMALL_GUILMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_GUILMON_FQNAME_LEN = sizeof(ALT_DMALL_GUILMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_GUILMON_X_FQID_ARR[] = "dmall:guilmon_x";
    inline static constexpr const char* ALT_DMALL_GUILMON_X_FQID = ALT_DMALL_GUILMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_GUILMON_X_FQID_LEN = sizeof(ALT_DMALL_GUILMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_GUILMON_X_FQNAME_ARR[] = "dmall:Guilmon X";
    inline static constexpr const char* ALT_DMALL_GUILMON_X_FQNAME = ALT_DMALL_GUILMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_GUILMON_X_FQNAME_LEN = sizeof(ALT_DMALL_GUILMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_GUMMYMON_FQID_ARR[] = "dmall:gummymon";
    inline static constexpr const char* ALT_DMALL_GUMMYMON_FQID = ALT_DMALL_GUMMYMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_GUMMYMON_FQID_LEN = sizeof(ALT_DMALL_GUMMYMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_GUMMYMON_FQNAME_ARR[] = "dmall:Gummymon";
    inline static constexpr const char* ALT_DMALL_GUMMYMON_FQNAME = ALT_DMALL_GUMMYMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_GUMMYMON_FQNAME_LEN = sizeof(ALT_DMALL_GUMMYMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_GUNDRAMON_FQID_ARR[] = "dmall:gundramon";
    inline static constexpr const char* ALT_DMALL_GUNDRAMON_FQID = ALT_DMALL_GUNDRAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_GUNDRAMON_FQID_LEN = sizeof(ALT_DMALL_GUNDRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_GUNDRAMON_FQNAME_ARR[] = "dmall:Gundramon";
    inline static constexpr const char* ALT_DMALL_GUNDRAMON_FQNAME = ALT_DMALL_GUNDRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_GUNDRAMON_FQNAME_LEN = sizeof(ALT_DMALL_GUNDRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_GURURUMON_FQID_ARR[] = "dmall:gururumon";
    inline static constexpr const char* ALT_DMALL_GURURUMON_FQID = ALT_DMALL_GURURUMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_GURURUMON_FQID_LEN = sizeof(ALT_DMALL_GURURUMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_GURURUMON_FQNAME_ARR[] = "dmall:Gururumon";
    inline static constexpr const char* ALT_DMALL_GURURUMON_FQNAME = ALT_DMALL_GURURUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_GURURUMON_FQNAME_LEN = sizeof(ALT_DMALL_GURURUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_GUSOKUMON_FQID_ARR[] = "dmall:gusokumon";
    inline static constexpr const char* ALT_DMALL_GUSOKUMON_FQID = ALT_DMALL_GUSOKUMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_GUSOKUMON_FQID_LEN = sizeof(ALT_DMALL_GUSOKUMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_GUSOKUMON_FQNAME_ARR[] = "dmall:Gusokumon";
    inline static constexpr const char* ALT_DMALL_GUSOKUMON_FQNAME = ALT_DMALL_GUSOKUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_GUSOKUMON_FQNAME_LEN = sizeof(ALT_DMALL_GUSOKUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_HACKMON_FQID_ARR[] = "dmall:hackmon";
    inline static constexpr const char* ALT_DMALL_HACKMON_FQID = ALT_DMALL_HACKMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_HACKMON_FQID_LEN = sizeof(ALT_DMALL_HACKMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_HACKMON_FQNAME_ARR[] = "dmall:Hackmon";
    inline static constexpr const char* ALT_DMALL_HACKMON_FQNAME = ALT_DMALL_HACKMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_HACKMON_FQNAME_LEN = sizeof(ALT_DMALL_HACKMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_HAGURUMON_FQID_ARR[] = "dmall:hagurumon";
    inline static constexpr const char* ALT_DMALL_HAGURUMON_FQID = ALT_DMALL_HAGURUMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_HAGURUMON_FQID_LEN = sizeof(ALT_DMALL_HAGURUMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_HAGURUMON_FQNAME_ARR[] = "dmall:Hagurumon";
    inline static constexpr const char* ALT_DMALL_HAGURUMON_FQNAME = ALT_DMALL_HAGURUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_HAGURUMON_FQNAME_LEN = sizeof(ALT_DMALL_HAGURUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_HANGYOMON_FQID_ARR[] = "dmall:hangyomon";
    inline static constexpr const char* ALT_DMALL_HANGYOMON_FQID = ALT_DMALL_HANGYOMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_HANGYOMON_FQID_LEN = sizeof(ALT_DMALL_HANGYOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_HANGYOMON_FQNAME_ARR[] = "dmall:Hangyomon";
    inline static constexpr const char* ALT_DMALL_HANGYOMON_FQNAME = ALT_DMALL_HANGYOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_HANGYOMON_FQNAME_LEN = sizeof(ALT_DMALL_HANGYOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_HANUMON_FQID_ARR[] = "dmall:hanumon";
    inline static constexpr const char* ALT_DMALL_HANUMON_FQID = ALT_DMALL_HANUMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_HANUMON_FQID_LEN = sizeof(ALT_DMALL_HANUMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_HANUMON_FQNAME_ARR[] = "dmall:Hanumon";
    inline static constexpr const char* ALT_DMALL_HANUMON_FQNAME = ALT_DMALL_HANUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_HANUMON_FQNAME_LEN = sizeof(ALT_DMALL_HANUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_HERAKLE_KABUTERIMON_FQID_ARR[] = "dmall:herakle_kabuterimon";
    inline static constexpr const char* ALT_DMALL_HERAKLE_KABUTERIMON_FQID = ALT_DMALL_HERAKLE_KABUTERIMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_HERAKLE_KABUTERIMON_FQID_LEN = sizeof(ALT_DMALL_HERAKLE_KABUTERIMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_HERAKLE_KABUTERIMON_FQNAME_ARR[] = "dmall:Herakle Kabuterimon";
    inline static constexpr const char* ALT_DMALL_HERAKLE_KABUTERIMON_FQNAME = ALT_DMALL_HERAKLE_KABUTERIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_HERAKLE_KABUTERIMON_FQNAME_LEN = sizeof(ALT_DMALL_HERAKLE_KABUTERIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_HERISSMON_FQID_ARR[] = "dmall:herissmon";
    inline static constexpr const char* ALT_DMALL_HERISSMON_FQID = ALT_DMALL_HERISSMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_HERISSMON_FQID_LEN = sizeof(ALT_DMALL_HERISSMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_HERISSMON_FQNAME_ARR[] = "dmall:Herissmon";
    inline static constexpr const char* ALT_DMALL_HERISSMON_FQNAME = ALT_DMALL_HERISSMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_HERISSMON_FQNAME_LEN = sizeof(ALT_DMALL_HERISSMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_HEXEBLAUMON_FQID_ARR[] = "dmall:hexeblaumon";
    inline static constexpr const char* ALT_DMALL_HEXEBLAUMON_FQID = ALT_DMALL_HEXEBLAUMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_HEXEBLAUMON_FQID_LEN = sizeof(ALT_DMALL_HEXEBLAUMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_HEXEBLAUMON_FQNAME_ARR[] = "dmall:Hexeblaumon";
    inline static constexpr const char* ALT_DMALL_HEXEBLAUMON_FQNAME = ALT_DMALL_HEXEBLAUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_HEXEBLAUMON_FQNAME_LEN = sizeof(ALT_DMALL_HEXEBLAUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_HI_ANDROMON_FQID_ARR[] = "dmall:hi_andromon";
    inline static constexpr const char* ALT_DMALL_HI_ANDROMON_FQID = ALT_DMALL_HI_ANDROMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_HI_ANDROMON_FQID_LEN = sizeof(ALT_DMALL_HI_ANDROMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_HI_ANDROMON_FQNAME_ARR[] = "dmall:Hi Andromon";
    inline static constexpr const char* ALT_DMALL_HI_ANDROMON_FQNAME = ALT_DMALL_HI_ANDROMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_HI_ANDROMON_FQNAME_LEN = sizeof(ALT_DMALL_HI_ANDROMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_HISYARYUMON_FQID_ARR[] = "dmall:hisyaryumon";
    inline static constexpr const char* ALT_DMALL_HISYARYUMON_FQID = ALT_DMALL_HISYARYUMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_HISYARYUMON_FQID_LEN = sizeof(ALT_DMALL_HISYARYUMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_HISYARYUMON_FQNAME_ARR[] = "dmall:Hisyaryumon";
    inline static constexpr const char* ALT_DMALL_HISYARYUMON_FQNAME = ALT_DMALL_HISYARYUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_HISYARYUMON_FQNAME_LEN = sizeof(ALT_DMALL_HISYARYUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_HIYARIMON_FQID_ARR[] = "dmall:hiyarimon";
    inline static constexpr const char* ALT_DMALL_HIYARIMON_FQID = ALT_DMALL_HIYARIMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_HIYARIMON_FQID_LEN = sizeof(ALT_DMALL_HIYARIMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_HIYARIMON_FQNAME_ARR[] = "dmall:Hiyarimon";
    inline static constexpr const char* ALT_DMALL_HIYARIMON_FQNAME = ALT_DMALL_HIYARIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_HIYARIMON_FQNAME_LEN = sizeof(ALT_DMALL_HIYARIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_HOLY_ANGEMON_FQID_ARR[] = "dmall:holy_angemon";
    inline static constexpr const char* ALT_DMALL_HOLY_ANGEMON_FQID = ALT_DMALL_HOLY_ANGEMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_HOLY_ANGEMON_FQID_LEN = sizeof(ALT_DMALL_HOLY_ANGEMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_HOLY_ANGEMON_FQNAME_ARR[] = "dmall:Holy Angemon";
    inline static constexpr const char* ALT_DMALL_HOLY_ANGEMON_FQNAME = ALT_DMALL_HOLY_ANGEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_HOLY_ANGEMON_FQNAME_LEN = sizeof(ALT_DMALL_HOLY_ANGEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_HOLY_DIGITAMAMON_FQID_ARR[] = "dmall:holy_digitamamon";
    inline static constexpr const char* ALT_DMALL_HOLY_DIGITAMAMON_FQID = ALT_DMALL_HOLY_DIGITAMAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_HOLY_DIGITAMAMON_FQID_LEN = sizeof(ALT_DMALL_HOLY_DIGITAMAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_HOLY_DIGITAMAMON_FQNAME_ARR[] = "dmall:Holy Digitamamon";
    inline static constexpr const char* ALT_DMALL_HOLY_DIGITAMAMON_FQNAME = ALT_DMALL_HOLY_DIGITAMAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_HOLY_DIGITAMAMON_FQNAME_LEN = sizeof(ALT_DMALL_HOLY_DIGITAMAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_HOLYDRAMON_FQID_ARR[] = "dmall:holydramon";
    inline static constexpr const char* ALT_DMALL_HOLYDRAMON_FQID = ALT_DMALL_HOLYDRAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_HOLYDRAMON_FQID_LEN = sizeof(ALT_DMALL_HOLYDRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_HOLYDRAMON_FQNAME_ARR[] = "dmall:Holydramon";
    inline static constexpr const char* ALT_DMALL_HOLYDRAMON_FQNAME = ALT_DMALL_HOLYDRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_HOLYDRAMON_FQNAME_LEN = sizeof(ALT_DMALL_HOLYDRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_HOLYDRAMON_X_FQID_ARR[] = "dmall:holydramon_x";
    inline static constexpr const char* ALT_DMALL_HOLYDRAMON_X_FQID = ALT_DMALL_HOLYDRAMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_HOLYDRAMON_X_FQID_LEN = sizeof(ALT_DMALL_HOLYDRAMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_HOLYDRAMON_X_FQNAME_ARR[] = "dmall:Holydramon X";
    inline static constexpr const char* ALT_DMALL_HOLYDRAMON_X_FQNAME = ALT_DMALL_HOLYDRAMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_HOLYDRAMON_X_FQNAME_LEN = sizeof(ALT_DMALL_HOLYDRAMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_HOOKMON_FQID_ARR[] = "dmall:hookmon";
    inline static constexpr const char* ALT_DMALL_HOOKMON_FQID = ALT_DMALL_HOOKMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_HOOKMON_FQID_LEN = sizeof(ALT_DMALL_HOOKMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_HOOKMON_FQNAME_ARR[] = "dmall:Hookmon";
    inline static constexpr const char* ALT_DMALL_HOOKMON_FQNAME = ALT_DMALL_HOOKMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_HOOKMON_FQNAME_LEN = sizeof(ALT_DMALL_HOOKMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_HOUOUMON_FQID_ARR[] = "dmall:hououmon";
    inline static constexpr const char* ALT_DMALL_HOUOUMON_FQID = ALT_DMALL_HOUOUMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_HOUOUMON_FQID_LEN = sizeof(ALT_DMALL_HOUOUMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_HOUOUMON_FQNAME_ARR[] = "dmall:Hououmon";
    inline static constexpr const char* ALT_DMALL_HOUOUMON_FQNAME = ALT_DMALL_HOUOUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_HOUOUMON_FQNAME_LEN = sizeof(ALT_DMALL_HOUOUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_HOUOUMON_X_FQID_ARR[] = "dmall:hououmon_x";
    inline static constexpr const char* ALT_DMALL_HOUOUMON_X_FQID = ALT_DMALL_HOUOUMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_HOUOUMON_X_FQID_LEN = sizeof(ALT_DMALL_HOUOUMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_HOUOUMON_X_FQNAME_ARR[] = "dmall:Hououmon X";
    inline static constexpr const char* ALT_DMALL_HOUOUMON_X_FQNAME = ALT_DMALL_HOUOUMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_HOUOUMON_X_FQNAME_LEN = sizeof(ALT_DMALL_HOUOUMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_HYOKOMON_FQID_ARR[] = "dmall:hyokomon";
    inline static constexpr const char* ALT_DMALL_HYOKOMON_FQID = ALT_DMALL_HYOKOMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_HYOKOMON_FQID_LEN = sizeof(ALT_DMALL_HYOKOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_HYOKOMON_FQNAME_ARR[] = "dmall:Hyokomon";
    inline static constexpr const char* ALT_DMALL_HYOKOMON_FQNAME = ALT_DMALL_HYOKOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_HYOKOMON_FQNAME_LEN = sizeof(ALT_DMALL_HYOKOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_HYOUGAMON_FQID_ARR[] = "dmall:hyougamon";
    inline static constexpr const char* ALT_DMALL_HYOUGAMON_FQID = ALT_DMALL_HYOUGAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_HYOUGAMON_FQID_LEN = sizeof(ALT_DMALL_HYOUGAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_HYOUGAMON_FQNAME_ARR[] = "dmall:Hyougamon";
    inline static constexpr const char* ALT_DMALL_HYOUGAMON_FQNAME = ALT_DMALL_HYOUGAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_HYOUGAMON_FQNAME_LEN = sizeof(ALT_DMALL_HYOUGAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_ICE_DEVIMON_FQID_ARR[] = "dmall:ice_devimon";
    inline static constexpr const char* ALT_DMALL_ICE_DEVIMON_FQID = ALT_DMALL_ICE_DEVIMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_ICE_DEVIMON_FQID_LEN = sizeof(ALT_DMALL_ICE_DEVIMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_ICE_DEVIMON_FQNAME_ARR[] = "dmall:Ice Devimon";
    inline static constexpr const char* ALT_DMALL_ICE_DEVIMON_FQNAME = ALT_DMALL_ICE_DEVIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_ICE_DEVIMON_FQNAME_LEN = sizeof(ALT_DMALL_ICE_DEVIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_ICEMON_FQID_ARR[] = "dmall:icemon";
    inline static constexpr const char* ALT_DMALL_ICEMON_FQID = ALT_DMALL_ICEMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_ICEMON_FQID_LEN = sizeof(ALT_DMALL_ICEMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_ICEMON_FQNAME_ARR[] = "dmall:Icemon";
    inline static constexpr const char* ALT_DMALL_ICEMON_FQNAME = ALT_DMALL_ICEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_ICEMON_FQNAME_LEN = sizeof(ALT_DMALL_ICEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_IGAMON_FQID_ARR[] = "dmall:igamon";
    inline static constexpr const char* ALT_DMALL_IGAMON_FQID = ALT_DMALL_IGAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_IGAMON_FQID_LEN = sizeof(ALT_DMALL_IGAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_IGAMON_FQNAME_ARR[] = "dmall:Igamon";
    inline static constexpr const char* ALT_DMALL_IGAMON_FQNAME = ALT_DMALL_IGAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_IGAMON_FQNAME_LEN = sizeof(ALT_DMALL_IGAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_IKKAKUMON_FQID_ARR[] = "dmall:ikkakumon";
    inline static constexpr const char* ALT_DMALL_IKKAKUMON_FQID = ALT_DMALL_IKKAKUMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_IKKAKUMON_FQID_LEN = sizeof(ALT_DMALL_IKKAKUMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_IKKAKUMON_FQNAME_ARR[] = "dmall:Ikkakumon";
    inline static constexpr const char* ALT_DMALL_IKKAKUMON_FQNAME = ALT_DMALL_IKKAKUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_IKKAKUMON_FQNAME_LEN = sizeof(ALT_DMALL_IKKAKUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_IMPERIALDRAMON_FIGHTER_MODE_BLACK_FQID_ARR[] = "dmall:imperialdramon_fighter_mode_black";
    inline static constexpr const char* ALT_DMALL_IMPERIALDRAMON_FIGHTER_MODE_BLACK_FQID = ALT_DMALL_IMPERIALDRAMON_FIGHTER_MODE_BLACK_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_IMPERIALDRAMON_FIGHTER_MODE_BLACK_FQID_LEN = sizeof(ALT_DMALL_IMPERIALDRAMON_FIGHTER_MODE_BLACK_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_IMPERIALDRAMON_FIGHTER_MODE_BLACK_FQNAME_ARR[] = "dmall:Imperialdramon Fighter Mode (Black)";
    inline static constexpr const char* ALT_DMALL_IMPERIALDRAMON_FIGHTER_MODE_BLACK_FQNAME = ALT_DMALL_IMPERIALDRAMON_FIGHTER_MODE_BLACK_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_IMPERIALDRAMON_FIGHTER_MODE_BLACK_FQNAME_LEN = sizeof(ALT_DMALL_IMPERIALDRAMON_FIGHTER_MODE_BLACK_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_IMPERIALDRAMON_FIGHTER_MODE_FQID_ARR[] = "dmall:imperialdramon_fighter_mode";
    inline static constexpr const char* ALT_DMALL_IMPERIALDRAMON_FIGHTER_MODE_FQID = ALT_DMALL_IMPERIALDRAMON_FIGHTER_MODE_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_IMPERIALDRAMON_FIGHTER_MODE_FQID_LEN = sizeof(ALT_DMALL_IMPERIALDRAMON_FIGHTER_MODE_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_IMPERIALDRAMON_FIGHTER_MODE_FQNAME_ARR[] = "dmall:Imperialdramon Fighter Mode";
    inline static constexpr const char* ALT_DMALL_IMPERIALDRAMON_FIGHTER_MODE_FQNAME = ALT_DMALL_IMPERIALDRAMON_FIGHTER_MODE_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_IMPERIALDRAMON_FIGHTER_MODE_FQNAME_LEN = sizeof(ALT_DMALL_IMPERIALDRAMON_FIGHTER_MODE_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_IMPERIALDRAMON_PALADIN_MODE_FQID_ARR[] = "dmall:imperialdramon_paladin_mode";
    inline static constexpr const char* ALT_DMALL_IMPERIALDRAMON_PALADIN_MODE_FQID = ALT_DMALL_IMPERIALDRAMON_PALADIN_MODE_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_IMPERIALDRAMON_PALADIN_MODE_FQID_LEN = sizeof(ALT_DMALL_IMPERIALDRAMON_PALADIN_MODE_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_IMPERIALDRAMON_PALADIN_MODE_FQNAME_ARR[] = "dmall:Imperialdramon Paladin Mode";
    inline static constexpr const char* ALT_DMALL_IMPERIALDRAMON_PALADIN_MODE_FQNAME = ALT_DMALL_IMPERIALDRAMON_PALADIN_MODE_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_IMPERIALDRAMON_PALADIN_MODE_FQNAME_LEN = sizeof(ALT_DMALL_IMPERIALDRAMON_PALADIN_MODE_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_IMPMON_FQID_ARR[] = "dmall:impmon";
    inline static constexpr const char* ALT_DMALL_IMPMON_FQID = ALT_DMALL_IMPMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_IMPMON_FQID_LEN = sizeof(ALT_DMALL_IMPMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_IMPMON_FQNAME_ARR[] = "dmall:Impmon";
    inline static constexpr const char* ALT_DMALL_IMPMON_FQNAME = ALT_DMALL_IMPMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_IMPMON_FQNAME_LEN = sizeof(ALT_DMALL_IMPMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_IMPMON_X_FQID_ARR[] = "dmall:impmon_x";
    inline static constexpr const char* ALT_DMALL_IMPMON_X_FQID = ALT_DMALL_IMPMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_IMPMON_X_FQID_LEN = sizeof(ALT_DMALL_IMPMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_IMPMON_X_FQNAME_ARR[] = "dmall:Impmon X";
    inline static constexpr const char* ALT_DMALL_IMPMON_X_FQNAME = ALT_DMALL_IMPMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_IMPMON_X_FQNAME_LEN = sizeof(ALT_DMALL_IMPMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_INSEKIMON_FQID_ARR[] = "dmall:insekimon";
    inline static constexpr const char* ALT_DMALL_INSEKIMON_FQID = ALT_DMALL_INSEKIMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_INSEKIMON_FQID_LEN = sizeof(ALT_DMALL_INSEKIMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_INSEKIMON_FQNAME_ARR[] = "dmall:Insekimon";
    inline static constexpr const char* ALT_DMALL_INSEKIMON_FQNAME = ALT_DMALL_INSEKIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_INSEKIMON_FQNAME_LEN = sizeof(ALT_DMALL_INSEKIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_JAZAMON_FQID_ARR[] = "dmall:jazamon";
    inline static constexpr const char* ALT_DMALL_JAZAMON_FQID = ALT_DMALL_JAZAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_JAZAMON_FQID_LEN = sizeof(ALT_DMALL_JAZAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_JAZAMON_FQNAME_ARR[] = "dmall:Jazamon";
    inline static constexpr const char* ALT_DMALL_JAZAMON_FQNAME = ALT_DMALL_JAZAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_JAZAMON_FQNAME_LEN = sizeof(ALT_DMALL_JAZAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_JAZARDMON_FQID_ARR[] = "dmall:jazardmon";
    inline static constexpr const char* ALT_DMALL_JAZARDMON_FQID = ALT_DMALL_JAZARDMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_JAZARDMON_FQID_LEN = sizeof(ALT_DMALL_JAZARDMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_JAZARDMON_FQNAME_ARR[] = "dmall:Jazardmon";
    inline static constexpr const char* ALT_DMALL_JAZARDMON_FQNAME = ALT_DMALL_JAZARDMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_JAZARDMON_FQNAME_LEN = sizeof(ALT_DMALL_JAZARDMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_JAZARICHMON_FQID_ARR[] = "dmall:jazarichmon";
    inline static constexpr const char* ALT_DMALL_JAZARICHMON_FQID = ALT_DMALL_JAZARICHMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_JAZARICHMON_FQID_LEN = sizeof(ALT_DMALL_JAZARICHMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_JAZARICHMON_FQNAME_ARR[] = "dmall:Jazarichmon";
    inline static constexpr const char* ALT_DMALL_JAZARICHMON_FQNAME = ALT_DMALL_JAZARICHMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_JAZARICHMON_FQNAME_LEN = sizeof(ALT_DMALL_JAZARICHMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_JESMON_GX_FQID_ARR[] = "dmall:jesmon_gx";
    inline static constexpr const char* ALT_DMALL_JESMON_GX_FQID = ALT_DMALL_JESMON_GX_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_JESMON_GX_FQID_LEN = sizeof(ALT_DMALL_JESMON_GX_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_JESMON_GX_FQNAME_ARR[] = "dmall:Jesmon GX";
    inline static constexpr const char* ALT_DMALL_JESMON_GX_FQNAME = ALT_DMALL_JESMON_GX_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_JESMON_GX_FQNAME_LEN = sizeof(ALT_DMALL_JESMON_GX_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_JESMON_FQID_ARR[] = "dmall:jesmon";
    inline static constexpr const char* ALT_DMALL_JESMON_FQID = ALT_DMALL_JESMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_JESMON_FQID_LEN = sizeof(ALT_DMALL_JESMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_JESMON_FQNAME_ARR[] = "dmall:Jesmon";
    inline static constexpr const char* ALT_DMALL_JESMON_FQNAME = ALT_DMALL_JESMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_JESMON_FQNAME_LEN = sizeof(ALT_DMALL_JESMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_JESMON_X_FQID_ARR[] = "dmall:jesmon_x";
    inline static constexpr const char* ALT_DMALL_JESMON_X_FQID = ALT_DMALL_JESMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_JESMON_X_FQID_LEN = sizeof(ALT_DMALL_JESMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_JESMON_X_FQNAME_ARR[] = "dmall:Jesmon X";
    inline static constexpr const char* ALT_DMALL_JESMON_X_FQNAME = ALT_DMALL_JESMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_JESMON_X_FQNAME_LEN = sizeof(ALT_DMALL_JESMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_JUNKMON_FQID_ARR[] = "dmall:junkmon";
    inline static constexpr const char* ALT_DMALL_JUNKMON_FQID = ALT_DMALL_JUNKMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_JUNKMON_FQID_LEN = sizeof(ALT_DMALL_JUNKMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_JUNKMON_FQNAME_ARR[] = "dmall:Junkmon";
    inline static constexpr const char* ALT_DMALL_JUNKMON_FQNAME = ALT_DMALL_JUNKMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_JUNKMON_FQNAME_LEN = sizeof(ALT_DMALL_JUNKMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_JUSTIMON_X_FQID_ARR[] = "dmall:justimon_x";
    inline static constexpr const char* ALT_DMALL_JUSTIMON_X_FQID = ALT_DMALL_JUSTIMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_JUSTIMON_X_FQID_LEN = sizeof(ALT_DMALL_JUSTIMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_JUSTIMON_X_FQNAME_ARR[] = "dmall:Justimon X";
    inline static constexpr const char* ALT_DMALL_JUSTIMON_X_FQNAME = ALT_DMALL_JUSTIMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_JUSTIMON_X_FQNAME_LEN = sizeof(ALT_DMALL_JUSTIMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_JYAGAMON_FQID_ARR[] = "dmall:jyagamon";
    inline static constexpr const char* ALT_DMALL_JYAGAMON_FQID = ALT_DMALL_JYAGAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_JYAGAMON_FQID_LEN = sizeof(ALT_DMALL_JYAGAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_JYAGAMON_FQNAME_ARR[] = "dmall:Jyagamon";
    inline static constexpr const char* ALT_DMALL_JYAGAMON_FQNAME = ALT_DMALL_JYAGAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_JYAGAMON_FQNAME_LEN = sizeof(ALT_DMALL_JYAGAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_JYARIMON_FQID_ARR[] = "dmall:jyarimon";
    inline static constexpr const char* ALT_DMALL_JYARIMON_FQID = ALT_DMALL_JYARIMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_JYARIMON_FQID_LEN = sizeof(ALT_DMALL_JYARIMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_JYARIMON_FQNAME_ARR[] = "dmall:Jyarimon";
    inline static constexpr const char* ALT_DMALL_JYARIMON_FQNAME = ALT_DMALL_JYARIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_JYARIMON_FQNAME_LEN = sizeof(ALT_DMALL_JYARIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_JYUREIMON_FQID_ARR[] = "dmall:jyureimon";
    inline static constexpr const char* ALT_DMALL_JYUREIMON_FQID = ALT_DMALL_JYUREIMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_JYUREIMON_FQID_LEN = sizeof(ALT_DMALL_JYUREIMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_JYUREIMON_FQNAME_ARR[] = "dmall:Jyureimon";
    inline static constexpr const char* ALT_DMALL_JYUREIMON_FQNAME = ALT_DMALL_JYUREIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_JYUREIMON_FQNAME_LEN = sizeof(ALT_DMALL_JYUREIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_KABUTERIMON_FQID_ARR[] = "dmall:kabuterimon";
    inline static constexpr const char* ALT_DMALL_KABUTERIMON_FQID = ALT_DMALL_KABUTERIMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_KABUTERIMON_FQID_LEN = sizeof(ALT_DMALL_KABUTERIMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_KABUTERIMON_FQNAME_ARR[] = "dmall:Kabuterimon";
    inline static constexpr const char* ALT_DMALL_KABUTERIMON_FQNAME = ALT_DMALL_KABUTERIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_KABUTERIMON_FQNAME_LEN = sizeof(ALT_DMALL_KABUTERIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_KAISER_GREYMON_FQID_ARR[] = "dmall:kaiser_greymon";
    inline static constexpr const char* ALT_DMALL_KAISER_GREYMON_FQID = ALT_DMALL_KAISER_GREYMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_KAISER_GREYMON_FQID_LEN = sizeof(ALT_DMALL_KAISER_GREYMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_KAISER_GREYMON_FQNAME_ARR[] = "dmall:Kaiser Greymon";
    inline static constexpr const char* ALT_DMALL_KAISER_GREYMON_FQNAME = ALT_DMALL_KAISER_GREYMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_KAISER_GREYMON_FQNAME_LEN = sizeof(ALT_DMALL_KAISER_GREYMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_KAISER_LEOMON_FQID_ARR[] = "dmall:kaiser_leomon";
    inline static constexpr const char* ALT_DMALL_KAISER_LEOMON_FQID = ALT_DMALL_KAISER_LEOMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_KAISER_LEOMON_FQID_LEN = sizeof(ALT_DMALL_KAISER_LEOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_KAISER_LEOMON_FQNAME_ARR[] = "dmall:Kaiser Leomon";
    inline static constexpr const char* ALT_DMALL_KAISER_LEOMON_FQNAME = ALT_DMALL_KAISER_LEOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_KAISER_LEOMON_FQNAME_LEN = sizeof(ALT_DMALL_KAISER_LEOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_KAKKINMON_FQID_ARR[] = "dmall:kakkinmon";
    inline static constexpr const char* ALT_DMALL_KAKKINMON_FQID = ALT_DMALL_KAKKINMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_KAKKINMON_FQID_LEN = sizeof(ALT_DMALL_KAKKINMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_KAKKINMON_FQNAME_ARR[] = "dmall:Kakkinmon";
    inline static constexpr const char* ALT_DMALL_KAKKINMON_FQNAME = ALT_DMALL_KAKKINMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_KAKKINMON_FQNAME_LEN = sizeof(ALT_DMALL_KAKKINMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_KARATSUKI_NUMEMON_FQID_ARR[] = "dmall:karatsuki_numemon";
    inline static constexpr const char* ALT_DMALL_KARATSUKI_NUMEMON_FQID = ALT_DMALL_KARATSUKI_NUMEMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_KARATSUKI_NUMEMON_FQID_LEN = sizeof(ALT_DMALL_KARATSUKI_NUMEMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_KARATSUKI_NUMEMON_FQNAME_ARR[] = "dmall:Karatsuki Numemon";
    inline static constexpr const char* ALT_DMALL_KARATSUKI_NUMEMON_FQNAME = ALT_DMALL_KARATSUKI_NUMEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_KARATSUKI_NUMEMON_FQNAME_LEN = sizeof(ALT_DMALL_KARATSUKI_NUMEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_KAZUCHIMON_FQID_ARR[] = "dmall:kazuchimon";
    inline static constexpr const char* ALT_DMALL_KAZUCHIMON_FQID = ALT_DMALL_KAZUCHIMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_KAZUCHIMON_FQID_LEN = sizeof(ALT_DMALL_KAZUCHIMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_KAZUCHIMON_FQNAME_ARR[] = "dmall:Kazuchimon";
    inline static constexpr const char* ALT_DMALL_KAZUCHIMON_FQNAME = ALT_DMALL_KAZUCHIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_KAZUCHIMON_FQNAME_LEN = sizeof(ALT_DMALL_KAZUCHIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_KERAMON_FQID_ARR[] = "dmall:keramon";
    inline static constexpr const char* ALT_DMALL_KERAMON_FQID = ALT_DMALL_KERAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_KERAMON_FQID_LEN = sizeof(ALT_DMALL_KERAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_KERAMON_FQNAME_ARR[] = "dmall:Keramon";
    inline static constexpr const char* ALT_DMALL_KERAMON_FQNAME = ALT_DMALL_KERAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_KERAMON_FQNAME_LEN = sizeof(ALT_DMALL_KERAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_KERAMON_X_FQID_ARR[] = "dmall:keramon_x";
    inline static constexpr const char* ALT_DMALL_KERAMON_X_FQID = ALT_DMALL_KERAMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_KERAMON_X_FQID_LEN = sizeof(ALT_DMALL_KERAMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_KERAMON_X_FQNAME_ARR[] = "dmall:Keramon X";
    inline static constexpr const char* ALT_DMALL_KERAMON_X_FQNAME = ALT_DMALL_KERAMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_KERAMON_X_FQNAME_LEN = sizeof(ALT_DMALL_KERAMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_KETOMON_FQID_ARR[] = "dmall:ketomon";
    inline static constexpr const char* ALT_DMALL_KETOMON_FQID = ALT_DMALL_KETOMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_KETOMON_FQID_LEN = sizeof(ALT_DMALL_KETOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_KETOMON_FQNAME_ARR[] = "dmall:Ketomon";
    inline static constexpr const char* ALT_DMALL_KETOMON_FQNAME = ALT_DMALL_KETOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_KETOMON_FQNAME_LEN = sizeof(ALT_DMALL_KETOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_KIIMON_FQID_ARR[] = "dmall:kiimon";
    inline static constexpr const char* ALT_DMALL_KIIMON_FQID = ALT_DMALL_KIIMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_KIIMON_FQID_LEN = sizeof(ALT_DMALL_KIIMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_KIIMON_FQNAME_ARR[] = "dmall:Kiimon";
    inline static constexpr const char* ALT_DMALL_KIIMON_FQNAME = ALT_DMALL_KIIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_KIIMON_FQNAME_LEN = sizeof(ALT_DMALL_KIIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_KING_ETEMON_FQID_ARR[] = "dmall:king_etemon";
    inline static constexpr const char* ALT_DMALL_KING_ETEMON_FQID = ALT_DMALL_KING_ETEMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_KING_ETEMON_FQID_LEN = sizeof(ALT_DMALL_KING_ETEMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_KING_ETEMON_FQNAME_ARR[] = "dmall:King Etemon";
    inline static constexpr const char* ALT_DMALL_KING_ETEMON_FQNAME = ALT_DMALL_KING_ETEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_KING_ETEMON_FQNAME_LEN = sizeof(ALT_DMALL_KING_ETEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_KIWIMON_FQID_ARR[] = "dmall:kiwimon";
    inline static constexpr const char* ALT_DMALL_KIWIMON_FQID = ALT_DMALL_KIWIMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_KIWIMON_FQID_LEN = sizeof(ALT_DMALL_KIWIMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_KIWIMON_FQNAME_ARR[] = "dmall:Kiwimon";
    inline static constexpr const char* ALT_DMALL_KIWIMON_FQNAME = ALT_DMALL_KIWIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_KIWIMON_FQNAME_LEN = sizeof(ALT_DMALL_KIWIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_KNIGHTMON_FQID_ARR[] = "dmall:knightmon";
    inline static constexpr const char* ALT_DMALL_KNIGHTMON_FQID = ALT_DMALL_KNIGHTMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_KNIGHTMON_FQID_LEN = sizeof(ALT_DMALL_KNIGHTMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_KNIGHTMON_FQNAME_ARR[] = "dmall:Knightmon";
    inline static constexpr const char* ALT_DMALL_KNIGHTMON_FQNAME = ALT_DMALL_KNIGHTMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_KNIGHTMON_FQNAME_LEN = sizeof(ALT_DMALL_KNIGHTMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_KOEMON_FQID_ARR[] = "dmall:koemon";
    inline static constexpr const char* ALT_DMALL_KOEMON_FQID = ALT_DMALL_KOEMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_KOEMON_FQID_LEN = sizeof(ALT_DMALL_KOEMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_KOEMON_FQNAME_ARR[] = "dmall:Koemon";
    inline static constexpr const char* ALT_DMALL_KOEMON_FQNAME = ALT_DMALL_KOEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_KOEMON_FQNAME_LEN = sizeof(ALT_DMALL_KOEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_KOKABUTERIMON_FQID_ARR[] = "dmall:kokabuterimon";
    inline static constexpr const char* ALT_DMALL_KOKABUTERIMON_FQID = ALT_DMALL_KOKABUTERIMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_KOKABUTERIMON_FQID_LEN = sizeof(ALT_DMALL_KOKABUTERIMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_KOKABUTERIMON_FQNAME_ARR[] = "dmall:Kokabuterimon";
    inline static constexpr const char* ALT_DMALL_KOKABUTERIMON_FQNAME = ALT_DMALL_KOKABUTERIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_KOKABUTERIMON_FQNAME_LEN = sizeof(ALT_DMALL_KOKABUTERIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_KOKUWAMON_FQID_ARR[] = "dmall:kokuwamon";
    inline static constexpr const char* ALT_DMALL_KOKUWAMON_FQID = ALT_DMALL_KOKUWAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_KOKUWAMON_FQID_LEN = sizeof(ALT_DMALL_KOKUWAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_KOKUWAMON_FQNAME_ARR[] = "dmall:Kokuwamon";
    inline static constexpr const char* ALT_DMALL_KOKUWAMON_FQNAME = ALT_DMALL_KOKUWAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_KOKUWAMON_FQNAME_LEN = sizeof(ALT_DMALL_KOKUWAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_KOKUWAMON_X_FQID_ARR[] = "dmall:kokuwamon_x";
    inline static constexpr const char* ALT_DMALL_KOKUWAMON_X_FQID = ALT_DMALL_KOKUWAMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_KOKUWAMON_X_FQID_LEN = sizeof(ALT_DMALL_KOKUWAMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_KOKUWAMON_X_FQNAME_ARR[] = "dmall:Kokuwamon X";
    inline static constexpr const char* ALT_DMALL_KOKUWAMON_X_FQNAME = ALT_DMALL_KOKUWAMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_KOKUWAMON_X_FQNAME_LEN = sizeof(ALT_DMALL_KOKUWAMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_KOROMON_FQID_ARR[] = "dmall:koromon";
    inline static constexpr const char* ALT_DMALL_KOROMON_FQID = ALT_DMALL_KOROMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_KOROMON_FQID_LEN = sizeof(ALT_DMALL_KOROMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_KOROMON_FQNAME_ARR[] = "dmall:Koromon";
    inline static constexpr const char* ALT_DMALL_KOROMON_FQNAME = ALT_DMALL_KOROMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_KOROMON_FQNAME_LEN = sizeof(ALT_DMALL_KOROMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_KOUGAMON_FQID_ARR[] = "dmall:kougamon";
    inline static constexpr const char* ALT_DMALL_KOUGAMON_FQID = ALT_DMALL_KOUGAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_KOUGAMON_FQID_LEN = sizeof(ALT_DMALL_KOUGAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_KOUGAMON_FQNAME_ARR[] = "dmall:Kougamon";
    inline static constexpr const char* ALT_DMALL_KOUGAMON_FQNAME = ALT_DMALL_KOUGAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_KOUGAMON_FQNAME_LEN = sizeof(ALT_DMALL_KOUGAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_KOZENIMON_FQID_ARR[] = "dmall:kozenimon";
    inline static constexpr const char* ALT_DMALL_KOZENIMON_FQID = ALT_DMALL_KOZENIMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_KOZENIMON_FQID_LEN = sizeof(ALT_DMALL_KOZENIMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_KOZENIMON_FQNAME_ARR[] = "dmall:Kozenimon";
    inline static constexpr const char* ALT_DMALL_KOZENIMON_FQNAME = ALT_DMALL_KOZENIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_KOZENIMON_FQNAME_LEN = sizeof(ALT_DMALL_KOZENIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_KUNEMON_FQID_ARR[] = "dmall:kunemon";
    inline static constexpr const char* ALT_DMALL_KUNEMON_FQID = ALT_DMALL_KUNEMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_KUNEMON_FQID_LEN = sizeof(ALT_DMALL_KUNEMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_KUNEMON_FQNAME_ARR[] = "dmall:Kunemon";
    inline static constexpr const char* ALT_DMALL_KUNEMON_FQNAME = ALT_DMALL_KUNEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_KUNEMON_FQNAME_LEN = sizeof(ALT_DMALL_KUNEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_KURAMON_FQID_ARR[] = "dmall:kuramon";
    inline static constexpr const char* ALT_DMALL_KURAMON_FQID = ALT_DMALL_KURAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_KURAMON_FQID_LEN = sizeof(ALT_DMALL_KURAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_KURAMON_FQNAME_ARR[] = "dmall:Kuramon";
    inline static constexpr const char* ALT_DMALL_KURAMON_FQNAME = ALT_DMALL_KURAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_KURAMON_FQNAME_LEN = sizeof(ALT_DMALL_KURAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_KUWAGAMON_FQID_ARR[] = "dmall:kuwagamon";
    inline static constexpr const char* ALT_DMALL_KUWAGAMON_FQID = ALT_DMALL_KUWAGAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_KUWAGAMON_FQID_LEN = sizeof(ALT_DMALL_KUWAGAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_KUWAGAMON_FQNAME_ARR[] = "dmall:Kuwagamon";
    inline static constexpr const char* ALT_DMALL_KUWAGAMON_FQNAME = ALT_DMALL_KUWAGAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_KUWAGAMON_FQNAME_LEN = sizeof(ALT_DMALL_KUWAGAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_KUWAGAMON_X_FQID_ARR[] = "dmall:kuwagamon_x";
    inline static constexpr const char* ALT_DMALL_KUWAGAMON_X_FQID = ALT_DMALL_KUWAGAMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_KUWAGAMON_X_FQID_LEN = sizeof(ALT_DMALL_KUWAGAMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_KUWAGAMON_X_FQNAME_ARR[] = "dmall:Kuwagamon X";
    inline static constexpr const char* ALT_DMALL_KUWAGAMON_X_FQNAME = ALT_DMALL_KUWAGAMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_KUWAGAMON_X_FQNAME_LEN = sizeof(ALT_DMALL_KUWAGAMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_KUZUHAMON_FQID_ARR[] = "dmall:kuzuhamon";
    inline static constexpr const char* ALT_DMALL_KUZUHAMON_FQID = ALT_DMALL_KUZUHAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_KUZUHAMON_FQID_LEN = sizeof(ALT_DMALL_KUZUHAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_KUZUHAMON_FQNAME_ARR[] = "dmall:Kuzuhamon";
    inline static constexpr const char* ALT_DMALL_KUZUHAMON_FQNAME = ALT_DMALL_KUZUHAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_KUZUHAMON_FQNAME_LEN = sizeof(ALT_DMALL_KUZUHAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_KYOKYOMON_FQID_ARR[] = "dmall:kyokyomon";
    inline static constexpr const char* ALT_DMALL_KYOKYOMON_FQID = ALT_DMALL_KYOKYOMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_KYOKYOMON_FQID_LEN = sizeof(ALT_DMALL_KYOKYOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_KYOKYOMON_FQNAME_ARR[] = "dmall:Kyokyomon";
    inline static constexpr const char* ALT_DMALL_KYOKYOMON_FQNAME = ALT_DMALL_KYOKYOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_KYOKYOMON_FQNAME_LEN = sizeof(ALT_DMALL_KYOKYOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_KYUBIMON_FQID_ARR[] = "dmall:kyubimon";
    inline static constexpr const char* ALT_DMALL_KYUBIMON_FQID = ALT_DMALL_KYUBIMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_KYUBIMON_FQID_LEN = sizeof(ALT_DMALL_KYUBIMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_KYUBIMON_FQNAME_ARR[] = "dmall:Kyubimon";
    inline static constexpr const char* ALT_DMALL_KYUBIMON_FQNAME = ALT_DMALL_KYUBIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_KYUBIMON_FQNAME_LEN = sizeof(ALT_DMALL_KYUBIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_KYUBIMON_SILVER_FQID_ARR[] = "dmall:kyubimon_silver";
    inline static constexpr const char* ALT_DMALL_KYUBIMON_SILVER_FQID = ALT_DMALL_KYUBIMON_SILVER_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_KYUBIMON_SILVER_FQID_LEN = sizeof(ALT_DMALL_KYUBIMON_SILVER_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_KYUBIMON_SILVER_FQNAME_ARR[] = "dmall:Kyubimon (Silver)";
    inline static constexpr const char* ALT_DMALL_KYUBIMON_SILVER_FQNAME = ALT_DMALL_KYUBIMON_SILVER_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_KYUBIMON_SILVER_FQNAME_LEN = sizeof(ALT_DMALL_KYUBIMON_SILVER_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_LABRAMON_FQID_ARR[] = "dmall:labramon";
    inline static constexpr const char* ALT_DMALL_LABRAMON_FQID = ALT_DMALL_LABRAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_LABRAMON_FQID_LEN = sizeof(ALT_DMALL_LABRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_LABRAMON_FQNAME_ARR[] = "dmall:Labramon";
    inline static constexpr const char* ALT_DMALL_LABRAMON_FQNAME = ALT_DMALL_LABRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_LABRAMON_FQNAME_LEN = sizeof(ALT_DMALL_LABRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_LADYDEVIMON_FQID_ARR[] = "dmall:ladydevimon";
    inline static constexpr const char* ALT_DMALL_LADYDEVIMON_FQID = ALT_DMALL_LADYDEVIMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_LADYDEVIMON_FQID_LEN = sizeof(ALT_DMALL_LADYDEVIMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_LADYDEVIMON_FQNAME_ARR[] = "dmall:LadyDevimon";
    inline static constexpr const char* ALT_DMALL_LADYDEVIMON_FQNAME = ALT_DMALL_LADYDEVIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_LADYDEVIMON_FQNAME_LEN = sizeof(ALT_DMALL_LADYDEVIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_LADYDEVIMON_X_FQID_ARR[] = "dmall:ladydevimon_x";
    inline static constexpr const char* ALT_DMALL_LADYDEVIMON_X_FQID = ALT_DMALL_LADYDEVIMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_LADYDEVIMON_X_FQID_LEN = sizeof(ALT_DMALL_LADYDEVIMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_LADYDEVIMON_X_FQNAME_ARR[] = "dmall:LadyDevimon X";
    inline static constexpr const char* ALT_DMALL_LADYDEVIMON_X_FQNAME = ALT_DMALL_LADYDEVIMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_LADYDEVIMON_X_FQNAME_LEN = sizeof(ALT_DMALL_LADYDEVIMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_LALAMON_FQID_ARR[] = "dmall:lalamon";
    inline static constexpr const char* ALT_DMALL_LALAMON_FQID = ALT_DMALL_LALAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_LALAMON_FQID_LEN = sizeof(ALT_DMALL_LALAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_LALAMON_FQNAME_ARR[] = "dmall:Lalamon";
    inline static constexpr const char* ALT_DMALL_LALAMON_FQNAME = ALT_DMALL_LALAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_LALAMON_FQNAME_LEN = sizeof(ALT_DMALL_LALAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_LAVOGARITAMON_FQID_ARR[] = "dmall:lavogaritamon";
    inline static constexpr const char* ALT_DMALL_LAVOGARITAMON_FQID = ALT_DMALL_LAVOGARITAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_LAVOGARITAMON_FQID_LEN = sizeof(ALT_DMALL_LAVOGARITAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_LAVOGARITAMON_FQNAME_ARR[] = "dmall:Lavogaritamon";
    inline static constexpr const char* ALT_DMALL_LAVOGARITAMON_FQNAME = ALT_DMALL_LAVOGARITAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_LAVOGARITAMON_FQNAME_LEN = sizeof(ALT_DMALL_LAVOGARITAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_LAVORVOMON_FQID_ARR[] = "dmall:lavorvomon";
    inline static constexpr const char* ALT_DMALL_LAVORVOMON_FQID = ALT_DMALL_LAVORVOMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_LAVORVOMON_FQID_LEN = sizeof(ALT_DMALL_LAVORVOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_LAVORVOMON_FQNAME_ARR[] = "dmall:Lavorvomon";
    inline static constexpr const char* ALT_DMALL_LAVORVOMON_FQNAME = ALT_DMALL_LAVORVOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_LAVORVOMON_FQNAME_LEN = sizeof(ALT_DMALL_LAVORVOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_LEAFMON_FQID_ARR[] = "dmall:leafmon";
    inline static constexpr const char* ALT_DMALL_LEAFMON_FQID = ALT_DMALL_LEAFMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_LEAFMON_FQID_LEN = sizeof(ALT_DMALL_LEAFMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_LEAFMON_FQNAME_ARR[] = "dmall:Leafmon";
    inline static constexpr const char* ALT_DMALL_LEAFMON_FQNAME = ALT_DMALL_LEAFMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_LEAFMON_FQNAME_LEN = sizeof(ALT_DMALL_LEAFMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_LEKISMON_FQID_ARR[] = "dmall:lekismon";
    inline static constexpr const char* ALT_DMALL_LEKISMON_FQID = ALT_DMALL_LEKISMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_LEKISMON_FQID_LEN = sizeof(ALT_DMALL_LEKISMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_LEKISMON_FQNAME_ARR[] = "dmall:Lekismon";
    inline static constexpr const char* ALT_DMALL_LEKISMON_FQNAME = ALT_DMALL_LEKISMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_LEKISMON_FQNAME_LEN = sizeof(ALT_DMALL_LEKISMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_LEOMON_FQID_ARR[] = "dmall:leomon";
    inline static constexpr const char* ALT_DMALL_LEOMON_FQID = ALT_DMALL_LEOMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_LEOMON_FQID_LEN = sizeof(ALT_DMALL_LEOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_LEOMON_FQNAME_ARR[] = "dmall:Leomon";
    inline static constexpr const char* ALT_DMALL_LEOMON_FQNAME = ALT_DMALL_LEOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_LEOMON_FQNAME_LEN = sizeof(ALT_DMALL_LEOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_LEOMON_X_FQID_ARR[] = "dmall:leomon_x";
    inline static constexpr const char* ALT_DMALL_LEOMON_X_FQID = ALT_DMALL_LEOMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_LEOMON_X_FQID_LEN = sizeof(ALT_DMALL_LEOMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_LEOMON_X_FQNAME_ARR[] = "dmall:Leomon X";
    inline static constexpr const char* ALT_DMALL_LEOMON_X_FQNAME = ALT_DMALL_LEOMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_LEOMON_X_FQNAME_LEN = sizeof(ALT_DMALL_LEOMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_LEVIAMON_FQID_ARR[] = "dmall:leviamon";
    inline static constexpr const char* ALT_DMALL_LEVIAMON_FQID = ALT_DMALL_LEVIAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_LEVIAMON_FQID_LEN = sizeof(ALT_DMALL_LEVIAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_LEVIAMON_FQNAME_ARR[] = "dmall:Leviamon";
    inline static constexpr const char* ALT_DMALL_LEVIAMON_FQNAME = ALT_DMALL_LEVIAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_LEVIAMON_FQNAME_LEN = sizeof(ALT_DMALL_LEVIAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_LEVIAMON_X_FQID_ARR[] = "dmall:leviamon_x";
    inline static constexpr const char* ALT_DMALL_LEVIAMON_X_FQID = ALT_DMALL_LEVIAMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_LEVIAMON_X_FQID_LEN = sizeof(ALT_DMALL_LEVIAMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_LEVIAMON_X_FQNAME_ARR[] = "dmall:Leviamon X";
    inline static constexpr const char* ALT_DMALL_LEVIAMON_X_FQNAME = ALT_DMALL_LEVIAMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_LEVIAMON_X_FQNAME_LEN = sizeof(ALT_DMALL_LEVIAMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_LILAMON_FQID_ARR[] = "dmall:lilamon";
    inline static constexpr const char* ALT_DMALL_LILAMON_FQID = ALT_DMALL_LILAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_LILAMON_FQID_LEN = sizeof(ALT_DMALL_LILAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_LILAMON_FQNAME_ARR[] = "dmall:Lilamon";
    inline static constexpr const char* ALT_DMALL_LILAMON_FQNAME = ALT_DMALL_LILAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_LILAMON_FQNAME_LEN = sizeof(ALT_DMALL_LILAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_LILIMON_FQID_ARR[] = "dmall:lilimon";
    inline static constexpr const char* ALT_DMALL_LILIMON_FQID = ALT_DMALL_LILIMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_LILIMON_FQID_LEN = sizeof(ALT_DMALL_LILIMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_LILIMON_FQNAME_ARR[] = "dmall:Lilimon";
    inline static constexpr const char* ALT_DMALL_LILIMON_FQNAME = ALT_DMALL_LILIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_LILIMON_FQNAME_LEN = sizeof(ALT_DMALL_LILIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_LILIMON_X_FQID_ARR[] = "dmall:lilimon_x";
    inline static constexpr const char* ALT_DMALL_LILIMON_X_FQID = ALT_DMALL_LILIMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_LILIMON_X_FQID_LEN = sizeof(ALT_DMALL_LILIMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_LILIMON_X_FQNAME_ARR[] = "dmall:Lilimon X";
    inline static constexpr const char* ALT_DMALL_LILIMON_X_FQNAME = ALT_DMALL_LILIMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_LILIMON_X_FQNAME_LEN = sizeof(ALT_DMALL_LILIMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_LILITHMON_FQID_ARR[] = "dmall:lilithmon";
    inline static constexpr const char* ALT_DMALL_LILITHMON_FQID = ALT_DMALL_LILITHMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_LILITHMON_FQID_LEN = sizeof(ALT_DMALL_LILITHMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_LILITHMON_FQNAME_ARR[] = "dmall:Lilithmon";
    inline static constexpr const char* ALT_DMALL_LILITHMON_FQNAME = ALT_DMALL_LILITHMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_LILITHMON_FQNAME_LEN = sizeof(ALT_DMALL_LILITHMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_LILITHMON_X_FQID_ARR[] = "dmall:lilithmon_x";
    inline static constexpr const char* ALT_DMALL_LILITHMON_X_FQID = ALT_DMALL_LILITHMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_LILITHMON_X_FQID_LEN = sizeof(ALT_DMALL_LILITHMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_LILITHMON_X_FQNAME_ARR[] = "dmall:Lilithmon X";
    inline static constexpr const char* ALT_DMALL_LILITHMON_X_FQNAME = ALT_DMALL_LILITHMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_LILITHMON_X_FQNAME_LEN = sizeof(ALT_DMALL_LILITHMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_LOPMON_FQID_ARR[] = "dmall:lopmon";
    inline static constexpr const char* ALT_DMALL_LOPMON_FQID = ALT_DMALL_LOPMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_LOPMON_FQID_LEN = sizeof(ALT_DMALL_LOPMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_LOPMON_FQNAME_ARR[] = "dmall:Lopmon";
    inline static constexpr const char* ALT_DMALL_LOPMON_FQNAME = ALT_DMALL_LOPMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_LOPMON_FQNAME_LEN = sizeof(ALT_DMALL_LOPMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_LOPMON_X_FQID_ARR[] = "dmall:lopmon_x";
    inline static constexpr const char* ALT_DMALL_LOPMON_X_FQID = ALT_DMALL_LOPMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_LOPMON_X_FQID_LEN = sizeof(ALT_DMALL_LOPMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_LOPMON_X_FQNAME_ARR[] = "dmall:Lopmon X";
    inline static constexpr const char* ALT_DMALL_LOPMON_X_FQNAME = ALT_DMALL_LOPMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_LOPMON_X_FQNAME_LEN = sizeof(ALT_DMALL_LOPMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_LORDKNIGHTMON_X_FQID_ARR[] = "dmall:lordknightmon_x";
    inline static constexpr const char* ALT_DMALL_LORDKNIGHTMON_X_FQID = ALT_DMALL_LORDKNIGHTMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_LORDKNIGHTMON_X_FQID_LEN = sizeof(ALT_DMALL_LORDKNIGHTMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_LORDKNIGHTMON_X_FQNAME_ARR[] = "dmall:LordKnightmon X";
    inline static constexpr const char* ALT_DMALL_LORDKNIGHTMON_X_FQNAME = ALT_DMALL_LORDKNIGHTMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_LORDKNIGHTMON_X_FQNAME_LEN = sizeof(ALT_DMALL_LORDKNIGHTMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_LOTUSMON_FQID_ARR[] = "dmall:lotusmon";
    inline static constexpr const char* ALT_DMALL_LOTUSMON_FQID = ALT_DMALL_LOTUSMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_LOTUSMON_FQID_LEN = sizeof(ALT_DMALL_LOTUSMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_LOTUSMON_FQNAME_ARR[] = "dmall:Lotusmon";
    inline static constexpr const char* ALT_DMALL_LOTUSMON_FQNAME = ALT_DMALL_LOTUSMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_LOTUSMON_FQNAME_LEN = sizeof(ALT_DMALL_LOTUSMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_LUCEMON_FALLDOWN_MODE_FQID_ARR[] = "dmall:lucemon_falldown_mode";
    inline static constexpr const char* ALT_DMALL_LUCEMON_FALLDOWN_MODE_FQID = ALT_DMALL_LUCEMON_FALLDOWN_MODE_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_LUCEMON_FALLDOWN_MODE_FQID_LEN = sizeof(ALT_DMALL_LUCEMON_FALLDOWN_MODE_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_LUCEMON_FALLDOWN_MODE_FQNAME_ARR[] = "dmall:Lucemon Falldown Mode";
    inline static constexpr const char* ALT_DMALL_LUCEMON_FALLDOWN_MODE_FQNAME = ALT_DMALL_LUCEMON_FALLDOWN_MODE_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_LUCEMON_FALLDOWN_MODE_FQNAME_LEN = sizeof(ALT_DMALL_LUCEMON_FALLDOWN_MODE_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_LUCEMON_FQID_ARR[] = "dmall:lucemon";
    inline static constexpr const char* ALT_DMALL_LUCEMON_FQID = ALT_DMALL_LUCEMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_LUCEMON_FQID_LEN = sizeof(ALT_DMALL_LUCEMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_LUCEMON_FQNAME_ARR[] = "dmall:Lucemon";
    inline static constexpr const char* ALT_DMALL_LUCEMON_FQNAME = ALT_DMALL_LUCEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_LUCEMON_FQNAME_LEN = sizeof(ALT_DMALL_LUCEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_LUCEMON_SATAN_MODE_FQID_ARR[] = "dmall:lucemon_satan_mode";
    inline static constexpr const char* ALT_DMALL_LUCEMON_SATAN_MODE_FQID = ALT_DMALL_LUCEMON_SATAN_MODE_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_LUCEMON_SATAN_MODE_FQID_LEN = sizeof(ALT_DMALL_LUCEMON_SATAN_MODE_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_LUCEMON_SATAN_MODE_FQNAME_ARR[] = "dmall:Lucemon Satan Mode";
    inline static constexpr const char* ALT_DMALL_LUCEMON_SATAN_MODE_FQNAME = ALT_DMALL_LUCEMON_SATAN_MODE_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_LUCEMON_SATAN_MODE_FQNAME_LEN = sizeof(ALT_DMALL_LUCEMON_SATAN_MODE_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_LUCEMON_X_FQID_ARR[] = "dmall:lucemon_x";
    inline static constexpr const char* ALT_DMALL_LUCEMON_X_FQID = ALT_DMALL_LUCEMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_LUCEMON_X_FQID_LEN = sizeof(ALT_DMALL_LUCEMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_LUCEMON_X_FQNAME_ARR[] = "dmall:Lucemon X";
    inline static constexpr const char* ALT_DMALL_LUCEMON_X_FQNAME = ALT_DMALL_LUCEMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_LUCEMON_X_FQNAME_LEN = sizeof(ALT_DMALL_LUCEMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_LUDOMON_FQID_ARR[] = "dmall:ludomon";
    inline static constexpr const char* ALT_DMALL_LUDOMON_FQID = ALT_DMALL_LUDOMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_LUDOMON_FQID_LEN = sizeof(ALT_DMALL_LUDOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_LUDOMON_FQNAME_ARR[] = "dmall:Ludomon";
    inline static constexpr const char* ALT_DMALL_LUDOMON_FQNAME = ALT_DMALL_LUDOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_LUDOMON_FQNAME_LEN = sizeof(ALT_DMALL_LUDOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_LUNAMON_FQID_ARR[] = "dmall:lunamon";
    inline static constexpr const char* ALT_DMALL_LUNAMON_FQID = ALT_DMALL_LUNAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_LUNAMON_FQID_LEN = sizeof(ALT_DMALL_LUNAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_LUNAMON_FQNAME_ARR[] = "dmall:Lunamon";
    inline static constexpr const char* ALT_DMALL_LUNAMON_FQNAME = ALT_DMALL_LUNAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_LUNAMON_FQNAME_LEN = sizeof(ALT_DMALL_LUNAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_LYNXMON_FQID_ARR[] = "dmall:lynxmon";
    inline static constexpr const char* ALT_DMALL_LYNXMON_FQID = ALT_DMALL_LYNXMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_LYNXMON_FQID_LEN = sizeof(ALT_DMALL_LYNXMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_LYNXMON_FQNAME_ARR[] = "dmall:Lynxmon";
    inline static constexpr const char* ALT_DMALL_LYNXMON_FQNAME = ALT_DMALL_LYNXMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_LYNXMON_FQNAME_LEN = sizeof(ALT_DMALL_LYNXMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_MACH_GAOGAMON_FQID_ARR[] = "dmall:mach_gaogamon";
    inline static constexpr const char* ALT_DMALL_MACH_GAOGAMON_FQID = ALT_DMALL_MACH_GAOGAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_MACH_GAOGAMON_FQID_LEN = sizeof(ALT_DMALL_MACH_GAOGAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_MACH_GAOGAMON_FQNAME_ARR[] = "dmall:Mach Gaogamon";
    inline static constexpr const char* ALT_DMALL_MACH_GAOGAMON_FQNAME = ALT_DMALL_MACH_GAOGAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_MACH_GAOGAMON_FQNAME_LEN = sizeof(ALT_DMALL_MACH_GAOGAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_MAD_LEOMON_FQID_ARR[] = "dmall:mad_leomon";
    inline static constexpr const char* ALT_DMALL_MAD_LEOMON_FQID = ALT_DMALL_MAD_LEOMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_MAD_LEOMON_FQID_LEN = sizeof(ALT_DMALL_MAD_LEOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_MAD_LEOMON_FQNAME_ARR[] = "dmall:Mad Leomon";
    inline static constexpr const char* ALT_DMALL_MAD_LEOMON_FQNAME = ALT_DMALL_MAD_LEOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_MAD_LEOMON_FQNAME_LEN = sizeof(ALT_DMALL_MAD_LEOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_MAGNAMON_X_FQID_ARR[] = "dmall:magnamon_x";
    inline static constexpr const char* ALT_DMALL_MAGNAMON_X_FQID = ALT_DMALL_MAGNAMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_MAGNAMON_X_FQID_LEN = sizeof(ALT_DMALL_MAGNAMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_MAGNAMON_X_FQNAME_ARR[] = "dmall:Magnamon X";
    inline static constexpr const char* ALT_DMALL_MAGNAMON_X_FQNAME = ALT_DMALL_MAGNAMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_MAGNAMON_X_FQNAME_LEN = sizeof(ALT_DMALL_MAGNAMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_MAMBOMON_FQID_ARR[] = "dmall:mambomon";
    inline static constexpr const char* ALT_DMALL_MAMBOMON_FQID = ALT_DMALL_MAMBOMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_MAMBOMON_FQID_LEN = sizeof(ALT_DMALL_MAMBOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_MAMBOMON_FQNAME_ARR[] = "dmall:Mambomon";
    inline static constexpr const char* ALT_DMALL_MAMBOMON_FQNAME = ALT_DMALL_MAMBOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_MAMBOMON_FQNAME_LEN = sizeof(ALT_DMALL_MAMBOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_MAMEMON_FQID_ARR[] = "dmall:mamemon";
    inline static constexpr const char* ALT_DMALL_MAMEMON_FQID = ALT_DMALL_MAMEMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_MAMEMON_FQID_LEN = sizeof(ALT_DMALL_MAMEMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_MAMEMON_FQNAME_ARR[] = "dmall:Mamemon";
    inline static constexpr const char* ALT_DMALL_MAMEMON_FQNAME = ALT_DMALL_MAMEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_MAMEMON_FQNAME_LEN = sizeof(ALT_DMALL_MAMEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_MAMEMON_X_FQID_ARR[] = "dmall:mamemon_x";
    inline static constexpr const char* ALT_DMALL_MAMEMON_X_FQID = ALT_DMALL_MAMEMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_MAMEMON_X_FQID_LEN = sizeof(ALT_DMALL_MAMEMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_MAMEMON_X_FQNAME_ARR[] = "dmall:Mamemon X";
    inline static constexpr const char* ALT_DMALL_MAMEMON_X_FQNAME = ALT_DMALL_MAMEMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_MAMEMON_X_FQNAME_LEN = sizeof(ALT_DMALL_MAMEMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_MAMETYRAMON_FQID_ARR[] = "dmall:mametyramon";
    inline static constexpr const char* ALT_DMALL_MAMETYRAMON_FQID = ALT_DMALL_MAMETYRAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_MAMETYRAMON_FQID_LEN = sizeof(ALT_DMALL_MAMETYRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_MAMETYRAMON_FQNAME_ARR[] = "dmall:Mametyramon";
    inline static constexpr const char* ALT_DMALL_MAMETYRAMON_FQNAME = ALT_DMALL_MAMETYRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_MAMETYRAMON_FQNAME_LEN = sizeof(ALT_DMALL_MAMETYRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_MAMMON_FQID_ARR[] = "dmall:mammon";
    inline static constexpr const char* ALT_DMALL_MAMMON_FQID = ALT_DMALL_MAMMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_MAMMON_FQID_LEN = sizeof(ALT_DMALL_MAMMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_MAMMON_FQNAME_ARR[] = "dmall:Mammon";
    inline static constexpr const char* ALT_DMALL_MAMMON_FQNAME = ALT_DMALL_MAMMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_MAMMON_FQNAME_LEN = sizeof(ALT_DMALL_MAMMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_MAMMON_X_FQID_ARR[] = "dmall:mammon_x";
    inline static constexpr const char* ALT_DMALL_MAMMON_X_FQID = ALT_DMALL_MAMMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_MAMMON_X_FQID_LEN = sizeof(ALT_DMALL_MAMMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_MAMMON_X_FQNAME_ARR[] = "dmall:Mammon X";
    inline static constexpr const char* ALT_DMALL_MAMMON_X_FQNAME = ALT_DMALL_MAMMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_MAMMON_X_FQNAME_LEN = sizeof(ALT_DMALL_MAMMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_MANTARAYMON_X_FQID_ARR[] = "dmall:mantaraymon_x";
    inline static constexpr const char* ALT_DMALL_MANTARAYMON_X_FQID = ALT_DMALL_MANTARAYMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_MANTARAYMON_X_FQID_LEN = sizeof(ALT_DMALL_MANTARAYMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_MANTARAYMON_X_FQNAME_ARR[] = "dmall:Mantaraymon X";
    inline static constexpr const char* ALT_DMALL_MANTARAYMON_X_FQNAME = ALT_DMALL_MANTARAYMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_MANTARAYMON_X_FQNAME_LEN = sizeof(ALT_DMALL_MANTARAYMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_MANTICOREMON_FQID_ARR[] = "dmall:manticoremon";
    inline static constexpr const char* ALT_DMALL_MANTICOREMON_FQID = ALT_DMALL_MANTICOREMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_MANTICOREMON_FQID_LEN = sizeof(ALT_DMALL_MANTICOREMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_MANTICOREMON_FQNAME_ARR[] = "dmall:Manticoremon";
    inline static constexpr const char* ALT_DMALL_MANTICOREMON_FQNAME = ALT_DMALL_MANTICOREMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_MANTICOREMON_FQNAME_LEN = sizeof(ALT_DMALL_MANTICOREMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_MARIN_ANGEMON_FQID_ARR[] = "dmall:marin_angemon";
    inline static constexpr const char* ALT_DMALL_MARIN_ANGEMON_FQID = ALT_DMALL_MARIN_ANGEMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_MARIN_ANGEMON_FQID_LEN = sizeof(ALT_DMALL_MARIN_ANGEMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_MARIN_ANGEMON_FQNAME_ARR[] = "dmall:Marin Angemon";
    inline static constexpr const char* ALT_DMALL_MARIN_ANGEMON_FQNAME = ALT_DMALL_MARIN_ANGEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_MARIN_ANGEMON_FQNAME_LEN = sizeof(ALT_DMALL_MARIN_ANGEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_MARIN_CHIMAIRAMON_FQID_ARR[] = "dmall:marin_chimairamon";
    inline static constexpr const char* ALT_DMALL_MARIN_CHIMAIRAMON_FQID = ALT_DMALL_MARIN_CHIMAIRAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_MARIN_CHIMAIRAMON_FQID_LEN = sizeof(ALT_DMALL_MARIN_CHIMAIRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_MARIN_CHIMAIRAMON_FQNAME_ARR[] = "dmall:Marin Chimairamon";
    inline static constexpr const char* ALT_DMALL_MARIN_CHIMAIRAMON_FQNAME = ALT_DMALL_MARIN_CHIMAIRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_MARIN_CHIMAIRAMON_FQNAME_LEN = sizeof(ALT_DMALL_MARIN_CHIMAIRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_MARIN_DEVIMON_FQID_ARR[] = "dmall:marin_devimon";
    inline static constexpr const char* ALT_DMALL_MARIN_DEVIMON_FQID = ALT_DMALL_MARIN_DEVIMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_MARIN_DEVIMON_FQID_LEN = sizeof(ALT_DMALL_MARIN_DEVIMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_MARIN_DEVIMON_FQNAME_ARR[] = "dmall:Marin Devimon";
    inline static constexpr const char* ALT_DMALL_MARIN_DEVIMON_FQNAME = ALT_DMALL_MARIN_DEVIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_MARIN_DEVIMON_FQNAME_LEN = sizeof(ALT_DMALL_MARIN_DEVIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_MASTEMON_FQID_ARR[] = "dmall:mastemon";
    inline static constexpr const char* ALT_DMALL_MASTEMON_FQID = ALT_DMALL_MASTEMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_MASTEMON_FQID_LEN = sizeof(ALT_DMALL_MASTEMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_MASTEMON_FQNAME_ARR[] = "dmall:Mastemon";
    inline static constexpr const char* ALT_DMALL_MASTEMON_FQNAME = ALT_DMALL_MASTEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_MASTEMON_FQNAME_LEN = sizeof(ALT_DMALL_MASTEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_MECHANORIMON_FQID_ARR[] = "dmall:mechanorimon";
    inline static constexpr const char* ALT_DMALL_MECHANORIMON_FQID = ALT_DMALL_MECHANORIMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_MECHANORIMON_FQID_LEN = sizeof(ALT_DMALL_MECHANORIMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_MECHANORIMON_FQNAME_ARR[] = "dmall:Mechanorimon";
    inline static constexpr const char* ALT_DMALL_MECHANORIMON_FQNAME = ALT_DMALL_MECHANORIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_MECHANORIMON_FQNAME_LEN = sizeof(ALT_DMALL_MECHANORIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_MEGADRAMON_FQID_ARR[] = "dmall:megadramon";
    inline static constexpr const char* ALT_DMALL_MEGADRAMON_FQID = ALT_DMALL_MEGADRAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_MEGADRAMON_FQID_LEN = sizeof(ALT_DMALL_MEGADRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_MEGADRAMON_FQNAME_ARR[] = "dmall:Megadramon";
    inline static constexpr const char* ALT_DMALL_MEGADRAMON_FQNAME = ALT_DMALL_MEGADRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_MEGADRAMON_FQNAME_LEN = sizeof(ALT_DMALL_MEGADRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_MEGALO_GROWMON_ORANGE_FQID_ARR[] = "dmall:megalo_growmon_orange";
    inline static constexpr const char* ALT_DMALL_MEGALO_GROWMON_ORANGE_FQID = ALT_DMALL_MEGALO_GROWMON_ORANGE_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_MEGALO_GROWMON_ORANGE_FQID_LEN = sizeof(ALT_DMALL_MEGALO_GROWMON_ORANGE_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_MEGALO_GROWMON_ORANGE_FQNAME_ARR[] = "dmall:Megalo Growmon (Orange)";
    inline static constexpr const char* ALT_DMALL_MEGALO_GROWMON_ORANGE_FQNAME = ALT_DMALL_MEGALO_GROWMON_ORANGE_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_MEGALO_GROWMON_ORANGE_FQNAME_LEN = sizeof(ALT_DMALL_MEGALO_GROWMON_ORANGE_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_MEGALO_GROWMON_FQID_ARR[] = "dmall:megalo_growmon";
    inline static constexpr const char* ALT_DMALL_MEGALO_GROWMON_FQID = ALT_DMALL_MEGALO_GROWMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_MEGALO_GROWMON_FQID_LEN = sizeof(ALT_DMALL_MEGALO_GROWMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_MEGALO_GROWMON_FQNAME_ARR[] = "dmall:Megalo Growmon";
    inline static constexpr const char* ALT_DMALL_MEGALO_GROWMON_FQNAME = ALT_DMALL_MEGALO_GROWMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_MEGALO_GROWMON_FQNAME_LEN = sizeof(ALT_DMALL_MEGALO_GROWMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_MEGALO_GROWMON_X_FQID_ARR[] = "dmall:megalo_growmon_x";
    inline static constexpr const char* ALT_DMALL_MEGALO_GROWMON_X_FQID = ALT_DMALL_MEGALO_GROWMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_MEGALO_GROWMON_X_FQID_LEN = sizeof(ALT_DMALL_MEGALO_GROWMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_MEGALO_GROWMON_X_FQNAME_ARR[] = "dmall:Megalo Growmon X";
    inline static constexpr const char* ALT_DMALL_MEGALO_GROWMON_X_FQNAME = ALT_DMALL_MEGALO_GROWMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_MEGALO_GROWMON_X_FQNAME_LEN = sizeof(ALT_DMALL_MEGALO_GROWMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_MEGA_SEADRAMON_FQID_ARR[] = "dmall:mega_seadramon";
    inline static constexpr const char* ALT_DMALL_MEGA_SEADRAMON_FQID = ALT_DMALL_MEGA_SEADRAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_MEGA_SEADRAMON_FQID_LEN = sizeof(ALT_DMALL_MEGA_SEADRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_MEGA_SEADRAMON_FQNAME_ARR[] = "dmall:Mega Seadramon";
    inline static constexpr const char* ALT_DMALL_MEGA_SEADRAMON_FQNAME = ALT_DMALL_MEGA_SEADRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_MEGA_SEADRAMON_FQNAME_LEN = sizeof(ALT_DMALL_MEGA_SEADRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_MEGA_SEADRAMON_X_FQID_ARR[] = "dmall:mega_seadramon_x";
    inline static constexpr const char* ALT_DMALL_MEGA_SEADRAMON_X_FQID = ALT_DMALL_MEGA_SEADRAMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_MEGA_SEADRAMON_X_FQID_LEN = sizeof(ALT_DMALL_MEGA_SEADRAMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_MEGA_SEADRAMON_X_FQNAME_ARR[] = "dmall:Mega Seadramon X";
    inline static constexpr const char* ALT_DMALL_MEGA_SEADRAMON_X_FQNAME = ALT_DMALL_MEGA_SEADRAMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_MEGA_SEADRAMON_X_FQNAME_LEN = sizeof(ALT_DMALL_MEGA_SEADRAMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_MEGIDRAMON_FQID_ARR[] = "dmall:megidramon";
    inline static constexpr const char* ALT_DMALL_MEGIDRAMON_FQID = ALT_DMALL_MEGIDRAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_MEGIDRAMON_FQID_LEN = sizeof(ALT_DMALL_MEGIDRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_MEGIDRAMON_FQNAME_ARR[] = "dmall:Megidramon";
    inline static constexpr const char* ALT_DMALL_MEGIDRAMON_FQNAME = ALT_DMALL_MEGIDRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_MEGIDRAMON_FQNAME_LEN = sizeof(ALT_DMALL_MEGIDRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_MEGIDRAMON_X_FQID_ARR[] = "dmall:megidramon_x";
    inline static constexpr const char* ALT_DMALL_MEGIDRAMON_X_FQID = ALT_DMALL_MEGIDRAMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_MEGIDRAMON_X_FQID_LEN = sizeof(ALT_DMALL_MEGIDRAMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_MEGIDRAMON_X_FQNAME_ARR[] = "dmall:Megidramon X";
    inline static constexpr const char* ALT_DMALL_MEGIDRAMON_X_FQNAME = ALT_DMALL_MEGIDRAMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_MEGIDRAMON_X_FQNAME_LEN = sizeof(ALT_DMALL_MEGIDRAMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_MEICOOMON_BABY_FQID_ARR[] = "dmall:meicoomon_baby";
    inline static constexpr const char* ALT_DMALL_MEICOOMON_BABY_FQID = ALT_DMALL_MEICOOMON_BABY_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_MEICOOMON_BABY_FQID_LEN = sizeof(ALT_DMALL_MEICOOMON_BABY_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_MEICOOMON_BABY_FQNAME_ARR[] = "dmall:Meicoomon (Baby)";
    inline static constexpr const char* ALT_DMALL_MEICOOMON_BABY_FQNAME = ALT_DMALL_MEICOOMON_BABY_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_MEICOOMON_BABY_FQNAME_LEN = sizeof(ALT_DMALL_MEICOOMON_BABY_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_MEICOOMON_CHILD_FQID_ARR[] = "dmall:meicoomon_child";
    inline static constexpr const char* ALT_DMALL_MEICOOMON_CHILD_FQID = ALT_DMALL_MEICOOMON_CHILD_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_MEICOOMON_CHILD_FQID_LEN = sizeof(ALT_DMALL_MEICOOMON_CHILD_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_MEICOOMON_CHILD_FQNAME_ARR[] = "dmall:Meicoomon (Child)";
    inline static constexpr const char* ALT_DMALL_MEICOOMON_CHILD_FQNAME = ALT_DMALL_MEICOOMON_CHILD_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_MEICOOMON_CHILD_FQNAME_LEN = sizeof(ALT_DMALL_MEICOOMON_CHILD_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_MEICOOMON_FQID_ARR[] = "dmall:meicoomon";
    inline static constexpr const char* ALT_DMALL_MEICOOMON_FQID = ALT_DMALL_MEICOOMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_MEICOOMON_FQID_LEN = sizeof(ALT_DMALL_MEICOOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_MEICOOMON_FQNAME_ARR[] = "dmall:Meicoomon";
    inline static constexpr const char* ALT_DMALL_MEICOOMON_FQNAME = ALT_DMALL_MEICOOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_MEICOOMON_FQNAME_LEN = sizeof(ALT_DMALL_MEICOOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_MEICRACKMON_FQID_ARR[] = "dmall:meicrackmon";
    inline static constexpr const char* ALT_DMALL_MEICRACKMON_FQID = ALT_DMALL_MEICRACKMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_MEICRACKMON_FQID_LEN = sizeof(ALT_DMALL_MEICRACKMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_MEICRACKMON_FQNAME_ARR[] = "dmall:Meicrackmon";
    inline static constexpr const char* ALT_DMALL_MEICRACKMON_FQNAME = ALT_DMALL_MEICRACKMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_MEICRACKMON_FQNAME_LEN = sizeof(ALT_DMALL_MEICRACKMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_MEICRACKMON_VICIOUS_MODE_FQID_ARR[] = "dmall:meicrackmon_vicious_mode";
    inline static constexpr const char* ALT_DMALL_MEICRACKMON_VICIOUS_MODE_FQID = ALT_DMALL_MEICRACKMON_VICIOUS_MODE_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_MEICRACKMON_VICIOUS_MODE_FQID_LEN = sizeof(ALT_DMALL_MEICRACKMON_VICIOUS_MODE_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_MEICRACKMON_VICIOUS_MODE_FQNAME_ARR[] = "dmall:Meicrackmon Vicious Mode";
    inline static constexpr const char* ALT_DMALL_MEICRACKMON_VICIOUS_MODE_FQNAME = ALT_DMALL_MEICRACKMON_VICIOUS_MODE_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_MEICRACKMON_VICIOUS_MODE_FQNAME_LEN = sizeof(ALT_DMALL_MEICRACKMON_VICIOUS_MODE_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_MEPHISMON_FQID_ARR[] = "dmall:mephismon";
    inline static constexpr const char* ALT_DMALL_MEPHISMON_FQID = ALT_DMALL_MEPHISMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_MEPHISMON_FQID_LEN = sizeof(ALT_DMALL_MEPHISMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_MEPHISMON_FQNAME_ARR[] = "dmall:Mephismon";
    inline static constexpr const char* ALT_DMALL_MEPHISMON_FQNAME = ALT_DMALL_MEPHISMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_MEPHISMON_FQNAME_LEN = sizeof(ALT_DMALL_MEPHISMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_MEPHISMON_X_FQID_ARR[] = "dmall:mephismon_x";
    inline static constexpr const char* ALT_DMALL_MEPHISMON_X_FQID = ALT_DMALL_MEPHISMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_MEPHISMON_X_FQID_LEN = sizeof(ALT_DMALL_MEPHISMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_MEPHISMON_X_FQNAME_ARR[] = "dmall:Mephismon X";
    inline static constexpr const char* ALT_DMALL_MEPHISMON_X_FQNAME = ALT_DMALL_MEPHISMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_MEPHISMON_X_FQNAME_LEN = sizeof(ALT_DMALL_MEPHISMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_MERAMON_FQID_ARR[] = "dmall:meramon";
    inline static constexpr const char* ALT_DMALL_MERAMON_FQID = ALT_DMALL_MERAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_MERAMON_FQID_LEN = sizeof(ALT_DMALL_MERAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_MERAMON_FQNAME_ARR[] = "dmall:Meramon";
    inline static constexpr const char* ALT_DMALL_MERAMON_FQNAME = ALT_DMALL_MERAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_MERAMON_FQNAME_LEN = sizeof(ALT_DMALL_MERAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_MERAMON_X_FQID_ARR[] = "dmall:meramon_x";
    inline static constexpr const char* ALT_DMALL_MERAMON_X_FQID = ALT_DMALL_MERAMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_MERAMON_X_FQID_LEN = sizeof(ALT_DMALL_MERAMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_MERAMON_X_FQNAME_ARR[] = "dmall:Meramon X";
    inline static constexpr const char* ALT_DMALL_MERAMON_X_FQNAME = ALT_DMALL_MERAMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_MERAMON_X_FQNAME_LEN = sizeof(ALT_DMALL_MERAMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_MERMAIMON_FQID_ARR[] = "dmall:mermaimon";
    inline static constexpr const char* ALT_DMALL_MERMAIMON_FQID = ALT_DMALL_MERMAIMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_MERMAIMON_FQID_LEN = sizeof(ALT_DMALL_MERMAIMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_MERMAIMON_FQNAME_ARR[] = "dmall:Mermaimon";
    inline static constexpr const char* ALT_DMALL_MERMAIMON_FQNAME = ALT_DMALL_MERMAIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_MERMAIMON_FQNAME_LEN = sizeof(ALT_DMALL_MERMAIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_METAL_ETEMON_FQID_ARR[] = "dmall:metal_etemon";
    inline static constexpr const char* ALT_DMALL_METAL_ETEMON_FQID = ALT_DMALL_METAL_ETEMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_METAL_ETEMON_FQID_LEN = sizeof(ALT_DMALL_METAL_ETEMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_METAL_ETEMON_FQNAME_ARR[] = "dmall:Metal Etemon";
    inline static constexpr const char* ALT_DMALL_METAL_ETEMON_FQNAME = ALT_DMALL_METAL_ETEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_METAL_ETEMON_FQNAME_LEN = sizeof(ALT_DMALL_METAL_ETEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_METAL_GARURUMON_BLACK_FQID_ARR[] = "dmall:metal_garurumon_black";
    inline static constexpr const char* ALT_DMALL_METAL_GARURUMON_BLACK_FQID = ALT_DMALL_METAL_GARURUMON_BLACK_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_METAL_GARURUMON_BLACK_FQID_LEN = sizeof(ALT_DMALL_METAL_GARURUMON_BLACK_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_METAL_GARURUMON_BLACK_FQNAME_ARR[] = "dmall:Metal Garurumon (Black)";
    inline static constexpr const char* ALT_DMALL_METAL_GARURUMON_BLACK_FQNAME = ALT_DMALL_METAL_GARURUMON_BLACK_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_METAL_GARURUMON_BLACK_FQNAME_LEN = sizeof(ALT_DMALL_METAL_GARURUMON_BLACK_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_METAL_GARURUMON_FQID_ARR[] = "dmall:metal_garurumon";
    inline static constexpr const char* ALT_DMALL_METAL_GARURUMON_FQID = ALT_DMALL_METAL_GARURUMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_METAL_GARURUMON_FQID_LEN = sizeof(ALT_DMALL_METAL_GARURUMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_METAL_GARURUMON_FQNAME_ARR[] = "dmall:Metal Garurumon";
    inline static constexpr const char* ALT_DMALL_METAL_GARURUMON_FQNAME = ALT_DMALL_METAL_GARURUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_METAL_GARURUMON_FQNAME_LEN = sizeof(ALT_DMALL_METAL_GARURUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_METAL_GARURUMON_X_FQID_ARR[] = "dmall:metal_garurumon_x";
    inline static constexpr const char* ALT_DMALL_METAL_GARURUMON_X_FQID = ALT_DMALL_METAL_GARURUMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_METAL_GARURUMON_X_FQID_LEN = sizeof(ALT_DMALL_METAL_GARURUMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_METAL_GARURUMON_X_FQNAME_ARR[] = "dmall:Metal Garurumon X";
    inline static constexpr const char* ALT_DMALL_METAL_GARURUMON_X_FQNAME = ALT_DMALL_METAL_GARURUMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_METAL_GARURUMON_X_FQNAME_LEN = sizeof(ALT_DMALL_METAL_GARURUMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_METAL_GREYMON_FQID_ARR[] = "dmall:metal_greymon";
    inline static constexpr const char* ALT_DMALL_METAL_GREYMON_FQID = ALT_DMALL_METAL_GREYMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_METAL_GREYMON_FQID_LEN = sizeof(ALT_DMALL_METAL_GREYMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_METAL_GREYMON_FQNAME_ARR[] = "dmall:Metal Greymon";
    inline static constexpr const char* ALT_DMALL_METAL_GREYMON_FQNAME = ALT_DMALL_METAL_GREYMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_METAL_GREYMON_FQNAME_LEN = sizeof(ALT_DMALL_METAL_GREYMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_METAL_GREYMON_VIRUS_FQID_ARR[] = "dmall:metal_greymon_virus";
    inline static constexpr const char* ALT_DMALL_METAL_GREYMON_VIRUS_FQID = ALT_DMALL_METAL_GREYMON_VIRUS_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_METAL_GREYMON_VIRUS_FQID_LEN = sizeof(ALT_DMALL_METAL_GREYMON_VIRUS_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_METAL_GREYMON_VIRUS_FQNAME_ARR[] = "dmall:Metal Greymon (Virus)";
    inline static constexpr const char* ALT_DMALL_METAL_GREYMON_VIRUS_FQNAME = ALT_DMALL_METAL_GREYMON_VIRUS_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_METAL_GREYMON_VIRUS_FQNAME_LEN = sizeof(ALT_DMALL_METAL_GREYMON_VIRUS_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_METAL_GREYMON_VIRUS_X_FQID_ARR[] = "dmall:metal_greymon_virus_x";
    inline static constexpr const char* ALT_DMALL_METAL_GREYMON_VIRUS_X_FQID = ALT_DMALL_METAL_GREYMON_VIRUS_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_METAL_GREYMON_VIRUS_X_FQID_LEN = sizeof(ALT_DMALL_METAL_GREYMON_VIRUS_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_METAL_GREYMON_VIRUS_X_FQNAME_ARR[] = "dmall:Metal Greymon (Virus) X";
    inline static constexpr const char* ALT_DMALL_METAL_GREYMON_VIRUS_X_FQNAME = ALT_DMALL_METAL_GREYMON_VIRUS_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_METAL_GREYMON_VIRUS_X_FQNAME_LEN = sizeof(ALT_DMALL_METAL_GREYMON_VIRUS_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_METALGREYMON_X_FQID_ARR[] = "dmall:metalgreymon_x";
    inline static constexpr const char* ALT_DMALL_METALGREYMON_X_FQID = ALT_DMALL_METALGREYMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_METALGREYMON_X_FQID_LEN = sizeof(ALT_DMALL_METALGREYMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_METALGREYMON_X_FQNAME_ARR[] = "dmall:MetalGreymon X";
    inline static constexpr const char* ALT_DMALL_METALGREYMON_X_FQNAME = ALT_DMALL_METALGREYMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_METALGREYMON_X_FQNAME_LEN = sizeof(ALT_DMALL_METALGREYMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_METALLICDRAMON_FQID_ARR[] = "dmall:metallicdramon";
    inline static constexpr const char* ALT_DMALL_METALLICDRAMON_FQID = ALT_DMALL_METALLICDRAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_METALLICDRAMON_FQID_LEN = sizeof(ALT_DMALL_METALLICDRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_METALLICDRAMON_FQNAME_ARR[] = "dmall:Metallicdramon";
    inline static constexpr const char* ALT_DMALL_METALLICDRAMON_FQNAME = ALT_DMALL_METALLICDRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_METALLICDRAMON_FQNAME_LEN = sizeof(ALT_DMALL_METALLICDRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_METAL_MAMEMON_FQID_ARR[] = "dmall:metal_mamemon";
    inline static constexpr const char* ALT_DMALL_METAL_MAMEMON_FQID = ALT_DMALL_METAL_MAMEMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_METAL_MAMEMON_FQID_LEN = sizeof(ALT_DMALL_METAL_MAMEMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_METAL_MAMEMON_FQNAME_ARR[] = "dmall:Metal Mamemon";
    inline static constexpr const char* ALT_DMALL_METAL_MAMEMON_FQNAME = ALT_DMALL_METAL_MAMEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_METAL_MAMEMON_FQNAME_LEN = sizeof(ALT_DMALL_METAL_MAMEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_METAL_MAMEMON_X_FQID_ARR[] = "dmall:metal_mamemon_x";
    inline static constexpr const char* ALT_DMALL_METAL_MAMEMON_X_FQID = ALT_DMALL_METAL_MAMEMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_METAL_MAMEMON_X_FQID_LEN = sizeof(ALT_DMALL_METAL_MAMEMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_METAL_MAMEMON_X_FQNAME_ARR[] = "dmall:Metal Mamemon X";
    inline static constexpr const char* ALT_DMALL_METAL_MAMEMON_X_FQNAME = ALT_DMALL_METAL_MAMEMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_METAL_MAMEMON_X_FQNAME_LEN = sizeof(ALT_DMALL_METAL_MAMEMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_METAL_PHANTOMON_FQID_ARR[] = "dmall:metal_phantomon";
    inline static constexpr const char* ALT_DMALL_METAL_PHANTOMON_FQID = ALT_DMALL_METAL_PHANTOMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_METAL_PHANTOMON_FQID_LEN = sizeof(ALT_DMALL_METAL_PHANTOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_METAL_PHANTOMON_FQNAME_ARR[] = "dmall:Metal Phantomon";
    inline static constexpr const char* ALT_DMALL_METAL_PHANTOMON_FQNAME = ALT_DMALL_METAL_PHANTOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_METAL_PHANTOMON_FQNAME_LEN = sizeof(ALT_DMALL_METAL_PHANTOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_METAL_PIRANIMON_FQID_ARR[] = "dmall:metal_piranimon";
    inline static constexpr const char* ALT_DMALL_METAL_PIRANIMON_FQID = ALT_DMALL_METAL_PIRANIMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_METAL_PIRANIMON_FQID_LEN = sizeof(ALT_DMALL_METAL_PIRANIMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_METAL_PIRANIMON_FQNAME_ARR[] = "dmall:Metal Piranimon";
    inline static constexpr const char* ALT_DMALL_METAL_PIRANIMON_FQNAME = ALT_DMALL_METAL_PIRANIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_METAL_PIRANIMON_FQNAME_LEN = sizeof(ALT_DMALL_METAL_PIRANIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_METAL_SEADRAMON_FQID_ARR[] = "dmall:metal_seadramon";
    inline static constexpr const char* ALT_DMALL_METAL_SEADRAMON_FQID = ALT_DMALL_METAL_SEADRAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_METAL_SEADRAMON_FQID_LEN = sizeof(ALT_DMALL_METAL_SEADRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_METAL_SEADRAMON_FQNAME_ARR[] = "dmall:Metal Seadramon";
    inline static constexpr const char* ALT_DMALL_METAL_SEADRAMON_FQNAME = ALT_DMALL_METAL_SEADRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_METAL_SEADRAMON_FQNAME_LEN = sizeof(ALT_DMALL_METAL_SEADRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_METAL_TYRANOMON_FQID_ARR[] = "dmall:metal_tyranomon";
    inline static constexpr const char* ALT_DMALL_METAL_TYRANOMON_FQID = ALT_DMALL_METAL_TYRANOMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_METAL_TYRANOMON_FQID_LEN = sizeof(ALT_DMALL_METAL_TYRANOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_METAL_TYRANOMON_FQNAME_ARR[] = "dmall:Metal Tyranomon";
    inline static constexpr const char* ALT_DMALL_METAL_TYRANOMON_FQNAME = ALT_DMALL_METAL_TYRANOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_METAL_TYRANOMON_FQNAME_LEN = sizeof(ALT_DMALL_METAL_TYRANOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_METAL_TYRANOMON_X_FQID_ARR[] = "dmall:metal_tyranomon_x";
    inline static constexpr const char* ALT_DMALL_METAL_TYRANOMON_X_FQID = ALT_DMALL_METAL_TYRANOMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_METAL_TYRANOMON_X_FQID_LEN = sizeof(ALT_DMALL_METAL_TYRANOMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_METAL_TYRANOMON_X_FQNAME_ARR[] = "dmall:Metal Tyranomon X";
    inline static constexpr const char* ALT_DMALL_METAL_TYRANOMON_X_FQNAME = ALT_DMALL_METAL_TYRANOMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_METAL_TYRANOMON_X_FQNAME_LEN = sizeof(ALT_DMALL_METAL_TYRANOMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_MIKEMON_FQID_ARR[] = "dmall:mikemon";
    inline static constexpr const char* ALT_DMALL_MIKEMON_FQID = ALT_DMALL_MIKEMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_MIKEMON_FQID_LEN = sizeof(ALT_DMALL_MIKEMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_MIKEMON_FQNAME_ARR[] = "dmall:Mikemon";
    inline static constexpr const char* ALT_DMALL_MIKEMON_FQNAME = ALT_DMALL_MIKEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_MIKEMON_FQNAME_LEN = sizeof(ALT_DMALL_MIKEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_MILLENNIUMON_FQID_ARR[] = "dmall:millenniumon";
    inline static constexpr const char* ALT_DMALL_MILLENNIUMON_FQID = ALT_DMALL_MILLENNIUMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_MILLENNIUMON_FQID_LEN = sizeof(ALT_DMALL_MILLENNIUMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_MILLENNIUMON_FQNAME_ARR[] = "dmall:Millenniumon";
    inline static constexpr const char* ALT_DMALL_MILLENNIUMON_FQNAME = ALT_DMALL_MILLENNIUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_MILLENNIUMON_FQNAME_LEN = sizeof(ALT_DMALL_MILLENNIUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_MIMICMON_FQID_ARR[] = "dmall:mimicmon";
    inline static constexpr const char* ALT_DMALL_MIMICMON_FQID = ALT_DMALL_MIMICMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_MIMICMON_FQID_LEN = sizeof(ALT_DMALL_MIMICMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_MIMICMON_FQNAME_ARR[] = "dmall:Mimicmon";
    inline static constexpr const char* ALT_DMALL_MIMICMON_FQNAME = ALT_DMALL_MIMICMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_MIMICMON_FQNAME_LEN = sizeof(ALT_DMALL_MIMICMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_MINERVAMON_X_FQID_ARR[] = "dmall:minervamon_x";
    inline static constexpr const char* ALT_DMALL_MINERVAMON_X_FQID = ALT_DMALL_MINERVAMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_MINERVAMON_X_FQID_LEN = sizeof(ALT_DMALL_MINERVAMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_MINERVAMON_X_FQNAME_ARR[] = "dmall:Minervamon X";
    inline static constexpr const char* ALT_DMALL_MINERVAMON_X_FQNAME = ALT_DMALL_MINERVAMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_MINERVAMON_X_FQNAME_LEN = sizeof(ALT_DMALL_MINERVAMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_MINOMON_FQID_ARR[] = "dmall:minomon";
    inline static constexpr const char* ALT_DMALL_MINOMON_FQID = ALT_DMALL_MINOMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_MINOMON_FQID_LEN = sizeof(ALT_DMALL_MINOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_MINOMON_FQNAME_ARR[] = "dmall:Minomon";
    inline static constexpr const char* ALT_DMALL_MINOMON_FQNAME = ALT_DMALL_MINOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_MINOMON_FQNAME_LEN = sizeof(ALT_DMALL_MINOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_MOCHIMON_FQID_ARR[] = "dmall:mochimon";
    inline static constexpr const char* ALT_DMALL_MOCHIMON_FQID = ALT_DMALL_MOCHIMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_MOCHIMON_FQID_LEN = sizeof(ALT_DMALL_MOCHIMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_MOCHIMON_FQNAME_ARR[] = "dmall:Mochimon";
    inline static constexpr const char* ALT_DMALL_MOCHIMON_FQNAME = ALT_DMALL_MOCHIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_MOCHIMON_FQNAME_LEN = sizeof(ALT_DMALL_MOCHIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_MOKUMON_FQID_ARR[] = "dmall:mokumon";
    inline static constexpr const char* ALT_DMALL_MOKUMON_FQID = ALT_DMALL_MOKUMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_MOKUMON_FQID_LEN = sizeof(ALT_DMALL_MOKUMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_MOKUMON_FQNAME_ARR[] = "dmall:Mokumon";
    inline static constexpr const char* ALT_DMALL_MOKUMON_FQNAME = ALT_DMALL_MOKUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_MOKUMON_FQNAME_LEN = sizeof(ALT_DMALL_MOKUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_MONIMON_FQID_ARR[] = "dmall:monimon";
    inline static constexpr const char* ALT_DMALL_MONIMON_FQID = ALT_DMALL_MONIMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_MONIMON_FQID_LEN = sizeof(ALT_DMALL_MONIMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_MONIMON_FQNAME_ARR[] = "dmall:Monimon";
    inline static constexpr const char* ALT_DMALL_MONIMON_FQNAME = ALT_DMALL_MONIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_MONIMON_FQNAME_LEN = sizeof(ALT_DMALL_MONIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_MONOCHROMON_FQID_ARR[] = "dmall:monochromon";
    inline static constexpr const char* ALT_DMALL_MONOCHROMON_FQID = ALT_DMALL_MONOCHROMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_MONOCHROMON_FQID_LEN = sizeof(ALT_DMALL_MONOCHROMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_MONOCHROMON_FQNAME_ARR[] = "dmall:Monochromon";
    inline static constexpr const char* ALT_DMALL_MONOCHROMON_FQNAME = ALT_DMALL_MONOCHROMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_MONOCHROMON_FQNAME_LEN = sizeof(ALT_DMALL_MONOCHROMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_MONOCHROMON_X_FQID_ARR[] = "dmall:monochromon_x";
    inline static constexpr const char* ALT_DMALL_MONOCHROMON_X_FQID = ALT_DMALL_MONOCHROMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_MONOCHROMON_X_FQID_LEN = sizeof(ALT_DMALL_MONOCHROMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_MONOCHROMON_X_FQNAME_ARR[] = "dmall:Monochromon X";
    inline static constexpr const char* ALT_DMALL_MONOCHROMON_X_FQNAME = ALT_DMALL_MONOCHROMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_MONOCHROMON_X_FQNAME_LEN = sizeof(ALT_DMALL_MONOCHROMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_MONZAEMON_FQID_ARR[] = "dmall:monzaemon";
    inline static constexpr const char* ALT_DMALL_MONZAEMON_FQID = ALT_DMALL_MONZAEMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_MONZAEMON_FQID_LEN = sizeof(ALT_DMALL_MONZAEMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_MONZAEMON_FQNAME_ARR[] = "dmall:Monzaemon";
    inline static constexpr const char* ALT_DMALL_MONZAEMON_FQNAME = ALT_DMALL_MONZAEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_MONZAEMON_FQNAME_LEN = sizeof(ALT_DMALL_MONZAEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_MONZAEMON_X_FQID_ARR[] = "dmall:monzaemon_x";
    inline static constexpr const char* ALT_DMALL_MONZAEMON_X_FQID = ALT_DMALL_MONZAEMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_MONZAEMON_X_FQID_LEN = sizeof(ALT_DMALL_MONZAEMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_MONZAEMON_X_FQNAME_ARR[] = "dmall:Monzaemon X";
    inline static constexpr const char* ALT_DMALL_MONZAEMON_X_FQNAME = ALT_DMALL_MONZAEMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_MONZAEMON_X_FQNAME_LEN = sizeof(ALT_DMALL_MONZAEMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_MOONMON_FQID_ARR[] = "dmall:moonmon";
    inline static constexpr const char* ALT_DMALL_MOONMON_FQID = ALT_DMALL_MOONMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_MOONMON_FQID_LEN = sizeof(ALT_DMALL_MOONMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_MOONMON_FQNAME_ARR[] = "dmall:Moonmon";
    inline static constexpr const char* ALT_DMALL_MOONMON_FQNAME = ALT_DMALL_MOONMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_MOONMON_FQNAME_LEN = sizeof(ALT_DMALL_MOONMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_MORI_SHELLMON_FQID_ARR[] = "dmall:mori_shellmon";
    inline static constexpr const char* ALT_DMALL_MORI_SHELLMON_FQID = ALT_DMALL_MORI_SHELLMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_MORI_SHELLMON_FQID_LEN = sizeof(ALT_DMALL_MORI_SHELLMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_MORI_SHELLMON_FQNAME_ARR[] = "dmall:Mori Shellmon";
    inline static constexpr const char* ALT_DMALL_MORI_SHELLMON_FQNAME = ALT_DMALL_MORI_SHELLMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_MORI_SHELLMON_FQNAME_LEN = sizeof(ALT_DMALL_MORI_SHELLMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_MORPHOMON_FQID_ARR[] = "dmall:morphomon";
    inline static constexpr const char* ALT_DMALL_MORPHOMON_FQID = ALT_DMALL_MORPHOMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_MORPHOMON_FQID_LEN = sizeof(ALT_DMALL_MORPHOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_MORPHOMON_FQNAME_ARR[] = "dmall:Morphomon";
    inline static constexpr const char* ALT_DMALL_MORPHOMON_FQNAME = ALT_DMALL_MORPHOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_MORPHOMON_FQNAME_LEN = sizeof(ALT_DMALL_MORPHOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_MUCHOMON_FQID_ARR[] = "dmall:muchomon";
    inline static constexpr const char* ALT_DMALL_MUCHOMON_FQID = ALT_DMALL_MUCHOMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_MUCHOMON_FQID_LEN = sizeof(ALT_DMALL_MUCHOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_MUCHOMON_FQNAME_ARR[] = "dmall:Muchomon";
    inline static constexpr const char* ALT_DMALL_MUCHOMON_FQNAME = ALT_DMALL_MUCHOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_MUCHOMON_FQNAME_LEN = sizeof(ALT_DMALL_MUCHOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_MUGENDRAMON_FQID_ARR[] = "dmall:mugendramon";
    inline static constexpr const char* ALT_DMALL_MUGENDRAMON_FQID = ALT_DMALL_MUGENDRAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_MUGENDRAMON_FQID_LEN = sizeof(ALT_DMALL_MUGENDRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_MUGENDRAMON_FQNAME_ARR[] = "dmall:Mugendramon";
    inline static constexpr const char* ALT_DMALL_MUGENDRAMON_FQNAME = ALT_DMALL_MUGENDRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_MUGENDRAMON_FQNAME_LEN = sizeof(ALT_DMALL_MUGENDRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_MUSHMON_FQID_ARR[] = "dmall:mushmon";
    inline static constexpr const char* ALT_DMALL_MUSHMON_FQID = ALT_DMALL_MUSHMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_MUSHMON_FQID_LEN = sizeof(ALT_DMALL_MUSHMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_MUSHMON_FQNAME_ARR[] = "dmall:Mushmon";
    inline static constexpr const char* ALT_DMALL_MUSHMON_FQNAME = ALT_DMALL_MUSHMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_MUSHMON_FQNAME_LEN = sizeof(ALT_DMALL_MUSHMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_NANOMON_FQID_ARR[] = "dmall:nanomon";
    inline static constexpr const char* ALT_DMALL_NANOMON_FQID = ALT_DMALL_NANOMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_NANOMON_FQID_LEN = sizeof(ALT_DMALL_NANOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_NANOMON_FQNAME_ARR[] = "dmall:Nanomon";
    inline static constexpr const char* ALT_DMALL_NANOMON_FQNAME = ALT_DMALL_NANOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_NANOMON_FQNAME_LEN = sizeof(ALT_DMALL_NANOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_NEFERTIMON_X_FQID_ARR[] = "dmall:nefertimon_x";
    inline static constexpr const char* ALT_DMALL_NEFERTIMON_X_FQID = ALT_DMALL_NEFERTIMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_NEFERTIMON_X_FQID_LEN = sizeof(ALT_DMALL_NEFERTIMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_NEFERTIMON_X_FQNAME_ARR[] = "dmall:Nefertimon X";
    inline static constexpr const char* ALT_DMALL_NEFERTIMON_X_FQNAME = ALT_DMALL_NEFERTIMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_NEFERTIMON_X_FQNAME_LEN = sizeof(ALT_DMALL_NEFERTIMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_NEO_DEVIMON_FQID_ARR[] = "dmall:neo_devimon";
    inline static constexpr const char* ALT_DMALL_NEO_DEVIMON_FQID = ALT_DMALL_NEO_DEVIMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_NEO_DEVIMON_FQID_LEN = sizeof(ALT_DMALL_NEO_DEVIMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_NEO_DEVIMON_FQNAME_ARR[] = "dmall:Neo Devimon";
    inline static constexpr const char* ALT_DMALL_NEO_DEVIMON_FQNAME = ALT_DMALL_NEO_DEVIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_NEO_DEVIMON_FQNAME_LEN = sizeof(ALT_DMALL_NEO_DEVIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_NISE_DRIMOGEMON_FQID_ARR[] = "dmall:nise_drimogemon";
    inline static constexpr const char* ALT_DMALL_NISE_DRIMOGEMON_FQID = ALT_DMALL_NISE_DRIMOGEMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_NISE_DRIMOGEMON_FQID_LEN = sizeof(ALT_DMALL_NISE_DRIMOGEMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_NISE_DRIMOGEMON_FQNAME_ARR[] = "dmall:Nise Drimogemon";
    inline static constexpr const char* ALT_DMALL_NISE_DRIMOGEMON_FQNAME = ALT_DMALL_NISE_DRIMOGEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_NISE_DRIMOGEMON_FQNAME_LEN = sizeof(ALT_DMALL_NISE_DRIMOGEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_NOBLE_PUMPMON_FQID_ARR[] = "dmall:noble_pumpmon";
    inline static constexpr const char* ALT_DMALL_NOBLE_PUMPMON_FQID = ALT_DMALL_NOBLE_PUMPMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_NOBLE_PUMPMON_FQID_LEN = sizeof(ALT_DMALL_NOBLE_PUMPMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_NOBLE_PUMPMON_FQNAME_ARR[] = "dmall:Noble Pumpmon";
    inline static constexpr const char* ALT_DMALL_NOBLE_PUMPMON_FQNAME = ALT_DMALL_NOBLE_PUMPMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_NOBLE_PUMPMON_FQNAME_LEN = sizeof(ALT_DMALL_NOBLE_PUMPMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_NUMEMON_FQID_ARR[] = "dmall:numemon";
    inline static constexpr const char* ALT_DMALL_NUMEMON_FQID = ALT_DMALL_NUMEMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_NUMEMON_FQID_LEN = sizeof(ALT_DMALL_NUMEMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_NUMEMON_FQNAME_ARR[] = "dmall:Numemon";
    inline static constexpr const char* ALT_DMALL_NUMEMON_FQNAME = ALT_DMALL_NUMEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_NUMEMON_FQNAME_LEN = sizeof(ALT_DMALL_NUMEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_NUMEMON_X_FQID_ARR[] = "dmall:numemon_x";
    inline static constexpr const char* ALT_DMALL_NUMEMON_X_FQID = ALT_DMALL_NUMEMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_NUMEMON_X_FQID_LEN = sizeof(ALT_DMALL_NUMEMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_NUMEMON_X_FQNAME_ARR[] = "dmall:Numemon X";
    inline static constexpr const char* ALT_DMALL_NUMEMON_X_FQNAME = ALT_DMALL_NUMEMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_NUMEMON_X_FQNAME_LEN = sizeof(ALT_DMALL_NUMEMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_NYAROMON_FQID_ARR[] = "dmall:nyaromon";
    inline static constexpr const char* ALT_DMALL_NYAROMON_FQID = ALT_DMALL_NYAROMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_NYAROMON_FQID_LEN = sizeof(ALT_DMALL_NYAROMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_NYAROMON_FQNAME_ARR[] = "dmall:Nyaromon";
    inline static constexpr const char* ALT_DMALL_NYAROMON_FQNAME = ALT_DMALL_NYAROMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_NYAROMON_FQNAME_LEN = sizeof(ALT_DMALL_NYAROMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_NYOKIMON_FQID_ARR[] = "dmall:nyokimon";
    inline static constexpr const char* ALT_DMALL_NYOKIMON_FQID = ALT_DMALL_NYOKIMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_NYOKIMON_FQID_LEN = sizeof(ALT_DMALL_NYOKIMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_NYOKIMON_FQNAME_ARR[] = "dmall:Nyokimon";
    inline static constexpr const char* ALT_DMALL_NYOKIMON_FQNAME = ALT_DMALL_NYOKIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_NYOKIMON_FQNAME_LEN = sizeof(ALT_DMALL_NYOKIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_OFANIMON_CORE_FQID_ARR[] = "dmall:ofanimon_core";
    inline static constexpr const char* ALT_DMALL_OFANIMON_CORE_FQID = ALT_DMALL_OFANIMON_CORE_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_OFANIMON_CORE_FQID_LEN = sizeof(ALT_DMALL_OFANIMON_CORE_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_OFANIMON_CORE_FQNAME_ARR[] = "dmall:Ofanimon Core";
    inline static constexpr const char* ALT_DMALL_OFANIMON_CORE_FQNAME = ALT_DMALL_OFANIMON_CORE_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_OFANIMON_CORE_FQNAME_LEN = sizeof(ALT_DMALL_OFANIMON_CORE_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_OFANIMON_FALLDOWN_MODE_FQID_ARR[] = "dmall:ofanimon_falldown_mode";
    inline static constexpr const char* ALT_DMALL_OFANIMON_FALLDOWN_MODE_FQID = ALT_DMALL_OFANIMON_FALLDOWN_MODE_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_OFANIMON_FALLDOWN_MODE_FQID_LEN = sizeof(ALT_DMALL_OFANIMON_FALLDOWN_MODE_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_OFANIMON_FALLDOWN_MODE_FQNAME_ARR[] = "dmall:Ofanimon Falldown Mode";
    inline static constexpr const char* ALT_DMALL_OFANIMON_FALLDOWN_MODE_FQNAME = ALT_DMALL_OFANIMON_FALLDOWN_MODE_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_OFANIMON_FALLDOWN_MODE_FQNAME_LEN = sizeof(ALT_DMALL_OFANIMON_FALLDOWN_MODE_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_OGREMON_FQID_ARR[] = "dmall:ogremon";
    inline static constexpr const char* ALT_DMALL_OGREMON_FQID = ALT_DMALL_OGREMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_OGREMON_FQID_LEN = sizeof(ALT_DMALL_OGREMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_OGREMON_FQNAME_ARR[] = "dmall:Ogremon";
    inline static constexpr const char* ALT_DMALL_OGREMON_FQNAME = ALT_DMALL_OGREMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_OGREMON_FQNAME_LEN = sizeof(ALT_DMALL_OGREMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_OGREMON_X_FQID_ARR[] = "dmall:ogremon_x";
    inline static constexpr const char* ALT_DMALL_OGREMON_X_FQID = ALT_DMALL_OGREMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_OGREMON_X_FQID_LEN = sizeof(ALT_DMALL_OGREMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_OGREMON_X_FQNAME_ARR[] = "dmall:Ogremon X";
    inline static constexpr const char* ALT_DMALL_OGREMON_X_FQNAME = ALT_DMALL_OGREMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_OGREMON_X_FQNAME_LEN = sizeof(ALT_DMALL_OGREMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_OGUDOMON_FQID_ARR[] = "dmall:ogudomon";
    inline static constexpr const char* ALT_DMALL_OGUDOMON_FQID = ALT_DMALL_OGUDOMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_OGUDOMON_FQID_LEN = sizeof(ALT_DMALL_OGUDOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_OGUDOMON_FQNAME_ARR[] = "dmall:Ogudomon";
    inline static constexpr const char* ALT_DMALL_OGUDOMON_FQNAME = ALT_DMALL_OGUDOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_OGUDOMON_FQNAME_LEN = sizeof(ALT_DMALL_OGUDOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_OGUDOMON_X_FQID_ARR[] = "dmall:ogudomon_x";
    inline static constexpr const char* ALT_DMALL_OGUDOMON_X_FQID = ALT_DMALL_OGUDOMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_OGUDOMON_X_FQID_LEN = sizeof(ALT_DMALL_OGUDOMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_OGUDOMON_X_FQNAME_ARR[] = "dmall:Ogudomon X";
    inline static constexpr const char* ALT_DMALL_OGUDOMON_X_FQNAME = ALT_DMALL_OGUDOMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_OGUDOMON_X_FQNAME_LEN = sizeof(ALT_DMALL_OGUDOMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_OKUWAMON_FQID_ARR[] = "dmall:okuwamon";
    inline static constexpr const char* ALT_DMALL_OKUWAMON_FQID = ALT_DMALL_OKUWAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_OKUWAMON_FQID_LEN = sizeof(ALT_DMALL_OKUWAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_OKUWAMON_FQNAME_ARR[] = "dmall:Okuwamon";
    inline static constexpr const char* ALT_DMALL_OKUWAMON_FQNAME = ALT_DMALL_OKUWAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_OKUWAMON_FQNAME_LEN = sizeof(ALT_DMALL_OKUWAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_OKUWAMON_X_FQID_ARR[] = "dmall:okuwamon_x";
    inline static constexpr const char* ALT_DMALL_OKUWAMON_X_FQID = ALT_DMALL_OKUWAMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_OKUWAMON_X_FQID_LEN = sizeof(ALT_DMALL_OKUWAMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_OKUWAMON_X_FQNAME_ARR[] = "dmall:Okuwamon X";
    inline static constexpr const char* ALT_DMALL_OKUWAMON_X_FQNAME = ALT_DMALL_OKUWAMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_OKUWAMON_X_FQNAME_LEN = sizeof(ALT_DMALL_OKUWAMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_OMEGAMON_ALTER_S_FQID_ARR[] = "dmall:omegamon_alter_s";
    inline static constexpr const char* ALT_DMALL_OMEGAMON_ALTER_S_FQID = ALT_DMALL_OMEGAMON_ALTER_S_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_OMEGAMON_ALTER_S_FQID_LEN = sizeof(ALT_DMALL_OMEGAMON_ALTER_S_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_OMEGAMON_ALTER_S_FQNAME_ARR[] = "dmall:Omegamon Alter S";
    inline static constexpr const char* ALT_DMALL_OMEGAMON_ALTER_S_FQNAME = ALT_DMALL_OMEGAMON_ALTER_S_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_OMEGAMON_ALTER_S_FQNAME_LEN = sizeof(ALT_DMALL_OMEGAMON_ALTER_S_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_OMEGAMON_FQID_ARR[] = "dmall:omegamon";
    inline static constexpr const char* ALT_DMALL_OMEGAMON_FQID = ALT_DMALL_OMEGAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_OMEGAMON_FQID_LEN = sizeof(ALT_DMALL_OMEGAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_OMEGAMON_FQNAME_ARR[] = "dmall:Omegamon";
    inline static constexpr const char* ALT_DMALL_OMEGAMON_FQNAME = ALT_DMALL_OMEGAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_OMEGAMON_FQNAME_LEN = sizeof(ALT_DMALL_OMEGAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_OMEGAMON_X_FQID_ARR[] = "dmall:omegamon_x";
    inline static constexpr const char* ALT_DMALL_OMEGAMON_X_FQID = ALT_DMALL_OMEGAMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_OMEGAMON_X_FQID_LEN = sizeof(ALT_DMALL_OMEGAMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_OMEGAMON_X_FQNAME_ARR[] = "dmall:Omegamon X";
    inline static constexpr const char* ALT_DMALL_OMEGAMON_X_FQNAME = ALT_DMALL_OMEGAMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_OMEGAMON_X_FQNAME_LEN = sizeof(ALT_DMALL_OMEGAMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_OMEGAMON_ZWART_FQID_ARR[] = "dmall:omegamon_zwart";
    inline static constexpr const char* ALT_DMALL_OMEGAMON_ZWART_FQID = ALT_DMALL_OMEGAMON_ZWART_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_OMEGAMON_ZWART_FQID_LEN = sizeof(ALT_DMALL_OMEGAMON_ZWART_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_OMEGAMON_ZWART_FQNAME_ARR[] = "dmall:Omegamon Zwart";
    inline static constexpr const char* ALT_DMALL_OMEGAMON_ZWART_FQNAME = ALT_DMALL_OMEGAMON_ZWART_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_OMEGAMON_ZWART_FQNAME_LEN = sizeof(ALT_DMALL_OMEGAMON_ZWART_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_OMEGA_SHOUTMON_X_FQID_ARR[] = "dmall:omega_shoutmon_x";
    inline static constexpr const char* ALT_DMALL_OMEGA_SHOUTMON_X_FQID = ALT_DMALL_OMEGA_SHOUTMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_OMEGA_SHOUTMON_X_FQID_LEN = sizeof(ALT_DMALL_OMEGA_SHOUTMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_OMEGA_SHOUTMON_X_FQNAME_ARR[] = "dmall:Omega Shoutmon X";
    inline static constexpr const char* ALT_DMALL_OMEGA_SHOUTMON_X_FQNAME = ALT_DMALL_OMEGA_SHOUTMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_OMEGA_SHOUTMON_X_FQNAME_LEN = sizeof(ALT_DMALL_OMEGA_SHOUTMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_OMEKAMON_FQID_ARR[] = "dmall:omekamon";
    inline static constexpr const char* ALT_DMALL_OMEKAMON_FQID = ALT_DMALL_OMEKAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_OMEKAMON_FQID_LEN = sizeof(ALT_DMALL_OMEKAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_OMEKAMON_FQNAME_ARR[] = "dmall:Omekamon";
    inline static constexpr const char* ALT_DMALL_OMEKAMON_FQNAME = ALT_DMALL_OMEKAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_OMEKAMON_FQNAME_LEN = sizeof(ALT_DMALL_OMEKAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_OPHANIMON_FQID_ARR[] = "dmall:ophanimon";
    inline static constexpr const char* ALT_DMALL_OPHANIMON_FQID = ALT_DMALL_OPHANIMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_OPHANIMON_FQID_LEN = sizeof(ALT_DMALL_OPHANIMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_OPHANIMON_FQNAME_ARR[] = "dmall:Ophanimon";
    inline static constexpr const char* ALT_DMALL_OPHANIMON_FQNAME = ALT_DMALL_OPHANIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_OPHANIMON_FQNAME_LEN = sizeof(ALT_DMALL_OPHANIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_OPHANIMON_X_FQID_ARR[] = "dmall:ophanimon_x";
    inline static constexpr const char* ALT_DMALL_OPHANIMON_X_FQID = ALT_DMALL_OPHANIMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_OPHANIMON_X_FQID_LEN = sizeof(ALT_DMALL_OPHANIMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_OPHANIMON_X_FQNAME_ARR[] = "dmall:Ophanimon X";
    inline static constexpr const char* ALT_DMALL_OPHANIMON_X_FQNAME = ALT_DMALL_OPHANIMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_OPHANIMON_X_FQNAME_LEN = sizeof(ALT_DMALL_OPHANIMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_ORDINEMON_FQID_ARR[] = "dmall:ordinemon";
    inline static constexpr const char* ALT_DMALL_ORDINEMON_FQID = ALT_DMALL_ORDINEMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_ORDINEMON_FQID_LEN = sizeof(ALT_DMALL_ORDINEMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_ORDINEMON_FQNAME_ARR[] = "dmall:Ordinemon";
    inline static constexpr const char* ALT_DMALL_ORDINEMON_FQNAME = ALT_DMALL_ORDINEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_ORDINEMON_FQNAME_LEN = sizeof(ALT_DMALL_ORDINEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_OROCHIMON_FQID_ARR[] = "dmall:orochimon";
    inline static constexpr const char* ALT_DMALL_OROCHIMON_FQID = ALT_DMALL_OROCHIMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_OROCHIMON_FQID_LEN = sizeof(ALT_DMALL_OROCHIMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_OROCHIMON_FQNAME_ARR[] = "dmall:Orochimon";
    inline static constexpr const char* ALT_DMALL_OROCHIMON_FQNAME = ALT_DMALL_OROCHIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_OROCHIMON_FQNAME_LEN = sizeof(ALT_DMALL_OROCHIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_OTAMAMON_FQID_ARR[] = "dmall:otamamon";
    inline static constexpr const char* ALT_DMALL_OTAMAMON_FQID = ALT_DMALL_OTAMAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_OTAMAMON_FQID_LEN = sizeof(ALT_DMALL_OTAMAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_OTAMAMON_FQNAME_ARR[] = "dmall:Otamamon";
    inline static constexpr const char* ALT_DMALL_OTAMAMON_FQNAME = ALT_DMALL_OTAMAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_OTAMAMON_FQNAME_LEN = sizeof(ALT_DMALL_OTAMAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_OTAMAMON_RED_FQID_ARR[] = "dmall:otamamon_red";
    inline static constexpr const char* ALT_DMALL_OTAMAMON_RED_FQID = ALT_DMALL_OTAMAMON_RED_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_OTAMAMON_RED_FQID_LEN = sizeof(ALT_DMALL_OTAMAMON_RED_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_OTAMAMON_RED_FQNAME_ARR[] = "dmall:Otamamon (Red)";
    inline static constexpr const char* ALT_DMALL_OTAMAMON_RED_FQNAME = ALT_DMALL_OTAMAMON_RED_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_OTAMAMON_RED_FQNAME_LEN = sizeof(ALT_DMALL_OTAMAMON_RED_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_OTAMAMON_X_FQID_ARR[] = "dmall:otamamon_x";
    inline static constexpr const char* ALT_DMALL_OTAMAMON_X_FQID = ALT_DMALL_OTAMAMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_OTAMAMON_X_FQID_LEN = sizeof(ALT_DMALL_OTAMAMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_OTAMAMON_X_FQNAME_ARR[] = "dmall:Otamamon X";
    inline static constexpr const char* ALT_DMALL_OTAMAMON_X_FQNAME = ALT_DMALL_OTAMAMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_OTAMAMON_X_FQNAME_LEN = sizeof(ALT_DMALL_OTAMAMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_OURYUMON_FQID_ARR[] = "dmall:ouryumon";
    inline static constexpr const char* ALT_DMALL_OURYUMON_FQID = ALT_DMALL_OURYUMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_OURYUMON_FQID_LEN = sizeof(ALT_DMALL_OURYUMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_OURYUMON_FQNAME_ARR[] = "dmall:Ouryumon";
    inline static constexpr const char* ALT_DMALL_OURYUMON_FQNAME = ALT_DMALL_OURYUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_OURYUMON_FQNAME_LEN = sizeof(ALT_DMALL_OURYUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_PAFUMON_FQID_ARR[] = "dmall:pafumon";
    inline static constexpr const char* ALT_DMALL_PAFUMON_FQID = ALT_DMALL_PAFUMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_PAFUMON_FQID_LEN = sizeof(ALT_DMALL_PAFUMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_PAFUMON_FQNAME_ARR[] = "dmall:Pafumon";
    inline static constexpr const char* ALT_DMALL_PAFUMON_FQNAME = ALT_DMALL_PAFUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_PAFUMON_FQNAME_LEN = sizeof(ALT_DMALL_PAFUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_PAGUMON_FQID_ARR[] = "dmall:pagumon";
    inline static constexpr const char* ALT_DMALL_PAGUMON_FQID = ALT_DMALL_PAGUMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_PAGUMON_FQID_LEN = sizeof(ALT_DMALL_PAGUMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_PAGUMON_FQNAME_ARR[] = "dmall:Pagumon";
    inline static constexpr const char* ALT_DMALL_PAGUMON_FQNAME = ALT_DMALL_PAGUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_PAGUMON_FQNAME_LEN = sizeof(ALT_DMALL_PAGUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_PAILDRAMON_FQID_ARR[] = "dmall:paildramon";
    inline static constexpr const char* ALT_DMALL_PAILDRAMON_FQID = ALT_DMALL_PAILDRAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_PAILDRAMON_FQID_LEN = sizeof(ALT_DMALL_PAILDRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_PAILDRAMON_FQNAME_ARR[] = "dmall:Paildramon";
    inline static constexpr const char* ALT_DMALL_PAILDRAMON_FQNAME = ALT_DMALL_PAILDRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_PAILDRAMON_FQNAME_LEN = sizeof(ALT_DMALL_PAILDRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_PALEDRAMON_FQID_ARR[] = "dmall:paledramon";
    inline static constexpr const char* ALT_DMALL_PALEDRAMON_FQID = ALT_DMALL_PALEDRAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_PALEDRAMON_FQID_LEN = sizeof(ALT_DMALL_PALEDRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_PALEDRAMON_FQNAME_ARR[] = "dmall:Paledramon";
    inline static constexpr const char* ALT_DMALL_PALEDRAMON_FQNAME = ALT_DMALL_PALEDRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_PALEDRAMON_FQNAME_LEN = sizeof(ALT_DMALL_PALEDRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_PALMON_FQID_ARR[] = "dmall:palmon";
    inline static constexpr const char* ALT_DMALL_PALMON_FQID = ALT_DMALL_PALMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_PALMON_FQID_LEN = sizeof(ALT_DMALL_PALMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_PALMON_FQNAME_ARR[] = "dmall:Palmon";
    inline static constexpr const char* ALT_DMALL_PALMON_FQNAME = ALT_DMALL_PALMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_PALMON_FQNAME_LEN = sizeof(ALT_DMALL_PALMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_PALMON_X_FQID_ARR[] = "dmall:palmon_x";
    inline static constexpr const char* ALT_DMALL_PALMON_X_FQID = ALT_DMALL_PALMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_PALMON_X_FQID_LEN = sizeof(ALT_DMALL_PALMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_PALMON_X_FQNAME_ARR[] = "dmall:Palmon X";
    inline static constexpr const char* ALT_DMALL_PALMON_X_FQNAME = ALT_DMALL_PALMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_PALMON_X_FQNAME_LEN = sizeof(ALT_DMALL_PALMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_PANDAMON_FQID_ARR[] = "dmall:pandamon";
    inline static constexpr const char* ALT_DMALL_PANDAMON_FQID = ALT_DMALL_PANDAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_PANDAMON_FQID_LEN = sizeof(ALT_DMALL_PANDAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_PANDAMON_FQNAME_ARR[] = "dmall:Pandamon";
    inline static constexpr const char* ALT_DMALL_PANDAMON_FQNAME = ALT_DMALL_PANDAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_PANDAMON_FQNAME_LEN = sizeof(ALT_DMALL_PANDAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_PANJYAMON_FQID_ARR[] = "dmall:panjyamon";
    inline static constexpr const char* ALT_DMALL_PANJYAMON_FQID = ALT_DMALL_PANJYAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_PANJYAMON_FQID_LEN = sizeof(ALT_DMALL_PANJYAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_PANJYAMON_FQNAME_ARR[] = "dmall:Panjyamon";
    inline static constexpr const char* ALT_DMALL_PANJYAMON_FQNAME = ALT_DMALL_PANJYAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_PANJYAMON_FQNAME_LEN = sizeof(ALT_DMALL_PANJYAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_PANJYAMON_X_FQID_ARR[] = "dmall:panjyamon_x";
    inline static constexpr const char* ALT_DMALL_PANJYAMON_X_FQID = ALT_DMALL_PANJYAMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_PANJYAMON_X_FQID_LEN = sizeof(ALT_DMALL_PANJYAMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_PANJYAMON_X_FQNAME_ARR[] = "dmall:Panjyamon X";
    inline static constexpr const char* ALT_DMALL_PANJYAMON_X_FQNAME = ALT_DMALL_PANJYAMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_PANJYAMON_X_FQNAME_LEN = sizeof(ALT_DMALL_PANJYAMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_PAOMON_FQID_ARR[] = "dmall:paomon";
    inline static constexpr const char* ALT_DMALL_PAOMON_FQID = ALT_DMALL_PAOMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_PAOMON_FQID_LEN = sizeof(ALT_DMALL_PAOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_PAOMON_FQNAME_ARR[] = "dmall:Paomon";
    inline static constexpr const char* ALT_DMALL_PAOMON_FQNAME = ALT_DMALL_PAOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_PAOMON_FQNAME_LEN = sizeof(ALT_DMALL_PAOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_PARASAURMON_FQID_ARR[] = "dmall:parasaurmon";
    inline static constexpr const char* ALT_DMALL_PARASAURMON_FQID = ALT_DMALL_PARASAURMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_PARASAURMON_FQID_LEN = sizeof(ALT_DMALL_PARASAURMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_PARASAURMON_FQNAME_ARR[] = "dmall:Parasaurmon";
    inline static constexpr const char* ALT_DMALL_PARASAURMON_FQNAME = ALT_DMALL_PARASAURMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_PARASAURMON_FQNAME_LEN = sizeof(ALT_DMALL_PARASAURMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_PEGASMON_X_FQID_ARR[] = "dmall:pegasmon_x";
    inline static constexpr const char* ALT_DMALL_PEGASMON_X_FQID = ALT_DMALL_PEGASMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_PEGASMON_X_FQID_LEN = sizeof(ALT_DMALL_PEGASMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_PEGASMON_X_FQNAME_ARR[] = "dmall:Pegasmon X";
    inline static constexpr const char* ALT_DMALL_PEGASMON_X_FQNAME = ALT_DMALL_PEGASMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_PEGASMON_X_FQNAME_LEN = sizeof(ALT_DMALL_PEGASMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_PENMON_FQID_ARR[] = "dmall:penmon";
    inline static constexpr const char* ALT_DMALL_PENMON_FQID = ALT_DMALL_PENMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_PENMON_FQID_LEN = sizeof(ALT_DMALL_PENMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_PENMON_FQNAME_ARR[] = "dmall:Penmon";
    inline static constexpr const char* ALT_DMALL_PENMON_FQNAME = ALT_DMALL_PENMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_PENMON_FQNAME_LEN = sizeof(ALT_DMALL_PENMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_PETIMERAMON_FQID_ARR[] = "dmall:petimeramon";
    inline static constexpr const char* ALT_DMALL_PETIMERAMON_FQID = ALT_DMALL_PETIMERAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_PETIMERAMON_FQID_LEN = sizeof(ALT_DMALL_PETIMERAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_PETIMERAMON_FQNAME_ARR[] = "dmall:PetiMeramon";
    inline static constexpr const char* ALT_DMALL_PETIMERAMON_FQNAME = ALT_DMALL_PETIMERAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_PETIMERAMON_FQNAME_LEN = sizeof(ALT_DMALL_PETIMERAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_PETITMAMON_FQID_ARR[] = "dmall:petitmamon";
    inline static constexpr const char* ALT_DMALL_PETITMAMON_FQID = ALT_DMALL_PETITMAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_PETITMAMON_FQID_LEN = sizeof(ALT_DMALL_PETITMAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_PETITMAMON_FQNAME_ARR[] = "dmall:PetitMamon";
    inline static constexpr const char* ALT_DMALL_PETITMAMON_FQNAME = ALT_DMALL_PETITMAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_PETITMAMON_FQNAME_LEN = sizeof(ALT_DMALL_PETITMAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_PETITMON_FQID_ARR[] = "dmall:petitmon";
    inline static constexpr const char* ALT_DMALL_PETITMON_FQID = ALT_DMALL_PETITMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_PETITMON_FQID_LEN = sizeof(ALT_DMALL_PETITMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_PETITMON_FQNAME_ARR[] = "dmall:Petitmon";
    inline static constexpr const char* ALT_DMALL_PETITMON_FQNAME = ALT_DMALL_PETITMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_PETITMON_FQNAME_LEN = sizeof(ALT_DMALL_PETITMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_PHANTOMON_FQID_ARR[] = "dmall:phantomon";
    inline static constexpr const char* ALT_DMALL_PHANTOMON_FQID = ALT_DMALL_PHANTOMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_PHANTOMON_FQID_LEN = sizeof(ALT_DMALL_PHANTOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_PHANTOMON_FQNAME_ARR[] = "dmall:Phantomon";
    inline static constexpr const char* ALT_DMALL_PHANTOMON_FQNAME = ALT_DMALL_PHANTOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_PHANTOMON_FQNAME_LEN = sizeof(ALT_DMALL_PHANTOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_PHASCOMON_FQID_ARR[] = "dmall:phascomon";
    inline static constexpr const char* ALT_DMALL_PHASCOMON_FQID = ALT_DMALL_PHASCOMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_PHASCOMON_FQID_LEN = sizeof(ALT_DMALL_PHASCOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_PHASCOMON_FQNAME_ARR[] = "dmall:Phascomon";
    inline static constexpr const char* ALT_DMALL_PHASCOMON_FQNAME = ALT_DMALL_PHASCOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_PHASCOMON_FQNAME_LEN = sizeof(ALT_DMALL_PHASCOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_PICCOLOMON_FQID_ARR[] = "dmall:piccolomon";
    inline static constexpr const char* ALT_DMALL_PICCOLOMON_FQID = ALT_DMALL_PICCOLOMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_PICCOLOMON_FQID_LEN = sizeof(ALT_DMALL_PICCOLOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_PICCOLOMON_FQNAME_ARR[] = "dmall:Piccolomon";
    inline static constexpr const char* ALT_DMALL_PICCOLOMON_FQNAME = ALT_DMALL_PICCOLOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_PICCOLOMON_FQNAME_LEN = sizeof(ALT_DMALL_PICCOLOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_PICKMON_FQID_ARR[] = "dmall:pickmon";
    inline static constexpr const char* ALT_DMALL_PICKMON_FQID = ALT_DMALL_PICKMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_PICKMON_FQID_LEN = sizeof(ALT_DMALL_PICKMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_PICKMON_FQNAME_ARR[] = "dmall:Pickmon";
    inline static constexpr const char* ALT_DMALL_PICKMON_FQNAME = ALT_DMALL_PICKMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_PICKMON_FQNAME_LEN = sizeof(ALT_DMALL_PICKMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_PICO_DEVIMON_FQID_ARR[] = "dmall:pico_devimon";
    inline static constexpr const char* ALT_DMALL_PICO_DEVIMON_FQID = ALT_DMALL_PICO_DEVIMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_PICO_DEVIMON_FQID_LEN = sizeof(ALT_DMALL_PICO_DEVIMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_PICO_DEVIMON_FQNAME_ARR[] = "dmall:Pico Devimon";
    inline static constexpr const char* ALT_DMALL_PICO_DEVIMON_FQNAME = ALT_DMALL_PICO_DEVIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_PICO_DEVIMON_FQNAME_LEN = sizeof(ALT_DMALL_PICO_DEVIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_PIDMON_FQID_ARR[] = "dmall:pidmon";
    inline static constexpr const char* ALT_DMALL_PIDMON_FQID = ALT_DMALL_PIDMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_PIDMON_FQID_LEN = sizeof(ALT_DMALL_PIDMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_PIDMON_FQNAME_ARR[] = "dmall:Pidmon";
    inline static constexpr const char* ALT_DMALL_PIDMON_FQNAME = ALT_DMALL_PIDMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_PIDMON_FQNAME_LEN = sizeof(ALT_DMALL_PIDMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_PIEMON_FQID_ARR[] = "dmall:piemon";
    inline static constexpr const char* ALT_DMALL_PIEMON_FQID = ALT_DMALL_PIEMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_PIEMON_FQID_LEN = sizeof(ALT_DMALL_PIEMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_PIEMON_FQNAME_ARR[] = "dmall:Piemon";
    inline static constexpr const char* ALT_DMALL_PIEMON_FQNAME = ALT_DMALL_PIEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_PIEMON_FQNAME_LEN = sizeof(ALT_DMALL_PIEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_PINOCHIMON_FQID_ARR[] = "dmall:pinochimon";
    inline static constexpr const char* ALT_DMALL_PINOCHIMON_FQID = ALT_DMALL_PINOCHIMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_PINOCHIMON_FQID_LEN = sizeof(ALT_DMALL_PINOCHIMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_PINOCHIMON_FQNAME_ARR[] = "dmall:Pinochimon";
    inline static constexpr const char* ALT_DMALL_PINOCHIMON_FQNAME = ALT_DMALL_PINOCHIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_PINOCHIMON_FQNAME_LEN = sizeof(ALT_DMALL_PINOCHIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_PIPIMON_FQID_ARR[] = "dmall:pipimon";
    inline static constexpr const char* ALT_DMALL_PIPIMON_FQID = ALT_DMALL_PIPIMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_PIPIMON_FQID_LEN = sizeof(ALT_DMALL_PIPIMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_PIPIMON_FQNAME_ARR[] = "dmall:Pipimon";
    inline static constexpr const char* ALT_DMALL_PIPIMON_FQNAME = ALT_DMALL_PIPIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_PIPIMON_FQNAME_LEN = sizeof(ALT_DMALL_PIPIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_PIRANIMON_FQID_ARR[] = "dmall:piranimon";
    inline static constexpr const char* ALT_DMALL_PIRANIMON_FQID = ALT_DMALL_PIRANIMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_PIRANIMON_FQID_LEN = sizeof(ALT_DMALL_PIRANIMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_PIRANIMON_FQNAME_ARR[] = "dmall:Piranimon";
    inline static constexpr const char* ALT_DMALL_PIRANIMON_FQNAME = ALT_DMALL_PIRANIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_PIRANIMON_FQNAME_LEN = sizeof(ALT_DMALL_PIRANIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_PITCHMON_FQID_ARR[] = "dmall:pitchmon";
    inline static constexpr const char* ALT_DMALL_PITCHMON_FQID = ALT_DMALL_PITCHMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_PITCHMON_FQID_LEN = sizeof(ALT_DMALL_PITCHMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_PITCHMON_FQNAME_ARR[] = "dmall:Pitchmon";
    inline static constexpr const char* ALT_DMALL_PITCHMON_FQNAME = ALT_DMALL_PITCHMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_PITCHMON_FQNAME_LEN = sizeof(ALT_DMALL_PITCHMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_PIYOMON_FQID_ARR[] = "dmall:piyomon";
    inline static constexpr const char* ALT_DMALL_PIYOMON_FQID = ALT_DMALL_PIYOMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_PIYOMON_FQID_LEN = sizeof(ALT_DMALL_PIYOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_PIYOMON_FQNAME_ARR[] = "dmall:Piyomon";
    inline static constexpr const char* ALT_DMALL_PIYOMON_FQNAME = ALT_DMALL_PIYOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_PIYOMON_FQNAME_LEN = sizeof(ALT_DMALL_PIYOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_PLATINUM_NUMEMON_FQID_ARR[] = "dmall:platinum_numemon";
    inline static constexpr const char* ALT_DMALL_PLATINUM_NUMEMON_FQID = ALT_DMALL_PLATINUM_NUMEMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_PLATINUM_NUMEMON_FQID_LEN = sizeof(ALT_DMALL_PLATINUM_NUMEMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_PLATINUM_NUMEMON_FQNAME_ARR[] = "dmall:Platinum Numemon";
    inline static constexpr const char* ALT_DMALL_PLATINUM_NUMEMON_FQNAME = ALT_DMALL_PLATINUM_NUMEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_PLATINUM_NUMEMON_FQNAME_LEN = sizeof(ALT_DMALL_PLATINUM_NUMEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_PLATINUM_SCUMON_FQID_ARR[] = "dmall:platinum_scumon";
    inline static constexpr const char* ALT_DMALL_PLATINUM_SCUMON_FQID = ALT_DMALL_PLATINUM_SCUMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_PLATINUM_SCUMON_FQID_LEN = sizeof(ALT_DMALL_PLATINUM_SCUMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_PLATINUM_SCUMON_FQNAME_ARR[] = "dmall:Platinum Scumon";
    inline static constexpr const char* ALT_DMALL_PLATINUM_SCUMON_FQNAME = ALT_DMALL_PLATINUM_SCUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_PLATINUM_SCUMON_FQNAME_LEN = sizeof(ALT_DMALL_PLATINUM_SCUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_PLESIOMON_FQID_ARR[] = "dmall:plesiomon";
    inline static constexpr const char* ALT_DMALL_PLESIOMON_FQID = ALT_DMALL_PLESIOMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_PLESIOMON_FQID_LEN = sizeof(ALT_DMALL_PLESIOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_PLESIOMON_FQNAME_ARR[] = "dmall:Plesiomon";
    inline static constexpr const char* ALT_DMALL_PLESIOMON_FQNAME = ALT_DMALL_PLESIOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_PLESIOMON_FQNAME_LEN = sizeof(ALT_DMALL_PLESIOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_PLESIOMON_X_FQID_ARR[] = "dmall:plesiomon_x";
    inline static constexpr const char* ALT_DMALL_PLESIOMON_X_FQID = ALT_DMALL_PLESIOMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_PLESIOMON_X_FQID_LEN = sizeof(ALT_DMALL_PLESIOMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_PLESIOMON_X_FQNAME_ARR[] = "dmall:Plesiomon X";
    inline static constexpr const char* ALT_DMALL_PLESIOMON_X_FQNAME = ALT_DMALL_PLESIOMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_PLESIOMON_X_FQNAME_LEN = sizeof(ALT_DMALL_PLESIOMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_PLOTMON_FQID_ARR[] = "dmall:plotmon";
    inline static constexpr const char* ALT_DMALL_PLOTMON_FQID = ALT_DMALL_PLOTMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_PLOTMON_FQID_LEN = sizeof(ALT_DMALL_PLOTMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_PLOTMON_FQNAME_ARR[] = "dmall:Plotmon";
    inline static constexpr const char* ALT_DMALL_PLOTMON_FQNAME = ALT_DMALL_PLOTMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_PLOTMON_FQNAME_LEN = sizeof(ALT_DMALL_PLOTMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_PLOTMON_X_FQID_ARR[] = "dmall:plotmon_x";
    inline static constexpr const char* ALT_DMALL_PLOTMON_X_FQID = ALT_DMALL_PLOTMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_PLOTMON_X_FQID_LEN = sizeof(ALT_DMALL_PLOTMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_PLOTMON_X_FQNAME_ARR[] = "dmall:Plotmon X";
    inline static constexpr const char* ALT_DMALL_PLOTMON_X_FQNAME = ALT_DMALL_PLOTMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_PLOTMON_X_FQNAME_LEN = sizeof(ALT_DMALL_PLOTMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_POKOMON_FQID_ARR[] = "dmall:pokomon";
    inline static constexpr const char* ALT_DMALL_POKOMON_FQID = ALT_DMALL_POKOMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_POKOMON_FQID_LEN = sizeof(ALT_DMALL_POKOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_POKOMON_FQNAME_ARR[] = "dmall:Pokomon";
    inline static constexpr const char* ALT_DMALL_POKOMON_FQNAME = ALT_DMALL_POKOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_POKOMON_FQNAME_LEN = sizeof(ALT_DMALL_POKOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_POPOMON_FQID_ARR[] = "dmall:popomon";
    inline static constexpr const char* ALT_DMALL_POPOMON_FQID = ALT_DMALL_POPOMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_POPOMON_FQID_LEN = sizeof(ALT_DMALL_POPOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_POPOMON_FQNAME_ARR[] = "dmall:Popomon";
    inline static constexpr const char* ALT_DMALL_POPOMON_FQNAME = ALT_DMALL_POPOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_POPOMON_FQNAME_LEN = sizeof(ALT_DMALL_POPOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_PORCUPAMON_FQID_ARR[] = "dmall:porcupamon";
    inline static constexpr const char* ALT_DMALL_PORCUPAMON_FQID = ALT_DMALL_PORCUPAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_PORCUPAMON_FQID_LEN = sizeof(ALT_DMALL_PORCUPAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_PORCUPAMON_FQNAME_ARR[] = "dmall:Porcupamon";
    inline static constexpr const char* ALT_DMALL_PORCUPAMON_FQNAME = ALT_DMALL_PORCUPAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_PORCUPAMON_FQNAME_LEN = sizeof(ALT_DMALL_PORCUPAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_POROMON_FQID_ARR[] = "dmall:poromon";
    inline static constexpr const char* ALT_DMALL_POROMON_FQID = ALT_DMALL_POROMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_POROMON_FQID_LEN = sizeof(ALT_DMALL_POROMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_POROMON_FQNAME_ARR[] = "dmall:Poromon";
    inline static constexpr const char* ALT_DMALL_POROMON_FQNAME = ALT_DMALL_POROMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_POROMON_FQNAME_LEN = sizeof(ALT_DMALL_POROMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_PRINCE_MAMEMON_FQID_ARR[] = "dmall:prince_mamemon";
    inline static constexpr const char* ALT_DMALL_PRINCE_MAMEMON_FQID = ALT_DMALL_PRINCE_MAMEMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_PRINCE_MAMEMON_FQID_LEN = sizeof(ALT_DMALL_PRINCE_MAMEMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_PRINCE_MAMEMON_FQNAME_ARR[] = "dmall:Prince Mamemon";
    inline static constexpr const char* ALT_DMALL_PRINCE_MAMEMON_FQNAME = ALT_DMALL_PRINCE_MAMEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_PRINCE_MAMEMON_FQNAME_LEN = sizeof(ALT_DMALL_PRINCE_MAMEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_PRINCE_MAMEMON_X_FQID_ARR[] = "dmall:prince_mamemon_x";
    inline static constexpr const char* ALT_DMALL_PRINCE_MAMEMON_X_FQID = ALT_DMALL_PRINCE_MAMEMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_PRINCE_MAMEMON_X_FQID_LEN = sizeof(ALT_DMALL_PRINCE_MAMEMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_PRINCE_MAMEMON_X_FQNAME_ARR[] = "dmall:Prince Mamemon X";
    inline static constexpr const char* ALT_DMALL_PRINCE_MAMEMON_X_FQNAME = ALT_DMALL_PRINCE_MAMEMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_PRINCE_MAMEMON_X_FQNAME_LEN = sizeof(ALT_DMALL_PRINCE_MAMEMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_PTERANOMON_X_FQID_ARR[] = "dmall:pteranomon_x";
    inline static constexpr const char* ALT_DMALL_PTERANOMON_X_FQID = ALT_DMALL_PTERANOMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_PTERANOMON_X_FQID_LEN = sizeof(ALT_DMALL_PTERANOMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_PTERANOMON_X_FQNAME_ARR[] = "dmall:Pteranomon X";
    inline static constexpr const char* ALT_DMALL_PTERANOMON_X_FQNAME = ALT_DMALL_PTERANOMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_PTERANOMON_X_FQNAME_LEN = sizeof(ALT_DMALL_PTERANOMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_PUKAMON_FQID_ARR[] = "dmall:pukamon";
    inline static constexpr const char* ALT_DMALL_PUKAMON_FQID = ALT_DMALL_PUKAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_PUKAMON_FQID_LEN = sizeof(ALT_DMALL_PUKAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_PUKAMON_FQNAME_ARR[] = "dmall:Pukamon";
    inline static constexpr const char* ALT_DMALL_PUKAMON_FQNAME = ALT_DMALL_PUKAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_PUKAMON_FQNAME_LEN = sizeof(ALT_DMALL_PUKAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_PUKUMON_FQID_ARR[] = "dmall:pukumon";
    inline static constexpr const char* ALT_DMALL_PUKUMON_FQID = ALT_DMALL_PUKUMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_PUKUMON_FQID_LEN = sizeof(ALT_DMALL_PUKUMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_PUKUMON_FQNAME_ARR[] = "dmall:Pukumon";
    inline static constexpr const char* ALT_DMALL_PUKUMON_FQNAME = ALT_DMALL_PUKUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_PUKUMON_FQNAME_LEN = sizeof(ALT_DMALL_PUKUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_PULSEMON_FQID_ARR[] = "dmall:pulsemon";
    inline static constexpr const char* ALT_DMALL_PULSEMON_FQID = ALT_DMALL_PULSEMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_PULSEMON_FQID_LEN = sizeof(ALT_DMALL_PULSEMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_PULSEMON_FQNAME_ARR[] = "dmall:Pulsemon";
    inline static constexpr const char* ALT_DMALL_PULSEMON_FQNAME = ALT_DMALL_PULSEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_PULSEMON_FQNAME_LEN = sizeof(ALT_DMALL_PULSEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_PUMPMON_FQID_ARR[] = "dmall:pumpmon";
    inline static constexpr const char* ALT_DMALL_PUMPMON_FQID = ALT_DMALL_PUMPMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_PUMPMON_FQID_LEN = sizeof(ALT_DMALL_PUMPMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_PUMPMON_FQNAME_ARR[] = "dmall:Pumpmon";
    inline static constexpr const char* ALT_DMALL_PUMPMON_FQNAME = ALT_DMALL_PUMPMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_PUMPMON_FQNAME_LEN = sizeof(ALT_DMALL_PUMPMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_PUPUMON_FQID_ARR[] = "dmall:pupumon";
    inline static constexpr const char* ALT_DMALL_PUPUMON_FQID = ALT_DMALL_PUPUMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_PUPUMON_FQID_LEN = sizeof(ALT_DMALL_PUPUMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_PUPUMON_FQNAME_ARR[] = "dmall:Pupumon";
    inline static constexpr const char* ALT_DMALL_PUPUMON_FQNAME = ALT_DMALL_PUPUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_PUPUMON_FQNAME_LEN = sizeof(ALT_DMALL_PUPUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_PUROROMON_FQID_ARR[] = "dmall:puroromon";
    inline static constexpr const char* ALT_DMALL_PUROROMON_FQID = ALT_DMALL_PUROROMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_PUROROMON_FQID_LEN = sizeof(ALT_DMALL_PUROROMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_PUROROMON_FQNAME_ARR[] = "dmall:Puroromon";
    inline static constexpr const char* ALT_DMALL_PUROROMON_FQNAME = ALT_DMALL_PUROROMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_PUROROMON_FQNAME_LEN = sizeof(ALT_DMALL_PUROROMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_PURURUMON_FQID_ARR[] = "dmall:pururumon";
    inline static constexpr const char* ALT_DMALL_PURURUMON_FQID = ALT_DMALL_PURURUMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_PURURUMON_FQID_LEN = sizeof(ALT_DMALL_PURURUMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_PURURUMON_FQNAME_ARR[] = "dmall:Pururumon";
    inline static constexpr const char* ALT_DMALL_PURURUMON_FQNAME = ALT_DMALL_PURURUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_PURURUMON_FQNAME_LEN = sizeof(ALT_DMALL_PURURUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_PUSUMON_FQID_ARR[] = "dmall:pusumon";
    inline static constexpr const char* ALT_DMALL_PUSUMON_FQID = ALT_DMALL_PUSUMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_PUSUMON_FQID_LEN = sizeof(ALT_DMALL_PUSUMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_PUSUMON_FQNAME_ARR[] = "dmall:Pusumon";
    inline static constexpr const char* ALT_DMALL_PUSUMON_FQNAME = ALT_DMALL_PUSUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_PUSUMON_FQNAME_LEN = sizeof(ALT_DMALL_PUSUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_PUSURIMON_FQID_ARR[] = "dmall:pusurimon";
    inline static constexpr const char* ALT_DMALL_PUSURIMON_FQID = ALT_DMALL_PUSURIMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_PUSURIMON_FQID_LEN = sizeof(ALT_DMALL_PUSURIMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_PUSURIMON_FQNAME_ARR[] = "dmall:Pusurimon";
    inline static constexpr const char* ALT_DMALL_PUSURIMON_FQNAME = ALT_DMALL_PUSURIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_PUSURIMON_FQNAME_LEN = sizeof(ALT_DMALL_PUSURIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_PUTTIMON_FQID_ARR[] = "dmall:puttimon";
    inline static constexpr const char* ALT_DMALL_PUTTIMON_FQID = ALT_DMALL_PUTTIMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_PUTTIMON_FQID_LEN = sizeof(ALT_DMALL_PUTTIMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_PUTTIMON_FQNAME_ARR[] = "dmall:Puttimon";
    inline static constexpr const char* ALT_DMALL_PUTTIMON_FQNAME = ALT_DMALL_PUTTIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_PUTTIMON_FQNAME_LEN = sizeof(ALT_DMALL_PUTTIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_PUYOMON_FQID_ARR[] = "dmall:puyomon";
    inline static constexpr const char* ALT_DMALL_PUYOMON_FQID = ALT_DMALL_PUYOMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_PUYOMON_FQID_LEN = sizeof(ALT_DMALL_PUYOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_PUYOMON_FQNAME_ARR[] = "dmall:Puyomon";
    inline static constexpr const char* ALT_DMALL_PUYOMON_FQNAME = ALT_DMALL_PUYOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_PUYOMON_FQNAME_LEN = sizeof(ALT_DMALL_PUYOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_PYOCOMON_FQID_ARR[] = "dmall:pyocomon";
    inline static constexpr const char* ALT_DMALL_PYOCOMON_FQID = ALT_DMALL_PYOCOMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_PYOCOMON_FQID_LEN = sizeof(ALT_DMALL_PYOCOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_PYOCOMON_FQNAME_ARR[] = "dmall:Pyocomon";
    inline static constexpr const char* ALT_DMALL_PYOCOMON_FQNAME = ALT_DMALL_PYOCOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_PYOCOMON_FQNAME_LEN = sizeof(ALT_DMALL_PYOCOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_PYONMON_FQID_ARR[] = "dmall:pyonmon";
    inline static constexpr const char* ALT_DMALL_PYONMON_FQID = ALT_DMALL_PYONMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_PYONMON_FQID_LEN = sizeof(ALT_DMALL_PYONMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_PYONMON_FQNAME_ARR[] = "dmall:Pyonmon";
    inline static constexpr const char* ALT_DMALL_PYONMON_FQNAME = ALT_DMALL_PYONMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_PYONMON_FQNAME_LEN = sizeof(ALT_DMALL_PYONMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_RAFFLESIMON_FQID_ARR[] = "dmall:rafflesimon";
    inline static constexpr const char* ALT_DMALL_RAFFLESIMON_FQID = ALT_DMALL_RAFFLESIMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_RAFFLESIMON_FQID_LEN = sizeof(ALT_DMALL_RAFFLESIMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_RAFFLESIMON_FQNAME_ARR[] = "dmall:Rafflesimon";
    inline static constexpr const char* ALT_DMALL_RAFFLESIMON_FQNAME = ALT_DMALL_RAFFLESIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_RAFFLESIMON_FQNAME_LEN = sizeof(ALT_DMALL_RAFFLESIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_RAGNA_LORDMON_FQID_ARR[] = "dmall:ragna_lordmon";
    inline static constexpr const char* ALT_DMALL_RAGNA_LORDMON_FQID = ALT_DMALL_RAGNA_LORDMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_RAGNA_LORDMON_FQID_LEN = sizeof(ALT_DMALL_RAGNA_LORDMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_RAGNA_LORDMON_FQNAME_ARR[] = "dmall:Ragna Lordmon";
    inline static constexpr const char* ALT_DMALL_RAGNA_LORDMON_FQNAME = ALT_DMALL_RAGNA_LORDMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_RAGNA_LORDMON_FQNAME_LEN = sizeof(ALT_DMALL_RAGNA_LORDMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_RAGUELMON_FQID_ARR[] = "dmall:raguelmon";
    inline static constexpr const char* ALT_DMALL_RAGUELMON_FQID = ALT_DMALL_RAGUELMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_RAGUELMON_FQID_LEN = sizeof(ALT_DMALL_RAGUELMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_RAGUELMON_FQNAME_ARR[] = "dmall:Raguelmon";
    inline static constexpr const char* ALT_DMALL_RAGUELMON_FQNAME = ALT_DMALL_RAGUELMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_RAGUELMON_FQNAME_LEN = sizeof(ALT_DMALL_RAGUELMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_RAIDENMON_FQID_ARR[] = "dmall:raidenmon";
    inline static constexpr const char* ALT_DMALL_RAIDENMON_FQID = ALT_DMALL_RAIDENMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_RAIDENMON_FQID_LEN = sizeof(ALT_DMALL_RAIDENMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_RAIDENMON_FQNAME_ARR[] = "dmall:Raidenmon";
    inline static constexpr const char* ALT_DMALL_RAIDENMON_FQNAME = ALT_DMALL_RAIDENMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_RAIDENMON_FQNAME_LEN = sizeof(ALT_DMALL_RAIDENMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_RAIHIMON_FQID_ARR[] = "dmall:raihimon";
    inline static constexpr const char* ALT_DMALL_RAIHIMON_FQID = ALT_DMALL_RAIHIMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_RAIHIMON_FQID_LEN = sizeof(ALT_DMALL_RAIHIMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_RAIHIMON_FQNAME_ARR[] = "dmall:Raihimon";
    inline static constexpr const char* ALT_DMALL_RAIHIMON_FQNAME = ALT_DMALL_RAIHIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_RAIHIMON_FQNAME_LEN = sizeof(ALT_DMALL_RAIHIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_RAIJI_LUDOMON_FQID_ARR[] = "dmall:raiji_ludomon";
    inline static constexpr const char* ALT_DMALL_RAIJI_LUDOMON_FQID = ALT_DMALL_RAIJI_LUDOMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_RAIJI_LUDOMON_FQID_LEN = sizeof(ALT_DMALL_RAIJI_LUDOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_RAIJI_LUDOMON_FQNAME_ARR[] = "dmall:Raiji Ludomon";
    inline static constexpr const char* ALT_DMALL_RAIJI_LUDOMON_FQNAME = ALT_DMALL_RAIJI_LUDOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_RAIJI_LUDOMON_FQNAME_LEN = sizeof(ALT_DMALL_RAIJI_LUDOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_RAPIDMON_ARMOR_FQID_ARR[] = "dmall:rapidmon_armor";
    inline static constexpr const char* ALT_DMALL_RAPIDMON_ARMOR_FQID = ALT_DMALL_RAPIDMON_ARMOR_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_RAPIDMON_ARMOR_FQID_LEN = sizeof(ALT_DMALL_RAPIDMON_ARMOR_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_RAPIDMON_ARMOR_FQNAME_ARR[] = "dmall:Rapidmon (Armor)";
    inline static constexpr const char* ALT_DMALL_RAPIDMON_ARMOR_FQNAME = ALT_DMALL_RAPIDMON_ARMOR_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_RAPIDMON_ARMOR_FQNAME_LEN = sizeof(ALT_DMALL_RAPIDMON_ARMOR_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_RAPIDMON_FQID_ARR[] = "dmall:rapidmon";
    inline static constexpr const char* ALT_DMALL_RAPIDMON_FQID = ALT_DMALL_RAPIDMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_RAPIDMON_FQID_LEN = sizeof(ALT_DMALL_RAPIDMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_RAPIDMON_FQNAME_ARR[] = "dmall:Rapidmon";
    inline static constexpr const char* ALT_DMALL_RAPIDMON_FQNAME = ALT_DMALL_RAPIDMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_RAPIDMON_FQNAME_LEN = sizeof(ALT_DMALL_RAPIDMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_RAPIDMON_X_FQID_ARR[] = "dmall:rapidmon_x";
    inline static constexpr const char* ALT_DMALL_RAPIDMON_X_FQID = ALT_DMALL_RAPIDMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_RAPIDMON_X_FQID_LEN = sizeof(ALT_DMALL_RAPIDMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_RAPIDMON_X_FQNAME_ARR[] = "dmall:Rapidmon X";
    inline static constexpr const char* ALT_DMALL_RAPIDMON_X_FQNAME = ALT_DMALL_RAPIDMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_RAPIDMON_X_FQNAME_LEN = sizeof(ALT_DMALL_RAPIDMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_RAPTORDRAMON_FQID_ARR[] = "dmall:raptordramon";
    inline static constexpr const char* ALT_DMALL_RAPTORDRAMON_FQID = ALT_DMALL_RAPTORDRAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_RAPTORDRAMON_FQID_LEN = sizeof(ALT_DMALL_RAPTORDRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_RAPTORDRAMON_FQNAME_ARR[] = "dmall:Raptordramon";
    inline static constexpr const char* ALT_DMALL_RAPTORDRAMON_FQNAME = ALT_DMALL_RAPTORDRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_RAPTORDRAMON_FQNAME_LEN = sizeof(ALT_DMALL_RAPTORDRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_RASENMON_FURY_MODE_FQID_ARR[] = "dmall:rasenmon_fury_mode";
    inline static constexpr const char* ALT_DMALL_RASENMON_FURY_MODE_FQID = ALT_DMALL_RASENMON_FURY_MODE_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_RASENMON_FURY_MODE_FQID_LEN = sizeof(ALT_DMALL_RASENMON_FURY_MODE_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_RASENMON_FURY_MODE_FQNAME_ARR[] = "dmall:Rasenmon Fury Mode";
    inline static constexpr const char* ALT_DMALL_RASENMON_FURY_MODE_FQNAME = ALT_DMALL_RASENMON_FURY_MODE_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_RASENMON_FURY_MODE_FQNAME_LEN = sizeof(ALT_DMALL_RASENMON_FURY_MODE_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_RASENMON_FQID_ARR[] = "dmall:rasenmon";
    inline static constexpr const char* ALT_DMALL_RASENMON_FQID = ALT_DMALL_RASENMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_RASENMON_FQID_LEN = sizeof(ALT_DMALL_RASENMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_RASENMON_FQNAME_ARR[] = "dmall:Rasenmon";
    inline static constexpr const char* ALT_DMALL_RASENMON_FQNAME = ALT_DMALL_RASENMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_RASENMON_FQNAME_LEN = sizeof(ALT_DMALL_RASENMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_RASIELMON_FQID_ARR[] = "dmall:rasielmon";
    inline static constexpr const char* ALT_DMALL_RASIELMON_FQID = ALT_DMALL_RASIELMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_RASIELMON_FQID_LEN = sizeof(ALT_DMALL_RASIELMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_RASIELMON_FQNAME_ARR[] = "dmall:Rasielmon";
    inline static constexpr const char* ALT_DMALL_RASIELMON_FQNAME = ALT_DMALL_RASIELMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_RASIELMON_FQNAME_LEN = sizeof(ALT_DMALL_RASIELMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_REBELLIMON_FQID_ARR[] = "dmall:rebellimon";
    inline static constexpr const char* ALT_DMALL_REBELLIMON_FQID = ALT_DMALL_REBELLIMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_REBELLIMON_FQID_LEN = sizeof(ALT_DMALL_REBELLIMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_REBELLIMON_FQNAME_ARR[] = "dmall:Rebellimon";
    inline static constexpr const char* ALT_DMALL_REBELLIMON_FQNAME = ALT_DMALL_REBELLIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_REBELLIMON_FQNAME_LEN = sizeof(ALT_DMALL_REBELLIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_RED_V_DRAMON_FQID_ARR[] = "dmall:red_v_dramon";
    inline static constexpr const char* ALT_DMALL_RED_V_DRAMON_FQID = ALT_DMALL_RED_V_DRAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_RED_V_DRAMON_FQID_LEN = sizeof(ALT_DMALL_RED_V_DRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_RED_V_DRAMON_FQNAME_ARR[] = "dmall:Red V-dramon";
    inline static constexpr const char* ALT_DMALL_RED_V_DRAMON_FQNAME = ALT_DMALL_RED_V_DRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_RED_V_DRAMON_FQNAME_LEN = sizeof(ALT_DMALL_RED_V_DRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_RED_VEGIMON_FQID_ARR[] = "dmall:red_vegimon";
    inline static constexpr const char* ALT_DMALL_RED_VEGIMON_FQID = ALT_DMALL_RED_VEGIMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_RED_VEGIMON_FQID_LEN = sizeof(ALT_DMALL_RED_VEGIMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_RED_VEGIMON_FQNAME_ARR[] = "dmall:Red Vegimon";
    inline static constexpr const char* ALT_DMALL_RED_VEGIMON_FQNAME = ALT_DMALL_RED_VEGIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_RED_VEGIMON_FQNAME_LEN = sizeof(ALT_DMALL_RED_VEGIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_REGALECUSMON_FQID_ARR[] = "dmall:regalecusmon";
    inline static constexpr const char* ALT_DMALL_REGALECUSMON_FQID = ALT_DMALL_REGALECUSMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_REGALECUSMON_FQID_LEN = sizeof(ALT_DMALL_REGALECUSMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_REGALECUSMON_FQNAME_ARR[] = "dmall:Regalecusmon";
    inline static constexpr const char* ALT_DMALL_REGALECUSMON_FQNAME = ALT_DMALL_REGALECUSMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_REGALECUSMON_FQNAME_LEN = sizeof(ALT_DMALL_REGALECUSMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_RELEMON_FQID_ARR[] = "dmall:relemon";
    inline static constexpr const char* ALT_DMALL_RELEMON_FQID = ALT_DMALL_RELEMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_RELEMON_FQID_LEN = sizeof(ALT_DMALL_RELEMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_RELEMON_FQNAME_ARR[] = "dmall:Relemon";
    inline static constexpr const char* ALT_DMALL_RELEMON_FQNAME = ALT_DMALL_RELEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_RELEMON_FQNAME_LEN = sizeof(ALT_DMALL_RELEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_RENAMON_FQID_ARR[] = "dmall:renamon";
    inline static constexpr const char* ALT_DMALL_RENAMON_FQID = ALT_DMALL_RENAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_RENAMON_FQID_LEN = sizeof(ALT_DMALL_RENAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_RENAMON_FQNAME_ARR[] = "dmall:Renamon";
    inline static constexpr const char* ALT_DMALL_RENAMON_FQNAME = ALT_DMALL_RENAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_RENAMON_FQNAME_LEN = sizeof(ALT_DMALL_RENAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_RENAMON_X_FQID_ARR[] = "dmall:renamon_x";
    inline static constexpr const char* ALT_DMALL_RENAMON_X_FQID = ALT_DMALL_RENAMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_RENAMON_X_FQID_LEN = sizeof(ALT_DMALL_RENAMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_RENAMON_X_FQNAME_ARR[] = "dmall:Renamon X";
    inline static constexpr const char* ALT_DMALL_RENAMON_X_FQNAME = ALT_DMALL_RENAMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_RENAMON_X_FQNAME_LEN = sizeof(ALT_DMALL_RENAMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_REPPAMON_FQID_ARR[] = "dmall:reppamon";
    inline static constexpr const char* ALT_DMALL_REPPAMON_FQID = ALT_DMALL_REPPAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_REPPAMON_FQID_LEN = sizeof(ALT_DMALL_REPPAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_REPPAMON_FQNAME_ARR[] = "dmall:Reppamon";
    inline static constexpr const char* ALT_DMALL_REPPAMON_FQNAME = ALT_DMALL_REPPAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_REPPAMON_FQNAME_LEN = sizeof(ALT_DMALL_REPPAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_RHINOMON_FQID_ARR[] = "dmall:rhinomon";
    inline static constexpr const char* ALT_DMALL_RHINOMON_FQID = ALT_DMALL_RHINOMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_RHINOMON_FQID_LEN = sizeof(ALT_DMALL_RHINOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_RHINOMON_FQNAME_ARR[] = "dmall:Rhinomon";
    inline static constexpr const char* ALT_DMALL_RHINOMON_FQNAME = ALT_DMALL_RHINOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_RHINOMON_FQNAME_LEN = sizeof(ALT_DMALL_RHINOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_RHINOMON_X_FQID_ARR[] = "dmall:rhinomon_x";
    inline static constexpr const char* ALT_DMALL_RHINOMON_X_FQID = ALT_DMALL_RHINOMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_RHINOMON_X_FQID_LEN = sizeof(ALT_DMALL_RHINOMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_RHINOMON_X_FQNAME_ARR[] = "dmall:Rhinomon X";
    inline static constexpr const char* ALT_DMALL_RHINOMON_X_FQNAME = ALT_DMALL_RHINOMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_RHINOMON_X_FQNAME_LEN = sizeof(ALT_DMALL_RHINOMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_RIZE_GREYMON_FQID_ARR[] = "dmall:rize_greymon";
    inline static constexpr const char* ALT_DMALL_RIZE_GREYMON_FQID = ALT_DMALL_RIZE_GREYMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_RIZE_GREYMON_FQID_LEN = sizeof(ALT_DMALL_RIZE_GREYMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_RIZE_GREYMON_FQNAME_ARR[] = "dmall:Rize Greymon";
    inline static constexpr const char* ALT_DMALL_RIZE_GREYMON_FQNAME = ALT_DMALL_RIZE_GREYMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_RIZE_GREYMON_FQNAME_LEN = sizeof(ALT_DMALL_RIZE_GREYMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_RIZEGREYMON_X_FQID_ARR[] = "dmall:rizegreymon_x";
    inline static constexpr const char* ALT_DMALL_RIZEGREYMON_X_FQID = ALT_DMALL_RIZEGREYMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_RIZEGREYMON_X_FQID_LEN = sizeof(ALT_DMALL_RIZEGREYMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_RIZEGREYMON_X_FQNAME_ARR[] = "dmall:RizeGreymon X";
    inline static constexpr const char* ALT_DMALL_RIZEGREYMON_X_FQNAME = ALT_DMALL_RIZEGREYMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_RIZEGREYMON_X_FQNAME_LEN = sizeof(ALT_DMALL_RIZEGREYMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_ROSEMON_BURST_MODE_FQID_ARR[] = "dmall:rosemon_burst_mode";
    inline static constexpr const char* ALT_DMALL_ROSEMON_BURST_MODE_FQID = ALT_DMALL_ROSEMON_BURST_MODE_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_ROSEMON_BURST_MODE_FQID_LEN = sizeof(ALT_DMALL_ROSEMON_BURST_MODE_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_ROSEMON_BURST_MODE_FQNAME_ARR[] = "dmall:Rosemon Burst Mode";
    inline static constexpr const char* ALT_DMALL_ROSEMON_BURST_MODE_FQNAME = ALT_DMALL_ROSEMON_BURST_MODE_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_ROSEMON_BURST_MODE_FQNAME_LEN = sizeof(ALT_DMALL_ROSEMON_BURST_MODE_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_ROSEMON_FQID_ARR[] = "dmall:rosemon";
    inline static constexpr const char* ALT_DMALL_ROSEMON_FQID = ALT_DMALL_ROSEMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_ROSEMON_FQID_LEN = sizeof(ALT_DMALL_ROSEMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_ROSEMON_FQNAME_ARR[] = "dmall:Rosemon";
    inline static constexpr const char* ALT_DMALL_ROSEMON_FQNAME = ALT_DMALL_ROSEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_ROSEMON_FQNAME_LEN = sizeof(ALT_DMALL_ROSEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_ROSEMON_X_FQID_ARR[] = "dmall:rosemon_x";
    inline static constexpr const char* ALT_DMALL_ROSEMON_X_FQID = ALT_DMALL_ROSEMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_ROSEMON_X_FQID_LEN = sizeof(ALT_DMALL_ROSEMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_ROSEMON_X_FQNAME_ARR[] = "dmall:Rosemon X";
    inline static constexpr const char* ALT_DMALL_ROSEMON_X_FQNAME = ALT_DMALL_ROSEMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_ROSEMON_X_FQNAME_LEN = sizeof(ALT_DMALL_ROSEMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_RUKAMON_FQID_ARR[] = "dmall:rukamon";
    inline static constexpr const char* ALT_DMALL_RUKAMON_FQID = ALT_DMALL_RUKAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_RUKAMON_FQID_LEN = sizeof(ALT_DMALL_RUKAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_RUKAMON_FQNAME_ARR[] = "dmall:Rukamon";
    inline static constexpr const char* ALT_DMALL_RUKAMON_FQNAME = ALT_DMALL_RUKAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_RUKAMON_FQNAME_LEN = sizeof(ALT_DMALL_RUKAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_RUST_TYRANNOMON_FQID_ARR[] = "dmall:rust_tyrannomon";
    inline static constexpr const char* ALT_DMALL_RUST_TYRANNOMON_FQID = ALT_DMALL_RUST_TYRANNOMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_RUST_TYRANNOMON_FQID_LEN = sizeof(ALT_DMALL_RUST_TYRANNOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_RUST_TYRANNOMON_FQNAME_ARR[] = "dmall:Rust Tyrannomon";
    inline static constexpr const char* ALT_DMALL_RUST_TYRANNOMON_FQNAME = ALT_DMALL_RUST_TYRANNOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_RUST_TYRANNOMON_FQNAME_LEN = sizeof(ALT_DMALL_RUST_TYRANNOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_RYUDAMON_FQID_ARR[] = "dmall:ryudamon";
    inline static constexpr const char* ALT_DMALL_RYUDAMON_FQID = ALT_DMALL_RYUDAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_RYUDAMON_FQID_LEN = sizeof(ALT_DMALL_RYUDAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_RYUDAMON_FQNAME_ARR[] = "dmall:Ryudamon";
    inline static constexpr const char* ALT_DMALL_RYUDAMON_FQNAME = ALT_DMALL_RYUDAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_RYUDAMON_FQNAME_LEN = sizeof(ALT_DMALL_RYUDAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_SABERDRAMON_FQID_ARR[] = "dmall:saberdramon";
    inline static constexpr const char* ALT_DMALL_SABERDRAMON_FQID = ALT_DMALL_SABERDRAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_SABERDRAMON_FQID_LEN = sizeof(ALT_DMALL_SABERDRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_SABERDRAMON_FQNAME_ARR[] = "dmall:Saberdramon";
    inline static constexpr const char* ALT_DMALL_SABERDRAMON_FQNAME = ALT_DMALL_SABERDRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_SABERDRAMON_FQNAME_LEN = sizeof(ALT_DMALL_SABERDRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_SABER_LEOMON_FQID_ARR[] = "dmall:saber_leomon";
    inline static constexpr const char* ALT_DMALL_SABER_LEOMON_FQID = ALT_DMALL_SABER_LEOMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_SABER_LEOMON_FQID_LEN = sizeof(ALT_DMALL_SABER_LEOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_SABER_LEOMON_FQNAME_ARR[] = "dmall:Saber Leomon";
    inline static constexpr const char* ALT_DMALL_SABER_LEOMON_FQNAME = ALT_DMALL_SABER_LEOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_SABER_LEOMON_FQNAME_LEN = sizeof(ALT_DMALL_SABER_LEOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_SAGOMON_FQID_ARR[] = "dmall:sagomon";
    inline static constexpr const char* ALT_DMALL_SAGOMON_FQID = ALT_DMALL_SAGOMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_SAGOMON_FQID_LEN = sizeof(ALT_DMALL_SAGOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_SAGOMON_FQNAME_ARR[] = "dmall:Sagomon";
    inline static constexpr const char* ALT_DMALL_SAGOMON_FQNAME = ALT_DMALL_SAGOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_SAGOMON_FQNAME_LEN = sizeof(ALT_DMALL_SAGOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_SAINT_GALGOMON_FQID_ARR[] = "dmall:saint_galgomon";
    inline static constexpr const char* ALT_DMALL_SAINT_GALGOMON_FQID = ALT_DMALL_SAINT_GALGOMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_SAINT_GALGOMON_FQID_LEN = sizeof(ALT_DMALL_SAINT_GALGOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_SAINT_GALGOMON_FQNAME_ARR[] = "dmall:Saint Galgomon";
    inline static constexpr const char* ALT_DMALL_SAINT_GALGOMON_FQNAME = ALT_DMALL_SAINT_GALGOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_SAINT_GALGOMON_FQNAME_LEN = sizeof(ALT_DMALL_SAINT_GALGOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_SAKUYAMON_FQID_ARR[] = "dmall:sakuyamon";
    inline static constexpr const char* ALT_DMALL_SAKUYAMON_FQID = ALT_DMALL_SAKUYAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_SAKUYAMON_FQID_LEN = sizeof(ALT_DMALL_SAKUYAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_SAKUYAMON_FQNAME_ARR[] = "dmall:Sakuyamon";
    inline static constexpr const char* ALT_DMALL_SAKUYAMON_FQNAME = ALT_DMALL_SAKUYAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_SAKUYAMON_FQNAME_LEN = sizeof(ALT_DMALL_SAKUYAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_SAKUYAMON_X_FQID_ARR[] = "dmall:sakuyamon_x";
    inline static constexpr const char* ALT_DMALL_SAKUYAMON_X_FQID = ALT_DMALL_SAKUYAMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_SAKUYAMON_X_FQID_LEN = sizeof(ALT_DMALL_SAKUYAMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_SAKUYAMON_X_FQNAME_ARR[] = "dmall:Sakuyamon X";
    inline static constexpr const char* ALT_DMALL_SAKUYAMON_X_FQNAME = ALT_DMALL_SAKUYAMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_SAKUYAMON_X_FQNAME_LEN = sizeof(ALT_DMALL_SAKUYAMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_SAND_YANMAMON_FQID_ARR[] = "dmall:sand_yanmamon";
    inline static constexpr const char* ALT_DMALL_SAND_YANMAMON_FQID = ALT_DMALL_SAND_YANMAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_SAND_YANMAMON_FQID_LEN = sizeof(ALT_DMALL_SAND_YANMAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_SAND_YANMAMON_FQNAME_ARR[] = "dmall:Sand Yanmamon";
    inline static constexpr const char* ALT_DMALL_SAND_YANMAMON_FQNAME = ALT_DMALL_SAND_YANMAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_SAND_YANMAMON_FQNAME_LEN = sizeof(ALT_DMALL_SAND_YANMAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_SANGLOUPMON_FQID_ARR[] = "dmall:sangloupmon";
    inline static constexpr const char* ALT_DMALL_SANGLOUPMON_FQID = ALT_DMALL_SANGLOUPMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_SANGLOUPMON_FQID_LEN = sizeof(ALT_DMALL_SANGLOUPMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_SANGLOUPMON_FQNAME_ARR[] = "dmall:Sangloupmon";
    inline static constexpr const char* ALT_DMALL_SANGLOUPMON_FQNAME = ALT_DMALL_SANGLOUPMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_SANGLOUPMON_FQNAME_LEN = sizeof(ALT_DMALL_SANGLOUPMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_SANGOMON_FQID_ARR[] = "dmall:sangomon";
    inline static constexpr const char* ALT_DMALL_SANGOMON_FQID = ALT_DMALL_SANGOMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_SANGOMON_FQID_LEN = sizeof(ALT_DMALL_SANGOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_SANGOMON_FQNAME_ARR[] = "dmall:Sangomon";
    inline static constexpr const char* ALT_DMALL_SANGOMON_FQNAME = ALT_DMALL_SANGOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_SANGOMON_FQNAME_LEN = sizeof(ALT_DMALL_SANGOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_SAVIORHACKMON_FQID_ARR[] = "dmall:saviorhackmon";
    inline static constexpr const char* ALT_DMALL_SAVIORHACKMON_FQID = ALT_DMALL_SAVIORHACKMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_SAVIORHACKMON_FQID_LEN = sizeof(ALT_DMALL_SAVIORHACKMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_SAVIORHACKMON_FQNAME_ARR[] = "dmall:SaviorHackmon";
    inline static constexpr const char* ALT_DMALL_SAVIORHACKMON_FQNAME = ALT_DMALL_SAVIORHACKMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_SAVIORHACKMON_FQNAME_LEN = sizeof(ALT_DMALL_SAVIORHACKMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_SCORPIOMON_FQID_ARR[] = "dmall:scorpiomon";
    inline static constexpr const char* ALT_DMALL_SCORPIOMON_FQID = ALT_DMALL_SCORPIOMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_SCORPIOMON_FQID_LEN = sizeof(ALT_DMALL_SCORPIOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_SCORPIOMON_FQNAME_ARR[] = "dmall:Scorpiomon";
    inline static constexpr const char* ALT_DMALL_SCORPIOMON_FQNAME = ALT_DMALL_SCORPIOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_SCORPIOMON_FQNAME_LEN = sizeof(ALT_DMALL_SCORPIOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_SCUMON_FQID_ARR[] = "dmall:scumon";
    inline static constexpr const char* ALT_DMALL_SCUMON_FQID = ALT_DMALL_SCUMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_SCUMON_FQID_LEN = sizeof(ALT_DMALL_SCUMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_SCUMON_FQNAME_ARR[] = "dmall:Scumon";
    inline static constexpr const char* ALT_DMALL_SCUMON_FQNAME = ALT_DMALL_SCUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_SCUMON_FQNAME_LEN = sizeof(ALT_DMALL_SCUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_SEADRAMON_FQID_ARR[] = "dmall:seadramon";
    inline static constexpr const char* ALT_DMALL_SEADRAMON_FQID = ALT_DMALL_SEADRAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_SEADRAMON_FQID_LEN = sizeof(ALT_DMALL_SEADRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_SEADRAMON_FQNAME_ARR[] = "dmall:Seadramon";
    inline static constexpr const char* ALT_DMALL_SEADRAMON_FQNAME = ALT_DMALL_SEADRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_SEADRAMON_FQNAME_LEN = sizeof(ALT_DMALL_SEADRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_SEADRAMON_X_FQID_ARR[] = "dmall:seadramon_x";
    inline static constexpr const char* ALT_DMALL_SEADRAMON_X_FQID = ALT_DMALL_SEADRAMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_SEADRAMON_X_FQID_LEN = sizeof(ALT_DMALL_SEADRAMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_SEADRAMON_X_FQNAME_ARR[] = "dmall:Seadramon X";
    inline static constexpr const char* ALT_DMALL_SEADRAMON_X_FQNAME = ALT_DMALL_SEADRAMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_SEADRAMON_X_FQNAME_LEN = sizeof(ALT_DMALL_SEADRAMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_SERAPHIMON_FQID_ARR[] = "dmall:seraphimon";
    inline static constexpr const char* ALT_DMALL_SERAPHIMON_FQID = ALT_DMALL_SERAPHIMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_SERAPHIMON_FQID_LEN = sizeof(ALT_DMALL_SERAPHIMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_SERAPHIMON_FQNAME_ARR[] = "dmall:Seraphimon";
    inline static constexpr const char* ALT_DMALL_SERAPHIMON_FQNAME = ALT_DMALL_SERAPHIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_SERAPHIMON_FQNAME_LEN = sizeof(ALT_DMALL_SERAPHIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_SHADRAMON_FQID_ARR[] = "dmall:shadramon";
    inline static constexpr const char* ALT_DMALL_SHADRAMON_FQID = ALT_DMALL_SHADRAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_SHADRAMON_FQID_LEN = sizeof(ALT_DMALL_SHADRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_SHADRAMON_FQNAME_ARR[] = "dmall:Shadramon";
    inline static constexpr const char* ALT_DMALL_SHADRAMON_FQNAME = ALT_DMALL_SHADRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_SHADRAMON_FQNAME_LEN = sizeof(ALT_DMALL_SHADRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_SHAKOMON_FQID_ARR[] = "dmall:shakomon";
    inline static constexpr const char* ALT_DMALL_SHAKOMON_FQID = ALT_DMALL_SHAKOMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_SHAKOMON_FQID_LEN = sizeof(ALT_DMALL_SHAKOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_SHAKOMON_FQNAME_ARR[] = "dmall:Shakomon";
    inline static constexpr const char* ALT_DMALL_SHAKOMON_FQNAME = ALT_DMALL_SHAKOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_SHAKOMON_FQNAME_LEN = sizeof(ALT_DMALL_SHAKOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_SHAKOMON_X_FQID_ARR[] = "dmall:shakomon_x";
    inline static constexpr const char* ALT_DMALL_SHAKOMON_X_FQID = ALT_DMALL_SHAKOMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_SHAKOMON_X_FQID_LEN = sizeof(ALT_DMALL_SHAKOMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_SHAKOMON_X_FQNAME_ARR[] = "dmall:Shakomon X";
    inline static constexpr const char* ALT_DMALL_SHAKOMON_X_FQNAME = ALT_DMALL_SHAKOMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_SHAKOMON_X_FQNAME_LEN = sizeof(ALT_DMALL_SHAKOMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_SHAWUJINMON_FQID_ARR[] = "dmall:shawujinmon";
    inline static constexpr const char* ALT_DMALL_SHAWUJINMON_FQID = ALT_DMALL_SHAWUJINMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_SHAWUJINMON_FQID_LEN = sizeof(ALT_DMALL_SHAWUJINMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_SHAWUJINMON_FQNAME_ARR[] = "dmall:Shawujinmon";
    inline static constexpr const char* ALT_DMALL_SHAWUJINMON_FQNAME = ALT_DMALL_SHAWUJINMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_SHAWUJINMON_FQNAME_LEN = sizeof(ALT_DMALL_SHAWUJINMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_SHEEPMON_FQID_ARR[] = "dmall:sheepmon";
    inline static constexpr const char* ALT_DMALL_SHEEPMON_FQID = ALT_DMALL_SHEEPMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_SHEEPMON_FQID_LEN = sizeof(ALT_DMALL_SHEEPMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_SHEEPMON_FQNAME_ARR[] = "dmall:Sheepmon";
    inline static constexpr const char* ALT_DMALL_SHEEPMON_FQNAME = ALT_DMALL_SHEEPMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_SHEEPMON_FQNAME_LEN = sizeof(ALT_DMALL_SHEEPMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_SHELLMON_FQID_ARR[] = "dmall:shellmon";
    inline static constexpr const char* ALT_DMALL_SHELLMON_FQID = ALT_DMALL_SHELLMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_SHELLMON_FQID_LEN = sizeof(ALT_DMALL_SHELLMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_SHELLMON_FQNAME_ARR[] = "dmall:Shellmon";
    inline static constexpr const char* ALT_DMALL_SHELLMON_FQNAME = ALT_DMALL_SHELLMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_SHELLMON_FQNAME_LEN = sizeof(ALT_DMALL_SHELLMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_SHIMA_UNIMON_FQID_ARR[] = "dmall:shima_unimon";
    inline static constexpr const char* ALT_DMALL_SHIMA_UNIMON_FQID = ALT_DMALL_SHIMA_UNIMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_SHIMA_UNIMON_FQID_LEN = sizeof(ALT_DMALL_SHIMA_UNIMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_SHIMA_UNIMON_FQNAME_ARR[] = "dmall:Shima Unimon";
    inline static constexpr const char* ALT_DMALL_SHIMA_UNIMON_FQNAME = ALT_DMALL_SHIMA_UNIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_SHIMA_UNIMON_FQNAME_LEN = sizeof(ALT_DMALL_SHIMA_UNIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_SHIN_MONZAEMON_FQID_ARR[] = "dmall:shin_monzaemon";
    inline static constexpr const char* ALT_DMALL_SHIN_MONZAEMON_FQID = ALT_DMALL_SHIN_MONZAEMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_SHIN_MONZAEMON_FQID_LEN = sizeof(ALT_DMALL_SHIN_MONZAEMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_SHIN_MONZAEMON_FQNAME_ARR[] = "dmall:Shin Monzaemon";
    inline static constexpr const char* ALT_DMALL_SHIN_MONZAEMON_FQNAME = ALT_DMALL_SHIN_MONZAEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_SHIN_MONZAEMON_FQNAME_LEN = sizeof(ALT_DMALL_SHIN_MONZAEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_SHOOTMON_FQID_ARR[] = "dmall:shootmon";
    inline static constexpr const char* ALT_DMALL_SHOOTMON_FQID = ALT_DMALL_SHOOTMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_SHOOTMON_FQID_LEN = sizeof(ALT_DMALL_SHOOTMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_SHOOTMON_FQNAME_ARR[] = "dmall:Shootmon";
    inline static constexpr const char* ALT_DMALL_SHOOTMON_FQNAME = ALT_DMALL_SHOOTMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_SHOOTMON_FQNAME_LEN = sizeof(ALT_DMALL_SHOOTMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_SIESAMON_X_FQID_ARR[] = "dmall:siesamon_x";
    inline static constexpr const char* ALT_DMALL_SIESAMON_X_FQID = ALT_DMALL_SIESAMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_SIESAMON_X_FQID_LEN = sizeof(ALT_DMALL_SIESAMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_SIESAMON_X_FQNAME_ARR[] = "dmall:Siesamon X";
    inline static constexpr const char* ALT_DMALL_SIESAMON_X_FQNAME = ALT_DMALL_SIESAMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_SIESAMON_X_FQNAME_LEN = sizeof(ALT_DMALL_SIESAMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_SIRENMON_FQID_ARR[] = "dmall:sirenmon";
    inline static constexpr const char* ALT_DMALL_SIRENMON_FQID = ALT_DMALL_SIRENMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_SIRENMON_FQID_LEN = sizeof(ALT_DMALL_SIRENMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_SIRENMON_FQNAME_ARR[] = "dmall:Sirenmon";
    inline static constexpr const char* ALT_DMALL_SIRENMON_FQNAME = ALT_DMALL_SIRENMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_SIRENMON_FQNAME_LEN = sizeof(ALT_DMALL_SIRENMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_SISTERMON_BLANC_FQID_ARR[] = "dmall:sistermon_blanc";
    inline static constexpr const char* ALT_DMALL_SISTERMON_BLANC_FQID = ALT_DMALL_SISTERMON_BLANC_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_SISTERMON_BLANC_FQID_LEN = sizeof(ALT_DMALL_SISTERMON_BLANC_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_SISTERMON_BLANC_FQNAME_ARR[] = "dmall:Sistermon Blanc";
    inline static constexpr const char* ALT_DMALL_SISTERMON_BLANC_FQNAME = ALT_DMALL_SISTERMON_BLANC_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_SISTERMON_BLANC_FQNAME_LEN = sizeof(ALT_DMALL_SISTERMON_BLANC_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_SKULL_BALUCHIMON_FQID_ARR[] = "dmall:skull_baluchimon";
    inline static constexpr const char* ALT_DMALL_SKULL_BALUCHIMON_FQID = ALT_DMALL_SKULL_BALUCHIMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_SKULL_BALUCHIMON_FQID_LEN = sizeof(ALT_DMALL_SKULL_BALUCHIMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_SKULL_BALUCHIMON_FQNAME_ARR[] = "dmall:Skull Baluchimon";
    inline static constexpr const char* ALT_DMALL_SKULL_BALUCHIMON_FQNAME = ALT_DMALL_SKULL_BALUCHIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_SKULL_BALUCHIMON_FQNAME_LEN = sizeof(ALT_DMALL_SKULL_BALUCHIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_SKULL_GREYMON_FQID_ARR[] = "dmall:skull_greymon";
    inline static constexpr const char* ALT_DMALL_SKULL_GREYMON_FQID = ALT_DMALL_SKULL_GREYMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_SKULL_GREYMON_FQID_LEN = sizeof(ALT_DMALL_SKULL_GREYMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_SKULL_GREYMON_FQNAME_ARR[] = "dmall:Skull Greymon";
    inline static constexpr const char* ALT_DMALL_SKULL_GREYMON_FQNAME = ALT_DMALL_SKULL_GREYMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_SKULL_GREYMON_FQNAME_LEN = sizeof(ALT_DMALL_SKULL_GREYMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_SKULLKNIGHTMON_FQID_ARR[] = "dmall:skullknightmon";
    inline static constexpr const char* ALT_DMALL_SKULLKNIGHTMON_FQID = ALT_DMALL_SKULLKNIGHTMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_SKULLKNIGHTMON_FQID_LEN = sizeof(ALT_DMALL_SKULLKNIGHTMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_SKULLKNIGHTMON_FQNAME_ARR[] = "dmall:SkullKnightmon";
    inline static constexpr const char* ALT_DMALL_SKULLKNIGHTMON_FQNAME = ALT_DMALL_SKULLKNIGHTMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_SKULLKNIGHTMON_FQNAME_LEN = sizeof(ALT_DMALL_SKULLKNIGHTMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_SKULL_MAMMON_FQID_ARR[] = "dmall:skull_mammon";
    inline static constexpr const char* ALT_DMALL_SKULL_MAMMON_FQID = ALT_DMALL_SKULL_MAMMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_SKULL_MAMMON_FQID_LEN = sizeof(ALT_DMALL_SKULL_MAMMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_SKULL_MAMMON_FQNAME_ARR[] = "dmall:Skull Mammon";
    inline static constexpr const char* ALT_DMALL_SKULL_MAMMON_FQNAME = ALT_DMALL_SKULL_MAMMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_SKULL_MAMMON_FQNAME_LEN = sizeof(ALT_DMALL_SKULL_MAMMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_SKULL_MAMMON_X_FQID_ARR[] = "dmall:skull_mammon_x";
    inline static constexpr const char* ALT_DMALL_SKULL_MAMMON_X_FQID = ALT_DMALL_SKULL_MAMMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_SKULL_MAMMON_X_FQID_LEN = sizeof(ALT_DMALL_SKULL_MAMMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_SKULL_MAMMON_X_FQNAME_ARR[] = "dmall:Skull Mammon X";
    inline static constexpr const char* ALT_DMALL_SKULL_MAMMON_X_FQNAME = ALT_DMALL_SKULL_MAMMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_SKULL_MAMMON_X_FQNAME_LEN = sizeof(ALT_DMALL_SKULL_MAMMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_SLEIPMON_X_FQID_ARR[] = "dmall:sleipmon_x";
    inline static constexpr const char* ALT_DMALL_SLEIPMON_X_FQID = ALT_DMALL_SLEIPMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_SLEIPMON_X_FQID_LEN = sizeof(ALT_DMALL_SLEIPMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_SLEIPMON_X_FQNAME_ARR[] = "dmall:Sleipmon X";
    inline static constexpr const char* ALT_DMALL_SLEIPMON_X_FQNAME = ALT_DMALL_SLEIPMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_SLEIPMON_X_FQNAME_LEN = sizeof(ALT_DMALL_SLEIPMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_SOLARMON_FQID_ARR[] = "dmall:solarmon";
    inline static constexpr const char* ALT_DMALL_SOLARMON_FQID = ALT_DMALL_SOLARMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_SOLARMON_FQID_LEN = sizeof(ALT_DMALL_SOLARMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_SOLARMON_FQNAME_ARR[] = "dmall:Solarmon";
    inline static constexpr const char* ALT_DMALL_SOLARMON_FQNAME = ALT_DMALL_SOLARMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_SOLARMON_FQNAME_LEN = sizeof(ALT_DMALL_SOLARMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_SORCERYMON_FQID_ARR[] = "dmall:sorcerymon";
    inline static constexpr const char* ALT_DMALL_SORCERYMON_FQID = ALT_DMALL_SORCERYMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_SORCERYMON_FQID_LEN = sizeof(ALT_DMALL_SORCERYMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_SORCERYMON_FQNAME_ARR[] = "dmall:Sorcerymon";
    inline static constexpr const char* ALT_DMALL_SORCERYMON_FQNAME = ALT_DMALL_SORCERYMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_SORCERYMON_FQNAME_LEN = sizeof(ALT_DMALL_SORCERYMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_SOULMON_FQID_ARR[] = "dmall:soulmon";
    inline static constexpr const char* ALT_DMALL_SOULMON_FQID = ALT_DMALL_SOULMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_SOULMON_FQID_LEN = sizeof(ALT_DMALL_SOULMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_SOULMON_FQNAME_ARR[] = "dmall:Soulmon";
    inline static constexpr const char* ALT_DMALL_SOULMON_FQNAME = ALT_DMALL_SOULMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_SOULMON_FQNAME_LEN = sizeof(ALT_DMALL_SOULMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_STARMON_FQID_ARR[] = "dmall:starmon";
    inline static constexpr const char* ALT_DMALL_STARMON_FQID = ALT_DMALL_STARMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_STARMON_FQID_LEN = sizeof(ALT_DMALL_STARMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_STARMON_FQNAME_ARR[] = "dmall:Starmon";
    inline static constexpr const char* ALT_DMALL_STARMON_FQNAME = ALT_DMALL_STARMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_STARMON_FQNAME_LEN = sizeof(ALT_DMALL_STARMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_STIFFILMON_FQID_ARR[] = "dmall:stiffilmon";
    inline static constexpr const char* ALT_DMALL_STIFFILMON_FQID = ALT_DMALL_STIFFILMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_STIFFILMON_FQID_LEN = sizeof(ALT_DMALL_STIFFILMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_STIFFILMON_FQNAME_ARR[] = "dmall:Stiffilmon";
    inline static constexpr const char* ALT_DMALL_STIFFILMON_FQNAME = ALT_DMALL_STIFFILMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_STIFFILMON_FQNAME_LEN = sizeof(ALT_DMALL_STIFFILMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_SUBMARINMON_FQID_ARR[] = "dmall:submarinmon";
    inline static constexpr const char* ALT_DMALL_SUBMARINMON_FQID = ALT_DMALL_SUBMARINMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_SUBMARINMON_FQID_LEN = sizeof(ALT_DMALL_SUBMARINMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_SUBMARINMON_FQNAME_ARR[] = "dmall:Submarinmon";
    inline static constexpr const char* ALT_DMALL_SUBMARINMON_FQNAME = ALT_DMALL_SUBMARINMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_SUBMARINMON_FQNAME_LEN = sizeof(ALT_DMALL_SUBMARINMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_SUNAMON_FQID_ARR[] = "dmall:sunamon";
    inline static constexpr const char* ALT_DMALL_SUNAMON_FQID = ALT_DMALL_SUNAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_SUNAMON_FQID_LEN = sizeof(ALT_DMALL_SUNAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_SUNAMON_FQNAME_ARR[] = "dmall:Sunamon";
    inline static constexpr const char* ALT_DMALL_SUNAMON_FQNAME = ALT_DMALL_SUNAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_SUNAMON_FQNAME_LEN = sizeof(ALT_DMALL_SUNAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_SUNARIZAMON_FQID_ARR[] = "dmall:sunarizamon";
    inline static constexpr const char* ALT_DMALL_SUNARIZAMON_FQID = ALT_DMALL_SUNARIZAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_SUNARIZAMON_FQID_LEN = sizeof(ALT_DMALL_SUNARIZAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_SUNARIZAMON_FQNAME_ARR[] = "dmall:Sunarizamon";
    inline static constexpr const char* ALT_DMALL_SUNARIZAMON_FQNAME = ALT_DMALL_SUNARIZAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_SUNARIZAMON_FQNAME_LEN = sizeof(ALT_DMALL_SUNARIZAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_SUNFLOWMON_FQID_ARR[] = "dmall:sunflowmon";
    inline static constexpr const char* ALT_DMALL_SUNFLOWMON_FQID = ALT_DMALL_SUNFLOWMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_SUNFLOWMON_FQID_LEN = sizeof(ALT_DMALL_SUNFLOWMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_SUNFLOWMON_FQNAME_ARR[] = "dmall:Sunflowmon";
    inline static constexpr const char* ALT_DMALL_SUNFLOWMON_FQNAME = ALT_DMALL_SUNFLOWMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_SUNFLOWMON_FQNAME_LEN = sizeof(ALT_DMALL_SUNFLOWMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_SUNMON_FQID_ARR[] = "dmall:sunmon";
    inline static constexpr const char* ALT_DMALL_SUNMON_FQID = ALT_DMALL_SUNMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_SUNMON_FQID_LEN = sizeof(ALT_DMALL_SUNMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_SUNMON_FQNAME_ARR[] = "dmall:Sunmon";
    inline static constexpr const char* ALT_DMALL_SUNMON_FQNAME = ALT_DMALL_SUNMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_SUNMON_FQNAME_LEN = sizeof(ALT_DMALL_SUNMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_SUPERSTARMON_FQID_ARR[] = "dmall:superstarmon";
    inline static constexpr const char* ALT_DMALL_SUPERSTARMON_FQID = ALT_DMALL_SUPERSTARMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_SUPERSTARMON_FQID_LEN = sizeof(ALT_DMALL_SUPERSTARMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_SUPERSTARMON_FQNAME_ARR[] = "dmall:Superstarmon";
    inline static constexpr const char* ALT_DMALL_SUPERSTARMON_FQNAME = ALT_DMALL_SUPERSTARMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_SUPERSTARMON_FQNAME_LEN = sizeof(ALT_DMALL_SUPERSTARMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_SUSANOOMON_FQID_ARR[] = "dmall:susanoomon";
    inline static constexpr const char* ALT_DMALL_SUSANOOMON_FQID = ALT_DMALL_SUSANOOMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_SUSANOOMON_FQID_LEN = sizeof(ALT_DMALL_SUSANOOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_SUSANOOMON_FQNAME_ARR[] = "dmall:Susanoomon";
    inline static constexpr const char* ALT_DMALL_SUSANOOMON_FQNAME = ALT_DMALL_SUSANOOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_SUSANOOMON_FQNAME_LEN = sizeof(ALT_DMALL_SUSANOOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_SWIMMON_FQID_ARR[] = "dmall:swimmon";
    inline static constexpr const char* ALT_DMALL_SWIMMON_FQID = ALT_DMALL_SWIMMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_SWIMMON_FQID_LEN = sizeof(ALT_DMALL_SWIMMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_SWIMMON_FQNAME_ARR[] = "dmall:Swimmon";
    inline static constexpr const char* ALT_DMALL_SWIMMON_FQNAME = ALT_DMALL_SWIMMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_SWIMMON_FQNAME_LEN = sizeof(ALT_DMALL_SWIMMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_TAILMON_FQID_ARR[] = "dmall:tailmon";
    inline static constexpr const char* ALT_DMALL_TAILMON_FQID = ALT_DMALL_TAILMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_TAILMON_FQID_LEN = sizeof(ALT_DMALL_TAILMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_TAILMON_FQNAME_ARR[] = "dmall:Tailmon";
    inline static constexpr const char* ALT_DMALL_TAILMON_FQNAME = ALT_DMALL_TAILMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_TAILMON_FQNAME_LEN = sizeof(ALT_DMALL_TAILMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_TAILMON_X_FQID_ARR[] = "dmall:tailmon_x";
    inline static constexpr const char* ALT_DMALL_TAILMON_X_FQID = ALT_DMALL_TAILMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_TAILMON_X_FQID_LEN = sizeof(ALT_DMALL_TAILMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_TAILMON_X_FQNAME_ARR[] = "dmall:Tailmon X";
    inline static constexpr const char* ALT_DMALL_TAILMON_X_FQNAME = ALT_DMALL_TAILMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_TAILMON_X_FQNAME_LEN = sizeof(ALT_DMALL_TAILMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_TANEMON_FQID_ARR[] = "dmall:tanemon";
    inline static constexpr const char* ALT_DMALL_TANEMON_FQID = ALT_DMALL_TANEMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_TANEMON_FQID_LEN = sizeof(ALT_DMALL_TANEMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_TANEMON_FQNAME_ARR[] = "dmall:Tanemon";
    inline static constexpr const char* ALT_DMALL_TANEMON_FQNAME = ALT_DMALL_TANEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_TANEMON_FQNAME_LEN = sizeof(ALT_DMALL_TANEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_TANKMON_FQID_ARR[] = "dmall:tankmon";
    inline static constexpr const char* ALT_DMALL_TANKMON_FQID = ALT_DMALL_TANKMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_TANKMON_FQID_LEN = sizeof(ALT_DMALL_TANKMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_TANKMON_FQNAME_ARR[] = "dmall:Tankmon";
    inline static constexpr const char* ALT_DMALL_TANKMON_FQNAME = ALT_DMALL_TANKMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_TANKMON_FQNAME_LEN = sizeof(ALT_DMALL_TANKMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_TARGETMON_FQID_ARR[] = "dmall:targetmon";
    inline static constexpr const char* ALT_DMALL_TARGETMON_FQID = ALT_DMALL_TARGETMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_TARGETMON_FQID_LEN = sizeof(ALT_DMALL_TARGETMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_TARGETMON_FQNAME_ARR[] = "dmall:Targetmon";
    inline static constexpr const char* ALT_DMALL_TARGETMON_FQNAME = ALT_DMALL_TARGETMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_TARGETMON_FQNAME_LEN = sizeof(ALT_DMALL_TARGETMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_TEKKAMON_FQID_ARR[] = "dmall:tekkamon";
    inline static constexpr const char* ALT_DMALL_TEKKAMON_FQID = ALT_DMALL_TEKKAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_TEKKAMON_FQID_LEN = sizeof(ALT_DMALL_TEKKAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_TEKKAMON_FQNAME_ARR[] = "dmall:Tekkamon";
    inline static constexpr const char* ALT_DMALL_TEKKAMON_FQNAME = ALT_DMALL_TEKKAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_TEKKAMON_FQNAME_LEN = sizeof(ALT_DMALL_TEKKAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_TENTOMON_FQID_ARR[] = "dmall:tentomon";
    inline static constexpr const char* ALT_DMALL_TENTOMON_FQID = ALT_DMALL_TENTOMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_TENTOMON_FQID_LEN = sizeof(ALT_DMALL_TENTOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_TENTOMON_FQNAME_ARR[] = "dmall:Tentomon";
    inline static constexpr const char* ALT_DMALL_TENTOMON_FQNAME = ALT_DMALL_TENTOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_TENTOMON_FQNAME_LEN = sizeof(ALT_DMALL_TENTOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_TERRIERMON_FQID_ARR[] = "dmall:terriermon";
    inline static constexpr const char* ALT_DMALL_TERRIERMON_FQID = ALT_DMALL_TERRIERMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_TERRIERMON_FQID_LEN = sizeof(ALT_DMALL_TERRIERMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_TERRIERMON_FQNAME_ARR[] = "dmall:Terriermon";
    inline static constexpr const char* ALT_DMALL_TERRIERMON_FQNAME = ALT_DMALL_TERRIERMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_TERRIERMON_FQNAME_LEN = sizeof(ALT_DMALL_TERRIERMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_TERRIERMON_X_FQID_ARR[] = "dmall:terriermon_x";
    inline static constexpr const char* ALT_DMALL_TERRIERMON_X_FQID = ALT_DMALL_TERRIERMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_TERRIERMON_X_FQID_LEN = sizeof(ALT_DMALL_TERRIERMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_TERRIERMON_X_FQNAME_ARR[] = "dmall:Terriermon X";
    inline static constexpr const char* ALT_DMALL_TERRIERMON_X_FQNAME = ALT_DMALL_TERRIERMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_TERRIERMON_X_FQNAME_LEN = sizeof(ALT_DMALL_TERRIERMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_THUNDERBALLMON_FQID_ARR[] = "dmall:thunderballmon";
    inline static constexpr const char* ALT_DMALL_THUNDERBALLMON_FQID = ALT_DMALL_THUNDERBALLMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_THUNDERBALLMON_FQID_LEN = sizeof(ALT_DMALL_THUNDERBALLMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_THUNDERBALLMON_FQNAME_ARR[] = "dmall:Thunderballmon";
    inline static constexpr const char* ALT_DMALL_THUNDERBALLMON_FQNAME = ALT_DMALL_THUNDERBALLMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_THUNDERBALLMON_FQNAME_LEN = sizeof(ALT_DMALL_THUNDERBALLMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_TIA_LUDOMON_FQID_ARR[] = "dmall:tia_ludomon";
    inline static constexpr const char* ALT_DMALL_TIA_LUDOMON_FQID = ALT_DMALL_TIA_LUDOMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_TIA_LUDOMON_FQID_LEN = sizeof(ALT_DMALL_TIA_LUDOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_TIA_LUDOMON_FQNAME_ARR[] = "dmall:Tia Ludomon";
    inline static constexpr const char* ALT_DMALL_TIA_LUDOMON_FQNAME = ALT_DMALL_TIA_LUDOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_TIA_LUDOMON_FQNAME_LEN = sizeof(ALT_DMALL_TIA_LUDOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_TIGER_VESPAMON_FQID_ARR[] = "dmall:tiger_vespamon";
    inline static constexpr const char* ALT_DMALL_TIGER_VESPAMON_FQID = ALT_DMALL_TIGER_VESPAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_TIGER_VESPAMON_FQID_LEN = sizeof(ALT_DMALL_TIGER_VESPAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_TIGER_VESPAMON_FQNAME_ARR[] = "dmall:Tiger Vespamon";
    inline static constexpr const char* ALT_DMALL_TIGER_VESPAMON_FQNAME = ALT_DMALL_TIGER_VESPAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_TIGER_VESPAMON_FQNAME_LEN = sizeof(ALT_DMALL_TIGER_VESPAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_TINKERMON_FQID_ARR[] = "dmall:tinkermon";
    inline static constexpr const char* ALT_DMALL_TINKERMON_FQID = ALT_DMALL_TINKERMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_TINKERMON_FQID_LEN = sizeof(ALT_DMALL_TINKERMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_TINKERMON_FQNAME_ARR[] = "dmall:Tinkermon";
    inline static constexpr const char* ALT_DMALL_TINKERMON_FQNAME = ALT_DMALL_TINKERMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_TINKERMON_FQNAME_LEN = sizeof(ALT_DMALL_TINKERMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_TITAMON_FQID_ARR[] = "dmall:titamon";
    inline static constexpr const char* ALT_DMALL_TITAMON_FQID = ALT_DMALL_TITAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_TITAMON_FQID_LEN = sizeof(ALT_DMALL_TITAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_TITAMON_FQNAME_ARR[] = "dmall:Titamon";
    inline static constexpr const char* ALT_DMALL_TITAMON_FQNAME = ALT_DMALL_TITAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_TITAMON_FQNAME_LEN = sizeof(ALT_DMALL_TITAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_TOBIUMON_FQID_ARR[] = "dmall:tobiumon";
    inline static constexpr const char* ALT_DMALL_TOBIUMON_FQID = ALT_DMALL_TOBIUMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_TOBIUMON_FQID_LEN = sizeof(ALT_DMALL_TOBIUMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_TOBIUMON_FQNAME_ARR[] = "dmall:Tobiumon";
    inline static constexpr const char* ALT_DMALL_TOBIUMON_FQNAME = ALT_DMALL_TOBIUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_TOBIUMON_FQNAME_LEN = sizeof(ALT_DMALL_TOBIUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_TOBUCATMON_FQID_ARR[] = "dmall:tobucatmon";
    inline static constexpr const char* ALT_DMALL_TOBUCATMON_FQID = ALT_DMALL_TOBUCATMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_TOBUCATMON_FQID_LEN = sizeof(ALT_DMALL_TOBUCATMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_TOBUCATMON_FQNAME_ARR[] = "dmall:Tobucatmon";
    inline static constexpr const char* ALT_DMALL_TOBUCATMON_FQNAME = ALT_DMALL_TOBUCATMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_TOBUCATMON_FQNAME_LEN = sizeof(ALT_DMALL_TOBUCATMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_TOGEMON_FQID_ARR[] = "dmall:togemon";
    inline static constexpr const char* ALT_DMALL_TOGEMON_FQID = ALT_DMALL_TOGEMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_TOGEMON_FQID_LEN = sizeof(ALT_DMALL_TOGEMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_TOGEMON_FQNAME_ARR[] = "dmall:Togemon";
    inline static constexpr const char* ALT_DMALL_TOGEMON_FQNAME = ALT_DMALL_TOGEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_TOGEMON_FQNAME_LEN = sizeof(ALT_DMALL_TOGEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_TOGEMON_X_FQID_ARR[] = "dmall:togemon_x";
    inline static constexpr const char* ALT_DMALL_TOGEMON_X_FQID = ALT_DMALL_TOGEMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_TOGEMON_X_FQID_LEN = sizeof(ALT_DMALL_TOGEMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_TOGEMON_X_FQNAME_ARR[] = "dmall:Togemon X";
    inline static constexpr const char* ALT_DMALL_TOGEMON_X_FQNAME = ALT_DMALL_TOGEMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_TOGEMON_X_FQNAME_LEN = sizeof(ALT_DMALL_TOGEMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_TOKOMON_X_FQID_ARR[] = "dmall:tokomon_x";
    inline static constexpr const char* ALT_DMALL_TOKOMON_X_FQID = ALT_DMALL_TOKOMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_TOKOMON_X_FQID_LEN = sizeof(ALT_DMALL_TOKOMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_TOKOMON_X_FQNAME_ARR[] = "dmall:Tokomon X";
    inline static constexpr const char* ALT_DMALL_TOKOMON_X_FQNAME = ALT_DMALL_TOKOMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_TOKOMON_X_FQNAME_LEN = sizeof(ALT_DMALL_TOKOMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_TONOSAMA_GEKOMON_FQID_ARR[] = "dmall:tonosama_gekomon";
    inline static constexpr const char* ALT_DMALL_TONOSAMA_GEKOMON_FQID = ALT_DMALL_TONOSAMA_GEKOMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_TONOSAMA_GEKOMON_FQID_LEN = sizeof(ALT_DMALL_TONOSAMA_GEKOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_TONOSAMA_GEKOMON_FQNAME_ARR[] = "dmall:Tonosama Gekomon";
    inline static constexpr const char* ALT_DMALL_TONOSAMA_GEKOMON_FQNAME = ALT_DMALL_TONOSAMA_GEKOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_TONOSAMA_GEKOMON_FQNAME_LEN = sizeof(ALT_DMALL_TONOSAMA_GEKOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_TORIKARA_BALLMON_FQID_ARR[] = "dmall:torikara_ballmon";
    inline static constexpr const char* ALT_DMALL_TORIKARA_BALLMON_FQID = ALT_DMALL_TORIKARA_BALLMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_TORIKARA_BALLMON_FQID_LEN = sizeof(ALT_DMALL_TORIKARA_BALLMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_TORIKARA_BALLMON_FQNAME_ARR[] = "dmall:Torikara Ballmon";
    inline static constexpr const char* ALT_DMALL_TORIKARA_BALLMON_FQNAME = ALT_DMALL_TORIKARA_BALLMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_TORIKARA_BALLMON_FQNAME_LEN = sizeof(ALT_DMALL_TORIKARA_BALLMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_TORTAMON_FQID_ARR[] = "dmall:tortamon";
    inline static constexpr const char* ALT_DMALL_TORTAMON_FQID = ALT_DMALL_TORTAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_TORTAMON_FQID_LEN = sizeof(ALT_DMALL_TORTAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_TORTAMON_FQNAME_ARR[] = "dmall:Tortamon";
    inline static constexpr const char* ALT_DMALL_TORTAMON_FQNAME = ALT_DMALL_TORTAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_TORTAMON_FQNAME_LEN = sizeof(ALT_DMALL_TORTAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_TOYAGUMON_BLACK_FQID_ARR[] = "dmall:toyagumon_black";
    inline static constexpr const char* ALT_DMALL_TOYAGUMON_BLACK_FQID = ALT_DMALL_TOYAGUMON_BLACK_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_TOYAGUMON_BLACK_FQID_LEN = sizeof(ALT_DMALL_TOYAGUMON_BLACK_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_TOYAGUMON_BLACK_FQNAME_ARR[] = "dmall:ToyAgumon (Black)";
    inline static constexpr const char* ALT_DMALL_TOYAGUMON_BLACK_FQNAME = ALT_DMALL_TOYAGUMON_BLACK_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_TOYAGUMON_BLACK_FQNAME_LEN = sizeof(ALT_DMALL_TOYAGUMON_BLACK_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_TOYAGUMON_FQID_ARR[] = "dmall:toyagumon";
    inline static constexpr const char* ALT_DMALL_TOYAGUMON_FQID = ALT_DMALL_TOYAGUMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_TOYAGUMON_FQID_LEN = sizeof(ALT_DMALL_TOYAGUMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_TOYAGUMON_FQNAME_ARR[] = "dmall:ToyAgumon";
    inline static constexpr const char* ALT_DMALL_TOYAGUMON_FQNAME = ALT_DMALL_TOYAGUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_TOYAGUMON_FQNAME_LEN = sizeof(ALT_DMALL_TOYAGUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_TRICERAMON_FQID_ARR[] = "dmall:triceramon";
    inline static constexpr const char* ALT_DMALL_TRICERAMON_FQID = ALT_DMALL_TRICERAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_TRICERAMON_FQID_LEN = sizeof(ALT_DMALL_TRICERAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_TRICERAMON_FQNAME_ARR[] = "dmall:Triceramon";
    inline static constexpr const char* ALT_DMALL_TRICERAMON_FQNAME = ALT_DMALL_TRICERAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_TRICERAMON_FQNAME_LEN = sizeof(ALT_DMALL_TRICERAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_TRICERAMON_X_FQID_ARR[] = "dmall:triceramon_x";
    inline static constexpr const char* ALT_DMALL_TRICERAMON_X_FQID = ALT_DMALL_TRICERAMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_TRICERAMON_X_FQID_LEN = sizeof(ALT_DMALL_TRICERAMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_TRICERAMON_X_FQNAME_ARR[] = "dmall:Triceramon X";
    inline static constexpr const char* ALT_DMALL_TRICERAMON_X_FQNAME = ALT_DMALL_TRICERAMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_TRICERAMON_X_FQNAME_LEN = sizeof(ALT_DMALL_TRICERAMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_TROOPMON_FQID_ARR[] = "dmall:troopmon";
    inline static constexpr const char* ALT_DMALL_TROOPMON_FQID = ALT_DMALL_TROOPMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_TROOPMON_FQID_LEN = sizeof(ALT_DMALL_TROOPMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_TROOPMON_FQNAME_ARR[] = "dmall:Troopmon";
    inline static constexpr const char* ALT_DMALL_TROOPMON_FQNAME = ALT_DMALL_TROOPMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_TROOPMON_FQNAME_LEN = sizeof(ALT_DMALL_TROOPMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_TSUBUMON_FQID_ARR[] = "dmall:tsubumon";
    inline static constexpr const char* ALT_DMALL_TSUBUMON_FQID = ALT_DMALL_TSUBUMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_TSUBUMON_FQID_LEN = sizeof(ALT_DMALL_TSUBUMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_TSUBUMON_FQNAME_ARR[] = "dmall:Tsubumon";
    inline static constexpr const char* ALT_DMALL_TSUBUMON_FQNAME = ALT_DMALL_TSUBUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_TSUBUMON_FQNAME_LEN = sizeof(ALT_DMALL_TSUBUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_TSUCHIDARUMON_FQID_ARR[] = "dmall:tsuchidarumon";
    inline static constexpr const char* ALT_DMALL_TSUCHIDARUMON_FQID = ALT_DMALL_TSUCHIDARUMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_TSUCHIDARUMON_FQID_LEN = sizeof(ALT_DMALL_TSUCHIDARUMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_TSUCHIDARUMON_FQNAME_ARR[] = "dmall:Tsuchidarumon";
    inline static constexpr const char* ALT_DMALL_TSUCHIDARUMON_FQNAME = ALT_DMALL_TSUCHIDARUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_TSUCHIDARUMON_FQNAME_LEN = sizeof(ALT_DMALL_TSUCHIDARUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_TSUMEMON_FQID_ARR[] = "dmall:tsumemon";
    inline static constexpr const char* ALT_DMALL_TSUMEMON_FQID = ALT_DMALL_TSUMEMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_TSUMEMON_FQID_LEN = sizeof(ALT_DMALL_TSUMEMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_TSUMEMON_FQNAME_ARR[] = "dmall:Tsumemon";
    inline static constexpr const char* ALT_DMALL_TSUMEMON_FQNAME = ALT_DMALL_TSUMEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_TSUMEMON_FQNAME_LEN = sizeof(ALT_DMALL_TSUMEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_TSUNOMON_FQID_ARR[] = "dmall:tsunomon";
    inline static constexpr const char* ALT_DMALL_TSUNOMON_FQID = ALT_DMALL_TSUNOMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_TSUNOMON_FQID_LEN = sizeof(ALT_DMALL_TSUNOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_TSUNOMON_FQNAME_ARR[] = "dmall:Tsunomon";
    inline static constexpr const char* ALT_DMALL_TSUNOMON_FQNAME = ALT_DMALL_TSUNOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_TSUNOMON_FQNAME_LEN = sizeof(ALT_DMALL_TSUNOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_TUNOMON_FQID_ARR[] = "dmall:tunomon";
    inline static constexpr const char* ALT_DMALL_TUNOMON_FQID = ALT_DMALL_TUNOMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_TUNOMON_FQID_LEN = sizeof(ALT_DMALL_TUNOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_TUNOMON_FQNAME_ARR[] = "dmall:Tunomon";
    inline static constexpr const char* ALT_DMALL_TUNOMON_FQNAME = ALT_DMALL_TUNOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_TUNOMON_FQNAME_LEN = sizeof(ALT_DMALL_TUNOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_TURUIEMON_FQID_ARR[] = "dmall:turuiemon";
    inline static constexpr const char* ALT_DMALL_TURUIEMON_FQID = ALT_DMALL_TURUIEMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_TURUIEMON_FQID_LEN = sizeof(ALT_DMALL_TURUIEMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_TURUIEMON_FQNAME_ARR[] = "dmall:Turuiemon";
    inline static constexpr const char* ALT_DMALL_TURUIEMON_FQNAME = ALT_DMALL_TURUIEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_TURUIEMON_FQNAME_LEN = sizeof(ALT_DMALL_TURUIEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_TYLOMON_X_FQID_ARR[] = "dmall:tylomon_x";
    inline static constexpr const char* ALT_DMALL_TYLOMON_X_FQID = ALT_DMALL_TYLOMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_TYLOMON_X_FQID_LEN = sizeof(ALT_DMALL_TYLOMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_TYLOMON_X_FQNAME_ARR[] = "dmall:Tylomon X";
    inline static constexpr const char* ALT_DMALL_TYLOMON_X_FQNAME = ALT_DMALL_TYLOMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_TYLOMON_X_FQNAME_LEN = sizeof(ALT_DMALL_TYLOMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_TYRANNOMON_FQID_ARR[] = "dmall:tyrannomon";
    inline static constexpr const char* ALT_DMALL_TYRANNOMON_FQID = ALT_DMALL_TYRANNOMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_TYRANNOMON_FQID_LEN = sizeof(ALT_DMALL_TYRANNOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_TYRANNOMON_FQNAME_ARR[] = "dmall:Tyrannomon";
    inline static constexpr const char* ALT_DMALL_TYRANNOMON_FQNAME = ALT_DMALL_TYRANNOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_TYRANNOMON_FQNAME_LEN = sizeof(ALT_DMALL_TYRANNOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_TYRANNOMON_X_FQID_ARR[] = "dmall:tyrannomon_x";
    inline static constexpr const char* ALT_DMALL_TYRANNOMON_X_FQID = ALT_DMALL_TYRANNOMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_TYRANNOMON_X_FQID_LEN = sizeof(ALT_DMALL_TYRANNOMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_TYRANNOMON_X_FQNAME_ARR[] = "dmall:Tyrannomon X";
    inline static constexpr const char* ALT_DMALL_TYRANNOMON_X_FQNAME = ALT_DMALL_TYRANNOMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_TYRANNOMON_X_FQNAME_LEN = sizeof(ALT_DMALL_TYRANNOMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_TYRANOMON_FQID_ARR[] = "dmall:tyranomon";
    inline static constexpr const char* ALT_DMALL_TYRANOMON_FQID = ALT_DMALL_TYRANOMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_TYRANOMON_FQID_LEN = sizeof(ALT_DMALL_TYRANOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_TYRANOMON_FQNAME_ARR[] = "dmall:Tyranomon";
    inline static constexpr const char* ALT_DMALL_TYRANOMON_FQNAME = ALT_DMALL_TYRANOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_TYRANOMON_FQNAME_LEN = sizeof(ALT_DMALL_TYRANOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_TYRANOMON_X_FQID_ARR[] = "dmall:tyranomon_x";
    inline static constexpr const char* ALT_DMALL_TYRANOMON_X_FQID = ALT_DMALL_TYRANOMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_TYRANOMON_X_FQID_LEN = sizeof(ALT_DMALL_TYRANOMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_TYRANOMON_X_FQNAME_ARR[] = "dmall:Tyranomon X";
    inline static constexpr const char* ALT_DMALL_TYRANOMON_X_FQNAME = ALT_DMALL_TYRANOMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_TYRANOMON_X_FQNAME_LEN = sizeof(ALT_DMALL_TYRANOMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_ULFORCE_V_DRAMON_FQID_ARR[] = "dmall:ulforce_v_dramon";
    inline static constexpr const char* ALT_DMALL_ULFORCE_V_DRAMON_FQID = ALT_DMALL_ULFORCE_V_DRAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_ULFORCE_V_DRAMON_FQID_LEN = sizeof(ALT_DMALL_ULFORCE_V_DRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_ULFORCE_V_DRAMON_FQNAME_ARR[] = "dmall:Ulforce V-dramon";
    inline static constexpr const char* ALT_DMALL_ULFORCE_V_DRAMON_FQNAME = ALT_DMALL_ULFORCE_V_DRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_ULFORCE_V_DRAMON_FQNAME_LEN = sizeof(ALT_DMALL_ULFORCE_V_DRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_ULFORCE_V_DRAMON_X_FQID_ARR[] = "dmall:ulforce_v_dramon_x";
    inline static constexpr const char* ALT_DMALL_ULFORCE_V_DRAMON_X_FQID = ALT_DMALL_ULFORCE_V_DRAMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_ULFORCE_V_DRAMON_X_FQID_LEN = sizeof(ALT_DMALL_ULFORCE_V_DRAMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_ULFORCE_V_DRAMON_X_FQNAME_ARR[] = "dmall:Ulforce V-dramon X";
    inline static constexpr const char* ALT_DMALL_ULFORCE_V_DRAMON_X_FQNAME = ALT_DMALL_ULFORCE_V_DRAMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_ULFORCE_V_DRAMON_X_FQNAME_LEN = sizeof(ALT_DMALL_ULFORCE_V_DRAMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_ULTIMATE_BRACHIMON_FQID_ARR[] = "dmall:ultimate_brachimon";
    inline static constexpr const char* ALT_DMALL_ULTIMATE_BRACHIMON_FQID = ALT_DMALL_ULTIMATE_BRACHIMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_ULTIMATE_BRACHIMON_FQID_LEN = sizeof(ALT_DMALL_ULTIMATE_BRACHIMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_ULTIMATE_BRACHIMON_FQNAME_ARR[] = "dmall:Ultimate Brachimon";
    inline static constexpr const char* ALT_DMALL_ULTIMATE_BRACHIMON_FQNAME = ALT_DMALL_ULTIMATE_BRACHIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_ULTIMATE_BRACHIMON_FQNAME_LEN = sizeof(ALT_DMALL_ULTIMATE_BRACHIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_UPAMON_FQID_ARR[] = "dmall:upamon";
    inline static constexpr const char* ALT_DMALL_UPAMON_FQID = ALT_DMALL_UPAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_UPAMON_FQID_LEN = sizeof(ALT_DMALL_UPAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_UPAMON_FQNAME_ARR[] = "dmall:Upamon";
    inline static constexpr const char* ALT_DMALL_UPAMON_FQNAME = ALT_DMALL_UPAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_UPAMON_FQNAME_LEN = sizeof(ALT_DMALL_UPAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_VADEMON_FQID_ARR[] = "dmall:vademon";
    inline static constexpr const char* ALT_DMALL_VADEMON_FQID = ALT_DMALL_VADEMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_VADEMON_FQID_LEN = sizeof(ALT_DMALL_VADEMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_VADEMON_FQNAME_ARR[] = "dmall:Vademon";
    inline static constexpr const char* ALT_DMALL_VADEMON_FQNAME = ALT_DMALL_VADEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_VADEMON_FQNAME_LEN = sizeof(ALT_DMALL_VADEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_VALDURMON_FQID_ARR[] = "dmall:valdurmon";
    inline static constexpr const char* ALT_DMALL_VALDURMON_FQID = ALT_DMALL_VALDURMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_VALDURMON_FQID_LEN = sizeof(ALT_DMALL_VALDURMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_VALDURMON_FQNAME_ARR[] = "dmall:Valdurmon";
    inline static constexpr const char* ALT_DMALL_VALDURMON_FQNAME = ALT_DMALL_VALDURMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_VALDURMON_FQNAME_LEN = sizeof(ALT_DMALL_VALDURMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_VAMDEMON_FQID_ARR[] = "dmall:vamdemon";
    inline static constexpr const char* ALT_DMALL_VAMDEMON_FQID = ALT_DMALL_VAMDEMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_VAMDEMON_FQID_LEN = sizeof(ALT_DMALL_VAMDEMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_VAMDEMON_FQNAME_ARR[] = "dmall:Vamdemon";
    inline static constexpr const char* ALT_DMALL_VAMDEMON_FQNAME = ALT_DMALL_VAMDEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_VAMDEMON_FQNAME_LEN = sizeof(ALT_DMALL_VAMDEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_VAMDEMON_X_FQID_ARR[] = "dmall:vamdemon_x";
    inline static constexpr const char* ALT_DMALL_VAMDEMON_X_FQID = ALT_DMALL_VAMDEMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_VAMDEMON_X_FQID_LEN = sizeof(ALT_DMALL_VAMDEMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_VAMDEMON_X_FQNAME_ARR[] = "dmall:Vamdemon X";
    inline static constexpr const char* ALT_DMALL_VAMDEMON_X_FQNAME = ALT_DMALL_VAMDEMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_VAMDEMON_X_FQNAME_LEN = sizeof(ALT_DMALL_VAMDEMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_V_DRAMON_BLACK_FQID_ARR[] = "dmall:v_dramon_black";
    inline static constexpr const char* ALT_DMALL_V_DRAMON_BLACK_FQID = ALT_DMALL_V_DRAMON_BLACK_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_V_DRAMON_BLACK_FQID_LEN = sizeof(ALT_DMALL_V_DRAMON_BLACK_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_V_DRAMON_BLACK_FQNAME_ARR[] = "dmall:V-dramon (Black)";
    inline static constexpr const char* ALT_DMALL_V_DRAMON_BLACK_FQNAME = ALT_DMALL_V_DRAMON_BLACK_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_V_DRAMON_BLACK_FQNAME_LEN = sizeof(ALT_DMALL_V_DRAMON_BLACK_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_V_DRAMON_FQID_ARR[] = "dmall:v_dramon";
    inline static constexpr const char* ALT_DMALL_V_DRAMON_FQID = ALT_DMALL_V_DRAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_V_DRAMON_FQID_LEN = sizeof(ALT_DMALL_V_DRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_V_DRAMON_FQNAME_ARR[] = "dmall:V-dramon";
    inline static constexpr const char* ALT_DMALL_V_DRAMON_FQNAME = ALT_DMALL_V_DRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_V_DRAMON_FQNAME_LEN = sizeof(ALT_DMALL_V_DRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_VEGIMON_FQID_ARR[] = "dmall:vegimon";
    inline static constexpr const char* ALT_DMALL_VEGIMON_FQID = ALT_DMALL_VEGIMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_VEGIMON_FQID_LEN = sizeof(ALT_DMALL_VEGIMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_VEGIMON_FQNAME_ARR[] = "dmall:Vegimon";
    inline static constexpr const char* ALT_DMALL_VEGIMON_FQNAME = ALT_DMALL_VEGIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_VEGIMON_FQNAME_LEN = sizeof(ALT_DMALL_VEGIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_VELGRMON_FQID_ARR[] = "dmall:velgrmon";
    inline static constexpr const char* ALT_DMALL_VELGRMON_FQID = ALT_DMALL_VELGRMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_VELGRMON_FQID_LEN = sizeof(ALT_DMALL_VELGRMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_VELGRMON_FQNAME_ARR[] = "dmall:Velgrmon";
    inline static constexpr const char* ALT_DMALL_VELGRMON_FQNAME = ALT_DMALL_VELGRMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_VELGRMON_FQNAME_LEN = sizeof(ALT_DMALL_VELGRMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_VENOM_VAMDEMON_FQID_ARR[] = "dmall:venom_vamdemon";
    inline static constexpr const char* ALT_DMALL_VENOM_VAMDEMON_FQID = ALT_DMALL_VENOM_VAMDEMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_VENOM_VAMDEMON_FQID_LEN = sizeof(ALT_DMALL_VENOM_VAMDEMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_VENOM_VAMDEMON_FQNAME_ARR[] = "dmall:Venom Vamdemon";
    inline static constexpr const char* ALT_DMALL_VENOM_VAMDEMON_FQNAME = ALT_DMALL_VENOM_VAMDEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_VENOM_VAMDEMON_FQNAME_LEN = sizeof(ALT_DMALL_VENOM_VAMDEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_VERMILLIMON_FQID_ARR[] = "dmall:vermillimon";
    inline static constexpr const char* ALT_DMALL_VERMILLIMON_FQID = ALT_DMALL_VERMILLIMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_VERMILLIMON_FQID_LEN = sizeof(ALT_DMALL_VERMILLIMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_VERMILLIMON_FQNAME_ARR[] = "dmall:Vermillimon";
    inline static constexpr const char* ALT_DMALL_VERMILLIMON_FQNAME = ALT_DMALL_VERMILLIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_VERMILLIMON_FQNAME_LEN = sizeof(ALT_DMALL_VERMILLIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_V_MON_FQID_ARR[] = "dmall:v_mon";
    inline static constexpr const char* ALT_DMALL_V_MON_FQID = ALT_DMALL_V_MON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_V_MON_FQID_LEN = sizeof(ALT_DMALL_V_MON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_V_MON_FQNAME_ARR[] = "dmall:V-mon";
    inline static constexpr const char* ALT_DMALL_V_MON_FQNAME = ALT_DMALL_V_MON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_V_MON_FQNAME_LEN = sizeof(ALT_DMALL_V_MON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_VOLCANICDRAMON_FQID_ARR[] = "dmall:volcanicdramon";
    inline static constexpr const char* ALT_DMALL_VOLCANICDRAMON_FQID = ALT_DMALL_VOLCANICDRAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_VOLCANICDRAMON_FQID_LEN = sizeof(ALT_DMALL_VOLCANICDRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_VOLCANICDRAMON_FQNAME_ARR[] = "dmall:Volcanicdramon";
    inline static constexpr const char* ALT_DMALL_VOLCANICDRAMON_FQNAME = ALT_DMALL_VOLCANICDRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_VOLCANICDRAMON_FQNAME_LEN = sizeof(ALT_DMALL_VOLCANICDRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_VOLTO_BAUTAMON_FQID_ARR[] = "dmall:volto_bautamon";
    inline static constexpr const char* ALT_DMALL_VOLTO_BAUTAMON_FQID = ALT_DMALL_VOLTO_BAUTAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_VOLTO_BAUTAMON_FQID_LEN = sizeof(ALT_DMALL_VOLTO_BAUTAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_VOLTO_BAUTAMON_FQNAME_ARR[] = "dmall:Volto Bautamon";
    inline static constexpr const char* ALT_DMALL_VOLTO_BAUTAMON_FQNAME = ALT_DMALL_VOLTO_BAUTAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_VOLTO_BAUTAMON_FQNAME_LEN = sizeof(ALT_DMALL_VOLTO_BAUTAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_VORVOMON_FQID_ARR[] = "dmall:vorvomon";
    inline static constexpr const char* ALT_DMALL_VORVOMON_FQID = ALT_DMALL_VORVOMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_VORVOMON_FQID_LEN = sizeof(ALT_DMALL_VORVOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_VORVOMON_FQNAME_ARR[] = "dmall:Vorvomon";
    inline static constexpr const char* ALT_DMALL_VORVOMON_FQNAME = ALT_DMALL_VORVOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_VORVOMON_FQNAME_LEN = sizeof(ALT_DMALL_VORVOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_WANYAMON_FQID_ARR[] = "dmall:wanyamon";
    inline static constexpr const char* ALT_DMALL_WANYAMON_FQID = ALT_DMALL_WANYAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_WANYAMON_FQID_LEN = sizeof(ALT_DMALL_WANYAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_WANYAMON_FQNAME_ARR[] = "dmall:Wanyamon";
    inline static constexpr const char* ALT_DMALL_WANYAMON_FQNAME = ALT_DMALL_WANYAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_WANYAMON_FQNAME_LEN = sizeof(ALT_DMALL_WANYAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_WAR_GREYMON_FQID_ARR[] = "dmall:war_greymon";
    inline static constexpr const char* ALT_DMALL_WAR_GREYMON_FQID = ALT_DMALL_WAR_GREYMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_WAR_GREYMON_FQID_LEN = sizeof(ALT_DMALL_WAR_GREYMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_WAR_GREYMON_FQNAME_ARR[] = "dmall:War Greymon";
    inline static constexpr const char* ALT_DMALL_WAR_GREYMON_FQNAME = ALT_DMALL_WAR_GREYMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_WAR_GREYMON_FQNAME_LEN = sizeof(ALT_DMALL_WAR_GREYMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_WAR_GREYMON_X_FQID_ARR[] = "dmall:war_greymon_x";
    inline static constexpr const char* ALT_DMALL_WAR_GREYMON_X_FQID = ALT_DMALL_WAR_GREYMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_WAR_GREYMON_X_FQID_LEN = sizeof(ALT_DMALL_WAR_GREYMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_WAR_GREYMON_X_FQNAME_ARR[] = "dmall:War Greymon X";
    inline static constexpr const char* ALT_DMALL_WAR_GREYMON_X_FQNAME = ALT_DMALL_WAR_GREYMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_WAR_GREYMON_X_FQNAME_LEN = sizeof(ALT_DMALL_WAR_GREYMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_WARU_MONZAEMON_FQID_ARR[] = "dmall:waru_monzaemon";
    inline static constexpr const char* ALT_DMALL_WARU_MONZAEMON_FQID = ALT_DMALL_WARU_MONZAEMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_WARU_MONZAEMON_FQID_LEN = sizeof(ALT_DMALL_WARU_MONZAEMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_WARU_MONZAEMON_FQNAME_ARR[] = "dmall:Waru Monzaemon";
    inline static constexpr const char* ALT_DMALL_WARU_MONZAEMON_FQNAME = ALT_DMALL_WARU_MONZAEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_WARU_MONZAEMON_FQNAME_LEN = sizeof(ALT_DMALL_WARU_MONZAEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_WARU_SEADRAMON_FQID_ARR[] = "dmall:waru_seadramon";
    inline static constexpr const char* ALT_DMALL_WARU_SEADRAMON_FQID = ALT_DMALL_WARU_SEADRAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_WARU_SEADRAMON_FQID_LEN = sizeof(ALT_DMALL_WARU_SEADRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_WARU_SEADRAMON_FQNAME_ARR[] = "dmall:Waru Seadramon";
    inline static constexpr const char* ALT_DMALL_WARU_SEADRAMON_FQNAME = ALT_DMALL_WARU_SEADRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_WARU_SEADRAMON_FQNAME_LEN = sizeof(ALT_DMALL_WARU_SEADRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_WASPMON_FQID_ARR[] = "dmall:waspmon";
    inline static constexpr const char* ALT_DMALL_WASPMON_FQID = ALT_DMALL_WASPMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_WASPMON_FQID_LEN = sizeof(ALT_DMALL_WASPMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_WASPMON_FQNAME_ARR[] = "dmall:Waspmon";
    inline static constexpr const char* ALT_DMALL_WASPMON_FQNAME = ALT_DMALL_WASPMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_WASPMON_FQNAME_LEN = sizeof(ALT_DMALL_WASPMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_WEREGARURUMON_BLACK_FQID_ARR[] = "dmall:weregarurumon_black";
    inline static constexpr const char* ALT_DMALL_WEREGARURUMON_BLACK_FQID = ALT_DMALL_WEREGARURUMON_BLACK_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_WEREGARURUMON_BLACK_FQID_LEN = sizeof(ALT_DMALL_WEREGARURUMON_BLACK_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_WEREGARURUMON_BLACK_FQNAME_ARR[] = "dmall:WereGarurumon (Black)";
    inline static constexpr const char* ALT_DMALL_WEREGARURUMON_BLACK_FQNAME = ALT_DMALL_WEREGARURUMON_BLACK_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_WEREGARURUMON_BLACK_FQNAME_LEN = sizeof(ALT_DMALL_WEREGARURUMON_BLACK_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_WERE_GARURUMON_FQID_ARR[] = "dmall:were_garurumon";
    inline static constexpr const char* ALT_DMALL_WERE_GARURUMON_FQID = ALT_DMALL_WERE_GARURUMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_WERE_GARURUMON_FQID_LEN = sizeof(ALT_DMALL_WERE_GARURUMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_WERE_GARURUMON_FQNAME_ARR[] = "dmall:Were Garurumon";
    inline static constexpr const char* ALT_DMALL_WERE_GARURUMON_FQNAME = ALT_DMALL_WERE_GARURUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_WERE_GARURUMON_FQNAME_LEN = sizeof(ALT_DMALL_WERE_GARURUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_WERE_GARURUMON_X_FQID_ARR[] = "dmall:were_garurumon_x";
    inline static constexpr const char* ALT_DMALL_WERE_GARURUMON_X_FQID = ALT_DMALL_WERE_GARURUMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_WERE_GARURUMON_X_FQID_LEN = sizeof(ALT_DMALL_WERE_GARURUMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_WERE_GARURUMON_X_FQNAME_ARR[] = "dmall:Were Garurumon X";
    inline static constexpr const char* ALT_DMALL_WERE_GARURUMON_X_FQNAME = ALT_DMALL_WERE_GARURUMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_WERE_GARURUMON_X_FQNAME_LEN = sizeof(ALT_DMALL_WERE_GARURUMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_WHAMON_FQID_ARR[] = "dmall:whamon";
    inline static constexpr const char* ALT_DMALL_WHAMON_FQID = ALT_DMALL_WHAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_WHAMON_FQID_LEN = sizeof(ALT_DMALL_WHAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_WHAMON_FQNAME_ARR[] = "dmall:Whamon";
    inline static constexpr const char* ALT_DMALL_WHAMON_FQNAME = ALT_DMALL_WHAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_WHAMON_FQNAME_LEN = sizeof(ALT_DMALL_WHAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_WIZARMON_FQID_ARR[] = "dmall:wizarmon";
    inline static constexpr const char* ALT_DMALL_WIZARMON_FQID = ALT_DMALL_WIZARMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_WIZARMON_FQID_LEN = sizeof(ALT_DMALL_WIZARMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_WIZARMON_FQNAME_ARR[] = "dmall:Wizarmon";
    inline static constexpr const char* ALT_DMALL_WIZARMON_FQNAME = ALT_DMALL_WIZARMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_WIZARMON_FQNAME_LEN = sizeof(ALT_DMALL_WIZARMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_WIZARMON_X_FQID_ARR[] = "dmall:wizarmon_x";
    inline static constexpr const char* ALT_DMALL_WIZARMON_X_FQID = ALT_DMALL_WIZARMON_X_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_WIZARMON_X_FQID_LEN = sizeof(ALT_DMALL_WIZARMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_WIZARMON_X_FQNAME_ARR[] = "dmall:Wizarmon X";
    inline static constexpr const char* ALT_DMALL_WIZARMON_X_FQNAME = ALT_DMALL_WIZARMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_WIZARMON_X_FQNAME_LEN = sizeof(ALT_DMALL_WIZARMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_WOODMON_FQID_ARR[] = "dmall:woodmon";
    inline static constexpr const char* ALT_DMALL_WOODMON_FQID = ALT_DMALL_WOODMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_WOODMON_FQID_LEN = sizeof(ALT_DMALL_WOODMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_WOODMON_FQNAME_ARR[] = "dmall:Woodmon";
    inline static constexpr const char* ALT_DMALL_WOODMON_FQNAME = ALT_DMALL_WOODMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_WOODMON_FQNAME_LEN = sizeof(ALT_DMALL_WOODMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_WORMMON_FQID_ARR[] = "dmall:wormmon";
    inline static constexpr const char* ALT_DMALL_WORMMON_FQID = ALT_DMALL_WORMMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_WORMMON_FQID_LEN = sizeof(ALT_DMALL_WORMMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_WORMMON_FQNAME_ARR[] = "dmall:Wormmon";
    inline static constexpr const char* ALT_DMALL_WORMMON_FQNAME = ALT_DMALL_WORMMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_WORMMON_FQNAME_LEN = sizeof(ALT_DMALL_WORMMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_XIAOMON_FQID_ARR[] = "dmall:xiaomon";
    inline static constexpr const char* ALT_DMALL_XIAOMON_FQID = ALT_DMALL_XIAOMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_XIAOMON_FQID_LEN = sizeof(ALT_DMALL_XIAOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_XIAOMON_FQNAME_ARR[] = "dmall:Xiaomon";
    inline static constexpr const char* ALT_DMALL_XIAOMON_FQNAME = ALT_DMALL_XIAOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_XIAOMON_FQNAME_LEN = sizeof(ALT_DMALL_XIAOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_XV_MON_BLACK_FQID_ARR[] = "dmall:xv_mon_black";
    inline static constexpr const char* ALT_DMALL_XV_MON_BLACK_FQID = ALT_DMALL_XV_MON_BLACK_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_XV_MON_BLACK_FQID_LEN = sizeof(ALT_DMALL_XV_MON_BLACK_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_XV_MON_BLACK_FQNAME_ARR[] = "dmall:XV-mon (Black)";
    inline static constexpr const char* ALT_DMALL_XV_MON_BLACK_FQNAME = ALT_DMALL_XV_MON_BLACK_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_XV_MON_BLACK_FQNAME_LEN = sizeof(ALT_DMALL_XV_MON_BLACK_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_XV_MON_FQID_ARR[] = "dmall:xv_mon";
    inline static constexpr const char* ALT_DMALL_XV_MON_FQID = ALT_DMALL_XV_MON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_XV_MON_FQID_LEN = sizeof(ALT_DMALL_XV_MON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_XV_MON_FQNAME_ARR[] = "dmall:XV-mon";
    inline static constexpr const char* ALT_DMALL_XV_MON_FQNAME = ALT_DMALL_XV_MON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_XV_MON_FQNAME_LEN = sizeof(ALT_DMALL_XV_MON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_YAAMON_FQID_ARR[] = "dmall:yaamon";
    inline static constexpr const char* ALT_DMALL_YAAMON_FQID = ALT_DMALL_YAAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_YAAMON_FQID_LEN = sizeof(ALT_DMALL_YAAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_YAAMON_FQNAME_ARR[] = "dmall:Yaamon";
    inline static constexpr const char* ALT_DMALL_YAAMON_FQNAME = ALT_DMALL_YAAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_YAAMON_FQNAME_LEN = sizeof(ALT_DMALL_YAAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_YANMAMON_FQID_ARR[] = "dmall:yanmamon";
    inline static constexpr const char* ALT_DMALL_YANMAMON_FQID = ALT_DMALL_YANMAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_YANMAMON_FQID_LEN = sizeof(ALT_DMALL_YANMAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_YANMAMON_FQNAME_ARR[] = "dmall:Yanmamon";
    inline static constexpr const char* ALT_DMALL_YANMAMON_FQNAME = ALT_DMALL_YANMAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_YANMAMON_FQNAME_LEN = sizeof(ALT_DMALL_YANMAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_YATAGARAMON_2006_FQID_ARR[] = "dmall:yatagaramon_2006";
    inline static constexpr const char* ALT_DMALL_YATAGARAMON_2006_FQID = ALT_DMALL_YATAGARAMON_2006_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_YATAGARAMON_2006_FQID_LEN = sizeof(ALT_DMALL_YATAGARAMON_2006_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_YATAGARAMON_2006_FQNAME_ARR[] = "dmall:Yatagaramon (2006)";
    inline static constexpr const char* ALT_DMALL_YATAGARAMON_2006_FQNAME = ALT_DMALL_YATAGARAMON_2006_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_YATAGARAMON_2006_FQNAME_LEN = sizeof(ALT_DMALL_YATAGARAMON_2006_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_YATAGARAMON_FQID_ARR[] = "dmall:yatagaramon";
    inline static constexpr const char* ALT_DMALL_YATAGARAMON_FQID = ALT_DMALL_YATAGARAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_YATAGARAMON_FQID_LEN = sizeof(ALT_DMALL_YATAGARAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_YATAGARAMON_FQNAME_ARR[] = "dmall:Yatagaramon";
    inline static constexpr const char* ALT_DMALL_YATAGARAMON_FQNAME = ALT_DMALL_YATAGARAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_YATAGARAMON_FQNAME_LEN = sizeof(ALT_DMALL_YATAGARAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_YOUKOMON_FQID_ARR[] = "dmall:youkomon";
    inline static constexpr const char* ALT_DMALL_YOUKOMON_FQID = ALT_DMALL_YOUKOMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_YOUKOMON_FQID_LEN = sizeof(ALT_DMALL_YOUKOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_YOUKOMON_FQNAME_ARR[] = "dmall:Youkomon";
    inline static constexpr const char* ALT_DMALL_YOUKOMON_FQNAME = ALT_DMALL_YOUKOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_YOUKOMON_FQNAME_LEN = sizeof(ALT_DMALL_YOUKOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_YUKI_AGUMON_FQID_ARR[] = "dmall:yuki_agumon";
    inline static constexpr const char* ALT_DMALL_YUKI_AGUMON_FQID = ALT_DMALL_YUKI_AGUMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_YUKI_AGUMON_FQID_LEN = sizeof(ALT_DMALL_YUKI_AGUMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_YUKI_AGUMON_FQNAME_ARR[] = "dmall:Yuki Agumon";
    inline static constexpr const char* ALT_DMALL_YUKI_AGUMON_FQNAME = ALT_DMALL_YUKI_AGUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_YUKI_AGUMON_FQNAME_LEN = sizeof(ALT_DMALL_YUKI_AGUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_YUKIDARUMON_FQID_ARR[] = "dmall:yukidarumon";
    inline static constexpr const char* ALT_DMALL_YUKIDARUMON_FQID = ALT_DMALL_YUKIDARUMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_YUKIDARUMON_FQID_LEN = sizeof(ALT_DMALL_YUKIDARUMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_YUKIDARUMON_FQNAME_ARR[] = "dmall:Yukidarumon";
    inline static constexpr const char* ALT_DMALL_YUKIDARUMON_FQNAME = ALT_DMALL_YUKIDARUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_YUKIDARUMON_FQNAME_LEN = sizeof(ALT_DMALL_YUKIDARUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_YUKIMI_BOTAMON_FQID_ARR[] = "dmall:yukimi_botamon";
    inline static constexpr const char* ALT_DMALL_YUKIMI_BOTAMON_FQID = ALT_DMALL_YUKIMI_BOTAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_YUKIMI_BOTAMON_FQID_LEN = sizeof(ALT_DMALL_YUKIMI_BOTAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_YUKIMI_BOTAMON_FQNAME_ARR[] = "dmall:Yukimi Botamon";
    inline static constexpr const char* ALT_DMALL_YUKIMI_BOTAMON_FQNAME = ALT_DMALL_YUKIMI_BOTAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_YUKIMI_BOTAMON_FQNAME_LEN = sizeof(ALT_DMALL_YUKIMI_BOTAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_YURAMON_FQID_ARR[] = "dmall:yuramon";
    inline static constexpr const char* ALT_DMALL_YURAMON_FQID = ALT_DMALL_YURAMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_YURAMON_FQID_LEN = sizeof(ALT_DMALL_YURAMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_YURAMON_FQNAME_ARR[] = "dmall:Yuramon";
    inline static constexpr const char* ALT_DMALL_YURAMON_FQNAME = ALT_DMALL_YURAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_YURAMON_FQNAME_LEN = sizeof(ALT_DMALL_YURAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_ZASSOUMON_FQID_ARR[] = "dmall:zassoumon";
    inline static constexpr const char* ALT_DMALL_ZASSOUMON_FQID = ALT_DMALL_ZASSOUMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_ZASSOUMON_FQID_LEN = sizeof(ALT_DMALL_ZASSOUMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_ZASSOUMON_FQNAME_ARR[] = "dmall:Zassoumon";
    inline static constexpr const char* ALT_DMALL_ZASSOUMON_FQNAME = ALT_DMALL_ZASSOUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_ZASSOUMON_FQNAME_LEN = sizeof(ALT_DMALL_ZASSOUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_ZENIMON_FQID_ARR[] = "dmall:zenimon";
    inline static constexpr const char* ALT_DMALL_ZENIMON_FQID = ALT_DMALL_ZENIMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_ZENIMON_FQID_LEN = sizeof(ALT_DMALL_ZENIMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_ZENIMON_FQNAME_ARR[] = "dmall:Zenimon";
    inline static constexpr const char* ALT_DMALL_ZENIMON_FQNAME = ALT_DMALL_ZENIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_ZENIMON_FQNAME_LEN = sizeof(ALT_DMALL_ZENIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_ZERIMON_FQID_ARR[] = "dmall:zerimon";
    inline static constexpr const char* ALT_DMALL_ZERIMON_FQID = ALT_DMALL_ZERIMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_ZERIMON_FQID_LEN = sizeof(ALT_DMALL_ZERIMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_ZERIMON_FQNAME_ARR[] = "dmall:Zerimon";
    inline static constexpr const char* ALT_DMALL_ZERIMON_FQNAME = ALT_DMALL_ZERIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_ZERIMON_FQNAME_LEN = sizeof(ALT_DMALL_ZERIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_ZUDOMON_FQID_ARR[] = "dmall:zudomon";
    inline static constexpr const char* ALT_DMALL_ZUDOMON_FQID = ALT_DMALL_ZUDOMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_ZUDOMON_FQID_LEN = sizeof(ALT_DMALL_ZUDOMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_ZUDOMON_FQNAME_ARR[] = "dmall:Zudomon";
    inline static constexpr const char* ALT_DMALL_ZUDOMON_FQNAME = ALT_DMALL_ZUDOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_ZUDOMON_FQNAME_LEN = sizeof(ALT_DMALL_ZUDOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_DMALL_ZURUMON_FQID_ARR[] = "dmall:zurumon";
    inline static constexpr const char* ALT_DMALL_ZURUMON_FQID = ALT_DMALL_ZURUMON_FQID_ARR;
    inline static constexpr size_t ALT_DMALL_ZURUMON_FQID_LEN = sizeof(ALT_DMALL_ZURUMON_FQID_ARR)-1;
    inline static constexpr char ALT_DMALL_ZURUMON_FQNAME_ARR[] = "dmall:Zurumon";
    inline static constexpr const char* ALT_DMALL_ZURUMON_FQNAME = ALT_DMALL_ZURUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_DMALL_ZURUMON_FQNAME_LEN = sizeof(ALT_DMALL_ZURUMON_FQNAME_ARR)-1;


    static const config_animation_entry_t dmall_alt_animation_table[] = {
        { DMALL_AEGISDRAMON_NAME, DMALL_AEGISDRAMON_ID, ALT_DMALL_AEGISDRAMON_FQID, ALT_DMALL_AEGISDRAMON_FQNAME, DMALL_AEGISDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Aegisdramon
        { DMALL_AERO_V_DRAMON_NAME, DMALL_AERO_V_DRAMON_ID, ALT_DMALL_AERO_V_DRAMON_FQID, ALT_DMALL_AERO_V_DRAMON_FQNAME, DMALL_AERO_V_DRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Aero V-dramon
        { DMALL_AGUMON_2006_NAME, DMALL_AGUMON_2006_ID, ALT_DMALL_AGUMON_2006_FQID, ALT_DMALL_AGUMON_2006_FQNAME, DMALL_AGUMON_2006_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Agumon (2006)
        { DMALL_AGUMON_BLACK_NAME, DMALL_AGUMON_BLACK_ID, ALT_DMALL_AGUMON_BLACK_FQID, ALT_DMALL_AGUMON_BLACK_FQNAME, DMALL_AGUMON_BLACK_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Agumon (Black)
        { DMALL_AGUMON_BLACK_X_NAME, DMALL_AGUMON_BLACK_X_ID, ALT_DMALL_AGUMON_BLACK_X_FQID, ALT_DMALL_AGUMON_BLACK_X_FQNAME, DMALL_AGUMON_BLACK_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Agumon (Black) X
        { DMALL_AGUMON_NAME, DMALL_AGUMON_ID, ALT_DMALL_AGUMON_FQID, ALT_DMALL_AGUMON_FQNAME, DMALL_AGUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Agumon
        { DMALL_AGUMON_X_NAME, DMALL_AGUMON_X_ID, ALT_DMALL_AGUMON_X_FQID, ALT_DMALL_AGUMON_X_FQNAME, DMALL_AGUMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Agumon X
        { DMALL_AGUMON_YUKI_NO_KIZUNA_NAME, DMALL_AGUMON_YUKI_NO_KIZUNA_ID, ALT_DMALL_AGUMON_YUKI_NO_KIZUNA_FQID, ALT_DMALL_AGUMON_YUKI_NO_KIZUNA_FQNAME, DMALL_AGUMON_YUKI_NO_KIZUNA_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Agumon - Yuki no Kizuna
        { DMALL_AIRDRAMON_NAME, DMALL_AIRDRAMON_ID, ALT_DMALL_AIRDRAMON_FQID, ALT_DMALL_AIRDRAMON_FQNAME, DMALL_AIRDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Airdramon
        { DMALL_ALGOMON_ADULT_NAME, DMALL_ALGOMON_ADULT_ID, ALT_DMALL_ALGOMON_ADULT_FQID, ALT_DMALL_ALGOMON_ADULT_FQNAME, DMALL_ALGOMON_ADULT_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Algomon (Adult)
        { DMALL_ALGOMON_BABYII_NAME, DMALL_ALGOMON_BABYII_ID, ALT_DMALL_ALGOMON_BABYII_FQID, ALT_DMALL_ALGOMON_BABYII_FQNAME, DMALL_ALGOMON_BABYII_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Algomon (BabyII)
        { DMALL_ALGOMON_BABYI_NAME, DMALL_ALGOMON_BABYI_ID, ALT_DMALL_ALGOMON_BABYI_FQID, ALT_DMALL_ALGOMON_BABYI_FQNAME, DMALL_ALGOMON_BABYI_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Algomon (BabyI)
        { DMALL_ALGOMON_CHILD_NAME, DMALL_ALGOMON_CHILD_ID, ALT_DMALL_ALGOMON_CHILD_FQID, ALT_DMALL_ALGOMON_CHILD_FQNAME, DMALL_ALGOMON_CHILD_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Algomon (Child)
        { DMALL_ALGOMON_ULTIMATE_NAME, DMALL_ALGOMON_ULTIMATE_ID, ALT_DMALL_ALGOMON_ULTIMATE_FQID, ALT_DMALL_ALGOMON_ULTIMATE_FQNAME, DMALL_ALGOMON_ULTIMATE_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Algomon (Ultimate)
        { DMALL_ALLOMON_X_NAME, DMALL_ALLOMON_X_ID, ALT_DMALL_ALLOMON_X_FQID, ALT_DMALL_ALLOMON_X_FQNAME, DMALL_ALLOMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Allomon X
        { DMALL_ALPHAMON_OURYUKEN_NAME, DMALL_ALPHAMON_OURYUKEN_ID, ALT_DMALL_ALPHAMON_OURYUKEN_FQID, ALT_DMALL_ALPHAMON_OURYUKEN_FQNAME, DMALL_ALPHAMON_OURYUKEN_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Alphamon Ouryuken
        { DMALL_ALPHAMON_NAME, DMALL_ALPHAMON_ID, ALT_DMALL_ALPHAMON_FQID, ALT_DMALL_ALPHAMON_FQNAME, DMALL_ALPHAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Alphamon
        { DMALL_ALRAUMON_NAME, DMALL_ALRAUMON_ID, ALT_DMALL_ALRAUMON_FQID, ALT_DMALL_ALRAUMON_FQNAME, DMALL_ALRAUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Alraumon
        { DMALL_ANCIENT_BEATMON_NAME, DMALL_ANCIENT_BEATMON_ID, ALT_DMALL_ANCIENT_BEATMON_FQID, ALT_DMALL_ANCIENT_BEATMON_FQNAME, DMALL_ANCIENT_BEATMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Ancient Beatmon
        { DMALL_ANCIENT_MEGATHERIUMON_NAME, DMALL_ANCIENT_MEGATHERIUMON_ID, ALT_DMALL_ANCIENT_MEGATHERIUMON_FQID, ALT_DMALL_ANCIENT_MEGATHERIUMON_FQNAME, DMALL_ANCIENT_MEGATHERIUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Ancient Megatheriumon
        { DMALL_ANCIENT_MERMAIMON_NAME, DMALL_ANCIENT_MERMAIMON_ID, ALT_DMALL_ANCIENT_MERMAIMON_FQID, ALT_DMALL_ANCIENT_MERMAIMON_FQNAME, DMALL_ANCIENT_MERMAIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Ancient Mermaimon
        { DMALL_ANCIENT_SPHINXMON_NAME, DMALL_ANCIENT_SPHINXMON_ID, ALT_DMALL_ANCIENT_SPHINXMON_FQID, ALT_DMALL_ANCIENT_SPHINXMON_FQNAME, DMALL_ANCIENT_SPHINXMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Ancient Sphinxmon
        { DMALL_ANDIRAMON_DATA_NAME, DMALL_ANDIRAMON_DATA_ID, ALT_DMALL_ANDIRAMON_DATA_FQID, ALT_DMALL_ANDIRAMON_DATA_FQNAME, DMALL_ANDIRAMON_DATA_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Andiramon (Data)
        { DMALL_ANDIRAMON_VIRUS_NAME, DMALL_ANDIRAMON_VIRUS_ID, ALT_DMALL_ANDIRAMON_VIRUS_FQID, ALT_DMALL_ANDIRAMON_VIRUS_FQNAME, DMALL_ANDIRAMON_VIRUS_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Andiramon (Virus)
        { DMALL_ANDROMON_NAME, DMALL_ANDROMON_ID, ALT_DMALL_ANDROMON_FQID, ALT_DMALL_ANDROMON_FQNAME, DMALL_ANDROMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Andromon
        { DMALL_ANGEMON_NAME, DMALL_ANGEMON_ID, ALT_DMALL_ANGEMON_FQID, ALT_DMALL_ANGEMON_FQNAME, DMALL_ANGEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Angemon
        { DMALL_ANGEWOMON_NAME, DMALL_ANGEWOMON_ID, ALT_DMALL_ANGEWOMON_FQID, ALT_DMALL_ANGEWOMON_FQNAME, DMALL_ANGEWOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Angewomon
        { DMALL_ANGEWOMON_X_NAME, DMALL_ANGEWOMON_X_ID, ALT_DMALL_ANGEWOMON_X_FQID, ALT_DMALL_ANGEWOMON_X_FQNAME, DMALL_ANGEWOMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Angewomon X
        { DMALL_ANOMALOCARIMON_NAME, DMALL_ANOMALOCARIMON_ID, ALT_DMALL_ANOMALOCARIMON_FQID, ALT_DMALL_ANOMALOCARIMON_FQNAME, DMALL_ANOMALOCARIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Anomalocarimon
        { DMALL_ANOMALOCARIMON_X_NAME, DMALL_ANOMALOCARIMON_X_ID, ALT_DMALL_ANOMALOCARIMON_X_FQID, ALT_DMALL_ANOMALOCARIMON_X_FQNAME, DMALL_ANOMALOCARIMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Anomalocarimon X
        { DMALL_APOCALYMON_NAME, DMALL_APOCALYMON_ID, ALT_DMALL_APOCALYMON_FQID, ALT_DMALL_APOCALYMON_FQNAME, DMALL_APOCALYMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Apocalymon
        { DMALL_APOLLOMON_NAME, DMALL_APOLLOMON_ID, ALT_DMALL_APOLLOMON_FQID, ALT_DMALL_APOLLOMON_FQNAME, DMALL_APOLLOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Apollomon
        { DMALL_ARCHNEMON_NAME, DMALL_ARCHNEMON_ID, ALT_DMALL_ARCHNEMON_FQID, ALT_DMALL_ARCHNEMON_FQNAME, DMALL_ARCHNEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Archnemon
        { DMALL_ARKADIMON_BABY_NAME, DMALL_ARKADIMON_BABY_ID, ALT_DMALL_ARKADIMON_BABY_FQID, ALT_DMALL_ARKADIMON_BABY_FQNAME, DMALL_ARKADIMON_BABY_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Arkadimon (Baby)
        { DMALL_ARKADIMON_CHILD_NAME, DMALL_ARKADIMON_CHILD_ID, ALT_DMALL_ARKADIMON_CHILD_FQID, ALT_DMALL_ARKADIMON_CHILD_FQNAME, DMALL_ARKADIMON_CHILD_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Arkadimon (Child)
        { DMALL_ARMADIMON_NAME, DMALL_ARMADIMON_ID, ALT_DMALL_ARMADIMON_FQID, ALT_DMALL_ARMADIMON_FQNAME, DMALL_ARMADIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Armadimon
        { DMALL_ARMAGEMON_NAME, DMALL_ARMAGEMON_ID, ALT_DMALL_ARMAGEMON_FQID, ALT_DMALL_ARMAGEMON_FQNAME, DMALL_ARMAGEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Armagemon
        { DMALL_ASTAMON_NAME, DMALL_ASTAMON_ID, ALT_DMALL_ASTAMON_FQID, ALT_DMALL_ASTAMON_FQNAME, DMALL_ASTAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Astamon
        { DMALL_ASURAMON_NAME, DMALL_ASURAMON_ID, ALT_DMALL_ASURAMON_FQID, ALT_DMALL_ASURAMON_FQNAME, DMALL_ASURAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Asuramon
        { DMALL_ATLUR_KABUTERIMON_BLUE_NAME, DMALL_ATLUR_KABUTERIMON_BLUE_ID, ALT_DMALL_ATLUR_KABUTERIMON_BLUE_FQID, ALT_DMALL_ATLUR_KABUTERIMON_BLUE_FQNAME, DMALL_ATLUR_KABUTERIMON_BLUE_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Atlur Kabuterimon (Blue)
        { DMALL_ATLUR_KABUTERIMON_RED_NAME, DMALL_ATLUR_KABUTERIMON_RED_ID, ALT_DMALL_ATLUR_KABUTERIMON_RED_FQID, ALT_DMALL_ATLUR_KABUTERIMON_RED_FQNAME, DMALL_ATLUR_KABUTERIMON_RED_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Atlur Kabuterimon (Red)
        { DMALL_AXEKNIGHTMON_NAME, DMALL_AXEKNIGHTMON_ID, ALT_DMALL_AXEKNIGHTMON_FQID, ALT_DMALL_AXEKNIGHTMON_FQNAME, DMALL_AXEKNIGHTMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for AxeKnightmon
        { DMALL_BAALMON_NAME, DMALL_BAALMON_ID, ALT_DMALL_BAALMON_FQID, ALT_DMALL_BAALMON_FQNAME, DMALL_BAALMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Baalmon
        { DMALL_BABOONGAMON_NAME, DMALL_BABOONGAMON_ID, ALT_DMALL_BABOONGAMON_FQID, ALT_DMALL_BABOONGAMON_FQNAME, DMALL_BABOONGAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Baboongamon
        { DMALL_BABYDMON_NAME, DMALL_BABYDMON_ID, ALT_DMALL_BABYDMON_FQID, ALT_DMALL_BABYDMON_FQNAME, DMALL_BABYDMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Babydmon
        { DMALL_BAGRAMON_NAME, DMALL_BAGRAMON_ID, ALT_DMALL_BAGRAMON_FQID, ALT_DMALL_BAGRAMON_FQNAME, DMALL_BAGRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Bagramon
        { DMALL_BAKEMON_NAME, DMALL_BAKEMON_ID, ALT_DMALL_BAKEMON_FQID, ALT_DMALL_BAKEMON_FQNAME, DMALL_BAKEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Bakemon
        { DMALL_BAKUMON_NAME, DMALL_BAKUMON_ID, ALT_DMALL_BAKUMON_FQID, ALT_DMALL_BAKUMON_FQNAME, DMALL_BAKUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Bakumon
        { DMALL_BANCHO_LEOMON_NAME, DMALL_BANCHO_LEOMON_ID, ALT_DMALL_BANCHO_LEOMON_FQID, ALT_DMALL_BANCHO_LEOMON_FQNAME, DMALL_BANCHO_LEOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Bancho Leomon
        { DMALL_BANCHO_LILIMON_NAME, DMALL_BANCHO_LILIMON_ID, ALT_DMALL_BANCHO_LILIMON_FQID, ALT_DMALL_BANCHO_LILIMON_FQNAME, DMALL_BANCHO_LILIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Bancho Lilimon
        { DMALL_BANCHO_MAMEMON_NAME, DMALL_BANCHO_MAMEMON_ID, ALT_DMALL_BANCHO_MAMEMON_FQID, ALT_DMALL_BANCHO_MAMEMON_FQNAME, DMALL_BANCHO_MAMEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Bancho Mamemon
        { DMALL_BARBAMON_NAME, DMALL_BARBAMON_ID, ALT_DMALL_BARBAMON_FQID, ALT_DMALL_BARBAMON_FQNAME, DMALL_BARBAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Barbamon
        { DMALL_BARBAMON_X_NAME, DMALL_BARBAMON_X_ID, ALT_DMALL_BARBAMON_X_FQID, ALT_DMALL_BARBAMON_X_FQNAME, DMALL_BARBAMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Barbamon X
        { DMALL_BEARMON_NAME, DMALL_BEARMON_ID, ALT_DMALL_BEARMON_FQID, ALT_DMALL_BEARMON_FQNAME, DMALL_BEARMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Bearmon
        { DMALL_BEEL_STARMON_X_NAME, DMALL_BEEL_STARMON_X_ID, ALT_DMALL_BEEL_STARMON_X_FQID, ALT_DMALL_BEEL_STARMON_X_FQNAME, DMALL_BEEL_STARMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Beel Starmon X
        { DMALL_BEELZEBUMON_BLAST_MODE_NAME, DMALL_BEELZEBUMON_BLAST_MODE_ID, ALT_DMALL_BEELZEBUMON_BLAST_MODE_FQID, ALT_DMALL_BEELZEBUMON_BLAST_MODE_FQNAME, DMALL_BEELZEBUMON_BLAST_MODE_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Beelzebumon Blast Mode
        { DMALL_BEELZEBUMON_NAME, DMALL_BEELZEBUMON_ID, ALT_DMALL_BEELZEBUMON_FQID, ALT_DMALL_BEELZEBUMON_FQNAME, DMALL_BEELZEBUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Beelzebumon
        { DMALL_BEELZEBUMON_X_NAME, DMALL_BEELZEBUMON_X_ID, ALT_DMALL_BEELZEBUMON_X_FQID, ALT_DMALL_BEELZEBUMON_X_FQNAME, DMALL_BEELZEBUMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Beelzebumon X
        { DMALL_BELIAL_VAMDEMON_NAME, DMALL_BELIAL_VAMDEMON_ID, ALT_DMALL_BELIAL_VAMDEMON_FQID, ALT_DMALL_BELIAL_VAMDEMON_FQNAME, DMALL_BELIAL_VAMDEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Belial Vamdemon
        { DMALL_BELPHEMON_RAGE_MODE_NAME, DMALL_BELPHEMON_RAGE_MODE_ID, ALT_DMALL_BELPHEMON_RAGE_MODE_FQID, ALT_DMALL_BELPHEMON_RAGE_MODE_FQNAME, DMALL_BELPHEMON_RAGE_MODE_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Belphemon Rage Mode
        { DMALL_BELPHEMON_X_NAME, DMALL_BELPHEMON_X_ID, ALT_DMALL_BELPHEMON_X_FQID, ALT_DMALL_BELPHEMON_X_FQNAME, DMALL_BELPHEMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Belphemon X
        { DMALL_BEOWOLFMON_NAME, DMALL_BEOWOLFMON_ID, ALT_DMALL_BEOWOLFMON_FQID, ALT_DMALL_BEOWOLFMON_FQNAME, DMALL_BEOWOLFMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Beowolfmon
        { DMALL_BIBIMON_NAME, DMALL_BIBIMON_ID, ALT_DMALL_BIBIMON_FQID, ALT_DMALL_BIBIMON_FQNAME, DMALL_BIBIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Bibimon
        { DMALL_BIG_MAMEMON_NAME, DMALL_BIG_MAMEMON_ID, ALT_DMALL_BIG_MAMEMON_FQID, ALT_DMALL_BIG_MAMEMON_FQNAME, DMALL_BIG_MAMEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Big Mamemon
        { DMALL_BIRDRAMON_NAME, DMALL_BIRDRAMON_ID, ALT_DMALL_BIRDRAMON_FQID, ALT_DMALL_BIRDRAMON_FQNAME, DMALL_BIRDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Birdramon
        { DMALL_BITMON_NAME, DMALL_BITMON_ID, ALT_DMALL_BITMON_FQID, ALT_DMALL_BITMON_FQNAME, DMALL_BITMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Bitmon
        { DMALL_BLACK_GALGOMON_NAME, DMALL_BLACK_GALGOMON_ID, ALT_DMALL_BLACK_GALGOMON_FQID, ALT_DMALL_BLACK_GALGOMON_FQNAME, DMALL_BLACK_GALGOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Black Galgomon
        { DMALL_BLACK_GAOGAMON_NAME, DMALL_BLACK_GAOGAMON_ID, ALT_DMALL_BLACK_GAOGAMON_FQID, ALT_DMALL_BLACK_GAOGAMON_FQNAME, DMALL_BLACK_GAOGAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Black Gaogamon
        { DMALL_BLACK_GROWMON_NAME, DMALL_BLACK_GROWMON_ID, ALT_DMALL_BLACK_GROWMON_FQID, ALT_DMALL_BLACK_GROWMON_FQNAME, DMALL_BLACK_GROWMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Black Growmon
        { DMALL_BLACK_GUILMON_NAME, DMALL_BLACK_GUILMON_ID, ALT_DMALL_BLACK_GUILMON_FQID, ALT_DMALL_BLACK_GUILMON_FQNAME, DMALL_BLACK_GUILMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Black Guilmon
        { DMALL_BLACK_KING_NUMEMON_NAME, DMALL_BLACK_KING_NUMEMON_ID, ALT_DMALL_BLACK_KING_NUMEMON_FQID, ALT_DMALL_BLACK_KING_NUMEMON_FQNAME, DMALL_BLACK_KING_NUMEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Black King Numemon
        { DMALL_BLACK_MACH_GAOGAMON_NAME, DMALL_BLACK_MACH_GAOGAMON_ID, ALT_DMALL_BLACK_MACH_GAOGAMON_FQID, ALT_DMALL_BLACK_MACH_GAOGAMON_FQNAME, DMALL_BLACK_MACH_GAOGAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Black Mach Gaogamon
        { DMALL_BLACK_MEGALO_GROWMON_NAME, DMALL_BLACK_MEGALO_GROWMON_ID, ALT_DMALL_BLACK_MEGALO_GROWMON_FQID, ALT_DMALL_BLACK_MEGALO_GROWMON_FQNAME, DMALL_BLACK_MEGALO_GROWMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Black Megalo Growmon
        { DMALL_BLACK_RAPIDMON_NAME, DMALL_BLACK_RAPIDMON_ID, ALT_DMALL_BLACK_RAPIDMON_FQID, ALT_DMALL_BLACK_RAPIDMON_FQNAME, DMALL_BLACK_RAPIDMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Black Rapidmon
        { DMALL_BLACK_SAINT_GALGOMON_NAME, DMALL_BLACK_SAINT_GALGOMON_ID, ALT_DMALL_BLACK_SAINT_GALGOMON_FQID, ALT_DMALL_BLACK_SAINT_GALGOMON_FQNAME, DMALL_BLACK_SAINT_GALGOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Black Saint Galgomon
        { DMALL_BLACK_SERAPHIMON_NAME, DMALL_BLACK_SERAPHIMON_ID, ALT_DMALL_BLACK_SERAPHIMON_FQID, ALT_DMALL_BLACK_SERAPHIMON_FQNAME, DMALL_BLACK_SERAPHIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Black Seraphimon
        { DMALL_BLACK_TAILMON_NAME, DMALL_BLACK_TAILMON_ID, ALT_DMALL_BLACK_TAILMON_FQID, ALT_DMALL_BLACK_TAILMON_FQNAME, DMALL_BLACK_TAILMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Black Tailmon
        { DMALL_BLACK_WAR_GREYMON_NAME, DMALL_BLACK_WAR_GREYMON_ID, ALT_DMALL_BLACK_WAR_GREYMON_FQID, ALT_DMALL_BLACK_WAR_GREYMON_FQNAME, DMALL_BLACK_WAR_GREYMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Black War Greymon
        { DMALL_BLACK_WAR_GREYMON_X_NAME, DMALL_BLACK_WAR_GREYMON_X_ID, ALT_DMALL_BLACK_WAR_GREYMON_X_FQID, ALT_DMALL_BLACK_WAR_GREYMON_X_FQNAME, DMALL_BLACK_WAR_GREYMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Black War Greymon X
        { DMALL_BLITZ_GREYMON_NAME, DMALL_BLITZ_GREYMON_ID, ALT_DMALL_BLITZ_GREYMON_FQID, ALT_DMALL_BLITZ_GREYMON_FQNAME, DMALL_BLITZ_GREYMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Blitz Greymon
        { DMALL_BLOOM_LORDMON_NAME, DMALL_BLOOM_LORDMON_ID, ALT_DMALL_BLOOM_LORDMON_FQID, ALT_DMALL_BLOOM_LORDMON_FQNAME, DMALL_BLOOM_LORDMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Bloom Lordmon
        { DMALL_BLOSSOMON_NAME, DMALL_BLOSSOMON_ID, ALT_DMALL_BLOSSOMON_FQID, ALT_DMALL_BLOSSOMON_FQNAME, DMALL_BLOSSOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Blossomon
        { DMALL_BLUCOMON_NAME, DMALL_BLUCOMON_ID, ALT_DMALL_BLUCOMON_FQID, ALT_DMALL_BLUCOMON_FQNAME, DMALL_BLUCOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Blucomon
        { DMALL_BLUE_MERAMON_NAME, DMALL_BLUE_MERAMON_ID, ALT_DMALL_BLUE_MERAMON_FQID, ALT_DMALL_BLUE_MERAMON_FQNAME, DMALL_BLUE_MERAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Blue Meramon
        { DMALL_BOLTMON_NAME, DMALL_BOLTMON_ID, ALT_DMALL_BOLTMON_FQID, ALT_DMALL_BOLTMON_FQNAME, DMALL_BOLTMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Boltmon
        { DMALL_BOMBMON_NAME, DMALL_BOMBMON_ID, ALT_DMALL_BOMBMON_FQID, ALT_DMALL_BOMBMON_FQNAME, DMALL_BOMBMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Bombmon
        { DMALL_BOMMON_NAME, DMALL_BOMMON_ID, ALT_DMALL_BOMMON_FQID, ALT_DMALL_BOMMON_FQNAME, DMALL_BOMMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Bommon
        { DMALL_BOUTMON_NAME, DMALL_BOUTMON_ID, ALT_DMALL_BOUTMON_FQID, ALT_DMALL_BOUTMON_FQNAME, DMALL_BOUTMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Boutmon
        { DMALL_BRYWELUDRAMON_NAME, DMALL_BRYWELUDRAMON_ID, ALT_DMALL_BRYWELUDRAMON_FQID, ALT_DMALL_BRYWELUDRAMON_FQNAME, DMALL_BRYWELUDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Bryweludramon
        { DMALL_BUBBMON_NAME, DMALL_BUBBMON_ID, ALT_DMALL_BUBBMON_FQID, ALT_DMALL_BUBBMON_FQNAME, DMALL_BUBBMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Bubbmon
        { DMALL_BUDMON_NAME, DMALL_BUDMON_ID, ALT_DMALL_BUDMON_FQID, ALT_DMALL_BUDMON_FQNAME, DMALL_BUDMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Budmon
        { DMALL_BURGERMON_MAMA_NAME, DMALL_BURGERMON_MAMA_ID, ALT_DMALL_BURGERMON_MAMA_FQID, ALT_DMALL_BURGERMON_MAMA_FQNAME, DMALL_BURGERMON_MAMA_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Burgermon (Mama)
        { DMALL_BURGERMON_PAPA_NAME, DMALL_BURGERMON_PAPA_ID, ALT_DMALL_BURGERMON_PAPA_FQID, ALT_DMALL_BURGERMON_PAPA_FQNAME, DMALL_BURGERMON_PAPA_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Burgermon (Papa)
        { DMALL_CANDMON_NAME, DMALL_CANDMON_ID, ALT_DMALL_CANDMON_FQID, ALT_DMALL_CANDMON_FQNAME, DMALL_CANDMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Candmon
        { DMALL_CANNONBEEMON_NAME, DMALL_CANNONBEEMON_ID, ALT_DMALL_CANNONBEEMON_FQID, ALT_DMALL_CANNONBEEMON_FQNAME, DMALL_CANNONBEEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Cannonbeemon
        { DMALL_CAPRIMON_NAME, DMALL_CAPRIMON_ID, ALT_DMALL_CAPRIMON_FQID, ALT_DMALL_CAPRIMON_FQNAME, DMALL_CAPRIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Caprimon
        { DMALL_CATCHMAMEMON_NAME, DMALL_CATCHMAMEMON_ID, ALT_DMALL_CATCHMAMEMON_FQID, ALT_DMALL_CATCHMAMEMON_FQNAME, DMALL_CATCHMAMEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for CatchMamemon
        { DMALL_CATURAMON_NAME, DMALL_CATURAMON_ID, ALT_DMALL_CATURAMON_FQID, ALT_DMALL_CATURAMON_FQNAME, DMALL_CATURAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Caturamon
        { DMALL_CENTALMON_NAME, DMALL_CENTALMON_ID, ALT_DMALL_CENTALMON_FQID, ALT_DMALL_CENTALMON_FQNAME, DMALL_CENTALMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Centalmon
        { DMALL_CERBERUMON_X_NAME, DMALL_CERBERUMON_X_ID, ALT_DMALL_CERBERUMON_X_FQID, ALT_DMALL_CERBERUMON_X_FQNAME, DMALL_CERBERUMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Cerberumon X
        { DMALL_CHAMBLEMON_NAME, DMALL_CHAMBLEMON_ID, ALT_DMALL_CHAMBLEMON_FQID, ALT_DMALL_CHAMBLEMON_FQNAME, DMALL_CHAMBLEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Chamblemon
        { DMALL_CHAOSDRAMON_NAME, DMALL_CHAOSDRAMON_ID, ALT_DMALL_CHAOSDRAMON_FQID, ALT_DMALL_CHAOSDRAMON_FQNAME, DMALL_CHAOSDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Chaosdramon
        { DMALL_CHAOSDRAMON_X_NAME, DMALL_CHAOSDRAMON_X_ID, ALT_DMALL_CHAOSDRAMON_X_FQID, ALT_DMALL_CHAOSDRAMON_X_FQNAME, DMALL_CHAOSDRAMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Chaosdramon X
        { DMALL_CHAOS_DUKEMON_CORE_NAME, DMALL_CHAOS_DUKEMON_CORE_ID, ALT_DMALL_CHAOS_DUKEMON_CORE_FQID, ALT_DMALL_CHAOS_DUKEMON_CORE_FQNAME, DMALL_CHAOS_DUKEMON_CORE_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Chaos Dukemon Core
        { DMALL_CHAOS_DUKEMON_NAME, DMALL_CHAOS_DUKEMON_ID, ALT_DMALL_CHAOS_DUKEMON_FQID, ALT_DMALL_CHAOS_DUKEMON_FQNAME, DMALL_CHAOS_DUKEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Chaos Dukemon
        { DMALL_CHAOSMON_NAME, DMALL_CHAOSMON_ID, ALT_DMALL_CHAOSMON_FQID, ALT_DMALL_CHAOSMON_FQNAME, DMALL_CHAOSMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Chaosmon
        { DMALL_CHERUBIMON_VICE_NAME, DMALL_CHERUBIMON_VICE_ID, ALT_DMALL_CHERUBIMON_VICE_FQID, ALT_DMALL_CHERUBIMON_VICE_FQNAME, DMALL_CHERUBIMON_VICE_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Cherubimon (Vice)
        { DMALL_CHERUBIMON_VICE_X_NAME, DMALL_CHERUBIMON_VICE_X_ID, ALT_DMALL_CHERUBIMON_VICE_X_FQID, ALT_DMALL_CHERUBIMON_VICE_X_FQNAME, DMALL_CHERUBIMON_VICE_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Cherubimon (Vice) X
        { DMALL_CHERUBIMON_VIRTUE_NAME, DMALL_CHERUBIMON_VIRTUE_ID, ALT_DMALL_CHERUBIMON_VIRTUE_FQID, ALT_DMALL_CHERUBIMON_VIRTUE_FQNAME, DMALL_CHERUBIMON_VIRTUE_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Cherubimon (Virtue)
        { DMALL_CHERUBIMON_VIRTUE_X_NAME, DMALL_CHERUBIMON_VIRTUE_X_ID, ALT_DMALL_CHERUBIMON_VIRTUE_X_FQID, ALT_DMALL_CHERUBIMON_VIRTUE_X_FQNAME, DMALL_CHERUBIMON_VIRTUE_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Cherubimon (Virtue) X
        { DMALL_CHIBICKMON_NAME, DMALL_CHIBICKMON_ID, ALT_DMALL_CHIBICKMON_FQID, ALT_DMALL_CHIBICKMON_FQNAME, DMALL_CHIBICKMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Chibickmon
        { DMALL_CHIBIMON_NAME, DMALL_CHIBIMON_ID, ALT_DMALL_CHIBIMON_FQID, ALT_DMALL_CHIBIMON_FQNAME, DMALL_CHIBIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Chibimon
        { DMALL_CHICCHIMON_NAME, DMALL_CHICCHIMON_ID, ALT_DMALL_CHICCHIMON_FQID, ALT_DMALL_CHICCHIMON_FQNAME, DMALL_CHICCHIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Chicchimon
        { DMALL_CHICOMON_NAME, DMALL_CHICOMON_ID, ALT_DMALL_CHICOMON_FQID, ALT_DMALL_CHICOMON_FQNAME, DMALL_CHICOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Chicomon
        { DMALL_CHIMAIRAMON_NAME, DMALL_CHIMAIRAMON_ID, ALT_DMALL_CHIMAIRAMON_FQID, ALT_DMALL_CHIMAIRAMON_FQNAME, DMALL_CHIMAIRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Chimairamon
        { DMALL_CHOCOMON_NAME, DMALL_CHOCOMON_ID, ALT_DMALL_CHOCOMON_FQID, ALT_DMALL_CHOCOMON_FQNAME, DMALL_CHOCOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Chocomon
        { DMALL_CHO_HAKKAIMON_NAME, DMALL_CHO_HAKKAIMON_ID, ALT_DMALL_CHO_HAKKAIMON_FQID, ALT_DMALL_CHO_HAKKAIMON_FQNAME, DMALL_CHO_HAKKAIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Cho Hakkaimon
        { DMALL_CHOROMON_NAME, DMALL_CHOROMON_ID, ALT_DMALL_CHOROMON_FQID, ALT_DMALL_CHOROMON_FQNAME, DMALL_CHOROMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Choromon
        { DMALL_CLEAR_AGUMON_NAME, DMALL_CLEAR_AGUMON_ID, ALT_DMALL_CLEAR_AGUMON_FQID, ALT_DMALL_CLEAR_AGUMON_FQNAME, DMALL_CLEAR_AGUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Clear Agumon
        { DMALL_CLOCKMON_NAME, DMALL_CLOCKMON_ID, ALT_DMALL_CLOCKMON_FQID, ALT_DMALL_CLOCKMON_FQNAME, DMALL_CLOCKMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Clockmon
        { DMALL_COCOMON_NAME, DMALL_COCOMON_ID, ALT_DMALL_COCOMON_FQID, ALT_DMALL_COCOMON_FQNAME, DMALL_COCOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Cocomon
        { DMALL_COELAMON_NAME, DMALL_COELAMON_ID, ALT_DMALL_COELAMON_FQID, ALT_DMALL_COELAMON_FQNAME, DMALL_COELAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Coelamon
        { DMALL_COMMANDRAMON_NAME, DMALL_COMMANDRAMON_ID, ALT_DMALL_COMMANDRAMON_FQID, ALT_DMALL_COMMANDRAMON_FQNAME, DMALL_COMMANDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Commandramon
        { DMALL_CORONAMON_NAME, DMALL_CORONAMON_ID, ALT_DMALL_CORONAMON_FQID, ALT_DMALL_CORONAMON_FQNAME, DMALL_CORONAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Coronamon
        { DMALL_COTSUCOMON_NAME, DMALL_COTSUCOMON_ID, ALT_DMALL_COTSUCOMON_FQID, ALT_DMALL_COTSUCOMON_FQNAME, DMALL_COTSUCOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Cotsucomon
        { DMALL_CRANIUMMON_NAME, DMALL_CRANIUMMON_ID, ALT_DMALL_CRANIUMMON_FQID, ALT_DMALL_CRANIUMMON_FQNAME, DMALL_CRANIUMMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Craniummon
        { DMALL_CRANIUMMON_X_NAME, DMALL_CRANIUMMON_X_ID, ALT_DMALL_CRANIUMMON_X_FQID, ALT_DMALL_CRANIUMMON_X_FQNAME, DMALL_CRANIUMMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Craniummon X
        { DMALL_CRESCEMON_NAME, DMALL_CRESCEMON_ID, ALT_DMALL_CRESCEMON_FQID, ALT_DMALL_CRESCEMON_FQNAME, DMALL_CRESCEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Crescemon
        { DMALL_CRES_GARURUMON_NAME, DMALL_CRES_GARURUMON_ID, ALT_DMALL_CRES_GARURUMON_FQID, ALT_DMALL_CRES_GARURUMON_FQNAME, DMALL_CRES_GARURUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Cres Garurumon
        { DMALL_CRYS_PALEDRAMON_NAME, DMALL_CRYS_PALEDRAMON_ID, ALT_DMALL_CRYS_PALEDRAMON_FQID, ALT_DMALL_CRYS_PALEDRAMON_FQNAME, DMALL_CRYS_PALEDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Crys Paledramon
        { DMALL_CTHYLLAMON_NAME, DMALL_CTHYLLAMON_ID, ALT_DMALL_CTHYLLAMON_FQID, ALT_DMALL_CTHYLLAMON_FQNAME, DMALL_CTHYLLAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Cthyllamon
        { DMALL_CUPIMON_NAME, DMALL_CUPIMON_ID, ALT_DMALL_CUPIMON_FQID, ALT_DMALL_CUPIMON_FQNAME, DMALL_CUPIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Cupimon
        { DMALL_CURIMON_NAME, DMALL_CURIMON_ID, ALT_DMALL_CURIMON_FQID, ALT_DMALL_CURIMON_FQNAME, DMALL_CURIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Curimon
        { DMALL_CYBERDRAMON_NAME, DMALL_CYBERDRAMON_ID, ALT_DMALL_CYBERDRAMON_FQID, ALT_DMALL_CYBERDRAMON_FQNAME, DMALL_CYBERDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Cyberdramon
        { DMALL_CYBERDRAMON_X_NAME, DMALL_CYBERDRAMON_X_ID, ALT_DMALL_CYBERDRAMON_X_FQID, ALT_DMALL_CYBERDRAMON_X_FQNAME, DMALL_CYBERDRAMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Cyberdramon X
        { DMALL_CYCLOMON_NAME, DMALL_CYCLOMON_ID, ALT_DMALL_CYCLOMON_FQID, ALT_DMALL_CYCLOMON_FQNAME, DMALL_CYCLOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Cyclomon
        { DMALL_DAGOMON_NAME, DMALL_DAGOMON_ID, ALT_DMALL_DAGOMON_FQID, ALT_DMALL_DAGOMON_FQNAME, DMALL_DAGOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Dagomon
        { DMALL_DAMEMON_NAME, DMALL_DAMEMON_ID, ALT_DMALL_DAMEMON_FQID, ALT_DMALL_DAMEMON_FQNAME, DMALL_DAMEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Damemon
        { DMALL_DARKDRAMON_NAME, DMALL_DARKDRAMON_ID, ALT_DMALL_DARKDRAMON_FQID, ALT_DMALL_DARKDRAMON_FQNAME, DMALL_DARKDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Darkdramon
        { DMALL_DARK_KNIGHTMON_NAME, DMALL_DARK_KNIGHTMON_ID, ALT_DMALL_DARK_KNIGHTMON_FQID, ALT_DMALL_DARK_KNIGHTMON_FQNAME, DMALL_DARK_KNIGHTMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Dark Knightmon
        { DMALL_DARKNESS_BAGRAMON_NAME, DMALL_DARKNESS_BAGRAMON_ID, ALT_DMALL_DARKNESS_BAGRAMON_FQID, ALT_DMALL_DARKNESS_BAGRAMON_FQNAME, DMALL_DARKNESS_BAGRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Darkness Bagramon
        { DMALL_DARK_SUPERSTARMON_NAME, DMALL_DARK_SUPERSTARMON_ID, ALT_DMALL_DARK_SUPERSTARMON_FQID, ALT_DMALL_DARK_SUPERSTARMON_FQNAME, DMALL_DARK_SUPERSTARMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Dark Superstarmon
        { DMALL_DARK_TYRANOMON_X_NAME, DMALL_DARK_TYRANOMON_X_ID, ALT_DMALL_DARK_TYRANOMON_X_FQID, ALT_DMALL_DARK_TYRANOMON_X_FQNAME, DMALL_DARK_TYRANOMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Dark Tyranomon X
        { DMALL_DEATH_MERAMON_NAME, DMALL_DEATH_MERAMON_ID, ALT_DMALL_DEATH_MERAMON_FQID, ALT_DMALL_DEATH_MERAMON_FQNAME, DMALL_DEATH_MERAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Death Meramon
        { DMALL_DEATHMON_BLACK_NAME, DMALL_DEATHMON_BLACK_ID, ALT_DMALL_DEATHMON_BLACK_FQID, ALT_DMALL_DEATHMON_BLACK_FQNAME, DMALL_DEATHMON_BLACK_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Deathmon (Black)
        { DMALL_DEATHMON_NAME, DMALL_DEATHMON_ID, ALT_DMALL_DEATHMON_FQID, ALT_DMALL_DEATHMON_FQNAME, DMALL_DEATHMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Deathmon
        { DMALL_DEATH_X_DORUGAMON_NAME, DMALL_DEATH_X_DORUGAMON_ID, ALT_DMALL_DEATH_X_DORUGAMON_FQID, ALT_DMALL_DEATH_X_DORUGAMON_FQNAME, DMALL_DEATH_X_DORUGAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Death-X-DORUgamon
        { DMALL_DELUMON_NAME, DMALL_DELUMON_ID, ALT_DMALL_DELUMON_FQID, ALT_DMALL_DELUMON_FQNAME, DMALL_DELUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Delumon
        { DMALL_DEMON_NAME, DMALL_DEMON_ID, ALT_DMALL_DEMON_FQID, ALT_DMALL_DEMON_FQNAME, DMALL_DEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Demon
        { DMALL_DEMON_X_NAME, DMALL_DEMON_X_ID, ALT_DMALL_DEMON_X_FQID, ALT_DMALL_DEMON_X_FQNAME, DMALL_DEMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Demon X
        { DMALL_DEVIMON_NAME, DMALL_DEVIMON_ID, ALT_DMALL_DEVIMON_FQID, ALT_DMALL_DEVIMON_FQNAME, DMALL_DEVIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Devimon
        { DMALL_DIABLOMON_NAME, DMALL_DIABLOMON_ID, ALT_DMALL_DIABLOMON_FQID, ALT_DMALL_DIABLOMON_FQNAME, DMALL_DIABLOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Diablomon
        { DMALL_DIABLOMON_X_NAME, DMALL_DIABLOMON_X_ID, ALT_DMALL_DIABLOMON_X_FQID, ALT_DMALL_DIABLOMON_X_FQNAME, DMALL_DIABLOMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Diablomon X
        { DMALL_DIANAMON_NAME, DMALL_DIANAMON_ID, ALT_DMALL_DIANAMON_FQID, ALT_DMALL_DIANAMON_FQNAME, DMALL_DIANAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Dianamon
        { DMALL_DIGINORIMON_NAME, DMALL_DIGINORIMON_ID, ALT_DMALL_DIGINORIMON_FQID, ALT_DMALL_DIGINORIMON_FQNAME, DMALL_DIGINORIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Diginorimon
        { DMALL_DIGITAMAMON_NAME, DMALL_DIGITAMAMON_ID, ALT_DMALL_DIGITAMAMON_FQID, ALT_DMALL_DIGITAMAMON_FQNAME, DMALL_DIGITAMAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Digitamamon
        { DMALL_DINOHUMON_NAME, DMALL_DINOHUMON_ID, ALT_DMALL_DINOHUMON_FQID, ALT_DMALL_DINOHUMON_FQNAME, DMALL_DINOHUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Dinohumon
        { DMALL_DINOREXMON_NAME, DMALL_DINOREXMON_ID, ALT_DMALL_DINOREXMON_FQID, ALT_DMALL_DINOREXMON_FQNAME, DMALL_DINOREXMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Dinorexmon
        { DMALL_DINOTIGERMON_NAME, DMALL_DINOTIGERMON_ID, ALT_DMALL_DINOTIGERMON_FQID, ALT_DMALL_DINOTIGERMON_FQNAME, DMALL_DINOTIGERMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Dinotigermon
        { DMALL_DOBERMON_NAME, DMALL_DOBERMON_ID, ALT_DMALL_DOBERMON_FQID, ALT_DMALL_DOBERMON_FQNAME, DMALL_DOBERMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Dobermon
        { DMALL_DODOMON_NAME, DMALL_DODOMON_ID, ALT_DMALL_DODOMON_FQID, ALT_DMALL_DODOMON_FQNAME, DMALL_DODOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Dodomon
        { DMALL_DOGMON_NAME, DMALL_DOGMON_ID, ALT_DMALL_DOGMON_FQID, ALT_DMALL_DOGMON_FQNAME, DMALL_DOGMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Dogmon
        { DMALL_DOKIMON_NAME, DMALL_DOKIMON_ID, ALT_DMALL_DOKIMON_FQID, ALT_DMALL_DOKIMON_FQNAME, DMALL_DOKIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Dokimon
        { DMALL_DOKUGUMON_NAME, DMALL_DOKUGUMON_ID, ALT_DMALL_DOKUGUMON_FQID, ALT_DMALL_DOKUGUMON_FQNAME, DMALL_DOKUGUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Dokugumon
        { DMALL_DOKUNEMON_NAME, DMALL_DOKUNEMON_ID, ALT_DMALL_DOKUNEMON_FQID, ALT_DMALL_DOKUNEMON_FQNAME, DMALL_DOKUNEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Dokunemon
        { DMALL_DORIMON_NAME, DMALL_DORIMON_ID, ALT_DMALL_DORIMON_FQID, ALT_DMALL_DORIMON_FQNAME, DMALL_DORIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Dorimon
        { DMALL_DORUGAMON_NAME, DMALL_DORUGAMON_ID, ALT_DMALL_DORUGAMON_FQID, ALT_DMALL_DORUGAMON_FQNAME, DMALL_DORUGAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for DORUgamon
        { DMALL_DORUGORAMON_NAME, DMALL_DORUGORAMON_ID, ALT_DMALL_DORUGORAMON_FQID, ALT_DMALL_DORUGORAMON_FQNAME, DMALL_DORUGORAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for DORUgoramon
        { DMALL_DORUGUREMON_NAME, DMALL_DORUGUREMON_ID, ALT_DMALL_DORUGUREMON_FQID, ALT_DMALL_DORUGUREMON_FQNAME, DMALL_DORUGUREMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for DORUguremon
        { DMALL_DORUMON_NAME, DMALL_DORUMON_ID, ALT_DMALL_DORUMON_FQID, ALT_DMALL_DORUMON_FQNAME, DMALL_DORUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for DORUmon
        { DMALL_DRACOMON_X_NAME, DMALL_DRACOMON_X_ID, ALT_DMALL_DRACOMON_X_FQID, ALT_DMALL_DRACOMON_X_FQNAME, DMALL_DRACOMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Dracomon X
        { DMALL_DRACUMON_NAME, DMALL_DRACUMON_ID, ALT_DMALL_DRACUMON_FQID, ALT_DMALL_DRACUMON_FQNAME, DMALL_DRACUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Dracumon
        { DMALL_DRIMOGEMON_NAME, DMALL_DRIMOGEMON_ID, ALT_DMALL_DRIMOGEMON_FQID, ALT_DMALL_DRIMOGEMON_FQNAME, DMALL_DRIMOGEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Drimogemon
        { DMALL_DUFTMON_NAME, DMALL_DUFTMON_ID, ALT_DMALL_DUFTMON_FQID, ALT_DMALL_DUFTMON_FQNAME, DMALL_DUFTMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Duftmon
        { DMALL_DUFTMON_X_NAME, DMALL_DUFTMON_X_ID, ALT_DMALL_DUFTMON_X_FQID, ALT_DMALL_DUFTMON_X_FQNAME, DMALL_DUFTMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Duftmon X
        { DMALL_DUKEMON_NAME, DMALL_DUKEMON_ID, ALT_DMALL_DUKEMON_FQID, ALT_DMALL_DUKEMON_FQNAME, DMALL_DUKEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Dukemon
        { DMALL_DUKEMON_X_NAME, DMALL_DUKEMON_X_ID, ALT_DMALL_DUKEMON_X_FQID, ALT_DMALL_DUKEMON_X_FQNAME, DMALL_DUKEMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Dukemon X
        { DMALL_DURAMON_NAME, DMALL_DURAMON_ID, ALT_DMALL_DURAMON_FQID, ALT_DMALL_DURAMON_FQNAME, DMALL_DURAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Duramon
        { DMALL_DUSKMON_NAME, DMALL_DUSKMON_ID, ALT_DMALL_DUSKMON_FQID, ALT_DMALL_DUSKMON_FQNAME, DMALL_DUSKMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Duskmon
        { DMALL_DYNASMON_X_NAME, DMALL_DYNASMON_X_ID, ALT_DMALL_DYNASMON_X_FQID, ALT_DMALL_DYNASMON_X_FQNAME, DMALL_DYNASMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Dynasmon X
        { DMALL_EBEMON_NAME, DMALL_EBEMON_ID, ALT_DMALL_EBEMON_FQID, ALT_DMALL_EBEMON_FQNAME, DMALL_EBEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Ebemon
        { DMALL_EBEMON_X_NAME, DMALL_EBEMON_X_ID, ALT_DMALL_EBEMON_X_FQID, ALT_DMALL_EBEMON_X_FQNAME, DMALL_EBEMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Ebemon X
        { DMALL_EBIDRAMON_NAME, DMALL_EBIDRAMON_ID, ALT_DMALL_EBIDRAMON_FQID, ALT_DMALL_EBIDRAMON_FQNAME, DMALL_EBIDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Ebidramon
        { DMALL_EKAKIMON_NAME, DMALL_EKAKIMON_ID, ALT_DMALL_EKAKIMON_FQID, ALT_DMALL_EKAKIMON_FQNAME, DMALL_EKAKIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Ekakimon
        { DMALL_ELECMON_NAME, DMALL_ELECMON_ID, ALT_DMALL_ELECMON_FQID, ALT_DMALL_ELECMON_FQNAME, DMALL_ELECMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Elecmon
        { DMALL_ELECMON_VIOLET_NAME, DMALL_ELECMON_VIOLET_ID, ALT_DMALL_ELECMON_VIOLET_FQID, ALT_DMALL_ELECMON_VIOLET_FQNAME, DMALL_ELECMON_VIOLET_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Elecmon (Violet)
        { DMALL_ENTMON_NAME, DMALL_ENTMON_ID, ALT_DMALL_ENTMON_FQID, ALT_DMALL_ENTMON_FQNAME, DMALL_ENTMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Entmon
        { DMALL_ETEMON_NAME, DMALL_ETEMON_ID, ALT_DMALL_ETEMON_FQID, ALT_DMALL_ETEMON_FQNAME, DMALL_ETEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Etemon
        { DMALL_EXAMON_X_NAME, DMALL_EXAMON_X_ID, ALT_DMALL_EXAMON_X_FQID, ALT_DMALL_EXAMON_X_FQNAME, DMALL_EXAMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Examon X
        { DMALL_FILMON_NAME, DMALL_FILMON_ID, ALT_DMALL_FILMON_FQID, ALT_DMALL_FILMON_FQNAME, DMALL_FILMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Filmon
        { DMALL_FIRAMON_NAME, DMALL_FIRAMON_ID, ALT_DMALL_FIRAMON_FQID, ALT_DMALL_FIRAMON_FQNAME, DMALL_FIRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Firamon
        { DMALL_FLAREMON_NAME, DMALL_FLAREMON_ID, ALT_DMALL_FLAREMON_FQID, ALT_DMALL_FLAREMON_FQNAME, DMALL_FLAREMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Flaremon
        { DMALL_FLORAMON_NAME, DMALL_FLORAMON_ID, ALT_DMALL_FLORAMON_FQID, ALT_DMALL_FLORAMON_FQNAME, DMALL_FLORAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Floramon
        { DMALL_FUFUMON_NAME, DMALL_FUFUMON_ID, ALT_DMALL_FUFUMON_FQID, ALT_DMALL_FUFUMON_FQNAME, DMALL_FUFUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Fufumon
        { DMALL_FUGAMON_NAME, DMALL_FUGAMON_ID, ALT_DMALL_FUGAMON_FQID, ALT_DMALL_FUGAMON_FQNAME, DMALL_FUGAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Fugamon
        { DMALL_FUNBEEMON_NAME, DMALL_FUNBEEMON_ID, ALT_DMALL_FUNBEEMON_FQID, ALT_DMALL_FUNBEEMON_FQNAME, DMALL_FUNBEEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Funbeemon
        { DMALL_GABUMON_X_NAME, DMALL_GABUMON_X_ID, ALT_DMALL_GABUMON_X_FQID, ALT_DMALL_GABUMON_X_FQNAME, DMALL_GABUMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Gabumon X
        { DMALL_GAIOUMON_NAME, DMALL_GAIOUMON_ID, ALT_DMALL_GAIOUMON_FQID, ALT_DMALL_GAIOUMON_FQNAME, DMALL_GAIOUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Gaioumon
        { DMALL_GALGOMON_NAME, DMALL_GALGOMON_ID, ALT_DMALL_GALGOMON_FQID, ALT_DMALL_GALGOMON_FQNAME, DMALL_GALGOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Galgomon
        { DMALL_GAMMAMON_NAME, DMALL_GAMMAMON_ID, ALT_DMALL_GAMMAMON_FQID, ALT_DMALL_GAMMAMON_FQNAME, DMALL_GAMMAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Gammamon
        { DMALL_GANIMON_NAME, DMALL_GANIMON_ID, ALT_DMALL_GANIMON_FQID, ALT_DMALL_GANIMON_FQNAME, DMALL_GANIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Ganimon
        { DMALL_GANKOOMON_NAME, DMALL_GANKOOMON_ID, ALT_DMALL_GANKOOMON_FQID, ALT_DMALL_GANKOOMON_FQNAME, DMALL_GANKOOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Gankoomon
        { DMALL_GANKOOMON_X_NAME, DMALL_GANKOOMON_X_ID, ALT_DMALL_GANKOOMON_X_FQID, ALT_DMALL_GANKOOMON_X_FQNAME, DMALL_GANKOOMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Gankoomon X
        { DMALL_GAOGAMON_NAME, DMALL_GAOGAMON_ID, ALT_DMALL_GAOGAMON_FQID, ALT_DMALL_GAOGAMON_FQNAME, DMALL_GAOGAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Gaogamon
        { DMALL_GAOMON_NAME, DMALL_GAOMON_ID, ALT_DMALL_GAOMON_FQID, ALT_DMALL_GAOMON_FQNAME, DMALL_GAOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Gaomon
        { DMALL_GARUDAMON_NAME, DMALL_GARUDAMON_ID, ALT_DMALL_GARUDAMON_FQID, ALT_DMALL_GARUDAMON_FQNAME, DMALL_GARUDAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Garudamon
        { DMALL_GARUDAMON_X_NAME, DMALL_GARUDAMON_X_ID, ALT_DMALL_GARUDAMON_X_FQID, ALT_DMALL_GARUDAMON_X_FQNAME, DMALL_GARUDAMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Garudamon X
        { DMALL_GARURUMON_BLACK_NAME, DMALL_GARURUMON_BLACK_ID, ALT_DMALL_GARURUMON_BLACK_FQID, ALT_DMALL_GARURUMON_BLACK_FQNAME, DMALL_GARURUMON_BLACK_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Garurumon (Black)
        { DMALL_GARURUMON_NAME, DMALL_GARURUMON_ID, ALT_DMALL_GARURUMON_FQID, ALT_DMALL_GARURUMON_FQNAME, DMALL_GARURUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Garurumon
        { DMALL_GAWAPPAMON_NAME, DMALL_GAWAPPAMON_ID, ALT_DMALL_GAWAPPAMON_FQID, ALT_DMALL_GAWAPPAMON_FQNAME, DMALL_GAWAPPAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Gawappamon
        { DMALL_GAZIMON_NAME, DMALL_GAZIMON_ID, ALT_DMALL_GAZIMON_FQID, ALT_DMALL_GAZIMON_FQNAME, DMALL_GAZIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Gazimon
        { DMALL_GAZIMON_X_NAME, DMALL_GAZIMON_X_ID, ALT_DMALL_GAZIMON_X_FQID, ALT_DMALL_GAZIMON_X_FQNAME, DMALL_GAZIMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Gazimon X
        { DMALL_GEKOMON_NAME, DMALL_GEKOMON_ID, ALT_DMALL_GEKOMON_FQID, ALT_DMALL_GEKOMON_FQNAME, DMALL_GEKOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Gekomon
        { DMALL_GEO_GREYMON_NAME, DMALL_GEO_GREYMON_ID, ALT_DMALL_GEO_GREYMON_FQID, ALT_DMALL_GEO_GREYMON_FQNAME, DMALL_GEO_GREYMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Geo Greymon
        { DMALL_GERBEMON_NAME, DMALL_GERBEMON_ID, ALT_DMALL_GERBEMON_FQID, ALT_DMALL_GERBEMON_FQNAME, DMALL_GERBEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Gerbemon
        { DMALL_GEREMON_NAME, DMALL_GEREMON_ID, ALT_DMALL_GEREMON_FQID, ALT_DMALL_GEREMON_FQNAME, DMALL_GEREMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Geremon
        { DMALL_GESOMON_NAME, DMALL_GESOMON_ID, ALT_DMALL_GESOMON_FQID, ALT_DMALL_GESOMON_FQNAME, DMALL_GESOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Gesomon
        { DMALL_GHOSTMON_NAME, DMALL_GHOSTMON_ID, ALT_DMALL_GHOSTMON_FQID, ALT_DMALL_GHOSTMON_FQNAME, DMALL_GHOSTMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Ghostmon
        { DMALL_GIGADRAMON_NAME, DMALL_GIGADRAMON_ID, ALT_DMALL_GIGADRAMON_FQID, ALT_DMALL_GIGADRAMON_FQNAME, DMALL_GIGADRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Gigadramon
        { DMALL_GIGA_SEADRAMON_NAME, DMALL_GIGA_SEADRAMON_ID, ALT_DMALL_GIGA_SEADRAMON_FQID, ALT_DMALL_GIGA_SEADRAMON_FQNAME, DMALL_GIGA_SEADRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Giga Seadramon
        { DMALL_GIGIMON_NAME, DMALL_GIGIMON_ID, ALT_DMALL_GIGIMON_FQID, ALT_DMALL_GIGIMON_FQNAME, DMALL_GIGIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Gigimon
        { DMALL_GINRYUMON_NAME, DMALL_GINRYUMON_ID, ALT_DMALL_GINRYUMON_FQID, ALT_DMALL_GINRYUMON_FQNAME, DMALL_GINRYUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Ginryumon
        { DMALL_GIROMON_NAME, DMALL_GIROMON_ID, ALT_DMALL_GIROMON_FQID, ALT_DMALL_GIROMON_FQNAME, DMALL_GIROMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Giromon
        { DMALL_GIZAMON_NAME, DMALL_GIZAMON_ID, ALT_DMALL_GIZAMON_FQID, ALT_DMALL_GIZAMON_FQNAME, DMALL_GIZAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Gizamon
        { DMALL_GODDRAMON_X_NAME, DMALL_GODDRAMON_X_ID, ALT_DMALL_GODDRAMON_X_FQID, ALT_DMALL_GODDRAMON_X_FQNAME, DMALL_GODDRAMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Goddramon X
        { DMALL_GOGMAMON_NAME, DMALL_GOGMAMON_ID, ALT_DMALL_GOGMAMON_FQID, ALT_DMALL_GOGMAMON_FQNAME, DMALL_GOGMAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Gogmamon
        { DMALL_GOKIMON_NAME, DMALL_GOKIMON_ID, ALT_DMALL_GOKIMON_FQID, ALT_DMALL_GOKIMON_FQNAME, DMALL_GOKIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Gokimon
        { DMALL_GOKUMON_NAME, DMALL_GOKUMON_ID, ALT_DMALL_GOKUMON_FQID, ALT_DMALL_GOKUMON_FQNAME, DMALL_GOKUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Gokumon
        { DMALL_GOLD_NUMEMON_NAME, DMALL_GOLD_NUMEMON_ID, ALT_DMALL_GOLD_NUMEMON_FQID, ALT_DMALL_GOLD_NUMEMON_FQNAME, DMALL_GOLD_NUMEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Gold Numemon
        { DMALL_GOLD_V_DRAMON_NAME, DMALL_GOLD_V_DRAMON_ID, ALT_DMALL_GOLD_V_DRAMON_FQID, ALT_DMALL_GOLD_V_DRAMON_FQNAME, DMALL_GOLD_V_DRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Gold V-dramon
        { DMALL_GOMAMON_NAME, DMALL_GOMAMON_ID, ALT_DMALL_GOMAMON_FQID, ALT_DMALL_GOMAMON_FQNAME, DMALL_GOMAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Gomamon
        { DMALL_GOMAMON_X_NAME, DMALL_GOMAMON_X_ID, ALT_DMALL_GOMAMON_X_FQID, ALT_DMALL_GOMAMON_X_FQNAME, DMALL_GOMAMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Gomamon X
        { DMALL_GOROMON_NAME, DMALL_GOROMON_ID, ALT_DMALL_GOROMON_FQID, ALT_DMALL_GOROMON_FQNAME, DMALL_GOROMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Goromon
        { DMALL_GOTSUMON_NAME, DMALL_GOTSUMON_ID, ALT_DMALL_GOTSUMON_FQID, ALT_DMALL_GOTSUMON_FQNAME, DMALL_GOTSUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Gotsumon
        { DMALL_GRACE_NOVAMON_NAME, DMALL_GRACE_NOVAMON_ID, ALT_DMALL_GRACE_NOVAMON_FQID, ALT_DMALL_GRACE_NOVAMON_FQNAME, DMALL_GRACE_NOVAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Grace Novamon
        { DMALL_GRADEMON_NAME, DMALL_GRADEMON_ID, ALT_DMALL_GRADEMON_FQID, ALT_DMALL_GRADEMON_FQNAME, DMALL_GRADEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Grademon
        { DMALL_GRAND_DRACUMON_NAME, DMALL_GRAND_DRACUMON_ID, ALT_DMALL_GRAND_DRACUMON_FQID, ALT_DMALL_GRAND_DRACUMON_FQNAME, DMALL_GRAND_DRACUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Grand Dracumon
        { DMALL_GRANDIS_KUWAGAMON_NAME, DMALL_GRANDIS_KUWAGAMON_ID, ALT_DMALL_GRANDIS_KUWAGAMON_FQID, ALT_DMALL_GRANDIS_KUWAGAMON_FQNAME, DMALL_GRANDIS_KUWAGAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Grandis Kuwagamon
        { DMALL_GRAND_LOCOMON_NAME, DMALL_GRAND_LOCOMON_ID, ALT_DMALL_GRAND_LOCOMON_FQID, ALT_DMALL_GRAND_LOCOMON_FQNAME, DMALL_GRAND_LOCOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Grand Locomon
        { DMALL_GRAPPLEOMON_NAME, DMALL_GRAPPLEOMON_ID, ALT_DMALL_GRAPPLEOMON_FQID, ALT_DMALL_GRAPPLEOMON_FQNAME, DMALL_GRAPPLEOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Grappleomon
        { DMALL_GREAT_KING_SCUMON_NAME, DMALL_GREAT_KING_SCUMON_ID, ALT_DMALL_GREAT_KING_SCUMON_FQID, ALT_DMALL_GREAT_KING_SCUMON_FQNAME, DMALL_GREAT_KING_SCUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Great King Scumon
        { DMALL_GREYMON_2010_NAME, DMALL_GREYMON_2010_ID, ALT_DMALL_GREYMON_2010_FQID, ALT_DMALL_GREYMON_2010_FQNAME, DMALL_GREYMON_2010_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Greymon (2010)
        { DMALL_GREYMON_BLUE_NAME, DMALL_GREYMON_BLUE_ID, ALT_DMALL_GREYMON_BLUE_FQID, ALT_DMALL_GREYMON_BLUE_FQNAME, DMALL_GREYMON_BLUE_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Greymon (Blue)
        { DMALL_GREYMON_NAME, DMALL_GREYMON_ID, ALT_DMALL_GREYMON_FQID, ALT_DMALL_GREYMON_FQNAME, DMALL_GREYMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Greymon
        { DMALL_GREYMON_X_NAME, DMALL_GREYMON_X_ID, ALT_DMALL_GREYMON_X_FQID, ALT_DMALL_GREYMON_X_FQNAME, DMALL_GREYMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Greymon X
        { DMALL_GRIFFOMON_NAME, DMALL_GRIFFOMON_ID, ALT_DMALL_GRIFFOMON_FQID, ALT_DMALL_GRIFFOMON_FQNAME, DMALL_GRIFFOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Griffomon
        { DMALL_GROWMON_ORANGE_NAME, DMALL_GROWMON_ORANGE_ID, ALT_DMALL_GROWMON_ORANGE_FQID, ALT_DMALL_GROWMON_ORANGE_FQNAME, DMALL_GROWMON_ORANGE_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Growmon (Orange)
        { DMALL_GROWMON_NAME, DMALL_GROWMON_ID, ALT_DMALL_GROWMON_FQID, ALT_DMALL_GROWMON_FQNAME, DMALL_GROWMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Growmon
        { DMALL_GROWMON_X_NAME, DMALL_GROWMON_X_ID, ALT_DMALL_GROWMON_X_FQID, ALT_DMALL_GROWMON_X_FQNAME, DMALL_GROWMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Growmon X
        { DMALL_GRYZMON_NAME, DMALL_GRYZMON_ID, ALT_DMALL_GRYZMON_FQID, ALT_DMALL_GRYZMON_FQNAME, DMALL_GRYZMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Gryzmon
        { DMALL_GUARDROMON_GOLD_NAME, DMALL_GUARDROMON_GOLD_ID, ALT_DMALL_GUARDROMON_GOLD_FQID, ALT_DMALL_GUARDROMON_GOLD_FQNAME, DMALL_GUARDROMON_GOLD_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Guardromon (Gold)
        { DMALL_GUARDROMON_NAME, DMALL_GUARDROMON_ID, ALT_DMALL_GUARDROMON_FQID, ALT_DMALL_GUARDROMON_FQNAME, DMALL_GUARDROMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Guardromon
        { DMALL_GUILMON_NAME, DMALL_GUILMON_ID, ALT_DMALL_GUILMON_FQID, ALT_DMALL_GUILMON_FQNAME, DMALL_GUILMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Guilmon
        { DMALL_GUILMON_X_NAME, DMALL_GUILMON_X_ID, ALT_DMALL_GUILMON_X_FQID, ALT_DMALL_GUILMON_X_FQNAME, DMALL_GUILMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Guilmon X
        { DMALL_GUMMYMON_NAME, DMALL_GUMMYMON_ID, ALT_DMALL_GUMMYMON_FQID, ALT_DMALL_GUMMYMON_FQNAME, DMALL_GUMMYMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Gummymon
        { DMALL_GUNDRAMON_NAME, DMALL_GUNDRAMON_ID, ALT_DMALL_GUNDRAMON_FQID, ALT_DMALL_GUNDRAMON_FQNAME, DMALL_GUNDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Gundramon
        { DMALL_GURURUMON_NAME, DMALL_GURURUMON_ID, ALT_DMALL_GURURUMON_FQID, ALT_DMALL_GURURUMON_FQNAME, DMALL_GURURUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Gururumon
        { DMALL_GUSOKUMON_NAME, DMALL_GUSOKUMON_ID, ALT_DMALL_GUSOKUMON_FQID, ALT_DMALL_GUSOKUMON_FQNAME, DMALL_GUSOKUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Gusokumon
        { DMALL_HACKMON_NAME, DMALL_HACKMON_ID, ALT_DMALL_HACKMON_FQID, ALT_DMALL_HACKMON_FQNAME, DMALL_HACKMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Hackmon
        { DMALL_HAGURUMON_NAME, DMALL_HAGURUMON_ID, ALT_DMALL_HAGURUMON_FQID, ALT_DMALL_HAGURUMON_FQNAME, DMALL_HAGURUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Hagurumon
        { DMALL_HANGYOMON_NAME, DMALL_HANGYOMON_ID, ALT_DMALL_HANGYOMON_FQID, ALT_DMALL_HANGYOMON_FQNAME, DMALL_HANGYOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Hangyomon
        { DMALL_HANUMON_NAME, DMALL_HANUMON_ID, ALT_DMALL_HANUMON_FQID, ALT_DMALL_HANUMON_FQNAME, DMALL_HANUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Hanumon
        { DMALL_HERAKLE_KABUTERIMON_NAME, DMALL_HERAKLE_KABUTERIMON_ID, ALT_DMALL_HERAKLE_KABUTERIMON_FQID, ALT_DMALL_HERAKLE_KABUTERIMON_FQNAME, DMALL_HERAKLE_KABUTERIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Herakle Kabuterimon
        { DMALL_HERISSMON_NAME, DMALL_HERISSMON_ID, ALT_DMALL_HERISSMON_FQID, ALT_DMALL_HERISSMON_FQNAME, DMALL_HERISSMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Herissmon
        { DMALL_HEXEBLAUMON_NAME, DMALL_HEXEBLAUMON_ID, ALT_DMALL_HEXEBLAUMON_FQID, ALT_DMALL_HEXEBLAUMON_FQNAME, DMALL_HEXEBLAUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Hexeblaumon
        { DMALL_HI_ANDROMON_NAME, DMALL_HI_ANDROMON_ID, ALT_DMALL_HI_ANDROMON_FQID, ALT_DMALL_HI_ANDROMON_FQNAME, DMALL_HI_ANDROMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Hi Andromon
        { DMALL_HISYARYUMON_NAME, DMALL_HISYARYUMON_ID, ALT_DMALL_HISYARYUMON_FQID, ALT_DMALL_HISYARYUMON_FQNAME, DMALL_HISYARYUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Hisyaryumon
        { DMALL_HIYARIMON_NAME, DMALL_HIYARIMON_ID, ALT_DMALL_HIYARIMON_FQID, ALT_DMALL_HIYARIMON_FQNAME, DMALL_HIYARIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Hiyarimon
        { DMALL_HOLY_ANGEMON_NAME, DMALL_HOLY_ANGEMON_ID, ALT_DMALL_HOLY_ANGEMON_FQID, ALT_DMALL_HOLY_ANGEMON_FQNAME, DMALL_HOLY_ANGEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Holy Angemon
        { DMALL_HOLY_DIGITAMAMON_NAME, DMALL_HOLY_DIGITAMAMON_ID, ALT_DMALL_HOLY_DIGITAMAMON_FQID, ALT_DMALL_HOLY_DIGITAMAMON_FQNAME, DMALL_HOLY_DIGITAMAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Holy Digitamamon
        { DMALL_HOLYDRAMON_NAME, DMALL_HOLYDRAMON_ID, ALT_DMALL_HOLYDRAMON_FQID, ALT_DMALL_HOLYDRAMON_FQNAME, DMALL_HOLYDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Holydramon
        { DMALL_HOLYDRAMON_X_NAME, DMALL_HOLYDRAMON_X_ID, ALT_DMALL_HOLYDRAMON_X_FQID, ALT_DMALL_HOLYDRAMON_X_FQNAME, DMALL_HOLYDRAMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Holydramon X
        { DMALL_HOOKMON_NAME, DMALL_HOOKMON_ID, ALT_DMALL_HOOKMON_FQID, ALT_DMALL_HOOKMON_FQNAME, DMALL_HOOKMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Hookmon
        { DMALL_HOUOUMON_NAME, DMALL_HOUOUMON_ID, ALT_DMALL_HOUOUMON_FQID, ALT_DMALL_HOUOUMON_FQNAME, DMALL_HOUOUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Hououmon
        { DMALL_HOUOUMON_X_NAME, DMALL_HOUOUMON_X_ID, ALT_DMALL_HOUOUMON_X_FQID, ALT_DMALL_HOUOUMON_X_FQNAME, DMALL_HOUOUMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Hououmon X
        { DMALL_HYOKOMON_NAME, DMALL_HYOKOMON_ID, ALT_DMALL_HYOKOMON_FQID, ALT_DMALL_HYOKOMON_FQNAME, DMALL_HYOKOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Hyokomon
        { DMALL_HYOUGAMON_NAME, DMALL_HYOUGAMON_ID, ALT_DMALL_HYOUGAMON_FQID, ALT_DMALL_HYOUGAMON_FQNAME, DMALL_HYOUGAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Hyougamon
        { DMALL_ICE_DEVIMON_NAME, DMALL_ICE_DEVIMON_ID, ALT_DMALL_ICE_DEVIMON_FQID, ALT_DMALL_ICE_DEVIMON_FQNAME, DMALL_ICE_DEVIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Ice Devimon
        { DMALL_ICEMON_NAME, DMALL_ICEMON_ID, ALT_DMALL_ICEMON_FQID, ALT_DMALL_ICEMON_FQNAME, DMALL_ICEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Icemon
        { DMALL_IGAMON_NAME, DMALL_IGAMON_ID, ALT_DMALL_IGAMON_FQID, ALT_DMALL_IGAMON_FQNAME, DMALL_IGAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Igamon
        { DMALL_IKKAKUMON_NAME, DMALL_IKKAKUMON_ID, ALT_DMALL_IKKAKUMON_FQID, ALT_DMALL_IKKAKUMON_FQNAME, DMALL_IKKAKUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Ikkakumon
        { DMALL_IMPERIALDRAMON_FIGHTER_MODE_BLACK_NAME, DMALL_IMPERIALDRAMON_FIGHTER_MODE_BLACK_ID, ALT_DMALL_IMPERIALDRAMON_FIGHTER_MODE_BLACK_FQID, ALT_DMALL_IMPERIALDRAMON_FIGHTER_MODE_BLACK_FQNAME, DMALL_IMPERIALDRAMON_FIGHTER_MODE_BLACK_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Imperialdramon Fighter Mode (Black)
        { DMALL_IMPERIALDRAMON_FIGHTER_MODE_NAME, DMALL_IMPERIALDRAMON_FIGHTER_MODE_ID, ALT_DMALL_IMPERIALDRAMON_FIGHTER_MODE_FQID, ALT_DMALL_IMPERIALDRAMON_FIGHTER_MODE_FQNAME, DMALL_IMPERIALDRAMON_FIGHTER_MODE_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Imperialdramon Fighter Mode
        { DMALL_IMPERIALDRAMON_PALADIN_MODE_NAME, DMALL_IMPERIALDRAMON_PALADIN_MODE_ID, ALT_DMALL_IMPERIALDRAMON_PALADIN_MODE_FQID, ALT_DMALL_IMPERIALDRAMON_PALADIN_MODE_FQNAME, DMALL_IMPERIALDRAMON_PALADIN_MODE_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Imperialdramon Paladin Mode
        { DMALL_IMPMON_NAME, DMALL_IMPMON_ID, ALT_DMALL_IMPMON_FQID, ALT_DMALL_IMPMON_FQNAME, DMALL_IMPMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Impmon
        { DMALL_IMPMON_X_NAME, DMALL_IMPMON_X_ID, ALT_DMALL_IMPMON_X_FQID, ALT_DMALL_IMPMON_X_FQNAME, DMALL_IMPMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Impmon X
        { DMALL_INSEKIMON_NAME, DMALL_INSEKIMON_ID, ALT_DMALL_INSEKIMON_FQID, ALT_DMALL_INSEKIMON_FQNAME, DMALL_INSEKIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Insekimon
        { DMALL_JAZAMON_NAME, DMALL_JAZAMON_ID, ALT_DMALL_JAZAMON_FQID, ALT_DMALL_JAZAMON_FQNAME, DMALL_JAZAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Jazamon
        { DMALL_JAZARDMON_NAME, DMALL_JAZARDMON_ID, ALT_DMALL_JAZARDMON_FQID, ALT_DMALL_JAZARDMON_FQNAME, DMALL_JAZARDMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Jazardmon
        { DMALL_JAZARICHMON_NAME, DMALL_JAZARICHMON_ID, ALT_DMALL_JAZARICHMON_FQID, ALT_DMALL_JAZARICHMON_FQNAME, DMALL_JAZARICHMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Jazarichmon
        { DMALL_JESMON_GX_NAME, DMALL_JESMON_GX_ID, ALT_DMALL_JESMON_GX_FQID, ALT_DMALL_JESMON_GX_FQNAME, DMALL_JESMON_GX_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Jesmon GX
        { DMALL_JESMON_NAME, DMALL_JESMON_ID, ALT_DMALL_JESMON_FQID, ALT_DMALL_JESMON_FQNAME, DMALL_JESMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Jesmon
        { DMALL_JESMON_X_NAME, DMALL_JESMON_X_ID, ALT_DMALL_JESMON_X_FQID, ALT_DMALL_JESMON_X_FQNAME, DMALL_JESMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Jesmon X
        { DMALL_JUNKMON_NAME, DMALL_JUNKMON_ID, ALT_DMALL_JUNKMON_FQID, ALT_DMALL_JUNKMON_FQNAME, DMALL_JUNKMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Junkmon
        { DMALL_JUSTIMON_X_NAME, DMALL_JUSTIMON_X_ID, ALT_DMALL_JUSTIMON_X_FQID, ALT_DMALL_JUSTIMON_X_FQNAME, DMALL_JUSTIMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Justimon X
        { DMALL_JYAGAMON_NAME, DMALL_JYAGAMON_ID, ALT_DMALL_JYAGAMON_FQID, ALT_DMALL_JYAGAMON_FQNAME, DMALL_JYAGAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Jyagamon
        { DMALL_JYARIMON_NAME, DMALL_JYARIMON_ID, ALT_DMALL_JYARIMON_FQID, ALT_DMALL_JYARIMON_FQNAME, DMALL_JYARIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Jyarimon
        { DMALL_JYUREIMON_NAME, DMALL_JYUREIMON_ID, ALT_DMALL_JYUREIMON_FQID, ALT_DMALL_JYUREIMON_FQNAME, DMALL_JYUREIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Jyureimon
        { DMALL_KABUTERIMON_NAME, DMALL_KABUTERIMON_ID, ALT_DMALL_KABUTERIMON_FQID, ALT_DMALL_KABUTERIMON_FQNAME, DMALL_KABUTERIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Kabuterimon
        { DMALL_KAISER_GREYMON_NAME, DMALL_KAISER_GREYMON_ID, ALT_DMALL_KAISER_GREYMON_FQID, ALT_DMALL_KAISER_GREYMON_FQNAME, DMALL_KAISER_GREYMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Kaiser Greymon
        { DMALL_KAISER_LEOMON_NAME, DMALL_KAISER_LEOMON_ID, ALT_DMALL_KAISER_LEOMON_FQID, ALT_DMALL_KAISER_LEOMON_FQNAME, DMALL_KAISER_LEOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Kaiser Leomon
        { DMALL_KAKKINMON_NAME, DMALL_KAKKINMON_ID, ALT_DMALL_KAKKINMON_FQID, ALT_DMALL_KAKKINMON_FQNAME, DMALL_KAKKINMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Kakkinmon
        { DMALL_KARATSUKI_NUMEMON_NAME, DMALL_KARATSUKI_NUMEMON_ID, ALT_DMALL_KARATSUKI_NUMEMON_FQID, ALT_DMALL_KARATSUKI_NUMEMON_FQNAME, DMALL_KARATSUKI_NUMEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Karatsuki Numemon
        { DMALL_KAZUCHIMON_NAME, DMALL_KAZUCHIMON_ID, ALT_DMALL_KAZUCHIMON_FQID, ALT_DMALL_KAZUCHIMON_FQNAME, DMALL_KAZUCHIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Kazuchimon
        { DMALL_KERAMON_NAME, DMALL_KERAMON_ID, ALT_DMALL_KERAMON_FQID, ALT_DMALL_KERAMON_FQNAME, DMALL_KERAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Keramon
        { DMALL_KERAMON_X_NAME, DMALL_KERAMON_X_ID, ALT_DMALL_KERAMON_X_FQID, ALT_DMALL_KERAMON_X_FQNAME, DMALL_KERAMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Keramon X
        { DMALL_KETOMON_NAME, DMALL_KETOMON_ID, ALT_DMALL_KETOMON_FQID, ALT_DMALL_KETOMON_FQNAME, DMALL_KETOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Ketomon
        { DMALL_KIIMON_NAME, DMALL_KIIMON_ID, ALT_DMALL_KIIMON_FQID, ALT_DMALL_KIIMON_FQNAME, DMALL_KIIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Kiimon
        { DMALL_KING_ETEMON_NAME, DMALL_KING_ETEMON_ID, ALT_DMALL_KING_ETEMON_FQID, ALT_DMALL_KING_ETEMON_FQNAME, DMALL_KING_ETEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for King Etemon
        { DMALL_KIWIMON_NAME, DMALL_KIWIMON_ID, ALT_DMALL_KIWIMON_FQID, ALT_DMALL_KIWIMON_FQNAME, DMALL_KIWIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Kiwimon
        { DMALL_KNIGHTMON_NAME, DMALL_KNIGHTMON_ID, ALT_DMALL_KNIGHTMON_FQID, ALT_DMALL_KNIGHTMON_FQNAME, DMALL_KNIGHTMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Knightmon
        { DMALL_KOEMON_NAME, DMALL_KOEMON_ID, ALT_DMALL_KOEMON_FQID, ALT_DMALL_KOEMON_FQNAME, DMALL_KOEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Koemon
        { DMALL_KOKABUTERIMON_NAME, DMALL_KOKABUTERIMON_ID, ALT_DMALL_KOKABUTERIMON_FQID, ALT_DMALL_KOKABUTERIMON_FQNAME, DMALL_KOKABUTERIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Kokabuterimon
        { DMALL_KOKUWAMON_NAME, DMALL_KOKUWAMON_ID, ALT_DMALL_KOKUWAMON_FQID, ALT_DMALL_KOKUWAMON_FQNAME, DMALL_KOKUWAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Kokuwamon
        { DMALL_KOKUWAMON_X_NAME, DMALL_KOKUWAMON_X_ID, ALT_DMALL_KOKUWAMON_X_FQID, ALT_DMALL_KOKUWAMON_X_FQNAME, DMALL_KOKUWAMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Kokuwamon X
        { DMALL_KOROMON_NAME, DMALL_KOROMON_ID, ALT_DMALL_KOROMON_FQID, ALT_DMALL_KOROMON_FQNAME, DMALL_KOROMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Koromon
        { DMALL_KOUGAMON_NAME, DMALL_KOUGAMON_ID, ALT_DMALL_KOUGAMON_FQID, ALT_DMALL_KOUGAMON_FQNAME, DMALL_KOUGAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Kougamon
        { DMALL_KOZENIMON_NAME, DMALL_KOZENIMON_ID, ALT_DMALL_KOZENIMON_FQID, ALT_DMALL_KOZENIMON_FQNAME, DMALL_KOZENIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Kozenimon
        { DMALL_KUNEMON_NAME, DMALL_KUNEMON_ID, ALT_DMALL_KUNEMON_FQID, ALT_DMALL_KUNEMON_FQNAME, DMALL_KUNEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Kunemon
        { DMALL_KURAMON_NAME, DMALL_KURAMON_ID, ALT_DMALL_KURAMON_FQID, ALT_DMALL_KURAMON_FQNAME, DMALL_KURAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Kuramon
        { DMALL_KUWAGAMON_NAME, DMALL_KUWAGAMON_ID, ALT_DMALL_KUWAGAMON_FQID, ALT_DMALL_KUWAGAMON_FQNAME, DMALL_KUWAGAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Kuwagamon
        { DMALL_KUWAGAMON_X_NAME, DMALL_KUWAGAMON_X_ID, ALT_DMALL_KUWAGAMON_X_FQID, ALT_DMALL_KUWAGAMON_X_FQNAME, DMALL_KUWAGAMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Kuwagamon X
        { DMALL_KUZUHAMON_NAME, DMALL_KUZUHAMON_ID, ALT_DMALL_KUZUHAMON_FQID, ALT_DMALL_KUZUHAMON_FQNAME, DMALL_KUZUHAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Kuzuhamon
        { DMALL_KYOKYOMON_NAME, DMALL_KYOKYOMON_ID, ALT_DMALL_KYOKYOMON_FQID, ALT_DMALL_KYOKYOMON_FQNAME, DMALL_KYOKYOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Kyokyomon
        { DMALL_KYUBIMON_NAME, DMALL_KYUBIMON_ID, ALT_DMALL_KYUBIMON_FQID, ALT_DMALL_KYUBIMON_FQNAME, DMALL_KYUBIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Kyubimon
        { DMALL_KYUBIMON_SILVER_NAME, DMALL_KYUBIMON_SILVER_ID, ALT_DMALL_KYUBIMON_SILVER_FQID, ALT_DMALL_KYUBIMON_SILVER_FQNAME, DMALL_KYUBIMON_SILVER_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Kyubimon (Silver)
        { DMALL_LABRAMON_NAME, DMALL_LABRAMON_ID, ALT_DMALL_LABRAMON_FQID, ALT_DMALL_LABRAMON_FQNAME, DMALL_LABRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Labramon
        { DMALL_LADYDEVIMON_NAME, DMALL_LADYDEVIMON_ID, ALT_DMALL_LADYDEVIMON_FQID, ALT_DMALL_LADYDEVIMON_FQNAME, DMALL_LADYDEVIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for LadyDevimon
        { DMALL_LADYDEVIMON_X_NAME, DMALL_LADYDEVIMON_X_ID, ALT_DMALL_LADYDEVIMON_X_FQID, ALT_DMALL_LADYDEVIMON_X_FQNAME, DMALL_LADYDEVIMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for LadyDevimon X
        { DMALL_LALAMON_NAME, DMALL_LALAMON_ID, ALT_DMALL_LALAMON_FQID, ALT_DMALL_LALAMON_FQNAME, DMALL_LALAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Lalamon
        { DMALL_LAVOGARITAMON_NAME, DMALL_LAVOGARITAMON_ID, ALT_DMALL_LAVOGARITAMON_FQID, ALT_DMALL_LAVOGARITAMON_FQNAME, DMALL_LAVOGARITAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Lavogaritamon
        { DMALL_LAVORVOMON_NAME, DMALL_LAVORVOMON_ID, ALT_DMALL_LAVORVOMON_FQID, ALT_DMALL_LAVORVOMON_FQNAME, DMALL_LAVORVOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Lavorvomon
        { DMALL_LEAFMON_NAME, DMALL_LEAFMON_ID, ALT_DMALL_LEAFMON_FQID, ALT_DMALL_LEAFMON_FQNAME, DMALL_LEAFMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Leafmon
        { DMALL_LEKISMON_NAME, DMALL_LEKISMON_ID, ALT_DMALL_LEKISMON_FQID, ALT_DMALL_LEKISMON_FQNAME, DMALL_LEKISMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Lekismon
        { DMALL_LEOMON_NAME, DMALL_LEOMON_ID, ALT_DMALL_LEOMON_FQID, ALT_DMALL_LEOMON_FQNAME, DMALL_LEOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Leomon
        { DMALL_LEOMON_X_NAME, DMALL_LEOMON_X_ID, ALT_DMALL_LEOMON_X_FQID, ALT_DMALL_LEOMON_X_FQNAME, DMALL_LEOMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Leomon X
        { DMALL_LEVIAMON_NAME, DMALL_LEVIAMON_ID, ALT_DMALL_LEVIAMON_FQID, ALT_DMALL_LEVIAMON_FQNAME, DMALL_LEVIAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Leviamon
        { DMALL_LEVIAMON_X_NAME, DMALL_LEVIAMON_X_ID, ALT_DMALL_LEVIAMON_X_FQID, ALT_DMALL_LEVIAMON_X_FQNAME, DMALL_LEVIAMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Leviamon X
        { DMALL_LILAMON_NAME, DMALL_LILAMON_ID, ALT_DMALL_LILAMON_FQID, ALT_DMALL_LILAMON_FQNAME, DMALL_LILAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Lilamon
        { DMALL_LILIMON_NAME, DMALL_LILIMON_ID, ALT_DMALL_LILIMON_FQID, ALT_DMALL_LILIMON_FQNAME, DMALL_LILIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Lilimon
        { DMALL_LILIMON_X_NAME, DMALL_LILIMON_X_ID, ALT_DMALL_LILIMON_X_FQID, ALT_DMALL_LILIMON_X_FQNAME, DMALL_LILIMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Lilimon X
        { DMALL_LILITHMON_NAME, DMALL_LILITHMON_ID, ALT_DMALL_LILITHMON_FQID, ALT_DMALL_LILITHMON_FQNAME, DMALL_LILITHMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Lilithmon
        { DMALL_LILITHMON_X_NAME, DMALL_LILITHMON_X_ID, ALT_DMALL_LILITHMON_X_FQID, ALT_DMALL_LILITHMON_X_FQNAME, DMALL_LILITHMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Lilithmon X
        { DMALL_LOPMON_NAME, DMALL_LOPMON_ID, ALT_DMALL_LOPMON_FQID, ALT_DMALL_LOPMON_FQNAME, DMALL_LOPMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Lopmon
        { DMALL_LOPMON_X_NAME, DMALL_LOPMON_X_ID, ALT_DMALL_LOPMON_X_FQID, ALT_DMALL_LOPMON_X_FQNAME, DMALL_LOPMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Lopmon X
        { DMALL_LORDKNIGHTMON_X_NAME, DMALL_LORDKNIGHTMON_X_ID, ALT_DMALL_LORDKNIGHTMON_X_FQID, ALT_DMALL_LORDKNIGHTMON_X_FQNAME, DMALL_LORDKNIGHTMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for LordKnightmon X
        { DMALL_LOTUSMON_NAME, DMALL_LOTUSMON_ID, ALT_DMALL_LOTUSMON_FQID, ALT_DMALL_LOTUSMON_FQNAME, DMALL_LOTUSMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Lotusmon
        { DMALL_LUCEMON_FALLDOWN_MODE_NAME, DMALL_LUCEMON_FALLDOWN_MODE_ID, ALT_DMALL_LUCEMON_FALLDOWN_MODE_FQID, ALT_DMALL_LUCEMON_FALLDOWN_MODE_FQNAME, DMALL_LUCEMON_FALLDOWN_MODE_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Lucemon Falldown Mode
        { DMALL_LUCEMON_NAME, DMALL_LUCEMON_ID, ALT_DMALL_LUCEMON_FQID, ALT_DMALL_LUCEMON_FQNAME, DMALL_LUCEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Lucemon
        { DMALL_LUCEMON_SATAN_MODE_NAME, DMALL_LUCEMON_SATAN_MODE_ID, ALT_DMALL_LUCEMON_SATAN_MODE_FQID, ALT_DMALL_LUCEMON_SATAN_MODE_FQNAME, DMALL_LUCEMON_SATAN_MODE_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Lucemon Satan Mode
        { DMALL_LUCEMON_X_NAME, DMALL_LUCEMON_X_ID, ALT_DMALL_LUCEMON_X_FQID, ALT_DMALL_LUCEMON_X_FQNAME, DMALL_LUCEMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Lucemon X
        { DMALL_LUDOMON_NAME, DMALL_LUDOMON_ID, ALT_DMALL_LUDOMON_FQID, ALT_DMALL_LUDOMON_FQNAME, DMALL_LUDOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Ludomon
        { DMALL_LUNAMON_NAME, DMALL_LUNAMON_ID, ALT_DMALL_LUNAMON_FQID, ALT_DMALL_LUNAMON_FQNAME, DMALL_LUNAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Lunamon
        { DMALL_LYNXMON_NAME, DMALL_LYNXMON_ID, ALT_DMALL_LYNXMON_FQID, ALT_DMALL_LYNXMON_FQNAME, DMALL_LYNXMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Lynxmon
        { DMALL_MACH_GAOGAMON_NAME, DMALL_MACH_GAOGAMON_ID, ALT_DMALL_MACH_GAOGAMON_FQID, ALT_DMALL_MACH_GAOGAMON_FQNAME, DMALL_MACH_GAOGAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Mach Gaogamon
        { DMALL_MAD_LEOMON_NAME, DMALL_MAD_LEOMON_ID, ALT_DMALL_MAD_LEOMON_FQID, ALT_DMALL_MAD_LEOMON_FQNAME, DMALL_MAD_LEOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Mad Leomon
        { DMALL_MAGNAMON_X_NAME, DMALL_MAGNAMON_X_ID, ALT_DMALL_MAGNAMON_X_FQID, ALT_DMALL_MAGNAMON_X_FQNAME, DMALL_MAGNAMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Magnamon X
        { DMALL_MAMBOMON_NAME, DMALL_MAMBOMON_ID, ALT_DMALL_MAMBOMON_FQID, ALT_DMALL_MAMBOMON_FQNAME, DMALL_MAMBOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Mambomon
        { DMALL_MAMEMON_NAME, DMALL_MAMEMON_ID, ALT_DMALL_MAMEMON_FQID, ALT_DMALL_MAMEMON_FQNAME, DMALL_MAMEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Mamemon
        { DMALL_MAMEMON_X_NAME, DMALL_MAMEMON_X_ID, ALT_DMALL_MAMEMON_X_FQID, ALT_DMALL_MAMEMON_X_FQNAME, DMALL_MAMEMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Mamemon X
        { DMALL_MAMETYRAMON_NAME, DMALL_MAMETYRAMON_ID, ALT_DMALL_MAMETYRAMON_FQID, ALT_DMALL_MAMETYRAMON_FQNAME, DMALL_MAMETYRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Mametyramon
        { DMALL_MAMMON_NAME, DMALL_MAMMON_ID, ALT_DMALL_MAMMON_FQID, ALT_DMALL_MAMMON_FQNAME, DMALL_MAMMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Mammon
        { DMALL_MAMMON_X_NAME, DMALL_MAMMON_X_ID, ALT_DMALL_MAMMON_X_FQID, ALT_DMALL_MAMMON_X_FQNAME, DMALL_MAMMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Mammon X
        { DMALL_MANTARAYMON_X_NAME, DMALL_MANTARAYMON_X_ID, ALT_DMALL_MANTARAYMON_X_FQID, ALT_DMALL_MANTARAYMON_X_FQNAME, DMALL_MANTARAYMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Mantaraymon X
        { DMALL_MANTICOREMON_NAME, DMALL_MANTICOREMON_ID, ALT_DMALL_MANTICOREMON_FQID, ALT_DMALL_MANTICOREMON_FQNAME, DMALL_MANTICOREMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Manticoremon
        { DMALL_MARIN_ANGEMON_NAME, DMALL_MARIN_ANGEMON_ID, ALT_DMALL_MARIN_ANGEMON_FQID, ALT_DMALL_MARIN_ANGEMON_FQNAME, DMALL_MARIN_ANGEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Marin Angemon
        { DMALL_MARIN_CHIMAIRAMON_NAME, DMALL_MARIN_CHIMAIRAMON_ID, ALT_DMALL_MARIN_CHIMAIRAMON_FQID, ALT_DMALL_MARIN_CHIMAIRAMON_FQNAME, DMALL_MARIN_CHIMAIRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Marin Chimairamon
        { DMALL_MARIN_DEVIMON_NAME, DMALL_MARIN_DEVIMON_ID, ALT_DMALL_MARIN_DEVIMON_FQID, ALT_DMALL_MARIN_DEVIMON_FQNAME, DMALL_MARIN_DEVIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Marin Devimon
        { DMALL_MASTEMON_NAME, DMALL_MASTEMON_ID, ALT_DMALL_MASTEMON_FQID, ALT_DMALL_MASTEMON_FQNAME, DMALL_MASTEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Mastemon
        { DMALL_MECHANORIMON_NAME, DMALL_MECHANORIMON_ID, ALT_DMALL_MECHANORIMON_FQID, ALT_DMALL_MECHANORIMON_FQNAME, DMALL_MECHANORIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Mechanorimon
        { DMALL_MEGADRAMON_NAME, DMALL_MEGADRAMON_ID, ALT_DMALL_MEGADRAMON_FQID, ALT_DMALL_MEGADRAMON_FQNAME, DMALL_MEGADRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Megadramon
        { DMALL_MEGALO_GROWMON_ORANGE_NAME, DMALL_MEGALO_GROWMON_ORANGE_ID, ALT_DMALL_MEGALO_GROWMON_ORANGE_FQID, ALT_DMALL_MEGALO_GROWMON_ORANGE_FQNAME, DMALL_MEGALO_GROWMON_ORANGE_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Megalo Growmon (Orange)
        { DMALL_MEGALO_GROWMON_NAME, DMALL_MEGALO_GROWMON_ID, ALT_DMALL_MEGALO_GROWMON_FQID, ALT_DMALL_MEGALO_GROWMON_FQNAME, DMALL_MEGALO_GROWMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Megalo Growmon
        { DMALL_MEGALO_GROWMON_X_NAME, DMALL_MEGALO_GROWMON_X_ID, ALT_DMALL_MEGALO_GROWMON_X_FQID, ALT_DMALL_MEGALO_GROWMON_X_FQNAME, DMALL_MEGALO_GROWMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Megalo Growmon X
        { DMALL_MEGA_SEADRAMON_NAME, DMALL_MEGA_SEADRAMON_ID, ALT_DMALL_MEGA_SEADRAMON_FQID, ALT_DMALL_MEGA_SEADRAMON_FQNAME, DMALL_MEGA_SEADRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Mega Seadramon
        { DMALL_MEGA_SEADRAMON_X_NAME, DMALL_MEGA_SEADRAMON_X_ID, ALT_DMALL_MEGA_SEADRAMON_X_FQID, ALT_DMALL_MEGA_SEADRAMON_X_FQNAME, DMALL_MEGA_SEADRAMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Mega Seadramon X
        { DMALL_MEGIDRAMON_NAME, DMALL_MEGIDRAMON_ID, ALT_DMALL_MEGIDRAMON_FQID, ALT_DMALL_MEGIDRAMON_FQNAME, DMALL_MEGIDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Megidramon
        { DMALL_MEGIDRAMON_X_NAME, DMALL_MEGIDRAMON_X_ID, ALT_DMALL_MEGIDRAMON_X_FQID, ALT_DMALL_MEGIDRAMON_X_FQNAME, DMALL_MEGIDRAMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Megidramon X
        { DMALL_MEICOOMON_BABY_NAME, DMALL_MEICOOMON_BABY_ID, ALT_DMALL_MEICOOMON_BABY_FQID, ALT_DMALL_MEICOOMON_BABY_FQNAME, DMALL_MEICOOMON_BABY_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Meicoomon (Baby)
        { DMALL_MEICOOMON_CHILD_NAME, DMALL_MEICOOMON_CHILD_ID, ALT_DMALL_MEICOOMON_CHILD_FQID, ALT_DMALL_MEICOOMON_CHILD_FQNAME, DMALL_MEICOOMON_CHILD_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Meicoomon (Child)
        { DMALL_MEICOOMON_NAME, DMALL_MEICOOMON_ID, ALT_DMALL_MEICOOMON_FQID, ALT_DMALL_MEICOOMON_FQNAME, DMALL_MEICOOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Meicoomon
        { DMALL_MEICRACKMON_NAME, DMALL_MEICRACKMON_ID, ALT_DMALL_MEICRACKMON_FQID, ALT_DMALL_MEICRACKMON_FQNAME, DMALL_MEICRACKMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Meicrackmon
        { DMALL_MEICRACKMON_VICIOUS_MODE_NAME, DMALL_MEICRACKMON_VICIOUS_MODE_ID, ALT_DMALL_MEICRACKMON_VICIOUS_MODE_FQID, ALT_DMALL_MEICRACKMON_VICIOUS_MODE_FQNAME, DMALL_MEICRACKMON_VICIOUS_MODE_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Meicrackmon Vicious Mode
        { DMALL_MEPHISMON_NAME, DMALL_MEPHISMON_ID, ALT_DMALL_MEPHISMON_FQID, ALT_DMALL_MEPHISMON_FQNAME, DMALL_MEPHISMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Mephismon
        { DMALL_MEPHISMON_X_NAME, DMALL_MEPHISMON_X_ID, ALT_DMALL_MEPHISMON_X_FQID, ALT_DMALL_MEPHISMON_X_FQNAME, DMALL_MEPHISMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Mephismon X
        { DMALL_MERAMON_NAME, DMALL_MERAMON_ID, ALT_DMALL_MERAMON_FQID, ALT_DMALL_MERAMON_FQNAME, DMALL_MERAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Meramon
        { DMALL_MERAMON_X_NAME, DMALL_MERAMON_X_ID, ALT_DMALL_MERAMON_X_FQID, ALT_DMALL_MERAMON_X_FQNAME, DMALL_MERAMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Meramon X
        { DMALL_MERMAIMON_NAME, DMALL_MERMAIMON_ID, ALT_DMALL_MERMAIMON_FQID, ALT_DMALL_MERMAIMON_FQNAME, DMALL_MERMAIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Mermaimon
        { DMALL_METAL_ETEMON_NAME, DMALL_METAL_ETEMON_ID, ALT_DMALL_METAL_ETEMON_FQID, ALT_DMALL_METAL_ETEMON_FQNAME, DMALL_METAL_ETEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Metal Etemon
        { DMALL_METAL_GARURUMON_BLACK_NAME, DMALL_METAL_GARURUMON_BLACK_ID, ALT_DMALL_METAL_GARURUMON_BLACK_FQID, ALT_DMALL_METAL_GARURUMON_BLACK_FQNAME, DMALL_METAL_GARURUMON_BLACK_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Metal Garurumon (Black)
        { DMALL_METAL_GARURUMON_NAME, DMALL_METAL_GARURUMON_ID, ALT_DMALL_METAL_GARURUMON_FQID, ALT_DMALL_METAL_GARURUMON_FQNAME, DMALL_METAL_GARURUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Metal Garurumon
        { DMALL_METAL_GARURUMON_X_NAME, DMALL_METAL_GARURUMON_X_ID, ALT_DMALL_METAL_GARURUMON_X_FQID, ALT_DMALL_METAL_GARURUMON_X_FQNAME, DMALL_METAL_GARURUMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Metal Garurumon X
        { DMALL_METAL_GREYMON_NAME, DMALL_METAL_GREYMON_ID, ALT_DMALL_METAL_GREYMON_FQID, ALT_DMALL_METAL_GREYMON_FQNAME, DMALL_METAL_GREYMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Metal Greymon
        { DMALL_METAL_GREYMON_VIRUS_NAME, DMALL_METAL_GREYMON_VIRUS_ID, ALT_DMALL_METAL_GREYMON_VIRUS_FQID, ALT_DMALL_METAL_GREYMON_VIRUS_FQNAME, DMALL_METAL_GREYMON_VIRUS_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Metal Greymon (Virus)
        { DMALL_METAL_GREYMON_VIRUS_X_NAME, DMALL_METAL_GREYMON_VIRUS_X_ID, ALT_DMALL_METAL_GREYMON_VIRUS_X_FQID, ALT_DMALL_METAL_GREYMON_VIRUS_X_FQNAME, DMALL_METAL_GREYMON_VIRUS_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Metal Greymon (Virus) X
        { DMALL_METALGREYMON_X_NAME, DMALL_METALGREYMON_X_ID, ALT_DMALL_METALGREYMON_X_FQID, ALT_DMALL_METALGREYMON_X_FQNAME, DMALL_METALGREYMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for MetalGreymon X
        { DMALL_METALLICDRAMON_NAME, DMALL_METALLICDRAMON_ID, ALT_DMALL_METALLICDRAMON_FQID, ALT_DMALL_METALLICDRAMON_FQNAME, DMALL_METALLICDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Metallicdramon
        { DMALL_METAL_MAMEMON_NAME, DMALL_METAL_MAMEMON_ID, ALT_DMALL_METAL_MAMEMON_FQID, ALT_DMALL_METAL_MAMEMON_FQNAME, DMALL_METAL_MAMEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Metal Mamemon
        { DMALL_METAL_MAMEMON_X_NAME, DMALL_METAL_MAMEMON_X_ID, ALT_DMALL_METAL_MAMEMON_X_FQID, ALT_DMALL_METAL_MAMEMON_X_FQNAME, DMALL_METAL_MAMEMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Metal Mamemon X
        { DMALL_METAL_PHANTOMON_NAME, DMALL_METAL_PHANTOMON_ID, ALT_DMALL_METAL_PHANTOMON_FQID, ALT_DMALL_METAL_PHANTOMON_FQNAME, DMALL_METAL_PHANTOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Metal Phantomon
        { DMALL_METAL_PIRANIMON_NAME, DMALL_METAL_PIRANIMON_ID, ALT_DMALL_METAL_PIRANIMON_FQID, ALT_DMALL_METAL_PIRANIMON_FQNAME, DMALL_METAL_PIRANIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Metal Piranimon
        { DMALL_METAL_SEADRAMON_NAME, DMALL_METAL_SEADRAMON_ID, ALT_DMALL_METAL_SEADRAMON_FQID, ALT_DMALL_METAL_SEADRAMON_FQNAME, DMALL_METAL_SEADRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Metal Seadramon
        { DMALL_METAL_TYRANOMON_NAME, DMALL_METAL_TYRANOMON_ID, ALT_DMALL_METAL_TYRANOMON_FQID, ALT_DMALL_METAL_TYRANOMON_FQNAME, DMALL_METAL_TYRANOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Metal Tyranomon
        { DMALL_METAL_TYRANOMON_X_NAME, DMALL_METAL_TYRANOMON_X_ID, ALT_DMALL_METAL_TYRANOMON_X_FQID, ALT_DMALL_METAL_TYRANOMON_X_FQNAME, DMALL_METAL_TYRANOMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Metal Tyranomon X
        { DMALL_MIKEMON_NAME, DMALL_MIKEMON_ID, ALT_DMALL_MIKEMON_FQID, ALT_DMALL_MIKEMON_FQNAME, DMALL_MIKEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Mikemon
        { DMALL_MILLENNIUMON_NAME, DMALL_MILLENNIUMON_ID, ALT_DMALL_MILLENNIUMON_FQID, ALT_DMALL_MILLENNIUMON_FQNAME, DMALL_MILLENNIUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Millenniumon
        { DMALL_MIMICMON_NAME, DMALL_MIMICMON_ID, ALT_DMALL_MIMICMON_FQID, ALT_DMALL_MIMICMON_FQNAME, DMALL_MIMICMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Mimicmon
        { DMALL_MINERVAMON_X_NAME, DMALL_MINERVAMON_X_ID, ALT_DMALL_MINERVAMON_X_FQID, ALT_DMALL_MINERVAMON_X_FQNAME, DMALL_MINERVAMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Minervamon X
        { DMALL_MINOMON_NAME, DMALL_MINOMON_ID, ALT_DMALL_MINOMON_FQID, ALT_DMALL_MINOMON_FQNAME, DMALL_MINOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Minomon
        { DMALL_MOCHIMON_NAME, DMALL_MOCHIMON_ID, ALT_DMALL_MOCHIMON_FQID, ALT_DMALL_MOCHIMON_FQNAME, DMALL_MOCHIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Mochimon
        { DMALL_MOKUMON_NAME, DMALL_MOKUMON_ID, ALT_DMALL_MOKUMON_FQID, ALT_DMALL_MOKUMON_FQNAME, DMALL_MOKUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Mokumon
        { DMALL_MONIMON_NAME, DMALL_MONIMON_ID, ALT_DMALL_MONIMON_FQID, ALT_DMALL_MONIMON_FQNAME, DMALL_MONIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Monimon
        { DMALL_MONOCHROMON_NAME, DMALL_MONOCHROMON_ID, ALT_DMALL_MONOCHROMON_FQID, ALT_DMALL_MONOCHROMON_FQNAME, DMALL_MONOCHROMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Monochromon
        { DMALL_MONOCHROMON_X_NAME, DMALL_MONOCHROMON_X_ID, ALT_DMALL_MONOCHROMON_X_FQID, ALT_DMALL_MONOCHROMON_X_FQNAME, DMALL_MONOCHROMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Monochromon X
        { DMALL_MONZAEMON_NAME, DMALL_MONZAEMON_ID, ALT_DMALL_MONZAEMON_FQID, ALT_DMALL_MONZAEMON_FQNAME, DMALL_MONZAEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Monzaemon
        { DMALL_MONZAEMON_X_NAME, DMALL_MONZAEMON_X_ID, ALT_DMALL_MONZAEMON_X_FQID, ALT_DMALL_MONZAEMON_X_FQNAME, DMALL_MONZAEMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Monzaemon X
        { DMALL_MOONMON_NAME, DMALL_MOONMON_ID, ALT_DMALL_MOONMON_FQID, ALT_DMALL_MOONMON_FQNAME, DMALL_MOONMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Moonmon
        { DMALL_MORI_SHELLMON_NAME, DMALL_MORI_SHELLMON_ID, ALT_DMALL_MORI_SHELLMON_FQID, ALT_DMALL_MORI_SHELLMON_FQNAME, DMALL_MORI_SHELLMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Mori Shellmon
        { DMALL_MORPHOMON_NAME, DMALL_MORPHOMON_ID, ALT_DMALL_MORPHOMON_FQID, ALT_DMALL_MORPHOMON_FQNAME, DMALL_MORPHOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Morphomon
        { DMALL_MUCHOMON_NAME, DMALL_MUCHOMON_ID, ALT_DMALL_MUCHOMON_FQID, ALT_DMALL_MUCHOMON_FQNAME, DMALL_MUCHOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Muchomon
        { DMALL_MUGENDRAMON_NAME, DMALL_MUGENDRAMON_ID, ALT_DMALL_MUGENDRAMON_FQID, ALT_DMALL_MUGENDRAMON_FQNAME, DMALL_MUGENDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Mugendramon
        { DMALL_MUSHMON_NAME, DMALL_MUSHMON_ID, ALT_DMALL_MUSHMON_FQID, ALT_DMALL_MUSHMON_FQNAME, DMALL_MUSHMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Mushmon
        { DMALL_NANOMON_NAME, DMALL_NANOMON_ID, ALT_DMALL_NANOMON_FQID, ALT_DMALL_NANOMON_FQNAME, DMALL_NANOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Nanomon
        { DMALL_NEFERTIMON_X_NAME, DMALL_NEFERTIMON_X_ID, ALT_DMALL_NEFERTIMON_X_FQID, ALT_DMALL_NEFERTIMON_X_FQNAME, DMALL_NEFERTIMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Nefertimon X
        { DMALL_NEO_DEVIMON_NAME, DMALL_NEO_DEVIMON_ID, ALT_DMALL_NEO_DEVIMON_FQID, ALT_DMALL_NEO_DEVIMON_FQNAME, DMALL_NEO_DEVIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Neo Devimon
        { DMALL_NISE_DRIMOGEMON_NAME, DMALL_NISE_DRIMOGEMON_ID, ALT_DMALL_NISE_DRIMOGEMON_FQID, ALT_DMALL_NISE_DRIMOGEMON_FQNAME, DMALL_NISE_DRIMOGEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Nise Drimogemon
        { DMALL_NOBLE_PUMPMON_NAME, DMALL_NOBLE_PUMPMON_ID, ALT_DMALL_NOBLE_PUMPMON_FQID, ALT_DMALL_NOBLE_PUMPMON_FQNAME, DMALL_NOBLE_PUMPMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Noble Pumpmon
        { DMALL_NUMEMON_NAME, DMALL_NUMEMON_ID, ALT_DMALL_NUMEMON_FQID, ALT_DMALL_NUMEMON_FQNAME, DMALL_NUMEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Numemon
        { DMALL_NUMEMON_X_NAME, DMALL_NUMEMON_X_ID, ALT_DMALL_NUMEMON_X_FQID, ALT_DMALL_NUMEMON_X_FQNAME, DMALL_NUMEMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Numemon X
        { DMALL_NYAROMON_NAME, DMALL_NYAROMON_ID, ALT_DMALL_NYAROMON_FQID, ALT_DMALL_NYAROMON_FQNAME, DMALL_NYAROMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Nyaromon
        { DMALL_NYOKIMON_NAME, DMALL_NYOKIMON_ID, ALT_DMALL_NYOKIMON_FQID, ALT_DMALL_NYOKIMON_FQNAME, DMALL_NYOKIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Nyokimon
        { DMALL_OFANIMON_CORE_NAME, DMALL_OFANIMON_CORE_ID, ALT_DMALL_OFANIMON_CORE_FQID, ALT_DMALL_OFANIMON_CORE_FQNAME, DMALL_OFANIMON_CORE_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Ofanimon Core
        { DMALL_OFANIMON_FALLDOWN_MODE_NAME, DMALL_OFANIMON_FALLDOWN_MODE_ID, ALT_DMALL_OFANIMON_FALLDOWN_MODE_FQID, ALT_DMALL_OFANIMON_FALLDOWN_MODE_FQNAME, DMALL_OFANIMON_FALLDOWN_MODE_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Ofanimon Falldown Mode
        { DMALL_OGREMON_NAME, DMALL_OGREMON_ID, ALT_DMALL_OGREMON_FQID, ALT_DMALL_OGREMON_FQNAME, DMALL_OGREMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Ogremon
        { DMALL_OGREMON_X_NAME, DMALL_OGREMON_X_ID, ALT_DMALL_OGREMON_X_FQID, ALT_DMALL_OGREMON_X_FQNAME, DMALL_OGREMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Ogremon X
        { DMALL_OGUDOMON_NAME, DMALL_OGUDOMON_ID, ALT_DMALL_OGUDOMON_FQID, ALT_DMALL_OGUDOMON_FQNAME, DMALL_OGUDOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Ogudomon
        { DMALL_OGUDOMON_X_NAME, DMALL_OGUDOMON_X_ID, ALT_DMALL_OGUDOMON_X_FQID, ALT_DMALL_OGUDOMON_X_FQNAME, DMALL_OGUDOMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Ogudomon X
        { DMALL_OKUWAMON_NAME, DMALL_OKUWAMON_ID, ALT_DMALL_OKUWAMON_FQID, ALT_DMALL_OKUWAMON_FQNAME, DMALL_OKUWAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Okuwamon
        { DMALL_OKUWAMON_X_NAME, DMALL_OKUWAMON_X_ID, ALT_DMALL_OKUWAMON_X_FQID, ALT_DMALL_OKUWAMON_X_FQNAME, DMALL_OKUWAMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Okuwamon X
        { DMALL_OMEGAMON_ALTER_S_NAME, DMALL_OMEGAMON_ALTER_S_ID, ALT_DMALL_OMEGAMON_ALTER_S_FQID, ALT_DMALL_OMEGAMON_ALTER_S_FQNAME, DMALL_OMEGAMON_ALTER_S_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Omegamon Alter S
        { DMALL_OMEGAMON_NAME, DMALL_OMEGAMON_ID, ALT_DMALL_OMEGAMON_FQID, ALT_DMALL_OMEGAMON_FQNAME, DMALL_OMEGAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Omegamon
        { DMALL_OMEGAMON_X_NAME, DMALL_OMEGAMON_X_ID, ALT_DMALL_OMEGAMON_X_FQID, ALT_DMALL_OMEGAMON_X_FQNAME, DMALL_OMEGAMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Omegamon X
        { DMALL_OMEGAMON_ZWART_NAME, DMALL_OMEGAMON_ZWART_ID, ALT_DMALL_OMEGAMON_ZWART_FQID, ALT_DMALL_OMEGAMON_ZWART_FQNAME, DMALL_OMEGAMON_ZWART_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Omegamon Zwart
        { DMALL_OMEGA_SHOUTMON_X_NAME, DMALL_OMEGA_SHOUTMON_X_ID, ALT_DMALL_OMEGA_SHOUTMON_X_FQID, ALT_DMALL_OMEGA_SHOUTMON_X_FQNAME, DMALL_OMEGA_SHOUTMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Omega Shoutmon X
        { DMALL_OMEKAMON_NAME, DMALL_OMEKAMON_ID, ALT_DMALL_OMEKAMON_FQID, ALT_DMALL_OMEKAMON_FQNAME, DMALL_OMEKAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Omekamon
        { DMALL_OPHANIMON_NAME, DMALL_OPHANIMON_ID, ALT_DMALL_OPHANIMON_FQID, ALT_DMALL_OPHANIMON_FQNAME, DMALL_OPHANIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Ophanimon
        { DMALL_OPHANIMON_X_NAME, DMALL_OPHANIMON_X_ID, ALT_DMALL_OPHANIMON_X_FQID, ALT_DMALL_OPHANIMON_X_FQNAME, DMALL_OPHANIMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Ophanimon X
        { DMALL_ORDINEMON_NAME, DMALL_ORDINEMON_ID, ALT_DMALL_ORDINEMON_FQID, ALT_DMALL_ORDINEMON_FQNAME, DMALL_ORDINEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Ordinemon
        { DMALL_OROCHIMON_NAME, DMALL_OROCHIMON_ID, ALT_DMALL_OROCHIMON_FQID, ALT_DMALL_OROCHIMON_FQNAME, DMALL_OROCHIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Orochimon
        { DMALL_OTAMAMON_NAME, DMALL_OTAMAMON_ID, ALT_DMALL_OTAMAMON_FQID, ALT_DMALL_OTAMAMON_FQNAME, DMALL_OTAMAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Otamamon
        { DMALL_OTAMAMON_RED_NAME, DMALL_OTAMAMON_RED_ID, ALT_DMALL_OTAMAMON_RED_FQID, ALT_DMALL_OTAMAMON_RED_FQNAME, DMALL_OTAMAMON_RED_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Otamamon (Red)
        { DMALL_OTAMAMON_X_NAME, DMALL_OTAMAMON_X_ID, ALT_DMALL_OTAMAMON_X_FQID, ALT_DMALL_OTAMAMON_X_FQNAME, DMALL_OTAMAMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Otamamon X
        { DMALL_OURYUMON_NAME, DMALL_OURYUMON_ID, ALT_DMALL_OURYUMON_FQID, ALT_DMALL_OURYUMON_FQNAME, DMALL_OURYUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Ouryumon
        { DMALL_PAFUMON_NAME, DMALL_PAFUMON_ID, ALT_DMALL_PAFUMON_FQID, ALT_DMALL_PAFUMON_FQNAME, DMALL_PAFUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Pafumon
        { DMALL_PAGUMON_NAME, DMALL_PAGUMON_ID, ALT_DMALL_PAGUMON_FQID, ALT_DMALL_PAGUMON_FQNAME, DMALL_PAGUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Pagumon
        { DMALL_PAILDRAMON_NAME, DMALL_PAILDRAMON_ID, ALT_DMALL_PAILDRAMON_FQID, ALT_DMALL_PAILDRAMON_FQNAME, DMALL_PAILDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Paildramon
        { DMALL_PALEDRAMON_NAME, DMALL_PALEDRAMON_ID, ALT_DMALL_PALEDRAMON_FQID, ALT_DMALL_PALEDRAMON_FQNAME, DMALL_PALEDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Paledramon
        { DMALL_PALMON_NAME, DMALL_PALMON_ID, ALT_DMALL_PALMON_FQID, ALT_DMALL_PALMON_FQNAME, DMALL_PALMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Palmon
        { DMALL_PALMON_X_NAME, DMALL_PALMON_X_ID, ALT_DMALL_PALMON_X_FQID, ALT_DMALL_PALMON_X_FQNAME, DMALL_PALMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Palmon X
        { DMALL_PANDAMON_NAME, DMALL_PANDAMON_ID, ALT_DMALL_PANDAMON_FQID, ALT_DMALL_PANDAMON_FQNAME, DMALL_PANDAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Pandamon
        { DMALL_PANJYAMON_NAME, DMALL_PANJYAMON_ID, ALT_DMALL_PANJYAMON_FQID, ALT_DMALL_PANJYAMON_FQNAME, DMALL_PANJYAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Panjyamon
        { DMALL_PANJYAMON_X_NAME, DMALL_PANJYAMON_X_ID, ALT_DMALL_PANJYAMON_X_FQID, ALT_DMALL_PANJYAMON_X_FQNAME, DMALL_PANJYAMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Panjyamon X
        { DMALL_PAOMON_NAME, DMALL_PAOMON_ID, ALT_DMALL_PAOMON_FQID, ALT_DMALL_PAOMON_FQNAME, DMALL_PAOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Paomon
        { DMALL_PARASAURMON_NAME, DMALL_PARASAURMON_ID, ALT_DMALL_PARASAURMON_FQID, ALT_DMALL_PARASAURMON_FQNAME, DMALL_PARASAURMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Parasaurmon
        { DMALL_PEGASMON_X_NAME, DMALL_PEGASMON_X_ID, ALT_DMALL_PEGASMON_X_FQID, ALT_DMALL_PEGASMON_X_FQNAME, DMALL_PEGASMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Pegasmon X
        { DMALL_PENMON_NAME, DMALL_PENMON_ID, ALT_DMALL_PENMON_FQID, ALT_DMALL_PENMON_FQNAME, DMALL_PENMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Penmon
        { DMALL_PETIMERAMON_NAME, DMALL_PETIMERAMON_ID, ALT_DMALL_PETIMERAMON_FQID, ALT_DMALL_PETIMERAMON_FQNAME, DMALL_PETIMERAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for PetiMeramon
        { DMALL_PETITMAMON_NAME, DMALL_PETITMAMON_ID, ALT_DMALL_PETITMAMON_FQID, ALT_DMALL_PETITMAMON_FQNAME, DMALL_PETITMAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for PetitMamon
        { DMALL_PETITMON_NAME, DMALL_PETITMON_ID, ALT_DMALL_PETITMON_FQID, ALT_DMALL_PETITMON_FQNAME, DMALL_PETITMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Petitmon
        { DMALL_PHANTOMON_NAME, DMALL_PHANTOMON_ID, ALT_DMALL_PHANTOMON_FQID, ALT_DMALL_PHANTOMON_FQNAME, DMALL_PHANTOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Phantomon
        { DMALL_PHASCOMON_NAME, DMALL_PHASCOMON_ID, ALT_DMALL_PHASCOMON_FQID, ALT_DMALL_PHASCOMON_FQNAME, DMALL_PHASCOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Phascomon
        { DMALL_PICCOLOMON_NAME, DMALL_PICCOLOMON_ID, ALT_DMALL_PICCOLOMON_FQID, ALT_DMALL_PICCOLOMON_FQNAME, DMALL_PICCOLOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Piccolomon
        { DMALL_PICKMON_NAME, DMALL_PICKMON_ID, ALT_DMALL_PICKMON_FQID, ALT_DMALL_PICKMON_FQNAME, DMALL_PICKMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Pickmon
        { DMALL_PICO_DEVIMON_NAME, DMALL_PICO_DEVIMON_ID, ALT_DMALL_PICO_DEVIMON_FQID, ALT_DMALL_PICO_DEVIMON_FQNAME, DMALL_PICO_DEVIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Pico Devimon
        { DMALL_PIDMON_NAME, DMALL_PIDMON_ID, ALT_DMALL_PIDMON_FQID, ALT_DMALL_PIDMON_FQNAME, DMALL_PIDMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Pidmon
        { DMALL_PIEMON_NAME, DMALL_PIEMON_ID, ALT_DMALL_PIEMON_FQID, ALT_DMALL_PIEMON_FQNAME, DMALL_PIEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Piemon
        { DMALL_PINOCHIMON_NAME, DMALL_PINOCHIMON_ID, ALT_DMALL_PINOCHIMON_FQID, ALT_DMALL_PINOCHIMON_FQNAME, DMALL_PINOCHIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Pinochimon
        { DMALL_PIPIMON_NAME, DMALL_PIPIMON_ID, ALT_DMALL_PIPIMON_FQID, ALT_DMALL_PIPIMON_FQNAME, DMALL_PIPIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Pipimon
        { DMALL_PIRANIMON_NAME, DMALL_PIRANIMON_ID, ALT_DMALL_PIRANIMON_FQID, ALT_DMALL_PIRANIMON_FQNAME, DMALL_PIRANIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Piranimon
        { DMALL_PITCHMON_NAME, DMALL_PITCHMON_ID, ALT_DMALL_PITCHMON_FQID, ALT_DMALL_PITCHMON_FQNAME, DMALL_PITCHMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Pitchmon
        { DMALL_PIYOMON_NAME, DMALL_PIYOMON_ID, ALT_DMALL_PIYOMON_FQID, ALT_DMALL_PIYOMON_FQNAME, DMALL_PIYOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Piyomon
        { DMALL_PLATINUM_NUMEMON_NAME, DMALL_PLATINUM_NUMEMON_ID, ALT_DMALL_PLATINUM_NUMEMON_FQID, ALT_DMALL_PLATINUM_NUMEMON_FQNAME, DMALL_PLATINUM_NUMEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Platinum Numemon
        { DMALL_PLATINUM_SCUMON_NAME, DMALL_PLATINUM_SCUMON_ID, ALT_DMALL_PLATINUM_SCUMON_FQID, ALT_DMALL_PLATINUM_SCUMON_FQNAME, DMALL_PLATINUM_SCUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Platinum Scumon
        { DMALL_PLESIOMON_NAME, DMALL_PLESIOMON_ID, ALT_DMALL_PLESIOMON_FQID, ALT_DMALL_PLESIOMON_FQNAME, DMALL_PLESIOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Plesiomon
        { DMALL_PLESIOMON_X_NAME, DMALL_PLESIOMON_X_ID, ALT_DMALL_PLESIOMON_X_FQID, ALT_DMALL_PLESIOMON_X_FQNAME, DMALL_PLESIOMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Plesiomon X
        { DMALL_PLOTMON_NAME, DMALL_PLOTMON_ID, ALT_DMALL_PLOTMON_FQID, ALT_DMALL_PLOTMON_FQNAME, DMALL_PLOTMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Plotmon
        { DMALL_PLOTMON_X_NAME, DMALL_PLOTMON_X_ID, ALT_DMALL_PLOTMON_X_FQID, ALT_DMALL_PLOTMON_X_FQNAME, DMALL_PLOTMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Plotmon X
        { DMALL_POKOMON_NAME, DMALL_POKOMON_ID, ALT_DMALL_POKOMON_FQID, ALT_DMALL_POKOMON_FQNAME, DMALL_POKOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Pokomon
        { DMALL_POPOMON_NAME, DMALL_POPOMON_ID, ALT_DMALL_POPOMON_FQID, ALT_DMALL_POPOMON_FQNAME, DMALL_POPOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Popomon
        { DMALL_PORCUPAMON_NAME, DMALL_PORCUPAMON_ID, ALT_DMALL_PORCUPAMON_FQID, ALT_DMALL_PORCUPAMON_FQNAME, DMALL_PORCUPAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Porcupamon
        { DMALL_POROMON_NAME, DMALL_POROMON_ID, ALT_DMALL_POROMON_FQID, ALT_DMALL_POROMON_FQNAME, DMALL_POROMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Poromon
        { DMALL_PRINCE_MAMEMON_NAME, DMALL_PRINCE_MAMEMON_ID, ALT_DMALL_PRINCE_MAMEMON_FQID, ALT_DMALL_PRINCE_MAMEMON_FQNAME, DMALL_PRINCE_MAMEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Prince Mamemon
        { DMALL_PRINCE_MAMEMON_X_NAME, DMALL_PRINCE_MAMEMON_X_ID, ALT_DMALL_PRINCE_MAMEMON_X_FQID, ALT_DMALL_PRINCE_MAMEMON_X_FQNAME, DMALL_PRINCE_MAMEMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Prince Mamemon X
        { DMALL_PTERANOMON_X_NAME, DMALL_PTERANOMON_X_ID, ALT_DMALL_PTERANOMON_X_FQID, ALT_DMALL_PTERANOMON_X_FQNAME, DMALL_PTERANOMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Pteranomon X
        { DMALL_PUKAMON_NAME, DMALL_PUKAMON_ID, ALT_DMALL_PUKAMON_FQID, ALT_DMALL_PUKAMON_FQNAME, DMALL_PUKAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Pukamon
        { DMALL_PUKUMON_NAME, DMALL_PUKUMON_ID, ALT_DMALL_PUKUMON_FQID, ALT_DMALL_PUKUMON_FQNAME, DMALL_PUKUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Pukumon
        { DMALL_PULSEMON_NAME, DMALL_PULSEMON_ID, ALT_DMALL_PULSEMON_FQID, ALT_DMALL_PULSEMON_FQNAME, DMALL_PULSEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Pulsemon
        { DMALL_PUMPMON_NAME, DMALL_PUMPMON_ID, ALT_DMALL_PUMPMON_FQID, ALT_DMALL_PUMPMON_FQNAME, DMALL_PUMPMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Pumpmon
        { DMALL_PUPUMON_NAME, DMALL_PUPUMON_ID, ALT_DMALL_PUPUMON_FQID, ALT_DMALL_PUPUMON_FQNAME, DMALL_PUPUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Pupumon
        { DMALL_PUROROMON_NAME, DMALL_PUROROMON_ID, ALT_DMALL_PUROROMON_FQID, ALT_DMALL_PUROROMON_FQNAME, DMALL_PUROROMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Puroromon
        { DMALL_PURURUMON_NAME, DMALL_PURURUMON_ID, ALT_DMALL_PURURUMON_FQID, ALT_DMALL_PURURUMON_FQNAME, DMALL_PURURUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Pururumon
        { DMALL_PUSUMON_NAME, DMALL_PUSUMON_ID, ALT_DMALL_PUSUMON_FQID, ALT_DMALL_PUSUMON_FQNAME, DMALL_PUSUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Pusumon
        { DMALL_PUSURIMON_NAME, DMALL_PUSURIMON_ID, ALT_DMALL_PUSURIMON_FQID, ALT_DMALL_PUSURIMON_FQNAME, DMALL_PUSURIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Pusurimon
        { DMALL_PUTTIMON_NAME, DMALL_PUTTIMON_ID, ALT_DMALL_PUTTIMON_FQID, ALT_DMALL_PUTTIMON_FQNAME, DMALL_PUTTIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Puttimon
        { DMALL_PUYOMON_NAME, DMALL_PUYOMON_ID, ALT_DMALL_PUYOMON_FQID, ALT_DMALL_PUYOMON_FQNAME, DMALL_PUYOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Puyomon
        { DMALL_PYOCOMON_NAME, DMALL_PYOCOMON_ID, ALT_DMALL_PYOCOMON_FQID, ALT_DMALL_PYOCOMON_FQNAME, DMALL_PYOCOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Pyocomon
        { DMALL_PYONMON_NAME, DMALL_PYONMON_ID, ALT_DMALL_PYONMON_FQID, ALT_DMALL_PYONMON_FQNAME, DMALL_PYONMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Pyonmon
        { DMALL_RAFFLESIMON_NAME, DMALL_RAFFLESIMON_ID, ALT_DMALL_RAFFLESIMON_FQID, ALT_DMALL_RAFFLESIMON_FQNAME, DMALL_RAFFLESIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Rafflesimon
        { DMALL_RAGNA_LORDMON_NAME, DMALL_RAGNA_LORDMON_ID, ALT_DMALL_RAGNA_LORDMON_FQID, ALT_DMALL_RAGNA_LORDMON_FQNAME, DMALL_RAGNA_LORDMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Ragna Lordmon
        { DMALL_RAGUELMON_NAME, DMALL_RAGUELMON_ID, ALT_DMALL_RAGUELMON_FQID, ALT_DMALL_RAGUELMON_FQNAME, DMALL_RAGUELMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Raguelmon
        { DMALL_RAIDENMON_NAME, DMALL_RAIDENMON_ID, ALT_DMALL_RAIDENMON_FQID, ALT_DMALL_RAIDENMON_FQNAME, DMALL_RAIDENMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Raidenmon
        { DMALL_RAIHIMON_NAME, DMALL_RAIHIMON_ID, ALT_DMALL_RAIHIMON_FQID, ALT_DMALL_RAIHIMON_FQNAME, DMALL_RAIHIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Raihimon
        { DMALL_RAIJI_LUDOMON_NAME, DMALL_RAIJI_LUDOMON_ID, ALT_DMALL_RAIJI_LUDOMON_FQID, ALT_DMALL_RAIJI_LUDOMON_FQNAME, DMALL_RAIJI_LUDOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Raiji Ludomon
        { DMALL_RAPIDMON_ARMOR_NAME, DMALL_RAPIDMON_ARMOR_ID, ALT_DMALL_RAPIDMON_ARMOR_FQID, ALT_DMALL_RAPIDMON_ARMOR_FQNAME, DMALL_RAPIDMON_ARMOR_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Rapidmon (Armor)
        { DMALL_RAPIDMON_NAME, DMALL_RAPIDMON_ID, ALT_DMALL_RAPIDMON_FQID, ALT_DMALL_RAPIDMON_FQNAME, DMALL_RAPIDMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Rapidmon
        { DMALL_RAPIDMON_X_NAME, DMALL_RAPIDMON_X_ID, ALT_DMALL_RAPIDMON_X_FQID, ALT_DMALL_RAPIDMON_X_FQNAME, DMALL_RAPIDMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Rapidmon X
        { DMALL_RAPTORDRAMON_NAME, DMALL_RAPTORDRAMON_ID, ALT_DMALL_RAPTORDRAMON_FQID, ALT_DMALL_RAPTORDRAMON_FQNAME, DMALL_RAPTORDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Raptordramon
        { DMALL_RASENMON_FURY_MODE_NAME, DMALL_RASENMON_FURY_MODE_ID, ALT_DMALL_RASENMON_FURY_MODE_FQID, ALT_DMALL_RASENMON_FURY_MODE_FQNAME, DMALL_RASENMON_FURY_MODE_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Rasenmon Fury Mode
        { DMALL_RASENMON_NAME, DMALL_RASENMON_ID, ALT_DMALL_RASENMON_FQID, ALT_DMALL_RASENMON_FQNAME, DMALL_RASENMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Rasenmon
        { DMALL_RASIELMON_NAME, DMALL_RASIELMON_ID, ALT_DMALL_RASIELMON_FQID, ALT_DMALL_RASIELMON_FQNAME, DMALL_RASIELMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Rasielmon
        { DMALL_REBELLIMON_NAME, DMALL_REBELLIMON_ID, ALT_DMALL_REBELLIMON_FQID, ALT_DMALL_REBELLIMON_FQNAME, DMALL_REBELLIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Rebellimon
        { DMALL_RED_V_DRAMON_NAME, DMALL_RED_V_DRAMON_ID, ALT_DMALL_RED_V_DRAMON_FQID, ALT_DMALL_RED_V_DRAMON_FQNAME, DMALL_RED_V_DRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Red V-dramon
        { DMALL_RED_VEGIMON_NAME, DMALL_RED_VEGIMON_ID, ALT_DMALL_RED_VEGIMON_FQID, ALT_DMALL_RED_VEGIMON_FQNAME, DMALL_RED_VEGIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Red Vegimon
        { DMALL_REGALECUSMON_NAME, DMALL_REGALECUSMON_ID, ALT_DMALL_REGALECUSMON_FQID, ALT_DMALL_REGALECUSMON_FQNAME, DMALL_REGALECUSMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Regalecusmon
        { DMALL_RELEMON_NAME, DMALL_RELEMON_ID, ALT_DMALL_RELEMON_FQID, ALT_DMALL_RELEMON_FQNAME, DMALL_RELEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Relemon
        { DMALL_RENAMON_NAME, DMALL_RENAMON_ID, ALT_DMALL_RENAMON_FQID, ALT_DMALL_RENAMON_FQNAME, DMALL_RENAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Renamon
        { DMALL_RENAMON_X_NAME, DMALL_RENAMON_X_ID, ALT_DMALL_RENAMON_X_FQID, ALT_DMALL_RENAMON_X_FQNAME, DMALL_RENAMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Renamon X
        { DMALL_REPPAMON_NAME, DMALL_REPPAMON_ID, ALT_DMALL_REPPAMON_FQID, ALT_DMALL_REPPAMON_FQNAME, DMALL_REPPAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Reppamon
        { DMALL_RHINOMON_NAME, DMALL_RHINOMON_ID, ALT_DMALL_RHINOMON_FQID, ALT_DMALL_RHINOMON_FQNAME, DMALL_RHINOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Rhinomon
        { DMALL_RHINOMON_X_NAME, DMALL_RHINOMON_X_ID, ALT_DMALL_RHINOMON_X_FQID, ALT_DMALL_RHINOMON_X_FQNAME, DMALL_RHINOMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Rhinomon X
        { DMALL_RIZE_GREYMON_NAME, DMALL_RIZE_GREYMON_ID, ALT_DMALL_RIZE_GREYMON_FQID, ALT_DMALL_RIZE_GREYMON_FQNAME, DMALL_RIZE_GREYMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Rize Greymon
        { DMALL_RIZEGREYMON_X_NAME, DMALL_RIZEGREYMON_X_ID, ALT_DMALL_RIZEGREYMON_X_FQID, ALT_DMALL_RIZEGREYMON_X_FQNAME, DMALL_RIZEGREYMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for RizeGreymon X
        { DMALL_ROSEMON_BURST_MODE_NAME, DMALL_ROSEMON_BURST_MODE_ID, ALT_DMALL_ROSEMON_BURST_MODE_FQID, ALT_DMALL_ROSEMON_BURST_MODE_FQNAME, DMALL_ROSEMON_BURST_MODE_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Rosemon Burst Mode
        { DMALL_ROSEMON_NAME, DMALL_ROSEMON_ID, ALT_DMALL_ROSEMON_FQID, ALT_DMALL_ROSEMON_FQNAME, DMALL_ROSEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Rosemon
        { DMALL_ROSEMON_X_NAME, DMALL_ROSEMON_X_ID, ALT_DMALL_ROSEMON_X_FQID, ALT_DMALL_ROSEMON_X_FQNAME, DMALL_ROSEMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Rosemon X
        { DMALL_RUKAMON_NAME, DMALL_RUKAMON_ID, ALT_DMALL_RUKAMON_FQID, ALT_DMALL_RUKAMON_FQNAME, DMALL_RUKAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Rukamon
        { DMALL_RUST_TYRANNOMON_NAME, DMALL_RUST_TYRANNOMON_ID, ALT_DMALL_RUST_TYRANNOMON_FQID, ALT_DMALL_RUST_TYRANNOMON_FQNAME, DMALL_RUST_TYRANNOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Rust Tyrannomon
        { DMALL_RYUDAMON_NAME, DMALL_RYUDAMON_ID, ALT_DMALL_RYUDAMON_FQID, ALT_DMALL_RYUDAMON_FQNAME, DMALL_RYUDAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Ryudamon
        { DMALL_SABERDRAMON_NAME, DMALL_SABERDRAMON_ID, ALT_DMALL_SABERDRAMON_FQID, ALT_DMALL_SABERDRAMON_FQNAME, DMALL_SABERDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Saberdramon
        { DMALL_SABER_LEOMON_NAME, DMALL_SABER_LEOMON_ID, ALT_DMALL_SABER_LEOMON_FQID, ALT_DMALL_SABER_LEOMON_FQNAME, DMALL_SABER_LEOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Saber Leomon
        { DMALL_SAGOMON_NAME, DMALL_SAGOMON_ID, ALT_DMALL_SAGOMON_FQID, ALT_DMALL_SAGOMON_FQNAME, DMALL_SAGOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Sagomon
        { DMALL_SAINT_GALGOMON_NAME, DMALL_SAINT_GALGOMON_ID, ALT_DMALL_SAINT_GALGOMON_FQID, ALT_DMALL_SAINT_GALGOMON_FQNAME, DMALL_SAINT_GALGOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Saint Galgomon
        { DMALL_SAKUYAMON_NAME, DMALL_SAKUYAMON_ID, ALT_DMALL_SAKUYAMON_FQID, ALT_DMALL_SAKUYAMON_FQNAME, DMALL_SAKUYAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Sakuyamon
        { DMALL_SAKUYAMON_X_NAME, DMALL_SAKUYAMON_X_ID, ALT_DMALL_SAKUYAMON_X_FQID, ALT_DMALL_SAKUYAMON_X_FQNAME, DMALL_SAKUYAMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Sakuyamon X
        { DMALL_SAND_YANMAMON_NAME, DMALL_SAND_YANMAMON_ID, ALT_DMALL_SAND_YANMAMON_FQID, ALT_DMALL_SAND_YANMAMON_FQNAME, DMALL_SAND_YANMAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Sand Yanmamon
        { DMALL_SANGLOUPMON_NAME, DMALL_SANGLOUPMON_ID, ALT_DMALL_SANGLOUPMON_FQID, ALT_DMALL_SANGLOUPMON_FQNAME, DMALL_SANGLOUPMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Sangloupmon
        { DMALL_SANGOMON_NAME, DMALL_SANGOMON_ID, ALT_DMALL_SANGOMON_FQID, ALT_DMALL_SANGOMON_FQNAME, DMALL_SANGOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Sangomon
        { DMALL_SAVIORHACKMON_NAME, DMALL_SAVIORHACKMON_ID, ALT_DMALL_SAVIORHACKMON_FQID, ALT_DMALL_SAVIORHACKMON_FQNAME, DMALL_SAVIORHACKMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for SaviorHackmon
        { DMALL_SCORPIOMON_NAME, DMALL_SCORPIOMON_ID, ALT_DMALL_SCORPIOMON_FQID, ALT_DMALL_SCORPIOMON_FQNAME, DMALL_SCORPIOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Scorpiomon
        { DMALL_SCUMON_NAME, DMALL_SCUMON_ID, ALT_DMALL_SCUMON_FQID, ALT_DMALL_SCUMON_FQNAME, DMALL_SCUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Scumon
        { DMALL_SEADRAMON_NAME, DMALL_SEADRAMON_ID, ALT_DMALL_SEADRAMON_FQID, ALT_DMALL_SEADRAMON_FQNAME, DMALL_SEADRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Seadramon
        { DMALL_SEADRAMON_X_NAME, DMALL_SEADRAMON_X_ID, ALT_DMALL_SEADRAMON_X_FQID, ALT_DMALL_SEADRAMON_X_FQNAME, DMALL_SEADRAMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Seadramon X
        { DMALL_SERAPHIMON_NAME, DMALL_SERAPHIMON_ID, ALT_DMALL_SERAPHIMON_FQID, ALT_DMALL_SERAPHIMON_FQNAME, DMALL_SERAPHIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Seraphimon
        { DMALL_SHADRAMON_NAME, DMALL_SHADRAMON_ID, ALT_DMALL_SHADRAMON_FQID, ALT_DMALL_SHADRAMON_FQNAME, DMALL_SHADRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Shadramon
        { DMALL_SHAKOMON_NAME, DMALL_SHAKOMON_ID, ALT_DMALL_SHAKOMON_FQID, ALT_DMALL_SHAKOMON_FQNAME, DMALL_SHAKOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Shakomon
        { DMALL_SHAKOMON_X_NAME, DMALL_SHAKOMON_X_ID, ALT_DMALL_SHAKOMON_X_FQID, ALT_DMALL_SHAKOMON_X_FQNAME, DMALL_SHAKOMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Shakomon X
        { DMALL_SHAWUJINMON_NAME, DMALL_SHAWUJINMON_ID, ALT_DMALL_SHAWUJINMON_FQID, ALT_DMALL_SHAWUJINMON_FQNAME, DMALL_SHAWUJINMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Shawujinmon
        { DMALL_SHEEPMON_NAME, DMALL_SHEEPMON_ID, ALT_DMALL_SHEEPMON_FQID, ALT_DMALL_SHEEPMON_FQNAME, DMALL_SHEEPMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Sheepmon
        { DMALL_SHELLMON_NAME, DMALL_SHELLMON_ID, ALT_DMALL_SHELLMON_FQID, ALT_DMALL_SHELLMON_FQNAME, DMALL_SHELLMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Shellmon
        { DMALL_SHIMA_UNIMON_NAME, DMALL_SHIMA_UNIMON_ID, ALT_DMALL_SHIMA_UNIMON_FQID, ALT_DMALL_SHIMA_UNIMON_FQNAME, DMALL_SHIMA_UNIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Shima Unimon
        { DMALL_SHIN_MONZAEMON_NAME, DMALL_SHIN_MONZAEMON_ID, ALT_DMALL_SHIN_MONZAEMON_FQID, ALT_DMALL_SHIN_MONZAEMON_FQNAME, DMALL_SHIN_MONZAEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Shin Monzaemon
        { DMALL_SHOOTMON_NAME, DMALL_SHOOTMON_ID, ALT_DMALL_SHOOTMON_FQID, ALT_DMALL_SHOOTMON_FQNAME, DMALL_SHOOTMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Shootmon
        { DMALL_SIESAMON_X_NAME, DMALL_SIESAMON_X_ID, ALT_DMALL_SIESAMON_X_FQID, ALT_DMALL_SIESAMON_X_FQNAME, DMALL_SIESAMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Siesamon X
        { DMALL_SIRENMON_NAME, DMALL_SIRENMON_ID, ALT_DMALL_SIRENMON_FQID, ALT_DMALL_SIRENMON_FQNAME, DMALL_SIRENMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Sirenmon
        { DMALL_SISTERMON_BLANC_NAME, DMALL_SISTERMON_BLANC_ID, ALT_DMALL_SISTERMON_BLANC_FQID, ALT_DMALL_SISTERMON_BLANC_FQNAME, DMALL_SISTERMON_BLANC_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Sistermon Blanc
        { DMALL_SKULL_BALUCHIMON_NAME, DMALL_SKULL_BALUCHIMON_ID, ALT_DMALL_SKULL_BALUCHIMON_FQID, ALT_DMALL_SKULL_BALUCHIMON_FQNAME, DMALL_SKULL_BALUCHIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Skull Baluchimon
        { DMALL_SKULL_GREYMON_NAME, DMALL_SKULL_GREYMON_ID, ALT_DMALL_SKULL_GREYMON_FQID, ALT_DMALL_SKULL_GREYMON_FQNAME, DMALL_SKULL_GREYMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Skull Greymon
        { DMALL_SKULLKNIGHTMON_NAME, DMALL_SKULLKNIGHTMON_ID, ALT_DMALL_SKULLKNIGHTMON_FQID, ALT_DMALL_SKULLKNIGHTMON_FQNAME, DMALL_SKULLKNIGHTMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for SkullKnightmon
        { DMALL_SKULL_MAMMON_NAME, DMALL_SKULL_MAMMON_ID, ALT_DMALL_SKULL_MAMMON_FQID, ALT_DMALL_SKULL_MAMMON_FQNAME, DMALL_SKULL_MAMMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Skull Mammon
        { DMALL_SKULL_MAMMON_X_NAME, DMALL_SKULL_MAMMON_X_ID, ALT_DMALL_SKULL_MAMMON_X_FQID, ALT_DMALL_SKULL_MAMMON_X_FQNAME, DMALL_SKULL_MAMMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Skull Mammon X
        { DMALL_SLEIPMON_X_NAME, DMALL_SLEIPMON_X_ID, ALT_DMALL_SLEIPMON_X_FQID, ALT_DMALL_SLEIPMON_X_FQNAME, DMALL_SLEIPMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Sleipmon X
        { DMALL_SOLARMON_NAME, DMALL_SOLARMON_ID, ALT_DMALL_SOLARMON_FQID, ALT_DMALL_SOLARMON_FQNAME, DMALL_SOLARMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Solarmon
        { DMALL_SORCERYMON_NAME, DMALL_SORCERYMON_ID, ALT_DMALL_SORCERYMON_FQID, ALT_DMALL_SORCERYMON_FQNAME, DMALL_SORCERYMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Sorcerymon
        { DMALL_SOULMON_NAME, DMALL_SOULMON_ID, ALT_DMALL_SOULMON_FQID, ALT_DMALL_SOULMON_FQNAME, DMALL_SOULMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Soulmon
        { DMALL_STARMON_NAME, DMALL_STARMON_ID, ALT_DMALL_STARMON_FQID, ALT_DMALL_STARMON_FQNAME, DMALL_STARMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Starmon
        { DMALL_STIFFILMON_NAME, DMALL_STIFFILMON_ID, ALT_DMALL_STIFFILMON_FQID, ALT_DMALL_STIFFILMON_FQNAME, DMALL_STIFFILMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Stiffilmon
        { DMALL_SUBMARINMON_NAME, DMALL_SUBMARINMON_ID, ALT_DMALL_SUBMARINMON_FQID, ALT_DMALL_SUBMARINMON_FQNAME, DMALL_SUBMARINMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Submarinmon
        { DMALL_SUNAMON_NAME, DMALL_SUNAMON_ID, ALT_DMALL_SUNAMON_FQID, ALT_DMALL_SUNAMON_FQNAME, DMALL_SUNAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Sunamon
        { DMALL_SUNARIZAMON_NAME, DMALL_SUNARIZAMON_ID, ALT_DMALL_SUNARIZAMON_FQID, ALT_DMALL_SUNARIZAMON_FQNAME, DMALL_SUNARIZAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Sunarizamon
        { DMALL_SUNFLOWMON_NAME, DMALL_SUNFLOWMON_ID, ALT_DMALL_SUNFLOWMON_FQID, ALT_DMALL_SUNFLOWMON_FQNAME, DMALL_SUNFLOWMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Sunflowmon
        { DMALL_SUNMON_NAME, DMALL_SUNMON_ID, ALT_DMALL_SUNMON_FQID, ALT_DMALL_SUNMON_FQNAME, DMALL_SUNMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Sunmon
        { DMALL_SUPERSTARMON_NAME, DMALL_SUPERSTARMON_ID, ALT_DMALL_SUPERSTARMON_FQID, ALT_DMALL_SUPERSTARMON_FQNAME, DMALL_SUPERSTARMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Superstarmon
        { DMALL_SUSANOOMON_NAME, DMALL_SUSANOOMON_ID, ALT_DMALL_SUSANOOMON_FQID, ALT_DMALL_SUSANOOMON_FQNAME, DMALL_SUSANOOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Susanoomon
        { DMALL_SWIMMON_NAME, DMALL_SWIMMON_ID, ALT_DMALL_SWIMMON_FQID, ALT_DMALL_SWIMMON_FQNAME, DMALL_SWIMMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Swimmon
        { DMALL_TAILMON_NAME, DMALL_TAILMON_ID, ALT_DMALL_TAILMON_FQID, ALT_DMALL_TAILMON_FQNAME, DMALL_TAILMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Tailmon
        { DMALL_TAILMON_X_NAME, DMALL_TAILMON_X_ID, ALT_DMALL_TAILMON_X_FQID, ALT_DMALL_TAILMON_X_FQNAME, DMALL_TAILMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Tailmon X
        { DMALL_TANEMON_NAME, DMALL_TANEMON_ID, ALT_DMALL_TANEMON_FQID, ALT_DMALL_TANEMON_FQNAME, DMALL_TANEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Tanemon
        { DMALL_TANKMON_NAME, DMALL_TANKMON_ID, ALT_DMALL_TANKMON_FQID, ALT_DMALL_TANKMON_FQNAME, DMALL_TANKMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Tankmon
        { DMALL_TARGETMON_NAME, DMALL_TARGETMON_ID, ALT_DMALL_TARGETMON_FQID, ALT_DMALL_TARGETMON_FQNAME, DMALL_TARGETMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Targetmon
        { DMALL_TEKKAMON_NAME, DMALL_TEKKAMON_ID, ALT_DMALL_TEKKAMON_FQID, ALT_DMALL_TEKKAMON_FQNAME, DMALL_TEKKAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Tekkamon
        { DMALL_TENTOMON_NAME, DMALL_TENTOMON_ID, ALT_DMALL_TENTOMON_FQID, ALT_DMALL_TENTOMON_FQNAME, DMALL_TENTOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Tentomon
        { DMALL_TERRIERMON_NAME, DMALL_TERRIERMON_ID, ALT_DMALL_TERRIERMON_FQID, ALT_DMALL_TERRIERMON_FQNAME, DMALL_TERRIERMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Terriermon
        { DMALL_TERRIERMON_X_NAME, DMALL_TERRIERMON_X_ID, ALT_DMALL_TERRIERMON_X_FQID, ALT_DMALL_TERRIERMON_X_FQNAME, DMALL_TERRIERMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Terriermon X
        { DMALL_THUNDERBALLMON_NAME, DMALL_THUNDERBALLMON_ID, ALT_DMALL_THUNDERBALLMON_FQID, ALT_DMALL_THUNDERBALLMON_FQNAME, DMALL_THUNDERBALLMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Thunderballmon
        { DMALL_TIA_LUDOMON_NAME, DMALL_TIA_LUDOMON_ID, ALT_DMALL_TIA_LUDOMON_FQID, ALT_DMALL_TIA_LUDOMON_FQNAME, DMALL_TIA_LUDOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Tia Ludomon
        { DMALL_TIGER_VESPAMON_NAME, DMALL_TIGER_VESPAMON_ID, ALT_DMALL_TIGER_VESPAMON_FQID, ALT_DMALL_TIGER_VESPAMON_FQNAME, DMALL_TIGER_VESPAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Tiger Vespamon
        { DMALL_TINKERMON_NAME, DMALL_TINKERMON_ID, ALT_DMALL_TINKERMON_FQID, ALT_DMALL_TINKERMON_FQNAME, DMALL_TINKERMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Tinkermon
        { DMALL_TITAMON_NAME, DMALL_TITAMON_ID, ALT_DMALL_TITAMON_FQID, ALT_DMALL_TITAMON_FQNAME, DMALL_TITAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Titamon
        { DMALL_TOBIUMON_NAME, DMALL_TOBIUMON_ID, ALT_DMALL_TOBIUMON_FQID, ALT_DMALL_TOBIUMON_FQNAME, DMALL_TOBIUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Tobiumon
        { DMALL_TOBUCATMON_NAME, DMALL_TOBUCATMON_ID, ALT_DMALL_TOBUCATMON_FQID, ALT_DMALL_TOBUCATMON_FQNAME, DMALL_TOBUCATMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Tobucatmon
        { DMALL_TOGEMON_NAME, DMALL_TOGEMON_ID, ALT_DMALL_TOGEMON_FQID, ALT_DMALL_TOGEMON_FQNAME, DMALL_TOGEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Togemon
        { DMALL_TOGEMON_X_NAME, DMALL_TOGEMON_X_ID, ALT_DMALL_TOGEMON_X_FQID, ALT_DMALL_TOGEMON_X_FQNAME, DMALL_TOGEMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Togemon X
        { DMALL_TOKOMON_X_NAME, DMALL_TOKOMON_X_ID, ALT_DMALL_TOKOMON_X_FQID, ALT_DMALL_TOKOMON_X_FQNAME, DMALL_TOKOMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Tokomon X
        { DMALL_TONOSAMA_GEKOMON_NAME, DMALL_TONOSAMA_GEKOMON_ID, ALT_DMALL_TONOSAMA_GEKOMON_FQID, ALT_DMALL_TONOSAMA_GEKOMON_FQNAME, DMALL_TONOSAMA_GEKOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Tonosama Gekomon
        { DMALL_TORIKARA_BALLMON_NAME, DMALL_TORIKARA_BALLMON_ID, ALT_DMALL_TORIKARA_BALLMON_FQID, ALT_DMALL_TORIKARA_BALLMON_FQNAME, DMALL_TORIKARA_BALLMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Torikara Ballmon
        { DMALL_TORTAMON_NAME, DMALL_TORTAMON_ID, ALT_DMALL_TORTAMON_FQID, ALT_DMALL_TORTAMON_FQNAME, DMALL_TORTAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Tortamon
        { DMALL_TOYAGUMON_BLACK_NAME, DMALL_TOYAGUMON_BLACK_ID, ALT_DMALL_TOYAGUMON_BLACK_FQID, ALT_DMALL_TOYAGUMON_BLACK_FQNAME, DMALL_TOYAGUMON_BLACK_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for ToyAgumon (Black)
        { DMALL_TOYAGUMON_NAME, DMALL_TOYAGUMON_ID, ALT_DMALL_TOYAGUMON_FQID, ALT_DMALL_TOYAGUMON_FQNAME, DMALL_TOYAGUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for ToyAgumon
        { DMALL_TRICERAMON_NAME, DMALL_TRICERAMON_ID, ALT_DMALL_TRICERAMON_FQID, ALT_DMALL_TRICERAMON_FQNAME, DMALL_TRICERAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Triceramon
        { DMALL_TRICERAMON_X_NAME, DMALL_TRICERAMON_X_ID, ALT_DMALL_TRICERAMON_X_FQID, ALT_DMALL_TRICERAMON_X_FQNAME, DMALL_TRICERAMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Triceramon X
        { DMALL_TROOPMON_NAME, DMALL_TROOPMON_ID, ALT_DMALL_TROOPMON_FQID, ALT_DMALL_TROOPMON_FQNAME, DMALL_TROOPMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Troopmon
        { DMALL_TSUBUMON_NAME, DMALL_TSUBUMON_ID, ALT_DMALL_TSUBUMON_FQID, ALT_DMALL_TSUBUMON_FQNAME, DMALL_TSUBUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Tsubumon
        { DMALL_TSUCHIDARUMON_NAME, DMALL_TSUCHIDARUMON_ID, ALT_DMALL_TSUCHIDARUMON_FQID, ALT_DMALL_TSUCHIDARUMON_FQNAME, DMALL_TSUCHIDARUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Tsuchidarumon
        { DMALL_TSUMEMON_NAME, DMALL_TSUMEMON_ID, ALT_DMALL_TSUMEMON_FQID, ALT_DMALL_TSUMEMON_FQNAME, DMALL_TSUMEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Tsumemon
        { DMALL_TSUNOMON_NAME, DMALL_TSUNOMON_ID, ALT_DMALL_TSUNOMON_FQID, ALT_DMALL_TSUNOMON_FQNAME, DMALL_TSUNOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Tsunomon
        { DMALL_TUNOMON_NAME, DMALL_TUNOMON_ID, ALT_DMALL_TUNOMON_FQID, ALT_DMALL_TUNOMON_FQNAME, DMALL_TUNOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Tunomon
        { DMALL_TURUIEMON_NAME, DMALL_TURUIEMON_ID, ALT_DMALL_TURUIEMON_FQID, ALT_DMALL_TURUIEMON_FQNAME, DMALL_TURUIEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Turuiemon
        { DMALL_TYLOMON_X_NAME, DMALL_TYLOMON_X_ID, ALT_DMALL_TYLOMON_X_FQID, ALT_DMALL_TYLOMON_X_FQNAME, DMALL_TYLOMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Tylomon X
        { DMALL_TYRANNOMON_NAME, DMALL_TYRANNOMON_ID, ALT_DMALL_TYRANNOMON_FQID, ALT_DMALL_TYRANNOMON_FQNAME, DMALL_TYRANNOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Tyrannomon
        { DMALL_TYRANNOMON_X_NAME, DMALL_TYRANNOMON_X_ID, ALT_DMALL_TYRANNOMON_X_FQID, ALT_DMALL_TYRANNOMON_X_FQNAME, DMALL_TYRANNOMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Tyrannomon X
        { DMALL_TYRANOMON_NAME, DMALL_TYRANOMON_ID, ALT_DMALL_TYRANOMON_FQID, ALT_DMALL_TYRANOMON_FQNAME, DMALL_TYRANOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Tyranomon
        { DMALL_TYRANOMON_X_NAME, DMALL_TYRANOMON_X_ID, ALT_DMALL_TYRANOMON_X_FQID, ALT_DMALL_TYRANOMON_X_FQNAME, DMALL_TYRANOMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Tyranomon X
        { DMALL_ULFORCE_V_DRAMON_NAME, DMALL_ULFORCE_V_DRAMON_ID, ALT_DMALL_ULFORCE_V_DRAMON_FQID, ALT_DMALL_ULFORCE_V_DRAMON_FQNAME, DMALL_ULFORCE_V_DRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Ulforce V-dramon
        { DMALL_ULFORCE_V_DRAMON_X_NAME, DMALL_ULFORCE_V_DRAMON_X_ID, ALT_DMALL_ULFORCE_V_DRAMON_X_FQID, ALT_DMALL_ULFORCE_V_DRAMON_X_FQNAME, DMALL_ULFORCE_V_DRAMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Ulforce V-dramon X
        { DMALL_ULTIMATE_BRACHIMON_NAME, DMALL_ULTIMATE_BRACHIMON_ID, ALT_DMALL_ULTIMATE_BRACHIMON_FQID, ALT_DMALL_ULTIMATE_BRACHIMON_FQNAME, DMALL_ULTIMATE_BRACHIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Ultimate Brachimon
        { DMALL_UPAMON_NAME, DMALL_UPAMON_ID, ALT_DMALL_UPAMON_FQID, ALT_DMALL_UPAMON_FQNAME, DMALL_UPAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Upamon
        { DMALL_VADEMON_NAME, DMALL_VADEMON_ID, ALT_DMALL_VADEMON_FQID, ALT_DMALL_VADEMON_FQNAME, DMALL_VADEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Vademon
        { DMALL_VALDURMON_NAME, DMALL_VALDURMON_ID, ALT_DMALL_VALDURMON_FQID, ALT_DMALL_VALDURMON_FQNAME, DMALL_VALDURMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Valdurmon
        { DMALL_VAMDEMON_NAME, DMALL_VAMDEMON_ID, ALT_DMALL_VAMDEMON_FQID, ALT_DMALL_VAMDEMON_FQNAME, DMALL_VAMDEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Vamdemon
        { DMALL_VAMDEMON_X_NAME, DMALL_VAMDEMON_X_ID, ALT_DMALL_VAMDEMON_X_FQID, ALT_DMALL_VAMDEMON_X_FQNAME, DMALL_VAMDEMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Vamdemon X
        { DMALL_V_DRAMON_BLACK_NAME, DMALL_V_DRAMON_BLACK_ID, ALT_DMALL_V_DRAMON_BLACK_FQID, ALT_DMALL_V_DRAMON_BLACK_FQNAME, DMALL_V_DRAMON_BLACK_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for V-dramon (Black)
        { DMALL_V_DRAMON_NAME, DMALL_V_DRAMON_ID, ALT_DMALL_V_DRAMON_FQID, ALT_DMALL_V_DRAMON_FQNAME, DMALL_V_DRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for V-dramon
        { DMALL_VEGIMON_NAME, DMALL_VEGIMON_ID, ALT_DMALL_VEGIMON_FQID, ALT_DMALL_VEGIMON_FQNAME, DMALL_VEGIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Vegimon
        { DMALL_VELGRMON_NAME, DMALL_VELGRMON_ID, ALT_DMALL_VELGRMON_FQID, ALT_DMALL_VELGRMON_FQNAME, DMALL_VELGRMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Velgrmon
        { DMALL_VENOM_VAMDEMON_NAME, DMALL_VENOM_VAMDEMON_ID, ALT_DMALL_VENOM_VAMDEMON_FQID, ALT_DMALL_VENOM_VAMDEMON_FQNAME, DMALL_VENOM_VAMDEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Venom Vamdemon
        { DMALL_VERMILLIMON_NAME, DMALL_VERMILLIMON_ID, ALT_DMALL_VERMILLIMON_FQID, ALT_DMALL_VERMILLIMON_FQNAME, DMALL_VERMILLIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Vermillimon
        { DMALL_V_MON_NAME, DMALL_V_MON_ID, ALT_DMALL_V_MON_FQID, ALT_DMALL_V_MON_FQNAME, DMALL_V_MON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for V-mon
        { DMALL_VOLCANICDRAMON_NAME, DMALL_VOLCANICDRAMON_ID, ALT_DMALL_VOLCANICDRAMON_FQID, ALT_DMALL_VOLCANICDRAMON_FQNAME, DMALL_VOLCANICDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Volcanicdramon
        { DMALL_VOLTO_BAUTAMON_NAME, DMALL_VOLTO_BAUTAMON_ID, ALT_DMALL_VOLTO_BAUTAMON_FQID, ALT_DMALL_VOLTO_BAUTAMON_FQNAME, DMALL_VOLTO_BAUTAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Volto Bautamon
        { DMALL_VORVOMON_NAME, DMALL_VORVOMON_ID, ALT_DMALL_VORVOMON_FQID, ALT_DMALL_VORVOMON_FQNAME, DMALL_VORVOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Vorvomon
        { DMALL_WANYAMON_NAME, DMALL_WANYAMON_ID, ALT_DMALL_WANYAMON_FQID, ALT_DMALL_WANYAMON_FQNAME, DMALL_WANYAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Wanyamon
        { DMALL_WAR_GREYMON_NAME, DMALL_WAR_GREYMON_ID, ALT_DMALL_WAR_GREYMON_FQID, ALT_DMALL_WAR_GREYMON_FQNAME, DMALL_WAR_GREYMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for War Greymon
        { DMALL_WAR_GREYMON_X_NAME, DMALL_WAR_GREYMON_X_ID, ALT_DMALL_WAR_GREYMON_X_FQID, ALT_DMALL_WAR_GREYMON_X_FQNAME, DMALL_WAR_GREYMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for War Greymon X
        { DMALL_WARU_MONZAEMON_NAME, DMALL_WARU_MONZAEMON_ID, ALT_DMALL_WARU_MONZAEMON_FQID, ALT_DMALL_WARU_MONZAEMON_FQNAME, DMALL_WARU_MONZAEMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Waru Monzaemon
        { DMALL_WARU_SEADRAMON_NAME, DMALL_WARU_SEADRAMON_ID, ALT_DMALL_WARU_SEADRAMON_FQID, ALT_DMALL_WARU_SEADRAMON_FQNAME, DMALL_WARU_SEADRAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Waru Seadramon
        { DMALL_WASPMON_NAME, DMALL_WASPMON_ID, ALT_DMALL_WASPMON_FQID, ALT_DMALL_WASPMON_FQNAME, DMALL_WASPMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Waspmon
        { DMALL_WEREGARURUMON_BLACK_NAME, DMALL_WEREGARURUMON_BLACK_ID, ALT_DMALL_WEREGARURUMON_BLACK_FQID, ALT_DMALL_WEREGARURUMON_BLACK_FQNAME, DMALL_WEREGARURUMON_BLACK_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for WereGarurumon (Black)
        { DMALL_WERE_GARURUMON_NAME, DMALL_WERE_GARURUMON_ID, ALT_DMALL_WERE_GARURUMON_FQID, ALT_DMALL_WERE_GARURUMON_FQNAME, DMALL_WERE_GARURUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Were Garurumon
        { DMALL_WERE_GARURUMON_X_NAME, DMALL_WERE_GARURUMON_X_ID, ALT_DMALL_WERE_GARURUMON_X_FQID, ALT_DMALL_WERE_GARURUMON_X_FQNAME, DMALL_WERE_GARURUMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Were Garurumon X
        { DMALL_WHAMON_NAME, DMALL_WHAMON_ID, ALT_DMALL_WHAMON_FQID, ALT_DMALL_WHAMON_FQNAME, DMALL_WHAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Whamon
        { DMALL_WIZARMON_NAME, DMALL_WIZARMON_ID, ALT_DMALL_WIZARMON_FQID, ALT_DMALL_WIZARMON_FQNAME, DMALL_WIZARMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Wizarmon
        { DMALL_WIZARMON_X_NAME, DMALL_WIZARMON_X_ID, ALT_DMALL_WIZARMON_X_FQID, ALT_DMALL_WIZARMON_X_FQNAME, DMALL_WIZARMON_X_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Wizarmon X
        { DMALL_WOODMON_NAME, DMALL_WOODMON_ID, ALT_DMALL_WOODMON_FQID, ALT_DMALL_WOODMON_FQNAME, DMALL_WOODMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Woodmon
        { DMALL_WORMMON_NAME, DMALL_WORMMON_ID, ALT_DMALL_WORMMON_FQID, ALT_DMALL_WORMMON_FQNAME, DMALL_WORMMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Wormmon
        { DMALL_XIAOMON_NAME, DMALL_XIAOMON_ID, ALT_DMALL_XIAOMON_FQID, ALT_DMALL_XIAOMON_FQNAME, DMALL_XIAOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Xiaomon
        { DMALL_XV_MON_BLACK_NAME, DMALL_XV_MON_BLACK_ID, ALT_DMALL_XV_MON_BLACK_FQID, ALT_DMALL_XV_MON_BLACK_FQNAME, DMALL_XV_MON_BLACK_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for XV-mon (Black)
        { DMALL_XV_MON_NAME, DMALL_XV_MON_ID, ALT_DMALL_XV_MON_FQID, ALT_DMALL_XV_MON_FQNAME, DMALL_XV_MON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for XV-mon
        { DMALL_YAAMON_NAME, DMALL_YAAMON_ID, ALT_DMALL_YAAMON_FQID, ALT_DMALL_YAAMON_FQNAME, DMALL_YAAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Yaamon
        { DMALL_YANMAMON_NAME, DMALL_YANMAMON_ID, ALT_DMALL_YANMAMON_FQID, ALT_DMALL_YANMAMON_FQNAME, DMALL_YANMAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Yanmamon
        { DMALL_YATAGARAMON_2006_NAME, DMALL_YATAGARAMON_2006_ID, ALT_DMALL_YATAGARAMON_2006_FQID, ALT_DMALL_YATAGARAMON_2006_FQNAME, DMALL_YATAGARAMON_2006_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Yatagaramon (2006)
        { DMALL_YATAGARAMON_NAME, DMALL_YATAGARAMON_ID, ALT_DMALL_YATAGARAMON_FQID, ALT_DMALL_YATAGARAMON_FQNAME, DMALL_YATAGARAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Yatagaramon
        { DMALL_YOUKOMON_NAME, DMALL_YOUKOMON_ID, ALT_DMALL_YOUKOMON_FQID, ALT_DMALL_YOUKOMON_FQNAME, DMALL_YOUKOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Youkomon
        { DMALL_YUKI_AGUMON_NAME, DMALL_YUKI_AGUMON_ID, ALT_DMALL_YUKI_AGUMON_FQID, ALT_DMALL_YUKI_AGUMON_FQNAME, DMALL_YUKI_AGUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Yuki Agumon
        { DMALL_YUKIDARUMON_NAME, DMALL_YUKIDARUMON_ID, ALT_DMALL_YUKIDARUMON_FQID, ALT_DMALL_YUKIDARUMON_FQNAME, DMALL_YUKIDARUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Yukidarumon
        { DMALL_YUKIMI_BOTAMON_NAME, DMALL_YUKIMI_BOTAMON_ID, ALT_DMALL_YUKIMI_BOTAMON_FQID, ALT_DMALL_YUKIMI_BOTAMON_FQNAME, DMALL_YUKIMI_BOTAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Yukimi Botamon
        { DMALL_YURAMON_NAME, DMALL_YURAMON_ID, ALT_DMALL_YURAMON_FQID, ALT_DMALL_YURAMON_FQNAME, DMALL_YURAMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Yuramon
        { DMALL_ZASSOUMON_NAME, DMALL_ZASSOUMON_ID, ALT_DMALL_ZASSOUMON_FQID, ALT_DMALL_ZASSOUMON_FQNAME, DMALL_ZASSOUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Zassoumon
        { DMALL_ZENIMON_NAME, DMALL_ZENIMON_ID, ALT_DMALL_ZENIMON_FQID, ALT_DMALL_ZENIMON_FQNAME, DMALL_ZENIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Zenimon
        { DMALL_ZERIMON_NAME, DMALL_ZERIMON_ID, ALT_DMALL_ZERIMON_FQID, ALT_DMALL_ZERIMON_FQNAME, DMALL_ZERIMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Zerimon
        { DMALL_ZUDOMON_NAME, DMALL_ZUDOMON_ID, ALT_DMALL_ZUDOMON_FQID, ALT_DMALL_ZUDOMON_FQNAME, DMALL_ZUDOMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Zudomon
        { DMALL_ZURUMON_NAME, DMALL_ZURUMON_ID, ALT_DMALL_ZURUMON_FQID, ALT_DMALL_ZURUMON_FQNAME, DMALL_ZURUMON_ANIM_INDEX, config::config_animation_dm_set_t::dmall, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Zurumon
        
    };
    static const size_t dmall_alt_animation_table_size = LEN_ARRAY(dmall_animation_table);
    static const config_animation_names_entry_t dmall_animation_names_table[] = {
        { DMALL_ZURUMON_NAME, DMALL_ZURUMON_NAME_LEN, DMALL_ZURUMON_ID, DMALL_ZURUMON_ID_LEN, DMALL_ZURUMON_FQID, DMALL_ZURUMON_FQID_LEN, DMALL_ZURUMON_FQNAME, DMALL_ZURUMON_FQNAME_LEN },
        
    };

    config_animation_entry_t get_config_animation_name_dmall(size_t index) {
        assert(LEN_ARRAY(dmall_animation_table) == DMALL_ANIM_COUNT);
        assert(index < DMALL_ANIM_COUNT);
        return dmall_animation_table[index];
    }

    static void unload_config_parse_animation_names_dmall() {
        for (const auto& entry : dmall_animation_names_table) {
            platform::details::asset_unload_cstr(entry.name,   entry.name_len);
            platform::details::asset_unload_cstr(entry.id,     entry.id_len);
            platform::details::asset_unload_cstr(entry.fqid,   entry.fqid_len);
            platform::details::asset_unload_cstr(entry.fqname, entry.fqname_len);
        }
    }
    int config_parse_animation_name_dmall(config::config_t& config, const char *value) {
        assert(LEN_ARRAY(dmall_animation_table) == DMALL_ANIM_COUNT);
        int ret = -1;
        for (size_t i = 0;ret < 0 && i < DMALL_ANIM_COUNT;++i) {
            const auto& entry = dmall_animation_table[i];
            if (strcmp(value, entry.name) == 0 ||
                strcmp(value, entry.id) == 0 ||
                strcmp(value, entry.fqid) == 0 ||
                strcmp(value, entry.fqname) == 0) {
                config.animation_index = entry.anim_index;
                config.animation_dm_set = entry.set;
                config.animation_sprite_sheet_layout = entry.layout;
                ret = entry.anim_index;
                break;
            }
        }
        for (size_t i = 0;ret < 0 && i < dmall_alt_animation_table_size;++i) {
            const auto& entry = dmall_alt_animation_table[i];
            if (strcmp(value, entry.name) == 0 ||
                strcmp(value, entry.id) == 0 ||
                strcmp(value, entry.fqid) == 0 ||
                strcmp(value, entry.fqname) == 0) {
                config.animation_index = entry.anim_index;
                config.animation_dm_set = entry.set;
                config.animation_sprite_sheet_layout = entry.layout;
                ret = entry.anim_index;
                break;
            }
        }
        unload_config_parse_animation_names_dmall();
        return ret;
    }
}

