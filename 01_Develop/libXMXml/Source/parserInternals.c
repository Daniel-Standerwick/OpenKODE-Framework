/*
 * parserInternals.c : Internal routines (and obsolete ones) needed for the
 *                     XML and HTML parsers.
 *
 * See Copyright for the status of this software.
 *
 * daniel@veillard.com
 */

#define IN_LIBXML
#include "libxml.h"

#define XML_DIR_SEP '/'

#include <XMXML/xmlmemory.h>
#include <XMXML/tree.h>
#include <XMXML/parser.h>
#include <XMXML/parserInternals.h>
#include <XMXML/valid.h>
#include <XMXML/entities.h>
#include <XMXML/xmlerror.h>
#include <XMXML/encoding.h>
#include <XMXML/valid.h>
#include <XMXML/xmlIO.h>
#include <XMXML/uri.h>
#include <XMXML/dict.h>
#include <XMXML/SAX.h>
#ifdef LIBXML_CATALOG_ENABLED
#include <XMXML/catalog.h>
#endif
#include <XMXML/globals.h>
#include <XMXML/chvalid.h>

/*
 * Various global defaults for parsing
 */

/**
 * xmlCheckVersion:
 * @version: the include version number
 *
 * check the compiled lib version against the include one.
 * This can warn or immediately kill the application
 */
void
xmlCheckVersion(int version) {
    int myversion = (int) LIBXML_VERSION;

    xmlInitParser();

    if ((myversion / 10000) != (version / 10000)) {
	xmlGenericError(xmlGenericErrorContext, 
		"Fatal: program compiled against libxml %d using libxml %d\n",
		(version / 10000), (myversion / 10000));
	kdPrintf ( 
		"Fatal: program compiled against libxml %d using libxml %d\n",
		(version / 10000), (myversion / 10000));
    }
    if ((myversion / 100) < (version / 100)) {
	xmlGenericError(xmlGenericErrorContext, 
		"Warning: program compiled against libxml %d using older %d\n",
		(version / 100), (myversion / 100));
    }
}


/************************************************************************
 *									*
 * 		Some factorized error routines				*
 *									*
 ************************************************************************/


/**
 * xmlErrMemory:
 * @ctxt:  an XML parser context
 * @extra:  extra informations
 *
 * Handle a redefinition of attribute error
 */
void
xmlErrMemory(xmlParserCtxtPtr ctxt, const char *extra)
{
    if ((ctxt != KD_NULL) && (ctxt->disableSAX != 0) &&
        (ctxt->instate == XML_PARSER_EOF))
	return;
    if (ctxt != KD_NULL) {
        ctxt->errNo = XML_ERR_NO_MEMORY;
        ctxt->instate = XML_PARSER_EOF;
        ctxt->disableSAX = 1;
    }
    if (extra)
        __xmlRaiseError(KD_NULL, KD_NULL, KD_NULL, ctxt, KD_NULL, XML_FROM_PARSER,
                        XML_ERR_NO_MEMORY, XML_ERR_FATAL, KD_NULL, 0, extra,
                        KD_NULL, KD_NULL, 0, 0,
                        "Memory allocation failed : %s\n", extra);
    else
        __xmlRaiseError(KD_NULL, KD_NULL, KD_NULL, ctxt, KD_NULL, XML_FROM_PARSER,
                        XML_ERR_NO_MEMORY, XML_ERR_FATAL, KD_NULL, 0, KD_NULL,
                        KD_NULL, KD_NULL, 0, 0, "Memory allocation failed\n");
}

/**
 * __xmlErrEncoding:
 * @ctxt:  an XML parser context
 * @xmlerr:  the error number
 * @msg:  the error message
 * @str1:  an string info
 * @str2:  an string info
 *
 * Handle an encoding error
 */
void
__xmlErrEncoding(xmlParserCtxtPtr ctxt, xmlParserErrors xmlerr,
                 const char *msg, const xmlChar * str1, const xmlChar * str2)
{
    if ((ctxt != KD_NULL) && (ctxt->disableSAX != 0) &&
        (ctxt->instate == XML_PARSER_EOF))
	return;
    if (ctxt != KD_NULL)
        ctxt->errNo = xmlerr;
    __xmlRaiseError(KD_NULL, KD_NULL, KD_NULL,
                    ctxt, KD_NULL, XML_FROM_PARSER, xmlerr, XML_ERR_FATAL,
                    KD_NULL, 0, (const char *) str1, (const char *) str2,
                    KD_NULL, 0, 0, msg, str1, str2);
    if (ctxt != KD_NULL) {
        ctxt->wellFormed = 0;
        if (ctxt->recovery == 0)
            ctxt->disableSAX = 1;
    }
}

/**
 * xmlErrInternal:
 * @ctxt:  an XML parser context
 * @msg:  the error message
 * @str:  error informations
 *
 * Handle an internal error
 */
static void
xmlErrInternal(xmlParserCtxtPtr ctxt, const char *msg, const xmlChar * str)
{
    if ((ctxt != KD_NULL) && (ctxt->disableSAX != 0) &&
        (ctxt->instate == XML_PARSER_EOF))
	return;
    if (ctxt != KD_NULL)
        ctxt->errNo = XML_ERR_INTERNAL_ERROR;
    __xmlRaiseError(KD_NULL, KD_NULL, KD_NULL,
                    ctxt, KD_NULL, XML_FROM_PARSER, XML_ERR_INTERNAL_ERROR,
                    XML_ERR_FATAL, KD_NULL, 0, (const char *) str, KD_NULL, KD_NULL,
                    0, 0, msg, str);
    if (ctxt != KD_NULL) {
        ctxt->wellFormed = 0;
        if (ctxt->recovery == 0)
            ctxt->disableSAX = 1;
    }
}

/**
 * xmlErrEncodingInt:
 * @ctxt:  an XML parser context
 * @error:  the error number
 * @msg:  the error message
 * @val:  an integer value
 *
 * n encoding error
 */
static void
xmlErrEncodingInt(xmlParserCtxtPtr ctxt, xmlParserErrors error,
                  const char *msg, int val)
{
    if ((ctxt != KD_NULL) && (ctxt->disableSAX != 0) &&
        (ctxt->instate == XML_PARSER_EOF))
	return;
    if (ctxt != KD_NULL)
        ctxt->errNo = error;
    __xmlRaiseError(KD_NULL, KD_NULL, KD_NULL,
                    ctxt, KD_NULL, XML_FROM_PARSER, error, XML_ERR_FATAL,
                    KD_NULL, 0, KD_NULL, KD_NULL, KD_NULL, val, 0, msg, val);
    if (ctxt != KD_NULL) {
        ctxt->wellFormed = 0;
        if (ctxt->recovery == 0)
            ctxt->disableSAX = 1;
    }
}

/**
 * xmlIsLetter:
 * @c:  an unicode character (int)
 *
 * Check whether the character is allowed by the production
 * [84] Letter ::= BaseChar | Ideographic
 *
 * Returns 0 if not, non-zero otherwise
 */
int
xmlIsLetter(int c) {
    return(IS_BASECHAR(c) || IS_IDEOGRAPHIC(c));
}

/************************************************************************
 *									*
 * 		Input handling functions for progressive parsing	*
 *									*
 ************************************************************************/

/* #define DEBUG_INPUT */
/* #define DEBUG_STACK */
/* #define DEBUG_PUSH */


/* we need to keep enough input to show errors in context */
#define LINE_LEN        80

#ifdef DEBUG_INPUT
#define CHECK_BUFFER(in) check_buffer(in)

static
void check_buffer(xmlParserInputPtr in) {
    if (in->base != in->buf->buffer->content) {
        xmlGenericError(xmlGenericErrorContext,
		"xmlParserInput: base mismatch problem\n");
    }
    if (in->cur < in->base) {
        xmlGenericError(xmlGenericErrorContext,
		"xmlParserInput: cur < base problem\n");
    }
    if (in->cur > in->base + in->buf->buffer->use) {
        xmlGenericError(xmlGenericErrorContext,
		"xmlParserInput: cur > base + use problem\n");
    }
    xmlGenericError(xmlGenericErrorContext,"buffer %x : content %x, cur %d, use %d, size %d\n",
            (int) in, (int) in->buf->buffer->content, in->cur - in->base,
	    in->buf->buffer->use, in->buf->buffer->size);
}

#else
#define CHECK_BUFFER(in) 
#endif


/**
 * xmlParserInputRead:
 * @in:  an XML parser input
 * @len:  an indicative size for the lookahead
 *
 * This function refresh the input for the parser. It doesn't try to
 * preserve pointers to the input buffer, and discard already read data
 *
 * Returns the number of xmlChars read, or -1 in case of error, 0 indicate the
 * end of this entity
 */
int
xmlParserInputRead(xmlParserInputPtr in, int len) {
    int ret;
    int used;
    int indx;

    if (in == KD_NULL) return(-1);
#ifdef DEBUG_INPUT
    xmlGenericError(xmlGenericErrorContext, "Read\n");
#endif
    if (in->buf == KD_NULL) return(-1);
    if (in->base == KD_NULL) return(-1);
    if (in->cur == KD_NULL) return(-1);
    if (in->buf->buffer == KD_NULL) return(-1);
    if (in->buf->readcallback == KD_NULL) return(-1);

    CHECK_BUFFER(in);

    used = in->cur - in->buf->buffer->content;
    ret = xmlBufferShrink(in->buf->buffer, used);
    if (ret > 0) {
	in->cur -= ret;
	in->consumed += ret;
    }
    ret = xmlParserInputBufferRead(in->buf, len);
    if (in->base != in->buf->buffer->content) {
        /*
	 * the buffer has been reallocated
	 */
	indx = in->cur - in->base;
	in->base = in->buf->buffer->content;
	in->cur = &in->buf->buffer->content[indx];
    }
    in->end = &in->buf->buffer->content[in->buf->buffer->use];

    CHECK_BUFFER(in);

    return(ret);
}

