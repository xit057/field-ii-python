#include "../func.hpp"
#include "../para.hpp"


void delay_and_sum(float* signals, float* image, const Para& para) {
    const int offset = (para.element_count - para.line_count) / 2;

    int image_idx = 0;
    ff (i, para.line_count) {
        execute(printf("# Current Emit: %d\n", i));
        execute(fflush(stdout));

        float *signal_line = signals + i * para.element_count * para.data_length;
        ff (j, para.row_count) {
            float vertical_distance = para.z_start + j * para.pixel_height;

            ff (k, para.element_count) {
                float horizontal_distance = (i + offset - k) * para.pixel_width;
                float total_distance = vertical_distance + sqrt(
                        vertical_distance * vertical_distance + horizontal_distance * horizontal_distance
                );

                int idx = int(total_distance * para.ratio);

                if (0 <= idx && idx < para.data_length) {
                    image[image_idx] += signal_line[k * para.data_length + idx];
                }
            }
            ++ image_idx;
        }
    }
}
