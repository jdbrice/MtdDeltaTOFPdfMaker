

void compare_smear( TH2 * h2, int iBin = 1 ){
	TH1 * hs = h2->ProjectionY( TString::Format( "projection_%d", iBin), iBin, iBin);

	int dY_min = h2->GetXaxis()->GetBinLowEdge( iBin );
	int dY_max = h2->GetXaxis()->GetBinUpEdge( iBin );
	
	TH1 * hs1 = (TH1*)hs->Clone( TString::Format("dY_%d_to_%d_sampled1", dY_min, dY_max ) );
	TH1 * hs2 = (TH1*)hs->Clone( TString::Format("dY_%d_to_%d_sampled2", dY_min, dY_max ) );
	TH1 * hs3 = (TH1*)hs->Clone( TString::Format("dY_%d_to_%d_sampled3", dY_min, dY_max ) );
	TH1 * hs4 = (TH1*)hs->Clone( TString::Format("dY_%d_to_%d_sampled4", dY_min, dY_max ) );

	hs1->Reset();
	hs2->Reset();
	hs3->Reset();
	hs4->Reset();

	TRandom3 r3;
	r3.SetSeed(0);


	for ( int i = 0; i < 500000; i++ ){
		float rs = hs->GetRandom();
		hs1->Fill( rs );
		hs2->Fill( rs + r3.Gaus( 0, 0.1 ) );
		hs3->Fill( rs + r3.Gaus( 0, 0.2 ) );
		hs4->Fill( rs + r3.Gaus( 0, 0.5 ) );
	}

	hs1->Draw();
	hs2->SetLineColor(kRed);
	hs2->Draw("same");
	hs3->SetLineColor(kBlack);
	hs3->Draw("same");

	hs4->SetLineColor(kGreen);
	hs4->Draw("same");


}


void test_smearing(){

	TFile * f = new TFile( "deltaTOF_pdfs.root " );

	TFile * output = new TFile( "smear_comparison.root", "RECREATE" );
	TH2 * h2 = (TH2*)f->Get( "bg_vs_dY" );

	for ( int i = 1; i <= h2->GetXaxis()->GetNbins(); i++ ){
		compare_smear( h2, i );
	}

	output->Write();



}