/**
 * xmlParserInputGrow:
 * @in:  an XML parser input
 * @len:  an indicative size for the lookahead
 *
 * This function increase the input for the parser. It tries to
 * preserve pointers to the input buffer, and keep already read data
 *
 * Returns the number of xmlChars read, or -1 in case of error, 0 indicate the
 * end of this entity
 */
int
xmlParserInputGrow(xmlParserInputPtr in, int len) {
    int ret;
    int indx;

    if (in == KD_NULL) return(-1);
#ifdef DEBUG_INPUT
    xmlGenericError(xmlGenericErrorContext, "Grow\n");
#endif
    if (in->buf == KD_NULL) return(-1);
    if (in->base == KD_NULL) return(-1);
    if (in->cur == KD_NULL) return(-1);
    if (in->buf->buffer == KD_NULL) return(-1);

    CHECK_BUFFER(in);

    indx = in->cur - in->base;
    if (in->buf->buffer->use > (unsigned int) indx + INPUT_CHUNK) {

	CHECK_BUFFER(in);

        return(0);
    }
    if (in->buf->readcallback != KD_NULL)
	ret = xmlParserInputBufferGrow(in->buf, len);
    else	
        return(0);

    /*
     * NOTE : in->base may be a "dangling" i.e. freed pointer in this
     *        block, but we use it really as an integer to do some
     *        pointer arithmetic. Insure will raise it as a bug but in
     *        that specific case, that's not !
     */
    if (in->base != in->buf->buffer->content) {
        /*
	 * the buffer has been reallocated
	 */
	indx = in->cur - in->base;
	in->base = in->buf->buffer->content;
	in->cur = &in->buf->buffer->content[indx];
    }
    in->end = &in->buf->buffer->content[in->buf->buffer->use];

    CHECK_BUFFER(in);

    return(ret);
}

/**
 * xmlParserInputShrink:
 * @in:  an XML parser input
 *
 * This function removes used input for the parser.
 */
void
xmlParserInputShrink(xmlParserInputPtr in) {
    int used;
    int ret;
    int indx;

#ifdef DEBUG_INPUT
    xmlGenericError(xmlGenericErrorContext, "Shrink\n");
#endif
    if (in == KD_NULL) return;
    if (in->buf == KD_NULL) return;
    if (in->base == KD_NULL) return;
    if (in->cur == KD_NULL) return;
    if (in->buf->buffer == KD_NULL) return;

    CHECK_BUFFER(in);

    used = in->cur - in->buf->buffer->content;
    /*
     * Do not shrink on large buffers whose only a tiny fraction
     * was consumed
     */
    if (used > INPUT_CHUNK) {
	ret = xmlBufferShrink(in->buf->buffer, used - LINE_LEN);
	if (ret > 0) {
	    in->cur -= ret;
	    in->consumed += ret;
	}
	in->end = &in->buf->buffer->content[in->buf->buffer->use];
    }

    CHECK_BUFFER(in);

    if (in->buf->buffer->use > INPUT_CHUNK) {
        return;
    }
    xmlParserInputBufferRead(in->buf, 2 * INPUT_CHUNK);
    if (in->base != in->buf->buffer->content) {
        /*
	 * the buffer has been reallocated
	 */
	indx = in->cur - in->base;
	in->base = in->buf->buffer->content;
	in->cur = &in->buf->buffer->content[indx];
    }
    in->end = &in->buf->buffer->content[in->buf->buffer->use];

    CHECK_BUFFER(in);
}

/************************************************************************
 *									*
 * 		UTF8 character input and related functions		*
 *									*
 ************************************************************************/

/**
 * xmlNextChar:
 * @ctxt:  the XML parser context
 *
 * Skip to the next char input char.
 */

void
xmlNextChar(xmlParserCtxtPtr ctxt)
{
    if ((ctxt == KD_NULL) || (ctxt->instate == XML_PARSER_EOF) ||
        (ctxt->input == KD_NULL))
        return;

    if (ctxt->charset == XML_CHAR_ENCODING_UTF8) {
        if ((*ctxt->input->cur == 0) &&
            (xmlParserInputGrow(ctxt->input, INPUT_CHUNK) <= 0) &&
            (ctxt->instate != XML_PARSER_COMMENT)) {
            /*
             * If we are at the end of the current entity and
             * the context allows it, we pop consumed entities
             * automatically.
             * the auto closing should be blocked in other cases
             */
            xmlPopInput(ctxt);
        } else {
            const unsigned char *cur;
            unsigned char c;

            /*
             *   2.11 End-of-Line Handling
             *   the literal two-character sequence "#xD#xA" or a standalone
             *   literal #xD, an XML processor must pass to the application
             *   the single character #xA.
             */
            if (*(ctxt->input->cur) == '\n') {
                ctxt->input->line++; ctxt->input->col = 1;
            } else
                ctxt->input->col++;

            /*
             * We are supposed to handle UTF8, check it's valid
             * From rfc2044: encoding of the Unicode values on UTF-8:
             *
             * UCS-4 range (hex.)           UTF-8 octet sequence (binary)
             * 0000 0000-0000 007F   0xxxxxxx
             * 0000 0080-0000 07FF   110xxxxx 10xxxxxx
             * 0000 0800-0000 FFFF   1110xxxx 10xxxxxx 10xxxxxx 
             *
             * Check for the 0x110000 limit too
             */
            cur = ctxt->input->cur;

            c = *cur;
            if (c & 0x80) {
	        if (c == 0xC0)
		    goto encoding_error;
                if (cur[1] == 0) {
                    xmlParserInputGrow(ctxt->input, INPUT_CHUNK);
                    cur = ctxt->input->cur;
                }
                if ((cur[1] & 0xc0) != 0x80)
                    goto encoding_error;
                if ((c & 0xe0) == 0xe0) {
                    unsigned int val;

                    if (cur[2] == 0) {
                        xmlParserInputGrow(ctxt->input, INPUT_CHUNK);
                        cur = ctxt->input->cur;
                    }
                    if ((cur[2] & 0xc0) != 0x80)
                        goto encoding_error;
                    if ((c & 0xf0) == 0xf0) {
                        if (cur[3] == 0) {
                            xmlParserInputGrow(ctxt->input, INPUT_CHUNK);
                            cur = ctxt->input->cur;
                        }
                        if (((c & 0xf8) != 0xf0) ||
                            ((cur[3] & 0xc0) != 0x80))
                            goto encoding_error;
                        /* 4-byte code */
                        ctxt->input->cur += 4;
                        val = (cur[0] & 0x7) << 18;
                        val |= (cur[1] & 0x3f) << 12;
                        val |= (cur[2] & 0x3f) << 6;
                        val |= cur[3] & 0x3f;
                    } else {
                        /* 3-byte code */
                        ctxt->input->cur += 3;
                        val = (cur[0] & 0xf) << 12;
                        val |= (cur[1] & 0x3f) << 6;
                        val |= cur[2] & 0x3f;
                    }
                    if (((val > 0xd7ff) && (val < 0xe000)) ||
                        ((val > 0xfffd) && (val < 0x10000)) ||
                        (val >= 0x110000)) {
			xmlErrEncodingInt(ctxt, XML_ERR_INVALID_CHAR,
					  "Char 0x%X out of allowed range\n",
					  val);
                    }
                } else
                    /* 2-byte code */
                    ctxt->input->cur += 2;
            } else
                /* 1-byte code */
                ctxt->input->cur++;

            ctxt->nbChars++;
            if (*ctxt->input->cur == 0)
                xmlParserInputGrow(ctxt->input, INPUT_CHUNK);
        }
    } else {
        /*
         * Assume it's a fixed length encoding (1) with
         * a compatible encoding for the ASCII set, since
         * XML constructs only use < 128 chars
         */

        if (*(ctxt->input->cur) == '\n') {
            ctxt->input->line++; ctxt->input->col = 1;
        } else
            ctxt->input->col++;
        ctxt->input->cur++;
        ctxt->nbChars++;
        if (*ctxt->input->cur == 0)
            xmlParserInputGrow(ctxt->input, INPUT_CHUNK);
    }
    if ((*ctxt->input->cur == '%') && (!ctxt->html))
        xmlParserHandlePEReference(ctxt);
    if ((*ctxt->input->cur == 0) &&
        (xmlParserInputGrow(ctxt->input, INPUT_CHUNK) <= 0))
        xmlPopInput(ctxt);
    return;
encoding_error:
    /*
     * If we detect an UTF8 error that probably mean that the
     * input encoding didn't get properly advertised in the
     * declaration header. Report the error and switch the encoding
     * to ISO-Latin-1 (if you don't like this policy, just declare the
     * encoding !)
     */
    if ((ctxt == KD_NULL) || (ctxt->input == KD_NULL) ||
        (ctxt->input->end - ctxt->input->cur < 4)) {
	__xmlErrEncoding(ctxt, XML_ERR_INVALID_CHAR,
		     "Input is not proper UTF-8, indicate encoding !\n",
		     KD_NULL, KD_NULL);
    } else {
        char buffer[150];

	kdSnprintfKHR (buffer, 149, "Bytes: 0x%02X 0x%02X 0x%02X 0x%02X\n",
			ctxt->input->cur[0], ctxt->input->cur[1],
			ctxt->input->cur[2], ctxt->input->cur[3]);
	__xmlErrEncoding(ctxt, XML_ERR_INVALID_CHAR,
		     "Input is not proper UTF-8, indicate encoding !\n%s",
		     BAD_CAST buffer, KD_NULL);
    }
    ctxt->charset = XML_CHAR_ENCODING_8859_1;
    ctxt->input->cur++;
    return;
}

