#include "ekt_input_method_pinyin.h"
#include <string.h>
#include "etk_window.h"
#include "etk_wnd_manager.h"
#include "etk_button.h"
#include "etk_entry.h"
#include "etk_key.h"

typedef struct _CodeTable{
	char* pPinyin;
	char* pHanzi;
} CodeTable;
typedef CodeTable* PCodeTable;

#define MAX_ITEMS	406

CodeTable codeTable[] = {
	{"a"			,	"°¢°¡ºÇëçàÄï¹ß¹"},
	{"ai"			,	"°®°§°¤°­°£°©°¬°¦°«°¥°¨°ª°¯êÓö°ÞßàÈè¨æÈïÍàÉíÁ"},
	{"an"		,	"°²°¸°´°µ°¶°³ÚÏ÷ö°°°±âÖèñðÆ°·ï§ÞîáíÛû"},
	{"ang"		,	"°º°¹°»"},
	{"ao"		,	"°Â°Ä°Á°¾°½°¼°À°ÃÛêà»ÞÖ÷éæñ÷¡°¿á®âÚåÛéáñúæÁòüöË"},
	{"ba"		,	"°Ñ°Ë°É°Í°Ö°Õ°Î°È°Å°Ô°Ð°Ç°Ì°Ï°Ó°Ê°ÒôÎå±ÜØÝÃ÷Éá±°ÆîÙöÑ"},
	{"bai"		,	"°Ù°×°Ü°Ú²®°Ý°ØßÂêþÞã°Û°Þ"},
	{"ban"		,	"°ì°ë°æ°ã°à°å°é°á°ç°ß°ä°ê°è°â°íÚæÛàñ£îÓô²ñ­"},
	{"bang"		,	"°ï°î°ô°ò°ñ°ø°ó°õ°ùäº°ð°÷°öÝò"},
	{"bao"		,	"±¨±£°ü±©±¦±§±¡°û±¬±«±¥±¤ÆØÅÙ°ý±ª±¢°úÝáñÙæßìÒð±öµõÀ"},
	{"bei"		,	"±»±±±¸±³±¯±²±­±¶±´±®±°Ýí±¹ã£±·ßÂ±ºðÇØÃÚýÚéÛýíÕñØöÍ÷¹ÝÉ±µ"},
	{"ben"		,	"±¾±¼±¿±½º»ÛÎêÚï¼ÛÐ"},
	{"beng"		,	"±À±Â±Á±Ä±Åê´±ÃàÔ°ö"},
	{"bi"			,	"±È±Ø±Ê±Ï±Ò±Ü±Õ±Ç±Ë±Æ±Ú±Û±×±Ì±É±Ð±Î±ÓØ°èµ±Ö±Ýåöó÷æ¾ã¹±Ôåþå¨îéñÔÙÂ÷ÂÝÉÞµßÙáùâØïõääô°±ÑßÁæÔ±ÍêÚî¯Ý©ÛýóÙóëÜÅôÅõÏÜê"},
	{"bian"		,	"±à±ã±ß±ä±é±ç±æ±á±Þ±è±â±åí¾ÜÐØÒãêòùóÖíÜñ¹ñÛÛÍöýâíìÔçÂ"},
	{"biao"		,	"±í±ê±ëïÚ±ìæôïðñÑè¼ì­ñ¦÷Ôì®æ»ì©÷§"},
	{"bie"		,	"±ð±ï±ñõ¿±î"},
	{"bin"		,	"±ö±õ±ò±ó÷ÞçÍéë±ôéÄ±÷ë÷ÙÏçãáÙ÷ÆïÙ"},
	{"bing"		,	"²¢²¡±ø±ù±ý±û±ú±ü±þÙ÷ÚûÞð"},
	{"bo"		,	"²¨²¥²©²®²ª±¡²¦²´°Ø°þ²£²µ²·²±²«²²âÄô¤êþ²°õËíç²¤²¯²¬²§²³éÞîàë¢²­õÀØÃð¾õÛÙñà£"},
	{"bu"		,	"²»²¿²¼²½²¹²¶²À²·²¾²¸ÆÒß²²ºîßåÍõ³êÎê³îÐ"},
	{"ca"		,	"²Áàêíå"},
	{"cai"		,	"²Å²É²Ë²Æ²Ä²Ê²Ã²Â²Ì²È²Ç"},
	{"can"		,	"²Î²Í²Ð²Ò²Ó²Ñ²ô²Ïè²åîæî÷õôÓ"},
	{"cang"		,	"²Ø²Ô²Ö²×²ÕØ÷"},
	{"cao"		,	"²Ý²Ù²Ü²ÚàÐ²Ûó©ô½äî"},
	{"ce"		,	"²ß²â²à²Þ²áâü"},
	{"cen"		,	"²Îá¯ä¹"},
	{"ceng"		,	"Ôø²ã²äàá"},
	{"cha"		,	"²é²ì²î²è²åÉ²²æ²ï²ç²êÔû²íàêñÃè¾é«é¶éßïï²ëïÊâªâÇãâæ±"},
	{"chai"		,	"²î²ñ²ð²òîÎÙ­ò²ðû"},
	{"chan"		,	"²ú²ü²øìø²õ²ö²ù²ó²û²ôäýâãó¸æ¿ÚÆ²÷âÜåîå¤ÙæõðÝÛæöêèïâåñ"},
	{"chang"		,	"³¤³¡³£³ª³§³¢²ý³¦³¥³©³«ÌÈ³¨âêæ½²þæÏØöë©áäêÆöðãÑÝÅÜÉÛËã®"},
	{"chao"		,	"³¬³¯³±³´³³³­³°³®´Â³²êËìÌâ÷ñé"},
	{"che"		,	"³µ³¹³·³¶³º³¸Ûåíº"},
	{"chen"		,	"³Æ³Â³Á³¿³¾³¼³Ã³Ä³½³»Úßè¡³ÀàÁØ÷ÞÓÚÈå·é´ö³í×"},
	{"cheng"		,	"³É³Ç³Ì³Æ³Ð³ÏÊ¢³Ë³Ê³Å³Í³Î³Óîª³Èàá³ÑîõØ©³ÒÛôèÇëóîññÎõ¨èßòÉ"},
	{"chi"		,	"³Ô³Ö³Ù³ß³à³â³Ø³Õ³Ý³Û³Ü³á³×³ÞßêàÍà´³Úò¿³ãó×ë·ß³âÁõØð·ñÝôùÛæÜ¯ÜÝóøÙÑæÊó¤áÜí÷÷Îñ¡"},
	{"chong"		,	"ÖØ³å³ä³ç³æ³èã¿âçô¾Üûô©ï¥"},
	{"chou"		,	"³é³î³ð³ó³ï³ô³ê³ñ³ì³òã°³ë³íöÅÙ±àüñ¬"},
	{"chu"		,	"³ö´¦³ý³õ³þ´¥´¢´¡³øÐó³ù³÷³û´£âð³úèÆ´¤ç©÷íñÒòÜõéÛ»³üèúãÀØ¡éË"},
	{"chuai"		,	"´§à¨õßàÜëúÞõ"},
	{"chuan"		,	"´«´©´¨´¬´®´­â¶å×ô­çÝë°´ªîË"},
	{"chuang"	,	"´´´°´²´³´±´¯âë"},
	{"chui"		,	"´µ´¹´¶´¸´·Úïé³é¢"},
	{"chun"		,	"´º´¿´½´À´¼´¾´»ðÈòíÝ»"},
	{"chuo"		,	"´Â´Áà¨ê¡õÖöº"},
	{"ci"			,	"´Ë´Î´Ê²î´Ì´Ç´È´Å´Í´É×È´Ä´Æìô´ÃßÚðËôÙÜë"},
	{"cong"		,	"´Ó´Ò´Ï´Ô´Ð´ÑçýäÈèÈÜÊæõè®"},
	{"cou"		,	"´Õé¨ê£ëí"},
	{"cu"		,	"´Ù´Ö´Ø´××äâ§õíõ¾áÞéãÝýõ¡"},
	{"cuan"		,	"ÔÜ´Ü´Û´Úß¥ïéÙàìà"},
	{"cui"		,	"´à´â´ß´Ý´ÞÝÍ´ä´áã²è­ö¿´ãë¥éÁßý"},
	{"cun"		,	"´æ´å´çââñå"},
	{"cuo"		,	"´í´ë´ê´ì´é´èõãïóáÏëâðîðûõºØÈï±"},
	{"da"		,	"´ó´ò´ï´ð´î´ñàªí³ÞÇñ×÷²óÎ÷°âòæ§ßÕðã"},
	{"dai"		,	"´ú´ø´ý´÷´ü´ô´û´þ´õ´ù÷ìµ¡çéá·åÊ´öß¾ææçªÜ¤ß°"},
	{"dan"		,	"µ«µ¥µ£µ¯µ­µ©µ°µ¨µ®µ¤µ¢µ¬íñà¢å£µ§ééóìð÷êæðãñõµªÝÌµ¦ÙÙ"},
	{"dang"		,	"µ±µ³µ´µµµ²ñÉîõå´ÛÊÝÐÚÔí¸"},
	{"dao"		,	"µ½µÀµ¼µ¹µºµ¶µ¿µÁµ¸µ·µ»ß¶µ¾âáàüë®ôî"},
	{"de"		,	"µÄµÃµÂï½"},
	{"deng"		,	"µÈµÇµÆµËµÊµÉµÅàâíãê­ïëô£áØ"},
	{"di"			,	"µØµÚÌáµ×µÍµÛµÜµÐµÖµÝµÎµÏµÙµÌµÑµÞµÓàÖÚ®ÚÐµÒÛ¡íûµÕµÔíÆæ·é¦Ý¶ôÆÛæèÜêë÷¾Øµç°ïáíÚÙá"},
	{"dia"		,	"àÇ"},
	{"dian"		,	"µãµçµêµäµßµéµíµæµîµáµìµëµàµâñ²áÛõÚµèçèô¡ÚçÛãµåîäñ°Ø¼"},
	{"diao"		,	"µ÷µôµõµñµóµöµòµðõõµïï¢îööô"},
	{"die"		,	"µùµøµþµüµúµýµûà©ØýõÚëºñóõÞÜ¦ð¬ÞéÛìöø"},
	{"ding"		,	"¶¨¶©¶¥¶¡¶¢¶¤¶¦¶£î®îúëëôúØê¶§ðÛà¤çàíÖñô"},
	{"diu"		,	"¶ªîû"},
	{"dong"		,	"¶¯¶«¶®¶¬¶´¶³¶­¶°ßË¶²¶±ë±íÏð´á´Ûíá¼ëËëØ"},
	{"dou"		,	"¶¼¶·¶¹¶¶¶º¶µ¶¸ñ¼Ýúò½óû¶»"},
	{"du"		,	"¶¼¶Á¶È¶À¶¾¶½¶É¶Ç¶Å¶Ã¶Â¶Ä¶Êà½äÂóÆë¹¶Æ¶¿÷ò÷ÇèüÜ¶ó¼"},
	{"duan"		,	"¶Ï¶Î¶Ì¶Ë¶Í¶ÐìÑé²óý"},
	{"dui"		,	"¶Ô¶Ó¶Ñ¶ÒíÔí­í¡ïæ"},
	{"dun"		,	"¶Ù¶Ü¶Ö¶Ø¶×¶ÛìÀ¶Ýíïãç¶Ú¶Õõ»ïæíâí»"},
	{"duo"		,	"¶à¶á¶ä¶ã¶æ¶éõâßÍ¶å¶ß¶ç¶è¶âÍÔ¶ÞîìñÖßáç¶ãõèÞ"},
	{"e"			,	"¶î¶í¶ñ¶öÅ¶¶ì¶óãµ¶ôØ¬¶ð¶ëßÀ¶ò¶õ¶ïæ¹¶êéîò¦öùïÉÚÌåíï°ãÕÛÑëñÜÃðÊÝàÝ­"},
	{"ei"			,	"ÚÀ"},
	{"en"		,	"¶÷ÞôÝì"},
	{"er"		,	"¶ø¶þ¶ù¶û¶úåÇ¶ü¶ýð¹çíîïöÜ·¡Ù¦"},
	{"fa"		,	"·¢·¨·£·¦·¥·§íÀ·¤ÛÒ·©"},
	{"fan"		,	"·´·¹·¸·­·¶·²·³·µ·¬···±·º·«·ªá¦èó·®ìÜÞ¬î²·°ÞÀ·¯õì"},
	{"fang"		,	"·½·Å·¿·Ã·À·Â·¼·Á·ÄáÝ·»·¾ô³îÕöÐÚúèÊ"},
	{"fei"		,	"·Ç·Ñ·É·Ï·Ê·È·Ð·Æ·Î·Ë·Ìëèìé·Íö­ç³åúì³ôäòãðòäÇã­öîóõÜÀáôïÐé¼"},
	{"fen"		,	"·Ö·Ý·×·Ü·ß·Û·Õ·Ò·Ø·Ù·à·Þ·Ô·Úèû÷÷çã·ÓÙÇå¯ö÷"},
	{"feng"		,	"·ç·â·á·å·è·æ·ê·î·ì·ï·í·ë·ä·ã·éÙºí¿ßôÛºÝ×ãã"},
	{"fo"		,	"·ð"},
	{"fou"		,	"·ñó¾"},
	{"fu"		,	"·ò¸®·þ¸´¸¸¸º¸±¸£¸»¸¶¸¾¸½·ð·ù·ü·û¸°¸¯¸¡·ö¸¹¸§¸²·ô¸³¸¥¸µ¸¨·÷¸¦¸©¸«¸¿¸À¸¬¸¤·ý·ó¸·Ü½¸ªæÚ¸­Ùë·õ·ø¸¢¸¼·úèõòÝÜÀÜÞÜòÝ³ÝÊá¥âöÞÔäæíëåõôïç¦ç¨õÃìðíÉíêî·ò¶õÆòðß»ÙìÛ®ïûæâêçð¥òóöÖöû"},
	{"ga"		,	"¿§ÞÎ¸Â¸ÁÔþÙ¤ê¸îÅæØæÙ"},
	{"gai"		,	"¸Ä¸Ã¸Å¸ÇØ¤¸Æêà¸ÈÛòÚëê®"},
	{"gan"		,	"¸Ð¸É¸Ò¸Ï¸Ê¸Î¸ËÞÏ¸ÓéÏ¸Í¸Ñß¦ÛáÜÕ¸Ìãïí·ä÷ðáôûäÆç¤êº"},
	{"gang"		,	"¸Õ¸Û¸Ö¸Ú¸Ù¸×¿¸¸Ü¸Ô¸Øî¸í°óà"},
	{"gao"		,	"¸ß¸æ¸å¸ã¸â¸à¸Þ¸áØºéÂÞ»çÉ¸Ý¸äÚ¾éÀê½Û¬ï¯"},
	{"ge"		,	"¸ö¸ï¸÷¸è¸ñ¸ç¸ê¸ô¸ð¸î¸ó¸ì¸é¸í¿©¸ëàÃ÷Àò¢ÒÙë¡ëõïÓæüñËØîØªÜªÛÙÛÁô´¸õíÑò´"},
	{"gei"		,	"¸ø"},
	{"gen"		,	"¸ù¸úØ¨ôÞßçÝ¢"},
	{"geng"		,	"¸ü¹¢¸û¾±¸ý¸þ¹£ßìâÙöá¹¡ç®"},
	{"gong"		,	"¹¤¹«¹²¹©¹¦¹¥¹¬¹±¹§¹®¹ª¹¨¹­¹°ëÅ¹¯ò¼çîö¡"},
	{"gou"		,	"¹»¹º¹¹¹·¹µ¹´¹¶¹³êíóô¹¸Øþá¸Ú¸÷¸óÑèÛåÜæÅçÃì°"},
	{"gu"		,	"¹Ê¹Å¹Ë¹É¹Ä¹Ã¹Ç¹Ì¹Â¹È¹À¹Í¹¼¹¾¹Á¹¿¹½ãééïïÀ¹Æèôð³ì±ðÀëûî­î¹îÜõý÷½ÝÔòÁØÅÚ¬áÄôþêöêôðóöñ"},
	{"gua"		,	"¹Ò¹Ï¹Î¹ÑßÉ¹ÓØÔ¹Ðð»èéëÒÚ´"},
	{"guai"		,	"¹Ö¹Ô¹ÕÞâ"},
	{"guan"		,	"¹Ø¹Û¹Ü¹Ù¹Ý¹ß¹Ú¹á¹Þ¹à¹×Ý¸ÙÄÂÚÞèîÂäÊ÷¤ðÙ"},
	{"guang"		,	"¹ã¹â¹äáîßÛë×èæ"},
	{"gui"		,	"¹æ¹é¹ó¹í¹ð¹ò¹ñ¹ì¹å¹î¹ô¹ê¹è¹ëð§¿þ¹ï¹çêÐóþæ£öÙØÐâÑå³È²ØÛèíêÁ÷¬"},
	{"gun"		,	"¹ö¹÷öççµíÞ¹õÙò"},
	{"guo"		,	"¹ú¹ý¹û¹ø¹ù¹üàþòåñøÙåÞâÛöë½ßÃáÆâ£é¤òä"},
	{"ha"		,	"¹þ¸òîþ"},
	{"hai"		,	"»¹º£º¢º¦ºÙ¿Èº¥º§º¡àËëÜõ°º¤"},
	{"han"		,	"ººº°º¬º®º¹º«º¶º­º¯º²º³º±ºµº´º¨º·º©êÏå«÷ýñüãÛº¸òÀìÊò¥ÝÕÞþÚõºª"},
	{"hang"		,	"ÐÐº½Ïïº¼º»ãìñþç¬çñ"},
	{"hao"		,	"ºÃºÅºÁºÀºÆºÄð©º¿ê»ºÂº¾ÝïºÑå°¸äàÆàãÞ¶å©òºò«"},
	{"he"		,	"ºÍºÎºÏºÓºÈºÕºËÏÅºØºÐºÇºÌºÉº×ÛÖºÒºÖÚ­ºÔãØàÀºÑêÂò¢ÛÀîÁæüòÂôçºÊ"},
	{"hei"		,	"ºÚºÙàË"},
	{"hen"		,	"ºÜºÞºÝºÛ"},
	{"heng"		,	"ºáºâºãºßºàÞ¿çñèì"},
	{"hong"		,	"ºìºäºéºèºåºêºçºëºæãüãÈÞ°Ú§Þ®ÙêÙäÝ¦"},
	{"hou"		,	"ºóºòááºñºîºíºðºïåËô×÷¿Ü©ðúóóö×"},
	{"hu"		,	"ºõ»¤ºôºú»§ºþºö»¥ºý»¢ºøºü»¦ã±ä°»£ºù»¡ºûàñº÷õúìïâ©ðÀõ­ìæìèßüóËçúäïðÉéõìÃÙüá²âï÷½éÎì²ð­ð×ìÎ"},
	{"hua"		,	"»°»ª»¯»¨»®»­»¬»©èë»«í¹îüæè"},
	{"huai"		,	"»³»µ»²»´»±õ×"},
	{"huan"		,	"»¶»»»¹»·»º»¼»Ã»½»Â»À»¾å¾÷ß»Áä½Û¼»¸çÙ»¿ïÌÛ¨ÝÈà÷ä¡ß§âµäñåÕöé"},
	{"huang"		,	"»Æ»Ê»Ä»Î»Å»Í»Ì»Ð»Ñè«áå»É»Ë»Ïäê»Èó¨åØÚòëÁ»Çñ¥äÒóòöü"},
	{"hui"		,	"»á»Ø»ã»Ó»Ô»Ò»Ý»Ù»Ú»Ö»Û»æ»Õ»ä»ß»²»Þ»à»åÚ¶êÍåç÷â»âÜö»ÜÜîà¹»×í£ä§çõÞ¥ßÜßÔä«ò³çÀèíãÄó³"},
	{"hun"		,	"»é»ì»ê»è»ëâÆ»çÚ»äããÔçõ"},
	{"huo"		,	"ºÍ»ò»î»ð»ñ»õ»ï»ö»ó»ô»íâ·ïÁñëØåîØß«Þ½àëïìó¶"},
	{"ji"			,	"¼¸¸ø¼º»ú¼Ç¼°¼Æ¼´»ù¼Ã¼­¼¶¼«¼Ä¼Ê¼¼¼¯¼Í»÷Ææ¼±¼¤¼Ì¼È»ý¼®¼¦¼ª¼·¼£¼¾¼Å¼¨¼²¼¢¼À¼©¼É¼Á»ø¼§í¶¼¡¼µ¼¥½åß´¼¹¼½»ü¼Ë¼¬æ÷»û¼»¼³¼Âá§¼¿óÅõÒñ¤Ø½Úµôßö«î¿ð¢ÙÊêªïúé®ßóöê÷ÙÜù»þêéÝðçÜò±ì´éêÛÔÙ¥ÞáÜ¸Ø¢÷äÞªßÒáÕÜÁóÇßâä©ØÀê«åìØÞõÕçáöÝêåê÷"},
	{"jia"		,	"¼Ò¼Ó¼Û¼Ù¼Ü¼×¼Ñ¼Ý¼Ð¼Þ¼Î¼Ö¼ÚÇÑÙ®Ð®¼Õð¨½Ä¼Ïçìê©åÈÙ¤ä¤ðèëÎóÕ¼ÔÝç¼ØïØØÅÛ£ÞØáµáèäÐë¸ôÂðýí¢îòñÊòÌõÊ"},
	{"jian"		,	"¼û¼ä¼þ½¨¼ò¼á¼à¼õ½¥¼ì½¡¼æ½£¼è¼ç¼ü¼ö¼â¼ø¼ô¼ù¼é¼ñ¼ý½¢¼ð¼ú½¦¼å¼ó¼÷¼î¼ß¼ê¼ë¼ã¼íÚÉå¿ÙÔ½§ÝÑåÀ¼ïíúïµ½¤ë¦öä÷µÝóÞöÚÙàîäÕçÌèÅê¯ê§êùñÐóÈôåõÂé¥êððÏëìõÝ"},
	{"jiang"		,	"½«½²½±½µ½¯½®½´½ª½¬½©½³êñçÖç­½°ñðíää®ôøÜüôÝ"},
	{"jiao"		,	"½Ì½»¾õÐ£½Ð½Ï½Ç½Å½¹½¾½¼½Î½Á½À½º½É½Ê½È½·½Ã½¿Ù®½Æ½½õÓæ¯½Ñ½Ë½Äð¨½¶½Í½¸öÞáèäÐë¸ÙÕðÔá½òÔ½ÂÜ´ÜúÞØàÝõ´"},
	{"jie"		,	"½ç½â½Ó½á½Ú½Ö½ã½×½é½è½ä½Ü½ì½Ô½Ý½Ø½à½Ò½Ù½ß½å½Þ½ëàµÞ×æÝíÙ½ÕÚµèî½æÙÊò¡Ú¦ðÜ½êæ¼ôÉöÚò»÷ºà®"},
	{"jin"		,	"½ø½ñ½ð½ü¾¡½ö½ô½û¾¢½ò½ï½÷½õ½î½ú½í½þ½óèªñæ½ùçÆ½ýàäêîâËÝÀñÆÝ£âÛæ¡ÚáêáéÈ"},
	{"jing"		,	"¾­¾©¾«¾³¾¯¾¹¾²¾ª¾°¾´¾¦¾µ¾º¾»¾®¾¶¾§¾£¾¤¾±ã½¾¸¾¨ãþÚåÙÓìº¾·åÉ¾¥ëÖëæÝ¼¾¬â°ëÂåòæºØÙö¦"},
	{"jiong"		,	"¾½¾¼åÄìçêÁ"},
	{"jiu"		,	"¾Í¾Å¾¿¾Æ¾Ã¾É¾È¾À¾¾¾Î¾Ë¾Âôñð¯¾Ä¾Ìà±¾ÊðÕãÎÙÖ¾Ç¾ÁèÑèê÷Ý"},
	{"ju"		,	"¾Ö¾Ý¾Ó¾ä¾Ù¾ß¾ç¾Þ¾Û¾Ü¾ã¾à¾å¾Õ¾Ð¾Ø½Û¾Ô¾Ï¾×¾ÚöÄ¾â¾æì«ôòÞäõá¾áåáéÙÙÆ¾Òö´åðêøñÕîÒÜÚöÂ÷¶é§ÚªÜÄï¸¾Ñé°ÜìèÛé·ñÀõ¶è¢"},
	{"juan"		,	"¾è¾í¾ë¾ì¾êöÁ¾î¾éä¸ïÔïÃÛ²áúèðîÃ"},
	{"jue"		,	"¾õ¾ø¾ö½Å½À¾ò¾÷áÈ¾ô¾ñ¾óâ±àµØÊõê¾ðÚÜÛÇ¾ïàåæÞéÓàÙçåèöØãìßïãÞ§õû"},
	{"jun"		,	"¾ü¾ù¾ý¿¡¾þ¾ûöÁóÞ¾ú¿¤¿¥¿¢÷åñäÞÜ¿£"},
	{"ka"		,	"¿¨¿§¿¦ßÇØûëÌ"},
	{"kai"		,	"¿ª¿®¿­îø¿«¿¬âýÛîÝÜï´ØÜïÇâé"},
	{"kan"		,	"¿´¿¯Ù©¿°¿³¿²¼÷¿±î«íèãÛÝ¨ê¬"},
	{"kang"		,	"¿¹¿µ¿¶¿¸¿»¿º¿·ØøãÊîÖ"},
	{"kao"		,	"¿¼¿¿îí¿¾¿½êûèàåê"},
	{"ke"		,	"¿É¿Ë¿Æ¿Í¿Ì¿Î¿Å¿Ê¿ÂºÇ¿Ãã¡¿È¿Á¿Ä¿Ç¿Àà¾î§éðïýðâòòäÛ÷ÁîÝñ½ò¤çæá³æìç¼ë´ï¾òÂ"},
	{"ken"		,	"¿Ï¿Ò¿Ð¿Ñö¸ñÌ"},
	{"keng"		,	"¿Ó¿Ôï¬"},
	{"kong"		,	"¿Õ¿Ö¿Ø¿×ÙÅáÇóí"},
	{"kou"		,	"¿Ú¿Û¿Ù¿ÜßµÞ¢íîÜÒóØ"},
	{"ku"		,	"¿à¿Þ¿â¿ã¿á¿Ý¿ß÷¼ØÚÜ¥à·ç«"},
	{"kua"		,	"¿ä¿ç¿å¿æ¿èÙ¨"},
	{"kuai"		,	"»á¿ì¿é¿êëÚØáßà¿ëáöä«Û¦"},
	{"kuan"		,	"¿î¿í÷Å"},
	{"kuang"		,	"¿ö¿ñ¿ó¿ò¿õ¿ô¿ð¿ïßÑÚ÷Ú²ÞÅÚ¿ÛÛæþêÜ"},
	{"kui"		,	"¿÷À¢À£¿ú¿ýÀ¡î¥¿øåÓ¿û¿üØÑ¿þà°ñù¿ùØ¸Ùçóñà­ã¦êÒÚóÝÞòñã´ÞñõÍ"},
	{"kun"		,	"À§À¥À¦À¤öïã§÷Õï¿õ«ãÍçû"},
	{"kuo"		,	"À¨À«À©ÀªèéòÒ"},
	{"la"			,	"À­À²À±À°À®À¬À¯ØÝååê¹ðøíÇ"},
	{"lai"		,	"À´ÀµÀ³íùñ®ô¥áâäµêãïªáÁäþ"},
	{"lan"		,	"À¼À¶À¸ÀÃÀÁÀÀÀÄÀ¹ÀºÀ¿À½é­À·ÀÂìµá°À»ñÜïçî½À¾äí"},
	{"lang"		,	"ÀËÀÇÀÊÀÉÀÈÀÅòëÀÆà¥Ý¹ï¶ïüãÏÝõ"},
	{"lao"		,	"ÀÏÀÍÀÎÀÌÀÑÀÐÁÊßëÀÓÀÒÀÔáÀðìõ²ï©èáîîñì"},
	{"le"			,	"ÁËÀÖÀÕÀßß·ãî÷¦Øì"},
	{"lei"		,	"ÀàÀáÀÛÀ×ÀÙÀÝÀÚÀÞÀßÀÜÙúÚ³ÀØàÏéÛæÐçÐõªñç"},
	{"leng"		,	"Àäã¶ÀãÀâÜ¨"},
	{"li"			,	"ÀïÀíÁ¦ÀûÁ¢ÀîÀúÀëÀýÀñÀöÀøÀèÀ÷Á§ÀòÁ¨óÒÁ£ÀþÀìÀõÀêÀæÁ¥ÀôÁ¤ÀéÀåÀçö¨î¾Ý°ìåÀðÙµíÂÞ¼Ù³òÛ÷óÛªÁ¡èÀåÎæ²îºæêÀó÷¯à¬ð¿æËó»Øªöâã¦ÛÞÜÂÀùÞºß¿à¦áûäàå¢èÝéöÝñÀüçÊðÝðßòÃï®óöôÏõÈõ·"},
	{"lia"		,	"Á©"},
	{"lian"		,	"ÁªÁ¬Á³Á·ÁµÁ¯Á«Á®Á¶Á±Á´Á²Á°Á­éççöé¬ñÍñÏó¹öãå¥ì¡äòÝüÞÆ"},
	{"liang"		,	"Á½Á¿Á¼ÁÁÁ¾ÁºÁ©Á¹Á¸ÁÂÁ»ÁÀõÔÝ¹Ü®÷Ëé£ö¦"},
	{"liao"		,	"ÁËÁÏÁÄÁÆÁÉÁÅÁÎÁÈÁÍÁÊÁÃÁÌçÔÁÇå¼àÚîÉâ²ðÓÞ¤ÞÍ"},
	{"lie"		,	"ÁÐÁÒÁÑÁÓÁÔßÖôóÙýä£ÞæÛøõñ÷à"},
	{"lin"		,	"ÁÖÁÙÁÚÁÕÁÜÁØ÷ëÁÝÁßÁÛÁ×õïÁÞá×ê¥éÝåàôÔÝþãÁî¬ßøì¢âÞ"},
	{"ling"		,	"ÁìÁîÁíÁéÁãÁäÁèÁáÁåÁêÁëÁàÁæñöàòÀâÁâôáÜßê²èùç±ßÊèÚöìÛ¹ãöÁçòÈ"},
	{"liu"		,	"ÁùÁôÁ÷Â½ÁõÁïÁøÂµÁöÁñä¯ÁòÁðåÞÁóïÖæòç¸ï³ì¼ìÖöÌðÒ"},
	{"long"		,	"ÁúÂ¡ÁýëÊÂ£ÁüÁûÂ¢ççÁþÂ¤ñªÜ×èÐãñÛâíÃ"},
	{"lou"		,	"Â¥ÂªÂ©Â§à¶Â¨ÙÍÂ¦÷Ãò÷ïÎÝäáÐñïðü"},
	{"lu"			,	"Â·Â½Â¼Â¬Â¶Â³Â¯Â¹ÂµÂ®Â«ààÂ­Â»ê¤Â±Â²Â´ãòÂ¸äõÂ¾óüéñðØÂ°ÂºöÔß£èÓÛäëÍÞ¤äËðµåÖè´éûéÖïåôµëª"},
	{"lv"			,	"ÂÉÂÃÂÌÂÊÂÇÂÄÂÅÂÂÂÆÂ¿ÂÀéµÂËÞÛÂÁñÚãÌëöÂÈïù"},
	{"luan"		,	"ÂÒÂÑÂÍÂÎÂÏèïöÇæ®ÂÐð½Ùõ"},
	{"lue"		,	"ÂÔÂÓï²"},
	{"lun"		,	"ÂÛÂÖÂ×ÂÙÂØÂÕàðÂÚ"},
	{"luo"		,	"ÂäÂÞÂçÂåÂßÂãÂæÂÜÂÝÂàÂáÞûÀÓÞÛçóÂââ¤ïÝé¡ÙÀÙùÜýñ§ãøäðëáíÑöÃ"},
	{"m"		,	"ß¼"},
	{"ma"		,	"ÂíÂðÂèÂëÂéÂîÂïÄ¨ÂêÂìó¡ßéè¿áïæÖ"},
	{"mai"		,	"ÂòÂôÂóÂñÂõÂöö²Û½Ý¤"},
	{"man"		,	"ÂúÂýÂþÂüÂùÂøÂ÷Âûò©Ã¡Ü¬á£òý÷´÷©çÏì×ïÜ"},
	{"mang"		,	"Ã¦Ã£Ã¤Ã¢Ã¥Ã§òþÚøäÝíË"},
	{"mao"		,	"Ã«Ã°Ã¨Ã³Ã¬Ã±Ã²Ã©Ã¯÷ÖÃ®ë£è£Ãªí®ÙóÃ­á¹êóó±ã÷êÄÜâì¸òúî¦"},
	{"me"		,	"Ã´÷á"},
	{"mei"		,	"Ã»ÃÀÃ¿ÃÃÃ¼Ã·Ã½Ã¶÷ÈÃºÃÁÃ¹ÃµÃÄÃÂÃÓñÇÃ¸Ý®áÒé¹äØâ­ïÑä¼ðÌÃ¾"},
	{"men"		,	"ÃÇÃÅÃÆÞÑí¯ìËîÍ"},
	{"meng"		,	"ÃÎÃÉÃÍÃËëüÃÏÃÈÛÂãÂÃÊó·Þ«Ýùíæòìòµô»ô¿ÃÌ"},
	{"mi"		,	"ÃÜÃ×ÃØÃÔÃÖÃÕÃÙÃÐÃÛÃÒßäÚ×ÃÚÃÓãèåµ÷çÃÑåôôÍØÂìòëßÃÝ÷ãà×ÞÂâ¨ôé"},
	{"mian"		,	"ÃæÃâÃÞÃßÃåÃàÃãëïÃáÃääÏãæííö¼äÅ"},
	{"miao"		,	"ÃîÃèÃëÃíÃçÃìÃéÃêçÑíµç¿ß÷íðåãðÅèÂ"},
	{"mie"		,	"ÃðÃïóúßãØ¿óº"},
	{"min"		,	"ÃñÃôÃõÃöãýçëÃóÃòãÉÜåáºçÅçäíªö¼÷ª"},
	{"ming"		,	"ÃûÃ÷ÃüÃùÃúÚ¤Üøäéõ¤î¨êÔÃø"},
	{"miu"		,	"ÃýçÑ"},
	{"mo"		,	"Ä¬ÄªÄ£÷áÄ©Ä¥ÃþÄ¦Ä¯Ä®Ä«Ä¨Ä§Ä°ºÙÄ­Ä¤ÝëÄ¢ÜÔâÉÄ¡ºÑÚÓæÆï÷ïÒéâñ¢ñòõöõø"},
	{"mou"		,	"Ä³Ä±íøçÑöÊßèÙ°òÖ"},
	{"mu"		,	"Ä¿Ä¸Ä¾Ä»Ä·Ä½ÄÁÄ¹Ä¼ÄºÄ²Ä¶ÄÂÄÀÄ´ãåÄµØïÛéÜÙë¤îâ"},
	{"n"			,	"àÅßí"},
	{"na"		,	"ÄÇÄÃÄØÄÄÄÉÄÈÄÅÞàÄÆïÕëÇñÄ"},
	{"nai"		,	"ÄËÄÌÄÎÄÍÄÊÜµØ¾Ù¦ÝÁèÍ"},
	{"nan"		,	"ÄÑÄÏÄÐéªà«àïàîëîòïôö"},
	{"nang"		,	"ÄÒàìâÎß­êÙ"},
	{"nao"		,	"ÄÔÄÖÄÕÄÓè§Ä×ßÎâ®îóØ«íÐòÍÛñ"},
	{"ne"		,	"ÄØÚ«"},
	{"nei"		,	"ÄÚÄÙ"},
	{"nen"		,	"ÄÛí¥"},
	{"neng"		,	"ÄÜ"},
	{"ng"		,	"àÅßí"},
	{"ni"			,	"ÄãÄØÄáÄàÄæÄßÄäÄâÄåÄÝÄÞêÇÄçì»íþöòÛèâ¥âõÙ£ìòí«îê"},
	{"nian"		,	"ÄêÄîØ¥Õ³ÄëÄíÄèÄìÄéð¤öóöÓéýÛþ"},
	{"niang"		,	"ÄïÄð"},
	{"niao"		,	"ÄñÄòôÁæÕÜàëå"},
	{"nie"		,	"ÄóÄùÄôÄõõæà¿ÄöÄ÷ÄøØ¿Úíò¨ô«ÞÁ"},
	{"nin"		,	"Äúí¥"},
	{"ning"		,	"ÄþÄýÅ¡Å¢ßÌÄüÄûØúñ÷ÜÑå¸"},
	{"niu"		,	"Å£Å¦Å¤æ¤Å¥ÞÖâîáð"},
	{"nong"		,	"Å©ÅªÅ¨Ù¯ßæÅ§"},
	{"nou"		,	"ññ"},
	{"nu"		,	"Å­Å¬Å«åóæåæÀæÛ"},
	{"nv"		,	"Å®îÏí¤ô¬"},
	{"nuan"		,	"Å¯"},
	{"nue"		,	"Å°Å±"},
	{"nuo"		,	"ÅµÅ²Å³Å´ßöÞùÙÐï»"},
	{"o"			,	"Å¶àÞà¸"},
	{"ou"		,	"Å·Å¼Å¹Å»Å¸Ú©ê±ÅºÅ½ñîâæ"},
	{"pa"		,	"ÅÂÅÀÅÁ°ÇÅ¿Å¾ÅÃÝâ°ÒèËîÙóá"},
	{"pai"		,	"ÅÉÅÅÅÆÅÄÅÇÅÈÙ½Ýåßß"},
	{"pan"		,	"ÅÐÅÌÅÎÅÑÅÏÅËÅÊÞÕõçÅÍãÝó´ñáñÈãú"},
	{"pang"		,	"ÅÔÅÓÅÖÅÒ°ò°õáÝó¦äèÅÕåÌ"},
	{"pao"		,	"ÅÜÅÚÅ×ÅÝÅÛÅÙÅØáóðåëãâÒÞË"},
	{"pei"		,	"ÅäÅãÅàÅåÅâÅæÅáÅÞÅßõ¬ïÂàÎàúì·ö¬"},
	{"pen"		,	"ÅèÅçäÔ"},
	{"peng"		,	"ÅóÅôÅöÅíÅõÅïÅîÅòÅëÅêÅñÅéÅìâñÜ¡ó²àØÅð"},
	{"pi"			,	"Åú·ñÆ¤Æ¨ÅûÆ£±ÙÆ¡Æ¢Æ¥Æ§ÅüÆ©Å÷Æ¦ñ±ÅýÅþÅùàèæÇÛ¯ñÔç¢Ø§Ü±ÛÜò·òçõùÚéÚðÅøØòÛýß¨ßÁâÏÚüñâÜÅèÁî¼äÄîëê¶î¢"},
	{"pian"		,	"±ãÆ¬ÆªÆ«Æ­ôæ±âêúÚÒõäæéçÂëÝ"},
	{"piao"		,	"Æ±Æ¯Æ®Æ°æÎî©æôàÑØâóªçÎÝ³éè"},
	{"pie"		,	"Æ²Æ³ë­Ø¯ÜÖ"},
	{"pin"		,	"Æ·Æ¶Æ´ÆµÆ¸ÞÕæ°æÉé¯ò­êò"},
	{"ping"		,	"Æ½ÆÀÆ¿Æ¾Æ¼Æ¹ÆÁÆ»ÆºèÒæ³Ù·öÒ"},
	{"po"		,	"ÆÆÆÈÆÄÆÅÆÂ²´ÆÃÆÇÆÉçêØÏê·îÞóÍîÇÚéãøÛ¶ð«"},
	{"pou"		,	"ÆÊÙöÞå"},
	{"pu"		,	"ÆÕÆÌÆËÆÓÆ×ÆÖÆÏÆÑÆÍ¸¬ÆÙÆÐäßÙéè±àÛÆÔÆÒë«ïèõëïäå§ÆÎ"},
	{"qi"			,	"ÆðÆäÆÚÆøÆßÆæÆÞÆóÆ÷ÆûÆåÆëÆìÆúÆôÆïÆÛÆçÆñÆÝÆàÆüÆõç÷ÆòÆíÆáÆùÆêÆÜÆãì÷ÆéÆîçùõèÆöí¬ä¿ãàØ½ç²ÆýàÒáªÝÂÙ¹è½ÜÎÜùêÈéÊñýÜ»á¨ì¥èçôìÝ½òÓòàôë÷¢÷èÞ­ÆâØÁæëÝÝÆèÛßíÓ"},
	{"qia"		,	"Ç¡Ç¢ÆþÙ¤ñÊÝÖ÷Ä"},
	{"qian"		,	"Ç°Ç®Ç§Ç©Ç·Ç£Ç³Ç±Ç¨Ç«Ç²Ç¸ÏËÇ¶Ç¬Ç´Ç¦ò¯Ç¯å¹Ù»ÇµÇ­Þçã¥Ü·ç×í©Ý¡ÜÍÚäÙÝåºå½ëÉÇ¥ÇªêùîÔá©óé÷ÜÇ¤ã»èý"},
	{"qiang"		,	"Ç¿Ç¹Ç½ÇÀÇ»ÇºïÏõÄÇ¼Ç¾ãÞñßéÉìÁòÞæÍïºê¨ôÇïê"},
	{"qiao"		,	"ÇÅÇÄÇÇÇÉÇÈÇÆÇÃÇÌÇÎÇÏÇÍÇÂÇËõÎã¾éÔÇÊÇÁÚ½ã¸ÚÛÜñá½çØíÍ÷³Øä"},
	{"qie"		,	"ÇÐÇÒÇÔÇÓÇÑôòæªÆöã«Ù¤ïÆêüÛ§óæã»"},
	{"qin"		,	"Ç×ÇÕÇÙÇÖÇØÇÚÇÛÇÜÇÞñûÇßÇÝàßÞìéÕï·ÜËàºòûôÀâÛäÚßÄ"},
	{"qing"		,	"ÇéÇëÇàÇåÇáÇçÇìÇãÇäÇæÇêÇâóÀòßíàö¥ÜÜàõéÑ÷ôöëÇèóäôì"},
	{"qiong"		,	"ÇîÇíñ·ÜäÚöòËóÌõ¼öÆ"},
	{"qiu"		,	"ÇóÇòÇïÇñÇôÇðÇõòÇôÃÙ´ò°öúåÏåÙêäÇöé±áìäÐòøÛÏ÷üôÜ"},
	{"qu"		,	"È¥È¡ÇøÇúÈ¤ÇüÇ÷ÇýÇþÇûÈ¢êïöÄá«ÐçòÐáéÇùñ³ôðãÖìîíáð¶Ú°ó½Û¾Þ¡Þ¾È£ÜÄ÷ñè³ë¬ëÔ"},
	{"quan"		,	"È«È¨È¦È°ÈªÈ¯È­È®Ú¹È§òéç¹ÜõîýÈ¬÷Üéúãªî°È©óÜ"},
	{"que"		,	"È´È·È±È¸È³È¶Èµã×ãÚÈ²í¨"},
	{"qun"		,	"ÈºÈ¹åÒ÷å"},
	{"ran"		,	"È»È¾È¼È½÷×ÜÛòÅ"},
	{"rang"		,	"ÈÃÈÂÈÁÈÀÈ¿ð¦ìü"},
	{"rao"		,	"ÈÅÈÆÈÄæ¬èãÜé"},
	{"re"		,	"ÈÈÈÇßö"},
	{"ren"		,	"ÈËÈÎÈÏÈÌÈÊÈÍÈÐÈÒâ¿ÈÉØðïþÝØÜóÈÑéíñÅ"},
	{"reng"		,	"ÈÔÈÓ"},
	{"ri"			,	"ÈÕ"},
	{"rong"		,	"ÈÝÈÙÈÚÈØÈÜÈÞÈÛéÅÈÖáÉÈ×ÈßëÀòîáõ"},
	{"rou"		,	"ÈâÈáÈàõå÷·ôÛ"},
	{"ru"		,	"ÈçÈëÈèÈåÈéÈêÈìàéÈãå¦ÈäÈæçÈñàò¬Þ¸Ýêä²äáï¨"},
	{"ruan"		,	"ÈíÈîëÃ"},
	{"rui"		,	"ÈðÈñÜÇî£Þ¨èÄÈïò¸"},
	{"run"		,	"ÈóÈò"},
	{"ruo"		,	"ÈôÈõÙ¼óè"},
	{"sa"		,	"È÷ÈöÈøØ¦ØíìªêýëÛ"},
	{"sai"		,	"ÈüÈûÈùàçÈú"},
	{"san"		,	"ÈýÉ¢É¡Èþë§âÌôÖö±"},
	{"sang"		,	"É¥É£É¤Þúíßòª"},
	{"sao"		,	"É¨É§É©ÉÒëýÉ¦çØçÒöþÜ£ðþ"},
	{"se"		,	"É«ÈûÉ¬ÉªØÄï¤ð£"},
	{"sen"		,	"É­"},
	{"seng"		,	"É®"},
	{"sha"		,	"É±É³É¶ÉµÏÃÉ²É´É¯É·É°ö®àÄêýì¦öèßþððôÄï¡"},
	{"shai"		,	"É¹É¸õ§"},
	{"shan"		,	"É½ÉÆÉÁÉÀÉ¾É¿ÉÈÉÂÉºÉ¼ÉÃ²ôÉÅÕ¤Ú¨õÇÉÇæ©ÉÄäúÉÉæÓµ§ëþæóÜÏÛïØßîÌÛ·ô®É»÷ÔðÞóµ÷­"},
	{"shang"		,	"ÉÏÉÌÉËÉÐÉÍéäÉÑÉÎõüìØÉÊç´Ûð"},
	{"shao"		,	"ÉÙÉÜÉÕÉÔÉ×ÉÚÉÛÉÒÉÓÉØÜæÇÊäûÛ¿è¼ÉÖòÙóâô¹"},
	{"she"		,	"ÉçÉèÉáÉæÉäÉãÉàÉßÉÝÉâÉåÙÜÉÞ÷êî´ØÇäÜì¨â¦"},
	{"shei"		,	"Ë­"},
	{"shen"		,	"Ê²ÉíÉîÉñ²ÎÉõÉêÉóÉòÉìÉ÷ÉøÉðÉöÉëÉôÝ·ò×ÝØÉïäÉïòÚ·ÉéôÖÚÅé©ëÏßÓ"},
	{"sheng"		,	"ÉúÉùÊ¡Ê¤ÉýÊ¥Ê¢Ê£ÉüÉþÉûóÏäÅíòáÓêÉ"},
	{"shi"		,	"ÊÇÊ±Ê®ÊÂÊµÊ¹ÊÀÊÐÊ¶Ê¼Ê¿Ê¦Ê«Ê½Ê§Ê·ÊÓÊ¾Ê³ÊÒÊÆÊÔÊ¯ÊÍÊ©ÊÊÊÏÊ»ÊÎÊ¬Ê°ÊÅÊªÊÄÊ¨ÊÈÊ´ÐêÊºÊÌ³×ÖÅÊËÊÑÊÁéøÊ¸ÊÉÊÃÊ­ß±ÝéÛõÝªìÂÚÖöåõ¹êÛîæó§óÂóßöõõ§"},
	{"shou"		,	"ÊÖÊÜÊÕÊ×ÊÚÊØÊÛÊÝÊÙÊÞá÷ç·ô¼"},
	{"shu"		,	"ÊéÊýÊõÊôÊäÊ÷ÊöÊìÊøÊðÊâÊæÊåÊóÊèÊçÊãÊíÊáÊîÊúÊñË¡ÊûÊëÊþÊàÓáÊêÊòÊßÊïÙ¿ÊüÊùÛÓäøæ­ç£ïøë¨ì¯ñâÝÄØ­ãðÞóëò"},
	{"shua"		,	"Ë¢Ë£à§"},
	{"shuai"		,	"ÂÊË¥Ë¤Ë¦Ë§ó°"},
	{"shuan"		,	"äÌË¨Ë©ãÅ"},
	{"shuang"	,	"Ë«Ë¬Ëªæ×ãñ"},
	{"shui"		,	"Ë®Ë­Ë°Ë¯"},
	{"shun"		,	"Ë³Ë´Ë²Ë±"},
	{"shuo"		,	"ËµË·Ë¶Ë¸îååùÝôéÃÞ÷"},
	{"si"			,	"ËÄËÀË¼Ë¹Ë¾ËÆË½Ë¿ËÂËºËÁØËË»ËÅËÇËÃìëËÈæáð¸Ù¹ãáãôÛÌÙîòÏßÐæ¦äùçÁñêóÓïÈ"},
	{"song"		,	"ËÍËÉËÎËÐËÊËÌËÏã¤ËËâìäÁÝ¿áÂáÔÚ¡ñµ"},
	{"sou"		,	"ËÑËÒËÔËÓâÈÞ´àÕÛÅà²äÑì¬ïËî¤òô"},
	{"su"		,	"ËÕËßËÙËØË×ËàËÞËÜöÕËÝËÖËÚóùÙíà¼ÚÕËÛãºä³Ýøö¢"},
	{"suan"		,	"ËãËáËââ¡"},
	{"sui"		,	"ËêËæËäËéËìËîËíËèåäËëËåËçî¡Ý´ìÝÚÇíõå¡"},
	{"sun"		,	"ËïËðËñÝ¥áøâ¸é¾öÀ"},
	{"suo"		,	"ËùË÷ËõËøËöËóàÂËôêýæ¶íüßïàÊËòôÈèø"},
	{"ta"		,	"ËûËýËüÌ¤ËþËúé½àªÌ£í³åÝÌ¢÷£ãËîèõÁäðäâÌ¡"},
	{"tai"		,	"Ì«Ì¨Ì¬Ì©Ì§Ì¥Ì­Ì¦ß¾öØÛ¢Þ·ÌªææìÆõÌëÄîÑ"},
	{"tan"		,	"Ì¸Ì½µ¯Ì¹Ì¾Ì³Ì¯Ì°Ì²ÌºÌ·Ì¶Ì±Ì¿ñûÌµìþÌ®Ì»Ì¼å£Ì´ê¼ïâÛ°ïÄîã"},
	{"tang"		,	"ÌÃÌÆÌÀÌÉÌÇÌËÌÈÌÌÌÊÌÅÌÁÌÄÌÂäçó«è©éÌó¥ï¦õ±ïÛñíâ¼ÙÎàûôÊ"},
	{"tao"		,	"ÌÖÌ×ÌÓÌÎÌÍÌÕÌÒÌÔÌÏÌÑìâßûèº÷Òä¬ÌÐØ»"},
	{"te"		,	"ÌØìýß¯í«ï«"},
	{"tei"		,	"ß¯"},
	{"teng"		,	"ÌÚÌÛÌÙÌÜëø"},
	{"ti"			,	"ÌåÌáÌâÌæÌßÌÝÌäÌéÌãÌÞÌêÌèÌëÌçã©õ®ç¾ðÃÌàÜèÙÃç°åÑñÓ"},
	{"tian"		,	"ÌìÌïÌîÌðÌíÌóÌòÌñîäãÙî±ãÃéåÞÝ"},
	{"tiao"		,	"Ìõµ÷ÌøÌôÌöÌ÷öæÙ¬Üæñ»÷ØôÐóÔö¶ìöòè"},
	{"tie"		,	"ÌúÌùÌû÷ÑÝÆ"},
	{"ting"		,	"ÌýÍ£Í¥ÌüÍ¦Í¤æÃÍ¢Í§î®öªÍ¡îúòÑÜðèèÝãÌþ"},
	{"tong"		,	"Í¬Í¨Í³Í´Í¯Í®Í²Í­Í°Í±Í©Í«Ù¡âúÍª¶²¶±íÅàÌÙÚÛíÜíá¼äü"},
	{"tou"		,	"Í·Í¶ÍµÍ¸î×÷»"},
	{"tu"		,	"ÍÁÍ»Í¼Í¾Í½ÍÀÍ¿ÍÂÍÃÍºÍ¹Ý±õ©îÊÝËÜ¢"},
	{"tuan"		,	"ÍÅÍÄÞÒî¶åè"},
	{"tui"		,	"ÍÆÍËÍÈÍÊÍÇÍÉß¯ìÕ"},
	{"tun"		,	"ÍÌÍÍâ½ÍÊÍÎ¶ÚëàêÕÙÛ"},
	{"tuo"		,	"ÍÐÍÑÍÏÍ×ÍØÍÓÍÕÍÙÍÖíÈÍÔãûõÉÛçÍÒØ±ö¾éÒÙ¢âÕîèõ¢èÞèØóê"},
	{"wa"		,	"ÍßÍÚÍàÍÞÍÛ°¼æ´ÍÜÍÝØôëð"},
	{"wai"		,	"ÍâÍááË"},
	{"wan"		,	"ÍòÍêÍíÍåÍæÍëÍäÍìÍçÍóÍñÍïÍðÍèòêÝ¸îµØàÍãÍîæýçþëäÍéÜ¹ÝÒçº"},
	{"wang"		,	"ÍûÍõÍùÍøÍüÍöÍôÍúÍ÷Íýã¯ØèÞÌéþ÷Í"},
	{"wei"		,	"ÎªÎ»Î´Î¯Î¬Î¶Î§ÎÀÍþÎ¢Î°Î½Î¨Î£Î¿Î²Î¥ÎºçâÎµÎ±Î·Î¸Î¹ì¿Î¤Î©Î¡Î³Î®æ¸Î­Î¾á¡Î¼â«ÙËÞ±ðôâ¬åÔàøè¸ìÐöÛÎ¦Î«ÚñÛ×àíÚÃÚóáËä¢ÝÚáÍãÇãíä¶ôºê¦"},
	{"wen"		,	"ÎÄÎÊÎÅÎÂÎÈÎÇÎÆÎÃö©ÎÉÎÁãëØØãÓè·"},
	{"weng"		,	"ÎÌÎÍÎËÝîÞ³"},
	{"wo"		,	"ÎÒÎÕÎÑÎÔä×ÎÖÎÐÎÓÎÏá¢à¸ÙÁÎÎÝ«ë¿íÒö»"},
	{"wu"		,	"ÎÞÎåÎïÎñÎäÎçÎèì¶Îó¶ñÎâÎÝÎéÎòÎáÎÛÎÚÎíÎêÎæÎ×ÎãÎØÎÜÎðÎàÎëÎìØ£ßíÎîÎßðÍÎÙåüðíðÄâèå»æðÚùêõ÷ùÛØä´ØõÚãÜÌâÐæÄâäè»ìÉòÚåÃöÈ"},
	{"xi"			,	"Î÷ÏµÏ¢Ï£Ï²Ï¯Ï°Ï¸Ï·ÎüÏ´Ï§Ï¡Ï¤ÎöÏ¦ÎþÏ®ÎôÎõÙâÏªÏ¶ÎûÎýÎúÏ±éØÏ¨Ï¥Û­Ï¬ìûêØÞÉôËõèßñäÀæÒðªÏ«áãÜççôìäÏ©ôâó¬åïÏ­ä»ÙÒñ¶òáÚôêêó£Ï³Ý¾ÝßÝûô¸ÎùôÑÎøõµì¤÷ûì¨â¾ãÒìùôª"},
	{"xia"		,	"ÏÂÏÄÏÅÏ¿ÏÃÏÀÏÁÏ¼Ï¹Ï¾Ïº»£Ï½åÚÏ»÷ïè¦ßÈáòèÔíÌðýóÁ"},
	{"xian"		,	"ÏÖÏÈÏÔÏßÏÕÏÞÏØÏÊÏ×ÏÐÏÜÏÝÏÍÏÉÏÓÏÌÏÛÏÆÏÒÏËæµÏÎÏÚÏÑÏÏÏÙõÐåßá­áýò¹óÚõÑÝ²ÏÇðÂðïÏ³ë¯ììôÌÙþÞºõ£ÜÈìÞö±"},
	{"xiang"		,	"ÏëÏàÏòÏóÏãÏçÏñÏìÏîÏí½µÏäÏêÏéÏïÏáÏæÏðÏèÏâ÷ÏÏåâÃæøÝÙâÔößÜ¼ç½ó­"},
	{"xiao"		,	"Ð¡Ð¦Ð£ÏûÐ§ÏþÏúäìÐ¤ÏôÐ¢ÏüÏ÷ÏùÐ¥åÐÏõÏöÏýÏøèÉæçóïóãßØèÕç¯÷ÌòÙáÅ"},
	{"xie"		,	"Ð©Ð´Ð»Ð­Ð¬Ð¯Ð±Ð¹Ð²ÐªÐ³Ð°ÐµÐ¼Ð¶Ð®Ð¸ÐºÙôÐ·ÙÉåâé¿ß¢Ð¨å¬Ð«ò¡ÛÄÞ¯ÛÆõóçÓâ³ç¥âÝéÇäÍ"},
	{"xin"		,	"ÐÄÐÂÐÅÐÀÐÁÐ½Ü°öÎÐ¾ÐÆê¿ÐÃÐ¿ì§ïâØ¶"},
	{"xing"		,	"ÐÐÐÔÐÎÐËÐÇÐÍÐÕÐÒÐÌÐÑÐÈÐÓã¬ÐÊÐÏÐÉÜôß©Üþâ¼íÊÚê"},
	{"xiong"		,	"ÐÛÐÖÐØÐ×ÐÜÐÙÐÚÜº"},
	{"xiu"		,	"ÐÞÐÝÐãÐäËÞ³ôÐßÐåÐàÐâÐáßÝõ÷÷ÛâÊâÓð¼á¶äå"},
	{"xu"		,	"ÐíÐøÐèÐëÐìÐòÐéÐ÷ÓõÐîÐðÐóÐêÐôÐõä°ÐæÐñÐöèòÐçÚ¼ñãÐïìãí¹íìôÚõ¯çïÛÃäªäÓÛ×Þ£"},
	{"xuan"		,	"Ñ¡ÐûÐýÐüÈ¯ÐúÐùÐþìÅäÖÑ¤Ñ£ÝæäöêÑè¯ÚÎîçÙØðçãùìÓé¸Ñ¢íÛÞïïà"},
	{"xue"		,	"Ñ§ÑªÑ©Ï÷Ñ¨ÚÊÑ¥Ñ¦õ½àåí´÷¨"},
	{"xun"		,	"Ñ°Ñ¯ÑµÑ¸Ñ¶Ñ²Ñ·Ñ­Ñ®Ñ¬Ñ«Ñ±»çÑ³õ¸ÙãáßÛ÷Ü÷á¾ä­Þ¹Ñ´Û¨êÖñ¿âþâ´ä±öàÞ¦¿£"},
	{"ya"		,	"ÑÇÑ¹ÑÅÑÀÑ½ÑºÑÄÑÈÑ»ÑÆÑ¼ÑÂÑ¾Ñ¿ÑÃÔþðéíýæ«ÑÁØóñâá¬çðÛëÞëåÂèâë²í¼"},
	{"yan"		,	"ÑÛÑÔÑÏÑÝÑÐÑÌÑéÑÓÑØÑÚÑÕÑáÑ×ÑàÑÖÑçÑÎÑÊÑÒÑãÑæÑÞÑÉÑÍÑÜÑËÑÙÑèÙ²éÜÑÑÑåëçìÍêÌÑäåûÑâæÌëÙäÎóÛÑßØÍ÷Ð÷úÜ¾ÙÈ÷ÊãÆáÃØÉØßâûãÕÙðÛ±çüî»Û³ÚÝäÙÚç÷üõ¦ÝÎ"},
	{"yang"		,	"ÑùÑóÑôÑëÑîÑøÑïÑöÑòÑ÷ÑúãóÑõÑìÑíÑêí¦ÑñìÈÑð÷±âóáàì¾òÕ"},
	{"yao"		,	"ÒªÒ¡Ò©Ò«Ò£ÑûÑüÒ¦Ò§Ò¢Ò¥ÑþÒ¤Ø²ëÈÑýßºÔ¿½ÄèÃñºðÎê×Ò¨ï¢çÛØ³áæôí÷¥çòé÷áÊ"},
	{"ye"		,	"Ò²ÒµÒ¹Ò¯Ò¶Ò°Ò³ÒºÒ®ÑÊÒ·×§ÞÞÒ­ìÇÒ±Ò¬Ò´Ò¸ÚËÚþØÌêÊîô"},
	{"yi"			,	"Ò»ÒÔÒâÒÑÒåÒéÒ½Ò×ÒÂÒÕÒÀÒëÒÆÒìÒæÒàÒÚÒÉÒÅÒäÒËÒÎÒÁÒÇÒêÒÖÒíÒÓÒÛ°¬ÒÒÒçÒãÉßÒáÒÝÒÌÒÄéóâùÒÏÞÄÒÐÒîÒÃÒßÒïÒÍß×ØýÞÈìÚêÝäôÒèåÆß®Ü²ß½æäßÞÒ¾ì½ÒÙðêÞ²àæï×Ø×ÒÊÒÜçËÒØÒÈâ¢ôàîÆô¯ØæØîôýÙ«ÛüÚ±ÛÝÜèÒ¼ÞÚáÚâÂàÉá»âøã¨Ò¿ì¥éì÷ðÜÓÒÞïîðùñ¯ñ´òæíôôè"},
	{"yin"		,	"ÒòÒôÒýÓ¡ÒøÒþÒûÒõÒöñ«Ò÷ÒúÒóÒùÒðÒñÒüò¾Ûóà³äÎØ·Û´ë³ö¯Ûßî÷áþßÅâ¹Ü§ö¸ä¦Üáñ¿"},
	{"ying"		,	"Ó¦Ó¢Ó°ÓªÓ­Ó²Ó³Ó®Ó¯Ó±Ó¥Ó¤Ó¬Ó£Ó¨Ó«âßÓ©ÝÓÝºó¿å­éºÓ§ò£ÙøðÐçøÜãàÓè¬ÜþÞüÛ«ñ¨ÝöäÞäëëô"},
	{"yo"		,	"Ó´à¡"},
	{"yong"		,	"ÓÃÓÀÓµÓÂÓ¿Ó»Ó¾Ó¹Ó¶Ó½Ù¸ÓºÓÁð®Ó·çßïÞÓ¸ÛÕ÷«÷Óà¯Ü­Ó¼ã¼"},
	{"you"		,	"ÓÐÓÖÓÉÓÑÓÎÓÒÓÍÓÅÓÊÓÄÓÈÓÇÓÌÓÆÓ×ÓÕÓÓ÷îØüßÏÓÏèÖöÏÝ¬àó÷øÓËØÕéàë»îððàòÄòöÓÔòøôíÝ¯Ù§Ýµå¶òÊÞÌ"},
	{"yu"		,	"ÓÚÓëÓïÓýÓàÓöÓüÓêì¶ÓûÔ¤ÓèÓãÓñÓúÓòÓþÓõÓîÔ¢Ô¥ÓÞÓßÖàÓôÓ÷ÓðÓéÔ£ÓäÓíÔ¡âÅÓùÓâÓæÓåÓáÝÇè¤ÓçÔ¦ÓØÞíàôÚÍÓÜÓìÓÙØ¹ÓÝØ®ÚÄåýëéÓøóÄÓóæ¥ô§ì£ö¹êìÓÛêÅìÏìÙìÛñ¾òõáÎáüØñÙ¶ô¨àöâ×ÝÒÝ÷âÀãÐå÷ðõñÁö§ðöæúí²îÚðÁðÖòâ"},
	{"yuan"		,	"Ô±ÔªÔ­ÔºÔ¶Ô¸Ô°Ô´Ô²Ô¹ÔµÔ®Ô©Ô¬Ô¨Ô·Ô³Ô§Ô¯Ô«æÂãäéÚÜ¾ë¼ó¢ö½íóà÷ð°óîÜ«ÛùÞòè¥"},
	{"yue"		,	"ÔÂÀÖÔ½Ô¼ÔÄÔ¾Ô»ÔÃÔÀÔÁÔ¿ë¾å®èÝéÐÙßîá"},
	{"yun"		,	"ÔËÔÆÔÊÔÏÔÎÔÐÔÈÔÌÔÍóÞÜ¿ÔÅÔÉç¡éæã³ëµáñìÙÛ©ã¢êÀè¹ÔÇ"},
	{"za"		,	"ÔÓÔúÔÒÕ¦ßÆÔÑÞÙ"},
	{"zai"		,	"ÔÚÔÙÔØÔÖ×ÐÔ×ÔÕÔÔáÌçÞ"},
	{"zan"		,	"ÔÛÔÞÔÝÔÜô¢ôØè¶ÞÙêÃôõöÉ"},
	{"zang"		,	"²ØÔàÔáÔßê°ÕàÞÊæà"},
	{"zao"		,	"ÔçÔìÔâÔãÔèÔîÔêÔëÔäÔæÔíÔïÔéÔåçØßð"},
	{"ze"		,	"ÔòÔðÔóÔñÕ¦ßõØÆåÅóÐóåô·àýØÓê¾"},
	{"zei"		,	"Ôô"},
	{"zen"		,	"ÔõÚÚ"},
	{"zeng"		,	"ÔöÔùÔ÷çÕîÀêµï­"},
	{"zha"		,	"Õ¨ÔúÕ¦Õ©Õ§Õ£ÔüÔýÕ¤ÔþÕ¢Õ¥ÔûÞê×õé«ßîß¸Õ¡íÄ÷þßåðäòÆ"},
	{"zhai"		,	"ÕªÕ®Õ¬Õ­Õ«Õ¯µÔíÎñ©"},
	{"zhan"		,	"Õ½Õ¹Õ¾Õ¼Õ´Õ¶Õ·Õ³ÕµÕ¸Õ°ÕÀÕºÕ¿Õ²Õ±Õ»ÚÞÞøì¹"},
	{"zhang"		,	"³¤ÕÅÕÂÕÉÕÆÕÇÕÊÕÏÕËÕÍÕÌÕÈÕÃè°ó¯ÕÁÕÎÕÄáÖÛµâ¯Øëá¤æÑ"},
	{"zhao"		,	"×ÅÕÒÕÕÕÐ³¯ÕÔÕÙÕÖÕ×ÕÑÕØÕÓÚ¯îÈßúèþóÉ"},
	{"zhe"		,	"Õâ×ÅÕßÕÛÕÜÕãÕÚÕÞéüÚØÕáÕÝñÞðÑÕàíÝß¡òØô÷èÏ"},
	{"zhen"		,	"ÕæÕóÕòÕðÕëÕäÛÚÕñÕïÕíÕåÕêÕìêâÕçÕéóðÕîÕèèåçÇî³éôëÓð¡ìõä¥äÚÝèé©é»ëÞð²"},
	{"zheng"		,	"ÕþÕýÖ¤ÕûÕùÕ÷ÕõÖ£Ö¢ÕöáçÕôÕúóÝÕüï£á¿ÕøÚºöëîÛÖ¡"},
	{"zhi"		,	"Ö®Ö»ÖªÖÁÖÆÖ±ÖÎÖ¸Ö§Ö¾Ö°ÖÂÖµÖ¯Ö½Ö¹ÖÊÖ´ÖÇÖÃÖ·Ö¦ÖÈÖ²Ö¼ÖÍáçÖÄÖÉÖ¿Ö­ÖÀÖ³Ö¥Ö¨Ö«Ö¬ÖÅÖ¶ÖÏÖ©ÖºÖËÖÌåëÜÆèÎè×õÜèäàùèÙìíéùêÞðëõôØ´éòÛúÚìÛ¤íéâååéæïõ¥ÞýôêõÅëùïôðºëÕòÎõÙìóö£"},
	{"zhong"		,	"ÖÐÖÖÖØÖÚÖÕÖÓÖÒÖÔÖ×ÖÙïñõàÖÑÚ£âìô±ó®"},
	{"zhou"		,	"ÖÜÖÝÖÞÖàÖÛÖåÖèÖáÖæÖäÖçÖâÖãëÐæûÖßç§æ¨íØßúÝ§ô¦ôíôü"},
	{"zhu"		,	"Ö÷×¡×¢ÖúÖøÖðÖîÖì×¤Öé×£ÖíÖþÖñÖóÖöÖùÖòÖýÖêÖõÖëØùÖôÖüä¨ÖïñÒîùóçÖûÜïìÄõîóÃèÌôãä¾äó÷æéÆéÍÜÑÙªðñðæÛ¥ô¶"},
	{"zhua"		,	"×¥×¦"},
	{"zhuai"		,	"×§àÜ"},
	{"zhuan"		,	"´«×¨×ª×¬×«×©×­ßùâÍò§"},
	{"zhuang"	,	"×°×´×³×¯×²×±´±×®ÞÊÙ×í°"},
	{"zhui"		,	"×·×¹×º×¶×¸ö¿×µã·æíçÄ"},
	{"zhun"		,	"×¼×»ñ¸ëÆ"},
	{"zhuo"		,	"×Å×À×½×¿×Á×Æ×Ã×¾×Çåª×Â×Äí½ïíäÃìÌä·Ù¾ìúÚÂßª"},
	{"zi"			,	"×Ó×Ô×Ö×Ê×É×Ï×Ì×Ð×ËÖ¨×È×Îè÷×Õ×Ñæ¢í§×ÒÚÑö·ïößÚê¢ïÅíöóÊ÷Ú×ÍÜëõþö¤ç»ñèööáÑêßæÜôÒôô"},
	{"zong"		,	"×Ü×Ú×Ý×Ù×Û×ØôÕ××ÙÌëêèÈ"},
	{"zou"		,	"×ß×à×Þ×áæãöíÚÁÚîÛ¸"},
	{"zu"		,	"×é×ã×å×æ×â×è×ä×çÙÞïßÝÏ"},
	{"zuan"		,	"×¬×êß¬×ëõòçÚ"},
	{"zui"		,	"×î×ï×ì×í¾×õþÞ©"},
	{"zun"		,	"×ð×ñé×÷®ß¤"},
	{"zuo"		,	"×÷×ö×ø×ù×ó×ò×Á×ôÔä´é×õàÜâôëÑßòóÐÚèìñõ¡"}
	
};

