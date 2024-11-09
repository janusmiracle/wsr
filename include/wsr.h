/* clang-format off */
#ifndef WAVE_STRUCTURE_READER_H
#define WAVE_STRUCTURE_READER_H


#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <uuid/uuid.h>

/* System endianness check, ignore non-little endian systems. */
#if (__BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__)
  #error "Only little-endian systems are supported."
#endif

#define FOURCC(a, b, c, d) ((uint32_t) ((a) | ((b) << 8) | ((c) << 16) | (((uint32_t) (d)) << 24)))

/* RIFF master FourCC codes for WAVE. */
#define RIFF_CODE FOURCC('R', 'I', 'F', 'F')
#define RIFX_CODE FOURCC('R', 'I', 'F', 'X')
#define FFIR_CODE FOURCC('F', 'F', 'I', 'R')
#define RF64_CODE FOURCC('R', 'F', '6', '4')
#define BW64_CODE FOURCC('B', 'W', '6', '4')

/* Single valid formtype FourCC code for WAVE. */
#define WAVE_CODE FOURCC('W', 'A', 'V', 'E')

/* Chunk FOURCC codes. */ 
#define ACID_CODE FOURCC('a', 'c', 'i', 'd')
#define ADTL_CODE FOURCC('a', 'd', 't', 'l')
#define BEXT_CODE FOURCC('b', 'e', 'x', 't')
#define CART_CODE FOURCC('c', 'a', 'r', 't')
#define CHNA_CODE FOURCC('c', 'h', 'n', 'a')
#define CUE_CODE  FOURCC('c', 'u', 'e', ' ')
#define DISP_CODE FOURCC('D', 'I', 'S', 'P')
#define FACT_CODE FOURCC('f', 'a', 'c', 't')
#define FMT_CODE  FOURCC('f', 'm', 't', ' ')
#define INFO_CODE FOURCC('I', 'N', 'F', 'O')
#define INST_CODE FOURCC('i', 'n', 's', 't')
#define LEVL_CODE FOURCC('l', 'e', 'v', 'l')
#define LIST_CODE FOURCC('L', 'I', 'S', 'T')
#define MD5_CODE  FOURCC('M', 'D', '5', ' ')
#define SMPL_CODE FOURCC('s', 'm', 'p', 'l')
#define STRC_CODE FOURCC('s', 't', 'r', 'c')

/* INFO tags. */ 
#define IARL_CODE FOURCC('I', 'A', 'R', 'L')
#define IART_CODE FOURCC('I', 'A', 'R', 'T')
#define ICMS_CODE FOURCC('I', 'C', 'M', 'S')
#define ICMT_CODE FOURCC('I', 'C', 'M', 'T')
#define ICOP_CODE FOURCC('I', 'C', 'O', 'P')
#define ICRD_CODE FOURCC('I', 'C', 'R', 'D')
#define ICRP_CODE FOURCC('I', 'C', 'R', 'P')
#define IDIM_CODE FOURCC('I', 'D', 'I', 'M')
#define IDPI_CODE FOURCC('I', 'D', 'P', 'I')
#define IENG_CODE FOURCC('I', 'E', 'N', 'G')
#define IGNR_CODE FOURCC('I', 'G', 'N', 'R')
#define IKEY_CODE FOURCC('I', 'K', 'E', 'Y')
#define ILGT_CODE FOURCC('I', 'L', 'G', 'T')
#define IMED_CODE FOURCC('I', 'M', 'E', 'D')
#define INAM_CODE FOURCC('I', 'N', 'A', 'M')
#define IPLT_CODE FOURCC('I', 'P', 'L', 'T')
#define IPRD_CODE FOURCC('I', 'P', 'R', 'D')
#define ISBJ_CODE FOURCC('I', 'S', 'B', 'J')
#define ISFT_CODE FOURCC('I', 'S', 'F', 'T')
#define ISRC_CODE FOURCC('I', 'S', 'R', 'C')
#define ISRF_CODE FOURCC('I', 'S', 'R', 'F')
#define ITCH_CODE FOURCC('I', 'T', 'C', 'H')

