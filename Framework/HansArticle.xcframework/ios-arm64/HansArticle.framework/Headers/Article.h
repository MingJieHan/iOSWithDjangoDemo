//
//  Article.h
//  iOSWithDjango
//
//  Created by jia yu on 2020/12/20.
//

#ifndef Article_h
#define Article_h


//Keys json data from server
#define ARTICLE_TITLE @"title"
#define ARTICLE_TEXT @"text"
#define ARTICLE_READED @"readed"
#define ARTICLE_LIKED @"liked"
#define ARTICLE_COMMENT_COUNT @"comment"
#define ARTICLE_OPEN_COMMENT @"open_comment"
#define ARTICLE_DATE @"modifie_date"
#define ARTICLE_ID @"id"
#define ARTICLE_AUTH_ID @"auth_id"
#define ARTICLE_AUTH_NAME @"auth_name"
#define ARTICLE_URL @"url"
#define ARTICLE_IMAGES @"images"
#define ARTICLE_VIDEOS @"videos"
#define ARTICLE_FILES @"files"
#define ARTICLE_MP3S @"mp3s"
#define ARTICLE_COMMENTS @"comments"
#define ARTICLE_SHOW_HTML @"show_html"

#define KEY_MORE_INFOLIST_URL = "more_url"

#define KEY_IMAGE_ID @"id"
#define KEY_IMAGE_URL @"image"
#define KEY_IMAGE_THUMBNAILURL @"thumbnail"
#define KEY_IMAGE_TEXT @"text"
#define KEY_IMAGE_MODIFIED @"modifie_date"
#define KEY_IMAGE_WIDTH @"image_width"
#define KEY_IMAGE_HEIGHT @"image_height"

#define KEY_TITLE @"title"
#define KEY_TEXT @"text"
#define KEY_IMAGES @"images"
#define KEY_VIDEOS @"videos"
#define KEY_FILES @"files"
#define KEY_MP3S @"mp3s"

#define KEY_COMMENT_AUTH_ID @"auth_id"
#define KEY_COMMENT_DATE @"date"
#define KEY_COMMNET_TEXT @"text"

#define KEY_VIDEO_ID @"id"
#define KEY_VIDEO_WIDTH @"video_width"
#define KEY_VIDEO_HEIGHT @"video_height"
#define KEY_VIDEO_TEXT @"text"
#define KEY_VIDEO_URL @"video"
#define KEY_VIDEO_DURATION @"duration"
#define KEY_VIDEO_THUMBNAIL @"thumbnail"

#define KEY_FILE_ID @"id"
#define KEY_MP3_ID @"id"

//URLs path
#define PATH_ALL_ARTICLES @"/article/articles_json.html"
#define PATH_MY_ARTICLES @"/article/my_articles_json.html"
#define PATH_ARTICLE_UPDATE @"/article/update_article_json.html"
#define PATH_LIKE_ARTICLE @"/article/like_article_json.html?id="
#define PATH_ARTICLE_SENT_COMMENT @"/article/json_add_comment.html?id="
#define PATH_REMOVE_ARTICLE @"/article/remove?id="

//About MP3
#define PATH_REMOVE_MP3 @"article/mp3_remove?id="
#define ADD_MP3_PATH @"article/mp3_update"
#define PATH_UPDATE_MP3_VALUE @"article/mp3_update?id="
#define PATH_UPDATE_MP3_TEXT @"article/mp3_update?id="


//About File
#define PATH_REMOVE_FILE @"article/file_remove?id="
#define ADD_FILE_PATH @"article/file_update"
#define PATH_UPDATE_FILE_VALUE @"article/file_update?id="
#define PATH_UPDATE_FILE_TEXT @"article/file_update?id="

//About Image
#define PATH_REMOVE_IMAGE @"article/image_remove?id="
#define ADD_IMAGE_PATH @"article/image_update"
#define PATH_UPDATE_IMAGE_VALUE @"article/image_update?id=" //????????????????????????
#define PATH_UPDATE_IMAGE_TEXT @"article/image_update?id="  //??????????????????

//About Video
#define PATH_REMOVE_VIDEO @"article/video_remove?id="
#define PATH_ADD_VIDEO @"article/video_update"
#define PATH_UPDATE_VIDEO @"article/video_update?id="

#define ADD_VIDEO_VIDEO_POST_FILE_NAME @"video.mp4"
#define ADD_VIDEO_THUMBNAIL_FILE_NAME @"thumbnail.jpg"
#define ITEM_KEY_TEXT @"text"
#define ITEM_KEY_LONGITUDE @"longitude"
#define ITEM_KEY_LATITUDE @"latitude"
#define ITEM_KEY_ALTITUDE @"altitude"
#define ADD_VIDEO_VIDEO_DURATION @"duration"


//POST GET send to server Keys
#define IMAGE_VIDEO_ARTICLEID_KEY @"article_id"
#define ADD_IMAGE_IMAGE_FILE_KEY @"image.jpg"
#define ADD_FILE_FILE_KEY @"file.dat"
#define ADD_MP3_FILE_KEY @"abc.mp3"
#define KEY_MP3_DURATION @"duration"
#define KEY_MP3_SIZE @"size"
#define KEY_FILE_NAME_REALNAME @"filename"
#define KEY_FILE_SIZE @"size"
#define KEY_FILE_URL @"file"

#define KEY_MP3_URL @"mp3"

//Other Keys
#define NOTIFICATION_KEY_UPDATE @"NOTIFICATION_KEY_UPDATE"
#define NOTIFICATION_KEY_NEW_ARTICLE @"NOTIFICATION_KEY_NEW_ARTICLE"


#endif /* Article_h */