static char keys[]={
    '1','2','3','4','5','6','7','8','9','0','-','=',
    'q','w','e','r','t','y','u','i','o','p','[',']',
    'a','s','d','f','g','h','j','k','l',';','\'','\\',
    'z','x','c','v','b','n','m',',','.','/','`'
	};
static char keys2[]={
    '!','@','#','$','%','^','&','*','(',')','_','+',
    'Q','W','E','R','T','Y','U','I','O','P','{','}',
    'A','S','D','F','G','H','J','K','L',':','\"','|',
    'Z','X','C','V','B','N','M','<','>','?','~'
};

char* get_match_hz_string(char* pString){
	int i;
	for(i=0;i<MAX_ITEMS;i++){
		if(strcmp(pString, codeTable[i].pPinyin)==0)
			return codeTable[i].pHanzi;
	}
	return NULL;
}

Ret  etk_input_method_pinyin_focus_in(EtkInputMethod* thiz,EtkWidget* editor){
	EtkWidget *win;
	EtkWindowClass *priv;
	EtkEvent e;
	win=(EtkWidget*)thiz->priv;
	priv=(EtkWindowClass*)win->subclass;
	priv->data[0]=editor;
	win->visable=0;
	etk_default_wnd_manager_update_rect(etk_default_wnd_manager(),&win->rect);

	win->visable=1;
	win->rect.x=editor->rect.x;
	win->rect.y=editor->rect.y+editor->rect.height+10;

	etk_event_init(&e, ETK_EVENT_SHOW);
	e.widget = win;
	etk_wnd_manager_dispatch_event(etk_default_wnd_manager(),&e);
	//draw_rect(editor->rect,RED);
	printf("etk_input_method_pinyin_focus_in\n");
}
Ret  etk_input_method_pinyin_focus_out(EtkInputMethod* thiz){
	EtkWidget *win;
	EtkEvent e;
	win=(EtkWidget*)thiz->priv;
	win->visable=0;
	etk_widget_paint(win);
	etk_event_init(&e, ETK_EVENT_HIDE);
	e.widget = win;
	etk_wnd_manager_dispatch_event(etk_default_wnd_manager(),&e);

}
Ret  etk_input_method_pinyin_set_type(EtkInputMethod* thiz, EtkInputType type){
	
}
Ret  etk_input_method_pinyin_handle_event(EtkInputMethod* thiz, EtkEvent* event){
	EtkWidget *win;
	win=(EtkWidget*)thiz->priv;
	etk_input_method_pinyin_on_event(win,event);
}
void etk_input_method_pinyin_destroy(EtkInputMethod* thiz){
	EtkWidget *win;
	win=(EtkWidget*)thiz->priv;
}
void etk_input_method_pinyin_ref(EtkInputMethod* thiz){}
void etk_input_method_pinyin_unref(EtkInputMethod* thiz){}