/**
 * xmlCurrentChar:
 * @ctxt:  the XML parser context
 * @len:  pointer to the length of the char read
 *
 * The current char value, if using UTF-8 this may actually span multiple
 * bytes in the input buffer. Implement the end of line normalization:
 * 2.11 End-of-Line Handling
 * Wherever an external parsed entity or the literal entity value
 * of an internal parsed entity contains either the literal two-character
 * sequence "#xD#xA" or a standalone literal #xD, an XML processor
 * must pass to the application the single character #xA.
 * This behavior can conveniently be produced by normalizing all
 * line breaks to #xA on input, before parsing.)
 *
 * Returns the current char value and its length
 */

int
xmlCurrentChar(xmlParserCtxtPtr ctxt, int *len) {
    if ((ctxt == KD_NULL) || (len == KD_NULL) || (ctxt->input == KD_NULL)) return(0);
    if (ctxt->instate == XML_PARSER_EOF)
	return(0);

    if ((*ctxt->input->cur >= 0x20) && (*ctxt->input->cur <= 0x7F)) {
	    *len = 1;
	    return((int) *ctxt->input->cur);
    }
    if (ctxt->charset == XML_CHAR_ENCODING_UTF8) {
	/*
	 * We are supposed to handle UTF8, check it's valid
	 * From rfc2044: encoding of the Unicode values on UTF-8:
	 *
	 * UCS-4 range (hex.)           UTF-8 octet sequence (binary)
	 * 0000 0000-0000 007F   0xxxxxxx
	 * 0000 0080-0000 07FF   110xxxxx 10xxxxxx
	 * 0000 0800-0000 FFFF   1110xxxx 10xxxxxx 10xxxxxx 
	 *
	 * Check for the 0x110000 limit too
	 */
	const unsigned char *cur = ctxt->input->cur;
	unsigned char c;
	unsigned int val;

	c = *cur;
	if (c & 0x80) {
	    if (((c & 0x40) == 0) || (c == 0xC0))
		goto encoding_error;
	    if (cur[1] == 0) {
		xmlParserInputGrow(ctxt->input, INPUT_CHUNK);
                cur = ctxt->input->cur;
            }
	    if ((cur[1] & 0xc0) != 0x80)
		goto encoding_error;
	    if ((c & 0xe0) == 0xe0) {
		if (cur[2] == 0) {
		    xmlParserInputGrow(ctxt->input, INPUT_CHUNK);
                    cur = ctxt->input->cur;
                }
		if ((cur[2] & 0xc0) != 0x80)
		    goto encoding_error;
		if ((c & 0xf0) == 0xf0) {
		    if (cur[3] == 0) {
			xmlParserInputGrow(ctxt->input, INPUT_CHUNK);
                        cur = ctxt->input->cur;
                    }
		    if (((c & 0xf8) != 0xf0) ||
			((cur[3] & 0xc0) != 0x80))
			goto encoding_error;
		    /* 4-byte code */
		    *len = 4;
		    val = (cur[0] & 0x7) << 18;
		    val |= (cur[1] & 0x3f) << 12;
		    val |= (cur[2] & 0x3f) << 6;
		    val |= cur[3] & 0x3f;
		    if (val < 0x10000)
			goto encoding_error;
		} else {
		  /* 3-byte code */
		    *len = 3;
		    val = (cur[0] & 0xf) << 12;
		    val |= (cur[1] & 0x3f) << 6;
		    val |= cur[2] & 0x3f;
		    if (val < 0x800)
			goto encoding_error;
		}
	    } else {
	      /* 2-byte code */
		*len = 2;
		val = (cur[0] & 0x1f) << 6;
		val |= cur[1] & 0x3f;
		if (val < 0x80)
		    goto encoding_error;
	    }
	    if (!IS_CHAR(val)) {
	        xmlErrEncodingInt(ctxt, XML_ERR_INVALID_CHAR,
				  "Char 0x%X out of allowed range\n", val);
	    }    
	    return(val);
	} else {
	    /* 1-byte code */
	    *len = 1;
	    if (*ctxt->input->cur == 0)
		xmlParserInputGrow(ctxt->input, INPUT_CHUNK);
	    if ((*ctxt->input->cur == 0) &&
	        (ctxt->input->end > ctxt->input->cur)) {
	        xmlErrEncodingInt(ctxt, XML_ERR_INVALID_CHAR,
				  "Char 0x0 out of allowed range\n", 0);
	    }
	    if (*ctxt->input->cur == 0xD) {
		if (ctxt->input->cur[1] == 0xA) {
		    ctxt->nbChars++;
		    ctxt->input->cur++;
		}
		return(0xA);
	    }
	    return((int) *ctxt->input->cur);
	}
    }
    /*
     * Assume it's a fixed length encoding (1) with
     * a compatible encoding for the ASCII set, since
     * XML constructs only use < 128 chars
     */
    *len = 1;
    if (*ctxt->input->cur == 0xD) {
	if (ctxt->input->cur[1] == 0xA) {
	    ctxt->nbChars++;
	    ctxt->input->cur++;
	}
	return(0xA);
    }
    return((int) *ctxt->input->cur);
encoding_error:
    /*
     * An encoding problem may arise from a truncated input buffer
     * splitting a character in the middle. In that case do not raise
     * an error but return 0 to endicate an end of stream problem
     */
    if (ctxt->input->end - ctxt->input->cur < 4) {
	*len = 0;
	return(0);
    }

    /*
     * If we detect an UTF8 error that probably mean that the
     * input encoding didn't get properly advertised in the
     * declaration header. Report the error and switch the encoding
     * to ISO-Latin-1 (if you don't like this policy, just declare the
     * encoding !)
     */
    {
        char buffer[150];

	kdSnprintfKHR (&buffer[0], 149, "Bytes: 0x%02X 0x%02X 0x%02X 0x%02X\n",
			ctxt->input->cur[0], ctxt->input->cur[1],
			ctxt->input->cur[2], ctxt->input->cur[3]);
	__xmlErrEncoding(ctxt, XML_ERR_INVALID_CHAR,
		     "Input is not proper UTF-8, indicate encoding !\n%s",
		     BAD_CAST buffer, KD_NULL);
    }
    ctxt->charset = XML_CHAR_ENCODING_8859_1; 
    *len = 1;
    return((int) *ctxt->input->cur);
}

/**
 * xmlStringCurrentChar:
 * @ctxt:  the XML parser context
 * @cur:  pointer to the beginning of the char
 * @len:  pointer to the length of the char read
 *
 * The current char value, if using UTF-8 this may actually span multiple
 * bytes in the input buffer.
 *
 * Returns the current char value and its length
 */

int
xmlStringCurrentChar(xmlParserCtxtPtr ctxt, const xmlChar * cur, int *len)
{
    if ((len == KD_NULL) || (cur == KD_NULL)) return(0);
    if ((ctxt == KD_NULL) || (ctxt->charset == XML_CHAR_ENCODING_UTF8)) {
        /*
         * We are supposed to handle UTF8, check it's valid
         * From rfc2044: encoding of the Unicode values on UTF-8:
         *
         * UCS-4 range (hex.)           UTF-8 octet sequence (binary)
         * 0000 0000-0000 007F   0xxxxxxx
         * 0000 0080-0000 07FF   110xxxxx 10xxxxxx
         * 0000 0800-0000 FFFF   1110xxxx 10xxxxxx 10xxxxxx 
         *
         * Check for the 0x110000 limit too
         */
        unsigned char c;
        unsigned int val;

        c = *cur;
        if (c & 0x80) {
            if ((cur[1] & 0xc0) != 0x80)
                goto encoding_error;
            if ((c & 0xe0) == 0xe0) {

                if ((cur[2] & 0xc0) != 0x80)
                    goto encoding_error;
                if ((c & 0xf0) == 0xf0) {
                    if (((c & 0xf8) != 0xf0) || ((cur[3] & 0xc0) != 0x80))
                        goto encoding_error;
                    /* 4-byte code */
                    *len = 4;
                    val = (cur[0] & 0x7) << 18;
                    val |= (cur[1] & 0x3f) << 12;
                    val |= (cur[2] & 0x3f) << 6;
                    val |= cur[3] & 0x3f;
                } else {
                    /* 3-byte code */
                    *len = 3;
                    val = (cur[0] & 0xf) << 12;
                    val |= (cur[1] & 0x3f) << 6;
                    val |= cur[2] & 0x3f;
                }
            } else {
                /* 2-byte code */
                *len = 2;
                val = (cur[0] & 0x1f) << 6;
                val |= cur[1] & 0x3f;
            }
            if (!IS_CHAR(val)) {
	        xmlErrEncodingInt(ctxt, XML_ERR_INVALID_CHAR,
				  "Char 0x%X out of allowed range\n", val);
            }
            return (val);
        } else {
            /* 1-byte code */
            *len = 1;
            return ((int) *cur);
        }
    }
    /*
     * Assume it's a fixed length encoding (1) with
     * a compatible encoding for the ASCII set, since
     * XML constructs only use < 128 chars
     */
    *len = 1;
    return ((int) *cur);
encoding_error:

    /*
     * An encoding problem may arise from a truncated input buffer
     * splitting a character in the middle. In that case do not raise
     * an error but return 0 to endicate an end of stream problem
     */
    if ((ctxt == KD_NULL) || (ctxt->input == KD_NULL) ||
        (ctxt->input->end - ctxt->input->cur < 4)) {
	*len = 0;
	return(0);
    }
    /*
     * If we detect an UTF8 error that probably mean that the
     * input encoding didn't get properly advertised in the
     * declaration header. Report the error and switch the encoding
     * to ISO-Latin-1 (if you don't like this policy, just declare the
     * encoding !)
     */
    {
        char buffer[150];

	kdSnprintfKHR (buffer, 149, "Bytes: 0x%02X 0x%02X 0x%02X 0x%02X\n",
			ctxt->input->cur[0], ctxt->input->cur[1],
			ctxt->input->cur[2], ctxt->input->cur[3]);
	__xmlErrEncoding(ctxt, XML_ERR_INVALID_CHAR,
		     "Input is not proper UTF-8, indicate encoding !\n%s",
		     BAD_CAST buffer, KD_NULL);
    }
    *len = 1;
    return ((int) *cur);
}

