#include "embedded_assets/embedded_image.h"
#include "embedded_assets/pen20/pen20.hpp"
#include "pen20_config_parse_animation_name.h"
#include "utils/memory.h"
#include "utils/system_memory.h"

namespace bongocat::assets {
    static const config_animation_entry_t pen20_animation_table[] = {
        { PEN20_AERO_V_DRAMON_NAME, PEN20_AERO_V_DRAMON_ID, PEN20_AERO_V_DRAMON_FQID, PEN20_AERO_V_DRAMON_FQNAME, PEN20_AERO_V_DRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_AGUMON_HAKASE_NAME, PEN20_AGUMON_HAKASE_ID, PEN20_AGUMON_HAKASE_FQID, PEN20_AGUMON_HAKASE_FQNAME, PEN20_AGUMON_HAKASE_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_ALPHAMON_OURYUKEN_NAME, PEN20_ALPHAMON_OURYUKEN_ID, PEN20_ALPHAMON_OURYUKEN_FQID, PEN20_ALPHAMON_OURYUKEN_FQNAME, PEN20_ALPHAMON_OURYUKEN_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_ANDIRAMON_NAME, PEN20_ANDIRAMON_ID, PEN20_ANDIRAMON_FQID, PEN20_ANDIRAMON_FQNAME, PEN20_ANDIRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_ANDROMON_NAME, PEN20_ANDROMON_ID, PEN20_ANDROMON_FQID, PEN20_ANDROMON_FQNAME, PEN20_ANDROMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_ANGEWOMON_NAME, PEN20_ANGEWOMON_ID, PEN20_ANGEWOMON_FQID, PEN20_ANGEWOMON_FQNAME, PEN20_ANGEWOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_ANOMALOCARIMON_NAME, PEN20_ANOMALOCARIMON_ID, PEN20_ANOMALOCARIMON_FQID, PEN20_ANOMALOCARIMON_FQNAME, PEN20_ANOMALOCARIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_ARRESTERDRAMON_NAME, PEN20_ARRESTERDRAMON_ID, PEN20_ARRESTERDRAMON_FQID, PEN20_ARRESTERDRAMON_FQNAME, PEN20_ARRESTERDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_ASTAMON_NAME, PEN20_ASTAMON_ID, PEN20_ASTAMON_FQID, PEN20_ASTAMON_FQNAME, PEN20_ASTAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_ASTRAMON_NAME, PEN20_ASTRAMON_ID, PEN20_ASTRAMON_FQID, PEN20_ASTRAMON_FQNAME, PEN20_ASTRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_ASURAMON_NAME, PEN20_ASURAMON_ID, PEN20_ASURAMON_FQID, PEN20_ASURAMON_FQNAME, PEN20_ASURAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_ATLUR_KABUTERIMON_NAME, PEN20_ATLUR_KABUTERIMON_ID, PEN20_ATLUR_KABUTERIMON_FQID, PEN20_ATLUR_KABUTERIMON_FQNAME, PEN20_ATLUR_KABUTERIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_BAALMON_NAME, PEN20_BAALMON_ID, PEN20_BAALMON_FQID, PEN20_BAALMON_FQNAME, PEN20_BAALMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_BAKEMON_NAME, PEN20_BAKEMON_ID, PEN20_BAKEMON_FQID, PEN20_BAKEMON_FQNAME, PEN20_BAKEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_BAKUMON_NAME, PEN20_BAKUMON_ID, PEN20_BAKUMON_FQID, PEN20_BAKUMON_FQNAME, PEN20_BAKUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_BANCHO_LEOMON_NAME, PEN20_BANCHO_LEOMON_ID, PEN20_BANCHO_LEOMON_FQID, PEN20_BANCHO_LEOMON_FQNAME, PEN20_BANCHO_LEOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_BEELZEBUMON_BLAST_MODE_NAME, PEN20_BEELZEBUMON_BLAST_MODE_ID, PEN20_BEELZEBUMON_BLAST_MODE_FQID, PEN20_BEELZEBUMON_BLAST_MODE_FQNAME, PEN20_BEELZEBUMON_BLAST_MODE_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_BEOWOLFMON_NAME, PEN20_BEOWOLFMON_ID, PEN20_BEOWOLFMON_FQID, PEN20_BEOWOLFMON_FQNAME, PEN20_BEOWOLFMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_BEOWULFMON_NAME, PEN20_BEOWULFMON_ID, PEN20_BEOWULFMON_FQID, PEN20_BEOWULFMON_FQNAME, PEN20_BEOWULFMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_BIG_MAMEMON_NAME, PEN20_BIG_MAMEMON_ID, PEN20_BIG_MAMEMON_FQID, PEN20_BIG_MAMEMON_FQNAME, PEN20_BIG_MAMEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_BIRDRAMON_NAME, PEN20_BIRDRAMON_ID, PEN20_BIRDRAMON_FQID, PEN20_BIRDRAMON_FQNAME, PEN20_BIRDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_BLOSSOMON_NAME, PEN20_BLOSSOMON_ID, PEN20_BLOSSOMON_FQID, PEN20_BLOSSOMON_FQNAME, PEN20_BLOSSOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_BOLTMON_NAME, PEN20_BOLTMON_ID, PEN20_BOLTMON_FQID, PEN20_BOLTMON_FQNAME, PEN20_BOLTMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_BREAKDRAMON_NAME, PEN20_BREAKDRAMON_ID, PEN20_BREAKDRAMON_FQID, PEN20_BREAKDRAMON_FQNAME, PEN20_BREAKDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_BRYWELUDRAMON_NAME, PEN20_BRYWELUDRAMON_ID, PEN20_BRYWELUDRAMON_FQID, PEN20_BRYWELUDRAMON_FQNAME, PEN20_BRYWELUDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_BUBBMON_NAME, PEN20_BUBBMON_ID, PEN20_BUBBMON_FQID, PEN20_BUBBMON_FQNAME, PEN20_BUBBMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_BUDMON_NAME, PEN20_BUDMON_ID, PEN20_BUDMON_FQID, PEN20_BUDMON_FQNAME, PEN20_BUDMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_BUSHI_AGUMON_NAME, PEN20_BUSHI_AGUMON_ID, PEN20_BUSHI_AGUMON_FQID, PEN20_BUSHI_AGUMON_FQNAME, PEN20_BUSHI_AGUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_CANDMON_NAME, PEN20_CANDMON_ID, PEN20_CANDMON_FQID, PEN20_CANDMON_FQNAME, PEN20_CANDMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_CAPRIMON_NAME, PEN20_CAPRIMON_ID, PEN20_CAPRIMON_FQID, PEN20_CAPRIMON_FQNAME, PEN20_CAPRIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_CHAOSMON_NAME, PEN20_CHAOSMON_ID, PEN20_CHAOSMON_FQID, PEN20_CHAOSMON_FQNAME, PEN20_CHAOSMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_CHERUBIMON_NAME, PEN20_CHERUBIMON_ID, PEN20_CHERUBIMON_FQID, PEN20_CHERUBIMON_FQNAME, PEN20_CHERUBIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_CHIBIMON_NAME, PEN20_CHIBIMON_ID, PEN20_CHIBIMON_FQID, PEN20_CHIBIMON_FQNAME, PEN20_CHIBIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_CHICOMON_NAME, PEN20_CHICOMON_ID, PEN20_CHICOMON_FQID, PEN20_CHICOMON_FQNAME, PEN20_CHICOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_CHOROMON_NAME, PEN20_CHOROMON_ID, PEN20_CHOROMON_FQID, PEN20_CHOROMON_FQNAME, PEN20_CHOROMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_CLOCKMON_NAME, PEN20_CLOCKMON_ID, PEN20_CLOCKMON_FQID, PEN20_CLOCKMON_FQNAME, PEN20_CLOCKMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_COCOMON_NAME, PEN20_COCOMON_ID, PEN20_COCOMON_FQID, PEN20_COCOMON_FQNAME, PEN20_COCOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_COELAMON_NAME, PEN20_COELAMON_ID, PEN20_COELAMON_FQID, PEN20_COELAMON_FQNAME, PEN20_COELAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_COREDRAMON_BLUE_NAME, PEN20_COREDRAMON_BLUE_ID, PEN20_COREDRAMON_BLUE_FQID, PEN20_COREDRAMON_BLUE_FQNAME, PEN20_COREDRAMON_BLUE_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_COREDRAMON_GREEN_NAME, PEN20_COREDRAMON_GREEN_ID, PEN20_COREDRAMON_GREEN_FQID, PEN20_COREDRAMON_GREEN_FQNAME, PEN20_COREDRAMON_GREEN_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_COTSUCOMON_NAME, PEN20_COTSUCOMON_ID, PEN20_COTSUCOMON_FQID, PEN20_COTSUCOMON_FQNAME, PEN20_COTSUCOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_CYBERDRAMON_NAME, PEN20_CYBERDRAMON_ID, PEN20_CYBERDRAMON_FQID, PEN20_CYBERDRAMON_FQNAME, PEN20_CYBERDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_DAGOMON_NAME, PEN20_DAGOMON_ID, PEN20_DAGOMON_FQID, PEN20_DAGOMON_FQNAME, PEN20_DAGOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_DARKDRAMON_NAME, PEN20_DARKDRAMON_ID, PEN20_DARKDRAMON_FQID, PEN20_DARKDRAMON_FQNAME, PEN20_DARKDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_DARK_KNIGHTMON_NAME, PEN20_DARK_KNIGHTMON_ID, PEN20_DARK_KNIGHTMON_FQID, PEN20_DARK_KNIGHTMON_FQNAME, PEN20_DARK_KNIGHTMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_DEATH_MERAMON_NAME, PEN20_DEATH_MERAMON_ID, PEN20_DEATH_MERAMON_FQID, PEN20_DEATH_MERAMON_FQNAME, PEN20_DEATH_MERAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_DELUMON_NAME, PEN20_DELUMON_ID, PEN20_DELUMON_FQID, PEN20_DELUMON_FQNAME, PEN20_DELUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_DEVIDRAMON_NAME, PEN20_DEVIDRAMON_ID, PEN20_DEVIDRAMON_FQID, PEN20_DEVIDRAMON_FQNAME, PEN20_DEVIDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_DEVIMON_NAME, PEN20_DEVIMON_ID, PEN20_DEVIMON_FQID, PEN20_DEVIMON_FQNAME, PEN20_DEVIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_DOKUGUMON_NAME, PEN20_DOKUGUMON_ID, PEN20_DOKUGUMON_FQID, PEN20_DOKUGUMON_FQNAME, PEN20_DOKUGUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_DORUGORAMON_NAME, PEN20_DORUGORAMON_ID, PEN20_DORUGORAMON_FQID, PEN20_DORUGORAMON_FQNAME, PEN20_DORUGORAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_DURAMON_NAME, PEN20_DURAMON_ID, PEN20_DURAMON_FQID, PEN20_DURAMON_FQNAME, PEN20_DURAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_DURANDAMON_NAME, PEN20_DURANDAMON_ID, PEN20_DURANDAMON_FQID, PEN20_DURANDAMON_FQNAME, PEN20_DURANDAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_EBIDRAMON_NAME, PEN20_EBIDRAMON_ID, PEN20_EBIDRAMON_FQID, PEN20_EBIDRAMON_FQNAME, PEN20_EBIDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_ETEMON_NAME, PEN20_ETEMON_ID, PEN20_ETEMON_FQID, PEN20_ETEMON_FQNAME, PEN20_ETEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_EXAMON_NAME, PEN20_EXAMON_ID, PEN20_EXAMON_FQID, PEN20_EXAMON_FQNAME, PEN20_EXAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_FANTOMON_NAME, PEN20_FANTOMON_ID, PEN20_FANTOMON_FQID, PEN20_FANTOMON_FQNAME, PEN20_FANTOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_FLORAMON_NAME, PEN20_FLORAMON_ID, PEN20_FLORAMON_FQID, PEN20_FLORAMON_FQNAME, PEN20_FLORAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_FUFUMON_NAME, PEN20_FUFUMON_ID, PEN20_FUFUMON_FQID, PEN20_FUFUMON_FQNAME, PEN20_FUFUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_GALGOMON_NAME, PEN20_GALGOMON_ID, PEN20_GALGOMON_FQID, PEN20_GALGOMON_FQNAME, PEN20_GALGOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_GANIMON_NAME, PEN20_GANIMON_ID, PEN20_GANIMON_FQID, PEN20_GANIMON_FQNAME, PEN20_GANIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_GARUDAMON_NAME, PEN20_GARUDAMON_ID, PEN20_GARUDAMON_FQID, PEN20_GARUDAMON_FQNAME, PEN20_GARUDAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_GARURUMON_NAME, PEN20_GARURUMON_ID, PEN20_GARURUMON_FQID, PEN20_GARURUMON_FQNAME, PEN20_GARURUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_GEKOMON_NAME, PEN20_GEKOMON_ID, PEN20_GEKOMON_FQID, PEN20_GEKOMON_FQNAME, PEN20_GEKOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_GERBEMON_NAME, PEN20_GERBEMON_ID, PEN20_GERBEMON_FQID, PEN20_GERBEMON_FQNAME, PEN20_GERBEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_GESOMON_NAME, PEN20_GESOMON_ID, PEN20_GESOMON_FQID, PEN20_GESOMON_FQNAME, PEN20_GESOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_GINRYUMON_NAME, PEN20_GINRYUMON_ID, PEN20_GINRYUMON_FQID, PEN20_GINRYUMON_FQNAME, PEN20_GINRYUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_GOMAMON_NAME, PEN20_GOMAMON_ID, PEN20_GOMAMON_FQID, PEN20_GOMAMON_FQNAME, PEN20_GOMAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_GOTTSUMON_NAME, PEN20_GOTTSUMON_ID, PEN20_GOTTSUMON_FQID, PEN20_GOTTSUMON_FQNAME, PEN20_GOTTSUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_GREYMON_NAME, PEN20_GREYMON_ID, PEN20_GREYMON_FQID, PEN20_GREYMON_FQNAME, PEN20_GREYMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_GRIFFOMON_NAME, PEN20_GRIFFOMON_ID, PEN20_GRIFFOMON_FQID, PEN20_GRIFFOMON_FQNAME, PEN20_GRIFFOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_GROUNDRAMON_NAME, PEN20_GROUNDRAMON_ID, PEN20_GROUNDRAMON_FQID, PEN20_GROUNDRAMON_FQNAME, PEN20_GROUNDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_GROWMON_NAME, PEN20_GROWMON_ID, PEN20_GROWMON_FQID, PEN20_GROWMON_FQNAME, PEN20_GROWMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_GUARDROMON_NAME, PEN20_GUARDROMON_ID, PEN20_GUARDROMON_FQID, PEN20_GUARDROMON_FQNAME, PEN20_GUARDROMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_GUIMON_NAME, PEN20_GUIMON_ID, PEN20_GUIMON_FQID, PEN20_GUIMON_FQNAME, PEN20_GUIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_GUMMYMON_NAME, PEN20_GUMMYMON_ID, PEN20_GUMMYMON_FQID, PEN20_GUMMYMON_FQNAME, PEN20_GUMMYMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_HAGURUMON_NAME, PEN20_HAGURUMON_ID, PEN20_HAGURUMON_FQID, PEN20_HAGURUMON_FQNAME, PEN20_HAGURUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_HANGYMON_NAME, PEN20_HANGYMON_ID, PEN20_HANGYMON_FQID, PEN20_HANGYMON_FQNAME, PEN20_HANGYMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_HANGYOMON_NAME, PEN20_HANGYOMON_ID, PEN20_HANGYOMON_FQID, PEN20_HANGYOMON_FQNAME, PEN20_HANGYOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_HANUMON_NAME, PEN20_HANUMON_ID, PEN20_HANUMON_FQID, PEN20_HANUMON_FQNAME, PEN20_HANUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_HERAKLE_KABUTERIMON_NAME, PEN20_HERAKLE_KABUTERIMON_ID, PEN20_HERAKLE_KABUTERIMON_FQID, PEN20_HERAKLE_KABUTERIMON_FQNAME, PEN20_HERAKLE_KABUTERIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_HERKULE_KABUTERIMON_NAME, PEN20_HERKULE_KABUTERIMON_ID, PEN20_HERKULE_KABUTERIMON_FQID, PEN20_HERKULE_KABUTERIMON_FQNAME, PEN20_HERKULE_KABUTERIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_HISYARYUMON_NAME, PEN20_HISYARYUMON_ID, PEN20_HISYARYUMON_FQID, PEN20_HISYARYUMON_FQNAME, PEN20_HISYARYUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_HOLY_ANGEMON_NAME, PEN20_HOLY_ANGEMON_ID, PEN20_HOLY_ANGEMON_FQID, PEN20_HOLY_ANGEMON_FQNAME, PEN20_HOLY_ANGEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_HOLYDRAMON_NAME, PEN20_HOLYDRAMON_ID, PEN20_HOLYDRAMON_FQID, PEN20_HOLYDRAMON_FQNAME, PEN20_HOLYDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_HOUOUMON_NAME, PEN20_HOUOUMON_ID, PEN20_HOUOUMON_FQID, PEN20_HOUOUMON_FQNAME, PEN20_HOUOUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_IGNAMON_NAME, PEN20_IGNAMON_ID, PEN20_IGNAMON_FQID, PEN20_IGNAMON_FQNAME, PEN20_IGNAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_IKKAKUMON_NAME, PEN20_IKKAKUMON_ID, PEN20_IKKAKUMON_FQID, PEN20_IKKAKUMON_FQNAME, PEN20_IKKAKUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_IMPERIALDRAMON_FIGHTER_MODE_NAME, PEN20_IMPERIALDRAMON_FIGHTER_MODE_ID, PEN20_IMPERIALDRAMON_FIGHTER_MODE_FQID, PEN20_IMPERIALDRAMON_FIGHTER_MODE_FQNAME, PEN20_IMPERIALDRAMON_FIGHTER_MODE_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_IMPMON_NAME, PEN20_IMPMON_ID, PEN20_IMPMON_FQID, PEN20_IMPMON_FQNAME, PEN20_IMPMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_JESMON_NAME, PEN20_JESMON_ID, PEN20_JESMON_FQID, PEN20_JESMON_FQNAME, PEN20_JESMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_JESMON_X_NAME, PEN20_JESMON_X_ID, PEN20_JESMON_X_FQID, PEN20_JESMON_X_FQNAME, PEN20_JESMON_X_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_JYAGAMON_NAME, PEN20_JYAGAMON_ID, PEN20_JYAGAMON_FQID, PEN20_JYAGAMON_FQNAME, PEN20_JYAGAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_JYUREIMON_NAME, PEN20_JYUREIMON_ID, PEN20_JYUREIMON_FQID, PEN20_JYUREIMON_FQNAME, PEN20_JYUREIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_KABUTERIMON_NAME, PEN20_KABUTERIMON_ID, PEN20_KABUTERIMON_FQID, PEN20_KABUTERIMON_FQNAME, PEN20_KABUTERIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_KAKKINMON_NAME, PEN20_KAKKINMON_ID, PEN20_KAKKINMON_FQID, PEN20_KAKKINMON_FQNAME, PEN20_KAKKINMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_KIWIMON_NAME, PEN20_KIWIMON_ID, PEN20_KIWIMON_FQID, PEN20_KIWIMON_FQNAME, PEN20_KIWIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_KNIGHTMON_NAME, PEN20_KNIGHTMON_ID, PEN20_KNIGHTMON_FQID, PEN20_KNIGHTMON_FQNAME, PEN20_KNIGHTMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_KOKUWAMON_NAME, PEN20_KOKUWAMON_ID, PEN20_KOKUWAMON_FQID, PEN20_KOKUWAMON_FQNAME, PEN20_KOKUWAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_KUWAGAMON_NAME, PEN20_KUWAGAMON_ID, PEN20_KUWAGAMON_FQID, PEN20_KUWAGAMON_FQNAME, PEN20_KUWAGAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_KYOKYOMON_NAME, PEN20_KYOKYOMON_ID, PEN20_KYOKYOMON_FQID, PEN20_KYOKYOMON_FQNAME, PEN20_KYOKYOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_LADY_DEVIMON_NAME, PEN20_LADY_DEVIMON_ID, PEN20_LADY_DEVIMON_FQID, PEN20_LADY_DEVIMON_FQNAME, PEN20_LADY_DEVIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_LALAMON_NAME, PEN20_LALAMON_ID, PEN20_LALAMON_FQID, PEN20_LALAMON_FQNAME, PEN20_LALAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_LAVOGARITAMON_NAME, PEN20_LAVOGARITAMON_ID, PEN20_LAVOGARITAMON_FQID, PEN20_LAVOGARITAMON_FQNAME, PEN20_LAVOGARITAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_LAVORVOMON_NAME, PEN20_LAVORVOMON_ID, PEN20_LAVORVOMON_FQID, PEN20_LAVORVOMON_FQNAME, PEN20_LAVORVOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_LILAMON_NAME, PEN20_LILAMON_ID, PEN20_LILAMON_FQID, PEN20_LILAMON_FQNAME, PEN20_LILAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_LILIMON_NAME, PEN20_LILIMON_ID, PEN20_LILIMON_FQID, PEN20_LILIMON_FQNAME, PEN20_LILIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_LOPMON_NAME, PEN20_LOPMON_ID, PEN20_LOPMON_FQID, PEN20_LOPMON_FQNAME, PEN20_LOPMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_LOTUSMON_NAME, PEN20_LOTUSMON_ID, PEN20_LOTUSMON_FQID, PEN20_LOTUSMON_FQNAME, PEN20_LOTUSMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_LUDOMON_NAME, PEN20_LUDOMON_ID, PEN20_LUDOMON_FQID, PEN20_LUDOMON_FQNAME, PEN20_LUDOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_MAD_LEOMON_NAME, PEN20_MAD_LEOMON_ID, PEN20_MAD_LEOMON_FQID, PEN20_MAD_LEOMON_FQNAME, PEN20_MAD_LEOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_MAMBOMON_NAME, PEN20_MAMBOMON_ID, PEN20_MAMBOMON_FQID, PEN20_MAMBOMON_FQNAME, PEN20_MAMBOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_MAMMON_NAME, PEN20_MAMMON_ID, PEN20_MAMMON_FQID, PEN20_MAMMON_FQNAME, PEN20_MAMMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_MANBOMON_NAME, PEN20_MANBOMON_ID, PEN20_MANBOMON_FQID, PEN20_MANBOMON_FQNAME, PEN20_MANBOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_MARIN_ANGEMON_NAME, PEN20_MARIN_ANGEMON_ID, PEN20_MARIN_ANGEMON_FQID, PEN20_MARIN_ANGEMON_FQNAME, PEN20_MARIN_ANGEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_MARIN_DEVIMON_NAME, PEN20_MARIN_DEVIMON_ID, PEN20_MARIN_DEVIMON_FQID, PEN20_MARIN_DEVIMON_FQNAME, PEN20_MARIN_DEVIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_MASTEMON_NAME, PEN20_MASTEMON_ID, PEN20_MASTEMON_FQID, PEN20_MASTEMON_FQNAME, PEN20_MASTEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_MECHANORIMON_NAME, PEN20_MECHANORIMON_ID, PEN20_MECHANORIMON_FQID, PEN20_MECHANORIMON_FQNAME, PEN20_MECHANORIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_MEGADRAMON_NAME, PEN20_MEGADRAMON_ID, PEN20_MEGADRAMON_FQID, PEN20_MEGADRAMON_FQNAME, PEN20_MEGADRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_MEGALO_GROWMON_NAME, PEN20_MEGALO_GROWMON_ID, PEN20_MEGALO_GROWMON_FQID, PEN20_MEGALO_GROWMON_FQNAME, PEN20_MEGALO_GROWMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_MEGA_SEADRAMON_NAME, PEN20_MEGA_SEADRAMON_ID, PEN20_MEGA_SEADRAMON_FQID, PEN20_MEGA_SEADRAMON_FQNAME, PEN20_MEGA_SEADRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_MEICRACKMON_VICIOUS_MODE_NAME, PEN20_MEICRACKMON_VICIOUS_MODE_ID, PEN20_MEICRACKMON_VICIOUS_MODE_FQID, PEN20_MEICRACKMON_VICIOUS_MODE_FQNAME, PEN20_MEICRACKMON_VICIOUS_MODE_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_MERAMON_NAME, PEN20_MERAMON_ID, PEN20_MERAMON_FQID, PEN20_MERAMON_FQNAME, PEN20_MERAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_METAL_ETEMON_NAME, PEN20_METAL_ETEMON_ID, PEN20_METAL_ETEMON_FQID, PEN20_METAL_ETEMON_FQNAME, PEN20_METAL_ETEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_METAL_GARURUMON_NAME, PEN20_METAL_GARURUMON_ID, PEN20_METAL_GARURUMON_FQID, PEN20_METAL_GARURUMON_FQNAME, PEN20_METAL_GARURUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_METAL_GREYMON_NAME, PEN20_METAL_GREYMON_ID, PEN20_METAL_GREYMON_FQID, PEN20_METAL_GREYMON_FQNAME, PEN20_METAL_GREYMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_METAL_MAMEMON_NAME, PEN20_METAL_MAMEMON_ID, PEN20_METAL_MAMEMON_FQID, PEN20_METAL_MAMEMON_FQNAME, PEN20_METAL_MAMEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_METAL_SEADRAMON_NAME, PEN20_METAL_SEADRAMON_ID, PEN20_METAL_SEADRAMON_FQID, PEN20_METAL_SEADRAMON_FQNAME, PEN20_METAL_SEADRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_MOCHIMON_NAME, PEN20_MOCHIMON_ID, PEN20_MOCHIMON_FQID, PEN20_MOCHIMON_FQNAME, PEN20_MOCHIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_MOKUMON_NAME, PEN20_MOKUMON_ID, PEN20_MOKUMON_FQID, PEN20_MOKUMON_FQNAME, PEN20_MOKUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_MONCHROMON_NAME, PEN20_MONCHROMON_ID, PEN20_MONCHROMON_FQID, PEN20_MONCHROMON_FQNAME, PEN20_MONCHROMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_MONOCHROMON_NAME, PEN20_MONOCHROMON_ID, PEN20_MONOCHROMON_FQID, PEN20_MONOCHROMON_FQNAME, PEN20_MONOCHROMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_MUGENDRAMON_NAME, PEN20_MUGENDRAMON_ID, PEN20_MUGENDRAMON_FQID, PEN20_MUGENDRAMON_FQNAME, PEN20_MUGENDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_MUSHMON_NAME, PEN20_MUSHMON_ID, PEN20_MUSHMON_FQID, PEN20_MUSHMON_FQNAME, PEN20_MUSHMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_NYOKIMON_NAME, PEN20_NYOKIMON_ID, PEN20_NYOKIMON_FQID, PEN20_NYOKIMON_FQNAME, PEN20_NYOKIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_OCTMON_NAME, PEN20_OCTMON_ID, PEN20_OCTMON_FQID, PEN20_OCTMON_FQNAME, PEN20_OCTMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_OFANIMON_NAME, PEN20_OFANIMON_ID, PEN20_OFANIMON_FQID, PEN20_OFANIMON_FQNAME, PEN20_OFANIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_OGUDOMON_NAME, PEN20_OGUDOMON_ID, PEN20_OGUDOMON_FQID, PEN20_OGUDOMON_FQNAME, PEN20_OGUDOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_OKUWAMON_NAME, PEN20_OKUWAMON_ID, PEN20_OKUWAMON_FQID, PEN20_OKUWAMON_FQNAME, PEN20_OKUWAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_OMEGAMON_NAME, PEN20_OMEGAMON_ID, PEN20_OMEGAMON_FQID, PEN20_OMEGAMON_FQNAME, PEN20_OMEGAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_ORDINEMON_NAME, PEN20_ORDINEMON_ID, PEN20_ORDINEMON_FQID, PEN20_ORDINEMON_FQNAME, PEN20_ORDINEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_OTAMAMON_NAME, PEN20_OTAMAMON_ID, PEN20_OTAMAMON_FQID, PEN20_OTAMAMON_FQNAME, PEN20_OTAMAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_OURYUMON_NAME, PEN20_OURYUMON_ID, PEN20_OURYUMON_FQID, PEN20_OURYUMON_FQNAME, PEN20_OURYUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_PAILDRAMON_NAME, PEN20_PAILDRAMON_ID, PEN20_PAILDRAMON_FQID, PEN20_PAILDRAMON_FQNAME, PEN20_PAILDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_PALMON_NAME, PEN20_PALMON_ID, PEN20_PALMON_FQID, PEN20_PALMON_FQNAME, PEN20_PALMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_PETI_MERAMON_NAME, PEN20_PETI_MERAMON_ID, PEN20_PETI_MERAMON_FQID, PEN20_PETI_MERAMON_FQNAME, PEN20_PETI_MERAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_PHASCOMON_NAME, PEN20_PHASCOMON_ID, PEN20_PHASCOMON_FQID, PEN20_PHASCOMON_FQNAME, PEN20_PHASCOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_PICCOLOMON_NAME, PEN20_PICCOLOMON_ID, PEN20_PICCOLOMON_FQID, PEN20_PICCOLOMON_FQNAME, PEN20_PICCOLOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_PICO_DEVIMON_NAME, PEN20_PICO_DEVIMON_ID, PEN20_PICO_DEVIMON_FQID, PEN20_PICO_DEVIMON_FQNAME, PEN20_PICO_DEVIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_PIEMON_NAME, PEN20_PIEMON_ID, PEN20_PIEMON_FQID, PEN20_PIEMON_FQNAME, PEN20_PIEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_PINOCHIMON_NAME, PEN20_PINOCHIMON_ID, PEN20_PINOCHIMON_FQID, PEN20_PINOCHIMON_FQNAME, PEN20_PINOCHIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_PIYOMON_NAME, PEN20_PIYOMON_ID, PEN20_PIYOMON_FQID, PEN20_PIYOMON_FQNAME, PEN20_PIYOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_PLESIOMON_NAME, PEN20_PLESIOMON_ID, PEN20_PLESIOMON_FQID, PEN20_PLESIOMON_FQNAME, PEN20_PLESIOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_PORCUPAMON_NAME, PEN20_PORCUPAMON_ID, PEN20_PORCUPAMON_FQID, PEN20_PORCUPAMON_FQNAME, PEN20_PORCUPAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_PORCUPMON_NAME, PEN20_PORCUPMON_ID, PEN20_PORCUPMON_FQID, PEN20_PORCUPMON_FQNAME, PEN20_PORCUPMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_PUKUMON_NAME, PEN20_PUKUMON_ID, PEN20_PUKUMON_FQID, PEN20_PUKUMON_FQNAME, PEN20_PUKUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_PUMPMON_NAME, PEN20_PUMPMON_ID, PEN20_PUMPMON_FQID, PEN20_PUMPMON_FQNAME, PEN20_PUMPMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_PYOCOMON_NAME, PEN20_PYOCOMON_ID, PEN20_PYOCOMON_FQID, PEN20_PYOCOMON_FQNAME, PEN20_PYOCOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_RAFFLESIMON_NAME, PEN20_RAFFLESIMON_ID, PEN20_RAFFLESIMON_FQID, PEN20_RAFFLESIMON_FQNAME, PEN20_RAFFLESIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_RAGNA_LORDMON_NAME, PEN20_RAGNA_LORDMON_ID, PEN20_RAGNA_LORDMON_FQID, PEN20_RAGNA_LORDMON_FQNAME, PEN20_RAGNA_LORDMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_RAGUELMON_NAME, PEN20_RAGUELMON_ID, PEN20_RAGUELMON_FQID, PEN20_RAGUELMON_FQNAME, PEN20_RAGUELMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_RAIJI_LUDOMON_NAME, PEN20_RAIJI_LUDOMON_ID, PEN20_RAIJI_LUDOMON_FQID, PEN20_RAIJI_LUDOMON_FQNAME, PEN20_RAIJI_LUDOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_RAKAMON_NAME, PEN20_RAKAMON_ID, PEN20_RAKAMON_FQID, PEN20_RAKAMON_FQNAME, PEN20_RAKAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_RAPIDMON_NAME, PEN20_RAPIDMON_ID, PEN20_RAPIDMON_FQID, PEN20_RAPIDMON_FQNAME, PEN20_RAPIDMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_RED_VEGIMON_NAME, PEN20_RED_VEGIMON_ID, PEN20_RED_VEGIMON_FQID, PEN20_RED_VEGIMON_FQNAME, PEN20_RED_VEGIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_REPPAMON_NAME, PEN20_REPPAMON_ID, PEN20_REPPAMON_FQID, PEN20_REPPAMON_FQNAME, PEN20_REPPAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_REVOLMON_NAME, PEN20_REVOLMON_ID, PEN20_REVOLMON_FQID, PEN20_REVOLMON_FQNAME, PEN20_REVOLMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_RIZE_GREYMON_NAME, PEN20_RIZE_GREYMON_ID, PEN20_RIZE_GREYMON_FQID, PEN20_RIZE_GREYMON_FQNAME, PEN20_RIZE_GREYMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_ROSEMON_NAME, PEN20_ROSEMON_ID, PEN20_ROSEMON_FQID, PEN20_ROSEMON_FQNAME, PEN20_ROSEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_RUKAMON_NAME, PEN20_RUKAMON_ID, PEN20_RUKAMON_FQID, PEN20_RUKAMON_FQNAME, PEN20_RUKAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_RYUDAMON_NAME, PEN20_RYUDAMON_ID, PEN20_RYUDAMON_FQID, PEN20_RYUDAMON_FQNAME, PEN20_RYUDAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_SABER_LEOMON_NAME, PEN20_SABER_LEOMON_ID, PEN20_SABER_LEOMON_FQID, PEN20_SABER_LEOMON_FQNAME, PEN20_SABER_LEOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_SAINT_GALGOMON_NAME, PEN20_SAINT_GALGOMON_ID, PEN20_SAINT_GALGOMON_FQID, PEN20_SAINT_GALGOMON_FQNAME, PEN20_SAINT_GALGOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_SAVIOR_HACKMON_NAME, PEN20_SAVIOR_HACKMON_ID, PEN20_SAVIOR_HACKMON_FQID, PEN20_SAVIOR_HACKMON_FQNAME, PEN20_SAVIOR_HACKMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_SEADRAMON_NAME, PEN20_SEADRAMON_ID, PEN20_SEADRAMON_FQID, PEN20_SEADRAMON_FQNAME, PEN20_SEADRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_SERAPHIMON_NAME, PEN20_SERAPHIMON_ID, PEN20_SERAPHIMON_FQID, PEN20_SERAPHIMON_FQNAME, PEN20_SERAPHIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_SHADRAMON_NAME, PEN20_SHADRAMON_ID, PEN20_SHADRAMON_FQID, PEN20_SHADRAMON_FQNAME, PEN20_SHADRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_SHAKOMON_NAME, PEN20_SHAKOMON_ID, PEN20_SHAKOMON_FQID, PEN20_SHAKOMON_FQNAME, PEN20_SHAKOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_SKULL_MAMMON_NAME, PEN20_SKULL_MAMMON_ID, PEN20_SKULL_MAMMON_FQID, PEN20_SKULL_MAMMON_FQNAME, PEN20_SKULL_MAMMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_SLAYERDRAMON_NAME, PEN20_SLAYERDRAMON_ID, PEN20_SLAYERDRAMON_FQID, PEN20_SLAYERDRAMON_FQNAME, PEN20_SLAYERDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_STARMON_NAME, PEN20_STARMON_ID, PEN20_STARMON_FQID, PEN20_STARMON_FQNAME, PEN20_STARMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_SUNFLOWMON_NAME, PEN20_SUNFLOWMON_ID, PEN20_SUNFLOWMON_FQID, PEN20_SUNFLOWMON_FQNAME, PEN20_SUNFLOWMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_TAILMON_NAME, PEN20_TAILMON_ID, PEN20_TAILMON_FQID, PEN20_TAILMON_FQNAME, PEN20_TAILMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_TANKMON_NAME, PEN20_TANKMON_ID, PEN20_TANKMON_FQID, PEN20_TANKMON_FQNAME, PEN20_TANKMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_TARGETMON_NAME, PEN20_TARGETMON_ID, PEN20_TARGETMON_FQID, PEN20_TARGETMON_FQNAME, PEN20_TARGETMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_TENTOMON_NAME, PEN20_TENTOMON_ID, PEN20_TENTOMON_FQID, PEN20_TENTOMON_FQNAME, PEN20_TENTOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_TERRIERMON_NAME, PEN20_TERRIERMON_ID, PEN20_TERRIERMON_FQID, PEN20_TERRIERMON_FQNAME, PEN20_TERRIERMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_THUNDERBALLMON_NAME, PEN20_THUNDERBALLMON_ID, PEN20_THUNDERBALLMON_FQID, PEN20_THUNDERBALLMON_FQNAME, PEN20_THUNDERBALLMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_TIA_LUDOMON_NAME, PEN20_TIA_LUDOMON_ID, PEN20_TIA_LUDOMON_FQID, PEN20_TIA_LUDOMON_FQNAME, PEN20_TIA_LUDOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_TOGEMON_NAME, PEN20_TOGEMON_ID, PEN20_TOGEMON_FQID, PEN20_TOGEMON_FQNAME, PEN20_TOGEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_TONOSAMA_GEKOMON_NAME, PEN20_TONOSAMA_GEKOMON_ID, PEN20_TONOSAMA_GEKOMON_FQID, PEN20_TONOSAMA_GEKOMON_FQNAME, PEN20_TONOSAMA_GEKOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_TORTAMON_NAME, PEN20_TORTAMON_ID, PEN20_TORTAMON_FQID, PEN20_TORTAMON_FQNAME, PEN20_TORTAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_TOY_AGUMON_NAME, PEN20_TOY_AGUMON_ID, PEN20_TOY_AGUMON_FQID, PEN20_TOY_AGUMON_FQNAME, PEN20_TOY_AGUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_TRICERAMON_NAME, PEN20_TRICERAMON_ID, PEN20_TRICERAMON_FQID, PEN20_TRICERAMON_FQNAME, PEN20_TRICERAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_TROOPMON_NAME, PEN20_TROOPMON_ID, PEN20_TROOPMON_FQID, PEN20_TROOPMON_FQNAME, PEN20_TROOPMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_TURUIEMON_NAME, PEN20_TURUIEMON_ID, PEN20_TURUIEMON_FQID, PEN20_TURUIEMON_FQNAME, PEN20_TURUIEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_VAMDEMON_NAME, PEN20_VAMDEMON_ID, PEN20_VAMDEMON_FQID, PEN20_VAMDEMON_FQNAME, PEN20_VAMDEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_V_DRAMON_NAME, PEN20_V_DRAMON_ID, PEN20_V_DRAMON_FQID, PEN20_V_DRAMON_FQNAME, PEN20_V_DRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_VEMDEMON_NAME, PEN20_VEMDEMON_ID, PEN20_VEMDEMON_FQID, PEN20_VEMDEMON_FQNAME, PEN20_VEMDEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_VENOM_VAMDEMON_NAME, PEN20_VENOM_VAMDEMON_ID, PEN20_VENOM_VAMDEMON_FQID, PEN20_VENOM_VAMDEMON_FQNAME, PEN20_VENOM_VAMDEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_V_MON_NAME, PEN20_V_MON_ID, PEN20_V_MON_FQID, PEN20_V_MON_FQNAME, PEN20_V_MON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_VOLCANICDRAMON_NAME, PEN20_VOLCANICDRAMON_ID, PEN20_VOLCANICDRAMON_FQID, PEN20_VOLCANICDRAMON_FQNAME, PEN20_VOLCANICDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_VOLTOBAUTAMON_NAME, PEN20_VOLTOBAUTAMON_ID, PEN20_VOLTOBAUTAMON_FQID, PEN20_VOLTOBAUTAMON_FQNAME, PEN20_VOLTOBAUTAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_VORVOMON_NAME, PEN20_VORVOMON_ID, PEN20_VORVOMON_FQID, PEN20_VORVOMON_FQNAME, PEN20_VORVOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_WAR_GREYMON_NAME, PEN20_WAR_GREYMON_ID, PEN20_WAR_GREYMON_FQID, PEN20_WAR_GREYMON_FQNAME, PEN20_WAR_GREYMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_WARU_MOZAEMON_NAME, PEN20_WARU_MOZAEMON_ID, PEN20_WARU_MOZAEMON_FQID, PEN20_WARU_MOZAEMON_FQNAME, PEN20_WARU_MOZAEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_WERE_GARURUMON_NAME, PEN20_WERE_GARURUMON_ID, PEN20_WERE_GARURUMON_FQID, PEN20_WERE_GARURUMON_FQNAME, PEN20_WERE_GARURUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_WHAMON_NAME, PEN20_WHAMON_ID, PEN20_WHAMON_FQID, PEN20_WHAMON_FQNAME, PEN20_WHAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_WINGDRAMON_NAME, PEN20_WINGDRAMON_ID, PEN20_WINGDRAMON_FQID, PEN20_WINGDRAMON_FQNAME, PEN20_WINGDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_WIZARMON_NAME, PEN20_WIZARMON_ID, PEN20_WIZARMON_FQID, PEN20_WIZARMON_FQNAME, PEN20_WIZARMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_WOODMON_NAME, PEN20_WOODMON_ID, PEN20_WOODMON_FQID, PEN20_WOODMON_FQNAME, PEN20_WOODMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_XV_MON_NAME, PEN20_XV_MON_ID, PEN20_XV_MON_FQID, PEN20_XV_MON_FQNAME, PEN20_XV_MON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_ZERIMON_NAME, PEN20_ZERIMON_ID, PEN20_ZERIMON_FQID, PEN20_ZERIMON_FQNAME, PEN20_ZERIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        { PEN20_ZUDOMON_NAME, PEN20_ZUDOMON_ID, PEN20_ZUDOMON_FQID, PEN20_ZUDOMON_FQNAME, PEN20_ZUDOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },
        
    };
            inline static constexpr char ALT_PEN20_AERO_V_DRAMON_FQID_ARR[] = "pen20:aero_v_dramon";
    inline static constexpr const char* ALT_PEN20_AERO_V_DRAMON_FQID = ALT_PEN20_AERO_V_DRAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_AERO_V_DRAMON_FQID_LEN = sizeof(ALT_PEN20_AERO_V_DRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_AERO_V_DRAMON_FQNAME_ARR[] = "pen20:Aero V-dramon";
    inline static constexpr const char* ALT_PEN20_AERO_V_DRAMON_FQNAME = ALT_PEN20_AERO_V_DRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_AERO_V_DRAMON_FQNAME_LEN = sizeof(ALT_PEN20_AERO_V_DRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_AGUMON_HAKASE_FQID_ARR[] = "pen20:agumon_hakase";
    inline static constexpr const char* ALT_PEN20_AGUMON_HAKASE_FQID = ALT_PEN20_AGUMON_HAKASE_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_AGUMON_HAKASE_FQID_LEN = sizeof(ALT_PEN20_AGUMON_HAKASE_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_AGUMON_HAKASE_FQNAME_ARR[] = "pen20:Agumon Hakase";
    inline static constexpr const char* ALT_PEN20_AGUMON_HAKASE_FQNAME = ALT_PEN20_AGUMON_HAKASE_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_AGUMON_HAKASE_FQNAME_LEN = sizeof(ALT_PEN20_AGUMON_HAKASE_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_ALPHAMON_OURYUKEN_FQID_ARR[] = "pen20:alphamon_ouryuken";
    inline static constexpr const char* ALT_PEN20_ALPHAMON_OURYUKEN_FQID = ALT_PEN20_ALPHAMON_OURYUKEN_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_ALPHAMON_OURYUKEN_FQID_LEN = sizeof(ALT_PEN20_ALPHAMON_OURYUKEN_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_ALPHAMON_OURYUKEN_FQNAME_ARR[] = "pen20:Alphamon Ouryuken";
    inline static constexpr const char* ALT_PEN20_ALPHAMON_OURYUKEN_FQNAME = ALT_PEN20_ALPHAMON_OURYUKEN_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_ALPHAMON_OURYUKEN_FQNAME_LEN = sizeof(ALT_PEN20_ALPHAMON_OURYUKEN_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_ANDIRAMON_FQID_ARR[] = "pen20:andiramon";
    inline static constexpr const char* ALT_PEN20_ANDIRAMON_FQID = ALT_PEN20_ANDIRAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_ANDIRAMON_FQID_LEN = sizeof(ALT_PEN20_ANDIRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_ANDIRAMON_FQNAME_ARR[] = "pen20:Andiramon";
    inline static constexpr const char* ALT_PEN20_ANDIRAMON_FQNAME = ALT_PEN20_ANDIRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_ANDIRAMON_FQNAME_LEN = sizeof(ALT_PEN20_ANDIRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_ANDROMON_FQID_ARR[] = "pen20:andromon";
    inline static constexpr const char* ALT_PEN20_ANDROMON_FQID = ALT_PEN20_ANDROMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_ANDROMON_FQID_LEN = sizeof(ALT_PEN20_ANDROMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_ANDROMON_FQNAME_ARR[] = "pen20:Andromon";
    inline static constexpr const char* ALT_PEN20_ANDROMON_FQNAME = ALT_PEN20_ANDROMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_ANDROMON_FQNAME_LEN = sizeof(ALT_PEN20_ANDROMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_ANGEWOMON_FQID_ARR[] = "pen20:angewomon";
    inline static constexpr const char* ALT_PEN20_ANGEWOMON_FQID = ALT_PEN20_ANGEWOMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_ANGEWOMON_FQID_LEN = sizeof(ALT_PEN20_ANGEWOMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_ANGEWOMON_FQNAME_ARR[] = "pen20:Angewomon";
    inline static constexpr const char* ALT_PEN20_ANGEWOMON_FQNAME = ALT_PEN20_ANGEWOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_ANGEWOMON_FQNAME_LEN = sizeof(ALT_PEN20_ANGEWOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_ANOMALOCARIMON_FQID_ARR[] = "pen20:anomalocarimon";
    inline static constexpr const char* ALT_PEN20_ANOMALOCARIMON_FQID = ALT_PEN20_ANOMALOCARIMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_ANOMALOCARIMON_FQID_LEN = sizeof(ALT_PEN20_ANOMALOCARIMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_ANOMALOCARIMON_FQNAME_ARR[] = "pen20:Anomalocarimon";
    inline static constexpr const char* ALT_PEN20_ANOMALOCARIMON_FQNAME = ALT_PEN20_ANOMALOCARIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_ANOMALOCARIMON_FQNAME_LEN = sizeof(ALT_PEN20_ANOMALOCARIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_ARRESTERDRAMON_FQID_ARR[] = "pen20:arresterdramon";
    inline static constexpr const char* ALT_PEN20_ARRESTERDRAMON_FQID = ALT_PEN20_ARRESTERDRAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_ARRESTERDRAMON_FQID_LEN = sizeof(ALT_PEN20_ARRESTERDRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_ARRESTERDRAMON_FQNAME_ARR[] = "pen20:Arresterdramon";
    inline static constexpr const char* ALT_PEN20_ARRESTERDRAMON_FQNAME = ALT_PEN20_ARRESTERDRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_ARRESTERDRAMON_FQNAME_LEN = sizeof(ALT_PEN20_ARRESTERDRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_ASTAMON_FQID_ARR[] = "pen20:astamon";
    inline static constexpr const char* ALT_PEN20_ASTAMON_FQID = ALT_PEN20_ASTAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_ASTAMON_FQID_LEN = sizeof(ALT_PEN20_ASTAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_ASTAMON_FQNAME_ARR[] = "pen20:Astamon";
    inline static constexpr const char* ALT_PEN20_ASTAMON_FQNAME = ALT_PEN20_ASTAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_ASTAMON_FQNAME_LEN = sizeof(ALT_PEN20_ASTAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_ASTRAMON_FQID_ARR[] = "pen20:astramon";
    inline static constexpr const char* ALT_PEN20_ASTRAMON_FQID = ALT_PEN20_ASTRAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_ASTRAMON_FQID_LEN = sizeof(ALT_PEN20_ASTRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_ASTRAMON_FQNAME_ARR[] = "pen20:Astramon";
    inline static constexpr const char* ALT_PEN20_ASTRAMON_FQNAME = ALT_PEN20_ASTRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_ASTRAMON_FQNAME_LEN = sizeof(ALT_PEN20_ASTRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_ASURAMON_FQID_ARR[] = "pen20:asuramon";
    inline static constexpr const char* ALT_PEN20_ASURAMON_FQID = ALT_PEN20_ASURAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_ASURAMON_FQID_LEN = sizeof(ALT_PEN20_ASURAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_ASURAMON_FQNAME_ARR[] = "pen20:Asuramon";
    inline static constexpr const char* ALT_PEN20_ASURAMON_FQNAME = ALT_PEN20_ASURAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_ASURAMON_FQNAME_LEN = sizeof(ALT_PEN20_ASURAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_ATLUR_KABUTERIMON_FQID_ARR[] = "pen20:atlur_kabuterimon";
    inline static constexpr const char* ALT_PEN20_ATLUR_KABUTERIMON_FQID = ALT_PEN20_ATLUR_KABUTERIMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_ATLUR_KABUTERIMON_FQID_LEN = sizeof(ALT_PEN20_ATLUR_KABUTERIMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_ATLUR_KABUTERIMON_FQNAME_ARR[] = "pen20:Atlur Kabuterimon";
    inline static constexpr const char* ALT_PEN20_ATLUR_KABUTERIMON_FQNAME = ALT_PEN20_ATLUR_KABUTERIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_ATLUR_KABUTERIMON_FQNAME_LEN = sizeof(ALT_PEN20_ATLUR_KABUTERIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_BAALMON_FQID_ARR[] = "pen20:baalmon";
    inline static constexpr const char* ALT_PEN20_BAALMON_FQID = ALT_PEN20_BAALMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_BAALMON_FQID_LEN = sizeof(ALT_PEN20_BAALMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_BAALMON_FQNAME_ARR[] = "pen20:Baalmon";
    inline static constexpr const char* ALT_PEN20_BAALMON_FQNAME = ALT_PEN20_BAALMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_BAALMON_FQNAME_LEN = sizeof(ALT_PEN20_BAALMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_BAKEMON_FQID_ARR[] = "pen20:bakemon";
    inline static constexpr const char* ALT_PEN20_BAKEMON_FQID = ALT_PEN20_BAKEMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_BAKEMON_FQID_LEN = sizeof(ALT_PEN20_BAKEMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_BAKEMON_FQNAME_ARR[] = "pen20:Bakemon";
    inline static constexpr const char* ALT_PEN20_BAKEMON_FQNAME = ALT_PEN20_BAKEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_BAKEMON_FQNAME_LEN = sizeof(ALT_PEN20_BAKEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_BAKUMON_FQID_ARR[] = "pen20:bakumon";
    inline static constexpr const char* ALT_PEN20_BAKUMON_FQID = ALT_PEN20_BAKUMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_BAKUMON_FQID_LEN = sizeof(ALT_PEN20_BAKUMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_BAKUMON_FQNAME_ARR[] = "pen20:Bakumon";
    inline static constexpr const char* ALT_PEN20_BAKUMON_FQNAME = ALT_PEN20_BAKUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_BAKUMON_FQNAME_LEN = sizeof(ALT_PEN20_BAKUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_BANCHO_LEOMON_FQID_ARR[] = "pen20:bancho_leomon";
    inline static constexpr const char* ALT_PEN20_BANCHO_LEOMON_FQID = ALT_PEN20_BANCHO_LEOMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_BANCHO_LEOMON_FQID_LEN = sizeof(ALT_PEN20_BANCHO_LEOMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_BANCHO_LEOMON_FQNAME_ARR[] = "pen20:Bancho Leomon";
    inline static constexpr const char* ALT_PEN20_BANCHO_LEOMON_FQNAME = ALT_PEN20_BANCHO_LEOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_BANCHO_LEOMON_FQNAME_LEN = sizeof(ALT_PEN20_BANCHO_LEOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_BEELZEBUMON_BLAST_MODE_FQID_ARR[] = "pen20:beelzebumon_blast_mode";
    inline static constexpr const char* ALT_PEN20_BEELZEBUMON_BLAST_MODE_FQID = ALT_PEN20_BEELZEBUMON_BLAST_MODE_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_BEELZEBUMON_BLAST_MODE_FQID_LEN = sizeof(ALT_PEN20_BEELZEBUMON_BLAST_MODE_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_BEELZEBUMON_BLAST_MODE_FQNAME_ARR[] = "pen20:Beelzebumon Blast Mode";
    inline static constexpr const char* ALT_PEN20_BEELZEBUMON_BLAST_MODE_FQNAME = ALT_PEN20_BEELZEBUMON_BLAST_MODE_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_BEELZEBUMON_BLAST_MODE_FQNAME_LEN = sizeof(ALT_PEN20_BEELZEBUMON_BLAST_MODE_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_BEOWOLFMON_FQID_ARR[] = "pen20:beowolfmon";
    inline static constexpr const char* ALT_PEN20_BEOWOLFMON_FQID = ALT_PEN20_BEOWOLFMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_BEOWOLFMON_FQID_LEN = sizeof(ALT_PEN20_BEOWOLFMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_BEOWOLFMON_FQNAME_ARR[] = "pen20:Beowolfmon";
    inline static constexpr const char* ALT_PEN20_BEOWOLFMON_FQNAME = ALT_PEN20_BEOWOLFMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_BEOWOLFMON_FQNAME_LEN = sizeof(ALT_PEN20_BEOWOLFMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_BEOWULFMON_FQID_ARR[] = "pen20:beowulfmon";
    inline static constexpr const char* ALT_PEN20_BEOWULFMON_FQID = ALT_PEN20_BEOWULFMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_BEOWULFMON_FQID_LEN = sizeof(ALT_PEN20_BEOWULFMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_BEOWULFMON_FQNAME_ARR[] = "pen20:Beowulfmon";
    inline static constexpr const char* ALT_PEN20_BEOWULFMON_FQNAME = ALT_PEN20_BEOWULFMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_BEOWULFMON_FQNAME_LEN = sizeof(ALT_PEN20_BEOWULFMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_BIG_MAMEMON_FQID_ARR[] = "pen20:big_mamemon";
    inline static constexpr const char* ALT_PEN20_BIG_MAMEMON_FQID = ALT_PEN20_BIG_MAMEMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_BIG_MAMEMON_FQID_LEN = sizeof(ALT_PEN20_BIG_MAMEMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_BIG_MAMEMON_FQNAME_ARR[] = "pen20:Big Mamemon";
    inline static constexpr const char* ALT_PEN20_BIG_MAMEMON_FQNAME = ALT_PEN20_BIG_MAMEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_BIG_MAMEMON_FQNAME_LEN = sizeof(ALT_PEN20_BIG_MAMEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_BIRDRAMON_FQID_ARR[] = "pen20:birdramon";
    inline static constexpr const char* ALT_PEN20_BIRDRAMON_FQID = ALT_PEN20_BIRDRAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_BIRDRAMON_FQID_LEN = sizeof(ALT_PEN20_BIRDRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_BIRDRAMON_FQNAME_ARR[] = "pen20:Birdramon";
    inline static constexpr const char* ALT_PEN20_BIRDRAMON_FQNAME = ALT_PEN20_BIRDRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_BIRDRAMON_FQNAME_LEN = sizeof(ALT_PEN20_BIRDRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_BLOSSOMON_FQID_ARR[] = "pen20:blossomon";
    inline static constexpr const char* ALT_PEN20_BLOSSOMON_FQID = ALT_PEN20_BLOSSOMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_BLOSSOMON_FQID_LEN = sizeof(ALT_PEN20_BLOSSOMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_BLOSSOMON_FQNAME_ARR[] = "pen20:Blossomon";
    inline static constexpr const char* ALT_PEN20_BLOSSOMON_FQNAME = ALT_PEN20_BLOSSOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_BLOSSOMON_FQNAME_LEN = sizeof(ALT_PEN20_BLOSSOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_BOLTMON_FQID_ARR[] = "pen20:boltmon";
    inline static constexpr const char* ALT_PEN20_BOLTMON_FQID = ALT_PEN20_BOLTMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_BOLTMON_FQID_LEN = sizeof(ALT_PEN20_BOLTMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_BOLTMON_FQNAME_ARR[] = "pen20:Boltmon";
    inline static constexpr const char* ALT_PEN20_BOLTMON_FQNAME = ALT_PEN20_BOLTMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_BOLTMON_FQNAME_LEN = sizeof(ALT_PEN20_BOLTMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_BREAKDRAMON_FQID_ARR[] = "pen20:breakdramon";
    inline static constexpr const char* ALT_PEN20_BREAKDRAMON_FQID = ALT_PEN20_BREAKDRAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_BREAKDRAMON_FQID_LEN = sizeof(ALT_PEN20_BREAKDRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_BREAKDRAMON_FQNAME_ARR[] = "pen20:Breakdramon";
    inline static constexpr const char* ALT_PEN20_BREAKDRAMON_FQNAME = ALT_PEN20_BREAKDRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_BREAKDRAMON_FQNAME_LEN = sizeof(ALT_PEN20_BREAKDRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_BRYWELUDRAMON_FQID_ARR[] = "pen20:bryweludramon";
    inline static constexpr const char* ALT_PEN20_BRYWELUDRAMON_FQID = ALT_PEN20_BRYWELUDRAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_BRYWELUDRAMON_FQID_LEN = sizeof(ALT_PEN20_BRYWELUDRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_BRYWELUDRAMON_FQNAME_ARR[] = "pen20:Bryweludramon";
    inline static constexpr const char* ALT_PEN20_BRYWELUDRAMON_FQNAME = ALT_PEN20_BRYWELUDRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_BRYWELUDRAMON_FQNAME_LEN = sizeof(ALT_PEN20_BRYWELUDRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_BUBBMON_FQID_ARR[] = "pen20:bubbmon";
    inline static constexpr const char* ALT_PEN20_BUBBMON_FQID = ALT_PEN20_BUBBMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_BUBBMON_FQID_LEN = sizeof(ALT_PEN20_BUBBMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_BUBBMON_FQNAME_ARR[] = "pen20:Bubbmon";
    inline static constexpr const char* ALT_PEN20_BUBBMON_FQNAME = ALT_PEN20_BUBBMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_BUBBMON_FQNAME_LEN = sizeof(ALT_PEN20_BUBBMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_BUDMON_FQID_ARR[] = "pen20:budmon";
    inline static constexpr const char* ALT_PEN20_BUDMON_FQID = ALT_PEN20_BUDMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_BUDMON_FQID_LEN = sizeof(ALT_PEN20_BUDMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_BUDMON_FQNAME_ARR[] = "pen20:Budmon";
    inline static constexpr const char* ALT_PEN20_BUDMON_FQNAME = ALT_PEN20_BUDMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_BUDMON_FQNAME_LEN = sizeof(ALT_PEN20_BUDMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_BUSHI_AGUMON_FQID_ARR[] = "pen20:bushi_agumon";
    inline static constexpr const char* ALT_PEN20_BUSHI_AGUMON_FQID = ALT_PEN20_BUSHI_AGUMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_BUSHI_AGUMON_FQID_LEN = sizeof(ALT_PEN20_BUSHI_AGUMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_BUSHI_AGUMON_FQNAME_ARR[] = "pen20:Bushi Agumon";
    inline static constexpr const char* ALT_PEN20_BUSHI_AGUMON_FQNAME = ALT_PEN20_BUSHI_AGUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_BUSHI_AGUMON_FQNAME_LEN = sizeof(ALT_PEN20_BUSHI_AGUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_CANDMON_FQID_ARR[] = "pen20:candmon";
    inline static constexpr const char* ALT_PEN20_CANDMON_FQID = ALT_PEN20_CANDMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_CANDMON_FQID_LEN = sizeof(ALT_PEN20_CANDMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_CANDMON_FQNAME_ARR[] = "pen20:Candmon";
    inline static constexpr const char* ALT_PEN20_CANDMON_FQNAME = ALT_PEN20_CANDMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_CANDMON_FQNAME_LEN = sizeof(ALT_PEN20_CANDMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_CAPRIMON_FQID_ARR[] = "pen20:caprimon";
    inline static constexpr const char* ALT_PEN20_CAPRIMON_FQID = ALT_PEN20_CAPRIMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_CAPRIMON_FQID_LEN = sizeof(ALT_PEN20_CAPRIMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_CAPRIMON_FQNAME_ARR[] = "pen20:Caprimon";
    inline static constexpr const char* ALT_PEN20_CAPRIMON_FQNAME = ALT_PEN20_CAPRIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_CAPRIMON_FQNAME_LEN = sizeof(ALT_PEN20_CAPRIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_CHAOSMON_FQID_ARR[] = "pen20:chaosmon";
    inline static constexpr const char* ALT_PEN20_CHAOSMON_FQID = ALT_PEN20_CHAOSMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_CHAOSMON_FQID_LEN = sizeof(ALT_PEN20_CHAOSMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_CHAOSMON_FQNAME_ARR[] = "pen20:Chaosmon";
    inline static constexpr const char* ALT_PEN20_CHAOSMON_FQNAME = ALT_PEN20_CHAOSMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_CHAOSMON_FQNAME_LEN = sizeof(ALT_PEN20_CHAOSMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_CHERUBIMON_FQID_ARR[] = "pen20:cherubimon";
    inline static constexpr const char* ALT_PEN20_CHERUBIMON_FQID = ALT_PEN20_CHERUBIMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_CHERUBIMON_FQID_LEN = sizeof(ALT_PEN20_CHERUBIMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_CHERUBIMON_FQNAME_ARR[] = "pen20:Cherubimon";
    inline static constexpr const char* ALT_PEN20_CHERUBIMON_FQNAME = ALT_PEN20_CHERUBIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_CHERUBIMON_FQNAME_LEN = sizeof(ALT_PEN20_CHERUBIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_CHIBIMON_FQID_ARR[] = "pen20:chibimon";
    inline static constexpr const char* ALT_PEN20_CHIBIMON_FQID = ALT_PEN20_CHIBIMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_CHIBIMON_FQID_LEN = sizeof(ALT_PEN20_CHIBIMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_CHIBIMON_FQNAME_ARR[] = "pen20:Chibimon";
    inline static constexpr const char* ALT_PEN20_CHIBIMON_FQNAME = ALT_PEN20_CHIBIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_CHIBIMON_FQNAME_LEN = sizeof(ALT_PEN20_CHIBIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_CHICOMON_FQID_ARR[] = "pen20:chicomon";
    inline static constexpr const char* ALT_PEN20_CHICOMON_FQID = ALT_PEN20_CHICOMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_CHICOMON_FQID_LEN = sizeof(ALT_PEN20_CHICOMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_CHICOMON_FQNAME_ARR[] = "pen20:Chicomon";
    inline static constexpr const char* ALT_PEN20_CHICOMON_FQNAME = ALT_PEN20_CHICOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_CHICOMON_FQNAME_LEN = sizeof(ALT_PEN20_CHICOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_CHOROMON_FQID_ARR[] = "pen20:choromon";
    inline static constexpr const char* ALT_PEN20_CHOROMON_FQID = ALT_PEN20_CHOROMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_CHOROMON_FQID_LEN = sizeof(ALT_PEN20_CHOROMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_CHOROMON_FQNAME_ARR[] = "pen20:Choromon";
    inline static constexpr const char* ALT_PEN20_CHOROMON_FQNAME = ALT_PEN20_CHOROMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_CHOROMON_FQNAME_LEN = sizeof(ALT_PEN20_CHOROMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_CLOCKMON_FQID_ARR[] = "pen20:clockmon";
    inline static constexpr const char* ALT_PEN20_CLOCKMON_FQID = ALT_PEN20_CLOCKMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_CLOCKMON_FQID_LEN = sizeof(ALT_PEN20_CLOCKMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_CLOCKMON_FQNAME_ARR[] = "pen20:Clockmon";
    inline static constexpr const char* ALT_PEN20_CLOCKMON_FQNAME = ALT_PEN20_CLOCKMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_CLOCKMON_FQNAME_LEN = sizeof(ALT_PEN20_CLOCKMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_COCOMON_FQID_ARR[] = "pen20:cocomon";
    inline static constexpr const char* ALT_PEN20_COCOMON_FQID = ALT_PEN20_COCOMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_COCOMON_FQID_LEN = sizeof(ALT_PEN20_COCOMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_COCOMON_FQNAME_ARR[] = "pen20:Cocomon";
    inline static constexpr const char* ALT_PEN20_COCOMON_FQNAME = ALT_PEN20_COCOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_COCOMON_FQNAME_LEN = sizeof(ALT_PEN20_COCOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_COELAMON_FQID_ARR[] = "pen20:coelamon";
    inline static constexpr const char* ALT_PEN20_COELAMON_FQID = ALT_PEN20_COELAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_COELAMON_FQID_LEN = sizeof(ALT_PEN20_COELAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_COELAMON_FQNAME_ARR[] = "pen20:Coelamon";
    inline static constexpr const char* ALT_PEN20_COELAMON_FQNAME = ALT_PEN20_COELAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_COELAMON_FQNAME_LEN = sizeof(ALT_PEN20_COELAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_COREDRAMON_BLUE_FQID_ARR[] = "pen20:coredramon_blue";
    inline static constexpr const char* ALT_PEN20_COREDRAMON_BLUE_FQID = ALT_PEN20_COREDRAMON_BLUE_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_COREDRAMON_BLUE_FQID_LEN = sizeof(ALT_PEN20_COREDRAMON_BLUE_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_COREDRAMON_BLUE_FQNAME_ARR[] = "pen20:Coredramon (Blue)";
    inline static constexpr const char* ALT_PEN20_COREDRAMON_BLUE_FQNAME = ALT_PEN20_COREDRAMON_BLUE_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_COREDRAMON_BLUE_FQNAME_LEN = sizeof(ALT_PEN20_COREDRAMON_BLUE_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_COREDRAMON_GREEN_FQID_ARR[] = "pen20:coredramon_green";
    inline static constexpr const char* ALT_PEN20_COREDRAMON_GREEN_FQID = ALT_PEN20_COREDRAMON_GREEN_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_COREDRAMON_GREEN_FQID_LEN = sizeof(ALT_PEN20_COREDRAMON_GREEN_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_COREDRAMON_GREEN_FQNAME_ARR[] = "pen20:Coredramon (Green)";
    inline static constexpr const char* ALT_PEN20_COREDRAMON_GREEN_FQNAME = ALT_PEN20_COREDRAMON_GREEN_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_COREDRAMON_GREEN_FQNAME_LEN = sizeof(ALT_PEN20_COREDRAMON_GREEN_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_COTSUCOMON_FQID_ARR[] = "pen20:cotsucomon";
    inline static constexpr const char* ALT_PEN20_COTSUCOMON_FQID = ALT_PEN20_COTSUCOMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_COTSUCOMON_FQID_LEN = sizeof(ALT_PEN20_COTSUCOMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_COTSUCOMON_FQNAME_ARR[] = "pen20:Cotsucomon";
    inline static constexpr const char* ALT_PEN20_COTSUCOMON_FQNAME = ALT_PEN20_COTSUCOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_COTSUCOMON_FQNAME_LEN = sizeof(ALT_PEN20_COTSUCOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_CYBERDRAMON_FQID_ARR[] = "pen20:cyberdramon";
    inline static constexpr const char* ALT_PEN20_CYBERDRAMON_FQID = ALT_PEN20_CYBERDRAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_CYBERDRAMON_FQID_LEN = sizeof(ALT_PEN20_CYBERDRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_CYBERDRAMON_FQNAME_ARR[] = "pen20:Cyberdramon";
    inline static constexpr const char* ALT_PEN20_CYBERDRAMON_FQNAME = ALT_PEN20_CYBERDRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_CYBERDRAMON_FQNAME_LEN = sizeof(ALT_PEN20_CYBERDRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_DAGOMON_FQID_ARR[] = "pen20:dagomon";
    inline static constexpr const char* ALT_PEN20_DAGOMON_FQID = ALT_PEN20_DAGOMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_DAGOMON_FQID_LEN = sizeof(ALT_PEN20_DAGOMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_DAGOMON_FQNAME_ARR[] = "pen20:Dagomon";
    inline static constexpr const char* ALT_PEN20_DAGOMON_FQNAME = ALT_PEN20_DAGOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_DAGOMON_FQNAME_LEN = sizeof(ALT_PEN20_DAGOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_DARKDRAMON_FQID_ARR[] = "pen20:darkdramon";
    inline static constexpr const char* ALT_PEN20_DARKDRAMON_FQID = ALT_PEN20_DARKDRAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_DARKDRAMON_FQID_LEN = sizeof(ALT_PEN20_DARKDRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_DARKDRAMON_FQNAME_ARR[] = "pen20:Darkdramon";
    inline static constexpr const char* ALT_PEN20_DARKDRAMON_FQNAME = ALT_PEN20_DARKDRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_DARKDRAMON_FQNAME_LEN = sizeof(ALT_PEN20_DARKDRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_DARK_KNIGHTMON_FQID_ARR[] = "pen20:dark_knightmon";
    inline static constexpr const char* ALT_PEN20_DARK_KNIGHTMON_FQID = ALT_PEN20_DARK_KNIGHTMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_DARK_KNIGHTMON_FQID_LEN = sizeof(ALT_PEN20_DARK_KNIGHTMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_DARK_KNIGHTMON_FQNAME_ARR[] = "pen20:Dark Knightmon";
    inline static constexpr const char* ALT_PEN20_DARK_KNIGHTMON_FQNAME = ALT_PEN20_DARK_KNIGHTMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_DARK_KNIGHTMON_FQNAME_LEN = sizeof(ALT_PEN20_DARK_KNIGHTMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_DEATH_MERAMON_FQID_ARR[] = "pen20:death_meramon";
    inline static constexpr const char* ALT_PEN20_DEATH_MERAMON_FQID = ALT_PEN20_DEATH_MERAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_DEATH_MERAMON_FQID_LEN = sizeof(ALT_PEN20_DEATH_MERAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_DEATH_MERAMON_FQNAME_ARR[] = "pen20:Death Meramon";
    inline static constexpr const char* ALT_PEN20_DEATH_MERAMON_FQNAME = ALT_PEN20_DEATH_MERAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_DEATH_MERAMON_FQNAME_LEN = sizeof(ALT_PEN20_DEATH_MERAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_DELUMON_FQID_ARR[] = "pen20:delumon";
    inline static constexpr const char* ALT_PEN20_DELUMON_FQID = ALT_PEN20_DELUMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_DELUMON_FQID_LEN = sizeof(ALT_PEN20_DELUMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_DELUMON_FQNAME_ARR[] = "pen20:Delumon";
    inline static constexpr const char* ALT_PEN20_DELUMON_FQNAME = ALT_PEN20_DELUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_DELUMON_FQNAME_LEN = sizeof(ALT_PEN20_DELUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_DEVIDRAMON_FQID_ARR[] = "pen20:devidramon";
    inline static constexpr const char* ALT_PEN20_DEVIDRAMON_FQID = ALT_PEN20_DEVIDRAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_DEVIDRAMON_FQID_LEN = sizeof(ALT_PEN20_DEVIDRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_DEVIDRAMON_FQNAME_ARR[] = "pen20:Devidramon";
    inline static constexpr const char* ALT_PEN20_DEVIDRAMON_FQNAME = ALT_PEN20_DEVIDRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_DEVIDRAMON_FQNAME_LEN = sizeof(ALT_PEN20_DEVIDRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_DEVIMON_FQID_ARR[] = "pen20:devimon";
    inline static constexpr const char* ALT_PEN20_DEVIMON_FQID = ALT_PEN20_DEVIMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_DEVIMON_FQID_LEN = sizeof(ALT_PEN20_DEVIMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_DEVIMON_FQNAME_ARR[] = "pen20:Devimon";
    inline static constexpr const char* ALT_PEN20_DEVIMON_FQNAME = ALT_PEN20_DEVIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_DEVIMON_FQNAME_LEN = sizeof(ALT_PEN20_DEVIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_DOKUGUMON_FQID_ARR[] = "pen20:dokugumon";
    inline static constexpr const char* ALT_PEN20_DOKUGUMON_FQID = ALT_PEN20_DOKUGUMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_DOKUGUMON_FQID_LEN = sizeof(ALT_PEN20_DOKUGUMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_DOKUGUMON_FQNAME_ARR[] = "pen20:Dokugumon";
    inline static constexpr const char* ALT_PEN20_DOKUGUMON_FQNAME = ALT_PEN20_DOKUGUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_DOKUGUMON_FQNAME_LEN = sizeof(ALT_PEN20_DOKUGUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_DORUGORAMON_FQID_ARR[] = "pen20:dorugoramon";
    inline static constexpr const char* ALT_PEN20_DORUGORAMON_FQID = ALT_PEN20_DORUGORAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_DORUGORAMON_FQID_LEN = sizeof(ALT_PEN20_DORUGORAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_DORUGORAMON_FQNAME_ARR[] = "pen20:DORUgoramon";
    inline static constexpr const char* ALT_PEN20_DORUGORAMON_FQNAME = ALT_PEN20_DORUGORAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_DORUGORAMON_FQNAME_LEN = sizeof(ALT_PEN20_DORUGORAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_DURAMON_FQID_ARR[] = "pen20:duramon";
    inline static constexpr const char* ALT_PEN20_DURAMON_FQID = ALT_PEN20_DURAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_DURAMON_FQID_LEN = sizeof(ALT_PEN20_DURAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_DURAMON_FQNAME_ARR[] = "pen20:Duramon";
    inline static constexpr const char* ALT_PEN20_DURAMON_FQNAME = ALT_PEN20_DURAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_DURAMON_FQNAME_LEN = sizeof(ALT_PEN20_DURAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_DURANDAMON_FQID_ARR[] = "pen20:durandamon";
    inline static constexpr const char* ALT_PEN20_DURANDAMON_FQID = ALT_PEN20_DURANDAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_DURANDAMON_FQID_LEN = sizeof(ALT_PEN20_DURANDAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_DURANDAMON_FQNAME_ARR[] = "pen20:Durandamon";
    inline static constexpr const char* ALT_PEN20_DURANDAMON_FQNAME = ALT_PEN20_DURANDAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_DURANDAMON_FQNAME_LEN = sizeof(ALT_PEN20_DURANDAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_EBIDRAMON_FQID_ARR[] = "pen20:ebidramon";
    inline static constexpr const char* ALT_PEN20_EBIDRAMON_FQID = ALT_PEN20_EBIDRAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_EBIDRAMON_FQID_LEN = sizeof(ALT_PEN20_EBIDRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_EBIDRAMON_FQNAME_ARR[] = "pen20:Ebidramon";
    inline static constexpr const char* ALT_PEN20_EBIDRAMON_FQNAME = ALT_PEN20_EBIDRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_EBIDRAMON_FQNAME_LEN = sizeof(ALT_PEN20_EBIDRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_ETEMON_FQID_ARR[] = "pen20:etemon";
    inline static constexpr const char* ALT_PEN20_ETEMON_FQID = ALT_PEN20_ETEMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_ETEMON_FQID_LEN = sizeof(ALT_PEN20_ETEMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_ETEMON_FQNAME_ARR[] = "pen20:Etemon";
    inline static constexpr const char* ALT_PEN20_ETEMON_FQNAME = ALT_PEN20_ETEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_ETEMON_FQNAME_LEN = sizeof(ALT_PEN20_ETEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_EXAMON_FQID_ARR[] = "pen20:examon";
    inline static constexpr const char* ALT_PEN20_EXAMON_FQID = ALT_PEN20_EXAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_EXAMON_FQID_LEN = sizeof(ALT_PEN20_EXAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_EXAMON_FQNAME_ARR[] = "pen20:Examon";
    inline static constexpr const char* ALT_PEN20_EXAMON_FQNAME = ALT_PEN20_EXAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_EXAMON_FQNAME_LEN = sizeof(ALT_PEN20_EXAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_FANTOMON_FQID_ARR[] = "pen20:fantomon";
    inline static constexpr const char* ALT_PEN20_FANTOMON_FQID = ALT_PEN20_FANTOMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_FANTOMON_FQID_LEN = sizeof(ALT_PEN20_FANTOMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_FANTOMON_FQNAME_ARR[] = "pen20:Fantomon";
    inline static constexpr const char* ALT_PEN20_FANTOMON_FQNAME = ALT_PEN20_FANTOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_FANTOMON_FQNAME_LEN = sizeof(ALT_PEN20_FANTOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_FLORAMON_FQID_ARR[] = "pen20:floramon";
    inline static constexpr const char* ALT_PEN20_FLORAMON_FQID = ALT_PEN20_FLORAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_FLORAMON_FQID_LEN = sizeof(ALT_PEN20_FLORAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_FLORAMON_FQNAME_ARR[] = "pen20:Floramon";
    inline static constexpr const char* ALT_PEN20_FLORAMON_FQNAME = ALT_PEN20_FLORAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_FLORAMON_FQNAME_LEN = sizeof(ALT_PEN20_FLORAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_FUFUMON_FQID_ARR[] = "pen20:fufumon";
    inline static constexpr const char* ALT_PEN20_FUFUMON_FQID = ALT_PEN20_FUFUMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_FUFUMON_FQID_LEN = sizeof(ALT_PEN20_FUFUMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_FUFUMON_FQNAME_ARR[] = "pen20:Fufumon";
    inline static constexpr const char* ALT_PEN20_FUFUMON_FQNAME = ALT_PEN20_FUFUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_FUFUMON_FQNAME_LEN = sizeof(ALT_PEN20_FUFUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_GALGOMON_FQID_ARR[] = "pen20:galgomon";
    inline static constexpr const char* ALT_PEN20_GALGOMON_FQID = ALT_PEN20_GALGOMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_GALGOMON_FQID_LEN = sizeof(ALT_PEN20_GALGOMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_GALGOMON_FQNAME_ARR[] = "pen20:Galgomon";
    inline static constexpr const char* ALT_PEN20_GALGOMON_FQNAME = ALT_PEN20_GALGOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_GALGOMON_FQNAME_LEN = sizeof(ALT_PEN20_GALGOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_GANIMON_FQID_ARR[] = "pen20:ganimon";
    inline static constexpr const char* ALT_PEN20_GANIMON_FQID = ALT_PEN20_GANIMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_GANIMON_FQID_LEN = sizeof(ALT_PEN20_GANIMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_GANIMON_FQNAME_ARR[] = "pen20:Ganimon";
    inline static constexpr const char* ALT_PEN20_GANIMON_FQNAME = ALT_PEN20_GANIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_GANIMON_FQNAME_LEN = sizeof(ALT_PEN20_GANIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_GARUDAMON_FQID_ARR[] = "pen20:garudamon";
    inline static constexpr const char* ALT_PEN20_GARUDAMON_FQID = ALT_PEN20_GARUDAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_GARUDAMON_FQID_LEN = sizeof(ALT_PEN20_GARUDAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_GARUDAMON_FQNAME_ARR[] = "pen20:Garudamon";
    inline static constexpr const char* ALT_PEN20_GARUDAMON_FQNAME = ALT_PEN20_GARUDAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_GARUDAMON_FQNAME_LEN = sizeof(ALT_PEN20_GARUDAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_GARURUMON_FQID_ARR[] = "pen20:garurumon";
    inline static constexpr const char* ALT_PEN20_GARURUMON_FQID = ALT_PEN20_GARURUMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_GARURUMON_FQID_LEN = sizeof(ALT_PEN20_GARURUMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_GARURUMON_FQNAME_ARR[] = "pen20:Garurumon";
    inline static constexpr const char* ALT_PEN20_GARURUMON_FQNAME = ALT_PEN20_GARURUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_GARURUMON_FQNAME_LEN = sizeof(ALT_PEN20_GARURUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_GEKOMON_FQID_ARR[] = "pen20:gekomon";
    inline static constexpr const char* ALT_PEN20_GEKOMON_FQID = ALT_PEN20_GEKOMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_GEKOMON_FQID_LEN = sizeof(ALT_PEN20_GEKOMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_GEKOMON_FQNAME_ARR[] = "pen20:Gekomon";
    inline static constexpr const char* ALT_PEN20_GEKOMON_FQNAME = ALT_PEN20_GEKOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_GEKOMON_FQNAME_LEN = sizeof(ALT_PEN20_GEKOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_GERBEMON_FQID_ARR[] = "pen20:gerbemon";
    inline static constexpr const char* ALT_PEN20_GERBEMON_FQID = ALT_PEN20_GERBEMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_GERBEMON_FQID_LEN = sizeof(ALT_PEN20_GERBEMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_GERBEMON_FQNAME_ARR[] = "pen20:Gerbemon";
    inline static constexpr const char* ALT_PEN20_GERBEMON_FQNAME = ALT_PEN20_GERBEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_GERBEMON_FQNAME_LEN = sizeof(ALT_PEN20_GERBEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_GESOMON_FQID_ARR[] = "pen20:gesomon";
    inline static constexpr const char* ALT_PEN20_GESOMON_FQID = ALT_PEN20_GESOMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_GESOMON_FQID_LEN = sizeof(ALT_PEN20_GESOMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_GESOMON_FQNAME_ARR[] = "pen20:Gesomon";
    inline static constexpr const char* ALT_PEN20_GESOMON_FQNAME = ALT_PEN20_GESOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_GESOMON_FQNAME_LEN = sizeof(ALT_PEN20_GESOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_GINRYUMON_FQID_ARR[] = "pen20:ginryumon";
    inline static constexpr const char* ALT_PEN20_GINRYUMON_FQID = ALT_PEN20_GINRYUMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_GINRYUMON_FQID_LEN = sizeof(ALT_PEN20_GINRYUMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_GINRYUMON_FQNAME_ARR[] = "pen20:Ginryumon";
    inline static constexpr const char* ALT_PEN20_GINRYUMON_FQNAME = ALT_PEN20_GINRYUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_GINRYUMON_FQNAME_LEN = sizeof(ALT_PEN20_GINRYUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_GOMAMON_FQID_ARR[] = "pen20:gomamon";
    inline static constexpr const char* ALT_PEN20_GOMAMON_FQID = ALT_PEN20_GOMAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_GOMAMON_FQID_LEN = sizeof(ALT_PEN20_GOMAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_GOMAMON_FQNAME_ARR[] = "pen20:Gomamon";
    inline static constexpr const char* ALT_PEN20_GOMAMON_FQNAME = ALT_PEN20_GOMAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_GOMAMON_FQNAME_LEN = sizeof(ALT_PEN20_GOMAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_GOTTSUMON_FQID_ARR[] = "pen20:gottsumon";
    inline static constexpr const char* ALT_PEN20_GOTTSUMON_FQID = ALT_PEN20_GOTTSUMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_GOTTSUMON_FQID_LEN = sizeof(ALT_PEN20_GOTTSUMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_GOTTSUMON_FQNAME_ARR[] = "pen20:Gottsumon";
    inline static constexpr const char* ALT_PEN20_GOTTSUMON_FQNAME = ALT_PEN20_GOTTSUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_GOTTSUMON_FQNAME_LEN = sizeof(ALT_PEN20_GOTTSUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_GREYMON_FQID_ARR[] = "pen20:greymon";
    inline static constexpr const char* ALT_PEN20_GREYMON_FQID = ALT_PEN20_GREYMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_GREYMON_FQID_LEN = sizeof(ALT_PEN20_GREYMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_GREYMON_FQNAME_ARR[] = "pen20:Greymon";
    inline static constexpr const char* ALT_PEN20_GREYMON_FQNAME = ALT_PEN20_GREYMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_GREYMON_FQNAME_LEN = sizeof(ALT_PEN20_GREYMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_GRIFFOMON_FQID_ARR[] = "pen20:griffomon";
    inline static constexpr const char* ALT_PEN20_GRIFFOMON_FQID = ALT_PEN20_GRIFFOMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_GRIFFOMON_FQID_LEN = sizeof(ALT_PEN20_GRIFFOMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_GRIFFOMON_FQNAME_ARR[] = "pen20:Griffomon";
    inline static constexpr const char* ALT_PEN20_GRIFFOMON_FQNAME = ALT_PEN20_GRIFFOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_GRIFFOMON_FQNAME_LEN = sizeof(ALT_PEN20_GRIFFOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_GROUNDRAMON_FQID_ARR[] = "pen20:groundramon";
    inline static constexpr const char* ALT_PEN20_GROUNDRAMON_FQID = ALT_PEN20_GROUNDRAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_GROUNDRAMON_FQID_LEN = sizeof(ALT_PEN20_GROUNDRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_GROUNDRAMON_FQNAME_ARR[] = "pen20:Groundramon";
    inline static constexpr const char* ALT_PEN20_GROUNDRAMON_FQNAME = ALT_PEN20_GROUNDRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_GROUNDRAMON_FQNAME_LEN = sizeof(ALT_PEN20_GROUNDRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_GROWMON_FQID_ARR[] = "pen20:growmon";
    inline static constexpr const char* ALT_PEN20_GROWMON_FQID = ALT_PEN20_GROWMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_GROWMON_FQID_LEN = sizeof(ALT_PEN20_GROWMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_GROWMON_FQNAME_ARR[] = "pen20:Growmon";
    inline static constexpr const char* ALT_PEN20_GROWMON_FQNAME = ALT_PEN20_GROWMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_GROWMON_FQNAME_LEN = sizeof(ALT_PEN20_GROWMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_GUARDROMON_FQID_ARR[] = "pen20:guardromon";
    inline static constexpr const char* ALT_PEN20_GUARDROMON_FQID = ALT_PEN20_GUARDROMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_GUARDROMON_FQID_LEN = sizeof(ALT_PEN20_GUARDROMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_GUARDROMON_FQNAME_ARR[] = "pen20:Guardromon";
    inline static constexpr const char* ALT_PEN20_GUARDROMON_FQNAME = ALT_PEN20_GUARDROMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_GUARDROMON_FQNAME_LEN = sizeof(ALT_PEN20_GUARDROMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_GUIMON_FQID_ARR[] = "pen20:guimon";
    inline static constexpr const char* ALT_PEN20_GUIMON_FQID = ALT_PEN20_GUIMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_GUIMON_FQID_LEN = sizeof(ALT_PEN20_GUIMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_GUIMON_FQNAME_ARR[] = "pen20:Guimon";
    inline static constexpr const char* ALT_PEN20_GUIMON_FQNAME = ALT_PEN20_GUIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_GUIMON_FQNAME_LEN = sizeof(ALT_PEN20_GUIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_GUMMYMON_FQID_ARR[] = "pen20:gummymon";
    inline static constexpr const char* ALT_PEN20_GUMMYMON_FQID = ALT_PEN20_GUMMYMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_GUMMYMON_FQID_LEN = sizeof(ALT_PEN20_GUMMYMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_GUMMYMON_FQNAME_ARR[] = "pen20:Gummymon";
    inline static constexpr const char* ALT_PEN20_GUMMYMON_FQNAME = ALT_PEN20_GUMMYMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_GUMMYMON_FQNAME_LEN = sizeof(ALT_PEN20_GUMMYMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_HAGURUMON_FQID_ARR[] = "pen20:hagurumon";
    inline static constexpr const char* ALT_PEN20_HAGURUMON_FQID = ALT_PEN20_HAGURUMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_HAGURUMON_FQID_LEN = sizeof(ALT_PEN20_HAGURUMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_HAGURUMON_FQNAME_ARR[] = "pen20:Hagurumon";
    inline static constexpr const char* ALT_PEN20_HAGURUMON_FQNAME = ALT_PEN20_HAGURUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_HAGURUMON_FQNAME_LEN = sizeof(ALT_PEN20_HAGURUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_HANGYMON_FQID_ARR[] = "pen20:hangymon";
    inline static constexpr const char* ALT_PEN20_HANGYMON_FQID = ALT_PEN20_HANGYMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_HANGYMON_FQID_LEN = sizeof(ALT_PEN20_HANGYMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_HANGYMON_FQNAME_ARR[] = "pen20:Hangymon";
    inline static constexpr const char* ALT_PEN20_HANGYMON_FQNAME = ALT_PEN20_HANGYMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_HANGYMON_FQNAME_LEN = sizeof(ALT_PEN20_HANGYMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_HANGYOMON_FQID_ARR[] = "pen20:hangyomon";
    inline static constexpr const char* ALT_PEN20_HANGYOMON_FQID = ALT_PEN20_HANGYOMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_HANGYOMON_FQID_LEN = sizeof(ALT_PEN20_HANGYOMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_HANGYOMON_FQNAME_ARR[] = "pen20:Hangyomon";
    inline static constexpr const char* ALT_PEN20_HANGYOMON_FQNAME = ALT_PEN20_HANGYOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_HANGYOMON_FQNAME_LEN = sizeof(ALT_PEN20_HANGYOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_HANUMON_FQID_ARR[] = "pen20:hanumon";
    inline static constexpr const char* ALT_PEN20_HANUMON_FQID = ALT_PEN20_HANUMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_HANUMON_FQID_LEN = sizeof(ALT_PEN20_HANUMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_HANUMON_FQNAME_ARR[] = "pen20:Hanumon";
    inline static constexpr const char* ALT_PEN20_HANUMON_FQNAME = ALT_PEN20_HANUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_HANUMON_FQNAME_LEN = sizeof(ALT_PEN20_HANUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_HERAKLE_KABUTERIMON_FQID_ARR[] = "pen20:herakle_kabuterimon";
    inline static constexpr const char* ALT_PEN20_HERAKLE_KABUTERIMON_FQID = ALT_PEN20_HERAKLE_KABUTERIMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_HERAKLE_KABUTERIMON_FQID_LEN = sizeof(ALT_PEN20_HERAKLE_KABUTERIMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_HERAKLE_KABUTERIMON_FQNAME_ARR[] = "pen20:Herakle Kabuterimon";
    inline static constexpr const char* ALT_PEN20_HERAKLE_KABUTERIMON_FQNAME = ALT_PEN20_HERAKLE_KABUTERIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_HERAKLE_KABUTERIMON_FQNAME_LEN = sizeof(ALT_PEN20_HERAKLE_KABUTERIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_HERKULE_KABUTERIMON_FQID_ARR[] = "pen20:herkule_kabuterimon";
    inline static constexpr const char* ALT_PEN20_HERKULE_KABUTERIMON_FQID = ALT_PEN20_HERKULE_KABUTERIMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_HERKULE_KABUTERIMON_FQID_LEN = sizeof(ALT_PEN20_HERKULE_KABUTERIMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_HERKULE_KABUTERIMON_FQNAME_ARR[] = "pen20:Herkule Kabuterimon";
    inline static constexpr const char* ALT_PEN20_HERKULE_KABUTERIMON_FQNAME = ALT_PEN20_HERKULE_KABUTERIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_HERKULE_KABUTERIMON_FQNAME_LEN = sizeof(ALT_PEN20_HERKULE_KABUTERIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_HISYARYUMON_FQID_ARR[] = "pen20:hisyaryumon";
    inline static constexpr const char* ALT_PEN20_HISYARYUMON_FQID = ALT_PEN20_HISYARYUMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_HISYARYUMON_FQID_LEN = sizeof(ALT_PEN20_HISYARYUMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_HISYARYUMON_FQNAME_ARR[] = "pen20:Hisyaryumon";
    inline static constexpr const char* ALT_PEN20_HISYARYUMON_FQNAME = ALT_PEN20_HISYARYUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_HISYARYUMON_FQNAME_LEN = sizeof(ALT_PEN20_HISYARYUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_HOLY_ANGEMON_FQID_ARR[] = "pen20:holy_angemon";
    inline static constexpr const char* ALT_PEN20_HOLY_ANGEMON_FQID = ALT_PEN20_HOLY_ANGEMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_HOLY_ANGEMON_FQID_LEN = sizeof(ALT_PEN20_HOLY_ANGEMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_HOLY_ANGEMON_FQNAME_ARR[] = "pen20:Holy Angemon";
    inline static constexpr const char* ALT_PEN20_HOLY_ANGEMON_FQNAME = ALT_PEN20_HOLY_ANGEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_HOLY_ANGEMON_FQNAME_LEN = sizeof(ALT_PEN20_HOLY_ANGEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_HOLYDRAMON_FQID_ARR[] = "pen20:holydramon";
    inline static constexpr const char* ALT_PEN20_HOLYDRAMON_FQID = ALT_PEN20_HOLYDRAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_HOLYDRAMON_FQID_LEN = sizeof(ALT_PEN20_HOLYDRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_HOLYDRAMON_FQNAME_ARR[] = "pen20:Holydramon";
    inline static constexpr const char* ALT_PEN20_HOLYDRAMON_FQNAME = ALT_PEN20_HOLYDRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_HOLYDRAMON_FQNAME_LEN = sizeof(ALT_PEN20_HOLYDRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_HOUOUMON_FQID_ARR[] = "pen20:hououmon";
    inline static constexpr const char* ALT_PEN20_HOUOUMON_FQID = ALT_PEN20_HOUOUMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_HOUOUMON_FQID_LEN = sizeof(ALT_PEN20_HOUOUMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_HOUOUMON_FQNAME_ARR[] = "pen20:Hououmon";
    inline static constexpr const char* ALT_PEN20_HOUOUMON_FQNAME = ALT_PEN20_HOUOUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_HOUOUMON_FQNAME_LEN = sizeof(ALT_PEN20_HOUOUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_IGNAMON_FQID_ARR[] = "pen20:ignamon";
    inline static constexpr const char* ALT_PEN20_IGNAMON_FQID = ALT_PEN20_IGNAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_IGNAMON_FQID_LEN = sizeof(ALT_PEN20_IGNAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_IGNAMON_FQNAME_ARR[] = "pen20:Ignamon";
    inline static constexpr const char* ALT_PEN20_IGNAMON_FQNAME = ALT_PEN20_IGNAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_IGNAMON_FQNAME_LEN = sizeof(ALT_PEN20_IGNAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_IKKAKUMON_FQID_ARR[] = "pen20:ikkakumon";
    inline static constexpr const char* ALT_PEN20_IKKAKUMON_FQID = ALT_PEN20_IKKAKUMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_IKKAKUMON_FQID_LEN = sizeof(ALT_PEN20_IKKAKUMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_IKKAKUMON_FQNAME_ARR[] = "pen20:Ikkakumon";
    inline static constexpr const char* ALT_PEN20_IKKAKUMON_FQNAME = ALT_PEN20_IKKAKUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_IKKAKUMON_FQNAME_LEN = sizeof(ALT_PEN20_IKKAKUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_IMPERIALDRAMON_FIGHTER_MODE_FQID_ARR[] = "pen20:imperialdramon_fighter_mode";
    inline static constexpr const char* ALT_PEN20_IMPERIALDRAMON_FIGHTER_MODE_FQID = ALT_PEN20_IMPERIALDRAMON_FIGHTER_MODE_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_IMPERIALDRAMON_FIGHTER_MODE_FQID_LEN = sizeof(ALT_PEN20_IMPERIALDRAMON_FIGHTER_MODE_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_IMPERIALDRAMON_FIGHTER_MODE_FQNAME_ARR[] = "pen20:Imperialdramon Fighter Mode";
    inline static constexpr const char* ALT_PEN20_IMPERIALDRAMON_FIGHTER_MODE_FQNAME = ALT_PEN20_IMPERIALDRAMON_FIGHTER_MODE_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_IMPERIALDRAMON_FIGHTER_MODE_FQNAME_LEN = sizeof(ALT_PEN20_IMPERIALDRAMON_FIGHTER_MODE_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_IMPMON_FQID_ARR[] = "pen20:impmon";
    inline static constexpr const char* ALT_PEN20_IMPMON_FQID = ALT_PEN20_IMPMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_IMPMON_FQID_LEN = sizeof(ALT_PEN20_IMPMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_IMPMON_FQNAME_ARR[] = "pen20:Impmon";
    inline static constexpr const char* ALT_PEN20_IMPMON_FQNAME = ALT_PEN20_IMPMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_IMPMON_FQNAME_LEN = sizeof(ALT_PEN20_IMPMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_JESMON_FQID_ARR[] = "pen20:jesmon";
    inline static constexpr const char* ALT_PEN20_JESMON_FQID = ALT_PEN20_JESMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_JESMON_FQID_LEN = sizeof(ALT_PEN20_JESMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_JESMON_FQNAME_ARR[] = "pen20:Jesmon";
    inline static constexpr const char* ALT_PEN20_JESMON_FQNAME = ALT_PEN20_JESMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_JESMON_FQNAME_LEN = sizeof(ALT_PEN20_JESMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_JESMON_X_FQID_ARR[] = "pen20:jesmon_x";
    inline static constexpr const char* ALT_PEN20_JESMON_X_FQID = ALT_PEN20_JESMON_X_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_JESMON_X_FQID_LEN = sizeof(ALT_PEN20_JESMON_X_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_JESMON_X_FQNAME_ARR[] = "pen20:Jesmon X";
    inline static constexpr const char* ALT_PEN20_JESMON_X_FQNAME = ALT_PEN20_JESMON_X_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_JESMON_X_FQNAME_LEN = sizeof(ALT_PEN20_JESMON_X_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_JYAGAMON_FQID_ARR[] = "pen20:jyagamon";
    inline static constexpr const char* ALT_PEN20_JYAGAMON_FQID = ALT_PEN20_JYAGAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_JYAGAMON_FQID_LEN = sizeof(ALT_PEN20_JYAGAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_JYAGAMON_FQNAME_ARR[] = "pen20:Jyagamon";
    inline static constexpr const char* ALT_PEN20_JYAGAMON_FQNAME = ALT_PEN20_JYAGAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_JYAGAMON_FQNAME_LEN = sizeof(ALT_PEN20_JYAGAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_JYUREIMON_FQID_ARR[] = "pen20:jyureimon";
    inline static constexpr const char* ALT_PEN20_JYUREIMON_FQID = ALT_PEN20_JYUREIMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_JYUREIMON_FQID_LEN = sizeof(ALT_PEN20_JYUREIMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_JYUREIMON_FQNAME_ARR[] = "pen20:Jyureimon";
    inline static constexpr const char* ALT_PEN20_JYUREIMON_FQNAME = ALT_PEN20_JYUREIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_JYUREIMON_FQNAME_LEN = sizeof(ALT_PEN20_JYUREIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_KABUTERIMON_FQID_ARR[] = "pen20:kabuterimon";
    inline static constexpr const char* ALT_PEN20_KABUTERIMON_FQID = ALT_PEN20_KABUTERIMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_KABUTERIMON_FQID_LEN = sizeof(ALT_PEN20_KABUTERIMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_KABUTERIMON_FQNAME_ARR[] = "pen20:Kabuterimon";
    inline static constexpr const char* ALT_PEN20_KABUTERIMON_FQNAME = ALT_PEN20_KABUTERIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_KABUTERIMON_FQNAME_LEN = sizeof(ALT_PEN20_KABUTERIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_KAKKINMON_FQID_ARR[] = "pen20:kakkinmon";
    inline static constexpr const char* ALT_PEN20_KAKKINMON_FQID = ALT_PEN20_KAKKINMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_KAKKINMON_FQID_LEN = sizeof(ALT_PEN20_KAKKINMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_KAKKINMON_FQNAME_ARR[] = "pen20:Kakkinmon";
    inline static constexpr const char* ALT_PEN20_KAKKINMON_FQNAME = ALT_PEN20_KAKKINMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_KAKKINMON_FQNAME_LEN = sizeof(ALT_PEN20_KAKKINMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_KIWIMON_FQID_ARR[] = "pen20:kiwimon";
    inline static constexpr const char* ALT_PEN20_KIWIMON_FQID = ALT_PEN20_KIWIMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_KIWIMON_FQID_LEN = sizeof(ALT_PEN20_KIWIMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_KIWIMON_FQNAME_ARR[] = "pen20:Kiwimon";
    inline static constexpr const char* ALT_PEN20_KIWIMON_FQNAME = ALT_PEN20_KIWIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_KIWIMON_FQNAME_LEN = sizeof(ALT_PEN20_KIWIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_KNIGHTMON_FQID_ARR[] = "pen20:knightmon";
    inline static constexpr const char* ALT_PEN20_KNIGHTMON_FQID = ALT_PEN20_KNIGHTMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_KNIGHTMON_FQID_LEN = sizeof(ALT_PEN20_KNIGHTMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_KNIGHTMON_FQNAME_ARR[] = "pen20:Knightmon";
    inline static constexpr const char* ALT_PEN20_KNIGHTMON_FQNAME = ALT_PEN20_KNIGHTMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_KNIGHTMON_FQNAME_LEN = sizeof(ALT_PEN20_KNIGHTMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_KOKUWAMON_FQID_ARR[] = "pen20:kokuwamon";
    inline static constexpr const char* ALT_PEN20_KOKUWAMON_FQID = ALT_PEN20_KOKUWAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_KOKUWAMON_FQID_LEN = sizeof(ALT_PEN20_KOKUWAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_KOKUWAMON_FQNAME_ARR[] = "pen20:Kokuwamon";
    inline static constexpr const char* ALT_PEN20_KOKUWAMON_FQNAME = ALT_PEN20_KOKUWAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_KOKUWAMON_FQNAME_LEN = sizeof(ALT_PEN20_KOKUWAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_KUWAGAMON_FQID_ARR[] = "pen20:kuwagamon";
    inline static constexpr const char* ALT_PEN20_KUWAGAMON_FQID = ALT_PEN20_KUWAGAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_KUWAGAMON_FQID_LEN = sizeof(ALT_PEN20_KUWAGAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_KUWAGAMON_FQNAME_ARR[] = "pen20:Kuwagamon";
    inline static constexpr const char* ALT_PEN20_KUWAGAMON_FQNAME = ALT_PEN20_KUWAGAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_KUWAGAMON_FQNAME_LEN = sizeof(ALT_PEN20_KUWAGAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_KYOKYOMON_FQID_ARR[] = "pen20:kyokyomon";
    inline static constexpr const char* ALT_PEN20_KYOKYOMON_FQID = ALT_PEN20_KYOKYOMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_KYOKYOMON_FQID_LEN = sizeof(ALT_PEN20_KYOKYOMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_KYOKYOMON_FQNAME_ARR[] = "pen20:Kyokyomon";
    inline static constexpr const char* ALT_PEN20_KYOKYOMON_FQNAME = ALT_PEN20_KYOKYOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_KYOKYOMON_FQNAME_LEN = sizeof(ALT_PEN20_KYOKYOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_LADY_DEVIMON_FQID_ARR[] = "pen20:lady_devimon";
    inline static constexpr const char* ALT_PEN20_LADY_DEVIMON_FQID = ALT_PEN20_LADY_DEVIMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_LADY_DEVIMON_FQID_LEN = sizeof(ALT_PEN20_LADY_DEVIMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_LADY_DEVIMON_FQNAME_ARR[] = "pen20:Lady Devimon";
    inline static constexpr const char* ALT_PEN20_LADY_DEVIMON_FQNAME = ALT_PEN20_LADY_DEVIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_LADY_DEVIMON_FQNAME_LEN = sizeof(ALT_PEN20_LADY_DEVIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_LALAMON_FQID_ARR[] = "pen20:lalamon";
    inline static constexpr const char* ALT_PEN20_LALAMON_FQID = ALT_PEN20_LALAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_LALAMON_FQID_LEN = sizeof(ALT_PEN20_LALAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_LALAMON_FQNAME_ARR[] = "pen20:Lalamon";
    inline static constexpr const char* ALT_PEN20_LALAMON_FQNAME = ALT_PEN20_LALAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_LALAMON_FQNAME_LEN = sizeof(ALT_PEN20_LALAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_LAVOGARITAMON_FQID_ARR[] = "pen20:lavogaritamon";
    inline static constexpr const char* ALT_PEN20_LAVOGARITAMON_FQID = ALT_PEN20_LAVOGARITAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_LAVOGARITAMON_FQID_LEN = sizeof(ALT_PEN20_LAVOGARITAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_LAVOGARITAMON_FQNAME_ARR[] = "pen20:Lavogaritamon";
    inline static constexpr const char* ALT_PEN20_LAVOGARITAMON_FQNAME = ALT_PEN20_LAVOGARITAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_LAVOGARITAMON_FQNAME_LEN = sizeof(ALT_PEN20_LAVOGARITAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_LAVORVOMON_FQID_ARR[] = "pen20:lavorvomon";
    inline static constexpr const char* ALT_PEN20_LAVORVOMON_FQID = ALT_PEN20_LAVORVOMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_LAVORVOMON_FQID_LEN = sizeof(ALT_PEN20_LAVORVOMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_LAVORVOMON_FQNAME_ARR[] = "pen20:Lavorvomon";
    inline static constexpr const char* ALT_PEN20_LAVORVOMON_FQNAME = ALT_PEN20_LAVORVOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_LAVORVOMON_FQNAME_LEN = sizeof(ALT_PEN20_LAVORVOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_LILAMON_FQID_ARR[] = "pen20:lilamon";
    inline static constexpr const char* ALT_PEN20_LILAMON_FQID = ALT_PEN20_LILAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_LILAMON_FQID_LEN = sizeof(ALT_PEN20_LILAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_LILAMON_FQNAME_ARR[] = "pen20:Lilamon";
    inline static constexpr const char* ALT_PEN20_LILAMON_FQNAME = ALT_PEN20_LILAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_LILAMON_FQNAME_LEN = sizeof(ALT_PEN20_LILAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_LILIMON_FQID_ARR[] = "pen20:lilimon";
    inline static constexpr const char* ALT_PEN20_LILIMON_FQID = ALT_PEN20_LILIMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_LILIMON_FQID_LEN = sizeof(ALT_PEN20_LILIMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_LILIMON_FQNAME_ARR[] = "pen20:Lilimon";
    inline static constexpr const char* ALT_PEN20_LILIMON_FQNAME = ALT_PEN20_LILIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_LILIMON_FQNAME_LEN = sizeof(ALT_PEN20_LILIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_LOPMON_FQID_ARR[] = "pen20:lopmon";
    inline static constexpr const char* ALT_PEN20_LOPMON_FQID = ALT_PEN20_LOPMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_LOPMON_FQID_LEN = sizeof(ALT_PEN20_LOPMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_LOPMON_FQNAME_ARR[] = "pen20:Lopmon";
    inline static constexpr const char* ALT_PEN20_LOPMON_FQNAME = ALT_PEN20_LOPMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_LOPMON_FQNAME_LEN = sizeof(ALT_PEN20_LOPMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_LOTUSMON_FQID_ARR[] = "pen20:lotusmon";
    inline static constexpr const char* ALT_PEN20_LOTUSMON_FQID = ALT_PEN20_LOTUSMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_LOTUSMON_FQID_LEN = sizeof(ALT_PEN20_LOTUSMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_LOTUSMON_FQNAME_ARR[] = "pen20:Lotusmon";
    inline static constexpr const char* ALT_PEN20_LOTUSMON_FQNAME = ALT_PEN20_LOTUSMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_LOTUSMON_FQNAME_LEN = sizeof(ALT_PEN20_LOTUSMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_LUDOMON_FQID_ARR[] = "pen20:ludomon";
    inline static constexpr const char* ALT_PEN20_LUDOMON_FQID = ALT_PEN20_LUDOMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_LUDOMON_FQID_LEN = sizeof(ALT_PEN20_LUDOMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_LUDOMON_FQNAME_ARR[] = "pen20:Ludomon";
    inline static constexpr const char* ALT_PEN20_LUDOMON_FQNAME = ALT_PEN20_LUDOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_LUDOMON_FQNAME_LEN = sizeof(ALT_PEN20_LUDOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_MAD_LEOMON_FQID_ARR[] = "pen20:mad_leomon";
    inline static constexpr const char* ALT_PEN20_MAD_LEOMON_FQID = ALT_PEN20_MAD_LEOMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_MAD_LEOMON_FQID_LEN = sizeof(ALT_PEN20_MAD_LEOMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_MAD_LEOMON_FQNAME_ARR[] = "pen20:Mad Leomon";
    inline static constexpr const char* ALT_PEN20_MAD_LEOMON_FQNAME = ALT_PEN20_MAD_LEOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_MAD_LEOMON_FQNAME_LEN = sizeof(ALT_PEN20_MAD_LEOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_MAMBOMON_FQID_ARR[] = "pen20:mambomon";
    inline static constexpr const char* ALT_PEN20_MAMBOMON_FQID = ALT_PEN20_MAMBOMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_MAMBOMON_FQID_LEN = sizeof(ALT_PEN20_MAMBOMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_MAMBOMON_FQNAME_ARR[] = "pen20:Mambomon";
    inline static constexpr const char* ALT_PEN20_MAMBOMON_FQNAME = ALT_PEN20_MAMBOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_MAMBOMON_FQNAME_LEN = sizeof(ALT_PEN20_MAMBOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_MAMMON_FQID_ARR[] = "pen20:mammon";
    inline static constexpr const char* ALT_PEN20_MAMMON_FQID = ALT_PEN20_MAMMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_MAMMON_FQID_LEN = sizeof(ALT_PEN20_MAMMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_MAMMON_FQNAME_ARR[] = "pen20:Mammon";
    inline static constexpr const char* ALT_PEN20_MAMMON_FQNAME = ALT_PEN20_MAMMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_MAMMON_FQNAME_LEN = sizeof(ALT_PEN20_MAMMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_MANBOMON_FQID_ARR[] = "pen20:manbomon";
    inline static constexpr const char* ALT_PEN20_MANBOMON_FQID = ALT_PEN20_MANBOMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_MANBOMON_FQID_LEN = sizeof(ALT_PEN20_MANBOMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_MANBOMON_FQNAME_ARR[] = "pen20:Manbomon";
    inline static constexpr const char* ALT_PEN20_MANBOMON_FQNAME = ALT_PEN20_MANBOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_MANBOMON_FQNAME_LEN = sizeof(ALT_PEN20_MANBOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_MARIN_ANGEMON_FQID_ARR[] = "pen20:marin_angemon";
    inline static constexpr const char* ALT_PEN20_MARIN_ANGEMON_FQID = ALT_PEN20_MARIN_ANGEMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_MARIN_ANGEMON_FQID_LEN = sizeof(ALT_PEN20_MARIN_ANGEMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_MARIN_ANGEMON_FQNAME_ARR[] = "pen20:Marin Angemon";
    inline static constexpr const char* ALT_PEN20_MARIN_ANGEMON_FQNAME = ALT_PEN20_MARIN_ANGEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_MARIN_ANGEMON_FQNAME_LEN = sizeof(ALT_PEN20_MARIN_ANGEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_MARIN_DEVIMON_FQID_ARR[] = "pen20:marin_devimon";
    inline static constexpr const char* ALT_PEN20_MARIN_DEVIMON_FQID = ALT_PEN20_MARIN_DEVIMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_MARIN_DEVIMON_FQID_LEN = sizeof(ALT_PEN20_MARIN_DEVIMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_MARIN_DEVIMON_FQNAME_ARR[] = "pen20:Marin Devimon";
    inline static constexpr const char* ALT_PEN20_MARIN_DEVIMON_FQNAME = ALT_PEN20_MARIN_DEVIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_MARIN_DEVIMON_FQNAME_LEN = sizeof(ALT_PEN20_MARIN_DEVIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_MASTEMON_FQID_ARR[] = "pen20:mastemon";
    inline static constexpr const char* ALT_PEN20_MASTEMON_FQID = ALT_PEN20_MASTEMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_MASTEMON_FQID_LEN = sizeof(ALT_PEN20_MASTEMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_MASTEMON_FQNAME_ARR[] = "pen20:Mastemon";
    inline static constexpr const char* ALT_PEN20_MASTEMON_FQNAME = ALT_PEN20_MASTEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_MASTEMON_FQNAME_LEN = sizeof(ALT_PEN20_MASTEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_MECHANORIMON_FQID_ARR[] = "pen20:mechanorimon";
    inline static constexpr const char* ALT_PEN20_MECHANORIMON_FQID = ALT_PEN20_MECHANORIMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_MECHANORIMON_FQID_LEN = sizeof(ALT_PEN20_MECHANORIMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_MECHANORIMON_FQNAME_ARR[] = "pen20:Mechanorimon";
    inline static constexpr const char* ALT_PEN20_MECHANORIMON_FQNAME = ALT_PEN20_MECHANORIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_MECHANORIMON_FQNAME_LEN = sizeof(ALT_PEN20_MECHANORIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_MEGADRAMON_FQID_ARR[] = "pen20:megadramon";
    inline static constexpr const char* ALT_PEN20_MEGADRAMON_FQID = ALT_PEN20_MEGADRAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_MEGADRAMON_FQID_LEN = sizeof(ALT_PEN20_MEGADRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_MEGADRAMON_FQNAME_ARR[] = "pen20:Megadramon";
    inline static constexpr const char* ALT_PEN20_MEGADRAMON_FQNAME = ALT_PEN20_MEGADRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_MEGADRAMON_FQNAME_LEN = sizeof(ALT_PEN20_MEGADRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_MEGALO_GROWMON_FQID_ARR[] = "pen20:megalo_growmon";
    inline static constexpr const char* ALT_PEN20_MEGALO_GROWMON_FQID = ALT_PEN20_MEGALO_GROWMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_MEGALO_GROWMON_FQID_LEN = sizeof(ALT_PEN20_MEGALO_GROWMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_MEGALO_GROWMON_FQNAME_ARR[] = "pen20:Megalo Growmon";
    inline static constexpr const char* ALT_PEN20_MEGALO_GROWMON_FQNAME = ALT_PEN20_MEGALO_GROWMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_MEGALO_GROWMON_FQNAME_LEN = sizeof(ALT_PEN20_MEGALO_GROWMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_MEGA_SEADRAMON_FQID_ARR[] = "pen20:mega_seadramon";
    inline static constexpr const char* ALT_PEN20_MEGA_SEADRAMON_FQID = ALT_PEN20_MEGA_SEADRAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_MEGA_SEADRAMON_FQID_LEN = sizeof(ALT_PEN20_MEGA_SEADRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_MEGA_SEADRAMON_FQNAME_ARR[] = "pen20:Mega Seadramon";
    inline static constexpr const char* ALT_PEN20_MEGA_SEADRAMON_FQNAME = ALT_PEN20_MEGA_SEADRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_MEGA_SEADRAMON_FQNAME_LEN = sizeof(ALT_PEN20_MEGA_SEADRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_MEICRACKMON_VICIOUS_MODE_FQID_ARR[] = "pen20:meicrackmon_vicious_mode";
    inline static constexpr const char* ALT_PEN20_MEICRACKMON_VICIOUS_MODE_FQID = ALT_PEN20_MEICRACKMON_VICIOUS_MODE_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_MEICRACKMON_VICIOUS_MODE_FQID_LEN = sizeof(ALT_PEN20_MEICRACKMON_VICIOUS_MODE_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_MEICRACKMON_VICIOUS_MODE_FQNAME_ARR[] = "pen20:Meicrackmon Vicious Mode";
    inline static constexpr const char* ALT_PEN20_MEICRACKMON_VICIOUS_MODE_FQNAME = ALT_PEN20_MEICRACKMON_VICIOUS_MODE_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_MEICRACKMON_VICIOUS_MODE_FQNAME_LEN = sizeof(ALT_PEN20_MEICRACKMON_VICIOUS_MODE_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_MERAMON_FQID_ARR[] = "pen20:meramon";
    inline static constexpr const char* ALT_PEN20_MERAMON_FQID = ALT_PEN20_MERAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_MERAMON_FQID_LEN = sizeof(ALT_PEN20_MERAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_MERAMON_FQNAME_ARR[] = "pen20:Meramon";
    inline static constexpr const char* ALT_PEN20_MERAMON_FQNAME = ALT_PEN20_MERAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_MERAMON_FQNAME_LEN = sizeof(ALT_PEN20_MERAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_METAL_ETEMON_FQID_ARR[] = "pen20:metal_etemon";
    inline static constexpr const char* ALT_PEN20_METAL_ETEMON_FQID = ALT_PEN20_METAL_ETEMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_METAL_ETEMON_FQID_LEN = sizeof(ALT_PEN20_METAL_ETEMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_METAL_ETEMON_FQNAME_ARR[] = "pen20:Metal Etemon";
    inline static constexpr const char* ALT_PEN20_METAL_ETEMON_FQNAME = ALT_PEN20_METAL_ETEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_METAL_ETEMON_FQNAME_LEN = sizeof(ALT_PEN20_METAL_ETEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_METAL_GARURUMON_FQID_ARR[] = "pen20:metal_garurumon";
    inline static constexpr const char* ALT_PEN20_METAL_GARURUMON_FQID = ALT_PEN20_METAL_GARURUMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_METAL_GARURUMON_FQID_LEN = sizeof(ALT_PEN20_METAL_GARURUMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_METAL_GARURUMON_FQNAME_ARR[] = "pen20:Metal Garurumon";
    inline static constexpr const char* ALT_PEN20_METAL_GARURUMON_FQNAME = ALT_PEN20_METAL_GARURUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_METAL_GARURUMON_FQNAME_LEN = sizeof(ALT_PEN20_METAL_GARURUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_METAL_GREYMON_FQID_ARR[] = "pen20:metal_greymon";
    inline static constexpr const char* ALT_PEN20_METAL_GREYMON_FQID = ALT_PEN20_METAL_GREYMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_METAL_GREYMON_FQID_LEN = sizeof(ALT_PEN20_METAL_GREYMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_METAL_GREYMON_FQNAME_ARR[] = "pen20:Metal Greymon";
    inline static constexpr const char* ALT_PEN20_METAL_GREYMON_FQNAME = ALT_PEN20_METAL_GREYMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_METAL_GREYMON_FQNAME_LEN = sizeof(ALT_PEN20_METAL_GREYMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_METAL_MAMEMON_FQID_ARR[] = "pen20:metal_mamemon";
    inline static constexpr const char* ALT_PEN20_METAL_MAMEMON_FQID = ALT_PEN20_METAL_MAMEMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_METAL_MAMEMON_FQID_LEN = sizeof(ALT_PEN20_METAL_MAMEMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_METAL_MAMEMON_FQNAME_ARR[] = "pen20:Metal Mamemon";
    inline static constexpr const char* ALT_PEN20_METAL_MAMEMON_FQNAME = ALT_PEN20_METAL_MAMEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_METAL_MAMEMON_FQNAME_LEN = sizeof(ALT_PEN20_METAL_MAMEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_METAL_SEADRAMON_FQID_ARR[] = "pen20:metal_seadramon";
    inline static constexpr const char* ALT_PEN20_METAL_SEADRAMON_FQID = ALT_PEN20_METAL_SEADRAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_METAL_SEADRAMON_FQID_LEN = sizeof(ALT_PEN20_METAL_SEADRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_METAL_SEADRAMON_FQNAME_ARR[] = "pen20:Metal Seadramon";
    inline static constexpr const char* ALT_PEN20_METAL_SEADRAMON_FQNAME = ALT_PEN20_METAL_SEADRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_METAL_SEADRAMON_FQNAME_LEN = sizeof(ALT_PEN20_METAL_SEADRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_MOCHIMON_FQID_ARR[] = "pen20:mochimon";
    inline static constexpr const char* ALT_PEN20_MOCHIMON_FQID = ALT_PEN20_MOCHIMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_MOCHIMON_FQID_LEN = sizeof(ALT_PEN20_MOCHIMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_MOCHIMON_FQNAME_ARR[] = "pen20:Mochimon";
    inline static constexpr const char* ALT_PEN20_MOCHIMON_FQNAME = ALT_PEN20_MOCHIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_MOCHIMON_FQNAME_LEN = sizeof(ALT_PEN20_MOCHIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_MOKUMON_FQID_ARR[] = "pen20:mokumon";
    inline static constexpr const char* ALT_PEN20_MOKUMON_FQID = ALT_PEN20_MOKUMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_MOKUMON_FQID_LEN = sizeof(ALT_PEN20_MOKUMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_MOKUMON_FQNAME_ARR[] = "pen20:Mokumon";
    inline static constexpr const char* ALT_PEN20_MOKUMON_FQNAME = ALT_PEN20_MOKUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_MOKUMON_FQNAME_LEN = sizeof(ALT_PEN20_MOKUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_MONCHROMON_FQID_ARR[] = "pen20:monchromon";
    inline static constexpr const char* ALT_PEN20_MONCHROMON_FQID = ALT_PEN20_MONCHROMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_MONCHROMON_FQID_LEN = sizeof(ALT_PEN20_MONCHROMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_MONCHROMON_FQNAME_ARR[] = "pen20:Monchromon";
    inline static constexpr const char* ALT_PEN20_MONCHROMON_FQNAME = ALT_PEN20_MONCHROMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_MONCHROMON_FQNAME_LEN = sizeof(ALT_PEN20_MONCHROMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_MONOCHROMON_FQID_ARR[] = "pen20:monochromon";
    inline static constexpr const char* ALT_PEN20_MONOCHROMON_FQID = ALT_PEN20_MONOCHROMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_MONOCHROMON_FQID_LEN = sizeof(ALT_PEN20_MONOCHROMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_MONOCHROMON_FQNAME_ARR[] = "pen20:Monochromon";
    inline static constexpr const char* ALT_PEN20_MONOCHROMON_FQNAME = ALT_PEN20_MONOCHROMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_MONOCHROMON_FQNAME_LEN = sizeof(ALT_PEN20_MONOCHROMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_MUGENDRAMON_FQID_ARR[] = "pen20:mugendramon";
    inline static constexpr const char* ALT_PEN20_MUGENDRAMON_FQID = ALT_PEN20_MUGENDRAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_MUGENDRAMON_FQID_LEN = sizeof(ALT_PEN20_MUGENDRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_MUGENDRAMON_FQNAME_ARR[] = "pen20:Mugendramon";
    inline static constexpr const char* ALT_PEN20_MUGENDRAMON_FQNAME = ALT_PEN20_MUGENDRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_MUGENDRAMON_FQNAME_LEN = sizeof(ALT_PEN20_MUGENDRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_MUSHMON_FQID_ARR[] = "pen20:mushmon";
    inline static constexpr const char* ALT_PEN20_MUSHMON_FQID = ALT_PEN20_MUSHMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_MUSHMON_FQID_LEN = sizeof(ALT_PEN20_MUSHMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_MUSHMON_FQNAME_ARR[] = "pen20:Mushmon";
    inline static constexpr const char* ALT_PEN20_MUSHMON_FQNAME = ALT_PEN20_MUSHMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_MUSHMON_FQNAME_LEN = sizeof(ALT_PEN20_MUSHMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_NYOKIMON_FQID_ARR[] = "pen20:nyokimon";
    inline static constexpr const char* ALT_PEN20_NYOKIMON_FQID = ALT_PEN20_NYOKIMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_NYOKIMON_FQID_LEN = sizeof(ALT_PEN20_NYOKIMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_NYOKIMON_FQNAME_ARR[] = "pen20:Nyokimon";
    inline static constexpr const char* ALT_PEN20_NYOKIMON_FQNAME = ALT_PEN20_NYOKIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_NYOKIMON_FQNAME_LEN = sizeof(ALT_PEN20_NYOKIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_OCTMON_FQID_ARR[] = "pen20:octmon";
    inline static constexpr const char* ALT_PEN20_OCTMON_FQID = ALT_PEN20_OCTMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_OCTMON_FQID_LEN = sizeof(ALT_PEN20_OCTMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_OCTMON_FQNAME_ARR[] = "pen20:Octmon";
    inline static constexpr const char* ALT_PEN20_OCTMON_FQNAME = ALT_PEN20_OCTMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_OCTMON_FQNAME_LEN = sizeof(ALT_PEN20_OCTMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_OFANIMON_FQID_ARR[] = "pen20:ofanimon";
    inline static constexpr const char* ALT_PEN20_OFANIMON_FQID = ALT_PEN20_OFANIMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_OFANIMON_FQID_LEN = sizeof(ALT_PEN20_OFANIMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_OFANIMON_FQNAME_ARR[] = "pen20:Ofanimon";
    inline static constexpr const char* ALT_PEN20_OFANIMON_FQNAME = ALT_PEN20_OFANIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_OFANIMON_FQNAME_LEN = sizeof(ALT_PEN20_OFANIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_OGUDOMON_FQID_ARR[] = "pen20:ogudomon";
    inline static constexpr const char* ALT_PEN20_OGUDOMON_FQID = ALT_PEN20_OGUDOMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_OGUDOMON_FQID_LEN = sizeof(ALT_PEN20_OGUDOMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_OGUDOMON_FQNAME_ARR[] = "pen20:Ogudomon";
    inline static constexpr const char* ALT_PEN20_OGUDOMON_FQNAME = ALT_PEN20_OGUDOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_OGUDOMON_FQNAME_LEN = sizeof(ALT_PEN20_OGUDOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_OKUWAMON_FQID_ARR[] = "pen20:okuwamon";
    inline static constexpr const char* ALT_PEN20_OKUWAMON_FQID = ALT_PEN20_OKUWAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_OKUWAMON_FQID_LEN = sizeof(ALT_PEN20_OKUWAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_OKUWAMON_FQNAME_ARR[] = "pen20:Okuwamon";
    inline static constexpr const char* ALT_PEN20_OKUWAMON_FQNAME = ALT_PEN20_OKUWAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_OKUWAMON_FQNAME_LEN = sizeof(ALT_PEN20_OKUWAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_OMEGAMON_FQID_ARR[] = "pen20:omegamon";
    inline static constexpr const char* ALT_PEN20_OMEGAMON_FQID = ALT_PEN20_OMEGAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_OMEGAMON_FQID_LEN = sizeof(ALT_PEN20_OMEGAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_OMEGAMON_FQNAME_ARR[] = "pen20:Omegamon";
    inline static constexpr const char* ALT_PEN20_OMEGAMON_FQNAME = ALT_PEN20_OMEGAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_OMEGAMON_FQNAME_LEN = sizeof(ALT_PEN20_OMEGAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_ORDINEMON_FQID_ARR[] = "pen20:ordinemon";
    inline static constexpr const char* ALT_PEN20_ORDINEMON_FQID = ALT_PEN20_ORDINEMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_ORDINEMON_FQID_LEN = sizeof(ALT_PEN20_ORDINEMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_ORDINEMON_FQNAME_ARR[] = "pen20:Ordinemon";
    inline static constexpr const char* ALT_PEN20_ORDINEMON_FQNAME = ALT_PEN20_ORDINEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_ORDINEMON_FQNAME_LEN = sizeof(ALT_PEN20_ORDINEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_OTAMAMON_FQID_ARR[] = "pen20:otamamon";
    inline static constexpr const char* ALT_PEN20_OTAMAMON_FQID = ALT_PEN20_OTAMAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_OTAMAMON_FQID_LEN = sizeof(ALT_PEN20_OTAMAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_OTAMAMON_FQNAME_ARR[] = "pen20:Otamamon";
    inline static constexpr const char* ALT_PEN20_OTAMAMON_FQNAME = ALT_PEN20_OTAMAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_OTAMAMON_FQNAME_LEN = sizeof(ALT_PEN20_OTAMAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_OURYUMON_FQID_ARR[] = "pen20:ouryumon";
    inline static constexpr const char* ALT_PEN20_OURYUMON_FQID = ALT_PEN20_OURYUMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_OURYUMON_FQID_LEN = sizeof(ALT_PEN20_OURYUMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_OURYUMON_FQNAME_ARR[] = "pen20:Ouryumon";
    inline static constexpr const char* ALT_PEN20_OURYUMON_FQNAME = ALT_PEN20_OURYUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_OURYUMON_FQNAME_LEN = sizeof(ALT_PEN20_OURYUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_PAILDRAMON_FQID_ARR[] = "pen20:paildramon";
    inline static constexpr const char* ALT_PEN20_PAILDRAMON_FQID = ALT_PEN20_PAILDRAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_PAILDRAMON_FQID_LEN = sizeof(ALT_PEN20_PAILDRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_PAILDRAMON_FQNAME_ARR[] = "pen20:Paildramon";
    inline static constexpr const char* ALT_PEN20_PAILDRAMON_FQNAME = ALT_PEN20_PAILDRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_PAILDRAMON_FQNAME_LEN = sizeof(ALT_PEN20_PAILDRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_PALMON_FQID_ARR[] = "pen20:palmon";
    inline static constexpr const char* ALT_PEN20_PALMON_FQID = ALT_PEN20_PALMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_PALMON_FQID_LEN = sizeof(ALT_PEN20_PALMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_PALMON_FQNAME_ARR[] = "pen20:Palmon";
    inline static constexpr const char* ALT_PEN20_PALMON_FQNAME = ALT_PEN20_PALMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_PALMON_FQNAME_LEN = sizeof(ALT_PEN20_PALMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_PETI_MERAMON_FQID_ARR[] = "pen20:peti_meramon";
    inline static constexpr const char* ALT_PEN20_PETI_MERAMON_FQID = ALT_PEN20_PETI_MERAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_PETI_MERAMON_FQID_LEN = sizeof(ALT_PEN20_PETI_MERAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_PETI_MERAMON_FQNAME_ARR[] = "pen20:Peti Meramon";
    inline static constexpr const char* ALT_PEN20_PETI_MERAMON_FQNAME = ALT_PEN20_PETI_MERAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_PETI_MERAMON_FQNAME_LEN = sizeof(ALT_PEN20_PETI_MERAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_PHASCOMON_FQID_ARR[] = "pen20:phascomon";
    inline static constexpr const char* ALT_PEN20_PHASCOMON_FQID = ALT_PEN20_PHASCOMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_PHASCOMON_FQID_LEN = sizeof(ALT_PEN20_PHASCOMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_PHASCOMON_FQNAME_ARR[] = "pen20:Phascomon";
    inline static constexpr const char* ALT_PEN20_PHASCOMON_FQNAME = ALT_PEN20_PHASCOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_PHASCOMON_FQNAME_LEN = sizeof(ALT_PEN20_PHASCOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_PICCOLOMON_FQID_ARR[] = "pen20:piccolomon";
    inline static constexpr const char* ALT_PEN20_PICCOLOMON_FQID = ALT_PEN20_PICCOLOMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_PICCOLOMON_FQID_LEN = sizeof(ALT_PEN20_PICCOLOMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_PICCOLOMON_FQNAME_ARR[] = "pen20:Piccolomon";
    inline static constexpr const char* ALT_PEN20_PICCOLOMON_FQNAME = ALT_PEN20_PICCOLOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_PICCOLOMON_FQNAME_LEN = sizeof(ALT_PEN20_PICCOLOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_PICO_DEVIMON_FQID_ARR[] = "pen20:pico_devimon";
    inline static constexpr const char* ALT_PEN20_PICO_DEVIMON_FQID = ALT_PEN20_PICO_DEVIMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_PICO_DEVIMON_FQID_LEN = sizeof(ALT_PEN20_PICO_DEVIMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_PICO_DEVIMON_FQNAME_ARR[] = "pen20:Pico Devimon";
    inline static constexpr const char* ALT_PEN20_PICO_DEVIMON_FQNAME = ALT_PEN20_PICO_DEVIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_PICO_DEVIMON_FQNAME_LEN = sizeof(ALT_PEN20_PICO_DEVIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_PIEMON_FQID_ARR[] = "pen20:piemon";
    inline static constexpr const char* ALT_PEN20_PIEMON_FQID = ALT_PEN20_PIEMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_PIEMON_FQID_LEN = sizeof(ALT_PEN20_PIEMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_PIEMON_FQNAME_ARR[] = "pen20:Piemon";
    inline static constexpr const char* ALT_PEN20_PIEMON_FQNAME = ALT_PEN20_PIEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_PIEMON_FQNAME_LEN = sizeof(ALT_PEN20_PIEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_PINOCHIMON_FQID_ARR[] = "pen20:pinochimon";
    inline static constexpr const char* ALT_PEN20_PINOCHIMON_FQID = ALT_PEN20_PINOCHIMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_PINOCHIMON_FQID_LEN = sizeof(ALT_PEN20_PINOCHIMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_PINOCHIMON_FQNAME_ARR[] = "pen20:Pinochimon";
    inline static constexpr const char* ALT_PEN20_PINOCHIMON_FQNAME = ALT_PEN20_PINOCHIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_PINOCHIMON_FQNAME_LEN = sizeof(ALT_PEN20_PINOCHIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_PIYOMON_FQID_ARR[] = "pen20:piyomon";
    inline static constexpr const char* ALT_PEN20_PIYOMON_FQID = ALT_PEN20_PIYOMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_PIYOMON_FQID_LEN = sizeof(ALT_PEN20_PIYOMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_PIYOMON_FQNAME_ARR[] = "pen20:Piyomon";
    inline static constexpr const char* ALT_PEN20_PIYOMON_FQNAME = ALT_PEN20_PIYOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_PIYOMON_FQNAME_LEN = sizeof(ALT_PEN20_PIYOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_PLESIOMON_FQID_ARR[] = "pen20:plesiomon";
    inline static constexpr const char* ALT_PEN20_PLESIOMON_FQID = ALT_PEN20_PLESIOMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_PLESIOMON_FQID_LEN = sizeof(ALT_PEN20_PLESIOMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_PLESIOMON_FQNAME_ARR[] = "pen20:Plesiomon";
    inline static constexpr const char* ALT_PEN20_PLESIOMON_FQNAME = ALT_PEN20_PLESIOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_PLESIOMON_FQNAME_LEN = sizeof(ALT_PEN20_PLESIOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_PORCUPAMON_FQID_ARR[] = "pen20:porcupamon";
    inline static constexpr const char* ALT_PEN20_PORCUPAMON_FQID = ALT_PEN20_PORCUPAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_PORCUPAMON_FQID_LEN = sizeof(ALT_PEN20_PORCUPAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_PORCUPAMON_FQNAME_ARR[] = "pen20:Porcupamon";
    inline static constexpr const char* ALT_PEN20_PORCUPAMON_FQNAME = ALT_PEN20_PORCUPAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_PORCUPAMON_FQNAME_LEN = sizeof(ALT_PEN20_PORCUPAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_PORCUPMON_FQID_ARR[] = "pen20:porcupmon";
    inline static constexpr const char* ALT_PEN20_PORCUPMON_FQID = ALT_PEN20_PORCUPMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_PORCUPMON_FQID_LEN = sizeof(ALT_PEN20_PORCUPMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_PORCUPMON_FQNAME_ARR[] = "pen20:Porcupmon";
    inline static constexpr const char* ALT_PEN20_PORCUPMON_FQNAME = ALT_PEN20_PORCUPMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_PORCUPMON_FQNAME_LEN = sizeof(ALT_PEN20_PORCUPMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_PUKUMON_FQID_ARR[] = "pen20:pukumon";
    inline static constexpr const char* ALT_PEN20_PUKUMON_FQID = ALT_PEN20_PUKUMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_PUKUMON_FQID_LEN = sizeof(ALT_PEN20_PUKUMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_PUKUMON_FQNAME_ARR[] = "pen20:Pukumon";
    inline static constexpr const char* ALT_PEN20_PUKUMON_FQNAME = ALT_PEN20_PUKUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_PUKUMON_FQNAME_LEN = sizeof(ALT_PEN20_PUKUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_PUMPMON_FQID_ARR[] = "pen20:pumpmon";
    inline static constexpr const char* ALT_PEN20_PUMPMON_FQID = ALT_PEN20_PUMPMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_PUMPMON_FQID_LEN = sizeof(ALT_PEN20_PUMPMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_PUMPMON_FQNAME_ARR[] = "pen20:Pumpmon";
    inline static constexpr const char* ALT_PEN20_PUMPMON_FQNAME = ALT_PEN20_PUMPMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_PUMPMON_FQNAME_LEN = sizeof(ALT_PEN20_PUMPMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_PYOCOMON_FQID_ARR[] = "pen20:pyocomon";
    inline static constexpr const char* ALT_PEN20_PYOCOMON_FQID = ALT_PEN20_PYOCOMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_PYOCOMON_FQID_LEN = sizeof(ALT_PEN20_PYOCOMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_PYOCOMON_FQNAME_ARR[] = "pen20:Pyocomon";
    inline static constexpr const char* ALT_PEN20_PYOCOMON_FQNAME = ALT_PEN20_PYOCOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_PYOCOMON_FQNAME_LEN = sizeof(ALT_PEN20_PYOCOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_RAFFLESIMON_FQID_ARR[] = "pen20:rafflesimon";
    inline static constexpr const char* ALT_PEN20_RAFFLESIMON_FQID = ALT_PEN20_RAFFLESIMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_RAFFLESIMON_FQID_LEN = sizeof(ALT_PEN20_RAFFLESIMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_RAFFLESIMON_FQNAME_ARR[] = "pen20:Rafflesimon";
    inline static constexpr const char* ALT_PEN20_RAFFLESIMON_FQNAME = ALT_PEN20_RAFFLESIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_RAFFLESIMON_FQNAME_LEN = sizeof(ALT_PEN20_RAFFLESIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_RAGNA_LORDMON_FQID_ARR[] = "pen20:ragna_lordmon";
    inline static constexpr const char* ALT_PEN20_RAGNA_LORDMON_FQID = ALT_PEN20_RAGNA_LORDMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_RAGNA_LORDMON_FQID_LEN = sizeof(ALT_PEN20_RAGNA_LORDMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_RAGNA_LORDMON_FQNAME_ARR[] = "pen20:Ragna Lordmon";
    inline static constexpr const char* ALT_PEN20_RAGNA_LORDMON_FQNAME = ALT_PEN20_RAGNA_LORDMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_RAGNA_LORDMON_FQNAME_LEN = sizeof(ALT_PEN20_RAGNA_LORDMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_RAGUELMON_FQID_ARR[] = "pen20:raguelmon";
    inline static constexpr const char* ALT_PEN20_RAGUELMON_FQID = ALT_PEN20_RAGUELMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_RAGUELMON_FQID_LEN = sizeof(ALT_PEN20_RAGUELMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_RAGUELMON_FQNAME_ARR[] = "pen20:Raguelmon";
    inline static constexpr const char* ALT_PEN20_RAGUELMON_FQNAME = ALT_PEN20_RAGUELMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_RAGUELMON_FQNAME_LEN = sizeof(ALT_PEN20_RAGUELMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_RAIJI_LUDOMON_FQID_ARR[] = "pen20:raiji_ludomon";
    inline static constexpr const char* ALT_PEN20_RAIJI_LUDOMON_FQID = ALT_PEN20_RAIJI_LUDOMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_RAIJI_LUDOMON_FQID_LEN = sizeof(ALT_PEN20_RAIJI_LUDOMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_RAIJI_LUDOMON_FQNAME_ARR[] = "pen20:Raiji Ludomon";
    inline static constexpr const char* ALT_PEN20_RAIJI_LUDOMON_FQNAME = ALT_PEN20_RAIJI_LUDOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_RAIJI_LUDOMON_FQNAME_LEN = sizeof(ALT_PEN20_RAIJI_LUDOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_RAKAMON_FQID_ARR[] = "pen20:rakamon";
    inline static constexpr const char* ALT_PEN20_RAKAMON_FQID = ALT_PEN20_RAKAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_RAKAMON_FQID_LEN = sizeof(ALT_PEN20_RAKAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_RAKAMON_FQNAME_ARR[] = "pen20:Rakamon";
    inline static constexpr const char* ALT_PEN20_RAKAMON_FQNAME = ALT_PEN20_RAKAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_RAKAMON_FQNAME_LEN = sizeof(ALT_PEN20_RAKAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_RAPIDMON_FQID_ARR[] = "pen20:rapidmon";
    inline static constexpr const char* ALT_PEN20_RAPIDMON_FQID = ALT_PEN20_RAPIDMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_RAPIDMON_FQID_LEN = sizeof(ALT_PEN20_RAPIDMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_RAPIDMON_FQNAME_ARR[] = "pen20:Rapidmon";
    inline static constexpr const char* ALT_PEN20_RAPIDMON_FQNAME = ALT_PEN20_RAPIDMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_RAPIDMON_FQNAME_LEN = sizeof(ALT_PEN20_RAPIDMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_RED_VEGIMON_FQID_ARR[] = "pen20:red_vegimon";
    inline static constexpr const char* ALT_PEN20_RED_VEGIMON_FQID = ALT_PEN20_RED_VEGIMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_RED_VEGIMON_FQID_LEN = sizeof(ALT_PEN20_RED_VEGIMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_RED_VEGIMON_FQNAME_ARR[] = "pen20:Red Vegimon";
    inline static constexpr const char* ALT_PEN20_RED_VEGIMON_FQNAME = ALT_PEN20_RED_VEGIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_RED_VEGIMON_FQNAME_LEN = sizeof(ALT_PEN20_RED_VEGIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_REPPAMON_FQID_ARR[] = "pen20:reppamon";
    inline static constexpr const char* ALT_PEN20_REPPAMON_FQID = ALT_PEN20_REPPAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_REPPAMON_FQID_LEN = sizeof(ALT_PEN20_REPPAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_REPPAMON_FQNAME_ARR[] = "pen20:Reppamon";
    inline static constexpr const char* ALT_PEN20_REPPAMON_FQNAME = ALT_PEN20_REPPAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_REPPAMON_FQNAME_LEN = sizeof(ALT_PEN20_REPPAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_REVOLMON_FQID_ARR[] = "pen20:revolmon";
    inline static constexpr const char* ALT_PEN20_REVOLMON_FQID = ALT_PEN20_REVOLMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_REVOLMON_FQID_LEN = sizeof(ALT_PEN20_REVOLMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_REVOLMON_FQNAME_ARR[] = "pen20:Revolmon";
    inline static constexpr const char* ALT_PEN20_REVOLMON_FQNAME = ALT_PEN20_REVOLMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_REVOLMON_FQNAME_LEN = sizeof(ALT_PEN20_REVOLMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_RIZE_GREYMON_FQID_ARR[] = "pen20:rize_greymon";
    inline static constexpr const char* ALT_PEN20_RIZE_GREYMON_FQID = ALT_PEN20_RIZE_GREYMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_RIZE_GREYMON_FQID_LEN = sizeof(ALT_PEN20_RIZE_GREYMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_RIZE_GREYMON_FQNAME_ARR[] = "pen20:Rize Greymon";
    inline static constexpr const char* ALT_PEN20_RIZE_GREYMON_FQNAME = ALT_PEN20_RIZE_GREYMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_RIZE_GREYMON_FQNAME_LEN = sizeof(ALT_PEN20_RIZE_GREYMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_ROSEMON_FQID_ARR[] = "pen20:rosemon";
    inline static constexpr const char* ALT_PEN20_ROSEMON_FQID = ALT_PEN20_ROSEMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_ROSEMON_FQID_LEN = sizeof(ALT_PEN20_ROSEMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_ROSEMON_FQNAME_ARR[] = "pen20:Rosemon";
    inline static constexpr const char* ALT_PEN20_ROSEMON_FQNAME = ALT_PEN20_ROSEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_ROSEMON_FQNAME_LEN = sizeof(ALT_PEN20_ROSEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_RUKAMON_FQID_ARR[] = "pen20:rukamon";
    inline static constexpr const char* ALT_PEN20_RUKAMON_FQID = ALT_PEN20_RUKAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_RUKAMON_FQID_LEN = sizeof(ALT_PEN20_RUKAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_RUKAMON_FQNAME_ARR[] = "pen20:Rukamon";
    inline static constexpr const char* ALT_PEN20_RUKAMON_FQNAME = ALT_PEN20_RUKAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_RUKAMON_FQNAME_LEN = sizeof(ALT_PEN20_RUKAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_RYUDAMON_FQID_ARR[] = "pen20:ryudamon";
    inline static constexpr const char* ALT_PEN20_RYUDAMON_FQID = ALT_PEN20_RYUDAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_RYUDAMON_FQID_LEN = sizeof(ALT_PEN20_RYUDAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_RYUDAMON_FQNAME_ARR[] = "pen20:Ryudamon";
    inline static constexpr const char* ALT_PEN20_RYUDAMON_FQNAME = ALT_PEN20_RYUDAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_RYUDAMON_FQNAME_LEN = sizeof(ALT_PEN20_RYUDAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_SABER_LEOMON_FQID_ARR[] = "pen20:saber_leomon";
    inline static constexpr const char* ALT_PEN20_SABER_LEOMON_FQID = ALT_PEN20_SABER_LEOMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_SABER_LEOMON_FQID_LEN = sizeof(ALT_PEN20_SABER_LEOMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_SABER_LEOMON_FQNAME_ARR[] = "pen20:Saber Leomon";
    inline static constexpr const char* ALT_PEN20_SABER_LEOMON_FQNAME = ALT_PEN20_SABER_LEOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_SABER_LEOMON_FQNAME_LEN = sizeof(ALT_PEN20_SABER_LEOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_SAINT_GALGOMON_FQID_ARR[] = "pen20:saint_galgomon";
    inline static constexpr const char* ALT_PEN20_SAINT_GALGOMON_FQID = ALT_PEN20_SAINT_GALGOMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_SAINT_GALGOMON_FQID_LEN = sizeof(ALT_PEN20_SAINT_GALGOMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_SAINT_GALGOMON_FQNAME_ARR[] = "pen20:Saint Galgomon";
    inline static constexpr const char* ALT_PEN20_SAINT_GALGOMON_FQNAME = ALT_PEN20_SAINT_GALGOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_SAINT_GALGOMON_FQNAME_LEN = sizeof(ALT_PEN20_SAINT_GALGOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_SAVIOR_HACKMON_FQID_ARR[] = "pen20:savior_hackmon";
    inline static constexpr const char* ALT_PEN20_SAVIOR_HACKMON_FQID = ALT_PEN20_SAVIOR_HACKMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_SAVIOR_HACKMON_FQID_LEN = sizeof(ALT_PEN20_SAVIOR_HACKMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_SAVIOR_HACKMON_FQNAME_ARR[] = "pen20:Savior Hackmon";
    inline static constexpr const char* ALT_PEN20_SAVIOR_HACKMON_FQNAME = ALT_PEN20_SAVIOR_HACKMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_SAVIOR_HACKMON_FQNAME_LEN = sizeof(ALT_PEN20_SAVIOR_HACKMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_SEADRAMON_FQID_ARR[] = "pen20:seadramon";
    inline static constexpr const char* ALT_PEN20_SEADRAMON_FQID = ALT_PEN20_SEADRAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_SEADRAMON_FQID_LEN = sizeof(ALT_PEN20_SEADRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_SEADRAMON_FQNAME_ARR[] = "pen20:Seadramon";
    inline static constexpr const char* ALT_PEN20_SEADRAMON_FQNAME = ALT_PEN20_SEADRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_SEADRAMON_FQNAME_LEN = sizeof(ALT_PEN20_SEADRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_SERAPHIMON_FQID_ARR[] = "pen20:seraphimon";
    inline static constexpr const char* ALT_PEN20_SERAPHIMON_FQID = ALT_PEN20_SERAPHIMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_SERAPHIMON_FQID_LEN = sizeof(ALT_PEN20_SERAPHIMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_SERAPHIMON_FQNAME_ARR[] = "pen20:Seraphimon";
    inline static constexpr const char* ALT_PEN20_SERAPHIMON_FQNAME = ALT_PEN20_SERAPHIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_SERAPHIMON_FQNAME_LEN = sizeof(ALT_PEN20_SERAPHIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_SHADRAMON_FQID_ARR[] = "pen20:shadramon";
    inline static constexpr const char* ALT_PEN20_SHADRAMON_FQID = ALT_PEN20_SHADRAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_SHADRAMON_FQID_LEN = sizeof(ALT_PEN20_SHADRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_SHADRAMON_FQNAME_ARR[] = "pen20:Shadramon";
    inline static constexpr const char* ALT_PEN20_SHADRAMON_FQNAME = ALT_PEN20_SHADRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_SHADRAMON_FQNAME_LEN = sizeof(ALT_PEN20_SHADRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_SHAKOMON_FQID_ARR[] = "pen20:shakomon";
    inline static constexpr const char* ALT_PEN20_SHAKOMON_FQID = ALT_PEN20_SHAKOMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_SHAKOMON_FQID_LEN = sizeof(ALT_PEN20_SHAKOMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_SHAKOMON_FQNAME_ARR[] = "pen20:Shakomon";
    inline static constexpr const char* ALT_PEN20_SHAKOMON_FQNAME = ALT_PEN20_SHAKOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_SHAKOMON_FQNAME_LEN = sizeof(ALT_PEN20_SHAKOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_SKULL_MAMMON_FQID_ARR[] = "pen20:skull_mammon";
    inline static constexpr const char* ALT_PEN20_SKULL_MAMMON_FQID = ALT_PEN20_SKULL_MAMMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_SKULL_MAMMON_FQID_LEN = sizeof(ALT_PEN20_SKULL_MAMMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_SKULL_MAMMON_FQNAME_ARR[] = "pen20:Skull Mammon";
    inline static constexpr const char* ALT_PEN20_SKULL_MAMMON_FQNAME = ALT_PEN20_SKULL_MAMMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_SKULL_MAMMON_FQNAME_LEN = sizeof(ALT_PEN20_SKULL_MAMMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_SLAYERDRAMON_FQID_ARR[] = "pen20:slayerdramon";
    inline static constexpr const char* ALT_PEN20_SLAYERDRAMON_FQID = ALT_PEN20_SLAYERDRAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_SLAYERDRAMON_FQID_LEN = sizeof(ALT_PEN20_SLAYERDRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_SLAYERDRAMON_FQNAME_ARR[] = "pen20:Slayerdramon";
    inline static constexpr const char* ALT_PEN20_SLAYERDRAMON_FQNAME = ALT_PEN20_SLAYERDRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_SLAYERDRAMON_FQNAME_LEN = sizeof(ALT_PEN20_SLAYERDRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_STARMON_FQID_ARR[] = "pen20:starmon";
    inline static constexpr const char* ALT_PEN20_STARMON_FQID = ALT_PEN20_STARMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_STARMON_FQID_LEN = sizeof(ALT_PEN20_STARMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_STARMON_FQNAME_ARR[] = "pen20:Starmon";
    inline static constexpr const char* ALT_PEN20_STARMON_FQNAME = ALT_PEN20_STARMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_STARMON_FQNAME_LEN = sizeof(ALT_PEN20_STARMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_SUNFLOWMON_FQID_ARR[] = "pen20:sunflowmon";
    inline static constexpr const char* ALT_PEN20_SUNFLOWMON_FQID = ALT_PEN20_SUNFLOWMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_SUNFLOWMON_FQID_LEN = sizeof(ALT_PEN20_SUNFLOWMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_SUNFLOWMON_FQNAME_ARR[] = "pen20:Sunflowmon";
    inline static constexpr const char* ALT_PEN20_SUNFLOWMON_FQNAME = ALT_PEN20_SUNFLOWMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_SUNFLOWMON_FQNAME_LEN = sizeof(ALT_PEN20_SUNFLOWMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_TAILMON_FQID_ARR[] = "pen20:tailmon";
    inline static constexpr const char* ALT_PEN20_TAILMON_FQID = ALT_PEN20_TAILMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_TAILMON_FQID_LEN = sizeof(ALT_PEN20_TAILMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_TAILMON_FQNAME_ARR[] = "pen20:Tailmon";
    inline static constexpr const char* ALT_PEN20_TAILMON_FQNAME = ALT_PEN20_TAILMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_TAILMON_FQNAME_LEN = sizeof(ALT_PEN20_TAILMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_TANKMON_FQID_ARR[] = "pen20:tankmon";
    inline static constexpr const char* ALT_PEN20_TANKMON_FQID = ALT_PEN20_TANKMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_TANKMON_FQID_LEN = sizeof(ALT_PEN20_TANKMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_TANKMON_FQNAME_ARR[] = "pen20:Tankmon";
    inline static constexpr const char* ALT_PEN20_TANKMON_FQNAME = ALT_PEN20_TANKMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_TANKMON_FQNAME_LEN = sizeof(ALT_PEN20_TANKMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_TARGETMON_FQID_ARR[] = "pen20:targetmon";
    inline static constexpr const char* ALT_PEN20_TARGETMON_FQID = ALT_PEN20_TARGETMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_TARGETMON_FQID_LEN = sizeof(ALT_PEN20_TARGETMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_TARGETMON_FQNAME_ARR[] = "pen20:Targetmon";
    inline static constexpr const char* ALT_PEN20_TARGETMON_FQNAME = ALT_PEN20_TARGETMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_TARGETMON_FQNAME_LEN = sizeof(ALT_PEN20_TARGETMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_TENTOMON_FQID_ARR[] = "pen20:tentomon";
    inline static constexpr const char* ALT_PEN20_TENTOMON_FQID = ALT_PEN20_TENTOMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_TENTOMON_FQID_LEN = sizeof(ALT_PEN20_TENTOMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_TENTOMON_FQNAME_ARR[] = "pen20:Tentomon";
    inline static constexpr const char* ALT_PEN20_TENTOMON_FQNAME = ALT_PEN20_TENTOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_TENTOMON_FQNAME_LEN = sizeof(ALT_PEN20_TENTOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_TERRIERMON_FQID_ARR[] = "pen20:terriermon";
    inline static constexpr const char* ALT_PEN20_TERRIERMON_FQID = ALT_PEN20_TERRIERMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_TERRIERMON_FQID_LEN = sizeof(ALT_PEN20_TERRIERMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_TERRIERMON_FQNAME_ARR[] = "pen20:Terriermon";
    inline static constexpr const char* ALT_PEN20_TERRIERMON_FQNAME = ALT_PEN20_TERRIERMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_TERRIERMON_FQNAME_LEN = sizeof(ALT_PEN20_TERRIERMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_THUNDERBALLMON_FQID_ARR[] = "pen20:thunderballmon";
    inline static constexpr const char* ALT_PEN20_THUNDERBALLMON_FQID = ALT_PEN20_THUNDERBALLMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_THUNDERBALLMON_FQID_LEN = sizeof(ALT_PEN20_THUNDERBALLMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_THUNDERBALLMON_FQNAME_ARR[] = "pen20:Thunderballmon";
    inline static constexpr const char* ALT_PEN20_THUNDERBALLMON_FQNAME = ALT_PEN20_THUNDERBALLMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_THUNDERBALLMON_FQNAME_LEN = sizeof(ALT_PEN20_THUNDERBALLMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_TIA_LUDOMON_FQID_ARR[] = "pen20:tia_ludomon";
    inline static constexpr const char* ALT_PEN20_TIA_LUDOMON_FQID = ALT_PEN20_TIA_LUDOMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_TIA_LUDOMON_FQID_LEN = sizeof(ALT_PEN20_TIA_LUDOMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_TIA_LUDOMON_FQNAME_ARR[] = "pen20:Tia Ludomon";
    inline static constexpr const char* ALT_PEN20_TIA_LUDOMON_FQNAME = ALT_PEN20_TIA_LUDOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_TIA_LUDOMON_FQNAME_LEN = sizeof(ALT_PEN20_TIA_LUDOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_TOGEMON_FQID_ARR[] = "pen20:togemon";
    inline static constexpr const char* ALT_PEN20_TOGEMON_FQID = ALT_PEN20_TOGEMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_TOGEMON_FQID_LEN = sizeof(ALT_PEN20_TOGEMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_TOGEMON_FQNAME_ARR[] = "pen20:Togemon";
    inline static constexpr const char* ALT_PEN20_TOGEMON_FQNAME = ALT_PEN20_TOGEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_TOGEMON_FQNAME_LEN = sizeof(ALT_PEN20_TOGEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_TONOSAMA_GEKOMON_FQID_ARR[] = "pen20:tonosama_gekomon";
    inline static constexpr const char* ALT_PEN20_TONOSAMA_GEKOMON_FQID = ALT_PEN20_TONOSAMA_GEKOMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_TONOSAMA_GEKOMON_FQID_LEN = sizeof(ALT_PEN20_TONOSAMA_GEKOMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_TONOSAMA_GEKOMON_FQNAME_ARR[] = "pen20:Tonosama Gekomon";
    inline static constexpr const char* ALT_PEN20_TONOSAMA_GEKOMON_FQNAME = ALT_PEN20_TONOSAMA_GEKOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_TONOSAMA_GEKOMON_FQNAME_LEN = sizeof(ALT_PEN20_TONOSAMA_GEKOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_TORTAMON_FQID_ARR[] = "pen20:tortamon";
    inline static constexpr const char* ALT_PEN20_TORTAMON_FQID = ALT_PEN20_TORTAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_TORTAMON_FQID_LEN = sizeof(ALT_PEN20_TORTAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_TORTAMON_FQNAME_ARR[] = "pen20:Tortamon";
    inline static constexpr const char* ALT_PEN20_TORTAMON_FQNAME = ALT_PEN20_TORTAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_TORTAMON_FQNAME_LEN = sizeof(ALT_PEN20_TORTAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_TOY_AGUMON_FQID_ARR[] = "pen20:toy_agumon";
    inline static constexpr const char* ALT_PEN20_TOY_AGUMON_FQID = ALT_PEN20_TOY_AGUMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_TOY_AGUMON_FQID_LEN = sizeof(ALT_PEN20_TOY_AGUMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_TOY_AGUMON_FQNAME_ARR[] = "pen20:Toy Agumon";
    inline static constexpr const char* ALT_PEN20_TOY_AGUMON_FQNAME = ALT_PEN20_TOY_AGUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_TOY_AGUMON_FQNAME_LEN = sizeof(ALT_PEN20_TOY_AGUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_TRICERAMON_FQID_ARR[] = "pen20:triceramon";
    inline static constexpr const char* ALT_PEN20_TRICERAMON_FQID = ALT_PEN20_TRICERAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_TRICERAMON_FQID_LEN = sizeof(ALT_PEN20_TRICERAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_TRICERAMON_FQNAME_ARR[] = "pen20:Triceramon";
    inline static constexpr const char* ALT_PEN20_TRICERAMON_FQNAME = ALT_PEN20_TRICERAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_TRICERAMON_FQNAME_LEN = sizeof(ALT_PEN20_TRICERAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_TROOPMON_FQID_ARR[] = "pen20:troopmon";
    inline static constexpr const char* ALT_PEN20_TROOPMON_FQID = ALT_PEN20_TROOPMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_TROOPMON_FQID_LEN = sizeof(ALT_PEN20_TROOPMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_TROOPMON_FQNAME_ARR[] = "pen20:Troopmon";
    inline static constexpr const char* ALT_PEN20_TROOPMON_FQNAME = ALT_PEN20_TROOPMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_TROOPMON_FQNAME_LEN = sizeof(ALT_PEN20_TROOPMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_TURUIEMON_FQID_ARR[] = "pen20:turuiemon";
    inline static constexpr const char* ALT_PEN20_TURUIEMON_FQID = ALT_PEN20_TURUIEMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_TURUIEMON_FQID_LEN = sizeof(ALT_PEN20_TURUIEMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_TURUIEMON_FQNAME_ARR[] = "pen20:Turuiemon";
    inline static constexpr const char* ALT_PEN20_TURUIEMON_FQNAME = ALT_PEN20_TURUIEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_TURUIEMON_FQNAME_LEN = sizeof(ALT_PEN20_TURUIEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_VAMDEMON_FQID_ARR[] = "pen20:vamdemon";
    inline static constexpr const char* ALT_PEN20_VAMDEMON_FQID = ALT_PEN20_VAMDEMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_VAMDEMON_FQID_LEN = sizeof(ALT_PEN20_VAMDEMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_VAMDEMON_FQNAME_ARR[] = "pen20:Vamdemon";
    inline static constexpr const char* ALT_PEN20_VAMDEMON_FQNAME = ALT_PEN20_VAMDEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_VAMDEMON_FQNAME_LEN = sizeof(ALT_PEN20_VAMDEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_V_DRAMON_FQID_ARR[] = "pen20:v_dramon";
    inline static constexpr const char* ALT_PEN20_V_DRAMON_FQID = ALT_PEN20_V_DRAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_V_DRAMON_FQID_LEN = sizeof(ALT_PEN20_V_DRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_V_DRAMON_FQNAME_ARR[] = "pen20:V-dramon";
    inline static constexpr const char* ALT_PEN20_V_DRAMON_FQNAME = ALT_PEN20_V_DRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_V_DRAMON_FQNAME_LEN = sizeof(ALT_PEN20_V_DRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_VEMDEMON_FQID_ARR[] = "pen20:vemdemon";
    inline static constexpr const char* ALT_PEN20_VEMDEMON_FQID = ALT_PEN20_VEMDEMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_VEMDEMON_FQID_LEN = sizeof(ALT_PEN20_VEMDEMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_VEMDEMON_FQNAME_ARR[] = "pen20:Vemdemon";
    inline static constexpr const char* ALT_PEN20_VEMDEMON_FQNAME = ALT_PEN20_VEMDEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_VEMDEMON_FQNAME_LEN = sizeof(ALT_PEN20_VEMDEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_VENOM_VAMDEMON_FQID_ARR[] = "pen20:venom_vamdemon";
    inline static constexpr const char* ALT_PEN20_VENOM_VAMDEMON_FQID = ALT_PEN20_VENOM_VAMDEMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_VENOM_VAMDEMON_FQID_LEN = sizeof(ALT_PEN20_VENOM_VAMDEMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_VENOM_VAMDEMON_FQNAME_ARR[] = "pen20:Venom Vamdemon";
    inline static constexpr const char* ALT_PEN20_VENOM_VAMDEMON_FQNAME = ALT_PEN20_VENOM_VAMDEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_VENOM_VAMDEMON_FQNAME_LEN = sizeof(ALT_PEN20_VENOM_VAMDEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_V_MON_FQID_ARR[] = "pen20:v_mon";
    inline static constexpr const char* ALT_PEN20_V_MON_FQID = ALT_PEN20_V_MON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_V_MON_FQID_LEN = sizeof(ALT_PEN20_V_MON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_V_MON_FQNAME_ARR[] = "pen20:V-mon";
    inline static constexpr const char* ALT_PEN20_V_MON_FQNAME = ALT_PEN20_V_MON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_V_MON_FQNAME_LEN = sizeof(ALT_PEN20_V_MON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_VOLCANICDRAMON_FQID_ARR[] = "pen20:volcanicdramon";
    inline static constexpr const char* ALT_PEN20_VOLCANICDRAMON_FQID = ALT_PEN20_VOLCANICDRAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_VOLCANICDRAMON_FQID_LEN = sizeof(ALT_PEN20_VOLCANICDRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_VOLCANICDRAMON_FQNAME_ARR[] = "pen20:Volcanicdramon";
    inline static constexpr const char* ALT_PEN20_VOLCANICDRAMON_FQNAME = ALT_PEN20_VOLCANICDRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_VOLCANICDRAMON_FQNAME_LEN = sizeof(ALT_PEN20_VOLCANICDRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_VOLTOBAUTAMON_FQID_ARR[] = "pen20:voltobautamon";
    inline static constexpr const char* ALT_PEN20_VOLTOBAUTAMON_FQID = ALT_PEN20_VOLTOBAUTAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_VOLTOBAUTAMON_FQID_LEN = sizeof(ALT_PEN20_VOLTOBAUTAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_VOLTOBAUTAMON_FQNAME_ARR[] = "pen20:Voltobautamon";
    inline static constexpr const char* ALT_PEN20_VOLTOBAUTAMON_FQNAME = ALT_PEN20_VOLTOBAUTAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_VOLTOBAUTAMON_FQNAME_LEN = sizeof(ALT_PEN20_VOLTOBAUTAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_VORVOMON_FQID_ARR[] = "pen20:vorvomon";
    inline static constexpr const char* ALT_PEN20_VORVOMON_FQID = ALT_PEN20_VORVOMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_VORVOMON_FQID_LEN = sizeof(ALT_PEN20_VORVOMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_VORVOMON_FQNAME_ARR[] = "pen20:Vorvomon";
    inline static constexpr const char* ALT_PEN20_VORVOMON_FQNAME = ALT_PEN20_VORVOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_VORVOMON_FQNAME_LEN = sizeof(ALT_PEN20_VORVOMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_WAR_GREYMON_FQID_ARR[] = "pen20:war_greymon";
    inline static constexpr const char* ALT_PEN20_WAR_GREYMON_FQID = ALT_PEN20_WAR_GREYMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_WAR_GREYMON_FQID_LEN = sizeof(ALT_PEN20_WAR_GREYMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_WAR_GREYMON_FQNAME_ARR[] = "pen20:War Greymon";
    inline static constexpr const char* ALT_PEN20_WAR_GREYMON_FQNAME = ALT_PEN20_WAR_GREYMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_WAR_GREYMON_FQNAME_LEN = sizeof(ALT_PEN20_WAR_GREYMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_WARU_MOZAEMON_FQID_ARR[] = "pen20:waru_mozaemon";
    inline static constexpr const char* ALT_PEN20_WARU_MOZAEMON_FQID = ALT_PEN20_WARU_MOZAEMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_WARU_MOZAEMON_FQID_LEN = sizeof(ALT_PEN20_WARU_MOZAEMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_WARU_MOZAEMON_FQNAME_ARR[] = "pen20:Waru Mozaemon";
    inline static constexpr const char* ALT_PEN20_WARU_MOZAEMON_FQNAME = ALT_PEN20_WARU_MOZAEMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_WARU_MOZAEMON_FQNAME_LEN = sizeof(ALT_PEN20_WARU_MOZAEMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_WERE_GARURUMON_FQID_ARR[] = "pen20:were_garurumon";
    inline static constexpr const char* ALT_PEN20_WERE_GARURUMON_FQID = ALT_PEN20_WERE_GARURUMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_WERE_GARURUMON_FQID_LEN = sizeof(ALT_PEN20_WERE_GARURUMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_WERE_GARURUMON_FQNAME_ARR[] = "pen20:Were Garurumon";
    inline static constexpr const char* ALT_PEN20_WERE_GARURUMON_FQNAME = ALT_PEN20_WERE_GARURUMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_WERE_GARURUMON_FQNAME_LEN = sizeof(ALT_PEN20_WERE_GARURUMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_WHAMON_FQID_ARR[] = "pen20:whamon";
    inline static constexpr const char* ALT_PEN20_WHAMON_FQID = ALT_PEN20_WHAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_WHAMON_FQID_LEN = sizeof(ALT_PEN20_WHAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_WHAMON_FQNAME_ARR[] = "pen20:Whamon";
    inline static constexpr const char* ALT_PEN20_WHAMON_FQNAME = ALT_PEN20_WHAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_WHAMON_FQNAME_LEN = sizeof(ALT_PEN20_WHAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_WINGDRAMON_FQID_ARR[] = "pen20:wingdramon";
    inline static constexpr const char* ALT_PEN20_WINGDRAMON_FQID = ALT_PEN20_WINGDRAMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_WINGDRAMON_FQID_LEN = sizeof(ALT_PEN20_WINGDRAMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_WINGDRAMON_FQNAME_ARR[] = "pen20:Wingdramon";
    inline static constexpr const char* ALT_PEN20_WINGDRAMON_FQNAME = ALT_PEN20_WINGDRAMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_WINGDRAMON_FQNAME_LEN = sizeof(ALT_PEN20_WINGDRAMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_WIZARMON_FQID_ARR[] = "pen20:wizarmon";
    inline static constexpr const char* ALT_PEN20_WIZARMON_FQID = ALT_PEN20_WIZARMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_WIZARMON_FQID_LEN = sizeof(ALT_PEN20_WIZARMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_WIZARMON_FQNAME_ARR[] = "pen20:Wizarmon";
    inline static constexpr const char* ALT_PEN20_WIZARMON_FQNAME = ALT_PEN20_WIZARMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_WIZARMON_FQNAME_LEN = sizeof(ALT_PEN20_WIZARMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_WOODMON_FQID_ARR[] = "pen20:woodmon";
    inline static constexpr const char* ALT_PEN20_WOODMON_FQID = ALT_PEN20_WOODMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_WOODMON_FQID_LEN = sizeof(ALT_PEN20_WOODMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_WOODMON_FQNAME_ARR[] = "pen20:Woodmon";
    inline static constexpr const char* ALT_PEN20_WOODMON_FQNAME = ALT_PEN20_WOODMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_WOODMON_FQNAME_LEN = sizeof(ALT_PEN20_WOODMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_XV_MON_FQID_ARR[] = "pen20:xv_mon";
    inline static constexpr const char* ALT_PEN20_XV_MON_FQID = ALT_PEN20_XV_MON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_XV_MON_FQID_LEN = sizeof(ALT_PEN20_XV_MON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_XV_MON_FQNAME_ARR[] = "pen20:XV-mon";
    inline static constexpr const char* ALT_PEN20_XV_MON_FQNAME = ALT_PEN20_XV_MON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_XV_MON_FQNAME_LEN = sizeof(ALT_PEN20_XV_MON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_ZERIMON_FQID_ARR[] = "pen20:zerimon";
    inline static constexpr const char* ALT_PEN20_ZERIMON_FQID = ALT_PEN20_ZERIMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_ZERIMON_FQID_LEN = sizeof(ALT_PEN20_ZERIMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_ZERIMON_FQNAME_ARR[] = "pen20:Zerimon";
    inline static constexpr const char* ALT_PEN20_ZERIMON_FQNAME = ALT_PEN20_ZERIMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_ZERIMON_FQNAME_LEN = sizeof(ALT_PEN20_ZERIMON_FQNAME_ARR)-1;
    inline static constexpr char ALT_PEN20_ZUDOMON_FQID_ARR[] = "pen20:zudomon";
    inline static constexpr const char* ALT_PEN20_ZUDOMON_FQID = ALT_PEN20_ZUDOMON_FQID_ARR;
    inline static constexpr size_t ALT_PEN20_ZUDOMON_FQID_LEN = sizeof(ALT_PEN20_ZUDOMON_FQID_ARR)-1;
    inline static constexpr char ALT_PEN20_ZUDOMON_FQNAME_ARR[] = "pen20:Zudomon";
    inline static constexpr const char* ALT_PEN20_ZUDOMON_FQNAME = ALT_PEN20_ZUDOMON_FQNAME_ARR;
    inline static constexpr size_t ALT_PEN20_ZUDOMON_FQNAME_LEN = sizeof(ALT_PEN20_ZUDOMON_FQNAME_ARR)-1;


    static const config_animation_entry_t pen20_alt_animation_table[] = {
        { PEN20_AERO_V_DRAMON_NAME, PEN20_AERO_V_DRAMON_ID, ALT_PEN20_AERO_V_DRAMON_FQID, ALT_PEN20_AERO_V_DRAMON_FQNAME, PEN20_AERO_V_DRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Aero V-dramon
        { PEN20_AGUMON_HAKASE_NAME, PEN20_AGUMON_HAKASE_ID, ALT_PEN20_AGUMON_HAKASE_FQID, ALT_PEN20_AGUMON_HAKASE_FQNAME, PEN20_AGUMON_HAKASE_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Agumon Hakase
        { PEN20_ALPHAMON_OURYUKEN_NAME, PEN20_ALPHAMON_OURYUKEN_ID, ALT_PEN20_ALPHAMON_OURYUKEN_FQID, ALT_PEN20_ALPHAMON_OURYUKEN_FQNAME, PEN20_ALPHAMON_OURYUKEN_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Alphamon Ouryuken
        { PEN20_ANDIRAMON_NAME, PEN20_ANDIRAMON_ID, ALT_PEN20_ANDIRAMON_FQID, ALT_PEN20_ANDIRAMON_FQNAME, PEN20_ANDIRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Andiramon
        { PEN20_ANDROMON_NAME, PEN20_ANDROMON_ID, ALT_PEN20_ANDROMON_FQID, ALT_PEN20_ANDROMON_FQNAME, PEN20_ANDROMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Andromon
        { PEN20_ANGEWOMON_NAME, PEN20_ANGEWOMON_ID, ALT_PEN20_ANGEWOMON_FQID, ALT_PEN20_ANGEWOMON_FQNAME, PEN20_ANGEWOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Angewomon
        { PEN20_ANOMALOCARIMON_NAME, PEN20_ANOMALOCARIMON_ID, ALT_PEN20_ANOMALOCARIMON_FQID, ALT_PEN20_ANOMALOCARIMON_FQNAME, PEN20_ANOMALOCARIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Anomalocarimon
        { PEN20_ARRESTERDRAMON_NAME, PEN20_ARRESTERDRAMON_ID, ALT_PEN20_ARRESTERDRAMON_FQID, ALT_PEN20_ARRESTERDRAMON_FQNAME, PEN20_ARRESTERDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Arresterdramon
        { PEN20_ASTAMON_NAME, PEN20_ASTAMON_ID, ALT_PEN20_ASTAMON_FQID, ALT_PEN20_ASTAMON_FQNAME, PEN20_ASTAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Astamon
        { PEN20_ASTRAMON_NAME, PEN20_ASTRAMON_ID, ALT_PEN20_ASTRAMON_FQID, ALT_PEN20_ASTRAMON_FQNAME, PEN20_ASTRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Astramon
        { PEN20_ASURAMON_NAME, PEN20_ASURAMON_ID, ALT_PEN20_ASURAMON_FQID, ALT_PEN20_ASURAMON_FQNAME, PEN20_ASURAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Asuramon
        { PEN20_ATLUR_KABUTERIMON_NAME, PEN20_ATLUR_KABUTERIMON_ID, ALT_PEN20_ATLUR_KABUTERIMON_FQID, ALT_PEN20_ATLUR_KABUTERIMON_FQNAME, PEN20_ATLUR_KABUTERIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Atlur Kabuterimon
        { PEN20_BAALMON_NAME, PEN20_BAALMON_ID, ALT_PEN20_BAALMON_FQID, ALT_PEN20_BAALMON_FQNAME, PEN20_BAALMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Baalmon
        { PEN20_BAKEMON_NAME, PEN20_BAKEMON_ID, ALT_PEN20_BAKEMON_FQID, ALT_PEN20_BAKEMON_FQNAME, PEN20_BAKEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Bakemon
        { PEN20_BAKUMON_NAME, PEN20_BAKUMON_ID, ALT_PEN20_BAKUMON_FQID, ALT_PEN20_BAKUMON_FQNAME, PEN20_BAKUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Bakumon
        { PEN20_BANCHO_LEOMON_NAME, PEN20_BANCHO_LEOMON_ID, ALT_PEN20_BANCHO_LEOMON_FQID, ALT_PEN20_BANCHO_LEOMON_FQNAME, PEN20_BANCHO_LEOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Bancho Leomon
        { PEN20_BEELZEBUMON_BLAST_MODE_NAME, PEN20_BEELZEBUMON_BLAST_MODE_ID, ALT_PEN20_BEELZEBUMON_BLAST_MODE_FQID, ALT_PEN20_BEELZEBUMON_BLAST_MODE_FQNAME, PEN20_BEELZEBUMON_BLAST_MODE_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Beelzebumon Blast Mode
        { PEN20_BEOWOLFMON_NAME, PEN20_BEOWOLFMON_ID, ALT_PEN20_BEOWOLFMON_FQID, ALT_PEN20_BEOWOLFMON_FQNAME, PEN20_BEOWOLFMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Beowolfmon
        { PEN20_BEOWULFMON_NAME, PEN20_BEOWULFMON_ID, ALT_PEN20_BEOWULFMON_FQID, ALT_PEN20_BEOWULFMON_FQNAME, PEN20_BEOWULFMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Beowulfmon
        { PEN20_BIG_MAMEMON_NAME, PEN20_BIG_MAMEMON_ID, ALT_PEN20_BIG_MAMEMON_FQID, ALT_PEN20_BIG_MAMEMON_FQNAME, PEN20_BIG_MAMEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Big Mamemon
        { PEN20_BIRDRAMON_NAME, PEN20_BIRDRAMON_ID, ALT_PEN20_BIRDRAMON_FQID, ALT_PEN20_BIRDRAMON_FQNAME, PEN20_BIRDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Birdramon
        { PEN20_BLOSSOMON_NAME, PEN20_BLOSSOMON_ID, ALT_PEN20_BLOSSOMON_FQID, ALT_PEN20_BLOSSOMON_FQNAME, PEN20_BLOSSOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Blossomon
        { PEN20_BOLTMON_NAME, PEN20_BOLTMON_ID, ALT_PEN20_BOLTMON_FQID, ALT_PEN20_BOLTMON_FQNAME, PEN20_BOLTMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Boltmon
        { PEN20_BREAKDRAMON_NAME, PEN20_BREAKDRAMON_ID, ALT_PEN20_BREAKDRAMON_FQID, ALT_PEN20_BREAKDRAMON_FQNAME, PEN20_BREAKDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Breakdramon
        { PEN20_BRYWELUDRAMON_NAME, PEN20_BRYWELUDRAMON_ID, ALT_PEN20_BRYWELUDRAMON_FQID, ALT_PEN20_BRYWELUDRAMON_FQNAME, PEN20_BRYWELUDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Bryweludramon
        { PEN20_BUBBMON_NAME, PEN20_BUBBMON_ID, ALT_PEN20_BUBBMON_FQID, ALT_PEN20_BUBBMON_FQNAME, PEN20_BUBBMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Bubbmon
        { PEN20_BUDMON_NAME, PEN20_BUDMON_ID, ALT_PEN20_BUDMON_FQID, ALT_PEN20_BUDMON_FQNAME, PEN20_BUDMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Budmon
        { PEN20_BUSHI_AGUMON_NAME, PEN20_BUSHI_AGUMON_ID, ALT_PEN20_BUSHI_AGUMON_FQID, ALT_PEN20_BUSHI_AGUMON_FQNAME, PEN20_BUSHI_AGUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Bushi Agumon
        { PEN20_CANDMON_NAME, PEN20_CANDMON_ID, ALT_PEN20_CANDMON_FQID, ALT_PEN20_CANDMON_FQNAME, PEN20_CANDMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Candmon
        { PEN20_CAPRIMON_NAME, PEN20_CAPRIMON_ID, ALT_PEN20_CAPRIMON_FQID, ALT_PEN20_CAPRIMON_FQNAME, PEN20_CAPRIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Caprimon
        { PEN20_CHAOSMON_NAME, PEN20_CHAOSMON_ID, ALT_PEN20_CHAOSMON_FQID, ALT_PEN20_CHAOSMON_FQNAME, PEN20_CHAOSMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Chaosmon
        { PEN20_CHERUBIMON_NAME, PEN20_CHERUBIMON_ID, ALT_PEN20_CHERUBIMON_FQID, ALT_PEN20_CHERUBIMON_FQNAME, PEN20_CHERUBIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Cherubimon
        { PEN20_CHIBIMON_NAME, PEN20_CHIBIMON_ID, ALT_PEN20_CHIBIMON_FQID, ALT_PEN20_CHIBIMON_FQNAME, PEN20_CHIBIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Chibimon
        { PEN20_CHICOMON_NAME, PEN20_CHICOMON_ID, ALT_PEN20_CHICOMON_FQID, ALT_PEN20_CHICOMON_FQNAME, PEN20_CHICOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Chicomon
        { PEN20_CHOROMON_NAME, PEN20_CHOROMON_ID, ALT_PEN20_CHOROMON_FQID, ALT_PEN20_CHOROMON_FQNAME, PEN20_CHOROMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Choromon
        { PEN20_CLOCKMON_NAME, PEN20_CLOCKMON_ID, ALT_PEN20_CLOCKMON_FQID, ALT_PEN20_CLOCKMON_FQNAME, PEN20_CLOCKMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Clockmon
        { PEN20_COCOMON_NAME, PEN20_COCOMON_ID, ALT_PEN20_COCOMON_FQID, ALT_PEN20_COCOMON_FQNAME, PEN20_COCOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Cocomon
        { PEN20_COELAMON_NAME, PEN20_COELAMON_ID, ALT_PEN20_COELAMON_FQID, ALT_PEN20_COELAMON_FQNAME, PEN20_COELAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Coelamon
        { PEN20_COREDRAMON_BLUE_NAME, PEN20_COREDRAMON_BLUE_ID, ALT_PEN20_COREDRAMON_BLUE_FQID, ALT_PEN20_COREDRAMON_BLUE_FQNAME, PEN20_COREDRAMON_BLUE_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Coredramon (Blue)
        { PEN20_COREDRAMON_GREEN_NAME, PEN20_COREDRAMON_GREEN_ID, ALT_PEN20_COREDRAMON_GREEN_FQID, ALT_PEN20_COREDRAMON_GREEN_FQNAME, PEN20_COREDRAMON_GREEN_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Coredramon (Green)
        { PEN20_COTSUCOMON_NAME, PEN20_COTSUCOMON_ID, ALT_PEN20_COTSUCOMON_FQID, ALT_PEN20_COTSUCOMON_FQNAME, PEN20_COTSUCOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Cotsucomon
        { PEN20_CYBERDRAMON_NAME, PEN20_CYBERDRAMON_ID, ALT_PEN20_CYBERDRAMON_FQID, ALT_PEN20_CYBERDRAMON_FQNAME, PEN20_CYBERDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Cyberdramon
        { PEN20_DAGOMON_NAME, PEN20_DAGOMON_ID, ALT_PEN20_DAGOMON_FQID, ALT_PEN20_DAGOMON_FQNAME, PEN20_DAGOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Dagomon
        { PEN20_DARKDRAMON_NAME, PEN20_DARKDRAMON_ID, ALT_PEN20_DARKDRAMON_FQID, ALT_PEN20_DARKDRAMON_FQNAME, PEN20_DARKDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Darkdramon
        { PEN20_DARK_KNIGHTMON_NAME, PEN20_DARK_KNIGHTMON_ID, ALT_PEN20_DARK_KNIGHTMON_FQID, ALT_PEN20_DARK_KNIGHTMON_FQNAME, PEN20_DARK_KNIGHTMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Dark Knightmon
        { PEN20_DEATH_MERAMON_NAME, PEN20_DEATH_MERAMON_ID, ALT_PEN20_DEATH_MERAMON_FQID, ALT_PEN20_DEATH_MERAMON_FQNAME, PEN20_DEATH_MERAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Death Meramon
        { PEN20_DELUMON_NAME, PEN20_DELUMON_ID, ALT_PEN20_DELUMON_FQID, ALT_PEN20_DELUMON_FQNAME, PEN20_DELUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Delumon
        { PEN20_DEVIDRAMON_NAME, PEN20_DEVIDRAMON_ID, ALT_PEN20_DEVIDRAMON_FQID, ALT_PEN20_DEVIDRAMON_FQNAME, PEN20_DEVIDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Devidramon
        { PEN20_DEVIMON_NAME, PEN20_DEVIMON_ID, ALT_PEN20_DEVIMON_FQID, ALT_PEN20_DEVIMON_FQNAME, PEN20_DEVIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Devimon
        { PEN20_DOKUGUMON_NAME, PEN20_DOKUGUMON_ID, ALT_PEN20_DOKUGUMON_FQID, ALT_PEN20_DOKUGUMON_FQNAME, PEN20_DOKUGUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Dokugumon
        { PEN20_DORUGORAMON_NAME, PEN20_DORUGORAMON_ID, ALT_PEN20_DORUGORAMON_FQID, ALT_PEN20_DORUGORAMON_FQNAME, PEN20_DORUGORAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for DORUgoramon
        { PEN20_DURAMON_NAME, PEN20_DURAMON_ID, ALT_PEN20_DURAMON_FQID, ALT_PEN20_DURAMON_FQNAME, PEN20_DURAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Duramon
        { PEN20_DURANDAMON_NAME, PEN20_DURANDAMON_ID, ALT_PEN20_DURANDAMON_FQID, ALT_PEN20_DURANDAMON_FQNAME, PEN20_DURANDAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Durandamon
        { PEN20_EBIDRAMON_NAME, PEN20_EBIDRAMON_ID, ALT_PEN20_EBIDRAMON_FQID, ALT_PEN20_EBIDRAMON_FQNAME, PEN20_EBIDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Ebidramon
        { PEN20_ETEMON_NAME, PEN20_ETEMON_ID, ALT_PEN20_ETEMON_FQID, ALT_PEN20_ETEMON_FQNAME, PEN20_ETEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Etemon
        { PEN20_EXAMON_NAME, PEN20_EXAMON_ID, ALT_PEN20_EXAMON_FQID, ALT_PEN20_EXAMON_FQNAME, PEN20_EXAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Examon
        { PEN20_FANTOMON_NAME, PEN20_FANTOMON_ID, ALT_PEN20_FANTOMON_FQID, ALT_PEN20_FANTOMON_FQNAME, PEN20_FANTOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Fantomon
        { PEN20_FLORAMON_NAME, PEN20_FLORAMON_ID, ALT_PEN20_FLORAMON_FQID, ALT_PEN20_FLORAMON_FQNAME, PEN20_FLORAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Floramon
        { PEN20_FUFUMON_NAME, PEN20_FUFUMON_ID, ALT_PEN20_FUFUMON_FQID, ALT_PEN20_FUFUMON_FQNAME, PEN20_FUFUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Fufumon
        { PEN20_GALGOMON_NAME, PEN20_GALGOMON_ID, ALT_PEN20_GALGOMON_FQID, ALT_PEN20_GALGOMON_FQNAME, PEN20_GALGOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Galgomon
        { PEN20_GANIMON_NAME, PEN20_GANIMON_ID, ALT_PEN20_GANIMON_FQID, ALT_PEN20_GANIMON_FQNAME, PEN20_GANIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Ganimon
        { PEN20_GARUDAMON_NAME, PEN20_GARUDAMON_ID, ALT_PEN20_GARUDAMON_FQID, ALT_PEN20_GARUDAMON_FQNAME, PEN20_GARUDAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Garudamon
        { PEN20_GARURUMON_NAME, PEN20_GARURUMON_ID, ALT_PEN20_GARURUMON_FQID, ALT_PEN20_GARURUMON_FQNAME, PEN20_GARURUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Garurumon
        { PEN20_GEKOMON_NAME, PEN20_GEKOMON_ID, ALT_PEN20_GEKOMON_FQID, ALT_PEN20_GEKOMON_FQNAME, PEN20_GEKOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Gekomon
        { PEN20_GERBEMON_NAME, PEN20_GERBEMON_ID, ALT_PEN20_GERBEMON_FQID, ALT_PEN20_GERBEMON_FQNAME, PEN20_GERBEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Gerbemon
        { PEN20_GESOMON_NAME, PEN20_GESOMON_ID, ALT_PEN20_GESOMON_FQID, ALT_PEN20_GESOMON_FQNAME, PEN20_GESOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Gesomon
        { PEN20_GINRYUMON_NAME, PEN20_GINRYUMON_ID, ALT_PEN20_GINRYUMON_FQID, ALT_PEN20_GINRYUMON_FQNAME, PEN20_GINRYUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Ginryumon
        { PEN20_GOMAMON_NAME, PEN20_GOMAMON_ID, ALT_PEN20_GOMAMON_FQID, ALT_PEN20_GOMAMON_FQNAME, PEN20_GOMAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Gomamon
        { PEN20_GOTTSUMON_NAME, PEN20_GOTTSUMON_ID, ALT_PEN20_GOTTSUMON_FQID, ALT_PEN20_GOTTSUMON_FQNAME, PEN20_GOTTSUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Gottsumon
        { PEN20_GREYMON_NAME, PEN20_GREYMON_ID, ALT_PEN20_GREYMON_FQID, ALT_PEN20_GREYMON_FQNAME, PEN20_GREYMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Greymon
        { PEN20_GRIFFOMON_NAME, PEN20_GRIFFOMON_ID, ALT_PEN20_GRIFFOMON_FQID, ALT_PEN20_GRIFFOMON_FQNAME, PEN20_GRIFFOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Griffomon
        { PEN20_GROUNDRAMON_NAME, PEN20_GROUNDRAMON_ID, ALT_PEN20_GROUNDRAMON_FQID, ALT_PEN20_GROUNDRAMON_FQNAME, PEN20_GROUNDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Groundramon
        { PEN20_GROWMON_NAME, PEN20_GROWMON_ID, ALT_PEN20_GROWMON_FQID, ALT_PEN20_GROWMON_FQNAME, PEN20_GROWMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Growmon
        { PEN20_GUARDROMON_NAME, PEN20_GUARDROMON_ID, ALT_PEN20_GUARDROMON_FQID, ALT_PEN20_GUARDROMON_FQNAME, PEN20_GUARDROMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Guardromon
        { PEN20_GUIMON_NAME, PEN20_GUIMON_ID, ALT_PEN20_GUIMON_FQID, ALT_PEN20_GUIMON_FQNAME, PEN20_GUIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Guimon
        { PEN20_GUMMYMON_NAME, PEN20_GUMMYMON_ID, ALT_PEN20_GUMMYMON_FQID, ALT_PEN20_GUMMYMON_FQNAME, PEN20_GUMMYMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Gummymon
        { PEN20_HAGURUMON_NAME, PEN20_HAGURUMON_ID, ALT_PEN20_HAGURUMON_FQID, ALT_PEN20_HAGURUMON_FQNAME, PEN20_HAGURUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Hagurumon
        { PEN20_HANGYMON_NAME, PEN20_HANGYMON_ID, ALT_PEN20_HANGYMON_FQID, ALT_PEN20_HANGYMON_FQNAME, PEN20_HANGYMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Hangymon
        { PEN20_HANGYOMON_NAME, PEN20_HANGYOMON_ID, ALT_PEN20_HANGYOMON_FQID, ALT_PEN20_HANGYOMON_FQNAME, PEN20_HANGYOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Hangyomon
        { PEN20_HANUMON_NAME, PEN20_HANUMON_ID, ALT_PEN20_HANUMON_FQID, ALT_PEN20_HANUMON_FQNAME, PEN20_HANUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Hanumon
        { PEN20_HERAKLE_KABUTERIMON_NAME, PEN20_HERAKLE_KABUTERIMON_ID, ALT_PEN20_HERAKLE_KABUTERIMON_FQID, ALT_PEN20_HERAKLE_KABUTERIMON_FQNAME, PEN20_HERAKLE_KABUTERIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Herakle Kabuterimon
        { PEN20_HERKULE_KABUTERIMON_NAME, PEN20_HERKULE_KABUTERIMON_ID, ALT_PEN20_HERKULE_KABUTERIMON_FQID, ALT_PEN20_HERKULE_KABUTERIMON_FQNAME, PEN20_HERKULE_KABUTERIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Herkule Kabuterimon
        { PEN20_HISYARYUMON_NAME, PEN20_HISYARYUMON_ID, ALT_PEN20_HISYARYUMON_FQID, ALT_PEN20_HISYARYUMON_FQNAME, PEN20_HISYARYUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Hisyaryumon
        { PEN20_HOLY_ANGEMON_NAME, PEN20_HOLY_ANGEMON_ID, ALT_PEN20_HOLY_ANGEMON_FQID, ALT_PEN20_HOLY_ANGEMON_FQNAME, PEN20_HOLY_ANGEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Holy Angemon
        { PEN20_HOLYDRAMON_NAME, PEN20_HOLYDRAMON_ID, ALT_PEN20_HOLYDRAMON_FQID, ALT_PEN20_HOLYDRAMON_FQNAME, PEN20_HOLYDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Holydramon
        { PEN20_HOUOUMON_NAME, PEN20_HOUOUMON_ID, ALT_PEN20_HOUOUMON_FQID, ALT_PEN20_HOUOUMON_FQNAME, PEN20_HOUOUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Hououmon
        { PEN20_IGNAMON_NAME, PEN20_IGNAMON_ID, ALT_PEN20_IGNAMON_FQID, ALT_PEN20_IGNAMON_FQNAME, PEN20_IGNAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Ignamon
        { PEN20_IKKAKUMON_NAME, PEN20_IKKAKUMON_ID, ALT_PEN20_IKKAKUMON_FQID, ALT_PEN20_IKKAKUMON_FQNAME, PEN20_IKKAKUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Ikkakumon
        { PEN20_IMPERIALDRAMON_FIGHTER_MODE_NAME, PEN20_IMPERIALDRAMON_FIGHTER_MODE_ID, ALT_PEN20_IMPERIALDRAMON_FIGHTER_MODE_FQID, ALT_PEN20_IMPERIALDRAMON_FIGHTER_MODE_FQNAME, PEN20_IMPERIALDRAMON_FIGHTER_MODE_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Imperialdramon Fighter Mode
        { PEN20_IMPMON_NAME, PEN20_IMPMON_ID, ALT_PEN20_IMPMON_FQID, ALT_PEN20_IMPMON_FQNAME, PEN20_IMPMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Impmon
        { PEN20_JESMON_NAME, PEN20_JESMON_ID, ALT_PEN20_JESMON_FQID, ALT_PEN20_JESMON_FQNAME, PEN20_JESMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Jesmon
        { PEN20_JESMON_X_NAME, PEN20_JESMON_X_ID, ALT_PEN20_JESMON_X_FQID, ALT_PEN20_JESMON_X_FQNAME, PEN20_JESMON_X_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Jesmon X
        { PEN20_JYAGAMON_NAME, PEN20_JYAGAMON_ID, ALT_PEN20_JYAGAMON_FQID, ALT_PEN20_JYAGAMON_FQNAME, PEN20_JYAGAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Jyagamon
        { PEN20_JYUREIMON_NAME, PEN20_JYUREIMON_ID, ALT_PEN20_JYUREIMON_FQID, ALT_PEN20_JYUREIMON_FQNAME, PEN20_JYUREIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Jyureimon
        { PEN20_KABUTERIMON_NAME, PEN20_KABUTERIMON_ID, ALT_PEN20_KABUTERIMON_FQID, ALT_PEN20_KABUTERIMON_FQNAME, PEN20_KABUTERIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Kabuterimon
        { PEN20_KAKKINMON_NAME, PEN20_KAKKINMON_ID, ALT_PEN20_KAKKINMON_FQID, ALT_PEN20_KAKKINMON_FQNAME, PEN20_KAKKINMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Kakkinmon
        { PEN20_KIWIMON_NAME, PEN20_KIWIMON_ID, ALT_PEN20_KIWIMON_FQID, ALT_PEN20_KIWIMON_FQNAME, PEN20_KIWIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Kiwimon
        { PEN20_KNIGHTMON_NAME, PEN20_KNIGHTMON_ID, ALT_PEN20_KNIGHTMON_FQID, ALT_PEN20_KNIGHTMON_FQNAME, PEN20_KNIGHTMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Knightmon
        { PEN20_KOKUWAMON_NAME, PEN20_KOKUWAMON_ID, ALT_PEN20_KOKUWAMON_FQID, ALT_PEN20_KOKUWAMON_FQNAME, PEN20_KOKUWAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Kokuwamon
        { PEN20_KUWAGAMON_NAME, PEN20_KUWAGAMON_ID, ALT_PEN20_KUWAGAMON_FQID, ALT_PEN20_KUWAGAMON_FQNAME, PEN20_KUWAGAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Kuwagamon
        { PEN20_KYOKYOMON_NAME, PEN20_KYOKYOMON_ID, ALT_PEN20_KYOKYOMON_FQID, ALT_PEN20_KYOKYOMON_FQNAME, PEN20_KYOKYOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Kyokyomon
        { PEN20_LADY_DEVIMON_NAME, PEN20_LADY_DEVIMON_ID, ALT_PEN20_LADY_DEVIMON_FQID, ALT_PEN20_LADY_DEVIMON_FQNAME, PEN20_LADY_DEVIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Lady Devimon
        { PEN20_LALAMON_NAME, PEN20_LALAMON_ID, ALT_PEN20_LALAMON_FQID, ALT_PEN20_LALAMON_FQNAME, PEN20_LALAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Lalamon
        { PEN20_LAVOGARITAMON_NAME, PEN20_LAVOGARITAMON_ID, ALT_PEN20_LAVOGARITAMON_FQID, ALT_PEN20_LAVOGARITAMON_FQNAME, PEN20_LAVOGARITAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Lavogaritamon
        { PEN20_LAVORVOMON_NAME, PEN20_LAVORVOMON_ID, ALT_PEN20_LAVORVOMON_FQID, ALT_PEN20_LAVORVOMON_FQNAME, PEN20_LAVORVOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Lavorvomon
        { PEN20_LILAMON_NAME, PEN20_LILAMON_ID, ALT_PEN20_LILAMON_FQID, ALT_PEN20_LILAMON_FQNAME, PEN20_LILAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Lilamon
        { PEN20_LILIMON_NAME, PEN20_LILIMON_ID, ALT_PEN20_LILIMON_FQID, ALT_PEN20_LILIMON_FQNAME, PEN20_LILIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Lilimon
        { PEN20_LOPMON_NAME, PEN20_LOPMON_ID, ALT_PEN20_LOPMON_FQID, ALT_PEN20_LOPMON_FQNAME, PEN20_LOPMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Lopmon
        { PEN20_LOTUSMON_NAME, PEN20_LOTUSMON_ID, ALT_PEN20_LOTUSMON_FQID, ALT_PEN20_LOTUSMON_FQNAME, PEN20_LOTUSMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Lotusmon
        { PEN20_LUDOMON_NAME, PEN20_LUDOMON_ID, ALT_PEN20_LUDOMON_FQID, ALT_PEN20_LUDOMON_FQNAME, PEN20_LUDOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Ludomon
        { PEN20_MAD_LEOMON_NAME, PEN20_MAD_LEOMON_ID, ALT_PEN20_MAD_LEOMON_FQID, ALT_PEN20_MAD_LEOMON_FQNAME, PEN20_MAD_LEOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Mad Leomon
        { PEN20_MAMBOMON_NAME, PEN20_MAMBOMON_ID, ALT_PEN20_MAMBOMON_FQID, ALT_PEN20_MAMBOMON_FQNAME, PEN20_MAMBOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Mambomon
        { PEN20_MAMMON_NAME, PEN20_MAMMON_ID, ALT_PEN20_MAMMON_FQID, ALT_PEN20_MAMMON_FQNAME, PEN20_MAMMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Mammon
        { PEN20_MANBOMON_NAME, PEN20_MANBOMON_ID, ALT_PEN20_MANBOMON_FQID, ALT_PEN20_MANBOMON_FQNAME, PEN20_MANBOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Manbomon
        { PEN20_MARIN_ANGEMON_NAME, PEN20_MARIN_ANGEMON_ID, ALT_PEN20_MARIN_ANGEMON_FQID, ALT_PEN20_MARIN_ANGEMON_FQNAME, PEN20_MARIN_ANGEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Marin Angemon
        { PEN20_MARIN_DEVIMON_NAME, PEN20_MARIN_DEVIMON_ID, ALT_PEN20_MARIN_DEVIMON_FQID, ALT_PEN20_MARIN_DEVIMON_FQNAME, PEN20_MARIN_DEVIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Marin Devimon
        { PEN20_MASTEMON_NAME, PEN20_MASTEMON_ID, ALT_PEN20_MASTEMON_FQID, ALT_PEN20_MASTEMON_FQNAME, PEN20_MASTEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Mastemon
        { PEN20_MECHANORIMON_NAME, PEN20_MECHANORIMON_ID, ALT_PEN20_MECHANORIMON_FQID, ALT_PEN20_MECHANORIMON_FQNAME, PEN20_MECHANORIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Mechanorimon
        { PEN20_MEGADRAMON_NAME, PEN20_MEGADRAMON_ID, ALT_PEN20_MEGADRAMON_FQID, ALT_PEN20_MEGADRAMON_FQNAME, PEN20_MEGADRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Megadramon
        { PEN20_MEGALO_GROWMON_NAME, PEN20_MEGALO_GROWMON_ID, ALT_PEN20_MEGALO_GROWMON_FQID, ALT_PEN20_MEGALO_GROWMON_FQNAME, PEN20_MEGALO_GROWMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Megalo Growmon
        { PEN20_MEGA_SEADRAMON_NAME, PEN20_MEGA_SEADRAMON_ID, ALT_PEN20_MEGA_SEADRAMON_FQID, ALT_PEN20_MEGA_SEADRAMON_FQNAME, PEN20_MEGA_SEADRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Mega Seadramon
        { PEN20_MEICRACKMON_VICIOUS_MODE_NAME, PEN20_MEICRACKMON_VICIOUS_MODE_ID, ALT_PEN20_MEICRACKMON_VICIOUS_MODE_FQID, ALT_PEN20_MEICRACKMON_VICIOUS_MODE_FQNAME, PEN20_MEICRACKMON_VICIOUS_MODE_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Meicrackmon Vicious Mode
        { PEN20_MERAMON_NAME, PEN20_MERAMON_ID, ALT_PEN20_MERAMON_FQID, ALT_PEN20_MERAMON_FQNAME, PEN20_MERAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Meramon
        { PEN20_METAL_ETEMON_NAME, PEN20_METAL_ETEMON_ID, ALT_PEN20_METAL_ETEMON_FQID, ALT_PEN20_METAL_ETEMON_FQNAME, PEN20_METAL_ETEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Metal Etemon
        { PEN20_METAL_GARURUMON_NAME, PEN20_METAL_GARURUMON_ID, ALT_PEN20_METAL_GARURUMON_FQID, ALT_PEN20_METAL_GARURUMON_FQNAME, PEN20_METAL_GARURUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Metal Garurumon
        { PEN20_METAL_GREYMON_NAME, PEN20_METAL_GREYMON_ID, ALT_PEN20_METAL_GREYMON_FQID, ALT_PEN20_METAL_GREYMON_FQNAME, PEN20_METAL_GREYMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Metal Greymon
        { PEN20_METAL_MAMEMON_NAME, PEN20_METAL_MAMEMON_ID, ALT_PEN20_METAL_MAMEMON_FQID, ALT_PEN20_METAL_MAMEMON_FQNAME, PEN20_METAL_MAMEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Metal Mamemon
        { PEN20_METAL_SEADRAMON_NAME, PEN20_METAL_SEADRAMON_ID, ALT_PEN20_METAL_SEADRAMON_FQID, ALT_PEN20_METAL_SEADRAMON_FQNAME, PEN20_METAL_SEADRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Metal Seadramon
        { PEN20_MOCHIMON_NAME, PEN20_MOCHIMON_ID, ALT_PEN20_MOCHIMON_FQID, ALT_PEN20_MOCHIMON_FQNAME, PEN20_MOCHIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Mochimon
        { PEN20_MOKUMON_NAME, PEN20_MOKUMON_ID, ALT_PEN20_MOKUMON_FQID, ALT_PEN20_MOKUMON_FQNAME, PEN20_MOKUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Mokumon
        { PEN20_MONCHROMON_NAME, PEN20_MONCHROMON_ID, ALT_PEN20_MONCHROMON_FQID, ALT_PEN20_MONCHROMON_FQNAME, PEN20_MONCHROMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Monchromon
        { PEN20_MONOCHROMON_NAME, PEN20_MONOCHROMON_ID, ALT_PEN20_MONOCHROMON_FQID, ALT_PEN20_MONOCHROMON_FQNAME, PEN20_MONOCHROMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Monochromon
        { PEN20_MUGENDRAMON_NAME, PEN20_MUGENDRAMON_ID, ALT_PEN20_MUGENDRAMON_FQID, ALT_PEN20_MUGENDRAMON_FQNAME, PEN20_MUGENDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Mugendramon
        { PEN20_MUSHMON_NAME, PEN20_MUSHMON_ID, ALT_PEN20_MUSHMON_FQID, ALT_PEN20_MUSHMON_FQNAME, PEN20_MUSHMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Mushmon
        { PEN20_NYOKIMON_NAME, PEN20_NYOKIMON_ID, ALT_PEN20_NYOKIMON_FQID, ALT_PEN20_NYOKIMON_FQNAME, PEN20_NYOKIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Nyokimon
        { PEN20_OCTMON_NAME, PEN20_OCTMON_ID, ALT_PEN20_OCTMON_FQID, ALT_PEN20_OCTMON_FQNAME, PEN20_OCTMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Octmon
        { PEN20_OFANIMON_NAME, PEN20_OFANIMON_ID, ALT_PEN20_OFANIMON_FQID, ALT_PEN20_OFANIMON_FQNAME, PEN20_OFANIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Ofanimon
        { PEN20_OGUDOMON_NAME, PEN20_OGUDOMON_ID, ALT_PEN20_OGUDOMON_FQID, ALT_PEN20_OGUDOMON_FQNAME, PEN20_OGUDOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Ogudomon
        { PEN20_OKUWAMON_NAME, PEN20_OKUWAMON_ID, ALT_PEN20_OKUWAMON_FQID, ALT_PEN20_OKUWAMON_FQNAME, PEN20_OKUWAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Okuwamon
        { PEN20_OMEGAMON_NAME, PEN20_OMEGAMON_ID, ALT_PEN20_OMEGAMON_FQID, ALT_PEN20_OMEGAMON_FQNAME, PEN20_OMEGAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Omegamon
        { PEN20_ORDINEMON_NAME, PEN20_ORDINEMON_ID, ALT_PEN20_ORDINEMON_FQID, ALT_PEN20_ORDINEMON_FQNAME, PEN20_ORDINEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Ordinemon
        { PEN20_OTAMAMON_NAME, PEN20_OTAMAMON_ID, ALT_PEN20_OTAMAMON_FQID, ALT_PEN20_OTAMAMON_FQNAME, PEN20_OTAMAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Otamamon
        { PEN20_OURYUMON_NAME, PEN20_OURYUMON_ID, ALT_PEN20_OURYUMON_FQID, ALT_PEN20_OURYUMON_FQNAME, PEN20_OURYUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Ouryumon
        { PEN20_PAILDRAMON_NAME, PEN20_PAILDRAMON_ID, ALT_PEN20_PAILDRAMON_FQID, ALT_PEN20_PAILDRAMON_FQNAME, PEN20_PAILDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Paildramon
        { PEN20_PALMON_NAME, PEN20_PALMON_ID, ALT_PEN20_PALMON_FQID, ALT_PEN20_PALMON_FQNAME, PEN20_PALMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Palmon
        { PEN20_PETI_MERAMON_NAME, PEN20_PETI_MERAMON_ID, ALT_PEN20_PETI_MERAMON_FQID, ALT_PEN20_PETI_MERAMON_FQNAME, PEN20_PETI_MERAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Peti Meramon
        { PEN20_PHASCOMON_NAME, PEN20_PHASCOMON_ID, ALT_PEN20_PHASCOMON_FQID, ALT_PEN20_PHASCOMON_FQNAME, PEN20_PHASCOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Phascomon
        { PEN20_PICCOLOMON_NAME, PEN20_PICCOLOMON_ID, ALT_PEN20_PICCOLOMON_FQID, ALT_PEN20_PICCOLOMON_FQNAME, PEN20_PICCOLOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Piccolomon
        { PEN20_PICO_DEVIMON_NAME, PEN20_PICO_DEVIMON_ID, ALT_PEN20_PICO_DEVIMON_FQID, ALT_PEN20_PICO_DEVIMON_FQNAME, PEN20_PICO_DEVIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Pico Devimon
        { PEN20_PIEMON_NAME, PEN20_PIEMON_ID, ALT_PEN20_PIEMON_FQID, ALT_PEN20_PIEMON_FQNAME, PEN20_PIEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Piemon
        { PEN20_PINOCHIMON_NAME, PEN20_PINOCHIMON_ID, ALT_PEN20_PINOCHIMON_FQID, ALT_PEN20_PINOCHIMON_FQNAME, PEN20_PINOCHIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Pinochimon
        { PEN20_PIYOMON_NAME, PEN20_PIYOMON_ID, ALT_PEN20_PIYOMON_FQID, ALT_PEN20_PIYOMON_FQNAME, PEN20_PIYOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Piyomon
        { PEN20_PLESIOMON_NAME, PEN20_PLESIOMON_ID, ALT_PEN20_PLESIOMON_FQID, ALT_PEN20_PLESIOMON_FQNAME, PEN20_PLESIOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Plesiomon
        { PEN20_PORCUPAMON_NAME, PEN20_PORCUPAMON_ID, ALT_PEN20_PORCUPAMON_FQID, ALT_PEN20_PORCUPAMON_FQNAME, PEN20_PORCUPAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Porcupamon
        { PEN20_PORCUPMON_NAME, PEN20_PORCUPMON_ID, ALT_PEN20_PORCUPMON_FQID, ALT_PEN20_PORCUPMON_FQNAME, PEN20_PORCUPMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Porcupmon
        { PEN20_PUKUMON_NAME, PEN20_PUKUMON_ID, ALT_PEN20_PUKUMON_FQID, ALT_PEN20_PUKUMON_FQNAME, PEN20_PUKUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Pukumon
        { PEN20_PUMPMON_NAME, PEN20_PUMPMON_ID, ALT_PEN20_PUMPMON_FQID, ALT_PEN20_PUMPMON_FQNAME, PEN20_PUMPMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Pumpmon
        { PEN20_PYOCOMON_NAME, PEN20_PYOCOMON_ID, ALT_PEN20_PYOCOMON_FQID, ALT_PEN20_PYOCOMON_FQNAME, PEN20_PYOCOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Pyocomon
        { PEN20_RAFFLESIMON_NAME, PEN20_RAFFLESIMON_ID, ALT_PEN20_RAFFLESIMON_FQID, ALT_PEN20_RAFFLESIMON_FQNAME, PEN20_RAFFLESIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Rafflesimon
        { PEN20_RAGNA_LORDMON_NAME, PEN20_RAGNA_LORDMON_ID, ALT_PEN20_RAGNA_LORDMON_FQID, ALT_PEN20_RAGNA_LORDMON_FQNAME, PEN20_RAGNA_LORDMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Ragna Lordmon
        { PEN20_RAGUELMON_NAME, PEN20_RAGUELMON_ID, ALT_PEN20_RAGUELMON_FQID, ALT_PEN20_RAGUELMON_FQNAME, PEN20_RAGUELMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Raguelmon
        { PEN20_RAIJI_LUDOMON_NAME, PEN20_RAIJI_LUDOMON_ID, ALT_PEN20_RAIJI_LUDOMON_FQID, ALT_PEN20_RAIJI_LUDOMON_FQNAME, PEN20_RAIJI_LUDOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Raiji Ludomon
        { PEN20_RAKAMON_NAME, PEN20_RAKAMON_ID, ALT_PEN20_RAKAMON_FQID, ALT_PEN20_RAKAMON_FQNAME, PEN20_RAKAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Rakamon
        { PEN20_RAPIDMON_NAME, PEN20_RAPIDMON_ID, ALT_PEN20_RAPIDMON_FQID, ALT_PEN20_RAPIDMON_FQNAME, PEN20_RAPIDMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Rapidmon
        { PEN20_RED_VEGIMON_NAME, PEN20_RED_VEGIMON_ID, ALT_PEN20_RED_VEGIMON_FQID, ALT_PEN20_RED_VEGIMON_FQNAME, PEN20_RED_VEGIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Red Vegimon
        { PEN20_REPPAMON_NAME, PEN20_REPPAMON_ID, ALT_PEN20_REPPAMON_FQID, ALT_PEN20_REPPAMON_FQNAME, PEN20_REPPAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Reppamon
        { PEN20_REVOLMON_NAME, PEN20_REVOLMON_ID, ALT_PEN20_REVOLMON_FQID, ALT_PEN20_REVOLMON_FQNAME, PEN20_REVOLMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Revolmon
        { PEN20_RIZE_GREYMON_NAME, PEN20_RIZE_GREYMON_ID, ALT_PEN20_RIZE_GREYMON_FQID, ALT_PEN20_RIZE_GREYMON_FQNAME, PEN20_RIZE_GREYMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Rize Greymon
        { PEN20_ROSEMON_NAME, PEN20_ROSEMON_ID, ALT_PEN20_ROSEMON_FQID, ALT_PEN20_ROSEMON_FQNAME, PEN20_ROSEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Rosemon
        { PEN20_RUKAMON_NAME, PEN20_RUKAMON_ID, ALT_PEN20_RUKAMON_FQID, ALT_PEN20_RUKAMON_FQNAME, PEN20_RUKAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Rukamon
        { PEN20_RYUDAMON_NAME, PEN20_RYUDAMON_ID, ALT_PEN20_RYUDAMON_FQID, ALT_PEN20_RYUDAMON_FQNAME, PEN20_RYUDAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Ryudamon
        { PEN20_SABER_LEOMON_NAME, PEN20_SABER_LEOMON_ID, ALT_PEN20_SABER_LEOMON_FQID, ALT_PEN20_SABER_LEOMON_FQNAME, PEN20_SABER_LEOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Saber Leomon
        { PEN20_SAINT_GALGOMON_NAME, PEN20_SAINT_GALGOMON_ID, ALT_PEN20_SAINT_GALGOMON_FQID, ALT_PEN20_SAINT_GALGOMON_FQNAME, PEN20_SAINT_GALGOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Saint Galgomon
        { PEN20_SAVIOR_HACKMON_NAME, PEN20_SAVIOR_HACKMON_ID, ALT_PEN20_SAVIOR_HACKMON_FQID, ALT_PEN20_SAVIOR_HACKMON_FQNAME, PEN20_SAVIOR_HACKMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Savior Hackmon
        { PEN20_SEADRAMON_NAME, PEN20_SEADRAMON_ID, ALT_PEN20_SEADRAMON_FQID, ALT_PEN20_SEADRAMON_FQNAME, PEN20_SEADRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Seadramon
        { PEN20_SERAPHIMON_NAME, PEN20_SERAPHIMON_ID, ALT_PEN20_SERAPHIMON_FQID, ALT_PEN20_SERAPHIMON_FQNAME, PEN20_SERAPHIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Seraphimon
        { PEN20_SHADRAMON_NAME, PEN20_SHADRAMON_ID, ALT_PEN20_SHADRAMON_FQID, ALT_PEN20_SHADRAMON_FQNAME, PEN20_SHADRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Shadramon
        { PEN20_SHAKOMON_NAME, PEN20_SHAKOMON_ID, ALT_PEN20_SHAKOMON_FQID, ALT_PEN20_SHAKOMON_FQNAME, PEN20_SHAKOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Shakomon
        { PEN20_SKULL_MAMMON_NAME, PEN20_SKULL_MAMMON_ID, ALT_PEN20_SKULL_MAMMON_FQID, ALT_PEN20_SKULL_MAMMON_FQNAME, PEN20_SKULL_MAMMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Skull Mammon
        { PEN20_SLAYERDRAMON_NAME, PEN20_SLAYERDRAMON_ID, ALT_PEN20_SLAYERDRAMON_FQID, ALT_PEN20_SLAYERDRAMON_FQNAME, PEN20_SLAYERDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Slayerdramon
        { PEN20_STARMON_NAME, PEN20_STARMON_ID, ALT_PEN20_STARMON_FQID, ALT_PEN20_STARMON_FQNAME, PEN20_STARMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Starmon
        { PEN20_SUNFLOWMON_NAME, PEN20_SUNFLOWMON_ID, ALT_PEN20_SUNFLOWMON_FQID, ALT_PEN20_SUNFLOWMON_FQNAME, PEN20_SUNFLOWMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Sunflowmon
        { PEN20_TAILMON_NAME, PEN20_TAILMON_ID, ALT_PEN20_TAILMON_FQID, ALT_PEN20_TAILMON_FQNAME, PEN20_TAILMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Tailmon
        { PEN20_TANKMON_NAME, PEN20_TANKMON_ID, ALT_PEN20_TANKMON_FQID, ALT_PEN20_TANKMON_FQNAME, PEN20_TANKMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Tankmon
        { PEN20_TARGETMON_NAME, PEN20_TARGETMON_ID, ALT_PEN20_TARGETMON_FQID, ALT_PEN20_TARGETMON_FQNAME, PEN20_TARGETMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Targetmon
        { PEN20_TENTOMON_NAME, PEN20_TENTOMON_ID, ALT_PEN20_TENTOMON_FQID, ALT_PEN20_TENTOMON_FQNAME, PEN20_TENTOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Tentomon
        { PEN20_TERRIERMON_NAME, PEN20_TERRIERMON_ID, ALT_PEN20_TERRIERMON_FQID, ALT_PEN20_TERRIERMON_FQNAME, PEN20_TERRIERMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Terriermon
        { PEN20_THUNDERBALLMON_NAME, PEN20_THUNDERBALLMON_ID, ALT_PEN20_THUNDERBALLMON_FQID, ALT_PEN20_THUNDERBALLMON_FQNAME, PEN20_THUNDERBALLMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Thunderballmon
        { PEN20_TIA_LUDOMON_NAME, PEN20_TIA_LUDOMON_ID, ALT_PEN20_TIA_LUDOMON_FQID, ALT_PEN20_TIA_LUDOMON_FQNAME, PEN20_TIA_LUDOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Tia Ludomon
        { PEN20_TOGEMON_NAME, PEN20_TOGEMON_ID, ALT_PEN20_TOGEMON_FQID, ALT_PEN20_TOGEMON_FQNAME, PEN20_TOGEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Togemon
        { PEN20_TONOSAMA_GEKOMON_NAME, PEN20_TONOSAMA_GEKOMON_ID, ALT_PEN20_TONOSAMA_GEKOMON_FQID, ALT_PEN20_TONOSAMA_GEKOMON_FQNAME, PEN20_TONOSAMA_GEKOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Tonosama Gekomon
        { PEN20_TORTAMON_NAME, PEN20_TORTAMON_ID, ALT_PEN20_TORTAMON_FQID, ALT_PEN20_TORTAMON_FQNAME, PEN20_TORTAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Tortamon
        { PEN20_TOY_AGUMON_NAME, PEN20_TOY_AGUMON_ID, ALT_PEN20_TOY_AGUMON_FQID, ALT_PEN20_TOY_AGUMON_FQNAME, PEN20_TOY_AGUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Toy Agumon
        { PEN20_TRICERAMON_NAME, PEN20_TRICERAMON_ID, ALT_PEN20_TRICERAMON_FQID, ALT_PEN20_TRICERAMON_FQNAME, PEN20_TRICERAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Triceramon
        { PEN20_TROOPMON_NAME, PEN20_TROOPMON_ID, ALT_PEN20_TROOPMON_FQID, ALT_PEN20_TROOPMON_FQNAME, PEN20_TROOPMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Troopmon
        { PEN20_TURUIEMON_NAME, PEN20_TURUIEMON_ID, ALT_PEN20_TURUIEMON_FQID, ALT_PEN20_TURUIEMON_FQNAME, PEN20_TURUIEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Turuiemon
        { PEN20_VAMDEMON_NAME, PEN20_VAMDEMON_ID, ALT_PEN20_VAMDEMON_FQID, ALT_PEN20_VAMDEMON_FQNAME, PEN20_VAMDEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Vamdemon
        { PEN20_V_DRAMON_NAME, PEN20_V_DRAMON_ID, ALT_PEN20_V_DRAMON_FQID, ALT_PEN20_V_DRAMON_FQNAME, PEN20_V_DRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for V-dramon
        { PEN20_VEMDEMON_NAME, PEN20_VEMDEMON_ID, ALT_PEN20_VEMDEMON_FQID, ALT_PEN20_VEMDEMON_FQNAME, PEN20_VEMDEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Vemdemon
        { PEN20_VENOM_VAMDEMON_NAME, PEN20_VENOM_VAMDEMON_ID, ALT_PEN20_VENOM_VAMDEMON_FQID, ALT_PEN20_VENOM_VAMDEMON_FQNAME, PEN20_VENOM_VAMDEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Venom Vamdemon
        { PEN20_V_MON_NAME, PEN20_V_MON_ID, ALT_PEN20_V_MON_FQID, ALT_PEN20_V_MON_FQNAME, PEN20_V_MON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for V-mon
        { PEN20_VOLCANICDRAMON_NAME, PEN20_VOLCANICDRAMON_ID, ALT_PEN20_VOLCANICDRAMON_FQID, ALT_PEN20_VOLCANICDRAMON_FQNAME, PEN20_VOLCANICDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Volcanicdramon
        { PEN20_VOLTOBAUTAMON_NAME, PEN20_VOLTOBAUTAMON_ID, ALT_PEN20_VOLTOBAUTAMON_FQID, ALT_PEN20_VOLTOBAUTAMON_FQNAME, PEN20_VOLTOBAUTAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Voltobautamon
        { PEN20_VORVOMON_NAME, PEN20_VORVOMON_ID, ALT_PEN20_VORVOMON_FQID, ALT_PEN20_VORVOMON_FQNAME, PEN20_VORVOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Vorvomon
        { PEN20_WAR_GREYMON_NAME, PEN20_WAR_GREYMON_ID, ALT_PEN20_WAR_GREYMON_FQID, ALT_PEN20_WAR_GREYMON_FQNAME, PEN20_WAR_GREYMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for War Greymon
        { PEN20_WARU_MOZAEMON_NAME, PEN20_WARU_MOZAEMON_ID, ALT_PEN20_WARU_MOZAEMON_FQID, ALT_PEN20_WARU_MOZAEMON_FQNAME, PEN20_WARU_MOZAEMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Waru Mozaemon
        { PEN20_WERE_GARURUMON_NAME, PEN20_WERE_GARURUMON_ID, ALT_PEN20_WERE_GARURUMON_FQID, ALT_PEN20_WERE_GARURUMON_FQNAME, PEN20_WERE_GARURUMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Were Garurumon
        { PEN20_WHAMON_NAME, PEN20_WHAMON_ID, ALT_PEN20_WHAMON_FQID, ALT_PEN20_WHAMON_FQNAME, PEN20_WHAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Whamon
        { PEN20_WINGDRAMON_NAME, PEN20_WINGDRAMON_ID, ALT_PEN20_WINGDRAMON_FQID, ALT_PEN20_WINGDRAMON_FQNAME, PEN20_WINGDRAMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Wingdramon
        { PEN20_WIZARMON_NAME, PEN20_WIZARMON_ID, ALT_PEN20_WIZARMON_FQID, ALT_PEN20_WIZARMON_FQNAME, PEN20_WIZARMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Wizarmon
        { PEN20_WOODMON_NAME, PEN20_WOODMON_ID, ALT_PEN20_WOODMON_FQID, ALT_PEN20_WOODMON_FQNAME, PEN20_WOODMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Woodmon
        { PEN20_XV_MON_NAME, PEN20_XV_MON_ID, ALT_PEN20_XV_MON_FQID, ALT_PEN20_XV_MON_FQNAME, PEN20_XV_MON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for XV-mon
        { PEN20_ZERIMON_NAME, PEN20_ZERIMON_ID, ALT_PEN20_ZERIMON_FQID, ALT_PEN20_ZERIMON_FQNAME, PEN20_ZERIMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Zerimon
        { PEN20_ZUDOMON_NAME, PEN20_ZUDOMON_ID, ALT_PEN20_ZUDOMON_FQID, ALT_PEN20_ZUDOMON_FQNAME, PEN20_ZUDOMON_ANIM_INDEX, config::config_animation_dm_set_t::pen20, config::config_animation_sprite_sheet_layout_t::Dm },  // alt ids for Zudomon
        
    };
    static const size_t pen20_alt_animation_table_size = LEN_ARRAY(pen20_animation_table);
    static const config_animation_names_entry_t pen20_animation_names_table[] = {
        { PEN20_ZUDOMON_NAME, PEN20_ZUDOMON_NAME_LEN, PEN20_ZUDOMON_ID, PEN20_ZUDOMON_ID_LEN, PEN20_ZUDOMON_FQID, PEN20_ZUDOMON_FQID_LEN, PEN20_ZUDOMON_FQNAME, PEN20_ZUDOMON_FQNAME_LEN },
        
    };

    config_animation_entry_t get_config_animation_name_pen20(size_t index) {
        assert(LEN_ARRAY(pen20_animation_table) == PEN20_ANIM_COUNT);
        assert(index < PEN20_ANIM_COUNT);
        return pen20_animation_table[index];
    }

    static void unload_config_parse_animation_names_pen20() {
        for (const auto& entry : pen20_animation_names_table) {
            platform::details::asset_unload_cstr(entry.name,   entry.name_len);
            platform::details::asset_unload_cstr(entry.id,     entry.id_len);
            platform::details::asset_unload_cstr(entry.fqid,   entry.fqid_len);
            platform::details::asset_unload_cstr(entry.fqname, entry.fqname_len);
        }
    }
    int config_parse_animation_name_pen20(config::config_t& config, const char *value) {
        assert(LEN_ARRAY(pen20_animation_table) == PEN20_ANIM_COUNT);
        int ret = -1;
        for (size_t i = 0;ret < 0 && i < PEN20_ANIM_COUNT;++i) {
            const auto& entry = pen20_animation_table[i];
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
        for (size_t i = 0;ret < 0 && i < pen20_alt_animation_table_size;++i) {
            const auto& entry = pen20_alt_animation_table[i];
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
        unload_config_parse_animation_names_pen20();
        return ret;
    }
}