void etk_input_method_pinyin_create_keys(EtkWidget* thiz){
	e32 i,keynum,x,y,xsize,ysize,xspan,yspan,startx,starty;
	EtkWidget *key;
	EtkWindowClass *priv=(EtkWindowClass*)thiz->subclass;
	x=10;y=35;xspan=yspan=2;
	keynum=sizeof(keys)/sizeof(char);
	xsize=ysize=20;
	startx=x;
	starty=y;
	for(i=0;i<keynum;i++){
		key=etk_button_create_ex(x,y,xsize,ysize,ETK_WIDGET_NO_BITMAP);
		key->canvas->bitmap=thiz->canvas->bitmap;
		if(i==0){
			priv->data[1]=key;
		} 
		etk_widget_append_child((EtkWidget*)priv->data[1],key);
		key->canvas->draw_rect(key->canvas,key->rect.x,key->rect.y,key->rect.width,key->rect.height,key->canvas->gc.fgcolor.color);
		etk_canvas_draw_char_with_color(key->canvas,key->rect.x+8,key->rect.y+3,keys[i],RED,key->canvas->gc.bgcolor.color);
		etk_button_set_data(key,keys[i]);
		//key->event=etk_input_method_pinyin_on_event;
		x=x+xsize+xspan;
		if((i+1)%12==0){
			y=y+ysize+yspan;
			x=startx;
		}
	}
	//backspace
	key=etk_button_create_ex(x+xsize+xspan,35,xsize*2+10,ysize,ETK_WIDGET_NO_BITMAP);
	etk_button_set_data(key,ETK_KEY_BACKSPACE);
	key->canvas->bitmap=thiz->canvas->bitmap;
	etk_widget_append_child((EtkWidget*)priv->data[1],key);
	etk_widget_set_text(key,"<-");
	key->canvas->draw_rect(key->canvas,key->rect.x,key->rect.y,key->rect.width,key->rect.height,key->canvas->gc.fgcolor.color);
	etk_canvas_draw_string_with_color(key->canvas,key->rect.x+8,key->rect.y+3,"<--",RED,key->canvas->gc.bgcolor.color);
	//enter 

	key=etk_button_create_ex(x+xsize+xspan,35+ysize+yspan,xsize*2+10,ysize,ETK_WIDGET_NO_BITMAP);
	etk_button_set_data(key,ETK_KEY_ENTER);
	key->canvas->bitmap=thiz->canvas->bitmap;
	etk_widget_append_child((EtkWidget*)priv->data[1],key);
	etk_widget_set_text(key,"Enter");
	key->canvas->draw_rect(key->canvas,key->rect.x,key->rect.y,key->rect.width,key->rect.height,key->canvas->gc.fgcolor.color);
	etk_canvas_draw_string_with_color(key->canvas,key->rect.x+8,key->rect.y+3,"Enter",RED,key->canvas->gc.bgcolor.color);
	//shift
	key=etk_button_create_ex(x+xsize+xspan,35+(ysize+yspan)*2,xsize*2+10,ysize,ETK_WIDGET_NO_BITMAP);
	etk_button_set_data(key,ETK_KEY_ENTER);
	key->canvas->bitmap=thiz->canvas->bitmap;
	etk_widget_append_child((EtkWidget*)priv->data[1],key);
	etk_widget_set_text(key,"Shift");
	key->canvas->draw_rect(key->canvas,key->rect.x,key->rect.y,key->rect.width,key->rect.height,key->canvas->gc.fgcolor.color);
	etk_canvas_draw_string_with_color(key->canvas,key->rect.x+8,key->rect.y+3,"Shift",RED,key->canvas->gc.bgcolor.color);
	//space
	key=etk_button_create_ex(x+xspan,35+(ysize+yspan)*3,xsize*3+10,ysize,ETK_WIDGET_NO_BITMAP);
	etk_button_set_data(key,ETK_KEY_ENTER);
	key->canvas->bitmap=thiz->canvas->bitmap;
	etk_widget_append_child((EtkWidget*)priv->data[1],key);
	etk_widget_set_text(key,"Space");
	key->canvas->draw_rect(key->canvas,key->rect.x,key->rect.y,key->rect.width,key->rect.height,key->canvas->gc.fgcolor.color);
	etk_canvas_draw_string_with_color(key->canvas,key->rect.x+8,key->rect.y+3,"Space",RED,key->canvas->gc.bgcolor.color);


}

