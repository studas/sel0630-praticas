idf_component_register(SRC_DIRS "src"
                       INCLUDE_DIRS "inc"
                       REQUIRES adc_task button_task
                       PRIV_REQUIRES driver)
