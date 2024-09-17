#include "generadornpc.h"
#include "generadornpc.h"
#include "../lectorarchivos.h"

#include <QDebug>

GeneradorNPC::GeneradorNPC(QRandomGenerator * generador): generadorSkin(generador){
    Random = generador;

    // Lectura de dialogos
    LectorArchivos lector(":/Resources/ArchivosTexto/DialogosRevolucionario.txt");
    DialogosRevolucionario = lector.getArray();
    topeDialogosRev = lector.getTopeArray();

    lector.LeerArchivoNuevo(":/Resources/Dialogos/DialogosRefugiadoPolitico.txt");
    DialogosRefugiado = lector.getArray();
    topeDialogosRef = lector.getTopeArray();

    // Lectura de dialogos para nivel 2
    lector.LeerArchivoNuevo(":/Resources/Dialogos/DialogosEstudiante.txt");
    QString * DialogosEstudiante = lector.getArray();
    topeDialogosEstudiante=lector.getTopeArray();

    lector.LeerArchivoNuevo(":/Resources/Dialogos/DialogosTurista.txt");
    QString * DialogosTurista = lector.getArray();
    topeDialogosTurista=lector.getTopeArray();

    lector.LeerArchivoNuevo(":/Resources/Dialogos/DialogosTrabajador.txt");
    QString *  DialogosTrabajador = lector.getArray();
    topeDialogosTrabajador=lector.getTopeArray();

    DialogosEstancia[0] = DialogosTurista;
    DialogosEstancia[1] = DialogosTrabajador;
    DialogosEstancia[2] = DialogosEstudiante;

    // Lectura de dialogos de nivel 3
    lector.LeerArchivoNuevo(":/Resources/Dialogos/dialogosAcompaniantes.txt");
    this->dialogosAcomps = lector.getArray();
    this->topeDialogosAcomp = lector.getTopeArray();
}


// Esto necesita rework a futuro para distinguir entre caras de Mujeres y Hombres
NPC* GeneradorNPC::getNPCgenerico(int tipo, bool Validez, int nivel){
    NPCcomun* NPCaCrear;
    // 0: Aldeano, 1: Refugiado, 2: Diplomatico, 3: Revolucionario
    if (tipo > 3)
        tipo = Random->bounded(4);

    // Pickeamos un genero
    int valorCentinela2 = Random->bounded(11);
    if (valorCentinela2 < 5)
        valorCentinela2 = 0;
    else if (valorCentinela2 < 10)
        valorCentinela2 = 1;
    else valorCentinela2 = 2;

    // Generamos NPC con los datos basicos
    NPCaCrear = new NPCcomun(this->generos[valorCentinela2], tipo, Validez);

    // Generamos su skin y la seteamos.
    NPCaCrear->setSkin(generadorSkin.getSkin(tipo, this->generos[valorCentinela2]));
    NPCaCrear->setSkinDocs(NPCaCrear->getSkin());

    // Si el NPC es fake, añadimos la posibilidad de contener una imagen falsa.
    if (!Validez){
        int falsificarImagen = Random->bounded(20);
        if (falsificarImagen < 1){
            NPCaCrear->setDatosFalsos("Foto de identificacion invalida\n");
            NPCaCrear->setSkinDocs(generadorSkin.getSimilarSkin(NPCaCrear->getSkin(), NPCaCrear->getGenero(), nivel));
        }
    }

    return NPCaCrear;
}

// ######## Generadores de dialogos #############
void GeneradorNPC::generarDialogos(NPC *npc, int nivel)
{
    GenerarDialogosNivel1(npc);
    if (nivel >= 2)
        GenerarDialogosNivel2(npc);
    if (nivel >= 3)
        GenerarDialogosNivel3(npc);
    if (nivel >= 4)
        GenerarDialogosNivel4(npc);
    if (nivel >= 5)
        GenerarDialogosNivel5(npc);
}

GeneradorNPC::~GeneradorNPC()
{

}

void GeneradorNPC::GenerarDialogosNivel1(NPC *info)
{
    // En esta etapa solo los revolucionarios y los refugiados tendran dialogos
    if (info->getTipo() == 3)
        SortearDialogo(info, DialogosRevolucionario, topeDialogosRev);
    else
        if (info->getTipo() == 1)
            SortearDialogo(info, DialogosRefugiado, topeDialogosRef);
}

void GeneradorNPC::GenerarDialogosNivel2(NPC *info)
{
    Estancia * infoEstancia = info->getEstancia();

    if (!infoEstancia){
        qDebug() << "Puntero Estancia NULO";
        return;
    }

    QString TipoEstancia = infoEstancia->getTipoEstancia();
    int tipoEst = 0, topeEstancia = 1;

    // Decidimos que tipo es el NPC
    if (TipoEstancia == "Turismo"){
        tipoEst = 0;
        topeEstancia = topeDialogosTurista;
    } else if (TipoEstancia == "Trabajo") {
        tipoEst = 1;
        topeEstancia = topeDialogosTrabajador;

    }   else if (TipoEstancia == "Estudios") {
        tipoEst = 2;
        topeEstancia = topeDialogosEstudiante;
    }

    // Sorteamos si habra un dialogo falso o no.
    int Sorteo = Random->bounded(10);
    if (info->getValidez())
        Sorteo = 9;

    if (Sorteo > 4){
        SortearDialogo(info, DialogosEstancia[tipoEst], topeEstancia);
    } else {
        // Obtenemos un dialogo de otro tipo de estancia
        int tipoDiferente = Random->bounded(3);
        while (tipoDiferente == tipoEst)
            tipoDiferente = Random->bounded(3);

        switch(tipoDiferente){
        case 0: topeEstancia = topeDialogosTurista;
            break;
        case 1: topeEstancia = topeDialogosTrabajador;
            break;
        default: topeEstancia = topeDialogosEstudiante;
            break;
        }

        SortearDialogo(info, DialogosEstancia[tipoDiferente], topeEstancia);
    }
}

void GeneradorNPC::GenerarDialogosNivel3(NPC *info)
{
    ListaAcompaniantes * infoLista = info->getListaAcompaniantes();
    if (!infoLista){
        qDebug() << "Puntero Acompaniantes NULO";
        return;
    }

    QString dialogo;
    bool validez = infoLista->getValidez();
    int CantidadAcompaniantes = infoLista->getCantAcompaniantes();

    if (validez) { // si el documento es valido.. genero dialogos validos
        dialogo = dialogosAcomps[CantidadAcompaniantes];
        info->setDialogo(dialogo);
    } else { // genero dialogos invalidos
        dialogo = generarDialogosAcomps(CantidadAcompaniantes);
        info->setDialogo(dialogo);
    }
}

QString GeneradorNPC::generarDialogosAcomps(int CantidadRealAcomp)
{
    int sorteo = Random->bounded(topeDialogosAcomp);
    while(sorteo == CantidadRealAcomp)
        sorteo = Random->bounded(topeDialogosAcomp);

    return dialogosAcomps[sorteo];
}

void GeneradorNPC::GenerarDialogosNivel4(NPC *info)
{

}

void GeneradorNPC::GenerarDialogosNivel5(NPC *info)
{

}

void GeneradorNPC::SortearDialogo(NPC *info, QString * dialogos, int &tope)
{
    int sorteo = Random->bounded(tope);
    QString dialogo = dialogos[sorteo] + "\n";
    info->setDialogo(dialogo);
}

/// ################# GETTERS ##########################