/**
 * xmlCopyCharMultiByte:
 * @out:  pointer to an array of xmlChar
 * @val:  the char value
 *
 * append the char value in the array 
 *
 * Returns the number of xmlChar written
 */
int
xmlCopyCharMultiByte(xmlChar *out, int val) {
    if (out == KD_NULL) return(0);
    /*
     * We are supposed to handle UTF8, check it's valid
     * From rfc2044: encoding of the Unicode values on UTF-8:
     *
     * UCS-4 range (hex.)           UTF-8 octet sequence (binary)
     * 0000 0000-0000 007F   0xxxxxxx
     * 0000 0080-0000 07FF   110xxxxx 10xxxxxx
     * 0000 0800-0000 FFFF   1110xxxx 10xxxxxx 10xxxxxx 
     */
    if  (val >= 0x80) {
	xmlChar *savedout = out;
	int bits;
	if (val <   0x800) { *out++= (val >>  6) | 0xC0;  bits=  0; }
	else if (val < 0x10000) { *out++= (val >> 12) | 0xE0;  bits=  6;}
	else if (val < 0x110000)  { *out++= (val >> 18) | 0xF0;  bits=  12; }
	else {
	    xmlErrEncodingInt(KD_NULL, XML_ERR_INVALID_CHAR,
		    "Internal error, xmlCopyCharMultiByte 0x%X out of bound\n",
			      val);
	    return(0);
	}
	for ( ; bits >= 0; bits-= 6)
	    *out++= ((val >> bits) & 0x3F) | 0x80 ;
	return (out - savedout);
    }
    *out = (xmlChar) val;
    return 1;
}

/**
 * xmlCopyChar:
 * @len:  Ignored, compatibility
 * @out:  pointer to an array of xmlChar
 * @val:  the char value
 *
 * append the char value in the array 
 *
 * Returns the number of xmlChar written
 */

int
xmlCopyChar(int len ATTRIBUTE_UNUSED, xmlChar *out, int val) {
    if (out == KD_NULL) return(0);
    /* the len parameter is ignored */
    if  (val >= 0x80) {
	return(xmlCopyCharMultiByte (out, val));
    }
    *out = (xmlChar) val;
    return 1;
}

/************************************************************************
 *									*
 *		Commodity functions to switch encodings			*
 *									*
 ************************************************************************/

/* defined in encoding.c, not public */
int
xmlCharEncFirstLineInt(xmlCharEncodingHandler *handler, xmlBufferPtr out,
                       xmlBufferPtr in, int len);

static int
xmlSwitchToEncodingInt(xmlParserCtxtPtr ctxt,
                       xmlCharEncodingHandlerPtr handler, int len);
static int
xmlSwitchInputEncodingInt(xmlParserCtxtPtr ctxt, xmlParserInputPtr input,
                          xmlCharEncodingHandlerPtr handler, int len);
/**
 * xmlSwitchEncoding:
 * @ctxt:  the parser context
 * @enc:  the encoding value (number)
 *
 * change the input functions when discovering the character encoding
 * of a given entity.
 *
 * Returns 0 in case of success, -1 otherwise
 */
int
xmlSwitchEncoding(xmlParserCtxtPtr ctxt, xmlCharEncoding enc)
{
    xmlCharEncodingHandlerPtr handler;
    int len = -1;

    if (ctxt == KD_NULL) return(-1);
    switch (enc) {
	case XML_CHAR_ENCODING_ERROR:
	    __xmlErrEncoding(ctxt, XML_ERR_UNKNOWN_ENCODING,
	                   "encoding unknown\n", KD_NULL, KD_NULL);
	    return(-1);
	case XML_CHAR_ENCODING_NONE:
	    /* let's assume it's UTF-8 without the XML decl */
	    ctxt->charset = XML_CHAR_ENCODING_UTF8;
	    return(0);
	case XML_CHAR_ENCODING_UTF8:
	    /* default encoding, no conversion should be needed */
	    ctxt->charset = XML_CHAR_ENCODING_UTF8;

	    /*
	     * Errata on XML-1.0 June 20 2001
	     * Specific handling of the Byte Order Mark for
	     * UTF-8
	     */
	    if ((ctxt->input != KD_NULL) &&
		(ctxt->input->cur[0] == 0xEF) &&
		(ctxt->input->cur[1] == 0xBB) &&
		(ctxt->input->cur[2] == 0xBF)) {
		ctxt->input->cur += 3;
	    }
	    return(0);
    case XML_CHAR_ENCODING_UTF16LE:
    case XML_CHAR_ENCODING_UTF16BE:
        /*The raw input characters are encoded
         *in UTF-16. As we expect this function
         *to be called after xmlCharEncInFunc, we expect
         *ctxt->input->cur to contain UTF-8 encoded characters.
         *So the raw UTF16 Byte Order Mark
         *has also been converted into
         *an UTF-8 BOM. Let's skip that BOM.
         */
        if ((ctxt->input != KD_NULL) && (ctxt->input->cur != KD_NULL) &&
            (ctxt->input->cur[0] == 0xEF) &&
            (ctxt->input->cur[1] == 0xBB) &&
            (ctxt->input->cur[2] == 0xBF)) {
            ctxt->input->cur += 3;
        }
        len = 90;
	break;
    case XML_CHAR_ENCODING_UCS2:
        len = 90;
	break;
    case XML_CHAR_ENCODING_UCS4BE:
    case XML_CHAR_ENCODING_UCS4LE:
    case XML_CHAR_ENCODING_UCS4_2143:
    case XML_CHAR_ENCODING_UCS4_3412:
        len = 180;
	break;
    case XML_CHAR_ENCODING_EBCDIC:
    case XML_CHAR_ENCODING_8859_1:
    case XML_CHAR_ENCODING_8859_2:
    case XML_CHAR_ENCODING_8859_3:
    case XML_CHAR_ENCODING_8859_4:
    case XML_CHAR_ENCODING_8859_5:
    case XML_CHAR_ENCODING_8859_6:
    case XML_CHAR_ENCODING_8859_7:
    case XML_CHAR_ENCODING_8859_8:
    case XML_CHAR_ENCODING_8859_9:
    case XML_CHAR_ENCODING_ASCII:
    case XML_CHAR_ENCODING_2022_JP:
    case XML_CHAR_ENCODING_SHIFT_JIS:
    case XML_CHAR_ENCODING_EUC_JP:
        len = 45;
	break;
    }
    handler = xmlGetCharEncodingHandler(enc);
    if (handler == KD_NULL) {
	/*
	 * Default handlers.
	 */
	switch (enc) {
	    case XML_CHAR_ENCODING_ASCII:
		/* default encoding, no conversion should be needed */
		ctxt->charset = XML_CHAR_ENCODING_UTF8;
		return(0);
	    case XML_CHAR_ENCODING_UTF16LE:
		break;
	    case XML_CHAR_ENCODING_UTF16BE:
		break;
	    case XML_CHAR_ENCODING_UCS4LE:
		__xmlErrEncoding(ctxt, XML_ERR_UNSUPPORTED_ENCODING,
			       "encoding not supported %s\n",
			       BAD_CAST "USC4 little endian", KD_NULL);
		break;
	    case XML_CHAR_ENCODING_UCS4BE:
		__xmlErrEncoding(ctxt, XML_ERR_UNSUPPORTED_ENCODING,
			       "encoding not supported %s\n",
			       BAD_CAST "USC4 big endian", KD_NULL);
		break;
	    case XML_CHAR_ENCODING_EBCDIC:
		__xmlErrEncoding(ctxt, XML_ERR_UNSUPPORTED_ENCODING,
			       "encoding not supported %s\n",
			       BAD_CAST "EBCDIC", KD_NULL);
		break;
	    case XML_CHAR_ENCODING_UCS4_2143:
		__xmlErrEncoding(ctxt, XML_ERR_UNSUPPORTED_ENCODING,
			       "encoding not supported %s\n",
			       BAD_CAST "UCS4 2143", KD_NULL);
		break;
	    case XML_CHAR_ENCODING_UCS4_3412:
		__xmlErrEncoding(ctxt, XML_ERR_UNSUPPORTED_ENCODING,
			       "encoding not supported %s\n",
			       BAD_CAST "UCS4 3412", KD_NULL);
		break;
	    case XML_CHAR_ENCODING_UCS2:
		__xmlErrEncoding(ctxt, XML_ERR_UNSUPPORTED_ENCODING,
			       "encoding not supported %s\n",
			       BAD_CAST "UCS2", KD_NULL);
		break;
	    case XML_CHAR_ENCODING_8859_1:
	    case XML_CHAR_ENCODING_8859_2:
	    case XML_CHAR_ENCODING_8859_3:
	    case XML_CHAR_ENCODING_8859_4:
	    case XML_CHAR_ENCODING_8859_5:
	    case XML_CHAR_ENCODING_8859_6:
	    case XML_CHAR_ENCODING_8859_7:
	    case XML_CHAR_ENCODING_8859_8:
	    case XML_CHAR_ENCODING_8859_9:
		/*
		 * We used to keep the internal content in the
		 * document encoding however this turns being unmaintainable
		 * So xmlGetCharEncodingHandler() will return non-null
		 * values for this now.
		 */
		if ((ctxt->inputNr == 1) &&
		    (ctxt->encoding == KD_NULL) &&
		    (ctxt->input != KD_NULL) &&
		    (ctxt->input->encoding != KD_NULL)) {
		    ctxt->encoding = xmlStrdup(ctxt->input->encoding);
		}
		ctxt->charset = enc;
		return(0);
	    case XML_CHAR_ENCODING_2022_JP:
		__xmlErrEncoding(ctxt, XML_ERR_UNSUPPORTED_ENCODING,
			       "encoding not supported %s\n",
			       BAD_CAST "ISO-2022-JP", KD_NULL);
		break;
	    case XML_CHAR_ENCODING_SHIFT_JIS:
		__xmlErrEncoding(ctxt, XML_ERR_UNSUPPORTED_ENCODING,
			       "encoding not supported %s\n",
			       BAD_CAST "Shift_JIS", KD_NULL);
		break;
	    case XML_CHAR_ENCODING_EUC_JP:
		__xmlErrEncoding(ctxt, XML_ERR_UNSUPPORTED_ENCODING,
			       "encoding not supported %s\n",
			       BAD_CAST "EUC-JP", KD_NULL);
		break;
	    default:
	        break;
	}
    }
    if (handler == KD_NULL)
	return(-1);
    ctxt->charset = XML_CHAR_ENCODING_UTF8;
    return(xmlSwitchToEncodingInt(ctxt, handler, len));
}

