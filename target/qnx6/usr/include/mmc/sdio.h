/*
 * $QNXLicenseC$
 */




#ifndef _SDIO_INCLUDED
#define _SDIO_INCLUDED

#include <devctl.h>
#include <pthread.h>
#include <inttypes.h>
#include <semaphore.h>
#include <sys/cfg.h>

#define	SDIO_FIXED_ADDRESS		0x0
#define	SDIO_INCREMENT_ADDRESS	0x1
#define	SDIO_BLOCK_MODE			0x1

/* SDIO Command definitions */
#define	SD_IO_SEND_OP_COND			5
#define	SD_IO_RW_DIRECT				52
#define	SD_IO_RW_EXTENDED			53

#define	SDIO_RSP_R4		(MMC_RSP_PRESENT)
#define	SDIO_RSP_R5		(MMC_RSP_PRESENT | MMC_RSP_CRC | MMC_RSP_OPCODE)

/*
 * SDIO standard function interface code
 */
#define	SDIO_CLASS_NONE		0x00
#define	SDIO_CLASS_UART		0x01	/* SDIO Standard UART */
#define	SDIO_CLASS_BT_A		0x02	/* SDIO Type-A for Bluetooth standard interface */
#define	SDIO_CLASS_BT_B		0x03	/* SDIO Type-B for Bluetooth standard interface */
#define	SDIO_CLASS_GPS		0x04	/* SDIO GPS standard interface */
#define	SDIO_CLASS_CAMERA	0x05	/* SDIO Camera standard interface */
#define	SDIO_CLASS_PHS		0x06	/* SDIO PHS standard interface */
#define	SDIO_CLASS_WLAN		0x07	/* SDIO WLAN interface */
#define	SDIO_CLASS_ATA		0x08	/* SDIO-ATA standard interface */

/* SDIO Interface Registers */
#define	SDIO_CCCR_SDIO_REV_REG		0x00
#define	SDIO_SD_SPEC_REV_REG		0x01
#define	SDIO_IO_ENABLE_REG			0x02
#define	SDIO_IO_READY_REG			0x03
#define	SDIO_INT_ENABLE_REG			0x04
#define	SDIO_INT_PENDING_REG		0x05
#define	SDIO_IO_ABORT_REG			0x06
#define	SDIO_BUS_INTERFACE_CONTROL_REG	0x07
#define	SDIO_CARD_CAPABILITY_REG	0x08
#define	SDIO_COMMON_CIS_POINTER_0_REG	0x09
#define	SDIO_COMMON_CIS_POINTER_1_REG	0x0A
#define	SDIO_COMMON_CIS_POINTER_2_REG	0x0B
#define	SDIO_BUS_SUSPEND_REG		0x0C
#define	SDIO_FUNCTION_SELECT_REG	0x0D
#define	SDIO_EXEC_FLAGS_REG			0x0E
#define	SDIO_READY_FLAGS_REG		0x0F
#define	SDIO_POWER_CONTROL_REG		0x12
#define	SDIO_HIGH_SPEED_REG			0x13

#define	SDIO_FN_CSA_REG(x)				(0x100 * (x) + 0x00)
#define SDIO_FN_CIS_POINTER_0_REG(x)	(0x100 * (x) + 0x09)
#define SDIO_FN_CIS_POINTER_1_REG(x)	(0x100 * (x) + 0x0A)
#define SDIO_FN_CIS_POINTER_2_REG(x)	(0x100 * (x) + 0x0B)
#define	SDIO_FN_BLOCK_SIZE_0_REG(x)		(0x100 * (x) + 0x10)
#define	SDIO_FN_BLOCK_SIZE_1_REG(x)		(0x100 * (x) + 0x11)

/* SDIO CIS format */
#define	SDIO_CISTPL_NULL			0x00	/* NULL tuple */
#define	SDIO_CISTPL_CHECKSUM		0x10	/* Checksum control */
#define	SDIO_CISTPL_VERS_1			0x15	/* Level 1 version/product-information */
#define	SDIO_CISTPL_ALTSTR			0x16	/* The Alternate Language String Tuple */
#define	SDIO_CISTPL_MANFID			0x20	/* Manufacture Identification String Tuple */
#define	SDIO_CISTPL_FUNCID			0x21	/* Function Identification Tuple */
#define	SDIO_CISTPL_FUNCE			0x22	/* Function Extensions */
#define	SDIO_CISTPL_SDIO_STD		0x91	/* Additional information */
#define	SDIO_CISTPL_SDIO_EXT		0x92	/* Reserved for future use */
#define	SDIO_CISTPL_END				0xFF	/* The End-of-chain Tuple */

