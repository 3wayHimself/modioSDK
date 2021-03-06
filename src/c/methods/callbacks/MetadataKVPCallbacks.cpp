#include "c/methods/callbacks/MetadataKVPCallbacks.h"

std::map< u32, GetMetadataKVPParams* > get_metadata_kvp_callbacks;
std::map< u32, AddMetadataKVPParams* > add_metadata_kvp_callbacks;
std::map< u32, DeleteMetadataKVPParams* > delete_metadata_kvp_callbacks;

void modioOnGetMetadataKVP(u32 call_number, u32 response_code, json response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;

  ModioMetadataKVP* metadata_kvp_array = NULL;
  u32 metadata_kvp_array_size = 0;
  if(response.code == 200)
  {
    try
    {
      if(modio::hasKey(response_json, "data"))
      {
        metadata_kvp_array_size = (u32)response_json["data"].size();
        metadata_kvp_array = new ModioMetadataKVP[metadata_kvp_array_size];
        for(u32 i=0; i<metadata_kvp_array_size; i++)
        {
          modioInitMetadataKVP(&(metadata_kvp_array[i]), response_json["data"][i]);
        }
      }
    }catch(json::parse_error &e)
    {
      modio::writeLogLine(std::string("Error parsing json: ") + e.what(), MODIO_DEBUGLEVEL_ERROR);
    }
  }
  get_metadata_kvp_callbacks[call_number]->callback(get_metadata_kvp_callbacks[call_number]->object, response, metadata_kvp_array, metadata_kvp_array_size);
  for(u32 i=0; i<metadata_kvp_array_size; i++)
  {
    modioFreeMetadataKVP(&(metadata_kvp_array[i]));
  }
  if(metadata_kvp_array)
    delete[] metadata_kvp_array;
  delete get_metadata_kvp_callbacks[call_number];
  get_metadata_kvp_callbacks.erase(call_number);
}

void modioOnAddMetadataKVP(u32 call_number, u32 response_code, json response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;

  add_metadata_kvp_callbacks[call_number]->callback(add_metadata_kvp_callbacks[call_number]->object, response);
  delete add_metadata_kvp_callbacks[call_number];
  add_metadata_kvp_callbacks.erase(call_number);
}

void modioOnDeleteMetadataKVP(u32 call_number, u32 response_code, json response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;

  delete_metadata_kvp_callbacks[call_number]->callback(delete_metadata_kvp_callbacks[call_number]->object, response);
  delete delete_metadata_kvp_callbacks[call_number];
  delete_metadata_kvp_callbacks.erase(call_number);
}