/**
 * xmlSwitchInputEncoding:
 * @ctxt:  the parser context
 * @input:  the input stream
 * @handler:  the encoding handler
 * @len:  the number of bytes to convert for the first line or -1
 *
 * change the input functions when discovering the character encoding
 * of a given entity.
 *
 * Returns 0 in case of success, -1 otherwise
 */
static int
xmlSwitchInputEncodingInt(xmlParserCtxtPtr ctxt, xmlParserInputPtr input,
                          xmlCharEncodingHandlerPtr handler, int len)
{
    int nbchars;

    if (handler == KD_NULL)
        return (-1);
    if (input == KD_NULL)
        return (-1);
    if (input->buf != KD_NULL) {
        if (input->buf->encoder != KD_NULL) {
            /*
             * Check in case the auto encoding detetection triggered
             * in already.
             */
            if (input->buf->encoder == handler)
                return (0);

            /*
             * "UTF-16" can be used for both LE and BE
             if ((!xmlStrncmp(BAD_CAST input->buf->encoder->name,
             BAD_CAST "UTF-16", 6)) &&
             (!xmlStrncmp(BAD_CAST handler->name,
             BAD_CAST "UTF-16", 6))) {
             return(0);
             }
             */

            /*
             * Note: this is a bit dangerous, but that's what it
             * takes to use nearly compatible signature for different
             * encodings.
             */
            xmlCharEncCloseFunc(input->buf->encoder);
            input->buf->encoder = handler;
            return (0);
        }
        input->buf->encoder = handler;

        /*
         * Is there already some content down the pipe to convert ?
         */
        if ((input->buf->buffer != KD_NULL) && (input->buf->buffer->use > 0)) {
            int processed;
	    unsigned int use;

            /*
             * Specific handling of the Byte Order Mark for 
             * UTF-16
             */
            if ((handler->name != KD_NULL) &&
                (!kdStrcmp(handler->name, "UTF-16LE") ||
                 !kdStrcmp(handler->name, "UTF-16")) &&
                (input->cur[0] == 0xFF) && (input->cur[1] == 0xFE)) {
                input->cur += 2;
            }
            if ((handler->name != KD_NULL) &&
                (!kdStrcmp(handler->name, "UTF-16BE")) &&
                (input->cur[0] == 0xFE) && (input->cur[1] == 0xFF)) {
                input->cur += 2;
            }
            /*
             * Errata on XML-1.0 June 20 2001
             * Specific handling of the Byte Order Mark for
             * UTF-8
             */
            if ((handler->name != KD_NULL) &&
                (!kdStrcmp(handler->name, "UTF-8")) &&
                (input->cur[0] == 0xEF) &&
                (input->cur[1] == 0xBB) && (input->cur[2] == 0xBF)) {
                input->cur += 3;
            }

            /*
             * Shrink the current input buffer.
             * Move it as the raw buffer and create a new input buffer
             */
            processed = input->cur - input->base;
            xmlBufferShrink(input->buf->buffer, processed);
            input->buf->raw = input->buf->buffer;
            input->buf->buffer = xmlBufferCreate();
	    input->buf->rawconsumed = processed;
	    use = input->buf->raw->use;

            if (ctxt->html) {
                /*
                 * convert as much as possible of the buffer
                 */
                nbchars = xmlCharEncInFunc(input->buf->encoder,
                                           input->buf->buffer,
                                           input->buf->raw);
            } else {
                /*
                 * convert just enough to get
                 * '<?xml version="1.0" encoding="xxx"?>'
                 * parsed with the autodetected encoding
                 * into the parser reading buffer.
                 */
                nbchars = xmlCharEncFirstLineInt(input->buf->encoder,
                                                 input->buf->buffer,
                                                 input->buf->raw,
                                                 len);
            }
            if (nbchars < 0) {
                xmlErrInternal(ctxt,
                               "switching encoding: encoder error\n",
                               KD_NULL);
                return (-1);
            }
	    input->buf->rawconsumed += use - input->buf->raw->use;
            input->base = input->cur = input->buf->buffer->content;
            input->end = &input->base[input->buf->buffer->use];

        }
        return (0);
    } else if (input->length == 0) {
	/*
	 * When parsing a static memory array one must know the
	 * size to be able to convert the buffer.
	 */
	xmlErrInternal(ctxt, "switching encoding : no input\n", KD_NULL);
	return (-1);
    }
    return (0);
}

/**
 * xmlSwitchInputEncoding:
 * @ctxt:  the parser context
 * @input:  the input stream
 * @handler:  the encoding handler
 *
 * change the input functions when discovering the character encoding
 * of a given entity.
 *
 * Returns 0 in case of success, -1 otherwise
 */
int
xmlSwitchInputEncoding(xmlParserCtxtPtr ctxt, xmlParserInputPtr input,
                          xmlCharEncodingHandlerPtr handler) {
    return(xmlSwitchInputEncodingInt(ctxt, input, handler, -1));
}

/**
 * xmlSwitchToEncodingInt:
 * @ctxt:  the parser context
 * @handler:  the encoding handler
 * @len: the lenght to convert or -1
 *
 * change the input functions when discovering the character encoding
 * of a given entity, and convert only @len bytes of the output, this
 * is needed on auto detect to allows any declared encoding later to
 * convert the actual content after the xmlDecl
 *
 * Returns 0 in case of success, -1 otherwise
 */
static int
xmlSwitchToEncodingInt(xmlParserCtxtPtr ctxt,
                       xmlCharEncodingHandlerPtr handler, int len) {
    int ret = 0;

    if (handler != KD_NULL) {
        if (ctxt->input != KD_NULL) {
	    ret = xmlSwitchInputEncodingInt(ctxt, ctxt->input, handler, len);
	} else {
	    xmlErrInternal(ctxt, "xmlSwitchToEncoding : no input\n",
	                   KD_NULL);
	    return(-1);
	}
	/*
	 * The parsing is now done in UTF8 natively
	 */
	ctxt->charset = XML_CHAR_ENCODING_UTF8;
    } else
	return(-1);
    return(ret);
}

/**
 * xmlSwitchToEncoding:
 * @ctxt:  the parser context
 * @handler:  the encoding handler
 *
 * change the input functions when discovering the character encoding
 * of a given entity.
 *
 * Returns 0 in case of success, -1 otherwise
 */
int
xmlSwitchToEncoding(xmlParserCtxtPtr ctxt, xmlCharEncodingHandlerPtr handler) 
{
    return (xmlSwitchToEncodingInt(ctxt, handler, -1));
}

/************************************************************************
 *									*
 *	Commodity functions to handle entities processing		*
 *									*
 ************************************************************************/

/**
 * xmlFreeInputStream:
 * @input:  an xmlParserInputPtr
 *
 * Free up an input stream.
 */
