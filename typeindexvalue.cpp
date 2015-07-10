#include "typeindexvalue.h"

TypeIndexValue::TypeIndexValue()
{
    initType();
    initLanguage();
    initVersion();
    initEffect();
    initResolution();
    initQuality();
    initSource();
    initRhythm();
    initPitch();

    initNation();
    initSex();

    initMatch();
    initEnabled();
    initTrack();
    initStars();
}

TypeIndexValue::~TypeIndexValue()
{

}

void TypeIndexValue::initType()
{
    type.insert(0, "全部");
    type.insert(1, "甜蜜恋曲");
    type.insert(2, "情歌对唱");
    type.insert(3, "民族歌曲");
    type.insert(4, "经典红歌");
    type.insert(5, "劲爆舞曲");
    type.insert(6, "儿童歌曲");
    type.insert(7, "戏曲片段");
    type.insert(8, "怀旧金曲");
    type.insert(9, "乐曲钢琴");
    type.insert(10, "生日庆典");
    type.insert(11, "中国好声音");
    type.insert(12, "中国最强音");
    type.insert(13, "我为歌狂");
    type.insert(14, "我是歌手");

    type.insert(15, "中国梦之声");
    type.insert(16, "中国好歌曲");
    type.insert(17, "梦想星搭挡");
    type.insert(18, "Dj舞曲");
    type.insert(19, "影视类");
    type.insert(20, "亲情类");
    type.insert(21, "友情类");
    type.insert(22, "苦情歌");
    type.insert(23, "网络神曲");
    type.insert(24, "古风");
    type.insert(25, "校园民谣");
    type.insert(26, "励志");
    type.insert(27, "流行");
}

void TypeIndexValue::initLanguage()
{
    language.insert(0, "全部");
    language.insert(1, "国语");
    language.insert(2, "粤语");
    language.insert(3, "闽南语");
    language.insert(4, "英语");
    language.insert(5, "日语");
    language.insert(6, "韩语");
    language.insert(7, "其他");
}

void TypeIndexValue::initVersion()
{
    version.insert(0, "全部");
    version.insert(1, "MTV");
    version.insert(2, "演唱会");
    version.insert(3, "影视剧");
    version.insert(4, "FLASH");
    version.insert(5, "欣赏版");
    version.insert(6, "高清");
    version.insert(7, "非原人");
}

void TypeIndexValue::initEffect()
{
    effect.insert(0, "全部");
    effect.insert(1, "抒情");
    effect.insert(2, "轻快");
    effect.insert(3, "劲爆");
}

void TypeIndexValue::initResolution()
{
    resolution.insert(0, "全部");
    resolution.insert(1, "1080以上");
    resolution.insert(2, "1080-720");
    resolution.insert(3, "720-480");
    resolution.insert(4, "480以下");
}

void TypeIndexValue::initQuality()
{
    quality.insert(0, "全部");
    quality.insert(1, "好");
    quality.insert(2, "伴有原唱");
    quality.insert(3, "差");
    quality.insert(4, "无原唱");
    quality.insert(5, "无伴奏");
}

void TypeIndexValue::initSource()
{
    source.insert(0, "全部");

    source.insert(1, "视翰");
    source.insert(2, "天王");
    source.insert(3, "宝声");
    source.insert(4, "新势力");

    source.insert(5, "百乐迪");
    source.insert(6, "搜米");
    source.insert(7, "华谊");
    source.insert(8, "太合麦田");
    source.insert(9, "恒大");
}

void TypeIndexValue::initRhythm()
{
    rhythm.insert(0, "全部");

    rhythm.insert(1, "慢（60-96）");
    rhythm.insert(2, "中（96-124）");
    rhythm.insert(3, "快（124-150）");
    rhythm.insert(4, "超快（150-240）");
}

void TypeIndexValue::initPitch()
{
    pitch.insert(0, "全部");

    pitch.insert(1, "中低音");
    pitch.insert(2, "中高音");
    pitch.insert(3, "高音");
    pitch.insert(4, "海豚音");
}

void TypeIndexValue::initNation()
{
    nation.insert(0, "全部");

    nation.insert(1, "大陆");
    nation.insert(2, "港台");
    nation.insert(3, "欧美");
    nation.insert(4, "日韩");
    nation.insert(5, "其他");
}

void TypeIndexValue::initSex()
{
    sex.insert(0, "全部");

    sex.insert(1, "男");
    sex.insert(2, "女");
    sex.insert(3, "组合");
    sex.insert(4, "其他");
}

void TypeIndexValue::initMatch()
{
    match.insert(0, "全部");
    match.insert(1, "是");
    match.insert(2, "否");
}

void TypeIndexValue::initEnabled()
{
    enabled.insert(0, "全部");
    enabled.insert(1, "启用");
    enabled.insert(2, "禁用");
}

void TypeIndexValue::initTrack()
{
    track.insert(0, "0");
    track.insert(1, "1");
}

void TypeIndexValue::initStars()
{
    stars.insert(0,"全部");
    stars.insert(1,"5.0");
    stars.insert(2,"4.5");
    stars.insert(3,"4.0");
    stars.insert(4,"3.5");
    stars.insert(5,"3.0");
    stars.insert(6,"2.5");
    stars.insert(7,"2.0");
    stars.insert(8,"1.5");
    stars.insert(9,"1.0");
    stars.insert(10,"0.5");
    stars.insert(11,"0.0");
}

