//////////// cards
const cards = {
  tutor: (t) =>
    `<div class="bg-white flex flex-col gap-2 p-4 rounded-lg w-full border">
      <h3 class="font-semibold">${t.nome}</h3>
      <div class="flex flex-col text-sm gap-1">
        <p>Celular: ${t.numero}</p>
        <p>Endereço: ${t.endereco}</p>
      </div>
      </div>
      `,
  pet: (p) =>
    `<div class="bg-white flex flex-col gap-2 p-4 rounded-lg w-full border">
      <h3 class="font-semibold">${p.nome}</h3>
      <div class="flex flex-col text-sm gap-1">
        <p>Tipo: ${p.tipo}</p>
        <p>Idade: ${p.idade}</p>
        <p>Peso: ${p.peso}</p>
        <p>Raça: ${p.raca}</p>
      </div>
      </div>`,
};

//////////// search form

const searcher = {
  tutores: (query) => {
    const nomeTutor = query.toLowerCase();
    const tutores = JSON.parse(localStorage.getItem("tutores")) || [];
    const resultado = tutores.filter((tutor) =>
      tutor.nome.toLowerCase().includes(nomeTutor)
    );

    searcher.resultadosDaBusca(resultado, cards.tutor);
  },
  pets: (query) => {
    const nomePet = query.toLowerCase();
    const pets = JSON.parse(localStorage.getItem("pets")) || [];
    const resultado = pets.filter((pet) =>
      pet.nome.toLowerCase().includes(nomePet)
    );

    searcher.resultadosDaBusca(resultado, cards.pet);
  },
  resultadosDaBusca: (resultado, cardFunction) => {
    const resultadoDiv = document.getElementById("resultadosDaBusca");
    showSection("resultadosDaBusca");

    document.getElementById("conteudoResultadoBusca").innerHTML =
      resultado.length
        ? resultado.map(cardFunction).join("")
        : "<p class='bg-gray-50'>Nenhum resultado encontrado.</p>";
  },
};

////////////////////////////////////// main

function showSection(sectionId) {
  atualizarDados();

  const sections = document.querySelectorAll("section");
  sections.forEach((section) => (section.style.display = "none"));
  const section = document.getElementById(sectionId);
  if (section) {
    section.style.display = "";
  }
}

document
  .getElementById("formCadastroTutor")
  ?.addEventListener("submit", function (event) {
    event.preventDefault();
    const nomeTutor = document.getElementById("nomeTutor").value;
    const celularTutor = document.getElementById("celularTutor").value;
    const enderecoTutor = document.getElementById("enderecoTutor").value;

    const tutores = JSON.parse(localStorage.getItem("tutores")) || [];
    const novoTutor = {
      id: Date.now(),
      nome: nomeTutor,
      numero: celularTutor,
      endereco: enderecoTutor,
    };
    tutores.push(novoTutor);
    localStorage.setItem("tutores", JSON.stringify(tutores));
    alert(`Tutor cadastrado: ${nomeTutor}`);
    document.getElementById("formCadastroTutor").reset();
    loadTutors();
    showSection("lista-tutores");
  });

// Função para cadastrar um pet
document
  .getElementById("formPet")
  ?.addEventListener("submit", function (event) {
    event.preventDefault();
    const nomePet = document.getElementById("nomePet").value;
    const tipoPet = document.getElementById("tipoPet").value;
    const idadePet = document.getElementById("idadePet").value;
    const pesoPet = document.getElementById("pesoPet").value;
    const racaPet = document.getElementById("racaPet").value;
    const tutorPet = document.getElementById("tutorPet").value;

    const pets = JSON.parse(localStorage.getItem("pets")) || [];
    const novoPet = {
      nome: nomePet,
      tipo: tipoPet,
      idade: idadePet,
      peso: pesoPet,
      raca: racaPet,
      tutor: tutorPet,
    };
    pets.push(novoPet);
    localStorage.setItem("pets", JSON.stringify(pets));
    document.getElementById("formPet").reset();
    alert(`Pet cadastrado: ${nomePet}`);
    showSection("lista-pets");
  });

