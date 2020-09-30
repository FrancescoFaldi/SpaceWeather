{

  //Canvas
  gStyle->SetCanvasColor(kWhite);
  gStyle->SetPadColor(kWhite);
  gStyle->SetStatColor(kWhite);
  gStyle->SetPalette(1,0);
  gStyle->SetOptFit(1111);
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetFrameBorderMode(0);
  gStyle->SetLegendBorderSize();
  gStyle->SetHistLineWidth(2);
  gStyle->SetFrameLineWidth(2);
  gStyle->SetFrameBorderSize(2);
  gStyle->SetGridWidth(0.5);
  gStyle->SetTickLength(0.05);
  gStyle->SetStatX(0.84);
  gStyle->SetStatY(0.89);
  gStyle->SetStatH(0.1);
  gStyle->SetStatW(0.15);
  
  gStyle->SetPadLeftMargin(0.15);
  gStyle->SetPadRightMargin(0.15);
  gStyle->SetPadTopMargin(0.10);
  gStyle->SetPadBottomMargin(0.15);
  
  //Legend
  gStyle->SetLegendBorderSize(1);
  
  //Graphs
  gStyle->SetEndErrorSize(0);
  gStyle->SetErrorX(0);
  gStyle->SetMarkerStyle(20);
  gStyle->SetMarkerSize(1);
  gStyle->SetLineWidth(2);

  //Axis Labels
  gStyle->SetLabelSize(0.06,"X");
  gStyle->SetLabelSize(0.06,"Y");
  gStyle->SetLabelSize(0.06,"Z");
  gStyle->SetTitleSize(0.06,"X");
  gStyle->SetTitleSize(0.06,"Y");
  gStyle->SetTitleSize(0.06,"Z");
  gStyle->SetTitleSize(0.07,"title");
  gStyle->SetTitleOffset(1.10,"X");
  gStyle->SetTitleOffset(1.05,"Y");
  gStyle->SetTitleOffset(1.00,"Z");
  gStyle->SetTitleFont(62,"X");
  gStyle->SetTitleFont(62,"Y");
  gStyle->SetTitleFont(62,"Z");
  gStyle->SetTitleFont(62,"title");
  
  //color palette -  Karen's colors
  const int NRGBs = 5;
  const int NCont = 255;
  double stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
  double red[NRGBs] = { 0.00, 0.00, 0.87, 1.00, 0.51 };
  double green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
  double blue[NRGBs] = { 0.51, 1.00, 0.12, 0.00, 0.00 };
  TColor::CreateGradientColorTable(NRGBs,stops,red,green,blue,NCont);
  gStyle->SetNumberContours(NCont); 
  
  gStyle->cd();
  
  printf("Style set\n");
  
}