/* WAVE_FORMAT_EXTENSIBLE GUIDS. */ 
/* MSGUID_SUBTYPE_PCM
   MSGUID_SUBTYPE_MS_ADPCM
   MSGUID_SUBTYPE_IEEE_FLOAT
   MSGUID_SUBTYPE_ALAW
   MSGUID_SUBTYPE_MULAW
   MSGUID_SUBTYPE_AMBISONIC_B_FORMAT_PCM
   MSGUID_SUBTYPE_AMBISONIC_B_FORMAT_IEEE_FLOAT
   MSGUID_SUBTYPE_PVOCEX

TODO: Figure the above out. I only have PVOC-EX test files.
*/

#define EXTENSIBLE 65534
#define MSGUID_SUBTYPE_PVOCEX "C2B91283-6E2E-D411-A824-DE5B96C3AB21"

/* Generic speaker layouts. */
#define FRONT_LEFT            0x01
#define FRONT_RIGHT           0x02
#define FRONT_CENTER          0x04
#define LOW_FREQUENCY         0x08
#define BACK_LEFT             0x10
#define BACK_RIGHT            0x20
#define FRONT_LEFT_OF_CENTER  0x40
#define FRONT_RIGHT_OF_CENTER 0x80
#define BACK_CENTER           0x100
#define SIDE_LEFT             0x200
#define SIDE_RIGHT            0x400
#define TOP_CENTER            0x800
#define TOP_FRONT_LEFT        0x1000
#define TOP_FRONT_RIGHT       0x2000
#define TOP_BACK_LEFT         0x4000
#define TOP_BACK_RIGHT        0x8000

#define BEXT_MIN_CHUNK_SIZE		602
#define LEVL_MIN_CHUNK_SIZE   120

/* Internal stream endianness, RIFX == BIG_ENDIAN */
typedef enum {
    LITTLE_ENDIAN = 0,  
    BIG_ENDIAN = 1 
} ENDIAN;

/* Log speaker layout bitmask. */
void wsr_logcmask(uint32_t channel_mask) {
  printf("  Speaker layout:\n");
    if (channel_mask & FRONT_LEFT)            printf("    Front Left\n");
    if (channel_mask & FRONT_RIGHT)           printf("    Front Right\n");
    if (channel_mask & FRONT_CENTER)          printf("    Front Center\n");
    if (channel_mask & LOW_FREQUENCY)         printf("    Low Frequency\n");
    if (channel_mask & BACK_LEFT)             printf("    Back Left\n");
    if (channel_mask & BACK_RIGHT)            printf("    Back Right\n");
    if (channel_mask & FRONT_LEFT_OF_CENTER)  printf("    Front Left of Center\n");
    if (channel_mask & FRONT_RIGHT_OF_CENTER) printf("    Front Right of Center\n");
    if (channel_mask & BACK_CENTER)           printf("    Back Center\n");
    if (channel_mask & SIDE_LEFT)             printf("    Side Left\n");
    if (channel_mask & SIDE_RIGHT)            printf("    Side Right\n");
    if (channel_mask & TOP_CENTER)            printf("    Top Center\n");
    if (channel_mask & TOP_FRONT_LEFT)        printf("    Top Front Left\n");
    if (channel_mask & TOP_FRONT_RIGHT)       printf("    Top Front Right\n");
    if (channel_mask & TOP_BACK_LEFT)         printf("    Top Back Left\n");
    if (channel_mask & TOP_BACK_RIGHT)        printf("    Top Back Right\n");
}
/* clang-format on */

/* Log packed FourCC codes as characters. */
void wsr_log4cc(uint32_t code, const char *log) {
  char a = code & 0xFF;
  char b = (code >> 8) & 0xFF;
  char c = (code >> 16) & 0xFF;
  char d = (code >> 24) & 0xFF;
  printf("%s: %c%c%c%c\n", log, a, b, c, d);
}

