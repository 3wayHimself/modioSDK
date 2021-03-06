#include "c/schemas/ModioComment.h"

extern "C" {
void modioInitComment(ModioComment *comment, json comment_json)
{
    comment->id = 0;
    if (modio::hasKey(comment_json, "id"))
        comment->id = comment_json["id"];
    
    comment->mod_id = 0;
    if (modio::hasKey(comment_json, "mod_id"))
        comment->mod_id = comment_json["mod_id"];

    comment->date_added = 0;
    if (modio::hasKey(comment_json, "date_added"))
        comment->date_added = comment_json["date_added"];
    
    comment->reply_id = 0;
    if (modio::hasKey(comment_json, "reply_id"))
        comment->reply_id = comment_json["reply_id"];
    
    comment->karma = 0;
    if (modio::hasKey(comment_json, "karma"))
        comment->karma = comment_json["karma"];
    
    comment->karma_guest = 0;
    if (modio::hasKey(comment_json, "karma_guest"))
        comment->karma_guest = comment_json["karma_guest"];

    comment->reply_position = NULL;
    if (modio::hasKey(comment_json, "reply_position"))
    {
        std::string reply_position_str = comment_json["reply_position"];
        comment->reply_position = new char[reply_position_str.size() + 1];
        strcpy(comment->reply_position, reply_position_str.c_str());
    }
    
    comment->content = NULL;
    if (modio::hasKey(comment_json, "content"))
    {
        std::string content_str = comment_json["content"];
        comment->content = new char[content_str.size() + 1];
        strcpy(comment->content, content_str.c_str());
    }

    json submitted_by_json;
    if(modio::hasKey(comment_json, "submitted_by"))
      submitted_by_json = comment_json["submitted_by"];
    modioInitUser(&(comment->submitted_by), submitted_by_json);
}

void modioFreeComment(ModioComment *comment)
{
    if (comment)
    {
        //No pointers
    }
}
}
