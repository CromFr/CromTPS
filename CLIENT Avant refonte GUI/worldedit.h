#ifndef WORLDEDIT_H_INCLUDED
#define WORLDEDIT_H_INCLUDED

void LoadEmptyMap();
int ChangeCubeType(int nCubeType);
int ChangeSpecialType(int nSpecialType);
void PlotType(int nPlotingType, int nCubeType, int nSpecialType, struct worldposblock pPosBlock);
void DisplayType(int nPlotingType, int nCubeType, int nSpecialType);
void SaveMap(std::string sMapName);

void WorldEdit();


#endif // WORLDEDIT_H_INCLUDED