/* Reads data into given pointer, and handles endianness conversions. */
void wsr_fread(void *r_into, size_t size, size_t nmemb, FILE *stream,
               ENDIAN endian) {
  fread(r_into, size, nmemb, stream);

  if (endian == BIG_ENDIAN) {
    uint8_t *bdata = (uint8_t *)r_into;
    for (size_t i = 0; i < size / 2; i++) {
      uint8_t temp = bdata[i];
      bdata[i] = bdata[size - 1 - i];
      bdata[size - 1 - i] = temp;
    }
  }
}

/* Read WAVE file. */
void wsread(FILE *fp) {

  printf("wsr - wave structure reader\n\n");

  uint32_t master;
  fread(&master, sizeof(master), 1, fp);

  ENDIAN endianness;
  if (master == RIFF_CODE || master == RF64_CODE) {
    endianness = LITTLE_ENDIAN;
  } else if (master == RIFX_CODE || master == FFIR_CODE) {
    endianness = BIG_ENDIAN;
  } else {
    perror("Unknown file format. Exiting.\n");
    return;
  }

  wsr_log4cc(master, "Master identifier");
  printf("Endianness: %s\n",
         endianness == LITTLE_ENDIAN ? "LITTLE_ENDIAN" : "BIG_ENDIAN");

  uint32_t fsize;
  wsr_fread(&fsize, sizeof(fsize), 1, fp, endianness);

  /* TODO: Add FALSE_SIZE checks for RF64 later. */
  printf("File size: %u\n", fsize);

  uint32_t ftype;
  fread(&ftype, sizeof(ftype), 1, fp);

  if (ftype != WAVE_CODE) {
    perror("Invalid formtype. Exiting.\n");
    return;
  }

  wsr_log4cc(ftype, "Form type");

  uint32_t tr_size = 0; /* Total size read. */

  uint32_t preck_id = 0;
  /* Read chunks until EOF. */
  while (tr_size < fsize) {
    uint32_t ck_id;
    fread(&ck_id, sizeof(ck_id), 1, fp);

    if (preck_id == ck_id) {
      break; /* Assume that if a chunk repeats twice in a row,
                reading has failed and exit. */
    }
    if (ck_id > 1) {
      wsr_log4cc(ck_id, "\nChunk identifier");
    }

    uint32_t ck_size;
    wsr_fread(&ck_size, sizeof(ck_size), 1, fp, endianness);
    uint32_t ock_size = ck_size;
    if (ck_size > 1) {

      if (ck_size % 2 && ck_id != BEXT_CODE) {
        ck_size++; /* Pad uneven chunks. */
      }

      if (ck_id == LIST_CODE) {
        uint32_t ltype;
        fread(&ltype, sizeof(ltype), 1, fp);

        wsr_log4cc(ltype, "  List type");

        ck_size -= 4; /* Get list-type chunk size (minus LIST). */
        printf("  Size: %u (%d)\n", ock_size, ck_size);

        ck_id = ltype; /* Set chunk identifier to list-type. */
      } else {
        if (ck_size > ock_size) {
          printf("Size: %u (+%u)\n", ock_size, ck_size - ock_size);
        } else if (ck_size < ock_size) {
          printf("Size: %u (-%u)\n", ock_size, ock_size - ck_size);
        } else {
          printf("Size: %u\n", ock_size);
        }
      }
    }

    /* Save current position for seek. */
    long curr_pos = ftell(fp);

    /* Decode each chunk. */
    switch (ck_id) {
    case ACID_CODE: {
      uint32_t properties;
      wsr_fread(&properties, sizeof(properties), 1, fp, endianness);
      printf("Properties: 0x%x\n", properties);
      printf("  Oneshot: %d\n", (properties & 0x01) != 0);
      printf("  Root note: %d\n", (properties & 0x02) != 0);
      printf("  Stretched: %d\n", (properties & 0x04) != 0);
      printf("  Disk based: %d\n", (properties & 0x08) != 0);
      printf("  Unknown: %d\n", (properties & 0x10) != 0);

      uint16_t root_note;
      wsr_fread(&root_note, sizeof(root_note), 1, fp, endianness);
      printf("Root note: %hu\n", root_note);

      /* Unknown values. */
      uint16_t u1;
      wsr_fread(&u1, sizeof(u1), 1, fp, endianness);
      printf("Unknown 1: %hu\n", u1);

      float u2;
      wsr_fread(&u2, sizeof(u2), 1, fp, endianness);
      printf("Unknown 2: %f\n", u2);

      uint32_t beat_count;
      wsr_fread(&beat_count, sizeof(beat_count), 1, fp, endianness);
      printf("Beat count: %u\n", beat_count);

      uint16_t meter_num;
      wsr_fread(&meter_num, sizeof(meter_num), 1, fp, endianness);
      printf("Meter numerator: %hu\n", meter_num);

      uint16_t meter_denom; /* NOTE: could be opposite (meter_num). */
      wsr_fread(&meter_denom, sizeof(meter_denom), 1, fp, endianness);
      printf("Meter denominator: %hu\n", meter_denom);

      float tempo;
      wsr_fread(&tempo, sizeof(tempo), 1, fp, endianness);
      printf("Tempo: %f\n", tempo);

      break;
    }
    case BEXT_CODE: {
      char description[257];
      wsr_fread(&description, 1, 256, fp, endianness);
      description[256] = '\0';
      printf("Description: %s\n", description);

      char originator[33];
      wsr_fread(&originator, 1, 32, fp, endianness);
      originator[32] = '\0';
      printf("Originator: %s\n", originator);

      char originator_ref[33];
      wsr_fread(&originator_ref, 1, 32, fp, endianness);
      originator_ref[32] = '\0';
      printf("Originator reference: %s\n", originator_ref);

      char origin_date[11];
      wsr_fread(&origin_date, 1, 10, fp, endianness);
      origin_date[10] = '\0';
      printf("Origin date: %s\n", origin_date);

      char origin_time[9];
      wsr_fread(&origin_time, 1, 8, fp, endianness);
      origin_time[8] = '\0';
      printf("Origin time: %s\n", origin_time);

      uint32_t time_ref_low;
      wsr_fread(&time_ref_low, sizeof(time_ref_low), 1, fp, endianness);
      printf("Time reference low: %u\n", time_ref_low);

      uint32_t time_ref_high;
      wsr_fread(&time_ref_high, sizeof(time_ref_high), 1, fp, endianness);
      printf("Time reference high: %u\n", time_ref_high);

      uint16_t version;
      wsr_fread(&version, sizeof(version), 1, fp, endianness);
      printf("Version: %hu\n", version);

      char smpte_umid[64];
      wsr_fread(&smpte_umid, 1, 63, fp, endianness);
      smpte_umid[63] = '\0';
      printf("SMPTE umid: %s\n", smpte_umid);

      uint16_t loudness_value;
      wsr_fread(&loudness_value, sizeof(loudness_value), 1, fp, endianness);
      printf("Loudness value: %hu\n", loudness_value);

      uint16_t loudness_range;
      wsr_fread(&loudness_range, sizeof(loudness_range), 1, fp, endianness);
      printf("Loudness range: %hu\n", loudness_range);

      uint16_t max_true_peak_level;
      wsr_fread(&max_true_peak_level, sizeof(max_true_peak_level), 1, fp,
                endianness);
      printf("Max true peak level: %hu\n", max_true_peak_level);

      uint16_t max_momentary_loudness;
      wsr_fread(&max_momentary_loudness, sizeof(max_momentary_loudness), 1, fp,
                endianness);
      printf("Max momentary loudness: %hu\n", max_momentary_loudness);

      uint16_t max_short_term_loudness;
      wsr_fread(&max_short_term_loudness, sizeof(max_short_term_loudness), 1,
                fp, endianness);
      printf("Max short term loudness: %hu\n", max_short_term_loudness);

      fseek(fp, 180, SEEK_CUR); /* Skip RESERVED. */

      if (ck_size > BEXT_MIN_CHUNK_SIZE) {
        /* Coding history exists. */
        size_t ch_size = ck_size - BEXT_MIN_CHUNK_SIZE;
        char coding_history[ch_size];
        wsr_fread(&coding_history, 1, ch_size, fp, endianness);

        printf("Coding history: ");
        for (size_t i = 0; i < ch_size; i++) {
          /* NULL bytes MUST be ignored to properly print coding history. */
          if (coding_history[i] == '\0') {
            continue;
          }
          printf("%c", coding_history[i]);
        }
        printf("\n");
        printf(
            " Coding history field info:\n  A=(Coding algorithm)\n  "
            "F=(Sampling frequency in Hz)\n  B=(bitrate for MPEG 2 in kbit/s "
            "per channel)\n  W=(Word length for MPEG coding in bits)\n  "
            "M=(mode)\n  T=(text, could be ID-No, codec-type, A/D type..)\n");
      }

      break;
    }

    case DISP_CODE: {
      uint32_t cftype;
      wsr_fread(&cftype, sizeof(cftype), 1, fp, endianness);

      char cfdata[ck_size - 4];
      wsr_fread(&cfdata, 1, ck_size - 4, fp, endianness);

      printf("CF type: %d\nCF data: %s\n", cftype, cfdata);
      break;
    }

    case FACT_CODE: {
      uint32_t samples;
      wsr_fread(&samples, sizeof(samples), 1, fp, endianness);
      printf("Samples: %u\n", samples);
      break;
    }

    case FMT_CODE: {
      uint16_t audio_format;
      wsr_fread(&audio_format, sizeof(audio_format), 1, fp, endianness);
      printf("Audio format: %hu\n", audio_format);

      uint16_t num_channels;
      wsr_fread(&num_channels, sizeof(num_channels), 1, fp, endianness);
      printf("Channel count: %hu\n", num_channels);

      uint32_t sample_rate;
      wsr_fread(&sample_rate, sizeof(sample_rate), 1, fp, endianness);
      printf("Sample rate: %u\n", sample_rate);

      uint32_t byte_rate;
      wsr_fread(&byte_rate, sizeof(byte_rate), 1, fp, endianness);
      printf("Byte rate: %u\n", byte_rate);

      uint16_t block_align;
      wsr_fread(&block_align, sizeof(block_align), 1, fp, endianness);
      printf("Block align: %hu\n", block_align);

      uint16_t bits_per_sample;
      wsr_fread(&bits_per_sample, sizeof(bits_per_sample), 1, fp, endianness);
      printf("Bits per sample: %hu\n", bits_per_sample);

      if (ck_size > 16) {
        uint16_t ext_size;
        wsr_fread(&ext_size, sizeof(ext_size), 1, fp, endianness);
        printf("Extension size: %hu\n", ext_size);
      }

      if (audio_format == EXTENSIBLE) {
        uint16_t valid_bps;
        wsr_fread(&valid_bps, sizeof(valid_bps), 1, fp, endianness);
        printf("Valid bits per sample: %hu\n", valid_bps);

        uint32_t channel_mask;
        wsr_fread(&channel_mask, sizeof(channel_mask), 1, fp, endianness);
        printf("Channel mask: 0x%X\n", channel_mask);
        wsr_logcmask(channel_mask);

        uint8_t sfmt[16];
        wsr_fread(&sfmt, sizeof(uint8_t), sizeof(sfmt), fp, endianness);

        uint16_t format_code;
        memcpy(&format_code, sfmt, sizeof(format_code));
        printf("Format code: %hu\n", format_code);

        uuid_t guid;
        memcpy(&guid, sfmt, sizeof(guid));
        char guid_str[37];
        uuid_unparse(guid, guid_str);
        printf("GUID: %s\n", guid_str);

        if (strcmp(guid_str, MSGUID_SUBTYPE_PVOCEX) == 0 && ck_size == 80) {
          uint32_t version;
          wsr_fread(&version, sizeof(version), 1, fp, endianness);
          printf("Version: %u\n", version);

          uint32_t pvoc_size;
          wsr_fread(&pvoc_size, sizeof(pvoc_size), 1, fp, endianness);
          printf("PVOC-EX size: %u\n", pvoc_size);

          uint16_t word_format;
          wsr_fread(&word_format, sizeof(word_format), 1, fp, endianness);
          printf("Word format: %hu\n", word_format);

          uint16_t analysis_format;
          wsr_fread(&analysis_format, sizeof(analysis_format), 1, fp,
                    endianness);
          printf("Analysis format: %hu\n", analysis_format);

          uint16_t source_format;
          wsr_fread(&source_format, sizeof(source_format), 1, fp, endianness);
          printf("Source format: %hu\n", source_format);

          uint16_t window_type;
          wsr_fread(&window_type, sizeof(window_type), 1, fp, endianness);
          printf("Window type: %hu\n", window_type);

          uint32_t bin_count;
          wsr_fread(&bin_count, sizeof(bin_count), 1, fp, endianness);
          printf("Bin count: %u\n", bin_count);

          uint32_t window_length;
          wsr_fread(&window_length, sizeof(window_length), 1, fp, endianness);
          printf("Window length: %u\n", window_length);

          uint32_t overlap;
          wsr_fread(&overlap, sizeof(overlap), 1, fp, endianness);
          printf("Overlap: %u\n", overlap);

          uint32_t frame_align;
          wsr_fread(&frame_align, sizeof(frame_align), 1, fp, endianness);
          printf("Frame align: %u\n", frame_align);

          float analysis_rate;
          wsr_fread(&analysis_rate, sizeof(analysis_rate), 1, fp, endianness);
          printf("Analysis rate: %f\n", analysis_rate);

          float window_param;
          wsr_fread(&window_param, sizeof(window_param), 1, fp, endianness);
          printf("Window parameter: %f\n", window_param);
        }
      }
      break;
    }
    case INFO_CODE: {

      int nrec = 0;         /* Not-recognized tag identifier flag. */
      uint32_t pre_tid = 0; /* Track previous tag identifier. */
      while (1) {
        uint32_t t_id;
        fread(&t_id, sizeof(t_id), 1, fp);
        if (pre_tid == t_id) {
          break;
        }

        const char *t_mean = NULL;

        /* clang-format off */
        switch (t_id) {
            case IARL_CODE: t_mean = "Archival location"; break;
            case IART_CODE: t_mean = "Artist"; break;
            case ICMS_CODE: t_mean = "Commissioned"; break;
            case ICMT_CODE: t_mean = "Comments"; break;
            case ICOP_CODE: t_mean = "Copyright"; break;
            case ICRD_CODE: t_mean = "Creation date"; break;
            case ICRP_CODE: t_mean = "Cropped"; break;
            case IDIM_CODE: t_mean = "Dimensions"; break;
            case IDPI_CODE: t_mean = "Dots per inch"; break;
            case IENG_CODE: t_mean = "Engineer"; break;
            case IGNR_CODE: t_mean = "Genre"; break;
            case IKEY_CODE: t_mean = "Keywords"; break;
            case ILGT_CODE: t_mean = "Lightness"; break;
            case IMED_CODE: t_mean = "Medium"; break;
            case INAM_CODE: t_mean = "Name (title)"; break;
            case IPLT_CODE: t_mean = "Palette"; break;
            case IPRD_CODE: t_mean = "Product (album)"; break;
            case ISBJ_CODE: t_mean = "Subject"; break;
            case ISFT_CODE: t_mean = "Software"; break;
            case ISRC_CODE: t_mean = "Source"; break;
            case ISRF_CODE: t_mean = "Source form"; break;
            case ITCH_CODE: t_mean = "Technician"; break;
            default: {
                nrec = 1; /* Set the not-recognized flag. 
                             Although, it should never reach this.
                          */
                break;
            }
        }
        /* clang-format on */

        if (nrec) {
          break;
        }

        wsr_log4cc(t_id, "    Tag");

        uint32_t t_size;
        /* Have only seen RIFX files with `fmt ` and `data` chunks,
           so I am assuming identifiers (even tags) are always little,
           but the sizes and data are ENDIAN dependent. */
        wsr_fread(&t_size, sizeof(t_size), 1, fp, endianness);

        if (t_size < 1) {
          break;
        }

        uint32_t ot_size = t_size;

        if (t_size % 2) {
          t_size++; /* Pad uneven sizes. */
        }

        if (t_size > ot_size) {
          printf("    Tsize: %d (+%d)\n", ot_size, t_size - ot_size);
        } else {
          printf("    Tsize: %d\n", t_size);
        }

        char r_tag[t_size];
        wsr_fread(&r_tag, 1, t_size, fp, endianness);

        printf("    %s: %s\n\n", t_mean, r_tag);

        pre_tid = t_id;
      }
      break;
    }

    case INST_CODE: {
      char unshifted_note;
      wsr_fread(&unshifted_note, 1, 1, fp, endianness);
      printf("Unshifted note: %d\n", unshifted_note);

      char fine_tuning;
      wsr_fread(&fine_tuning, 1, 1, fp, endianness);
      printf("Fine-tuning: %d\n", fine_tuning);

      char gain;
      wsr_fread(&gain, 1, 1, fp, endianness);
      printf("Gain: %d\n", gain);

      char low_note;
      wsr_fread(&low_note, 1, 1, fp, endianness);
      printf("Low note: %d\n", low_note);

      char high_note;
      wsr_fread(&high_note, 1, 1, fp, endianness);
      printf("High note: %d\n", high_note);

      char low_velocity;
      wsr_fread(&low_velocity, 1, 1, fp, endianness);
      printf("Low velocity: %d\n", low_velocity);

      char high_velocity;
      wsr_fread(&high_velocity, 1, 1, fp, endianness);
      printf("High velocity: %d\n", high_velocity);

      break;
    }

    case LEVL_CODE: {
      uint32_t version;
      wsr_fread(&version, sizeof(version), 1, fp, endianness);

      uint32_t format;
      wsr_fread(&format, sizeof(format), 1, fp, endianness);

      uint32_t points_per_value;
      wsr_fread(&points_per_value, sizeof(points_per_value), 1, fp, endianness);

      uint32_t block_size;
      wsr_fread(&block_size, sizeof(block_size), 1, fp, endianness);

      uint32_t channel_count;
      wsr_fread(&channel_count, sizeof(channel_count), 1, fp, endianness);

      uint32_t frame_count;
      wsr_fread(&frame_count, sizeof(frame_count), 1, fp, endianness);

      uint32_t position;
      wsr_fread(&position, sizeof(version), 1, fp, endianness);

      uint32_t offset;
      wsr_fread(&offset, sizeof(offset), 1, fp, endianness);

      /* Timestamp is always 28 bytes, reserved 60. */
      char timestamp[28];
      wsr_fread(&timestamp, 1, 28, fp, endianness);

      char reserved[60];
      wsr_fread(&reserved, 1, 60, fp, endianness);

      printf("Version: %d\nFormat: %d\nPoints per value: %d\nBlock size: "
             "%d\nChannel count: %d\nFrame count: %d\nPosition: %d\nOffset: "
             "%d\nTimestamp: %s\nReserved: %s\n",
             version, format, points_per_value, block_size, channel_count,
             frame_count, position, offset, timestamp, reserved);

      /* Everything after reserved is peak envelope data, ignore. */
      break;
    }

    case MD5_CODE: {
      uint64_t buffront;
      wsr_fread(&buffront, sizeof(buffront), 1, fp, endianness);
      uint64_t bufback;
      wsr_fread(&bufback, sizeof(bufback), 1, fp, endianness);
      /* Cannot tell if this is correct. */
      printf("Checksum: %llu%llu\n", buffront, bufback);
      break;
    }

    case STRC_CODE:
      /* Almost entirely undocumented, not worth implementing. */
      break;
    default:
      break; /* Generic or unsupported chunk. */
    }

    /* Update total size read. */
    tr_size += ck_size;
    preck_id = ck_id;
    fseek(fp, ck_size + curr_pos, SEEK_SET); /* Next chunk. */
  }
}

#endif // WAVE_STRUCTURE_READER_H
