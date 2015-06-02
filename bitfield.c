#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define MAJOR_SERVICE_NUM	11
#define MINOR_CLASS_NUM		15

typedef struct _value_string {
	uint32_t      value;
	const char *strptr;
} value_string;

struct dev_class_field {
	const char	*name;
	const void	*strings;
	uint32_t	bitmask;
	const int	width;
};

static const value_string cod_major_device_class_vals[] = {
	{0x00, "Miscellaneous"},
	{0x01, "Computer"},
	{0x02, "Phone"},
	{0x03, "LAN/Network Access Point"},
	{0x04, "Audio/Video"},
	{0x05, "Peripheral (HID)"},
	{0x06, "Imaging"},
	{0x07, "Wearable"},
	{0x08, "Toy"},
	{0x09, "Health"},
	{0x1F, "Uncategorized: device code not specified"},
	{0, NULL }
};

static const value_string cod_minor_device_class_computer_vals[] = {
	{ 0x00,  "Uncategorized, code for device not assigned" },
	{ 0x01,  "Desktop workstation" },
	{ 0x02,  "Server-class computer" },
	{ 0x03,  "Laptop" },
	{ 0x04,  "Handheld PC/PDA (clamshell)" },
	{ 0x05,  "Palm-size PC/PDA" },
	{ 0x06,  "Wearable computer (watch size)" },
	{ 0x07,  "Tablet" },
	{ 0, NULL }
};

static const value_string cod_minor_device_class_phone_vals[] = {
	{ 0x00,  "Uncategorized, code for device not assigned" },
	{ 0x01,  "Cellular" },
	{ 0x02,  "Cordless" },
	{ 0x03,  "Smartphone" },
	{ 0x04,  "Wired modem or voice gateway" },
	{ 0x05,  "Common ISDN access" },
	{ 0, NULL }
};

static const value_string cod_minor_device_class_lan_net_load_factor_vals[] = {
	{ 0x00,  "Fully available" },
	{ 0x01,  "1% to 17% utilized" },
	{ 0x02,  "17% to 33% utilized" },
	{ 0x03,  "33% to 50% utilized" },
	{ 0x04,  "50% to 67% utilized" },
	{ 0x05,  "67% to 83% utilized" },
	{ 0x06,  "83% to 99% utilized" },
	{ 0x07,  "No service available" },
	{ 0, NULL }
};

static const value_string cod_minor_device_class_lan_net_type_vals[] = {
	{ 0x00,  "Uncategorized (used if no others apply)" },
	{ 0, NULL }
};

static const value_string cod_minor_device_class_audio_video_vals[] = {
	{ 0x00,  "Uncategorized, code not assigned" },
	{ 0x01,  "Wearable Headset Device" },
	{ 0x02,  "Hands-free Device" },
	{ 0x04,  "Microphone" },
	{ 0x05,  "Loudspeaker" },
	{ 0x06,  "Headphones" },
	{ 0x07,  "Portable Audio" },
	{ 0x08,  "Car audio" },
	{ 0x09,  "Set-top box" },
	{ 0x0A,  "HiFi Audio Device" },
	{ 0x0B,  "VCR" },
	{ 0x0C,  "Video Camera" },
	{ 0x0D,  "Camcorder" },
	{ 0x0E,  "Video Monitor" },
	{ 0x0F,  "Video Display and Loudspeaker" },
	{ 0x10,  "Video Conferencing" },
	{ 0x12,  "Gaming/Toy" },
	{ 0, NULL }
};

static const value_string cod_minor_device_class_peripheral_class_vals[] = {
	{ 0x00,  "Not Keyboard / Not Pointing Device" },
	{ 0x01,  "Keyboard" },
	{ 0x02,  "Pointing device" },
	{ 0x03,  "Combo keyboard/pointing device" },
	{ 0, NULL }
};

static const value_string cod_minor_device_class_peripheral_type_vals[] = {
	{ 0x00,  "Uncategorized device" },
	{ 0x01,  "Joystick" },
	{ 0x02,  "Gamepad" },
	{ 0x03,  "Remote control" },
	{ 0x04,  "Sensing device" },
	{ 0x05,  "Digitizer tablet" },
	{ 0x06,  "Card Reader" },
	{ 0x07,  "Digital Pen" },
	{ 0x08,  "Handheld scanner for bar-codes" },
	{ 0x09,  "Handheld gestural input device" },
	{ 0, NULL }
};

static const value_string cod_minor_device_class_imaging_type_vals[] = {
	{ 0x00,  "Uncategorized, default" },
	{ 0, NULL }
};

static const value_string cod_minor_device_class_wearable_vals[] = {
	{ 0x01,  "Wristwatch" },
	{ 0x02,  "Pager" },
	{ 0x03,  "Jacket" },
	{ 0x04,  "Helmet" },
	{ 0x05,  "Glasses" },
	{ 0, NULL }
};

