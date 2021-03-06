#include "c/methods/callbacks/AuthenticationCallbacks.h"

std::map< u32,EmailRequestParams* > email_request_params;
std::map< u32,EmailExchangeParams* > email_exchange_params;

void modioOnEmailRequested(u32 call_number, u32 response_code, json response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;

  email_request_params[call_number]->callback(email_request_params[call_number]->object, response);
  delete email_request_params[call_number];
  email_request_params.erase(call_number);
  modioFreeResponse(&response);
}

void modioOnEmailExchanged(u32 call_number, u32 response_code, json response_json)
{
  ModioResponse response;
  modioInitResponse(&response, response_json);
  response.code = response_code;
  if(response.code == 200)
  {
    modio::ACCESS_TOKEN = response_json["access_token"];
    json token_json;
    token_json["access_token"] = response_json["access_token"];
    modio::writeJson(modio::getModIODirectory() + "token.json", token_json);
  }
  email_exchange_params[call_number]->callback(email_exchange_params[call_number]->object, response);
  delete email_exchange_params[call_number];
  email_exchange_params.erase(call_number);
  modioFreeResponse(&response);
}
