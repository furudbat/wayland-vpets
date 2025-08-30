#ifndef BONGOCAT_EMBEDDED_ASSETS_IMAGE_H
#define BONGOCAT_EMBEDDED_ASSETS_IMAGE_H

#include "sprite_sheet.h"

namespace bongocat::assets {
    struct embedded_image_t {
        const unsigned char *data{nullptr};
        size_t size{0};
        const char *name{""};
    };


#ifdef FEATURE_MS_AGENT_EMBEDDED_ASSETS
    struct ms_agent_animation_indices_t {
        int32_t start_index_frame_idle{0};
        int32_t end_index_frame_idle{0};

        int32_t start_index_frame_boring{0};
        int32_t end_index_frame_boring{0};

        int32_t start_index_frame_start_writing{0};
        int32_t end_index_frame_start_writing{0};

        int32_t start_index_frame_writing{0};
        int32_t end_index_frame_writing{0};

        int32_t start_index_frame_end_writing{0};
        int32_t end_index_frame_end_writing{0};

        int32_t start_index_frame_sleep{0};
        int32_t end_index_frame_sleep{0};

        int32_t start_index_frame_wake_up{0};
        int32_t end_index_frame_wake_up{0};
    };
#endif
}

#endif // BONGOCAT_EMBEDDED_ASSETS_IMAGE_H
