#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_lcd_panel_ops.h"

void app_main(void) {
    printf("NEUER CODE GESTARTET! Hardware-Test aktiv.\n");

    esp_lcd_i80_bus_handle_t i80_bus = NULL;
    esp_lcd_i80_bus_config_t bus_config = {
        .clk_src = LCD_CLK_SRC_DEFAULT,
        .dc_gpio_num = 27,
        .wr_gpio_num = 26,
        .data_gpio_nums = {1, 2, 3, 4, 5, 6, 7, 8},
        .bus_width = 8,
        .max_transfer_bytes = 4000,
    };
    esp_lcd_new_i80_bus(&bus_config, &i80_bus);

    esp_lcd_panel_io_handle_t io_handle = NULL;
    esp_lcd_panel_io_i80_config_t io_config = {
        .cs_gpio_num = 33,
        .pclk_hz = 2 * 1000 * 1000, // 2MHz extrem langsam/sicher
        .trans_queue_depth = 10,
        .lcd_cmd_bits = 8,
        .lcd_param_bits = 8,
        .dc_levels = {.dc_idle_level = 0, .dc_cmd_level = 0, .dc_data_level = 1},
    };
    esp_lcd_new_panel_io_i80(i80_bus, &io_config, &io_handle);

    esp_lcd_panel_handle_t panel = NULL;
    esp_lcd_panel_dev_config_t panel_cfg = {.reset_gpio_num = -1, .color_space = ESP_LCD_COLOR_SPACE_RGB, .bits_per_pixel = 16};
    esp_lcd_new_panel_st7789(io_handle, &panel_cfg, &panel);
    
    esp_lcd_panel_reset(panel);
    esp_lcd_panel_init(panel);
    esp_lcd_panel_disp_on_off(panel, true);

    uint16_t blue = 0x001F; // Blau
    printf("Display sollte jetzt Blau werden...\n");
    while(1) {
        for(int y=0; y<320; y++) {
            esp_lcd_panel_draw_bitmap(panel, 0, y, 480, y+1, &blue);
        }
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}