void
xmlFreeInputStream(xmlParserInputPtr input) {
    if (input == KD_NULL) return;

    if (input->filename != KD_NULL) xmlFree((char *) input->filename);
    if (input->directory != KD_NULL) xmlFree((char *) input->directory);
    if (input->encoding != KD_NULL) xmlFree((char *) input->encoding);
    if (input->version != KD_NULL) xmlFree((char *) input->version);
    if ((input->free != KD_NULL) && (input->base != KD_NULL))
        input->free((xmlChar *) input->base);
    if (input->buf != KD_NULL) 
        xmlFreeParserInputBuffer(input->buf);
    xmlFree(input);
}

/**
 * xmlNewInputStream:
 * @ctxt:  an XML parser context
 *
 * Create a new input stream structure
 * Returns the new input stream or KD_NULL
 */
xmlParserInputPtr
xmlNewInputStream(xmlParserCtxtPtr ctxt) {
    xmlParserInputPtr input;
    static int id = 0;

    input = (xmlParserInputPtr) xmlMalloc(sizeof(xmlParserInput));
    if (input == KD_NULL) {
        xmlErrMemory(ctxt,  "couldn't allocate a new input stream\n");
	return(KD_NULL);
    }
    kdMemset(input, 0, sizeof(xmlParserInput));
    input->line = 1;
    input->col = 1;
    input->standalone = -1;
    /*
     * we don't care about thread reentrancy unicity for a single
     * parser context (and hence thread) is sufficient.
     */
    input->id = id++;
    return(input);
}

/**
 * xmlNewIOInputStream:
 * @ctxt:  an XML parser context
 * @input:  an I/O Input
 * @enc:  the charset encoding if known
 *
 * Create a new input stream structure encapsulating the @input into
 * a stream suitable for the parser.
 *
 * Returns the new input stream or KD_NULL
 */
xmlParserInputPtr
xmlNewIOInputStream(xmlParserCtxtPtr ctxt, xmlParserInputBufferPtr input,
	            xmlCharEncoding enc) {
    xmlParserInputPtr inputStream;

    if (input == KD_NULL) return(KD_NULL);
    if (xmlParserDebugEntities)
	xmlGenericError(xmlGenericErrorContext, "new input from I/O\n");
    inputStream = xmlNewInputStream(ctxt);
    if (inputStream == KD_NULL) {
	return(KD_NULL);
    }
    inputStream->filename = KD_NULL;
    inputStream->buf = input;
    inputStream->base = inputStream->buf->buffer->content;
    inputStream->cur = inputStream->buf->buffer->content;
    inputStream->end = &inputStream->base[inputStream->buf->buffer->use];
    if (enc != XML_CHAR_ENCODING_NONE) {
        xmlSwitchEncoding(ctxt, enc);
    }

    return(inputStream);
}

/**
 * xmlNewEntityInputStream:
 * @ctxt:  an XML parser context
 * @entity:  an Entity pointer
 *
 * Create a new input stream based on an xmlEntityPtr
 *
 * Returns the new input stream or KD_NULL
 */
xmlParserInputPtr
xmlNewEntityInputStream(xmlParserCtxtPtr ctxt, xmlEntityPtr entity) {
    xmlParserInputPtr input;

    if (entity == KD_NULL) {
        xmlErrInternal(ctxt, "xmlNewEntityInputStream entity = KD_NULL\n",
	               KD_NULL);
	return(KD_NULL);
    }
    if (xmlParserDebugEntities)
	xmlGenericError(xmlGenericErrorContext,
		"new input from entity: %s\n", entity->name);
    if (entity->content == KD_NULL) {
	switch (entity->etype) {
            case XML_EXTERNAL_GENERAL_UNPARSED_ENTITY:
	        xmlErrInternal(ctxt, "Cannot parse entity %s\n",
		               entity->name);
                break;
            case XML_EXTERNAL_GENERAL_PARSED_ENTITY:
            case XML_EXTERNAL_PARAMETER_ENTITY:
		return(xmlLoadExternalEntity((char *) entity->URI,
		       (char *) entity->ExternalID, ctxt));
            case XML_INTERNAL_GENERAL_ENTITY:
	        xmlErrInternal(ctxt,
		      "Internal entity %s without content !\n",
		               entity->name);
                break;
            case XML_INTERNAL_PARAMETER_ENTITY:
	        xmlErrInternal(ctxt,
		      "Internal parameter entity %s without content !\n",
		               entity->name);
                break;
            case XML_INTERNAL_PREDEFINED_ENTITY:
	        xmlErrInternal(ctxt,
		      "Predefined entity %s without content !\n",
		               entity->name);
                break;
	}
	return(KD_NULL);
    }
    input = xmlNewInputStream(ctxt);
    if (input == KD_NULL) {
	return(KD_NULL);
    }
    if (entity->URI != KD_NULL)
	input->filename = (char *) xmlStrdup((xmlChar *) entity->URI);
    input->base = entity->content;
    input->cur = entity->content;
    input->length = entity->length;
    input->end = &entity->content[input->length];
    return(input);
}

/**
 * xmlNewStringInputStream:
 * @ctxt:  an XML parser context
 * @buffer:  an memory buffer
 *
 * Create a new input stream based on a memory buffer.
 * Returns the new input stream
 */
xmlParserInputPtr
xmlNewStringInputStream(xmlParserCtxtPtr ctxt, const xmlChar *buffer) {
    xmlParserInputPtr input;

    if (buffer == KD_NULL) {
        xmlErrInternal(ctxt, "xmlNewStringInputStream string = KD_NULL\n",
	               KD_NULL);
	return(KD_NULL);
    }
    if (xmlParserDebugEntities)
	xmlGenericError(xmlGenericErrorContext,
		"new fixed input: %.30s\n", buffer);
    input = xmlNewInputStream(ctxt);
    if (input == KD_NULL) {
        xmlErrMemory(ctxt,  "couldn't allocate a new input stream\n");
	return(KD_NULL);
    }
    input->base = buffer;
    input->cur = buffer;
    input->length = xmlStrlen(buffer);
    input->end = &buffer[input->length];
    return(input);
}

/**
 * xmlNewInputFromFile:
 * @ctxt:  an XML parser context
 * @filename:  the filename to use as entity
 *
 * Create a new input stream based on a file or an URL.
 *
 * Returns the new input stream or KD_NULL in case of error
 */
xmlParserInputPtr
xmlNewInputFromFile(xmlParserCtxtPtr ctxt, const char *filename) {
    xmlParserInputBufferPtr buf;
    xmlParserInputPtr inputStream;
    char *directory = KD_NULL;
    xmlChar *URI = KD_NULL;

    if (xmlParserDebugEntities)
	xmlGenericError(xmlGenericErrorContext,
		"new input from file: %s\n", filename);
    if (ctxt == KD_NULL) return(KD_NULL);
    buf = xmlParserInputBufferCreateFilename(filename, XML_CHAR_ENCODING_NONE);
    if (buf == KD_NULL) {
	if (filename == KD_NULL)
	    __xmlLoaderErr(ctxt,
	                   "failed to load external entity: KD_NULL filename \n",
			   KD_NULL);
	else
	    __xmlLoaderErr(ctxt, "failed to load external entity \"%s\"\n",
			   (const char *) filename);
	return(KD_NULL);
    }

    inputStream = xmlNewInputStream(ctxt);
    if (inputStream == KD_NULL)
	return(KD_NULL);

    inputStream->buf = buf;
    inputStream = xmlCheckHTTPInput(ctxt, inputStream);
    if (inputStream == KD_NULL)
        return(KD_NULL);
    
    if (inputStream->filename == KD_NULL)
	URI = xmlStrdup((xmlChar *) filename);
    else
	URI = xmlStrdup((xmlChar *) inputStream->filename);
    directory = xmlParserGetDirectory((const char *) URI);
    if (inputStream->filename != KD_NULL) xmlFree((char *)inputStream->filename);
    inputStream->filename = (char *) xmlCanonicPath((const xmlChar *) URI);
    if (URI != KD_NULL) xmlFree((char *) URI);
    inputStream->directory = directory;

    inputStream->base = inputStream->buf->buffer->content;
    inputStream->cur = inputStream->buf->buffer->content;
    inputStream->end = &inputStream->base[inputStream->buf->buffer->use];
    if ((ctxt->directory == KD_NULL) && (directory != KD_NULL))
        ctxt->directory = (char *) xmlStrdup((const xmlChar *) directory);
    return(inputStream);
}

/************************************************************************
 *									*
 *		Commodity functions to handle parser contexts		*
 *									*
 ************************************************************************/

/**
 * xmlInitParserCtxt:
 * @ctxt:  an XML parser context
 *
 * Initialize a parser context
 *
 * Returns 0 in case of success and -1 in case of error
 */