static const value_string cod_minor_device_class_toy_vals[] = {
	{ 0x01,  "Robot" },
	{ 0x02,  "Vehicle" },
	{ 0x03,  "Doll / Action figure" },
	{ 0x04,  "Controller" },
	{ 0x05,  "Game" },
	{ 0, NULL }
};

static const value_string cod_minor_device_class_health_vals[] = {
	{ 0x00,  "Undefined" },
	{ 0x01,  "Blood Pressure Monitor" },
	{ 0x02,  "Thermometer" },
	{ 0x03,  "Weighing Scale" },
	{ 0x04,  "Glucose Meter" },
	{ 0x05,  "Pulse Oximeter" },
	{ 0x06,  "Heart/Pulse Rate Monitor" },
	{ 0x07,  "Health Data Display" },
	{ 0x08,  "Step Counter" },
	{ 0x09,  "Body Composition Analyzer" },
	{ 0x0A,  "Peak Flow Monitor" },
	{ 0x0B,  "Medication Monitor" },
	{ 0x0C,  "Knee Prosthesis" },
	{ 0x0D,  "Ankle Prosthesis" },
	{ 0x0E,  "Generic Health Manager" },
	{ 0x0F,  "Personal Mobility Device" },
	{ 0, NULL }
};

struct dev_class_field service_class_vals[] = {
	{ "Major Service Classes: Information", NULL, 0x8000, 16 },
	{ "Major Service Classes: Telephony", NULL, 0x4000, 16 },
	{ "Major Service Classes: Audio", NULL, 0x2000, 16 },
	{ "Major Service Classes: Object Transfer", NULL, 0x1000, 16 },
	{ "Major Service Classes: Capturing", NULL, 0x0800, 16 },
	{ "Major Service Classes: Rendering", NULL, 0x0400, 16 },
	{ "Major Service Classes: Networking", NULL, 0x0200, 16 },
	{ "Major Service Classes: Positioning", NULL, 0x0100, 16 },
	{ "Major Service Classes: Reserved", NULL, 0x00C0, 16 },
	{ "Major Service Classes: Limited Discoverable Mode", NULL, 0x0020, 16 },
	{ "Major Device Class", &cod_major_device_class_vals, 0x1F, 16 },
};


struct dev_class_field minor_class_vals[] = {
	{ "Minor Device Class", &cod_minor_device_class_computer_vals, 0xFC, 8 },
	{ "Minor Device Class", &cod_minor_device_class_phone_vals, 0xFC, 8 },
	{ "Minor Device Class: Load Factor", &cod_minor_device_class_lan_net_load_factor_vals, 0xE0, 8 },
	{ "Minor Device Class: Type", &cod_minor_device_class_lan_net_type_vals, 0x1C, 8 },
	{ "Minor Device Class", &cod_minor_device_class_audio_video_vals, 0xFC, 8 },
	{ "Minor Device Class", &cod_minor_device_class_peripheral_class_vals, 0xC0, 8 },
	{ "Minor Device Class", &cod_minor_device_class_peripheral_type_vals, 0x3C, 8 },
	{ "Minor Device Class: Class: Printer", &cod_minor_device_class_imaging_type_vals, 0x80, 8 },
	{ "Minor Device Class: Class: Scanner", &cod_minor_device_class_imaging_type_vals, 0x40, 8 },
	{ "Minor Device Class: Class: Camera", &cod_minor_device_class_imaging_type_vals, 0x20, 8 },
	{ "Minor Device Class: Class: Display", &cod_minor_device_class_imaging_type_vals, 0x10, 8 },
	{ "Minor Device Class: Type", &cod_minor_device_class_imaging_type_vals, 0x0C, 8 },
	{ "Minor Device Class", &cod_minor_device_class_wearable_vals, 0xFC, 8 },
	{ "Minor Device Class", &cod_minor_device_class_toy_vals, 0xFC, 8 },
	{ "Minor Device Class", &cod_minor_device_class_health_vals, 0xFC, 8 },
	{ "Minor Device Class", NULL, 0xFC, 8 },
	{ "Format Type", NULL, 0x03, 8 },
};

const char *val_to_str(const uint32_t val, const value_string *vs)
{
	int i = 0;

	if (vs) {
		while (vs[i].strptr) {
			if (vs[i].value == val) {
				return(vs[i].strptr);
			}
			i++;
		}
	}

	return NULL;
}

/* Generate, into "buf", a string showing the bits of a bitfield.
   Return a pointer to the character after that string. */
