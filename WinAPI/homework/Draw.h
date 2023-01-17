#pragma once
#include "stdafx.h"
//
#define 엉겅퀴		RGB(220,220,240) 
#define RAVENDER	RGB(230,230,250)
#define WHITE		RGB(255,255,255)
#define BLACK		RGB(0,0,0)
#define DARK_GRAY	RGB(25,25,25)
#define GRAY		RGB(140,140,140)
#define LIGHT_GRAY	RGB(200,200,200)
#define HAIR		RGB(160,140,180)
using namespace std;
class Face {
private:
	HGDIOBJ original = NULL;
	vector<POINT>::iterator iter;
	vector<POINT>::reverse_iterator riter;


	//프린트 순서 : 뒷머리->머리통 -> 머리통 그림자->얼굴->앞머리->손
#pragma region 머리통 좌표....
	POINT head[39] = { {280,115},{319,107},{369,114},	{490,303},
		/*얼굴외곽선*/		{466,311},{490,300},{507,308},{513,330},{517,343},{515,361},{507,382},{502,402},{493,406},{481,413},
							{472,444},{455,475},{419,503},{387,537},{330,560},{274,565},{234,554},{208,518},{193,487},{185,474},
							{178,462},{172,448},{167,433},{163,424},{161,414},{159,403},{159,392},{156,381},{152,342},{147,289},
							{158,236},{175,185},{197,148},{218,131},{248,120} };

	vector<POINT> lftShadow_1 = { {248,120},{253,164},{221,206},{191,189},{175,185}, {184,169}, {197,148},{218,131} };
	vector<POINT> lftShadow_2 = { {147,289},{151,260}, {158,236}, {163,214}, {175,185},{191,189},{221,206},{223,238},{215,255},{187,270},{168,291} };
	vector<POINT> lftShadow_3 = { {168,291},{186,284},{214,285},{242,292},{266,309},{266,330},{250,354},{222,369},{187,381},{170,382},{156,381},{154,359},{152,342},{150,325},{148,311}, {147,289} };
	vector<POINT> lftShadow_4 = { {193,487},{178,462},{167,433},{161,414},{159,403},{156,381}, {170,382},{188,408},{202,431},{217,454},{255,465},{223,477},{212,481},{204,484} };
	vector<POINT> lftShadow_5 = { {255,465},{276,502},{280,522},{279,541},{274,565},{250,561}, {234,554},{219,536}, {208,518},{199,505}, {193,487},{204,484}, {212,481},{223,477} };
	vector<vector<POINT>> faceShadow = { lftShadow_1 ,lftShadow_2,lftShadow_3,lftShadow_4 ,lftShadow_5 };


	vector<POINT> lftShadowEraser = { {255,465} ,{170,382},{173,398},{190,430},{222,455} };
	vector<POINT> rightShadow1 = { {370,342},{340,347},{314,344},{300,332},{295,317},{293,293},{305,276},{330,265},{358,262},{399,264},{412,275}, {416,291} };
	vector<POINT> rightShadowEraser = { {370,342}, {416,291},{406,307},{385,311},{374,323} };
	vector<vector<POINT>> fShadowEraser = { lftShadowEraser };
#pragma endregion

#pragma region 머리카락 좌표
	//뒤에 rightHairLine_2_1역순으로 붙여야함. 역방향이터레이터나 i--해야함
	vector<POINT> vBackhair = {
			{279,105},{287,94},{306,85},{327,81}

	,{344,82},{365,88},{379,91},{403,101},{428,115}
	,{441,126},{453,137},{462,148},{468,156},{479,175}
	,{483,185},{489,197},{498,220},{503,237},{505,248}
	,{511,262},{514,271},{519,278},{525,287},{531,292}
	,{538,302},{543,305},{554,306}
	,{532,306}
	,{528,324},{529,336},{530,360},{529,374},{525,388}
	,{522,403},{514,421},{486,458},{463,476}
		//rightHairLine_2_1역순으로 붙여야함. 역방향이터레이터나 i--해야함
	};
	vector<POINT> vFrontHair = {
	{279,105},{287,94},{306,85},{327,81}

	,{345,91},{361,92},{374,97},{391,103},{407,117},{415,129},{421,139},{426,150},{432,164},{437,179},{440,179},{441,213},{443,228},{446,243},{452,254},{460,266}
	};	//rightHairLine3 + RightHairLine_4역방향 붙여야함