int
xmlInitParserCtxt(xmlParserCtxtPtr ctxt)
{
    xmlParserInputPtr input;

    if(ctxt==KD_NULL) {
        xmlErrInternal(KD_NULL, "Got KD_NULL parser context\n", KD_NULL);
        return(-1);
    }

    xmlDefaultSAXHandlerInit();

    if (ctxt->dict == KD_NULL)
	ctxt->dict = xmlDictCreate();
    if (ctxt->dict == KD_NULL) {
        xmlErrMemory(KD_NULL, "cannot initialize parser context\n");
	return(-1);
    }
    if (ctxt->sax == KD_NULL)
	ctxt->sax = (xmlSAXHandler *) xmlMalloc(sizeof(xmlSAXHandler));
    if (ctxt->sax == KD_NULL) {
        xmlErrMemory(KD_NULL, "cannot initialize parser context\n");
	return(-1);
    }
    else
        xmlSAXVersion(ctxt->sax, 2);

    ctxt->maxatts = 0;
    ctxt->atts = KD_NULL;
    /* Allocate the Input stack */
    if (ctxt->inputTab == KD_NULL) {
	ctxt->inputTab = (xmlParserInputPtr *)
		    xmlMalloc(5 * sizeof(xmlParserInputPtr));
	ctxt->inputMax = 5;
    }
    if (ctxt->inputTab == KD_NULL) {
        xmlErrMemory(KD_NULL, "cannot initialize parser context\n");
	ctxt->inputNr = 0;
	ctxt->inputMax = 0;
	ctxt->input = KD_NULL;
	return(-1);
    }
    while ((input = inputPop(ctxt)) != KD_NULL) { /* Non consuming */
        xmlFreeInputStream(input);
    }
    ctxt->inputNr = 0;
    ctxt->input = KD_NULL;

    ctxt->version = KD_NULL;
    ctxt->encoding = KD_NULL;
    ctxt->standalone = -1;
    ctxt->hasExternalSubset = 0;
    ctxt->hasPErefs = 0;
    ctxt->html = 0;
    ctxt->external = 0;
    ctxt->instate = XML_PARSER_START;
    ctxt->token = 0;
    ctxt->directory = KD_NULL;

    /* Allocate the Node stack */
    if (ctxt->nodeTab == KD_NULL) {
	ctxt->nodeTab = (xmlNodePtr *) xmlMalloc(10 * sizeof(xmlNodePtr));
	ctxt->nodeMax = 10;
    }
    if (ctxt->nodeTab == KD_NULL) {
        xmlErrMemory(KD_NULL, "cannot initialize parser context\n");
	ctxt->nodeNr = 0;
	ctxt->nodeMax = 0;
	ctxt->node = KD_NULL;
	ctxt->inputNr = 0;
	ctxt->inputMax = 0;
	ctxt->input = KD_NULL;
	return(-1);
    }
    ctxt->nodeNr = 0;
    ctxt->node = KD_NULL;

    /* Allocate the Name stack */
    if (ctxt->nameTab == KD_NULL) {
	ctxt->nameTab = (const xmlChar **) xmlMalloc(10 * sizeof(xmlChar *));
	ctxt->nameMax = 10;
    }
    if (ctxt->nameTab == KD_NULL) {
        xmlErrMemory(KD_NULL, "cannot initialize parser context\n");
	ctxt->nodeNr = 0;
	ctxt->nodeMax = 0;
	ctxt->node = KD_NULL;
	ctxt->inputNr = 0;
	ctxt->inputMax = 0;
	ctxt->input = KD_NULL;
	ctxt->nameNr = 0;
	ctxt->nameMax = 0;
	ctxt->name = KD_NULL;
	return(-1);
    }
    ctxt->nameNr = 0;
    ctxt->name = KD_NULL;

    /* Allocate the space stack */
    if (ctxt->spaceTab == KD_NULL) {
	ctxt->spaceTab = (int *) xmlMalloc(10 * sizeof(int));
	ctxt->spaceMax = 10;
    }
    if (ctxt->spaceTab == KD_NULL) {
        xmlErrMemory(KD_NULL, "cannot initialize parser context\n");
	ctxt->nodeNr = 0;
	ctxt->nodeMax = 0;
	ctxt->node = KD_NULL;
	ctxt->inputNr = 0;
	ctxt->inputMax = 0;
	ctxt->input = KD_NULL;
	ctxt->nameNr = 0;
	ctxt->nameMax = 0;
	ctxt->name = KD_NULL;
	ctxt->spaceNr = 0;
	ctxt->spaceMax = 0;
	ctxt->space = KD_NULL;
	return(-1);
    }
    ctxt->spaceNr = 1;
    ctxt->spaceMax = 10;
    ctxt->spaceTab[0] = -1;
    ctxt->space = &ctxt->spaceTab[0];
    ctxt->userData = ctxt;
    ctxt->myDoc = KD_NULL;
    ctxt->wellFormed = 1;
    ctxt->nsWellFormed = 1;
    ctxt->valid = 1;
    ctxt->loadsubset = xmlLoadExtDtdDefaultValue;
    ctxt->validate = xmlDoValidityCheckingDefaultValue;
    ctxt->pedantic = xmlPedanticParserDefaultValue;
    ctxt->linenumbers = xmlLineNumbersDefaultValue;
    ctxt->keepBlanks = xmlKeepBlanksDefaultValue;
    if (ctxt->keepBlanks == 0)
	ctxt->sax->ignorableWhitespace = xmlSAX2IgnorableWhitespace;

    ctxt->vctxt.finishDtd = XML_CTXT_FINISH_DTD_0;
    ctxt->vctxt.userData = ctxt;
    ctxt->vctxt.error = xmlParserValidityError;
    ctxt->vctxt.warning = xmlParserValidityWarning;
    if (ctxt->validate) {
	if (xmlGetWarningsDefaultValue == 0)
	    ctxt->vctxt.warning = KD_NULL;
	else
	    ctxt->vctxt.warning = xmlParserValidityWarning;
	ctxt->vctxt.nodeMax = 0;
    }
    ctxt->replaceEntities = xmlSubstituteEntitiesDefaultValue;
    ctxt->record_info = 0;
    ctxt->nbChars = 0;
    ctxt->checkIndex = 0;
    ctxt->inSubset = 0;
    ctxt->errNo = XML_ERR_OK;
    ctxt->depth = 0;
    ctxt->charset = XML_CHAR_ENCODING_UTF8;
    ctxt->catalogs = KD_NULL;
    ctxt->nbentities = 0;
    xmlInitNodeInfoSeq(&ctxt->node_seq);
    return(0);
}

/**
 * xmlFreeParserCtxt:
 * @ctxt:  an XML parser context
 *
 * Free all the memory used by a parser context. However the parsed
 * document in ctxt->myDoc is not freed.
 */

void
xmlFreeParserCtxt(xmlParserCtxtPtr ctxt)
{
    xmlParserInputPtr input;

    if (ctxt == KD_NULL) return;

    while ((input = inputPop(ctxt)) != KD_NULL) { /* Non consuming */
        xmlFreeInputStream(input);
    }
    if (ctxt->spaceTab != KD_NULL) xmlFree(ctxt->spaceTab);
    if (ctxt->nameTab != KD_NULL) xmlFree((xmlChar * *)ctxt->nameTab);
    if (ctxt->nodeTab != KD_NULL) xmlFree(ctxt->nodeTab);
    if (ctxt->nodeInfoTab != KD_NULL) xmlFree(ctxt->nodeInfoTab);
    if (ctxt->inputTab != KD_NULL) xmlFree(ctxt->inputTab);
    if (ctxt->version != KD_NULL) xmlFree((char *) ctxt->version);
    if (ctxt->encoding != KD_NULL) xmlFree((char *) ctxt->encoding);
    if (ctxt->extSubURI != KD_NULL) xmlFree((char *) ctxt->extSubURI);
    if (ctxt->extSubSystem != KD_NULL) xmlFree((char *) ctxt->extSubSystem);
#ifdef LIBXML_SAX1_ENABLED
    if ((ctxt->sax != KD_NULL) &&
        (ctxt->sax != (xmlSAXHandlerPtr) &xmlDefaultSAXHandler))
#else
    if (ctxt->sax != KD_NULL)
#endif /* LIBXML_SAX1_ENABLED */
        xmlFree(ctxt->sax);
    if (ctxt->directory != KD_NULL) xmlFree((char *) ctxt->directory);
    if (ctxt->vctxt.nodeTab != KD_NULL) xmlFree(ctxt->vctxt.nodeTab);
    if (ctxt->atts != KD_NULL) xmlFree((xmlChar * *)ctxt->atts);
    if (ctxt->dict != KD_NULL) xmlDictFree(ctxt->dict);
    if (ctxt->nsTab != KD_NULL) xmlFree((char *) ctxt->nsTab);
    if (ctxt->pushTab != KD_NULL) xmlFree(ctxt->pushTab);
    if (ctxt->attallocs != KD_NULL) xmlFree(ctxt->attallocs);
    if (ctxt->attsDefault != KD_NULL) 
        xmlHashFree(ctxt->attsDefault, (xmlHashDeallocator) xmlFree);
    if (ctxt->attsSpecial != KD_NULL)
        xmlHashFree(ctxt->attsSpecial, KD_NULL);
    if (ctxt->freeElems != KD_NULL) {
        xmlNodePtr cur, next;

	cur = ctxt->freeElems;
	while (cur != KD_NULL) {
	    next = cur->next;
	    xmlFree(cur);
	    cur = next;
	}
    }
    if (ctxt->freeAttrs != KD_NULL) {
        xmlAttrPtr cur, next;

	cur = ctxt->freeAttrs;
	while (cur != KD_NULL) {
	    next = cur->next;
	    xmlFree(cur);
	    cur = next;
	}
    }
    /*
     * cleanup the error strings
     */
    if (ctxt->lastError.message != KD_NULL)
        xmlFree(ctxt->lastError.message);
    if (ctxt->lastError.file != KD_NULL)
        xmlFree(ctxt->lastError.file);
    if (ctxt->lastError.str1 != KD_NULL)
        xmlFree(ctxt->lastError.str1);
    if (ctxt->lastError.str2 != KD_NULL)
        xmlFree(ctxt->lastError.str2);
    if (ctxt->lastError.str3 != KD_NULL)
        xmlFree(ctxt->lastError.str3);

#ifdef LIBXML_CATALOG_ENABLED
    if (ctxt->catalogs != KD_NULL)
	xmlCatalogFreeLocal(ctxt->catalogs);
#endif
    xmlFree(ctxt);
}

