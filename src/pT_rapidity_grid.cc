//
// Created by mikhail on 12/24/20.
//

#include <TF1.h>
#include <TMath.h>
#include <TFile.h>
#include <TCanvas.h>

int main(){
  double y=-0.01;
  auto file =  TFile::Open("pT_y_grid.root", "recreate");
  std::vector<TF1> iso_rapidity;
  while ( y<1.49 ){
    std::string str_2y{ std::to_string(exp(2.0*y)) };
    double ratio = (exp(2*y)-1) / ( exp(2*y)+1 );
    double p_lo = sqrt( 0.938*0.938*ratio*ratio/( 0.99+ratio*ratio ) );
    if( ratio < 0.0 )
      p_lo=0.0;
    double p_hi = sqrt( 0.938*0.938*ratio*ratio/( 0.99-ratio*ratio ) );
    std::string formula{ "TMath::ATanH(sqrt(x*x+0.88)/x * ( "+str_2y+"-1 )/( 1 +"+str_2y+" ) )" };
    iso_rapidity.emplace_back( std::data( "y_"+std::to_string(y) ), formula.c_str(), p_hi, 5.0 );
    iso_rapidity.back().Write();
    y+=0.1;
  }
  std::vector<TF1> iso_pT;
  double pT=0.1;
  while ( pT<2.0 ){
    std::string str_pT{ std::to_string(pT) };
    std::string formula{ "TMath::ACosH(x/"+str_pT+")" };
    iso_pT.emplace_back( std::data( "pT_"+std::to_string(pT) ), formula.c_str(), pT, 5.0 );
    iso_pT.back().Write();
    pT+=0.1;
  }
  auto canv = new TCanvas("canv", "");
  canv->cd();
  iso_rapidity.front().Draw();
  for( auto func : iso_rapidity )
    func.Draw("same");
  for( auto func : iso_pT )
    func.Draw("same");
  canv->Write();
  file->Close();
  return 0;
}