#define	MAX_SDIO_FUNCTIONS	8
#define	SDIO_VID_ANY		0xFFFF
#define	SDIO_DID_ANY		0xFFFF
#define	SDIO_CLASS_ANY		0xFFFF
#define	SDIO_FUNC_ANY		-1


typedef struct _sdio_dev_t {
	uint16_t	vid;	/* Vendor ID */
	uint16_t	did;	/* Device ID */
	uint16_t	ccd;	/* Class code */
	int16_t		fun;	/* Function number */
} sdio_dev_t;

/* SDIO buffer descriptor header */
typedef struct _sdio_bdhdr_t {
	int32_t		nbd;	/* descriptor number */
	int32_t		pidx;	/* producer index */
	int32_t		cidx;	/* consumer index */
	uint32_t	count;	/* valid descriptor count */
	uint32_t	flag;
#define	SDIO_BDHDR_MUTEX		(1 << 0)
#define	SDIO_BDHDR_SEMAPHORE	(1 << 1)

	/* for IPC */
	/* mutex */
	pthread_mutex_t	mutex;
	/* semaphore */
	sem_t		sem;

	/* function specific event flag */
	int			func_event;
#define	SDIO_FUNC_INTR		(1 << 0)	/* SDIO interrupt */
#define	SDIO_FUNC_TXDONE	(1 << 16)	/* Tx done */
#define	SDIO_FUNC_RXDONE	(1 << 17)	/* Rx done */
} sdio_bdhdr_r;

/* SDIO buffer descriptor */
typedef struct _sdio_bd_t {
	paddr_t		paddr;		/* physical address of the buffer for this descriptor */
	int32_t		nbytes;		/* byte count in this descriptor */
	int32_t		pktlen;		/* byte count for the entire packet */
	int32_t		nidx;		/* index to the next descriptor */
	uint32_t	flags;
#define	SDIO_BD_NUMSG(x)	((x) & 0xFFFF)	/* total descriptor number */
#define	SDIO_BD_VALID		(1 << 31)
#define	SDIO_BD_COMP		(1 << 30)		/* buffer complete */
#define	SDIO_BD_ERR			(1 << 29)		/* error */
#define	SDIO_BD_FIRST		(1 << 28)		/* First descriptor */
#define	SDIO_BD_LAST		(1 << 27)		/* Last descriptor */
#define	SDIO_BD_WRAP		(1 << 26)		/* Wrap up */
#define	SDIO_BD_DIRIN		(1 << 25)		/* DMA read */

#define	SDIO_ERR_SIZE		(1 << 18)		/* invalid length */
#define	SDIO_ERR_EIO		(1 << 17)		/* hardware error */
#define	SDIO_ERR_INVALID	(1 << 16)		/* invalid descriptor */
	void		*privptr;					/* private pointer for client */
} sdio_bd_t;

typedef struct _sdio_shmcfg_t {
	int32_t		nsize;		/* total size in bytes */
	int32_t		extra;		/* given by caller: extra size in bytes for private usage */
	int32_t		ntbd;		/* given by caller: Tx descriptor number */
	int32_t		nrbd;		/* given by caller: Rx descriptor number */
	uint32_t	flag;		/* given by caller: flags */
#define	SDIO_SHMEM_TX_MUTEX		(1 << 0)
#define	SDIO_SHMEM_TX_SEMAPHORE	(1 << 1)
#define	SDIO_SHMEM_RX_MUTEX		(1 << 2)
#define	SDIO_SHMEM_RX_SEMAPHORE	(1 << 3)
	char		sname[16];	/* given by caller: shared memory name */

	int32_t		off_tbd;	/* Tx descriptor offset */
	int32_t		off_rbd;	/* Rx descriptor offset */

	/* private to process */
	int			shmfd;
	void		*shmvptr;
} sdio_shmcfg_t;

typedef struct _sdio_ioreg_t {
	uint8_t		func;
	uint8_t		val;
	uint8_t		rsvd[2];
	uint32_t	reg;
} sdio_ioreg_t;

typedef struct _sdio_iomem_t {
	uint8_t		func;
	uint8_t		blkmode;
	uint8_t		opcode;
	uint8_t		rsvd;
	uint32_t	address;
	uint32_t	blksz;
} sdio_iomem_t;


#define	DCMD_SDIO_READ_IOREG	__DIOTF(_DCMD_MISC, 0x01, sdio_ioreg_t)
#define	DCMD_SDIO_WRITE_IOREG	__DIOT (_DCMD_MISC, 0x02, sdio_ioreg_t)
#define	DCMD_SDIO_SET_IOREG		__DIOT (_DCMD_MISC, 0x03, sdio_ioreg_t)
#define	DCMD_SDIO_CLR_IOREG		__DIOT (_DCMD_MISC, 0x04, sdio_ioreg_t)
#define	DCMD_SDIO_CFG_IOMEM		__DIOT (_DCMD_MISC, 0x05, sdio_iomem_t)
#define	DCMD_SDIO_GET_HCCAP		__DIOF (_DCMD_MISC, 0x06, uint32_t)