EtkInputMethod *etk_input_method_pinyin_create(){
	EtkWidget *win;
	EtkWindowClass *priv;
	EtkInputMethod *thiz;

	/*EtkBitmap* b;
	EtkRect s,d;
	b=load_jpeg("keyboard.jpg");
	if(b!=NULL){
		s.x=0;s.y=0;
		s.width=b->w;
		s.height=b->h;
		d.x=0;
		d.y=30;d.width=b->w;d.height=b->h;
	}
	win=etk_create_window(100,100,s.width,s.height+30,ETK_WIDGET_WINDOW);
	etk_canvas_draw_bitmap(win->canvas,b,&s,&d,0x00);*/
	win=etk_create_window(100,100,330,100+30,ETK_WIDGET_WINDOW);

	priv=(EtkWindowClass*)win->subclass;
	priv->has_head=0;
	win->paint=etk_input_method_pinyin_on_paint;
	win->event=etk_input_method_pinyin_on_event;
	win->visable=2;	
	etk_input_method_pinyin_create_keys(win);
	etk_widget_paint(win);

	thiz=(EtkInputMethod *)ETK_MALLOC(sizeof(EtkInputMethod));
	thiz->destroy=etk_input_method_pinyin_destroy;
	thiz->focus_in=etk_input_method_pinyin_focus_in;
	thiz->focus_out=etk_input_method_pinyin_focus_out;
	thiz->handle_event=etk_input_method_pinyin_handle_event;
	thiz->name="pinyin";
	thiz->priv=win;

	return thiz;
}


