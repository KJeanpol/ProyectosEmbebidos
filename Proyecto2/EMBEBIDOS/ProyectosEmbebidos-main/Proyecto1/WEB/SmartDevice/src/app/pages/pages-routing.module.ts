import { NgModule } from '@angular/core';
import { Routes, RouterModule } from '@angular/router';

import { PagesComponent } from './pages.component';
import { HomeComponent } from './home/home.component';

const routes: Routes = [{
  path: '',
  component: PagesComponent,
  children: [
    { path: 'home', component: HomeComponent },
    { path: '', redirectTo: 'home', pathMatch: 'full', }

  ],
}];

@NgModule({
  imports: [RouterModule.forChild(routes)],
  exports: [RouterModule],
})
export class PagesRoutingModule { }

export const routedComponents = [
  PagesComponent,
  HomeComponent
];
