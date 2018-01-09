#include "modio_c.h"

void onModLogoEdited(void* object, ModioResponse response, u32 mod_id)
{
  bool* wait = object;
  printf("Edit mod logo response: %i\n", response.code);
  if(response.code == 201)
  {
    printf("Image downloaded successfully!\n");
  }
  *wait = false;
}

void onModGet(void* object, ModioResponse response, ModioMod mod)
{
  bool* wait = object;
  printf("On mod get response: %i\n",response.code);
  if(response.code == 200)
  {
    printf("Id:\t%i\n",mod.id);
    printf("Name:\t%s\n",mod.name);

    printf("Editing mod logo...\n");

    // Now we provide the mod id and the local image path to upload the new logo. Thumbnails will be generated automatically
    modioEditModLogo(wait, mod.id, (char*)"../ModExample/logo.png", &onModLogoEdited);
  }else
  {
    *wait = false;
  }
}

int main(void)
{
  modioInit(7, (char*)"e91c01b8882f4affeddd56c96111977b");

  bool wait = true;

  // Let's start by requesting a single mod
  printf("Please enter the mod id: \n");
  u32 mod_id;
  scanf("%i", &mod_id);

  printf("Getting mod...\n");
  modioGetMod(&wait, mod_id, &onModGet);

  while(wait)
  {
    modioProcess();
  }

  modioShutdown();

  printf("Process finished\n");

  return 0;
}
