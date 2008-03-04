/*
* This software was developed at the National Institute of Standards and
* Technology (NIST) by employees of the Federal Government in the course
* of their official duties. Pursuant to title 17 Section 105 of the
* United States Code, this software is not subject to copyright protection
* and is in the public domain. NIST assumes no responsibility whatsoever for
* its use by other parties, and makes no guarantees, expressed or implied,
* about its quality, reliability, or any other characteristic.
*/
/******************************************************************************/
/* Header file for the Iris Image Data Record format, as specified in         */
/* ISO/IEC 19794-6:2005.                                                      */
/*                                                                            */
/* Layout of the entire iris image biometric data block in memory:            */
/*                                                                            */
/*       Iris Image Biometric Data Block                                      */
/*   +-------------------------------------+                                  */
/*   |  iris record header (45 bytes)      |                                  */
/*   +-------------------------------------+                                  */
/*   Array[2] {                                                               */
/*       +--------------------------------------------+                       */
/*       |  iris biometric subtype header (3 bytes)   |                       */
/*       +--------------------------------------------+                       */
/*       List {                                                               */
/*           +--------------------------------|     +--------+---+            */
/*           |  iris image header (11 bytes)  |-->  | image data |            */
/*           +--------------------------------|     +--------+---+            */
/*                                               :                            */
/*                                               :                            */
/*           +--------------------------------|     +--------+---+            */
/*           |  iris image header (11 bytes)  |-->  | image data |            */
/*           +--------------------------------|     +--------+---+            */
/*       }                                                                    */
/*       +--------------------------------------------+                       */
/*       |  iris biometric subtype header (3 bytes)   |                       */
/*       +--------------------------------------------+                       */
/*       List {                                                               */
/*           +--------------------------------|     +--------+---+            */
/*           |  iris image header (11 bytes)  |-->  | image data |            */
/*           +--------------------------------|     +--------+---+            */
/*                                               :                            */
/*                                               :                            */
/*           +--------------------------------|     +--------+---+            */
/*           |  iris image header (11 bytes)  |-->  | image data |            */
/*           +--------------------------------|     +--------+---+            */
/*       }                                                                    */
/*   }                                                                        */
/*                                                                            */
/******************************************************************************/
#ifndef _IID_H
#define _IID_H

#define IID_FORMAT_ID				"IIR"
#define IID_FORMAT_ID_LEN			4

#define IID_FORMAT_VERSION_LEN			4

#define IID_DEVICE_UNIQUE_ID_LEN		16
#define IID_CAPTURE_DEVICE_UNDEF		0

#define IID_MIN_BIOMETRIC_SUBTYPES		1
#define IID_MAX_BIOMETRIC_SUBTYPES		2

#define IID_RECORD_HEADER_LENGTH		45

/* Bit definitions for the Iris Record Header image properties field. */
#define IID_HORIZONTAL_ORIENTATION_MASK		0x0003
#define IID_HORIZONTAL_ORIENTATION_SHIFT	0
#define IID_VERTICAL_ORIENTATION_MASK		0x000C
#define IID_VERTICAL_ORIENTATION_SHIFT		2
#define IID_SCAN_TYPE_MASK			0x0030
#define IID_SCAN_TYPE_SHIFT			4
#define IID_IRIS_OCCLUSIONS_MASK		0x0040
#define IID_IRIS_OCCLUSIONS_SHIFT		6
#define IID_OCCLUSION_FILLING_MASK		0x0080
#define IID_OCCLUSION_FILLING_SHIFT		7
#define IID_BOUNDARY_EXTRACTION_MASK		0x0100
#define IID_BOUNDARY_EXTRACTION_SHIFT		8

#define IID_ORIENTATION_UNDEF			0
#define IID_ORIENTATION_BASE			1
#define IID_ORIENTATION_FLIPPED			2
#define IID_SCAN_TYPE_CORRECTED			0
#define IID_SCAN_TYPE_PROGRESSIVE		1
#define IID_SCAN_TYPE_INTERLACE_FRAME		2
#define IID_SCAN_TYPE_INTERLACE_FIELD		3
#define IID_IROCC_UNDEF				0
#define IID_IROCC_PROCESSED			1
#define IID_IROCC_ZEROFILL			0
#define IID_IROCC_UNITFILL			1
#define IID_IRBNDY_UNDEF			0
#define IID_IRBNDY_PROCESSED			1

#define IID_IMAGEFORMAT_MONO_RAW		0x0002
#define IID_IMAGEFORMAT_RGB_RAW			0x0004
#define IID_IMAGEFORMAT_MONO_JPEG		0x0006
#define IID_IMAGEFORMAT_RGB_JPEG		0x0008
#define IID_IMAGEFORMAT_MONO_JPEG_LS		0x000A
#define IID_IMAGEFORMAT_RGB_JPEG_LS		0x000C
#define IID_IMAGEFORMAT_MONO_JPEG2000		0x000E
#define IID_IMAGEFORMAT_RGB_JPEG2000		0x0010
#define IID_WIDTH_UNDEF				0
#define IID_HIEGHT_UNDEF			0
#define IID_INTENSITY_DEPTH_UNDEF		0
#define IID_TRANS_UNDEF				0
#define IID_TRANS_STD				1
#define IID_DEVICE_UNIQUE_ID_SERIAL_NUMBER	'D'
#define IID_DEVICE_UNIQUE_ID_MAC_ADDRESS	'M'
#define IID_DEVICE_UNIQUE_ID_PROCESSOR_ID	'P'
#define IID_DEVICE_UNIQUE_ID_NONE		"0000000000000000"