#define	DCMD_SDIO_SHMEM_INIT	__DIOT (_DCMD_MISC, 0x10, sdio_shmcfg_t)
#define	DCMD_SDIO_SHMEM_FINI	__DIOT (_DCMD_MISC, 0x11, int)
#define	DCMD_SDIO_ATTACH_DEVICE	__DIOTF(_DCMD_MISC, 0x12, sdio_dev_t)
#define	DCMD_SDIO_DETACH_DEVICE	__DIOT (_DCMD_MISC, 0x13, int)
#define	DCMD_SDIO_INTR_ENABLE	__DIOT (_DCMD_MISC, 0x14, int)	/* enable function interrupt */
#define	DCMD_SDIO_INTR_DISABLE	__DIOT (_DCMD_MISC, 0x15, int)	/* disable function interrupt */
#define	DCMD_SDIO_DEV_START		__DIOT (_DCMD_MISC, 0x16, int)	/* start device handler */
#define	DCMD_SDIO_DEV_STOP		__DIOT (_DCMD_MISC, 0x17, int)	/* stop device handler */

#define	DCMD_SDIO_VENDOR		__DIOTF(_DCMD_MISC, 0x80, int)	/* vendor specific */


/*
 * Host capability
 */
#define	SDIO_HCAP_DMA			(1 << 0)	/* controller support DMA */
#define	SDIO_HCAP_SG			(1 << 1)	/* DMA supports scatter/gather  */
#define	SDIO_HCAP_PIO			(1 << 2)	/* controller support PIO */

#define	SDIO_HCAP_18V			(1 << 3)	/* 1.8v is supported */
#define	SDIO_HCAP_30V			(1 << 4)	/* 3.0v is supported */
#define	SDIO_HCAP_33V			(1 << 5)	/* 3.3v is supported */

#define	SDIO_HCAP_BW1			(1 << 6)	/* 1 bit bus supported */
#define	SDIO_HCAP_BW4			(1 << 7)	/* 4 bit bus supported */
#define	SDIO_HCAP_BW8			(1 << 8)	/* 8 bit bus supported */

#define	SDIO_HCAP_CD_INTR		(1 << 9)	/* Host support card detect interrupt */

#define	SDIO_HCAP_ACMD12		(1 << 10)	/* auto stop command(ACMD12) supported */
#define	SDIO_HCAP_HS			(1 << 11)	/* High speed device supported */

#define	SDIO_HCAP_MAXSG_SHIFT	16
#define	SDIO_HCAP_MAXSG_MASK	0x0F
#define	SDIO_HCAP_ALIGN_SHIFT	20
#define	SDIO_HCAP_ALIGN_MASK	0x0F

#define	SDIO_HCAP_MAXSG(x)		(1 << (((x) >> SDIO_HCAP_MAXSG_SHIFT) & SDIO_HCAP_MAXSG_MASK))
#define	SDIO_HCAP_ALIGN(x)		(1 << (((x) >> SDIO_HCAP_ALIGN_SHIFT) & SDIO_HCAP_ALIGN_MASK))

extern int	sdio_read_ioreg(int fd, uint8_t fn, int reg, uint8_t *data);
extern int	sdio_write_ioreg(int fd, uint8_t fn, int reg, uint8_t data);
extern int	sdio_set_ioreg(int fd, uint8_t fn, int reg, uint8_t bits);
extern int	sdio_clr_ioreg(int fd, uint8_t fn, int reg, uint8_t bits);
extern int	sdio_cfg_iomem(int fd, uint8_t fn, uint32_t address,
				uint8_t blkmode, uint8_t opcode, uint32_t blksz);
extern int	sdio_get_hccap(int fd, uint32_t *hccap);
extern int	sdio_shmem_init(int fd, sdio_shmcfg_t *shmcfg);
extern int	sdio_shmem_fini(int fd, sdio_shmcfg_t *shmcfg);
extern int	sdio_attach_device(int fd, sdio_dev_t *dev);
extern int	sdio_detach_device(int fd, int fn);
extern int	sdio_intr_enable(int fd, int fn);
extern int	sdio_intr_disable(int fd, int fn);
extern int	sdio_device_start(int fd, int arg);
extern int	sdio_device_stop(int fd, int arg);
extern int	sdio_devctl_vendor(int fd, int subcmd, void *sbuf, void *rbuf);


#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn/product/branches/6.6.0/trunk/lib/sdio/public/mmc/sdio.h $ $Rev: 732568 $")
#endif