/*XXX this needs a buf_len check */
char *
other_decode_bitfield_value(char *buf, const uint64_t val, const uint64_t mask, const int width)
{
	int i;
	uint64_t bit;
	char *p;

	i = 0;
	p = buf;
	bit = 1 << (width - 1);
	for (;;) {
		if (mask & bit) {
			/* This bit is part of the field.  Show its value. */
			if (val & bit)
				*p++ = '1';
			else
				*p++ = '0';
		} else {
			/* This bit is not part of the field. */
			*p++ = '.';
		}
		bit >>= 1;
		i++;
		if (i >= width)
			break;
		if (i % 4 == 0)
			*p++ = ' ';
	}
	*p = '\0';
	return p;
}

static char *
decode_bitfield_value(char *buf, const uint64_t val, const uint64_t mask, const int width)
{
	char *p;

	p = other_decode_bitfield_value(buf, val, mask, width);
	p = stpcpy(p, " = ");

	return p;
}

static char *
decode_bitfield_minor_class(const uint32_t val, int shift,
		const struct dev_class_field *field)
{
	char *p;
	char buf[64];
	uint8_t minor_class;	/* minor class */
	const char *minor_class_name;

	p = decode_bitfield_value(buf, val, field->bitmask, field->width);
	printf("\t%s%s", buf, field->name);

	minor_class = (val & field->bitmask) >> shift;
	minor_class_name = val_to_str(minor_class, field->strings);
	if (minor_class_name)
		printf(": %s\n", minor_class_name);
	else
		printf("\n");

	return p;
}

static void print_dev_class(const uint32_t dev_class)
{
	uint16_t major_service;		/* major service */
	uint8_t major_class;		/* major class */
	const char *minor_class_name;
	uint8_t format;
	int i;
	char buf[64];

	/* take major class into service bits for decoding */
	major_service = (dev_class & 0xffff00) >> 8;
	major_class = (dev_class & 0x001f00) >> 8;
	format = (dev_class & 0x000003);

	printf("Class of Device: %#x\n", dev_class);

	/* decode minor class */

	/* FIXME hard-coded index value */
	switch (major_class) {
	case 0x01: /* Computer */
		decode_bitfield_minor_class(dev_class, 2, &minor_class_vals[0]);
		break;
	case 0x02: /* Phone */
		decode_bitfield_minor_class(dev_class, 2, &minor_class_vals[1]);
		break;
	case 0x03: /* LAN/Network Access Point */
		decode_bitfield_minor_class(dev_class, 5, &minor_class_vals[2]);
		decode_bitfield_minor_class(dev_class, 2, &minor_class_vals[3]);
		break;
	case 0x04: /* Audio/Video */
		decode_bitfield_minor_class(dev_class, 2, &minor_class_vals[4]);
		break;
	case 0x05: /* Peripheral */
		decode_bitfield_minor_class(dev_class, 6, &minor_class_vals[5]);
		decode_bitfield_minor_class(dev_class, 2, &minor_class_vals[6]);
		break;
	case 0x06: /* Imaging */
		decode_bitfield_minor_class(dev_class, 7, &minor_class_vals[7]);
		decode_bitfield_minor_class(dev_class, 6, &minor_class_vals[8]);
		decode_bitfield_minor_class(dev_class, 5, &minor_class_vals[9]);
		decode_bitfield_minor_class(dev_class, 4, &minor_class_vals[10]);

		break;
	case 0x07: /* Wearable */
		decode_bitfield_minor_class(dev_class, 2, &minor_class_vals[11]);
		break;
	case 0x08: /* Toy */
		decode_bitfield_minor_class(dev_class, 2, &minor_class_vals[12]);
		break;
	case 0x09: /* Health */
		decode_bitfield_minor_class(dev_class, 2, &minor_class_vals[13]);
		break;
	default:
		minor_class_name = "Unknown";
		printf(" %s\n", minor_class_name);
		break;
	}

	/* decode format */
	decode_bitfield_value(buf, format,
			minor_class_vals[MINOR_CLASS_NUM+1].bitmask,
			minor_class_vals[MINOR_CLASS_NUM+1].width);
	printf("\t%s%s: %02x\n", buf, minor_class_vals[MINOR_CLASS_NUM+1].name, format);

	/* major service and class */
	for (i = 0; i < MAJOR_SERVICE_NUM; i++) {
		decode_bitfield_value(buf, major_service,
				service_class_vals[i].bitmask,
				service_class_vals[i].width);
		printf("\t%s%s", buf, service_class_vals[i].name);

		if (service_class_vals[i].strings == NULL) {
			printf(" : %s\n", (strchr(buf, '1') != NULL) ? "True" : "False");
			continue;
		}

		printf(": %s\t0x%04x\n",
				val_to_str(service_class_vals[i].bitmask & major_service,
					   service_class_vals[i].strings),
				service_class_vals[i].bitmask & major_service);
	}
}

int main(int argc, char **argv)
{
	uint32_t dev_class;

	if (argc != 2)
		dev_class = 0x08043c;
	else
		dev_class = strtoul(argv[1], NULL, 16);
	print_dev_class(dev_class);

	return 0;
}