	vector<POINT> rghtHairLine_1 = {
		//line2겹치는부분
		{279,105},{287,94},{306,85},{327,81}

	,{344,82},{365,88},{379,91},{403,101},{428,115},{441,126},{453,137},{462,148},{468,156},{479,175},{483,185},{489,197},{498,220},{503,237},{505,248},{511,262},{514,271},{519,278},{525,287},{531,292},{538,302},{543,305},{554,306}
	};
	//2_1을 역순으로 backHair에 넣기위해서 분리함..
	vector<POINT> rghtHairLine_2_1 = {
		//line1겹치는부분
	{279,105},{287,94},{306,85},{327,81}

	,{345,91},{361,92},{374,97},{391,103},{407,117},{415,129},{421,139},{426,150},{432,164},{437,179},{440,179},{441,213},{443,228},{446,243},{452,254},{460,266}

		//line3겹치는부분(시작점)
	,{469,278}
	};
	vector<POINT> rightHairLine_2_2 = { {466,299},{484,311},{499,312},{521,314}

		//line1과 연결하면 좋을..
		,{532,306}

		,{543,313},{556,317},{569,317} };
	vector<POINT> rghtHairLine_3 = {
		{469,278},{474,294},{487,305},{500,316},{513,328},

		//line4와 연결됨
		{534,346},{539,353},{546,362}
	};
	vector<POINT> rghtHairLine_4 = {
		{283,152},{291,132},{306,125},{317,125},{329,132},{339,144},{348,157},{355,173},{358,194},{359,215},{361,233},{367,251},{368,263},{374,275},{384,287},{395,295},{411,304},{431,315},{445,324},{457,331},{470,335},{481,338},{494,341},{507,344},{521,343},{534,345}
	};
	vector<POINT> lftHairLine_1 = {
		{279,105},{268,95},{247,91},{231,91},{216,97},{201,105},{186,116},{176,131},{166,145},{157,159},{147,173},{140,186},{135,204},{129,220},{126,239},{124,257},{122,279},{126,295},{129,308},{131,324},{133,337},{134,355},{133,373},{136,389},{132,399},{116,411 }

	};
	vector<POINT> lftHairLine_2 = { {283,152},{263,139},{251,144},{240,155},{228,164},{219,173},{210,188},{200,202},{189,218},{183,237},{177,256},{173,270},{169,287},{168,305},{166,322},{164,340},{161,358},{162,371},{154,381},{147,387},{141,395},{132,401},{114,411} };
	vector<POINT> lftHairLine_3 = {};

#pragma endregion

#pragma region 얼굴좌표

	vector<POINT> face_lfteyebrow = {
		{227,307},{224,308},{219,309},{213,308},{204,305},
		{196,305},{188,307},{183,310},{179,312},{174,315},
		{170,318},{167,319},{162,322},{159,324},{158,320},
		{164,318},{161,314},{165,311},{167,315},{169,308},
		{172,311},{171,305},{176,307},{175,301},{179,305},
		{182,303},{180,299},{185,297},{186,301},{190,300},
		{188,295},{192,295},{194,299},{195,302},{198,299},
		{202,302},{201,299},{203,295},{206,300},{208,304},
		{211,301},{209,297},{213,298},{214,304},{219,305},
		{218,302},{217,299},{221,299},{222,304},{224,300},

		{227,298},{222,295},{215,294},{208,292},{201,291},
		{196,290},{191,291},{185,293},{178,295},{173,297},
		{168,300},{165,303},{161,306},{159,311},{158,318}
	};
	vector<POINT>face_rghteyebrow = {
		{294,294},{299,291},{305,283},{312,278},{315,276},
		{321,273},{326,271},{332,268},{339,263},{347,259},
		{355,257},{364,258},{370,257},{379,258},
		{298,286},{297,285},{307,277},{306,271},{312,271},
		{311,268},{315,264},{323,261},{329,263},{334,263},
		{330,258},{335,255},{339,256},{344,259},{344,254},
		{346,248},{355,253},{359,256},
		{290,287},{291,280},{292,276},{295,272},{300,268},
		{305,266},{311,263},{316,260},{322,257},{326,254},
		{332,252},{339,249},{345,248},{350,247},{356,248},
		{364,250},{372,253}
	};
	vector<POINT> vface_rghteye = {
		{316,333},{321,333},{330,334},{344,333},{357,330},{366,324},{375,318},{379,310},{371,308},{361,307},{350,307},{336,311},{325,318},{318,325},{315,330}
	};
	vector<POINT> face_rghteyeline = {
		{382,303},{371,300},{356,300},{341,303},{327,311},{320,318},{316,325},{315,332},{316,333}
	};
	vector<POINT> vface_righteyehole = {
		{382,303},{371,300},{356,300},{341,303},{327,311},{320,318},{316,325},{315,332},{316,333},
		{327,336},{342,339},{358,336},{371,331},{389,320},{392,312}
	};

