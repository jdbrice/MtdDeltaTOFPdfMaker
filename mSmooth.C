


Double_t spline_4nodes(Double_t *x, Double_t *par)
{
   /*Fit parameters:
   par[0-3]=X of nodes (to be fixed in the fit!)
   par[4-7]=Y of nodes
   par[8-9]=first derivative at begin and end (to be fixed in the fit!)
   */
   Double_t xx = x[0];
   Double_t xn[4] = { par[0], par[1], par[2], par[3] };
   Double_t yn[4] = { par[4], par[5], par[6], par[7] };
   Double_t b1 = par[8];
   Double_t e1 = par[9];
   TSpline3 sp3("sp3", xn, yn, 4, "b1e1", b1, e1);
   return sp3.Eval(xx);
}




void mSmooth(){

	TFile * f = new TFile( "deltaTOF_pdfs.root", "READ" );

	// TF1 *f_spline4 = new TF1("f_spline4", spline_4nodes, -1, 1, 10); // npars = 2*nodes+2


	TH1 * hbg = (TH1*)f->Get( "bg" );


	// TH1 * hbg= new TH1D( "hbg", "h", 100, -10, 10 );
	// hbg->FillRandom( "gaus" );

	// hbg->Fit( f_spline4, "R", "", -1, 1 );


	TH1 * hsbg = ( TH1* )hbg->Clone("hsbg");
	hsbg->Reset();

	TRandom3 rnd;

	float bw = hbg->GetBinWidth(10);
	float nb = 50;

	gRandom->SetSeed(0);

	hbg->Rebin(4);

	for ( size_t i = 0; i < 10000000; i++ ){
		float x = gRandom->Rndm() * 100 - 50;
		float v = hbg->Interpolate( x );

		hsbg->Fill( x, v ); 
	}


	hbg->SetLineColor(kBlack);
	
	hbg->DrawNormalized();
	hsbg->DrawNormalized("same");
	gPad->SetLogy(1);


}