/**
 * xmlNewParserCtxt:
 *
 * Allocate and initialize a new parser context.
 *
 * Returns the xmlParserCtxtPtr or KD_NULL
 */

xmlParserCtxtPtr
xmlNewParserCtxt(void)
{
    xmlParserCtxtPtr ctxt;

    ctxt = (xmlParserCtxtPtr) xmlMalloc(sizeof(xmlParserCtxt));
    if (ctxt == KD_NULL) {
	xmlErrMemory(KD_NULL, "cannot allocate parser context\n");
	return(KD_NULL);
    }
    kdMemset(ctxt, 0, sizeof(xmlParserCtxt));
    if (xmlInitParserCtxt(ctxt) < 0) {
        xmlFreeParserCtxt(ctxt);
	return(KD_NULL);
    }
    return(ctxt);
}

/************************************************************************
 *									*
 *		Handling of node informations				*
 *									*
 ************************************************************************/

/**
 * xmlClearParserCtxt:
 * @ctxt:  an XML parser context
 *
 * Clear (release owned resources) and reinitialize a parser context
 */

void
xmlClearParserCtxt(xmlParserCtxtPtr ctxt)
{
  if (ctxt==KD_NULL)
    return;
  xmlClearNodeInfoSeq(&ctxt->node_seq);
  xmlCtxtReset(ctxt);
}


/**
 * xmlParserFindNodeInfo:
 * @ctx:  an XML parser context
 * @node:  an XML node within the tree
 *
 * Find the parser node info struct for a given node
 * 
 * Returns an xmlParserNodeInfo block pointer or KD_NULL
 */
const xmlParserNodeInfo *
xmlParserFindNodeInfo(const xmlParserCtxtPtr ctx, const xmlNodePtr node)
{
    unsigned long pos;

    if ((ctx == KD_NULL) || (node == KD_NULL))
        return (KD_NULL);
    /* Find position where node should be at */
    pos = xmlParserFindNodeInfoIndex(&ctx->node_seq, node);
    if (pos < ctx->node_seq.length
        && ctx->node_seq.buffer[pos].node == node)
        return &ctx->node_seq.buffer[pos];
    else
        return KD_NULL;
}


/**
 * xmlInitNodeInfoSeq:
 * @seq:  a node info sequence pointer
 *
 * -- Initialize (set to initial state) node info sequence
 */
void
xmlInitNodeInfoSeq(xmlParserNodeInfoSeqPtr seq)
{
    if (seq == KD_NULL)
        return;
    seq->length = 0;
    seq->maximum = 0;
    seq->buffer = KD_NULL;
}

/**
 * xmlClearNodeInfoSeq:
 * @seq:  a node info sequence pointer
 *
 * -- Clear (release memory and reinitialize) node
 *   info sequence
 */
void
xmlClearNodeInfoSeq(xmlParserNodeInfoSeqPtr seq)
{
    if (seq == KD_NULL)
        return;
    if (seq->buffer != KD_NULL)
        xmlFree(seq->buffer);
    xmlInitNodeInfoSeq(seq);
}

/**
 * xmlParserFindNodeInfoIndex:
 * @seq:  a node info sequence pointer
 * @node:  an XML node pointer
 *
 * 
 * xmlParserFindNodeInfoIndex : Find the index that the info record for
 *   the given node is or should be at in a sorted sequence
 *
 * Returns a long indicating the position of the record
 */
unsigned long
xmlParserFindNodeInfoIndex(const xmlParserNodeInfoSeqPtr seq,
                           const xmlNodePtr node)
{
    unsigned long upper, lower, middle;
    int found = 0;

    if ((seq == KD_NULL) || (node == KD_NULL))
        return ((unsigned long) -1);

    /* Do a binary search for the key */
    lower = 1;
    upper = seq->length;
    middle = 0;
    while (lower <= upper && !found) {
        middle = lower + (upper - lower) / 2;
        if (node == seq->buffer[middle - 1].node)
            found = 1;
        else if (node < seq->buffer[middle - 1].node)
            upper = middle - 1;
        else
            lower = middle + 1;
    }

    /* Return position */
    if (middle == 0 || seq->buffer[middle - 1].node < node)
        return middle;
    else
        return middle - 1;
}


/**
 * xmlParserAddNodeInfo:
 * @ctxt:  an XML parser context
 * @info:  a node info sequence pointer
 *
 * Insert node info record into the sorted sequence
 */
void
xmlParserAddNodeInfo(xmlParserCtxtPtr ctxt,
                     const xmlParserNodeInfoPtr info)
{
    unsigned long pos;

    if ((ctxt == KD_NULL) || (info == KD_NULL)) return;

    /* Find pos and check to see if node is already in the sequence */
    pos = xmlParserFindNodeInfoIndex(&ctxt->node_seq, (xmlNodePtr)
                                     info->node);

    if ((pos < ctxt->node_seq.length) && 
        (ctxt->node_seq.buffer != KD_NULL) &&
        (ctxt->node_seq.buffer[pos].node == info->node)) {
        ctxt->node_seq.buffer[pos] = *info;
    }

    /* Otherwise, we need to add new node to buffer */
    else {
        if (ctxt->node_seq.length + 1 > ctxt->node_seq.maximum) {
            xmlParserNodeInfo *tmp_buffer;
            unsigned int byte_size;

            if (ctxt->node_seq.maximum == 0)
                ctxt->node_seq.maximum = 2;
            byte_size = (sizeof(*ctxt->node_seq.buffer) *
			(2 * ctxt->node_seq.maximum));

            if (ctxt->node_seq.buffer == KD_NULL)
                tmp_buffer = (xmlParserNodeInfo *) xmlMalloc(byte_size);
            else
                tmp_buffer =
                    (xmlParserNodeInfo *) xmlRealloc(ctxt->node_seq.buffer,
                                                     byte_size);

            if (tmp_buffer == KD_NULL) {
		xmlErrMemory(ctxt, "failed to allocate buffer\n");
                return;
            }
            ctxt->node_seq.buffer = tmp_buffer;
            ctxt->node_seq.maximum *= 2;
        }

        /* If position is not at end, move elements out of the way */
        if (pos != ctxt->node_seq.length) {
            unsigned long i;

            for (i = ctxt->node_seq.length; i > pos; i--)
                ctxt->node_seq.buffer[i] = ctxt->node_seq.buffer[i - 1];
        }

        /* Copy element and increase length */
        ctxt->node_seq.buffer[pos] = *info;
        ctxt->node_seq.length++;
    }
}

/************************************************************************
 *									*
 *		Defaults settings					*
 *									*
 ************************************************************************/
/**
 * xmlPedanticParserDefault:
 * @val:  int 0 or 1 
 *
 * Set and return the previous value for enabling pedantic warnings.
 *
 * Returns the last value for 0 for no substitution, 1 for substitution.
 */

int
xmlPedanticParserDefault(int val) {
    int old = xmlPedanticParserDefaultValue;

    xmlPedanticParserDefaultValue = val;
    return(old);
}

/**
 * xmlLineNumbersDefault:
 * @val:  int 0 or 1 
 *
 * Set and return the previous value for enabling line numbers in elements
 * contents. This may break on old application and is turned off by default.
 *
 * Returns the last value for 0 for no substitution, 1 for substitution.
 */

int
xmlLineNumbersDefault(int val) {
    int old = xmlLineNumbersDefaultValue;

    xmlLineNumbersDefaultValue = val;
    return(old);
}

/**
 * xmlSubstituteEntitiesDefault:
 * @val:  int 0 or 1 
 *
 * Set and return the previous value for default entity support.
 * Initially the parser always keep entity references instead of substituting
 * entity values in the output. This function has to be used to change the
 * default parser behavior
 * SAX::substituteEntities() has to be used for changing that on a file by
 * file basis.
 *
 * Returns the last value for 0 for no substitution, 1 for substitution.
 */

int
xmlSubstituteEntitiesDefault(int val) {
    int old = xmlSubstituteEntitiesDefaultValue;

    xmlSubstituteEntitiesDefaultValue = val;
    return(old);
}

/**
 * xmlKeepBlanksDefault:
 * @val:  int 0 or 1 
 *
 * Set and return the previous value for default blanks text nodes support.
 * The 1.x version of the parser used an heuristic to try to detect
 * ignorable white spaces. As a result the SAX callback was generating
 * xmlSAX2IgnorableWhitespace() callbacks instead of characters() one, and when
 * using the DOM output text nodes containing those blanks were not generated.
 * The 2.x and later version will switch to the XML standard way and
 * ignorableWhitespace() are only generated when running the parser in
 * validating mode and when the current element doesn't allow CDATA or
 * mixed content.
 * This function is provided as a way to force the standard behavior 
 * on 1.X libs and to switch back to the old mode for compatibility when
 * running 1.X client code on 2.X . Upgrade of 1.X code should be done
 * by using xmlIsBlankNode() commodity function to detect the "empty"
 * nodes generated.
 * This value also affect autogeneration of indentation when saving code
 * if blanks sections are kept, indentation is not generated.
 *
 * Returns the last value for 0 for no substitution, 1 for substitution.
 */

int
xmlKeepBlanksDefault(int val) {
    int old = xmlKeepBlanksDefaultValue;

    xmlKeepBlanksDefaultValue = val;
    if (!val) xmlIndentTreeOutput = 1;
    return(old);
}

#define bottom_parserInternals
#include "elfgcchack.h"