	POINT hand;

	//폴리곤에 넣을 배열들 (head는 위에 있음)
	POINT** fShadowPoly;
	POINT** fShadowErPoly;
	POINT* backHair;	//vBackHair + rightHairLine_2_1(역방향)
	POINT* frontHair;	//vFrontHair + rightHairLine_3 + RightHairLine_4(역방향) + leftHairLine_2+leftHairLine_1(역방향)
	POINT frontHair_[46] = 
	{
		{344,82},{365,88},{379,91},{403,101},{428,115},{441,126},{453,137},{462,148},{468,156},{479,175},
		{483,185},{489,197},{498,220},{503,237},{505,248},{511,262},{514,271},{519,278},{525,287},{531,292},
		{538,302},{543,305},{554,306},{533,306},{515,303}, { 521,314 },{ 499,312 },{ 484,311 },{466, 299},{469,278},
		{460,266},{452,254},{446,243},{443,228},{441,213},{440,179},{437,179},{432,164},{426,150},{421,139},
		{415,129},{407,117},{391,103},{374,97},{361,92},{345,91}
	};
	POINT* face_righteyehole;
	POINT* face_rghteye;

public:
	Face() {
		for (riter = rghtHairLine_2_1.rbegin(); riter < rghtHairLine_2_1.rend(); riter++) {
			vBackhair.push_back(*riter);
		}
		backHair = new POINT[vBackhair.size()];
		iter = vBackhair.begin();
		for (int i = 0; iter < vBackhair.end(); iter++) {
			backHair[i] = *iter;
			i++;
		}
		for (int i = 0; i < rghtHairLine_3.size(); i++)
		{
			vFrontHair.push_back(rghtHairLine_3[i]);
		}
		riter = rghtHairLine_4.rbegin();
		for (riter; riter < rghtHairLine_4.rend(); riter++) {
			vFrontHair.push_back(*riter);
		}
		for (int i = 0; i < lftHairLine_2.size(); i++)
		{
			vFrontHair.push_back(lftHairLine_2[i]);
		}
		riter = lftHairLine_1.rbegin();
		for (riter; riter < lftHairLine_1.rend(); riter++) {
			vFrontHair.push_back(*riter);
		}
		frontHair = new POINT [vFrontHair.size()];
		for (int i = 0; i < vFrontHair.size(); i++) {
			frontHair[i] = vFrontHair[i];
		}
		face_righteyehole = new POINT[vface_righteyehole.size()];
		for (int i = 0; i < vface_righteyehole.size(); i++) {
			face_righteyehole[i] = vface_righteyehole[i];
		}
		face_rghteye = new POINT[vface_rghteye.size()];
		for (int i = 0; i < vface_rghteye.size(); i++) {
			face_rghteye[i] = vface_rghteye[i];
		}
	}
	~Face() {
		delete[] frontHair; 
		delete[] backHair;
		delete[] fShadowPoly;
		delete[] fShadowErPoly;
		delete[] face_righteyehole;
		delete[] face_rghteye;
	}
	//프린트 순서 : 뒷머리->머리통 -> 머리통 그림자->얼굴->앞머리->손
	void draw(HDC hdc) {
		original = SelectObject(hdc, GetStockObject(DC_PEN));
		SelectObject(hdc, GetStockObject(DC_BRUSH));

		drawBackHair(hdc);
		drawHead(hdc);
		drawFace(hdc);
		drawFrontHair(hdc);
		drawHand(hdc);
}
	void drawHead(HDC hdc) {
		SetDCBrushColor(hdc, WHITE);	//면색
		SetDCPenColor(hdc, BLACK);	//펜색

		Polygon(hdc, head, 39);
		drawShadow(hdc);
	}
	void drawShadow(HDC hdc) {
		SetDCBrushColor(hdc, RAVENDER);	//면색
		SetDCPenColor(hdc, 엉겅퀴);	//펜색

		//얼굴그림자 좌표 벡터를 배열로 바꾸기
		POINT** fShadowPoly = new POINT * [faceShadow.size()];
		for (int i = 0; i < faceShadow.size(); i++) {
			fShadowPoly[i] = new POINT[faceShadow[i].size()];
			for (int j = 0; j < faceShadow[i].size(); j++) {
				fShadowPoly[i][j] = faceShadow[i][j];
			}
		}
		POINT** fShadowErPoly = new POINT * [fShadowEraser.size()];
		for (int i = 0; i < fShadowEraser.size(); i++) {
			fShadowErPoly[i] = new POINT[fShadowEraser[i].size()];
			for (int j = 0; j < fShadowEraser[i].size(); j++) {
				fShadowErPoly[i][j] = fShadowEraser[i][j];
			}
		}


		//얼굴 그림자 그리기
		for(int i = 0; i<faceShadow.size();i++)
		{
			Polygon(hdc, fShadowPoly[i], faceShadow[i].size());
			//for(int j = 0; j< faceShadow[i].size()*5; j++)
			//{
			//int rand1 = RND->getInt(faceShadow[i].size());
			//int rand2 = RND->getInt(faceShadow[i].size());
			//	LineMake(hdc, fShadowPoly[i][rand1].x, fShadowPoly[i][rand1].y, fShadowPoly[i][rand2].x, fShadowPoly[i][rand2].y);
			//	//char strPT[50];
			//	//wsprintf(strPT, "%d,%d에서 %d,%d로", fShadowPoly[i][rand1].x, fShadowPoly[i][rand1].y, fShadowPoly[i][rand2].x, fShadowPoly[i][rand2].y);
			//	//TextOut(hdc, i * 100, j * 20, strPT, strlen("strPT"));
			//}//for j
		}//for i
		//얼굴 그림자 빈부분 지우기
		for(int i = 0; i< fShadowEraser.size(); i++)
		{
			SetDCBrushColor(hdc, WHITE);	//면색
			SetDCPenColor(hdc, WHITE);	//펜색
			Polygon(hdc, fShadowErPoly[i], fShadowEraser[i].size());
		LineMake(hdc, fShadowErPoly[i][0].x, fShadowErPoly[i][0].y, fShadowErPoly[0][1].x, fShadowErPoly[0][1].y);
		}

		SetDCPenColor(hdc, RAVENDER);	//펜색
		SetDCBrushColor(hdc, RAVENDER);	//면색
		Polygon(hdc, face_righteyehole, vface_righteyehole.size());

	}

