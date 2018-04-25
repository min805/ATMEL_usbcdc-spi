/*
 * m_spi.c
 *
 * Created: 4/25/2018 11:00:45 AM
 *  Author: Romero
 */ 

#include <asf.h>
#include "m_spi.h"
#include <conf_board.h>
#include <compiler.h>




struct spi_master_vec_module spi_master;
struct spi_master_vec_config spi_config;

void spi_init(void)
{
	
	
	//EXT1_SPI_MODULE	SERCOM0
	spi_master_vec_get_config_defaults(&spi_config);
		spi_config.baudrate = 100000;
		spi_config.gclk_generator = GCLK_GENERATOR_0;
		spi_config.run_in_standby = false;
		spi_config.mux_setting = SPI_SIGNAL_MUX_SETTING_E; //!> EXT1_SPI_SERCOM_MUX_SETTING
		spi_config.transfer_mode = SPI_TRANSFER_MODE_3;//!> Leading edge:falling,setup. Trailing edge: rising, sample
		spi_config.data_order = SPI_DATA_ORDER_MSB;
		spi_config.pinmux_pad0 = PINMUX_PA04D_SERCOM0_PAD0;//!> EXT1_SPI_SERCOM_PINMUX_PAD0
		spi_config.pinmux_pad1 = PINMUX_PA05D_SERCOM0_PAD1;//!> EXT1_SPI_SERCOM_PINMUX_PAD1
		spi_config.pinmux_pad2 = PINMUX_PA06D_SERCOM0_PAD2;//!> EXT1_SPI_SERCOM_PINMUX_PAD2
		spi_config.pinmux_pad3 = PINMUX_PA07D_SERCOM0_PAD3;//!> EXT1_SPI_SERCOM_PINMUX_PAD3

	spi_master_vec_init(&spi_master,SERCOM0, &spi_config);
	spi_master_vec_enable(&spi_master);
	
	
//! [start_reception_wait]
spi_master_vec_transceive_buffer_wait(&spi_master, NULL, rx_buffers);
//! [start_reception_wait]

//! [start_transmission]
spi_master_vec_transceive_buffer_job(&spi_master, tx_buffers, NULL);
//! [start_transmission]

//! [start_transception]
while (spi_master_vec_transceive_buffer_job(&spi_master, tx_buffers, rx_buffers) == STATUS_BUSY) {
	/* Try to start transfer until it succeeds. */
}
//! [start_transception]

//! [wait_transception]
spi_master_vec_get_job_status_wait(&spi_master);
//! [wait_transception]
	
	
}