/*
 * Class codes for converting codes to strings. See the iid_code_str()
 * function defined below.
 */
#define IID_CODE_CLASS_ORIENTATION		0
#define IID_CODE_CLASS_SCAN_TYPE		1
#define IID_CODE_CLASS_OCCLUSION		2
#define IID_CODE_CLASS_OCCLUSION_FILLING	3
#define IID_CODE_CLASS_BOUNDARY_EXTRACTION	4
#define IID_CODE_CLASS_IMAGE_FORMAT		5
#define IID_CODE_CLASS_IMAGE_TRANSFORMATION	6
#define IID_CODE_CLASS_BIOMETRIC_SUBTYPE	7

struct iris_record_header {
	char			format_id[IID_FORMAT_ID_LEN];
	char			format_version[IID_FORMAT_VERSION_LEN];
	uint32_t		record_length;
	uint16_t		capture_device_id;
	uint8_t			biometric_subtype_count;
	uint16_t		record_header_length;
	uint8_t			horizontal_orientation;
	uint8_t			vertical_orientation;
	uint8_t			scan_type;
	uint8_t			iris_occlusions;
	uint8_t			occlusion_filling;
	uint8_t			boundary_extraction;
	uint16_t		diameter;
	uint16_t		image_format;
	uint16_t		image_width;
	uint16_t		image_height;
	uint8_t			intesity_depth;
	uint8_t			image_transformation;
	uint8_t			device_unique_id[IID_DEVICE_UNIQUE_ID_LEN];
};
typedef struct iris_record_header IRH;

#define IID_ROT_ANGLE_UNDEF			0xFFFF
#define IID_ROT_UNCERTAIN_MIN			0
#define IID_ROT_UNCERTAIN_MAX			179
#define IID_ROT_UNCERTAIN_UNDEF			0xFFFF

struct iris_image_header {
	uint16_t				image_number;
	uint8_t					image_quality;
	uint16_t				rotation_angle;
	uint16_t				rotation_uncertainty;
	uint32_t				image_length;
	uint8_t					*image_data;
	TAILQ_ENTRY(iris_image_header)		list;
	struct iris_biometric_subtype_header	*ibsh; /* ptr to parent rec */
};
typedef struct iris_image_header IIH;

#define IID_EYE_UNDEF				0x00
#define IID_EYE_RIGHT				0x01
#define IID_EYE_LEFT				0x02

struct iris_biometric_subtype_header {
	uint8_t			biometric_subtype;
	uint16_t		num_images;
	TAILQ_HEAD(, iris_image_header)	image_headers;
};
typedef struct iris_biometric_subtype_header IBSH;

struct iris_image_biometric_data_block {
	IRH				record_header;
	IBSH				*biometric_subtype_headers[2];
};
typedef struct iris_image_biometric_data_block IIBDB;

/******************************************************************************/
/* Define the interface for allocating and freeing iris image data blocks.    */
/******************************************************************************/
int new_iih(IIH **iih);
void free_iih(IIH *iih);

int new_ibsh(IBSH **ibsh);
void free_ibsh(IBSH *ibsh);

int new_iibdb(IIBDB **iibdb);
void free_iibdb(IIBDB *iibdb);

/******************************************************************************/
/* Define the interface for reading/writing/verifying iris image data blocks. */
/******************************************************************************/
int read_iih(FILE *fp, IIH *iih);
int write_iih(FILE *fp, IIH *iih);
int print_iih(FILE *fp, IIH *iih);
int validate_iih(IIH *iih);

int read_ibsh(FILE *fp, IBSH *ibsh);
int write_ibsh(FILE *fp, IBSH *ibsh);
int print_ibsh(FILE *fp, IBSH *ibsh);
int validate_ibsh(IBSH *ibsh);

int read_iibdb(FILE *fp, IIBDB *iibdb);
int write_iibdb(FILE *fp, IIBDB *iibdb);
int print_iibdb(FILE *fp, IIBDB *iibdb);
int validate_iibdb(IIBDB *fir);

void add_iih_to_ibsh(IIH *iih, IBSH *ibsh);

/******************************************************************************/
/* Defintion of the higher level access routines.                             */
/******************************************************************************/
int get_ibsh_count(IIBDB *iibdb);
int get_ibshs(IIBDB *iibdb, IBSH *ibshs[]);
int get_iih_count(IBSH *ibsh);
int get_iihs(IBSH *ibsh, IIH *iihs[]);

/* Convert a code (image orientation, scan type, etc. to a string. The
 * 'class' argument must be on of those defined above. This function will
 * either return a string matching the code within the class, or 'INVALID'
 * for an invalid code for the class.
 */
char * iid_code_to_str(int class, int code);
#endif 	/* _IID_H */