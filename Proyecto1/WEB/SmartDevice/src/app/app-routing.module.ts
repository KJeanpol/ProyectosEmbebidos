import { NgModule } from '@angular/core';
import { Routes, RouterModule } from '@angular/router';
//SIEMPRE INCLUIR LOS ROUTING MODULES PARA CARGAR
import {PagesModule} from './pages/pages.module';
import {AuthModule} from './auth/auth.module';


const routes: Routes = [  
  { path: 'pages', loadChildren: './pages/pages.module#PagesModule' },
  { path: 'auth', loadChildren: './auth/auth.module#AuthModule' },
  { path: '', redirectTo: 'auth', pathMatch: 'full' },
  { path: '**', redirectTo: 'auth' }
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