Ret etk_input_method_pinyin_on_paint(EtkWidget* thiz){
	EtkWindowClass * priv=(EtkWindowClass *)thiz->subclass;
	EtkWidget *child=(EtkWidget *)priv->data[1];
	while(child!=NULL){
		child->paint(child);
		//child->canvas->draw_rect(child->canvas,child->rect.x,child->rect.y,child->rect.width,child->rect.height,RED);
		child=child->next;
	}

	etk_canvas_paint(thiz->display,thiz->canvas,&thiz->rect);
	etk_canvas_draw_rect(thiz->canvas,1,1,thiz->rect.width-2,25,thiz->canvas->gc.fgcolor.color);
	etk_canvas_draw_rect(thiz->canvas,1,30,thiz->rect.width-2,thiz->rect.height-31,thiz->canvas->gc.fgcolor.color);
	printf("etk_input_method_pinyin_on_paint\n");
}

Ret etk_input_method_on_mouse_event(EtkWidget* thiz, EtkEvent* event){
	EtkWindowClass *priv;
	EtkWidget *button;
	if(thiz==NULL||event==NULL)
		return;
	priv=(EtkWindowClass*)thiz->subclass;
	
	if(event->type==ETK_EVENT_MOUSE_UP){
		EtkRect r;
		r.width=2;
		r.height=2;
		r.x=event->u.mouse.x-thiz->rect.x;
		r.y=event->u.mouse.y-thiz->rect.y;
	
		button=(EtkWidget*)priv->data[1];
		while(button!=NULL){
			if(is_rect_cross(button->rect,r)){
				EtkEvent e;
				EtkWidget *editor=(EtkWidget *)priv->data[0];
				printf("button:%x\n",etk_button_get_data(button));
				//etk_entry_insert_text(editor,etk_widget_get_text(button));
				etk_event_init(&e,ETK_EVENT_KEY_DOWN);
				e.widget=editor;
				e.u.key.code=etk_button_get_data(button);
				etk_widget_event(editor,&e);
			}
			button=button->next;
		}
		//etk_canvas_draw_string(thiz->canvas,3,5,get_match_hz_string("zuo"));
		
	}else if(event->type==ETK_EVENT_MOUSE_DOWN){
		//etk_canvas_draw_string(thiz->canvas,3,5,get_match_hz_string("a"));
	}

	return RET_OK;
}


