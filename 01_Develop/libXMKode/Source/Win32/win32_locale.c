/* --------------------------------------------------------------------------
 *
 *      File            win32_locale.c
 *      Description     Locale specific functions
 *      Author          Y.H Mun
 * 
 * --------------------------------------------------------------------------
 *      
 *      Copyright (C) 2010-2012 XMSoft. All rights reserved.
 * 
 *      Contact Email: xmsoft77@gmail.com 
 * 
 * --------------------------------------------------------------------------
 * 
 *      This library is free software; you can redistribute it and/or
 *      modify it under the terms of the GNU Lesser General Public
 *      License as published by the Free Software Foundation; either
 *      version 2 of the License, or (at your option) any later version.
 * 
 *      This library is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *      Lesser General Public License for more details.
 * 
 *      You should have received a copy of the GNU Lesser General Public
 *      License along with this library in the file COPYING.LIB;
 *      if not, write to the Free Software Foundation, Inc.,
 *      59 Temple Place - Suite 330, Boston, MA 02111-1307, USA
 *
 * -------------------------------------------------------------------------- */

#include "../kd_library.h"

typedef struct XMLocale
{
	TCHAR*	    tcode;
	char*       info;
} XMLocale;

static struct XMLocale l_tables[] =
{
	_T("0436"),	"af_AF",					//	Afrikaans	South Africa				1252	AFK	
	_T("041c"),	"sq_AL",					//	Albanian	Albania						1250	SQI
	_T("1401"),	"ar_DZ",					//	Arabic		Algeria						1256	ARG
	_T("3c01"),	"ar_BH",					//	Arabic		Bahrain						1256	ARH
	_T("0c01"),	"ar_EG",					//	Arabic		Egypt						1256	ARE
	_T("0801"),	"ar_IQ",					//	Arabic		Iraq						1256	ARI
	_T("2c01"),	"ar_JO",					//	Arabic		Jordan						1256	ARJ
	_T("3401"),	"ar_KW",					//	Arabic		Kuwait						1256	ARK
	_T("3001"),	"ar_LB",					//	Arabic		Lebanon						1256	ARB
	_T("1001"),	"ar_LR",					//	Arabic		Libya						1256	ARL
	_T("1801"),	"ar_MA",					//	Arabic		Morocco						1256	ARM
	_T("2001"),	"ar_OM",					//	Arabic		Oman						1256	ARO
	_T("4001"),	"ar_QA",					//	Arabic		Qatar						1256	ARQ
	_T("0401"),	"ar_SA",					//	Arabic		Saudi Arabia				1256	ARA
	_T("2801"),	"ar_SY",					//	Arabic		Syria						1256	ARS
	_T("1c01"),	"ar_TN",					//	Arabic		Tunisia						1256	ART
	_T("3801"),	"ar_AE",					//	Arabic		U.A.E.						1256	ARU
	_T("2401"),	"ar_YE",					//	Arabic		Yemen						1256	ARY
	_T("042b"),	"hy_AM",					//	Armenian	Armenia						Unicode only	HYE
	_T("082c"),	"az_AZ",					//	Azeri		Azerbaijan (Cyrillic)		1251	AZE
	_T("042c"),	"az_AZ",					//	Azeri		Azerbaijan (Latin)			1254	AZE
	_T("042d"),	"eu_ES",					//	Basque		Spain						1252	EUQ
	_T("0423"),	"be_BY",					//	Belarusian	Belarus						1251	BEL
	_T("0402"),	"bg_BG",					//	Bulgarian	Bulgaria					1251	BGR
	_T("0403"),	"ca_ES",					//	Catalan		Spain						1252	CAT
	_T("0c04"),	"zh_HK",					//	Chinese		Hong Kong SAR				 950	ZHH
	_T("1404"),	"zh_MO",					//	Chinese		Macao SAR					 950	ZHM
	_T("0804"),	"zh_PR",					//	Chinese		PRC							 936	CHS
	_T("1004"),	"zh_SG",					//	Chinese		Singapore					 936	ZHI
	_T("0404"),	"zh_TW",					//	Chinese		Taiwan						 950	CHT
	_T("041a"),	"hr_HR",					//	Croatian	Croatia						1250	HRV
	_T("0405"),	"cs_CZ",					//	Czech		Czech Republic				1250	CSY
	_T("0406"),	"da_DK",					//	Danish		Denmark						1252	DAN
	_T("0465"),	"dv_MV",					//	Divehi		Maldives					Unicode only	DIV
	_T("0813"),	"nl_BE",					//	Dutch		Belgium						1252	NLB
	_T("0413"),	"nl_NL",					//	Dutch		Netherlands					1252	NLD
	_T("0c09"),	"en_AU",					//	English		Australia					1252	ENA
	_T("2809"),	"en_BZ",					//	English		Belize						1252	ENL
	_T("1009"),	"en_CA",					//	English		Canada						1252	ENC
	_T("2409"),	"en_CB",					//	English		Caribbean					1252	ENB
	_T("1809"),	"en_IE",					//	English		Ireland						1252	ENI
	_T("2009"),	"en_JM",					//	English		Jamaica						1252	ENJ
	_T("1409"),	"en_NZ",					//	English		New Zealand					1252	ENZ
	_T("3409"),	"en_PH",					//	English		Philippines					1252	ENP
	_T("1c09"),	"en_ZA",					//	English		South Africa				1252	ENS
	_T("2c09"),	"en_TT",					//	English		Trinidad					1252	ENT
	_T("0809"),	"en_GB",					//	English		United Kingdom				1252	ENG
	_T("0409"),	"en_US",					//	English		United States				1252	USA
	_T("3009"),	"en_ZW",					//	English		Zimbabwe					1252	ENW
	_T("0425"),	"en_EE",					//	Estonian	Estonia						1257	ETI
	_T("0438"),	"fo_FO",					//	Faroese		Faroe Islands				1252	FOS
	_T("0429"),	"fa_IR",					//	Farsi		Iran						1256	FAR
	_T("040b"),	"fi_FI",					//	Finnish		Finland						1252	FIN
	_T("080c"),	"fr_BE",					//	French		Belgium						1252	FRB
	_T("0c0c"),	"fr_CA",					//	French		Canada						1252	FRC
	_T("040c"),	"fr_FR",					//	French		France						1252	FRA
	_T("140c"),	"fr_LU",					//	French		Luxembourg					1252	FRL
	_T("180c"),	"fr_MC",					//	French		Monaco						1252	FRM
	_T("100c"),	"fr_CH",					//	French		Switzerland					1252	FRS
	_T("042f"),	"mk_MK",					//	Macedonian (FYROM)	FYRO Macedonia		1251	MKI
	_T("0456"),	"gl_ES",					//	Galician	Spain						1252	GLC
	_T("0437"),	"ka_KA",					//	Georgian	Georgia						Unicode only	KAT
	_T("0c07"),	"de_AT",					//	German		Austria						1252	DEA
	_T("0407"),	"de_DE",					//	German		Germany						1252	DEU
	_T("1407"),	"de_LI",					//	German		Liechtenstein				1252	DEC
	_T("1007"),	"de_LU",					//	German		Luxembourg					1252	DEL
	_T("0807"),	"de_CH",					//	German		Switzerland					1252	DES
	_T("0408"),	"el_GR",					//	Greek		Greece						1253	ELL
	_T("0447"),	"gu_IN",					//	Gujarati	India 						Unicode only	GUJ
	_T("040d"),	"he_IL",					//	Hebrew		Israel						1255	HEB
	_T("0439"),	"hi_IN",					//	Hindi		India						Unicode only	HIN
	_T("040e"),	"hu_HU",					//	Hungarian	Hungary						1250	HUN
	_T("040f"),	"is_IS",					//	Icelandic	Iceland						1252	ISL
	_T("0421"),	"id_ID",					//	Indonesian	Indonesia (Bahasa)			1252	IND
	_T("0410"),	"it_IT",					//	Italian		Italy						1252	ITA
	_T("0810"),	"it_CH",					//	Italian		Switzerland					1252	ITS
	_T("0411"),	"ja_JP",					//	Japanese	Japan						 932	JPN
	_T("044b"),	"kn_IN",					//	Kannada		India (Kannada script)		Unicode only	KAN
	_T("043f"),	"kk_KZ",					//	Kazakh		Kazakstan					1251	KKZ
	_T("0457"),	"ka_IN",					//	Konkani		India						Unicode only	KNK
	_T("0412"),	"ko_KR",					//	Korean		Korea						 949	KOR
	_T("0440"),	"kg_KG",					//	Kyrgyz		Kyrgyzstan					1251	KYR
	_T("0426"),	"lv_LV",					//	Latvian		Latvia						1257	LVI
	_T("0427"),	"lt_LT",					//	Lithuanian	Lithuania					1257	LTH
	_T("083e"),	"ms_BN",					//	Malay		Brunei Darussalam			1252	MSB
	_T("043e"),	"ms_MY",					//	Malay		Malaysia					1252	MSL
	_T("044e"),	"mr_IN",					//	Marathi		India						Unicode only	MAR
	_T("0450"),	"mn_MN",					//	Mongolian (Cyrillic)	Mongolia		1251	MON
	_T("0414"),	"no_NO",					//	Norwegian	Norway (Bokmål)				1252	NOR
	_T("0814"),	"no_NO",					//	Norwegian	Norway (Nynorsk)			1252	NON
	_T("0415"),	"pl_PL",					//	Polish		Poland						1250	PLK
	_T("0416"),	"pt_BR",					//	Portuguese	Brazil						1252	PTB
	_T("0816"),	"pt_PT",					//	Portuguese	Portugal					1252	PTG
	_T("0446"),	"pu_IN",					//	Punjabi		India (Gurmukhi script)		Unicode only	PAN
	_T("0418"),	"ro_RO",					//	Romanian	Romania						1250	ROM
	_T("0419"),	"ru_RU",					//	Russian		Russia						1251	RUS
	_T("044f"),	"sa_IN",					//	Sanskrit	India						Unicode only	SAN
	_T("0c1a"),	"sr_RS",					//	Serbian		Serbia (Cyrillic)			1251	SRB
	_T("081a"),	"sr_RS",					//	Serbian		Serbia (Latin)				1250	SRL
	_T("041b"),	"sk_SK",					//	Slovak		Slovakia					1250	SKY
	_T("0424"),	"sl_SI",					//	Slovenian	Slovenia					1250	SLV
	_T("2c0a"),	"es_AR",					//	Spanish		Argentina					1252	ESS
	_T("400a"),	"es_BO",					//	Spanish		Bolivia						1252	ESB
	_T("340a"),	"es_CL",					//	Spanish		Chile						1252	ESL
	_T("240a"),	"es_CO",					//	Spanish		Colombia					1252	ESO
	_T("140a"),	"es_CR",					//	Spanish		Costa Rica					1252	ESC
	_T("1c0a"),	"es_DO",					//	Spanish		Dominican Republic			1252	ESD
	_T("300a"),	"es_EC",					//	Spanish		Ecuador						1252	ESF
	_T("440a"),	"es_SV",					//	Spanish		El Salvador					1252	ESE
	_T("100a"),	"es_GT",					//	Spanish		Guatemala					1252	ESG
	_T("480a"),	"es_HN",					//	Spanish		Honduras					1252	ESH
	_T("080a"),	"es_MX",					//	Spanish		Mexico						1252	ESM
	_T("4c0a"),	"es_NI",					//	Spanish		Nicaragua					1252	ESI
	_T("180a"),	"es_PA",					//	Spanish		Panama						1252	ESA
	_T("3c0a"),	"es_PY",					//	Spanish		Paraguay					1252	ESZ
	_T("280a"),	"es_PE",					//	Spanish		Peru						1252	ESR
	_T("500a"),	"es_PR",					//	Spanish		Puerto Rico					1252	ESU
	_T("040a"),	"es_ES",					//	Spanish		Spain (Traditional sort)	1252	ESP
	_T("0c0a"),	"es_ES",					//	Spanish		Spain (International sort)	1252	ESN
	_T("380a"),	"es_UY",					//	Spanish		Uruguay						1252	ESY
	_T("200a"),	"es_VE",					//	Spanish		Venezuela					1252	ESV
	_T("0441"),	"sw_KE",					//	Swahili		Kenya						1252	SWK
	_T("081d"),	"sv_FI",					//	Swedish		Finland						1252	SVF
	_T("041d"),	"sv_SE",					//	Swedish		Sweden						1252	SVE
	_T("045a"),	"sy_SY",					//	Syriac		Syria						Unicode only	SYR
	_T("0449"),	"ta_IN",					//	Tamil		India						Unicode only	TAM
	_T("0444"),	"tt_TT",					//	Tatar		Tatarstan					1251	TTT
	_T("044a"),	"te_IN",					//	Telugu		India (Telugu script)		Unicode only	TEL
	_T("041e"),	"th_TH",					//	Thai		Thailand					 874	THA
	_T("041f"),	"tr_TR",					//	Turkish		Turkey						1254	TRK
	_T("0422"),	"uk_UA",					//	Ukrainian	Ukraine						1251	UKR
	_T("0420"),	"ur_PK",					//	Urdu		Pakistan					1256	URP
	_T("0843"),	"uz_UZ",					//	Uzbek		Uzbekistan (Cyrillic)		1251	UZB
	_T("0443"),	"uz_UZ",					//	Uzbek		Uzbekistan (Latin)			1254	UZB
	_T("042a"),	"vi_VN",					//	Vietnamese	Viet Nam					1258	VIT
	NULL  , 
};

// kdGetLocale : Determine the current language and locale in platform specific.
const KDchar* xmPlatformGetLocale ( KDvoid )
{	
	TCHAR	tcode[128];		
	int		i;
	
	if ( GetLocaleInfo ( LOCALE_SYSTEM_DEFAULT, LOCALE_IDEFAULTLANGUAGE, tcode, 128 ) )
	{
		for ( i = 0; l_tables[i].tcode != NULL; i++ )
		{
			if ( !_tcscmp ( tcode, l_tables[i].tcode ) )
			{
				return l_tables[i].info;				
			}
		}
	} 
 	
	return "Unknown";
}

