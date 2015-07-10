#ifndef SQLCOLUMNENUM
#define SQLCOLUMNENUM

#define SHADOW_WIDTH            5
#define WINDOW_WIDTH            680
#define WINDOW_HEIGHT           372
#define WINDOW_START_X          0
#define WINDOW_START_Y          0
#define WINDOW_PAGE_COUNT       4
#define WINDOW_BUTTON_COUNT     4
#define WINDOW_PAGE_MOVE        20
#define WINDOW_ONEBUTTON_WIDTH  170
#define DEFAULT_SKIN            ":/skin/17_big"

enum checkBoxStatus{
    checkBox_normal=10,
    checkBox_select=20,
    checkBox_disabled=30,

    icon_normal=40,
    icon_pressed=50
};


enum actor{
    act_sid = 0,
    act_serial_id,
    act_name,
    act_stars,
    act_nation,
    act_sex,
    act_pinyin,
    act_header,
    act_head,
    act_words,
    act_song_count,
    act_count,
    act_order,
    act_enable,
    act_black,
    act_info
};

enum actorView{
    actView_image=0,
    actView_serial_id,
    actView_name,
    actView_sex,
    actView_nation,
    actView_pinyin,
    actView_words
};


enum actorName{
    actName_id = 0,
    actName_nation,
    actName_detail
};

enum actorType{
    actType_id = 0,
    actType_name,
    actType_detail
};

enum media{
    med_mid = 0,
    med_serial_id,
    med_name,
    med_language,
    med_type,
    med_singer,
    med_artist_sid_1,
    med_artist_sid_2,
    med_pinyin,
    med_header,
    med_head,
    med_words,
    med_path,
    med_lyric,
    med_original_track,
    med_sound_track,
    med_start_volume_1,
    med_start_volume_2,
    med_prelude,
    med_stars,
    med_hot,
    med_count,
    med_enabled,
    med_black,
    med_match,
    med_info
};

enum mediaView{
    medView_serial_id = 0,
    medView_name,
    medView_singer,
    medView_language,
    medView_type,
    medView_original_sound_track,
    medView_enabled,

    medView_path,
    medView_mid,
};

enum mediaQueryCondition{    
    MQC_language = 1,
    MQC_type,
    MQC_resolution,
    MQC_quality,
    MQC_source,
    MQC_version,
    MQC_rthym,
    MQC_pitch
};

enum mediaLanguage{
    medLan_id = 0,
    medLan_name,
    medLan_detail
};

enum mediaType{
    medType_id = 0,
    medType_name,
    medType_detail
};

enum musicList{
    music_no = 0, //序号
    music_name,
    music_singer,
    music_language,
    music_type,
    music_mid,
    music_index
};

enum actorBlack{
    actBlack_check = 0,
    actBlack_image,
    actBlack_name,
    actBlack_sex,
    actBlack_nation,
    actBlack_edit,
    actBlack_sid
};

enum FMList{
    fmList_id=0,
    fmList_name,
    fmList_singer,
    fmList_language,
    fmList_type,
    fmList_edit,
    fmList_mid,
    fmList_lid
};

enum FMLintIndex{
    fmIndex_01 = 0,
    fmIndex_02,
    fmIndex_03
};

enum mediaBlack{
    medBlack_check = 0,
    medBlack_name,
    medBlack_singer,
    medBlack_language,
    medBlack_type,
    medBlack_edit,
    medBlack_mid,
    medBlack_sid1,
    medBlack_sid2,
    medBlack_path,
    medBlack_count
};

enum mediaList{
    medList_check = 0,
    medList_id , //自定义序号
    medList_name,
    medList_singer,
    medList_language,
    medList_type,
    medList_mid,
    medList_enabled
};

enum listWidgetItem{
    widItem_LibTotal=0,
    widItem_songsLib,
    widItem_songs,
    widItem_singer,
    widItem_songsLibOnline,
    widItem_songsOnline,
    widItem_singerOnline,
    widItem_list,
    widItem_listNew,
    widItem_listChinese,
    widItem_listHot,
    widItem_listNet,
    widItem_listHi,
    widItem_listbillboard,
    widItem_FM,
    widItem_AD,
    widItem_black,
    widItem_blackMusic,
    widItem_blackSinger,
    widItem_setInfo,
    widItem_songsInfo,
    widItem_singerInfo,
    widItem_listInfo
};

enum stackedWidgetItem{
    stacked_total = 0,
    stacked_mediaquery=1,
    stacked_actorquery=2,
    stacked_mediaonline=3,
    stacked_actoronline=4,
    stacked_medialist=5,
    stacked_medialistHN=6,
    stacked_FMlist=7,
    stacked_adlist=8,
    stacked_mediablack=9,
    stacked_actorblack=10,
    stacked_setmediainfo=11,
    stacked_setactorinfo=12,
    stacked_setlistinfo=13
};

enum setInfoList{

    infoList_no=0,
    infoList_type,
    infoList_edit

};




#endif // SQLCOLUMNENUM