Ret etk_input_method_pinyin_on_event(EtkWidget* thiz, EtkEvent* event){
	EtkWindowClass *priv=(EtkWindowClass*)thiz->subclass;
	Ret ret;
	EtkEvent e;
	if(event==NULL)
		return;
	//printf("etk_input_method_pinyin_on_event\n");
	switch(event->type){
	case ETK_EVENT_UPDATE:
		etk_widget_paint_all(thiz);
		//etk_window_update(thiz,&event->u.rect);
		break;
	case ETK_EVENT_MOVE_RESIZE:
		if(etk_widget_is_visible(thiz)){
			etk_wnd_manager_update(etk_default_wnd_manager());
		}
		break;
	case ETK_EVENT_SHOW:
		etk_widget_paint(thiz);
		etk_event_init(&e, ETK_EVENT_SHOW);
		e.widget = thiz;
		etk_wnd_manager_dispatch_event(etk_default_wnd_manager(),&e);
		break;
	case ETK_EVENT_HIDE:
		
		etk_event_init(&e, ETK_EVENT_HIDE);
		e.widget = thiz;
		etk_wnd_manager_dispatch_event(etk_default_wnd_manager(), &e);
		break;
	
	case ETK_EVENT_MOUSE_DOWN:
	case ETK_EVENT_MOUSE_UP:
			ret = etk_input_method_on_mouse_event(thiz,event);
			break;
	default:
		break;
	}
}