	void drawBackHair(HDC hdc) {
		SetDCBrushColor(hdc, RGB(120,105,135));	//면색
		SetDCPenColor(hdc, DARK_GRAY);	//펜색

		Polygon(hdc, backHair, vBackhair.size());
	}

	void drawFrontHair(HDC hdc) {
		SetDCBrushColor(hdc, HAIR);	//면색
		SetDCPenColor(hdc, LIGHT_GRAY);	//펜색
		Polygon(hdc, frontHair_, sizeof(frontHair_) / sizeof(frontHair_[0]));
		Polygon(hdc, frontHair, vFrontHair.size());
		//vFrontHair + rightHairLine_3 + RightHairLine_4(역방향) + leftHairLine_2+leftHairLine_1(역방향)
	}

	void drawFace(HDC hdc) {
		SetDCPenColor(hdc,RGB(120, 105, 135));	//펜색

		//왼쪽 눈썹
		short count = 0;
		while (true) {
			POINT pt_a = face_lfteyebrow[RND->getInt(face_lfteyebrow.size() -15)];
			POINT pt_b = face_lfteyebrow[RND->getInt(face_lfteyebrow.size())];
			if ((pt_a.x - pt_b.x) * (pt_a.y - pt_b.y) < 0) {
				LineMake(hdc, pt_a, pt_b);
				count++;
			}
			if (count == 50) break;
		}

		//오른쪽눈썹
		count = 0;
		while (true) {
			POINT pt_a= face_rghteyebrow[RND->getInt(face_rghteyebrow.size()/1.5)];
			POINT pt_b= face_rghteyebrow[RND->getInt(face_rghteyebrow.size())];
			if ((pt_a.x - pt_b.x) * (pt_a.y - pt_b.y) < 0) {
				LineMake(hdc, pt_a, pt_b);
				count++;
			}
			if (count == 50) break;
		}

		//오른쪽 눈
		MoveToEx(hdc, face_rghteyeline[0].x, face_rghteyeline[0].y, NULL);
		for (int i = 1; i < face_rghteyeline.size(); i++) {
			LineTo(hdc, face_rghteyeline[i].x, face_rghteyeline[i].y);
		}
		for (int i = 1; i < vface_rghteye.size(); i++) {
			LineTo(hdc, face_rghteye[i].x, face_rghteye[i].y);
		}
		SetDCPenColor(hdc, RAVENDER);	//펜색
		SetDCBrushColor(hdc, WHITE);
		Polygon(hdc, face_rghteye, vface_rghteye.size());

	}

	void drawHand(HDC hdc) {

	}

};
class Bye {

};