// Função para carregar os tutores no formulário de cadastro de pet
function loadTutorsPet() {
  const tutorSelect = document.getElementById("tutorPet");
  const tutores = JSON.parse(localStorage.getItem("tutores")) || [];

  tutorSelect.innerHTML = '<option value="">Selecione o Tutor</option>'; // Reseta o select
  tutores.forEach((tutor) => {
    const option = document.createElement("option");
    option.value = tutor.id;
    option.textContent = tutor.nome + " - " + tutor.numero;
    tutorSelect.appendChild(option);
  });
}

// Função para carregar os tutores no formulário de atendimento
function loadAtendimentoPet() {
  const petSelect = document.getElementById("petAtendimento");
  const pets = JSON.parse(localStorage.getItem("pets")) || [];

  petSelect.innerHTML = '<option value="">Selecione o Pet</option>'; // Reseta o select
  pets.forEach((pet) => {
    const option = document.createElement("option");
    option.value = pet.id;
    option.textContent = pet.nome;
    petSelect.appendChild(option);
  });
}

// Função para cadastrar atendimento
document
  .getElementById("formAtendimento")
  ?.addEventListener("submit", function (event) {
    event.preventDefault();
    const petAtendimento = document.getElementById("petAtendimento").value;
    const descricaoAtendimento = document.getElementById(
      "descricaoAtendimento"
    ).value;

    const atendimentos = JSON.parse(localStorage.getItem("atendimentos")) || [];
    const novoAtendimento = {
      pet: petAtendimento,
      descricao: descricaoAtendimento,
      status: "Em andamento",
    };
    atendimentos.push(novoAtendimento);
    localStorage.setItem("atendimentos", JSON.stringify(atendimentos));
    alert(`Atendimento registrado para o pet ${petAtendimento}`);
    document.getElementById("formAtendimento").reset();
  });

// Função para carregar atendimentos
function loadAtendimentos() {
  const listaAtendimentosDiv = document.getElementById("listaAtendimentos");
  const atendimentos = JSON.parse(localStorage.getItem("atendimentos")) || [];
  listaAtendimentosDiv.innerHTML = atendimentos
    .map(
      (atendimento) =>
        `<p>Pet: ${atendimento.pet}, Descrição: ${atendimento.descricao}, Status: ${atendimento.status}</p>`
    )
    .join("");
}

// Função para exibir o próximo atendimento
function showProximoAtendimento() {
  const atendimentos = JSON.parse(localStorage.getItem("atendimentos")) || [];
  const proximo = atendimentos.find(
    (atendimento) => atendimento.status === "Em andamento"
  );
  const proximoDiv = document.getElementById("proximoAtendimento");
  proximoDiv.innerHTML = proximo
    ? `<p>Próximo Atendimento: Pet ${proximo.pet}, Descrição: ${proximo.descricao}</p>`
    : "<p>Não há atendimentos em andamento.</p>";
}

// Função para carregar todos os tutores
function loadTutors() {
  const listaTutoresDiv = document.getElementById("listaTutores");
  const tutores = JSON.parse(localStorage.getItem("tutores")) || [];
  listaTutoresDiv.innerHTML = tutores.map(cards.tutor).join("");
}

// Função para carregar todos os pets
function loadPets() {
  const listaPetsDiv = document.getElementById("listaPets");
  const pets = JSON.parse(localStorage.getItem("pets")) || [];

  listaPetsDiv.innerHTML = pets.length
    ? pets.map(cards.pet).join("")
    : `<div class="w-full text-center">Você ainda não cadastrou pets!</div>`;
}

function atualizarDados() {
  loadTutors();
  loadPets();
  loadAtendimentos();
  showProximoAtendimento();

  loadTutorsPet();
  loadAtendimentoPet();
}

showSection("home");
atualizarDados();

document.getElementById("searchForm")?.addEventListener("submit", (e) => {
  e.preventDefault();
  const query = e.target.elements?.query?.value;
  if (query.length <= 3) {
    return;
  }
  const option = e.target.elements?.options?.value;

  switch (option) {
    case "tutor":
      searcher.tutores(query);
      break;
    case "pet":
      searcher.pets(query);
      break;
    default:
      alert("Selecione uma opção válida");
  }
});
